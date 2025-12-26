package com.example.guiex1.repository.dbrepo;


import java.sql.*;
import java.time.LocalDateTime;
import java.util.*;

import com.example.guiex1.domain.Message;
import com.example.guiex1.domain.Utilizator;
import com.example.guiex1.domain.Friendship;
import com.example.guiex1.domain.Validator;
import com.example.guiex1.repository.Repository;
import java.sql.*;
import java.util.HashMap;
import java.util.Map;
import java.util.Optional;
import java.time.LocalDateTime;

public class DBMessageRepo implements Repository<Long,Message> {
    private static final String URL = "jdbc:postgresql://127.0.0.1:5432/socialnetworking";
    private static final String USER = "postgres";
    private static final String PASSWORD = "1205";
    private Validator<Message> validator;

    public DBMessageRepo(Validator<Message> validator) {
        this.validator = validator;
    }

    protected Utilizator getOwner(ResultSet resultSet) throws SQLException {
        Long id_sender = resultSet.getLong("id_sender");
        String firstName = resultSet.getString("first_name");
        String lastName = resultSet.getString("last_name");
        String username = resultSet.getString("username");
        String password = resultSet.getString("password");
        Utilizator sender = new Utilizator(firstName, lastName, password,username,null,null);
        sender.setId(id_sender);
        return sender;
    }

    private Utilizator getReceiver(ResultSet resultSet) throws SQLException {
        Long id_receiver = resultSet.getLong("id_receiver");
        String firstNameR = resultSet.getString("first_nameR");
        String lastNameR = resultSet.getString("last_nameR");
        String usernameR = resultSet.getString("usernameR");
        String passwordR = resultSet.getString("passwordR");

        Utilizator receiver = new Utilizator(firstNameR, lastNameR, passwordR,usernameR,null,null);
        receiver.setId(id_receiver);
        return receiver;
    }

    public Optional<Message> findOne(Long id) {
        String query = """
        SELECT m.id AS id, m.message, m.date,
               sender.user_id AS id_sender, sender.first_name, sender.last_name, sender.username, sender.password,
               receiver.user_id AS id_receiver, receiver.first_name AS first_nameR, receiver.last_name AS last_nameR, 
               receiver.username AS usernameR, receiver.password AS passwordR
        FROM message m
        JOIN users sender ON m.id_sender = sender.user_id
        JOIN users receiver ON m.id_receiver = receiver.user_id
        WHERE m.id = ?;
    """;
        Message message = null;

        try (Connection connection = DriverManager.getConnection(URL, USER, PASSWORD);
             PreparedStatement statement = connection.prepareStatement(query)) {

            statement.setLong(1, id);
            ResultSet resultSet = statement.executeQuery();

            if (resultSet.next()) {
                Long id_message = resultSet.getLong("id");
                LocalDateTime dateTime = resultSet.getTimestamp("date").toLocalDateTime();
                String content = resultSet.getString("message");

                Utilizator sender = getOwner(resultSet);
                List<Utilizator> users = new ArrayList<>();
                Utilizator receiver = getReceiver(resultSet);
                users.add(receiver);

                while (resultSet.next()) {
                    receiver = getReceiver(resultSet);
                    users.add(receiver);
                }

                message = new Message(sender, content, dateTime, users);
                message.setId(id_message);
            }
        } catch (SQLException e) {
            System.err.println("Error retrieving message: " + e.getMessage());
        }

        return Optional.ofNullable(message);
    }

