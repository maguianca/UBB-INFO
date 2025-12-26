package com.example.examen.repository;

import com.example.examen.domeniu.Notificare;

import java.sql.*;
import java.util.HashMap;
import java.util.Map;
import java.util.Optional;

public class DBRepoNotificare {
    private static final String URL = "jdbc:postgresql://127.0.0.1:5432/examen";
    private static final String USER = "postgres";
    private static final String PASSWORD = "1205";
    private DBRepoAdoptionCentre dbRepoAdoptionCentre;

    public DBRepoNotificare(DBRepoAdoptionCentre dbRepoAdoptionCentre) {
        this.dbRepoAdoptionCentre = dbRepoAdoptionCentre;
    }

    public Optional<Notificare> findOne(Integer id) {
        if (id == null) throw new IllegalArgumentException("Id-ul utilizatorului nu poate fi nul");

        String query = "SELECT * FROM notificare WHERE id = ?";
        Notificare cerere = null;
        try (Connection connection = DriverManager.getConnection(URL, USER, PASSWORD);
             PreparedStatement statement = connection.prepareStatement(query)) {

            statement.setInt(1, id);
            ResultSet resultSet = statement.executeQuery();
            while (resultSet.next()) {
                Integer centreid = resultSet.getInt("centruid");
                Integer animalid = resultSet.getInt("animalid");
                Integer alocat= resultSet.getInt("centrualocat");
                cerere = new Notificare(id, centreid, animalid,alocat);
            }

        } catch (SQLException e) {
            return Optional.empty();
        }
        return Optional.ofNullable(cerere);
    }

    public Iterable<Notificare> findAll(Integer idcentre, String locatie) {
        Map<Long, Notificare> notificari = new HashMap<>();
        String query = "SELECT n.id, n.centruid, n.animalid,n.centrualocat " +
                "FROM notificare n " +
                "INNER JOIN adoptioncentre a ON n.centruid = a.id " +
                "WHERE a.location = ?";
        try (Connection connection = DriverManager.getConnection(URL, USER, PASSWORD);
             PreparedStatement statement = connection.prepareStatement(query)) {

            statement.setString(1, locatie);
            //statement.setInt(2, idcentre);
            ResultSet resultSet = statement.executeQuery();

            while (resultSet.next()) {
                Long id = resultSet.getLong("id");
                Integer animalid = resultSet.getInt("animalid");
                Integer alocat = resultSet.getInt("centrualocat");
                Integer centreid = resultSet.getInt("centruid");
                Notificare notificare = new Notificare(id.intValue(), centreid, animalid, alocat);
                notificari.put(notificare.getId().longValue(), notificare);
            }
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }

        return notificari.values();
    }

    public void save(Notificare notificare) {
        String query = "INSERT INTO notificare (centruid, animalid) VALUES (?, ?)";
        try (Connection connection = DriverManager.getConnection(URL, USER, PASSWORD);
             PreparedStatement statement = connection.prepareStatement(query)) {

            statement.setInt(1, notificare.getCentreid());
            statement.setInt(2, notificare.getAnimalid());
            statement.executeUpdate();
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    public void delete(Integer id) {
        String query = "DELETE FROM notificare WHERE id = ?";
        try (Connection connection = DriverManager.getConnection(URL, USER, PASSWORD);
             PreparedStatement statement = connection.prepareStatement(query)) {

            statement.setInt(1, id);
            statement.executeUpdate();
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }
}