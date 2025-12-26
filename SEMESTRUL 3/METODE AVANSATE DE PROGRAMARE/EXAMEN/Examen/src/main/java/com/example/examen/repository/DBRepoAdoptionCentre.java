package com.example.examen.repository;

import com.example.examen.domeniu.AdoptionCentre;

import java.sql.*;
import java.util.HashMap;
import java.util.Map;
import java.util.Optional;

public class DBRepoAdoptionCentre {
    private static final String URL = "jdbc:postgresql://127.0.0.1:5432/examen";
    private static final String USER = "postgres";
    private static final String PASSWORD = "1205";

    public DBRepoAdoptionCentre() {
    }

    public Optional<AdoptionCentre> findOne(Integer id) {
        if (id == null) throw new IllegalArgumentException("Id-ul utilizatorului nu poate fi nul");

        String query = "SELECT * FROM adoptioncentre WHERE id = ?";
        AdoptionCentre cerere = null;
        try (Connection connection = DriverManager.getConnection(URL, USER, PASSWORD);
             PreparedStatement statement = connection.prepareStatement(query)) {

            statement.setLong(1, id);
            ResultSet resultSet = statement.executeQuery();
            while (resultSet.next()) {
                String name = resultSet.getString("name");
                String locatie = resultSet.getString("location");
                Integer capacity = resultSet.getInt("capacity");
                cerere = new AdoptionCentre(id, name, locatie, capacity);
            }

        } catch (SQLException e) {
            return Optional.empty();
        }
        return Optional.ofNullable(cerere);
    }

    public Iterable<AdoptionCentre> findAll() {
        Map<Long, AdoptionCentre> users = new HashMap<>();
        try (Connection connection = DriverManager.getConnection(URL, USER, PASSWORD);
             PreparedStatement statement = connection.prepareStatement("SELECT * FROM adoptioncentre");
             ResultSet resultSet = statement.executeQuery()) {

            while (resultSet.next()) {
                Integer id = resultSet.getInt("id");
                String name = resultSet.getString("name");
                String locatie = resultSet.getString("location");
                Integer capacity = resultSet.getInt("capacity");
                AdoptionCentre adoptionCentre = new AdoptionCentre(id, name, locatie, capacity);

                users.put(adoptionCentre.getId().longValue(), adoptionCentre);
            }
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }

        return users.values();
    }
}