package com.example.faptebune.repository;
import java.sql.*;
import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;
import java.util.Optional;
import com.example.faptebune.domeniu.*;
public class RepoNevoie {
    private static final String URL = "jdbc:postgresql://127.0.0.1:5432/faptebune";
    private static final String USER = "postgres";
    private static final String PASSWORD = "1205";
    RepoPersoana repoPersoana=new RepoPersoana();
    public RepoNevoie(RepoPersoana repoPersoana) {
        this.repoPersoana = repoPersoana;
    }
    public Optional<Nevoie> findOne(Long id) {
        if (id == null) throw new IllegalArgumentException("Id-ul utilizatorului nu poate fi nul");
        Nevoie nevoie = null;
        String query = "SELECT * FROM nevoie WHERE id = ?";
        try (Connection connection = DriverManager.getConnection(URL, USER, PASSWORD);
             PreparedStatement statement = connection.prepareStatement(query)) {

            statement.setLong(1, id);
            ResultSet resultSet = statement.executeQuery();
            while (resultSet.next()) {
                String titlu=resultSet.getString("titlu");
                String descriere = resultSet.getString("descriere");
                LocalDateTime data = resultSet.getTimestamp("deadline").toLocalDateTime();
                Long om_nevoie=resultSet.getLong("ominnevoie");
                Long om_ajutat=resultSet.getLong("omsalvator");
                String status=resultSet.getString("status");
                nevoie = new Nevoie(titlu,descriere,data,om_nevoie,om_ajutat,status);
                nevoie.setId(id);
            }

        } catch (SQLException e) {
            return Optional.empty();
        }
        return Optional.ofNullable(nevoie);
    }
    public Optional<Nevoie>save(Nevoie entity){
        if (entity == null) {
            throw new IllegalArgumentException("Persoana nu poate fi nula");
        }
        String query = "INSERT INTO nevoie(titlu,descriere,deadline,ominnevoie,omsalvator,status) values(?,?,?,?,null,?)";
        try (Connection connection = DriverManager.getConnection(URL, USER, PASSWORD);
             PreparedStatement statement = connection.prepareStatement(query)) {

            statement.setString(1, entity.getTitlu());
            statement.setString(2, entity.getDescriere());
            statement.setTimestamp(3, Timestamp.valueOf(entity.getDeadline()));
            statement.setLong(4, entity.getOmInNevoie());
            //statement.setNull(5, Types.BIGINT);
            /*if (entity.getOmSalvator() != null) {
                statement.setLong(5, entity.getOmSalvator());
            } else {
                statement.setNull(5, Types.BIGINT);
            }*/
            statement.setString(5, entity.getStatus());
            statement.executeUpdate();
            System.out.println("Nevoie adaugata cu succes!");
            return Optional.empty();
        } catch (SQLException e) {
            return Optional.of(entity);
        }

    }
    public Iterable<Nevoie> findAll() {
        Map<Long, Nevoie> users = new HashMap<>();
        try (Connection connection = DriverManager.getConnection(URL, USER, PASSWORD);
             PreparedStatement statement = connection.prepareStatement("select * from nevoie");
             ResultSet resultSet = statement.executeQuery()) {

            while (resultSet.next()) {
                Long id = resultSet.getLong("id");
                String titlu=resultSet.getString("titlu");
                String descriere = resultSet.getString("descriere");
                LocalDateTime data = resultSet.getTimestamp("deadline").toLocalDateTime();
                Long om_nevoie=resultSet.getLong("ominnevoie");
                Long om_ajutat=resultSet.getLong("omsalvator");
                String status=resultSet.getString("status");
                Nevoie nevoie = new Nevoie(titlu,descriere,data,om_nevoie,om_ajutat,status);
                nevoie.setId(id);
                users.put(id, nevoie);
            }
        } catch (SQLException e) {
            return new ArrayList<>();
        }
        return users.values();
    }
    public void update(Long id,Long id2){
        String query = "UPDATE nevoie SET omsalvator = ?, status=? WHERE id = ?";
        try (Connection connection = DriverManager.getConnection(URL, USER, PASSWORD);
             PreparedStatement statement = connection.prepareStatement(query)) {
            statement.setLong(1, id2);
            statement.setString(2, "Erou Gasit!");
            statement.setLong(3, id);
            statement.executeUpdate();
        } catch (SQLException e) {
            System.err.println("Error updating user " + e);
        }
    }

}
