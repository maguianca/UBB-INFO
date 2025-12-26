package com.example.taximetrie2.repository;

import com.example.taximetrie2.domeniu.Sofer;

import java.sql.*;
import java.util.HashMap;
import java.util.Map;
import java.util.Optional;

public class DBRepoSofer {

    private static final String URL = "jdbc:postgresql://127.0.0.1:5432/taximetrie";
    private static final String USER = "postgres";
    private static final String PASSWORD="1205";
    public DBRepoSofer(){

    }
    public Optional<Sofer> findOne(String username) {
        if(username==null)throw new IllegalArgumentException("Id-ul utilizatorului nu poate fi nul");

        String query = "SELECT * FROM sofer WHERE username= ?";
        Sofer sofer= null;
        try (Connection connection = DriverManager.getConnection(URL, USER, PASSWORD);
             PreparedStatement statement = connection.prepareStatement(query);) {

            statement.setString(1, username);
            ResultSet resultSet = statement.executeQuery();
            while (resultSet.next()) {
                String nume= resultSet.getString("nume");
                Long id = resultSet.getLong("id");
                String indicativ = resultSet.getString("indicativ_masina");
                sofer= new Sofer(username,nume,indicativ);
                sofer.setId(id);
            }

        } catch (SQLException e) {
            return Optional.empty();
        }
        return Optional.ofNullable(sofer);
    }
    public Optional<Sofer> findOneId(Long id) {
        if(id==null)throw new IllegalArgumentException("Id-ul utilizatorului nu poate fi nul");

        String query = "SELECT * FROM sofer WHERE id = ?";
        Sofer sofer= null;
        try (Connection connection = DriverManager.getConnection(URL, USER, PASSWORD);
             PreparedStatement statement = connection.prepareStatement(query);) {

            statement.setLong(1, id);
            ResultSet resultSet = statement.executeQuery();
            while (resultSet.next()) {
                String nume= resultSet.getString("nume");
                String username = resultSet.getString("username");
                String indicativ = resultSet.getString("indicativ_masina");
                sofer= new Sofer(username,nume,indicativ);
                sofer.setId(id);
            }

        } catch (SQLException e) {
            return Optional.empty();
        }
        return Optional.ofNullable(sofer);
    }
    public Iterable<Sofer> findAll() {
        Map<Long, Sofer> users = new HashMap<>();
        try (Connection connection = DriverManager.getConnection(URL, USER, PASSWORD);
             PreparedStatement statement = connection.prepareStatement("select * from sofer");
             ResultSet resultSet = statement.executeQuery()) {

            while (resultSet.next()) {
                Long id = resultSet.getLong("id");
                String nume= resultSet.getString("nume");
                String username = resultSet.getString("username");
                String indicativ = resultSet.getString("indicativ_masina");
                Sofer sofer= new Sofer(username,nume,indicativ);
                sofer.setId(id);

                users.put(sofer.getId(), sofer);
            }
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }

        return users.values();
    }

}
