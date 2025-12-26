package com.example.taximetrie.repository;

import com.example.taximetrie.domeniu.Comanda;
import com.example.taximetrie.domeniu.Persoana;
import com.example.taximetrie.validator.Validator;
import com.example.taximetrie.domeniu.Sofer;

import java.sql.*;
import java.util.HashMap;
import java.util.Map;
import java.util.Optional;

public class DBSoferRepo implements Repository<Long,Sofer> {
    private static final String URL = "jdbc:postgresql://127.0.0.1:5432/taximetrie";
    private static final String USER = "postgres";
    private static final String PASSWORD="1205";
    //private Validator<Sofer> validator;
    public DBSoferRepo() {
    }

    @Override
    public Optional<Sofer> findOne(Long id) {
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

    @Override
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

    @Override
    public Optional<Sofer> save(Sofer entity) {
        if (entity == null) {
            throw new IllegalArgumentException("Persoana nu poate fi nula");
        }
        String query = "INSERT INTO sofer(username,nume,indicativ_masina) VALUES (?, ?,?)";
        try (Connection connection = DriverManager.getConnection(URL, USER, PASSWORD);
             PreparedStatement statement = connection.prepareStatement(query)) {

            //statement.setLong(1, entity.getId());
            statement.setString(1, entity.getUsername());
            statement.setString(2, entity.getNume());
            statement.setString(3, entity.getIndicativMasina());

            int rowsAffected = statement.executeUpdate();
            if (rowsAffected > 0) {
                return Optional.of(entity);
            }
        } catch (SQLException e) {
            System.err.println("Error saving user: " + e.getMessage());
        }
        return Optional.empty();
    }

    @Override
    public Optional<Sofer> delete(Long aLong) {
        return Optional.empty();
    }

}
