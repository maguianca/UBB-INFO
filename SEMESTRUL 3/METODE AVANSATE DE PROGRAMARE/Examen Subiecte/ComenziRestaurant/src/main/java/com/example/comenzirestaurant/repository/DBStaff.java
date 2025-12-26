package com.example.comenzirestaurant.repository;

import com.example.comenzirestaurant.domeniu.Angajat;

import java.sql.*;
import java.util.HashMap;
import java.util.Map;
import java.util.Optional;

public class DBStaff implements Repository<Long, Angajat> {

    private static final String URL = "jdbc:postgresql://127.0.0.1:5432/comenzi";
    private static final String USER = "postgres";
    private static final String PASSWORD = "1205";

    public DBStaff() {
    }

    @Override
    public Optional<Angajat> findOne(Long id) {
        // Implement findOne logic
        return Optional.empty();
    }

    @Override
    public Iterable<Angajat> findAll() {
        Map<Long, Angajat> users = new HashMap<>();
        try (Connection connection = DriverManager.getConnection(URL, USER, PASSWORD);
             PreparedStatement statement = connection.prepareStatement("select * from angajati");
             ResultSet resultSet = statement.executeQuery()) {

            while (resultSet.next()) {
                Long id = resultSet.getLong("id");
                String nume = resultSet.getString("nume");
                Angajat an = new Angajat(nume);
                an.setId(id);

                users.put(an.getId(), an);
            }
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }

        return users.values();
    }

    @Override
    public Optional<Angajat> save(Angajat entity) {
        if (entity == null) {
            throw new IllegalArgumentException("Entity cannot be null");
        }
        String query = "INSERT INTO angajati(id, nume) VALUES (?, ?)";
        try (Connection connection = DriverManager.getConnection(URL, USER, PASSWORD);
             PreparedStatement statement = connection.prepareStatement(query)) {
            statement.setLong(1, entity.getId());
            statement.setString(2, entity.getNume());
            int rowsAffected = statement.executeUpdate();
            if (rowsAffected > 0) {
                return Optional.of(entity);
            }
        } catch (SQLException e) {
            System.err.println("Error saving entity: " + e.getMessage());
        }
        return Optional.empty();
    }

    @Override
    public Optional<Angajat> delete(Long id) {
        if (id == null) {
            throw new IllegalArgumentException("ID cannot be null");
        }
        String query = "DELETE FROM angajati WHERE id = ?";
        try (Connection connection = DriverManager.getConnection(URL, USER, PASSWORD);
             PreparedStatement statement = connection.prepareStatement(query)) {
            statement.setLong(1, id);
            int rowsAffected = statement.executeUpdate();
            if (rowsAffected > 0) {
                return Optional.of(null); // Return a dummy Angajat object
            }
        } catch (SQLException e) {
            System.err.println("Error deleting entity: " + e.getMessage());
        }
        return Optional.empty();
    }

    @Override
    public Optional<Angajat> update(Angajat entity) {
        if (entity == null) {
            throw new IllegalArgumentException("Entity cannot be null");
        }
        String query = "UPDATE angajati SET nume = ? WHERE id = ?";
        try (Connection connection = DriverManager.getConnection(URL, USER, PASSWORD);
             PreparedStatement statement = connection.prepareStatement(query)) {
            statement.setString(1, entity.getNume());
            statement.setLong(2, entity.getId());
            int rowsAffected = statement.executeUpdate();
            if (rowsAffected > 0) {
                return Optional.of(entity);
            }
        } catch (SQLException e) {
            System.err.println("Error updating entity: " + e.getMessage());
        }
        return Optional.empty();
    }
}