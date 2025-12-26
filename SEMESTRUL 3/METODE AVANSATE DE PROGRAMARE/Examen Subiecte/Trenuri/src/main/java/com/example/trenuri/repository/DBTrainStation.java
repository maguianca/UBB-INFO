package com.example.trenuri.repository;

import com.example.trenuri.domeniu.TrainStation;

import java.util.ArrayList;
import java.util.HashMap;
import java.sql.*;
import java.util.Map;

public class DBTrainStation {
    DBCity cityRepository;
    private static final String URL = "jdbc:postgresql://127.0.0.1:5432/trenuri";
    private static final String USER = "postgres";
    private static final String PASSWORD = "1205";
    public DBTrainStation(DBCity cityRepository) {
        this.cityRepository = cityRepository;
    }
    public Iterable<TrainStation> findAll(){
        Map<Long, TrainStation> users = new HashMap<>();
        try (Connection connection = DriverManager.getConnection(URL, USER, PASSWORD);
             PreparedStatement statement = connection.prepareStatement("select * from trainstation");
             ResultSet resultSet = statement.executeQuery()) {

            while (resultSet.next()) {
                Long id = resultSet.getLong("id");
                String idTrainStation = resultSet.getString("idtrainstation");
                String departureCityId = resultSet.getString("departurecityid");
                String destinationCityId = resultSet.getString("destinationcityid");
                TrainStation trainStation=new TrainStation(idTrainStation,departureCityId,destinationCityId);
                trainStation.setId(id);
                //System.out.println(trainStation);
                users.put(id, trainStation);
            }
        } catch (SQLException e) {
            return new ArrayList<>();
        }
        return users.values();
    }

}
