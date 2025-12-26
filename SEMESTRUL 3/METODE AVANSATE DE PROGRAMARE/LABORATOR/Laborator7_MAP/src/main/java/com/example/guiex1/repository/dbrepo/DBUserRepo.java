package com.example.guiex1.repository.dbrepo;
import com.example.guiex1.domain.Utilizator;
import com.example.guiex1.domain.Validator;
import com.example.guiex1.repository.Repository;


import java.sql.*;
import java.util.HashSet;
import java.util.Optional;
import java.util.Set;

import java.sql.*;
import java.util.*;

public class DBUserRepo implements Repository<Long, Utilizator>{
    private static final String URL = "jdbc:postgresql://127.0.0.1:5432/socialnetworking";
    private static final String USER = "postgres";
    private static final String PASSWORD="1205";
    private Validator<Utilizator> validator;

    public DBUserRepo(Validator<Utilizator> validator){
        this.validator = validator;
    }

    @Override
    public Optional<Utilizator> findOne(Long id) {
        if(id==null)throw new IllegalArgumentException("Id-ul utilizatorului nu poate fi nul");

        String query = "SELECT * FROM users WHERE user_id = ?";
        Utilizator user = null;
        try (Connection connection = DriverManager.getConnection(URL, USER, PASSWORD);
             PreparedStatement statement = connection.prepareStatement(query);) {

            statement.setLong(1, id);
            ResultSet resultSet = statement.executeQuery();
            while (resultSet.next()) {
                String firstName = resultSet.getString("first_name");
                String lastName = resultSet.getString("last_name");
                user = new Utilizator(firstName, lastName);
                user.setId(id);
            }

        } catch (SQLException e) {
            return Optional.empty();
        }
        return Optional.ofNullable(user);
    }

    @Override
    public Iterable<Utilizator> findAll() {
        Map<Long, Utilizator> users = new HashMap<>();
        try (Connection connection = DriverManager.getConnection(URL, USER, PASSWORD);
             PreparedStatement statement = connection.prepareStatement("select * from users");
             ResultSet resultSet = statement.executeQuery()) {

            while (resultSet.next()) {
                Long id = resultSet.getLong("user_id");
                String nume = resultSet.getString("first_name");
                String prenume = resultSet.getString("last_name");
                Utilizator user = new Utilizator(nume, prenume);
                user.setId(id);

                users.put(user.getId(), user);
            }
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }

        return users.values();
    }

    @Override
    public Optional<Utilizator> save(Utilizator entity) {
        if (entity == null) {
            throw new IllegalArgumentException("Utilizatorul nu poate fi nul");
        }
        String query = "INSERT INTO users(user_id,first_name,last_name) VALUES (?,?,?)";

        try (Connection connection = DriverManager.getConnection(URL, USER, PASSWORD);
             PreparedStatement statement = connection.prepareStatement(query);) {
            statement.setLong(1, entity.getId());
            statement.setString(2, entity.getFirstName());
            statement.setString(3, entity.getLastName());
            statement.executeUpdate();
        } catch (SQLException e) {
            System.out.println(e.getMessage());
        }
        return Optional.of(entity);
    }

    @Override
    public Optional<Utilizator> delete(Long id) {
        if (id == null) throw new IllegalArgumentException("Utilizatorul nu poate fi nul");

        Utilizator userToDelete = findOne(id).orElse(null);
        if (userToDelete == null) {
            return Optional.empty();
        }

        String query = "DELETE FROM users WHERE user_id = ?";
        try (Connection connection = DriverManager.getConnection(URL, USER, PASSWORD);
             PreparedStatement statement = connection.prepareStatement(query)) {
            statement.setLong(1, id);
            statement.executeUpdate();
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }

        return Optional.of(userToDelete);
    }

    @Override
    public Optional<Utilizator> update(Utilizator entity) {
        if (entity == null) {
            throw new IllegalArgumentException("Entitatea utilizator nu poate fi nulă");
        }

        // Verificăm dacă utilizatorul există în baza de date
        Optional<Utilizator> existingUser = findOne(entity.getId());
        if (existingUser.isEmpty()) {
            return Optional.empty(); // Dacă utilizatorul nu există, returnăm Optional.empty()
        }

        String query = "UPDATE users SET first_name = ?, last_name = ? WHERE user_id = ?";

        try (Connection connection = DriverManager.getConnection(URL, USER, PASSWORD);
             PreparedStatement statement = connection.prepareStatement(query)) {
            statement.setString(1, entity.getFirstName());
            statement.setString(2, entity.getLastName());
            statement.setLong(3, entity.getId());

            int rowsUpdated = statement.executeUpdate();
            if (rowsUpdated > 0) {
                return Optional.of(entity); // Returnăm utilizatorul actualizat dacă query-ul a fost executat cu succes
            }
        } catch (SQLException e) {
            throw new RuntimeException("Eroare la actualizarea utilizatorului: " + e.getMessage(), e);
        }

        return Optional.empty(); // Dacă nu s-a actualizat nimic, returnăm Optional.empty()
    }

}
