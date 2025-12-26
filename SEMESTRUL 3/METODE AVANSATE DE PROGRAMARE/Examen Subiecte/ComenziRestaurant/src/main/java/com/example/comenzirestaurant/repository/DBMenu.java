package com.example.comenzirestaurant.repository;

import com.example.comenzirestaurant.domeniu.MenuItem;
import com.example.comenzirestaurant.domeniu.Table;

import java.sql.*;
import java.time.LocalDateTime;
import java.util.HashMap;
import java.util.Map;
import java.util.Optional;

public class DBMenu implements Repository<Long, MenuItem> {

        private static final String URL = "jdbc:postgresql://127.0.0.1:5432/comenzi";
        private static final String USER = "postgres";
        private static final String PASSWORD="1205";
        private Repository<Long, Table>repoTable;
        public DBMenu(Repository<Long,Table>repoTable) {
            this.repoTable=repoTable;

        }
        @Override
        public Optional<MenuItem> findOne(Long id) {
            String query = "SELECT * FROM menu WHERE id = ?";
            MenuItem menu = null;
            try (Connection connection = DriverManager.getConnection(URL, USER, PASSWORD);
                 PreparedStatement statement = connection.prepareStatement(query)) {

                statement.setLong(1, id);
                ResultSet resultSet = statement.executeQuery();
                while (resultSet.next()) {
                    String categorie = resultSet.getString("categorie");
                    String item = resultSet.getString("item");
                    Float pret = resultSet.getFloat("pret");
                    String moneda = resultSet.getString("moneda");
                    menu = new MenuItem(categorie,pret,item,moneda);  // Pass the 'date' to the Friendship object
                    menu.setId(id);
                }
            } catch (SQLException e) {
                System.out.println(e.getMessage());
            }
            return Optional.ofNullable(menu);
        }

        @Override
        public Iterable<MenuItem> findAll() {
            Map<Long, MenuItem> users = new HashMap<>();
            try (Connection connection = DriverManager.getConnection(URL, USER, PASSWORD);
                 PreparedStatement statement = connection.prepareStatement("select * from menu");
                 ResultSet resultSet = statement.executeQuery()) {

                while (resultSet.next()) {
                    Long id = resultSet.getLong("id");
                    String categorie= resultSet.getString("categorie");
                    String item = resultSet.getString("item");
                    Float pret= resultSet.getFloat("pret");
                    String moneda = resultSet.getString("moneda");
                    MenuItem meniu=new MenuItem(categorie,pret,item,moneda);
                    meniu.setId(id);

                    users.put(meniu.getId(), meniu);
                }
            } catch (SQLException e) {
                throw new RuntimeException(e);
            }

            return users.values();
        }

        @Override
        public Optional<MenuItem> save(MenuItem entity) {
            return Optional.empty();
        }

        @Override
        public Optional<MenuItem> delete(Long id) {

            return Optional.empty();
        }

        @Override
        public Optional<MenuItem>update(MenuItem entity){
            return Optional.empty();
        }


    }

