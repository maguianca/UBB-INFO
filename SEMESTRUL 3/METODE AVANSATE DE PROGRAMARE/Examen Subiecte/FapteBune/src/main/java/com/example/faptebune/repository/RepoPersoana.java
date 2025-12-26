package com.example.faptebune.repository;

import java.sql.*;
import java.util.HashMap;
import java.util.Map;
import java.util.Optional;
import com.example.faptebune.domeniu.*;

public class RepoPersoana {
    private static final String URL = "jdbc:postgresql://127.0.0.1:5432/faptebune";
    private static final String USER = "postgres";
    private static final String PASSWORD = "1205";

    public RepoPersoana() {
    }

    public Optional<Persoana> findOne(Long id) {
        if (id == null) throw new IllegalArgumentException("Id-ul utilizatorului nu poate fi nul");
        Persoana persoana = null;
        String query = "SELECT * FROM persoana WHERE id = ?";
        try (Connection connection = DriverManager.getConnection(URL, USER, PASSWORD);
             PreparedStatement statement = connection.prepareStatement(query)) {

            statement.setLong(1, id);
            ResultSet resultSet = statement.executeQuery();
            while (resultSet.next()) {
                String nume = resultSet.getString("nume");
                String prenume = resultSet.getString("prenume");
                String username = resultSet.getString("username");
                String parola = resultSet.getString("parola");
                String oras = resultSet.getString("oras");
                String strada = resultSet.getString("strada");
                String numar = resultSet.getString("numarstrada");
                String telefon = resultSet.getString("telefon");
                persoana = new Persoana(nume, prenume, username, parola, Persoana.Oras.valueOf(oras.toUpperCase()), strada, numar, telefon);
                persoana.setId(id);
            }

        } catch (SQLException e) {
            return Optional.empty();
        }
        return Optional.ofNullable(persoana);
    }
    public Optional<Persoana>save(Persoana entity){
        if (entity == null) {
            throw new IllegalArgumentException("Persoana nu poate fi nula");
        }
        String query = "INSERT INTO persoana(nume,prenume,username,parola,oras,strada,numarStrada,telefon) values(?,?,?,?,?,?,?,?)";
        try (Connection connection = DriverManager.getConnection(URL, USER, PASSWORD);
             PreparedStatement statement = connection.prepareStatement(query)) {

            statement.setString(1, entity.getNume());
            statement.setString(2, entity.getPrenume());
            statement.setString(3, entity.getUsername());
            statement.setString(4, entity.getParola());
            statement.setString(5, entity.getOras().toString());
            statement.setString(6, entity.getStrada());
            statement.setString(7, entity.getNumarStrada());
            statement.setString(8, entity.getTelefon());

            int rowsAffected = statement.executeUpdate();
            if (rowsAffected > 0) {
                return Optional.of(entity);
            }
        } catch (SQLException e) {
            System.err.println("Error saving user: " + e.getMessage());
        }
        return Optional.empty();
    }
    public Iterable<Persoana>findAll(){
        Map<Long, Persoana> users = new HashMap<>();
        try (Connection connection = DriverManager.getConnection(URL, USER, PASSWORD);
             PreparedStatement statement = connection.prepareStatement("select * from persoana");
             ResultSet resultSet = statement.executeQuery()) {

            while (resultSet.next()) {
                Long id = resultSet.getLong("id");
                String nume= resultSet.getString("nume");
                String prenume= resultSet.getString("prenume");
                String username = resultSet.getString("username");
                String parola = resultSet.getString("parola");
                String oras = resultSet.getString("oras");
                String strada = resultSet.getString("strada");
                String numar = resultSet.getString("numarstrada");
                String telefon = resultSet.getString("telefon");
                Persoana persoana=new Persoana(nume,prenume,username,parola,Persoana.Oras.valueOf(oras.toUpperCase()),strada,numar,telefon);
                persoana.setId(id);

                users.put(persoana.getId(), persoana);
            }
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }

        return users.values();
    }
}