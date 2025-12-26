package com.example.guiex1.repository.dbrepo;

import java.sql.*;
import java.time.LocalDateTime;
import java.util.*;

import com.example.guiex1.domain.Utilizator;
import com.example.guiex1.domain.Friendship;
import com.example.guiex1.domain.Validator;
import com.example.guiex1.repository.Repository;
import com.example.guiex1.utils.paging.Page;
import com.example.guiex1.utils.paging.Pageable;

import java.sql.*;
import java.util.HashMap;
import java.util.Map;
import java.util.Optional;
import java.time.LocalDateTime;
public class DBFriendshipRepo implements PagingFriendship<Long,Friendship>{
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

    public Page<Long> getPagedFriendsForUserID(Long id, Pageable pageable){
        ArrayList<Long> friendIds = new ArrayList<>();
        String queryTotalNumberOfElements = "SELECT COUNT(*) AS count FROM friendships WHERE id_friend1 = ? OR id_friend2 = ?";
        String query = "SELECT * FROM friendships WHERE id_friend1 = ? OR id_friend2 = ? LIMIT ? OFFSET ?";
        int count=0;
        try (Connection connection = DriverManager.getConnection(URL, USER, PASSWORD);
             PreparedStatement preparedStatement = connection.prepareStatement(query);
             PreparedStatement preparedStatementCount = connection.prepareStatement(queryTotalNumberOfElements)) {


            preparedStatement.setLong(1, id);
            preparedStatement.setLong(2, id);

            int offset = (pageable.getPageNumber() - 1) * pageable.getPageSize();
            preparedStatement.setInt(3,pageable.getPageSize());
            preparedStatement.setInt(4,offset);

            try (ResultSet resultSet = preparedStatement.executeQuery()) {
                while (resultSet.next()) {
                    long firstUserId = resultSet.getLong("id_friend1");
                    long secondUserId = resultSet.getLong("id_friend2");
                    friendIds.add((firstUserId != id) ? firstUserId : secondUserId);
                    //long id_friendship=resultSet.getLong("id");
                    //friendIds.add(id_friendship);
                }
            }
            preparedStatementCount.setLong(1,id);
            preparedStatementCount.setLong(2,id);

            try(ResultSet resultSet = preparedStatementCount.executeQuery()){
                while(resultSet.next()) {
                    count = resultSet.getInt("count");
                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return new Page<>(count, friendIds);
    }
}
