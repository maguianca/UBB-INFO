package com.example.vacante.repository;

import com.example.vacante.domeniu.Client;
import com.example.vacante.domeniu.Hotel;
import com.example.vacante.domeniu.SpecialOffer;

import java.sql.*;
import java.util.HashMap;
import java.util.Map;
import java.util.Optional;

public class DBHotel {
    private static final String URL = "jdbc:postgresql://127.0.0.1:5432/vacante";
    private static final String USER = "postgres";
    private static final String PASSWORD = "1205";
    public DBHotel(){

    }
    public Optional<Hotel>findOne(Double id){
        if (id == null) throw new IllegalArgumentException("Id-ul utilizatorului nu poate fi nul");
        Hotel hotel = null;
        String query = "SELECT * FROM hotel WHERE hotelid = ?";
        try (Connection connection = DriverManager.getConnection(URL, USER, PASSWORD);
             PreparedStatement statement = connection.prepareStatement(query)) {

            statement.setDouble(1, id);
            ResultSet resultSet = statement.executeQuery();
            while (resultSet.next()) {
                Long id_1=resultSet.getLong("id");
                String lname= resultSet.getString("locationname");
                String hname= resultSet.getString("hotelname");
                Integer norooms=resultSet.getInt("norooms");
                Double price=resultSet.getDouble("pricepernight");
                hotel=new Hotel(id,lname,hname,norooms,price);
                hotel.setId(id_1);
            }

        } catch (SQLException e) {
            return Optional.empty();
        }
        return Optional.ofNullable(hotel);
    }
    public Iterable<Hotel>findAll(){
        Map<Long, Hotel> users = new HashMap<>();
        String query = "SELECT * FROM hotel";
        try (Connection connection = DriverManager.getConnection(URL, USER, PASSWORD);
             PreparedStatement statement = connection.prepareStatement(query)) {
            ResultSet resultSet = statement.executeQuery();
            while (resultSet.next()) {
                Double hotelid = resultSet.getDouble("hotelid");
                Long id=resultSet.getLong("id");
                String lname= resultSet.getString("locationname");
                String hname= resultSet.getString("hotelname");
                Integer norooms=resultSet.getInt("norooms");
                Double price=resultSet.getDouble("pricepernight");
                Hotel hotel=new Hotel(hotelid,lname,hname,norooms,price);
                hotel.setId(id);
                users.put(id,hotel);
            }
        } catch (SQLException e) {
            return users.values();
        }
        return users.values();
    }
}
