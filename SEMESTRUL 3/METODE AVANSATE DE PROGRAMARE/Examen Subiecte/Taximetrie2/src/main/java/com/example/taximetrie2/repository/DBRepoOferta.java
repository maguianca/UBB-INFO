package com.example.taximetrie2.repository;

import com.example.taximetrie2.domeniu.Oferta;

import java.sql.*;
import java.util.HashMap;
import java.util.Map;
import java.util.Optional;

public class DBRepoOferta {
    private static final String URL = "jdbc:postgresql://127.0.0.1:5432/taximetrie";
    private static final String USER = "postgres";
    private static final String PASSWORD="1205";
    public DBRepoOferta(){

    }
    public Optional<Oferta> save(Oferta entity) {
        if (entity == null) {
            throw new IllegalArgumentException("Persoana nu poate fi nula");
        }
        String query = "INSERT INTO oferta(id_client,id_sofer,id_cerere,timp) VALUES (?,?,?,?)";
        try (Connection connection = DriverManager.getConnection(URL, USER, PASSWORD);
             PreparedStatement statement = connection.prepareStatement(query)) {

            //statement.setLong(1, entity.getId());
            statement.setLong(1, entity.getId_client());
            statement.setLong(2, entity.getId_sofer());
            statement.setLong(3,entity.getId_cerere());
            statement.setInt(4, entity.getMinute());

            int rowsAffected = statement.executeUpdate();
            if (rowsAffected > 0) {
                return Optional.of(entity);
            }
        } catch (SQLException e) {
            System.err.println("Error saving user: " + e.getMessage());
        }
        return Optional.empty();
    }
    public Optional<Oferta> findOne(Long id) {
        if (id == null) throw new IllegalArgumentException("Id-ul utilizatorului nu poate fi nul");

        String query = "SELECT * FROM oferta WHERE id = ?";
        //Comanda comanda= null;
        Oferta oferta = null;
        try (Connection connection = DriverManager.getConnection(URL, USER, PASSWORD);
             PreparedStatement statement = connection.prepareStatement(query);) {

            statement.setLong(1, id);
            ResultSet resultSet = statement.executeQuery();
            while (resultSet.next()) {
                Long id_persoana = resultSet.getLong("id_client");
                Long id_sofer = resultSet.getLong("id_sofer");
                int timp=resultSet.getInt("timp");
                Long id_cerere=resultSet.getLong("id_cerere");
                oferta=new Oferta(id_persoana, id_sofer, id_cerere,timp);
                oferta.setId(id);
            }

        } catch (SQLException e) {
            return Optional.empty();
        }
        return Optional.ofNullable(oferta);
    }

    public Optional<Oferta> delete(Long id) {
        if (id == null) throw new IllegalArgumentException("Utilizatorul nu poate fi nul");

        Oferta userToDelete = findOne(id).orElse(null);
        if (userToDelete == null) {
            return Optional.empty();
        }

        String query = "DELETE FROM oferta WHERE id = ?";
        try (Connection connection = DriverManager.getConnection(URL, USER, PASSWORD);
             PreparedStatement statement = connection.prepareStatement(query)) {
            statement.setLong(1, id);
            statement.executeUpdate();
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }

        return Optional.of(userToDelete);
    }
    public Iterable<Oferta> findAll() {
        Map<Long, Oferta> users = new HashMap<>();
        try (Connection connection = DriverManager.getConnection(URL, USER, PASSWORD);
             PreparedStatement statement = connection.prepareStatement("select * from oferta");
             ResultSet resultSet = statement.executeQuery()) {

            while (resultSet.next()) {
                Long id = resultSet.getLong("id");
                Long id_persoana= resultSet.getLong("id_client");
                Long id_sofer= resultSet.getLong("id_sofer");
                Integer timp=resultSet.getInt("timp");
                Long id_cerere=resultSet.getLong("id_cerere");
                //LocalDateTime data= resultSet.getTimestamp("data").toLocalDateTime();
                //Optional<Persoana> persoana=repoPersoana.findOne(id_persoana);
                //Optional<Sofer>sofer=repoSofer.findOne(id_sofer);
                Oferta oferta=new Oferta(id_persoana, id_sofer,id_cerere, timp);
                oferta.setId(id);

                users.put(oferta.getId(), oferta);
            }
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }

        return users.values();
    }

}
