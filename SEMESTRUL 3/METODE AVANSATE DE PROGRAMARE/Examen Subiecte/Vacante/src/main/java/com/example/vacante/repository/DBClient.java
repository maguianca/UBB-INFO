package com.example.vacante.repository;

import java.sql.*;
import java.util.Optional;
import com.example.vacante.domeniu.Client;

public class DBClient {
    private static final String URL = "jdbc:postgresql://127.0.0.1:5432/vacante";
    private static final String USER = "postgres";
    private static final String PASSWORD = "1205";

    public DBClient() {
    }

    public Optional<Client> findOne(Long id) {
        if (id == null) throw new IllegalArgumentException("Id-ul utilizatorului nu poate fi nul");
        Client client = null;
        String query = "SELECT * FROM client WHERE clientid = ?";
        try (Connection connection = DriverManager.getConnection(URL, USER, PASSWORD);
             PreparedStatement statement = connection.prepareStatement(query)) {

            statement.setLong(1, id);
            ResultSet resultSet = statement.executeQuery();
            while (resultSet.next()) {
                String hobby= resultSet.getString("hobbies");
                Integer age=resultSet.getInt("age");
                String name = resultSet.getString("name");
                Integer fidelitygrade=resultSet.getInt("fidelitygrade");
                client = new Client(id,name,fidelitygrade,age,Client.Hobby.valueOf(hobby));
            }

        } catch (SQLException e) {
            return Optional.empty();
        }
        return Optional.ofNullable(client);
    }
}