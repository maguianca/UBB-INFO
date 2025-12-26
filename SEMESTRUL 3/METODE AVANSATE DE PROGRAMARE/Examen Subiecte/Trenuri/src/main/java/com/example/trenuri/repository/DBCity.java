package com.example.trenuri.repository;

import com.example.trenuri.domeniu.City;

import java.sql.*;
import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;
import java.util.Optional;

public class DBCity {
    private static final String URL = "jdbc:postgresql://127.0.0.1:5432/trenuri";
    private static final String USER = "postgres";
    private static final String PASSWORD = "1205";
    public DBCity(){

    }
    public Iterable<City> findAll(){
        Map<Long, City> users = new HashMap<>();
        try (Connection connection = DriverManager.getConnection(URL, USER, PASSWORD);
             PreparedStatement statement = connection.prepareStatement("select * from city");
             ResultSet resultSet = statement.executeQuery()) {

            while (resultSet.next()) {
                Long id = resultSet.getLong("id");
                String idCity = resultSet.getString("idcity");
                String name = resultSet.getString("name");
                City city=new City(idCity,name);
                city.setId(id);
                users.put(id, city);
            }
        } catch (SQLException e) {
            return new ArrayList<>();
        }
        return users.values();
    }
    public Optional<City> findOne(String idCity){
        if (idCity == null) throw new IllegalArgumentException("Id-ul utilizatorului nu poate fi nul");
        City city = null;
        String query = "SELECT * FROM city WHERE idcity = ?";
        try (Connection connection = DriverManager.getConnection(URL, USER, PASSWORD);
             PreparedStatement statement = connection.prepareStatement(query)) {

            statement.setString(1, idCity);
            ResultSet resultSet = statement.executeQuery();
            while (resultSet.next()) {
                Long id = resultSet.getLong("id");
                String name = resultSet.getString("name");
                city = new City(idCity,name);
                city.setId(id);
            }

        } catch (SQLException e) {
            return Optional.empty();
        }
        return Optional.ofNullable(city);
    }
}
