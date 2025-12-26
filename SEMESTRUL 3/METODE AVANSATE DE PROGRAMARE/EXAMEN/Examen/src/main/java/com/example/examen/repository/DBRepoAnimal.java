package com.example.examen.repository;

import com.example.examen.domeniu.Animal;

import java.sql.*;
import java.util.HashMap;
import java.util.Map;
import java.util.Optional;

public class DBRepoAnimal {
    private static final String URL = "jdbc:postgresql://127.0.0.1:5432/examen";
    private static final String USER = "postgres";
    private static final String PASSWORD = "1205";

    public DBRepoAnimal() {
    }

    public Optional<Animal> findOne(Integer id) {
        if (id == null) throw new IllegalArgumentException("Id-ul utilizatorului nu poate fi nul");

        String query = "SELECT * FROM animal WHERE id = ?";
        Animal cerere = null;
        try (Connection connection = DriverManager.getConnection(URL, USER, PASSWORD);
             PreparedStatement statement = connection.prepareStatement(query)) {

            statement.setLong(1, id);
            ResultSet resultSet = statement.executeQuery();
            while (resultSet.next()) {
                String name = resultSet.getString("name");
                Integer centreid = resultSet.getInt("centreid");
                String type = resultSet.getString("type");
                cerere = new Animal(id, name, centreid, Animal.Type.valueOf(type));
            }

        } catch (SQLException e) {
            return Optional.empty();
        }
        return Optional.ofNullable(cerere);
    }

    public Iterable<Animal> findAll(Integer centreid) {
        Map<Long, Animal> animals = new HashMap<>();
        String query = "SELECT * FROM animal WHERE centreid = ?";
        try (Connection connection = DriverManager.getConnection(URL, USER, PASSWORD);
             PreparedStatement statement = connection.prepareStatement(query)) {

            statement.setInt(1, centreid);
            ResultSet resultSet = statement.executeQuery();

            while (resultSet.next()) {
                Long id = resultSet.getLong("id");
                String name = resultSet.getString("name");
                String type = resultSet.getString("type");
                Animal animal = new Animal(id.intValue(), name, centreid, Animal.Type.valueOf(type));

                animals.put(animal.getId().longValue(), animal);
            }
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }

        return animals.values();
    }
    public Iterable<Animal> find_filtrare(Integer centreid,String tip) {
        Map<Long, Animal> animals = new HashMap<>();
        String query = "SELECT * FROM animal WHERE centreid = ? and type=? ";
        try (Connection connection = DriverManager.getConnection(URL, USER, PASSWORD);
             PreparedStatement statement = connection.prepareStatement(query)) {

            statement.setInt(1, centreid);
            statement.setString(2, tip);
            ResultSet resultSet = statement.executeQuery();

            while (resultSet.next()) {
                Long id = resultSet.getLong("id");
                String name = resultSet.getString("name");
                Animal animal = new Animal(id.intValue(), name, centreid, Animal.Type.valueOf(tip));

                animals.put(animal.getId().longValue(), animal);
            }
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }

        return animals.values();
    }
    public void updateCentreId(Integer id, Integer newCentreId) {
        String query = "UPDATE animal SET centreid = ? WHERE id = ?";
        try (Connection connection = DriverManager.getConnection(URL, USER, PASSWORD);
             PreparedStatement statement = connection.prepareStatement(query)) {

            statement.setInt(1, newCentreId);
            statement.setInt(2, id);
            statement.executeUpdate();
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

}