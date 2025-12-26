package com.example.zboruri2.repository;

import com.example.zboruri2.domeniu.Client;
import com.example.zboruri2.domeniu.Flight;
import com.example.zboruri2.paging.Page;
import com.example.zboruri2.paging.Pageable;

import java.sql.*;
import java.time.LocalDate;
import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;
import java.util.Optional;

public class DBRepoFlight {
    private static final String URL = "jdbc:postgresql://127.0.0.1:5432/zboruri";
    private static final String USER = "postgres";
    private static final String PASSWORD = "1205";
    public DBRepoFlight() {
    }
    public Optional<Flight> findOne(Long flightId) {
        if (flightId == null) throw new IllegalArgumentException("Flight ID cannot be null");
        Flight flight = null;
        String query = "SELECT * FROM flight WHERE id = ?";
        try (Connection connection = DriverManager.getConnection(URL, USER, PASSWORD);
             PreparedStatement statement = connection.prepareStatement(query)) {

            statement.setLong(1, flightId);
            ResultSet resultSet = statement.executeQuery();
            if (resultSet.next()) {
                String from = resultSet.getString("from");
                String to = resultSet.getString("to");
                LocalDateTime departureTime = resultSet.getTimestamp("departuretime").toLocalDateTime();
                LocalDateTime arrivalTime = resultSet.getTimestamp("landingtime").toLocalDateTime();
                Integer seats = resultSet.getInt("seats");
                flight = new Flight(from, to, departureTime, arrivalTime, seats);
                flight.setId(flightId);
            }

        } catch (SQLException e) {
            return Optional.empty();
        }
        return Optional.ofNullable(flight);
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
    public Page<Long> getPagedFlightsId(LocalDate departuretime, String from, String to, Pageable pageable) {
        ArrayList<Long> Ids = new ArrayList<>();
        String queryTotalNumberOfElements = "SELECT COUNT(id) AS count FROM flight WHERE DATE(departuretime) = ? AND \"from\" = ? AND \"to\" = ?";
        String query = "SELECT DISTINCT id FROM flight WHERE DATE(departuretime) = ? AND \"from\" = ? AND \"to\" = ? LIMIT ? OFFSET ?";
        int count = 0;
        try (Connection connection = DriverManager.getConnection(URL, USER, PASSWORD);
             PreparedStatement preparedStatement = connection.prepareStatement(query);
             PreparedStatement preparedStatementCount = connection.prepareStatement(queryTotalNumberOfElements)) {

            preparedStatement.setDate(1, java.sql.Date.valueOf(departuretime));
            preparedStatement.setString(2, from);
            preparedStatement.setString(3, to);
            int offset = (pageable.getPageNumber() - 1) * pageable.getPageSize();
            preparedStatement.setInt(4, pageable.getPageSize());
            preparedStatement.setInt(5, offset);

            try (ResultSet resultSet = preparedStatement.executeQuery()) {
                while (resultSet.next()) {
                    long persoanaId = resultSet.getLong("id");
                    System.out.println(persoanaId);
                    Ids.add(persoanaId);
                }
            }

            preparedStatementCount.setDate(1, java.sql.Date.valueOf(departuretime));
            preparedStatementCount.setString(2, from);
            preparedStatementCount.setString(3, to);

            try (ResultSet resultSet = preparedStatementCount.executeQuery()) {
                if (resultSet.next()) {
                    count = resultSet.getInt("count");
                    System.out.println(count);
                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return new Page<>(count, Ids);
    }
}
