package com.example.zboruri2.repository;

import com.example.zboruri2.domeniu.Ticket;

import java.sql.*;
import java.time.LocalDateTime;
import java.util.HashMap;
import java.util.Map;
import java.util.Optional;

public class DBRepoTicket {
    private static final String URL = "jdbc:postgresql://127.0.0.1:5432/zboruri";
    private static final String USER = "postgres";
    private static final String PASSWORD = "1205";
    public DBRepoTicket() {
    }
    public Iterable<Ticket> findAllTicketClient(String username) {
        Map<Long, Ticket> users = new HashMap<>();
        String query = "SELECT * FROM ticket WHERE username = ?";
        try (Connection connection = DriverManager.getConnection(URL, USER, PASSWORD);
             PreparedStatement statement = connection.prepareStatement(query)) {
            // Set the username parameter before executing the query
            statement.setString(1, username);

            // Now execute the query
            ResultSet resultSet = statement.executeQuery();

            while (resultSet.next()) {
                Long id = resultSet.getLong("id");
                Long flightId = resultSet.getLong("flightid");
                LocalDateTime purchase = resultSet.getTimestamp("purchasetime").toLocalDateTime();
                Ticket ticket = new Ticket(username, flightId, purchase);
                ticket.setId(id);
                users.put(id, ticket);
            }
        } catch (SQLException e) {
            // Optionally, you might want to log or print the error
            e.printStackTrace();
        }
        return users.values();
    }
    public Iterable<Ticket> findAllTicket(long flightId) {
        Map<Long, Ticket> users = new HashMap<>();
        String query = "SELECT * FROM ticket WHERE flightid = ?";
        try (Connection connection = DriverManager.getConnection(URL, USER, PASSWORD);
             PreparedStatement statement = connection.prepareStatement(query)) {
            // Set the username parameter before executing the query
            statement.setLong(1, flightId);

            // Now execute the query
            ResultSet resultSet = statement.executeQuery();

            while (resultSet.next()) {
                Long id = resultSet.getLong("id");
                String username = resultSet.getString("username");
                LocalDateTime purchase = resultSet.getTimestamp("purchasetime").toLocalDateTime();
                Ticket ticket = new Ticket(username, flightId, purchase);
                ticket.setId(id);
                users.put(id, ticket);
                System.out.println(ticket);
            }
        } catch (SQLException e) {
            // Optionally, you might want to log or print the error
            e.printStackTrace();
        }
        return users.values();
    }
    public Optional<Ticket> save(Ticket entity){
        if (entity == null) {
            throw new IllegalArgumentException("Ticket cannot be null");
        }
        String query = "INSERT INTO ticket(username,flightid,purchasetime) values(?,?,?)";
        try (Connection connection = DriverManager.getConnection(URL, USER, PASSWORD);
             PreparedStatement statement = connection.prepareStatement(query)) {

            statement.setString(1, entity.getUsername());
            statement.setLong(2, entity.getFlightId());
            statement.setTimestamp(3, Timestamp.valueOf(entity.getPurchaseTime()));

            // Execute the query
            statement.executeUpdate();
        } catch (SQLException e) {
            // Optionally, you might want to log or print the error
            e.printStackTrace();
            return Optional.empty();
        }
        return Optional.of(entity);
    }

}
