package com.example.comenzirestaurant.repository;

import com.example.comenzirestaurant.domeniu.*;
import com.example.comenzirestaurant.domeniu.Table;

import java.sql.*;
import java.util.HashMap;
import java.util.Map;
import java.util.Optional;

public class DBTable implements Repository<Long, Table> {

        private static final String URL = "jdbc:postgresql://127.0.0.1:5432/comenzi";
        private static final String USER = "postgres";
        private static final String PASSWORD="1205";
        private Repository<Long, Table>repoTable;
        public DBTable() {

        }
        @Override
        public Optional<Table> findOne(Long id) {
            return Optional.empty();
        }

        @Override
        public Iterable<Table> findAll() {
            Map<Long, Table> users = new HashMap<>();
            try (Connection connection = DriverManager.getConnection(URL, USER, PASSWORD);
                 PreparedStatement statement = connection.prepareStatement("select * from masa");
                 ResultSet resultSet = statement.executeQuery()) {

                while (resultSet.next()) {
                    Long id = resultSet.getLong("id");
                    Table t=new Table(id);
                    t.setId(id);

                    users.put(t.getId(), t);
                }
            } catch (SQLException e) {
                throw new RuntimeException(e);
            }

            return users.values();
        }

        @Override
        public Optional<Table> save(Table entity) {
            if (entity == null) {
                throw new IllegalArgumentException("Persoana nu poate fi nula");
            }
            String query = "INSERT INTO masa(id) VALUES (?)";
            try (Connection connection = DriverManager.getConnection(URL, USER, PASSWORD);
                 PreparedStatement statement = connection.prepareStatement(query)) {
                statement.setLong(1, entity.getId());
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
        public Optional<Table> delete(Long id) {

            return Optional.empty();
        }
        @Override
    public Optional<Table>update(Table entity){
            return Optional.empty();
        }


    }

