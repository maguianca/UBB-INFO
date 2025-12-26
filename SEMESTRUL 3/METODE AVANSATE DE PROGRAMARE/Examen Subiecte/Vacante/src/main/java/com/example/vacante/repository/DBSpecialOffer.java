package com.example.vacante.repository;

import com.example.vacante.domeniu.SpecialOffer;

import java.sql.*;
import java.time.LocalDate;
import java.util.HashMap;
import java.util.Map;

public class DBSpecialOffer {
    private static final String URL = "jdbc:postgresql://127.0.0.1:5432/vacante";
    private static final String USER = "postgres";
    private static final String PASSWORD = "1205";
    public DBSpecialOffer(){

    }
    public Iterable<SpecialOffer>findAllOffer(){
        Map<Long, SpecialOffer> users = new HashMap<>();
        String query = "SELECT * FROM specialoffer";
        try (Connection connection = DriverManager.getConnection(URL, USER, PASSWORD);
             PreparedStatement statement = connection.prepareStatement(query)) {
            ResultSet resultSet = statement.executeQuery();
            while (resultSet.next()) {
                Long id = resultSet.getLong("id");
                Double specialofferid=resultSet.getDouble("specialofferid");
                Double hotelid=resultSet.getDouble("hotelid");
                LocalDate startdate=resultSet.getDate("startdate").toLocalDate();
                LocalDate enddate=resultSet.getDate("enddate").toLocalDate();
                Integer percent=resultSet.getInt("percents");
                SpecialOffer special=new SpecialOffer(specialofferid,hotelid,startdate,enddate,percent);
                special.setId(id);
                //System.out.println(startdate);
                //System.out.println(special);
                users.put(id,special);
            }
        } catch (SQLException e) {
            return users.values();
        }
        return users.values();
    }
}
