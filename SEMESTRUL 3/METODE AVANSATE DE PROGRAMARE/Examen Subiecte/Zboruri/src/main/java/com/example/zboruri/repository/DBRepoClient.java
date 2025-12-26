package com.example.zboruri.repository;

import com.example.zboruri.domeniu.Client;

import java.util.HashMap;
import java.util.Map;
import java.util.Optional;
import java.util.ArrayList;
import java.sql.*;

public class DBRepoClient {
    private static final String URL = "jdbc:postgresql://127.0.0.1:5432/zboruri";
    private static final String USER = "postgres";
    private static final String PASSWORD = "1205";
    public DBRepoClient() {
    }
    public Optional<Client> findOne(String username) {
        if (username == null) throw new IllegalArgumentException("Id-ul utilizatorului nu poate fi nul");
        Client client = null;
        String query = "SELECT * FROM client WHERE username = ?";
        try (Connection connection = DriverManager.getConnection(URL, USER, PASSWORD);
             PreparedStatement statement = connection.prepareStatement(query)) {

            statement.setString(1, username);
            ResultSet resultSet = statement.executeQuery();
            while (resultSet.next()) {
                Long id = resultSet.getLong("id");
                String name = resultSet.getString("name");
                client = new Client(username, name);
                client.setId(id);
            }

        } catch (SQLException e) {
            return Optional.empty();
        }
        return Optional.ofNullable(client);
    }
    public Iterable<Client> findAll(){
        Map<Long, Client> users = new HashMap<>();
        String query = "SELECT * FROM client";
        try (Connection connection = DriverManager.getConnection(URL, USER, PASSWORD);
             PreparedStatement statement = connection.prepareStatement(query)) {
            ResultSet resultSet = statement.executeQuery();
            while (resultSet.next()) {
                Long id = resultSet.getLong("id");
                String username = resultSet.getString("username");
                String name = resultSet.getString("name");
                Client client = new Client(username, name);
                client.setId(id);
                users.put(id,client);
            }
        } catch (SQLException e) {
            return users.values();
        }
        return users.values();
    }

}
