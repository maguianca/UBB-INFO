package com.example.taximetrie2.repository;

import com.example.taximetrie2.domeniu.Comanda;
import com.example.taximetrie2.domeniu.Persoana;
import com.example.taximetrie2.domeniu.Sofer;
import com.example.taximetrie2.paging.Page;
import com.example.taximetrie2.paging.Pageable;

import java.sql.*;
import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;
import java.util.Optional;

public class DBRepoComanda {

    private static final String URL = "jdbc:postgresql://127.0.0.1:5432/taximetrie";
    private static final String USER = "postgres";
    private static final String PASSWORD="1205";
    DBRepoSofer dbRepoSofer;
    DBRepoPersoana dbRepoPersoana;
    public DBRepoComanda(DBRepoPersoana dbRepoPersoana,DBRepoSofer dbRepoSofer){
        this.dbRepoPersoana=dbRepoPersoana;
        this.dbRepoSofer=dbRepoSofer;

    }
    public Optional<Comanda> save(Comanda entity) {
        if (entity == null) {
            throw new IllegalArgumentException("Persoana nu poate fi nula");
        }
        String query = "INSERT INTO comanda(id_persoana,id_sofer,data) VALUES (?, ?, ?)";
        try (Connection connection = DriverManager.getConnection(URL, USER, PASSWORD);
             PreparedStatement statement = connection.prepareStatement(query)) {

            //statement.setLong(1, entity.getId());
            statement.setLong(1, entity.getPersoana().getId());
            statement.setLong(2, entity.getTaximetrist().getId());
            statement.setTimestamp(3, Timestamp.valueOf(entity.getData()));

            int rowsAffected = statement.executeUpdate();
            if (rowsAffected > 0) {
                return Optional.of(entity);
            }
        } catch (SQLException e) {
            System.err.println("Error saving user: " + e.getMessage());
        }
        return Optional.empty();
    }
    public Page<Long> getPagedPersoaneForSoferID(Long id, Pageable pageable) {
        ArrayList<Long> Ids= new ArrayList<>();
        String queryTotalNumberOfElements = "SELECT COUNT(DISTINCT id_persoana) AS count FROM comanda WHERE id_sofer = ?";
        String query = "SELECT DISTINCT id_persoana FROM comanda WHERE id_sofer = ? LIMIT ? OFFSET ?";
        int count=0;
        try (Connection connection = DriverManager.getConnection(URL, USER, PASSWORD);
             PreparedStatement preparedStatement = connection.prepareStatement(query);
             PreparedStatement preparedStatementCount = connection.prepareStatement(queryTotalNumberOfElements)) {
            preparedStatement.setLong(1, id);
            int offset = (pageable.getPageNumber() - 1) * pageable.getPageSize();
            preparedStatement.setInt(2,pageable.getPageSize());
            preparedStatement.setInt(3,offset);

            try (ResultSet resultSet = preparedStatement.executeQuery()) {
                while (resultSet.next()) {
                    long persoanaId = resultSet.getLong("id_persoana");
                    Ids.add(persoanaId);
                }
            }
            preparedStatementCount.setLong(1,id);

            try(ResultSet resultSet = preparedStatementCount.executeQuery()){
                while(resultSet.next()) {
                    count = resultSet.getInt("count");
                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return new Page<>(count, Ids);
    }
    public Iterable<Comanda> findAll() {
        Map<Long, Comanda> users = new HashMap<>();
        try (Connection connection = DriverManager.getConnection(URL, USER, PASSWORD);
             PreparedStatement statement = connection.prepareStatement("select * from comanda");
             ResultSet resultSet = statement.executeQuery()) {

            while (resultSet.next()) {
                Long id = resultSet.getLong("id");
                Long id_persoana= resultSet.getLong("id_persoana");
                Long id_sofer= resultSet.getLong("id_sofer");
                LocalDateTime data= resultSet.getTimestamp("data").toLocalDateTime();
                Optional<Persoana> persoana=dbRepoPersoana.findOneId(id_persoana);
                Optional<Sofer>sofer=dbRepoSofer.findOneId(id_sofer);
                Comanda comanda=new Comanda(persoana.orElse(null),sofer.orElse(null),data);
                comanda.setId(id);

                users.put(comanda.getId(), comanda);
            }
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }

        return users.values();
    }
}
