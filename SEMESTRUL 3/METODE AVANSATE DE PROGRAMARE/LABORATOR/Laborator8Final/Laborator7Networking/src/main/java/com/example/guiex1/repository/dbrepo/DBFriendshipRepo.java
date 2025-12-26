package com.example.guiex1.repository.dbrepo;

import java.sql.*;
import java.time.LocalDateTime;
import java.util.HashMap;
import java.util.Map;
import java.util.Optional;
import com.example.guiex1.domain.Utilizator;
import com.example.guiex1.domain.Friendship;
import com.example.guiex1.domain.Validator;
import com.example.guiex1.repository.Repository;
import java.sql.*;
import java.util.HashMap;
import java.util.Map;
import java.util.Optional;
import java.time.LocalDateTime;
public class DBFriendshipRepo implements Repository<Long, Friendship> {
    private static final String URL = "jdbc:postgresql://127.0.0.1:5432/socialnetworking";
    private static final String USER = "postgres";
    private static final String PASSWORD = "1205";
    private Validator<Friendship> validator;

    public DBFriendshipRepo(Validator<Friendship> validator) {

        this.validator = validator;
        //actualizare_baza();
    }

    @Override
    public Optional<Friendship> findOne(Long id) {
        String query = "SELECT * FROM friendships WHERE id = ?";
        Friendship friendship = null;
        try (Connection connection = DriverManager.getConnection(URL, USER, PASSWORD);
             PreparedStatement statement = connection.prepareStatement(query)) {

            statement.setLong(1, id);
            ResultSet resultSet = statement.executeQuery();
            while (resultSet.next()) {
                Long idFriend1 = resultSet.getLong("id_friend1");
                Long idFriend2 = resultSet.getLong("id_friend2");
                Timestamp timestamp = resultSet.getTimestamp("data");
                LocalDateTime date = new Timestamp(timestamp.getTime()).toLocalDateTime();// Get the 'data' timestamp value
                //LocalDateTime date = timestamp != null ? timestamp.toLocalDateTime() : null;  // Convert to LocalDateTime
                friendship = new Friendship(idFriend1, idFriend2, date);  // Pass the 'date' to the Friendship object
                friendship.setId(id);
            }
        } catch (SQLException e) {
            System.out.println(e.getMessage());
        }
        return Optional.ofNullable(friendship);
    }

    @Override
    public Iterable<Friendship> findAll() {
        Map<Long, Friendship> friendships = new HashMap<>();
        try (Connection connection = DriverManager.getConnection(URL, USER, PASSWORD);
             PreparedStatement statement = connection.prepareStatement("SELECT * FROM friendships");
             ResultSet resultSet = statement.executeQuery()) {

            while (resultSet.next()) {
                Long id = resultSet.getLong("id");
                Long idFriend1 = resultSet.getLong("id_friend1");
                Long idFriend2 = resultSet.getLong("id_friend2");
                Timestamp timestamp = resultSet.getTimestamp("data");
                LocalDateTime date = new Timestamp(timestamp.getTime()).toLocalDateTime();// Get the 'data' timestamp value
                //LocalDateTime date = timestamp != null ? timestamp.toLocalDateTime() : null;  // Convert to LocalDateTime
                Friendship friendship = new Friendship(idFriend1, idFriend2, date);  // Pass the 'date' to the Friendship object
                friendship.setId(id);
                friendships.put(friendship.getId(), friendship);
            }
        } catch (SQLException e) {
            System.out.println(e.getMessage());
        }
        return friendships.values();
    }

    @Override
    public Optional<Friendship> save(Friendship entity) {
        if (entity == null) {
            throw new IllegalArgumentException("Friendship cannot be null");
        }

        String query = "INSERT INTO friendships(id, id_friend1, id_friend2, data) VALUES (?,?,?,?)";

        try (Connection connection = DriverManager.getConnection(URL, USER, PASSWORD);
             PreparedStatement statement = connection.prepareStatement(query)) {

            statement.setLong(1, entity.getId());
            statement.setLong(2, entity.getIdUser1());
            statement.setLong(3, entity.getIdUser2());
            statement.setTimestamp(4, Timestamp.valueOf(entity.getDate()));  // Convert LocalDateTime to Timestamp
            statement.executeUpdate();
        } catch (SQLException e) {
            System.out.println(e.getMessage());
        }

        return Optional.of(entity);
    }


    /*public Optional<Friendship> delete(Long id) {
        String query = "DELETE FROM friendships WHERE id = ?";

        try (Connection connection = DriverManager.getConnection(URL, USER, PASSWORD);
             PreparedStatement statement = connection.prepareStatement(query)) {
            statement.setLong(1, id);
            statement.executeUpdate();
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }

        Friendship friendshipToDelete = null;
        for (Friendship friendship : findAll()) {
            if (friendship.getId().equals(id)) {
                friendshipToDelete = friendship;
            }
        }
        return Optional.ofNullable(friendshipToDelete);
    }
    */
    @Override
    public Optional<Friendship> delete(Long id) {
        String query = "DELETE FROM friendships WHERE id = ?";

        try (Connection connection = DriverManager.getConnection(URL, USER, PASSWORD);
             PreparedStatement statement = connection.prepareStatement(query)) {
            statement.setLong(1, id);
            int rowsAffected = statement.executeUpdate();
            if (rowsAffected > 0) {
                return Optional.empty();
            } else {
                System.out.println("No friendship found with the given ID.");
                return Optional.of(new Friendship());
            }
        } catch (SQLException e) {
            System.err.println("Error deleting friendship: " + e.getMessage());
            return Optional.empty();
        }
    }


    @Override
    public Optional<Friendship> update(Friendship entity) {
        return Optional.empty();
    }
}
