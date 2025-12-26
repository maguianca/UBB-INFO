package com.example.taximetrie.repository;

import com.example.taximetrie.domeniu.*;

import java.sql.*;
import java.time.LocalDateTime;
import java.util.HashMap;
import java.util.Map;
import java.util.Optional;


import com.example.taximetrie.domeniu.Comanda;
import com.example.taximetrie.domeniu.Persoana;
import com.example.taximetrie.domeniu.Sofer;

import java.sql.*;
import java.time.LocalDateTime;
import java.util.HashMap;
import java.util.Map;
import java.util.Optional;
public class DBCerereRepo implements Repository<Long, Cerere> {

        private static final String URL = "jdbc:postgresql://127.0.0.1:5432/taximetrie";
        private static final String USER = "postgres";
        private static final String PASSWORD="1205";
        //private Validator<Comanda> validator;
        private Repository<Long, Persoana>repoPersoana;
        public DBCerereRepo() {
            //this.repoPersoana = repoPersoana;
        }
        @Override
        public Optional<Cerere> findOne(Long id) {
            if (id == null) throw new IllegalArgumentException("Id-ul utilizatorului nu poate fi nul");

            String query = "SELECT * FROM cerere WHERE id = ?";
            //Comanda comanda= null;
            Cerere cerere = null;
            try (Connection connection = DriverManager.getConnection(URL, USER, PASSWORD);
                 PreparedStatement statement = connection.prepareStatement(query);) {

                statement.setLong(1, id);
                ResultSet resultSet = statement.executeQuery();
                while (resultSet.next()) {
                    Long id_persoana = resultSet.getLong("id_client");
                    String adresa = resultSet.getString("adresa");
                    //Optional<Persoana> persoana = repoPersoana.findOne(id_persoana);
                    cerere = new Cerere(id_persoana, adresa);
                    cerere.setId(id);
                }

            } catch (SQLException e) {
                return Optional.empty();
            }
            return Optional.ofNullable(cerere);
        }

        @Override
        public Iterable<Cerere> findAll() {
            Map<Long, Cerere> users = new HashMap<>();
            try (Connection connection = DriverManager.getConnection(URL, USER, PASSWORD);
                 PreparedStatement statement = connection.prepareStatement("select * from cerere");
                 ResultSet resultSet = statement.executeQuery()) {

                while (resultSet.next()) {
                    Long id = resultSet.getLong("id");
                    Long id_persoana= resultSet.getLong("id_client");
                    String adresa= resultSet.getString("adresa");
                    //LocalDateTime data= resultSet.getTimestamp("data").toLocalDateTime();
                    //Optional<Persoana> persoana=repoPersoana.findOne(id_persoana);
                    //Optional<Sofer>sofer=repoSofer.findOne(id_sofer);
                    Cerere cerere=new Cerere(id_persoana,adresa);
                    cerere.setId(id);

                    users.put(cerere.getId(), cerere);
                }
            } catch (SQLException e) {
                throw new RuntimeException(e);
            }

            return users.values();
        }

        @Override
        public Optional<Cerere> save(Cerere entity) {
            if (entity == null) {
                throw new IllegalArgumentException("Persoana nu poate fi nula");
            }
            String query = "INSERT INTO cerere(id_client,adresa) VALUES (?,?)";
            try (Connection connection = DriverManager.getConnection(URL, USER, PASSWORD);
                 PreparedStatement statement = connection.prepareStatement(query)) {

                //statement.setLong(1, entity.getId());
                statement.setLong(1, entity.getId_client());
                statement.setString(2, entity.getAdresa());

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
        public Optional<Cerere> delete(Long id) {
            if (id == null) throw new IllegalArgumentException("Utilizatorul nu poate fi nul");

           /* Cerere userToDelete = findOne(id).orElse(null);
            if (userToDelete == null) {
                return Optional.empty();
            }*/
            System.out.println("Se sterge");
            String query = "DELETE FROM cerere WHERE id = ?";
            try (Connection connection = DriverManager.getConnection(URL, USER, PASSWORD);
                 PreparedStatement statement = connection.prepareStatement(query)) {
                statement.setLong(1, id);
                statement.executeUpdate();
            } catch (SQLException e) {
                throw new RuntimeException(e);
            }

            return Optional.empty();
        }


    }

