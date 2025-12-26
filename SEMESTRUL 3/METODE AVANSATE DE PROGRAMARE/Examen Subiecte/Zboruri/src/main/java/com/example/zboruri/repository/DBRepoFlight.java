package com.example.zboruri.repository;

import com.example.zboruri.domeniu.Flight;
import com.example.zboruri.domeniu.Ticket;

import java.sql.ResultSet;
import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;
import java.sql.*;
import java.util.Optional;

public class DBRepoFlight {
    private static final String URL = "jdbc:postgresql://127.0.0.1:5432/zboruri";
    private static final String USER = "postgres";
    private static final String PASSWORD = "1205";
    public DBRepoFlight() {
    }
    public Iterable<Flight> findAll() {
        Map<Long, Flight> users = new HashMap<>();
        try (Connection connection = DriverManager.getConnection(URL, USER, PASSWORD);
             PreparedStatement statement = connection.prepareStatement("select * from flight");
             ResultSet resultSet = statement.executeQuery()) {

            while (resultSet.next()) {
                Long id = resultSet.getLong("id");
                String from = resultSet.getString("from");
                String to = resultSet.getString("to");
                LocalDateTime departureTime = resultSet.getTimestamp("departuretime").toLocalDateTime();
                LocalDateTime arrivalTime = resultSet.getTimestamp("landingtime").toLocalDateTime();
                Integer seats=resultSet.getInt("seats");
                Flight flight = new Flight(from,to,departureTime,arrivalTime,seats);
                flight.setId(id);
                users.put(id, flight);
                System.out.println(flight);
            }
        } catch (SQLException e) {
            return new ArrayList<>();
        }
        return users.values();
    }
}