    public Iterable<Message> findAll() {
        Map<Long, Message> messageMap = new HashMap<>();
        String query = """
        SELECT m.id AS id, m.message, m.date,
               sender.user_id AS id_sender, sender.first_name, sender.last_name, sender.username, sender.password,
               receiver.user_id AS id_receiver, receiver.first_name AS first_nameR, receiver.last_name AS last_nameR, 
               receiver.username AS usernameR, receiver.password AS passwordR
        FROM message m
        JOIN users sender ON m.id_sender = sender.user_id
        JOIN users receiver ON m.id_receiver = receiver.user_id;
    """;

        try (Connection connection = DriverManager.getConnection(URL, USER, PASSWORD);
             PreparedStatement statement = connection.prepareStatement(query);
             ResultSet resultSet = statement.executeQuery()) {

            while (resultSet.next()) {
                Long id_message = resultSet.getLong("id");
                LocalDateTime dateTime = resultSet.getTimestamp("date").toLocalDateTime();
                String content = resultSet.getString("message");

                Utilizator sender = getOwner(resultSet);
                List<Utilizator> users = new ArrayList<>();
                Utilizator receiver = getReceiver(resultSet);
                users.add(receiver);

                if (!messageMap.containsKey(id_message)) {
                    Message message = new Message(sender, content, dateTime, users);
                    message.setId(id_message);
                    messageMap.put(id_message, message);
                } else {
                    Utilizator receiverToAdd = getReceiver(resultSet);
                    Message existingMessage = messageMap.get(id_message);
                    List<Utilizator> existingUsers = existingMessage.getUsers();
                    existingUsers.add(receiverToAdd);
                    existingMessage.setUsers(existingUsers);
                }
            }
        } catch (SQLException e) {
            System.err.println("Error retrieving messages: " + e.getMessage());
        }

        return messageMap.values();
    }

    public Optional<Message> save(Message entity) {
        String messageQuery = "INSERT INTO message (id_sender, id_receiver, message, date) VALUES (?, ?, ?, ?)";

        try (Connection connection = DriverManager.getConnection(URL, USER, PASSWORD);
             PreparedStatement statement = connection.prepareStatement(messageQuery, Statement.RETURN_GENERATED_KEYS)) {

            statement.setLong(1, entity.getUserSender().getId());  // Sender ID
            statement.setLong(2, entity.getUsers().get(0).getId()); // Receiver ID (assuming first user in the list)
            statement.setString(3, entity.getMessage());           // Message content
            statement.setTimestamp(4, Timestamp.valueOf(entity.getData())); // Timestamp

            int rowsAffected = statement.executeUpdate();

            if (rowsAffected > 0) {
                // Retrieve the generated ID for the message
                ResultSet generatedKeys = statement.getGeneratedKeys();
                if (generatedKeys.next()) {
                    long messageId = generatedKeys.getLong(1);
                    entity.setId(messageId);  // Set the generated ID to the entity

                    // Save replies for each recipient (assuming all replies are identical in content as the original message)
                    for (Utilizator receiver : entity.getUsers()) {
                        if (receiver.getId() != entity.getUserSender().getId()) {  // Not the sender
                            String replyQuery = "INSERT INTO reply (id_receiver, message, date) VALUES (?, ?, ?)";
                            try (PreparedStatement replyStatement = connection.prepareStatement(replyQuery)) {
                                replyStatement.setLong(1, receiver.getId());
                                replyStatement.setString(2, entity.getMessage());
                                replyStatement.setTimestamp(3, Timestamp.valueOf(entity.getData()));
                                replyStatement.executeUpdate();
                            }
                        }
                    }
                    return Optional.of(entity);  // Return the saved message entity with the generated ID
                }
            }
            return Optional.empty();  // Return empty if no rows were affected
        } catch (SQLException e) {
            System.err.println("Error saving message: " + e.getMessage());
            return Optional.empty();
        }
    }

    public Optional<Message> update(Message entity) {
        // Update query for the message
        String messageQuery = "UPDATE message SET message = ?, date = ? WHERE id = ?";

        try (Connection connection = DriverManager.getConnection(URL, USER, PASSWORD);
             PreparedStatement statement = connection.prepareStatement(messageQuery)) {

            // Set the updated values for the message
            statement.setString(1, entity.getMessage());      // Updated message content
            statement.setTimestamp(2, Timestamp.valueOf(entity.getData()));  // Updated timestamp
            statement.setLong(3, entity.getId());              // ID of the message to update

            // Execute the update query
            int rowsAffected = statement.executeUpdate();

            if (rowsAffected > 0) {
                // If the message update is successful, return the updated entity
                return Optional.of(entity);
            }
            return Optional.empty();  // If no rows are affected
        } catch (SQLException e) {
            System.err.println("Error updating message: " + e.getMessage());
            return Optional.empty();
        }
    }
    public Optional<Message> delete(Long id) {
        Optional<Message> entity = findOne(id);
        return Optional.empty();
    }



}
