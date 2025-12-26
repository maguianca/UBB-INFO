package com.example.guiex1.repository.dbrepo;

import com.example.guiex1.domain.*;
import com.example.guiex1.repository.Repository;

import java.sql.*;
import java.time.LocalDateTime;
import java.util.*;

public class DBReplyRepo implements Repository<Tuple<Long, Long>, ReplyMessage> {

    private static final String URL = "jdbc:postgresql://127.0.0.1:5432/socialnetworking";
    private static final String USER = "postgres";
    private static final String PASSWORD = "1205";

    private final Validator<Message> validator;

    public DBReplyRepo(Validator<Message> validator) {
        this.validator = validator;
    }
    // Query general pentru tabelul `reply`.
    private static final String REPLY_QUERY =
            "SELECT r.id, r.id_receiver, r.message, r.date, " +
                    "u.first_name AS receiver_first_name, u.last_name AS receiver_last_name, " +
                    "u.username AS receiver_username, u.password AS receiver_password, " +
                    "m.id_sender, m.message AS original_message, m.date AS original_date, " +
                    "us.first_name AS sender_first_name, us.last_name AS sender_last_name, " +
                    "us.username AS sender_username, us.password AS sender_password " +
                    "FROM reply r " +
                    "JOIN users u ON r.id_receiver = u.user_id " +
                    "JOIN message m ON r.id = m.id " +
                    "JOIN users us ON m.id_sender = us.user_id ";

    public Optional<ReplyMessage> findOne(Tuple<Long, Long> id) {
        String query = REPLY_QUERY + "WHERE r.id = ? AND r.id_receiver = ?";

        try (Connection connection = DriverManager.getConnection(URL, USER, PASSWORD);
             PreparedStatement statement = connection.prepareStatement(query)) {

            statement.setLong(1, id.getLeft()); // ID-ul mesajului original
            statement.setLong(2, id.getRight()); // ID-ul receptorului
            ResultSet resultSet = statement.executeQuery();

            if (resultSet.next()) {
                return Optional.of(createReplyMessageFromResultSet(resultSet));
            }
        } catch (SQLException e) {
            throw new RuntimeException("Error retrieving reply: " + e.getMessage());
        }
        return Optional.empty();
    }

    public Iterable<ReplyMessage> findAll() {
        List<ReplyMessage> replies = new ArrayList<>();
        String query = REPLY_QUERY;

        try (Connection connection = DriverManager.getConnection(URL, USER, PASSWORD);
             PreparedStatement statement = connection.prepareStatement(query);
             ResultSet resultSet = statement.executeQuery()) {

            while (resultSet.next()) {
                replies.add(createReplyMessageFromResultSet(resultSet));
            }
        } catch (SQLException e) {
            throw new RuntimeException("Error retrieving all replies: " + e.getMessage());
        }
        return replies;
    }

    private ReplyMessage createReplyMessageFromResultSet(ResultSet resultSet) throws SQLException {
        // Detalii mesaj original
        Long idMessage = resultSet.getLong("id");
        Long idSender = resultSet.getLong("id_sender");
        String originalMessageContent = resultSet.getString("original_message");
        LocalDateTime originalMessageDate = resultSet.getTimestamp("original_date").toLocalDateTime();

        Utilizator sender = new Utilizator(
                resultSet.getString("sender_first_name"),
                resultSet.getString("sender_last_name"),
                resultSet.getString("sender_username"),
                resultSet.getString("sender_password")
        );
        sender.setId(idSender);

        Message originalMessage = new Message(sender, originalMessageContent, originalMessageDate, new ArrayList<>());
        originalMessage.setId(idMessage);

        // Detalii utilizator receptor
        Long idReceiver = resultSet.getLong("id_receiver");
        Utilizator receiver = new Utilizator(
                resultSet.getString("receiver_first_name"),
                resultSet.getString("receiver_last_name"),
                resultSet.getString("receiver_username"),
                resultSet.getString("receiver_password")
        );
        receiver.setId(idReceiver);

        // Detalii răspuns
        LocalDateTime dataResponse = resultSet.getTimestamp("date").toLocalDateTime();
        String messageReply = resultSet.getString("message");

        return new ReplyMessage(originalMessage, receiver, dataResponse, messageReply);
    }

    public Optional<ReplyMessage> save(ReplyMessage entity) {
        String query = "INSERT INTO reply (id_receiver, message, date) VALUES ( ?, ?, ?)";

        try (Connection connection = DriverManager.getConnection(URL, USER, PASSWORD);
             PreparedStatement statement = connection.prepareStatement(query)) {

            statement.setLong(1, entity.getReceiver().getId());
            statement.setString(2, entity.getReply());
            statement.setTimestamp(3, Timestamp.valueOf(entity.getDataReceiver()));

            int rowsAffected = statement.executeUpdate();
            return rowsAffected == 0 ? Optional.of(entity) : Optional.empty();
        } catch (SQLException e) {
            throw new RuntimeException("Error saving reply: " + e.getMessage());
        }
    }

    public Optional<ReplyMessage> delete(Tuple<Long, Long> id) {
        Optional<ReplyMessage> entity = findOne(id);
        String query = "DELETE FROM reply WHERE id = ? AND id_receiver = ?";

        try (Connection connection = DriverManager.getConnection(URL, USER, PASSWORD);
             PreparedStatement statement = connection.prepareStatement(query)) {

            statement.setLong(1, id.getLeft());
            statement.setLong(2, id.getRight());

            int rowsAffected = statement.executeUpdate();
            return rowsAffected == 0 ? Optional.empty() : entity;
        } catch (SQLException e) {
            throw new RuntimeException("Error deleting reply: " + e.getMessage());
        }
    }

    public Optional<ReplyMessage> update(ReplyMessage entity) {
        String query = "UPDATE reply SET message = ?, date = ? WHERE id = ? AND id_receiver = ?";

        try (Connection connection = DriverManager.getConnection(URL, USER, PASSWORD);
             PreparedStatement statement = connection.prepareStatement(query)) {

            statement.setString(1, entity.getReply());
            statement.setTimestamp(2, Timestamp.valueOf(entity.getDataReceiver()));
            statement.setLong(3, entity.getReplyfor().getId());
            statement.setLong(4, entity.getReceiver().getId());

            int rowsAffected = statement.executeUpdate();
            return rowsAffected == 0 ? Optional.of(entity) : Optional.empty();
        } catch (SQLException e) {
            throw new RuntimeException("Error updating reply: " + e.getMessage());
        }
    }
}
