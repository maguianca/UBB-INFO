package com.example.vacante.repository;

import com.example.vacante.domeniu.Reservation;
import com.example.vacante.domeniu.SpecialOffer;

import java.sql.*;
import java.time.LocalDate;
import java.time.LocalDateTime;
import java.util.HashMap;
import java.util.Map;
import java.util.Optional;

public class DBReservation {
    private static final String URL = "jdbc:postgresql://127.0.0.1:5432/vacante";
    private static final String USER = "postgres";
    private static final String PASSWORD = "1205";
    public DBReservation(){

    }
    public Optional<Reservation> save(Reservation entity){
        if (entity == null) {
            throw new IllegalArgumentException("Ticket cannot be null");
        }
        String query = "INSERT INTO reservation(reservationid,clientid,hotelid,startdate,nonights) values(?,?,?,?,?)";
        try (Connection connection = DriverManager.getConnection(URL, USER, PASSWORD);
             PreparedStatement statement = connection.prepareStatement(query)) {

            statement.setDouble(1, entity.getReservationId());
            statement.setDouble(2,entity.getClientId());
            statement.setDouble(3,entity.getHotelId());
            statement.setTimestamp(4, Timestamp.valueOf(entity.getStartDate()));
            statement.setInt(5,entity.getNoNights());

            // Execute the query
            statement.executeUpdate();
        } catch (SQLException e) {
            // Optionally, you might want to log or print the error
            e.printStackTrace();
            return Optional.empty();
        }
        return Optional.of(entity);
    }
    public double getLastReservationId() {
        String query = "SELECT MAX(reservationid) FROM reservation";
        try (Connection connection = DriverManager.getConnection(URL, USER, PASSWORD);
             Statement statement = connection.createStatement();
             ResultSet resultSet = statement.executeQuery(query)) {

            if (resultSet.next()) {
                return resultSet.getDouble(1);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return 0;
    }
    public Iterable<Reservation>findAll(){
        Map<Long, Reservation> users = new HashMap<>();
        String query = "SELECT * FROM reservation";
        try (Connection connection = DriverManager.getConnection(URL, USER, PASSWORD);
             PreparedStatement statement = connection.prepareStatement(query)) {
            ResultSet resultSet = statement.executeQuery();
            while (resultSet.next()) {
                Long id = resultSet.getLong("id");
                Double reservationid=resultSet.getDouble("reservationid");
                Long clientid=resultSet.getLong("clientid");
                Double hotelid=resultSet.getDouble("hotelid");
                LocalDateTime startdate=resultSet.getTimestamp("startdate").toLocalDateTime();
                Integer nonights=resultSet.getInt("nonights");
                Reservation special=new Reservation(reservationid,clientid,hotelid,startdate,nonights);
                special.setId(id);
                //System.out.println(startdate);
                System.out.println(special);
                users.put(id,special);
            }
        } catch (SQLException e) {
            return users.values();
        }
        return users.values();
    }
}
