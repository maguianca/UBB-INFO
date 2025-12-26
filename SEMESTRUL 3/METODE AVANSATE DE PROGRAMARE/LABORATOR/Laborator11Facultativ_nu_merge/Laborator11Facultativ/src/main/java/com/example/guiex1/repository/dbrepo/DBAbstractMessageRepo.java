package com.example.guiex1.repository.dbrepo;


import com.example.guiex1.domain.Utilizator;
import com.example.guiex1.domain.Message;

import java.sql.ResultSet;
import java.sql.SQLException;
import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.List;


public abstract class  DBAbstractMessageRepo {
    protected Utilizator getOwner(ResultSet resultSet) throws SQLException {
        Long id_sender = resultSet.getLong("id_sender");
        String firstName = resultSet.getString("first_name");
        String lastName = resultSet.getString("last_name");
        String username = resultSet.getString("username");
        String password = resultSet.getString("password");
        Utilizator sender = new Utilizator(firstName, lastName, username, password,null,null);
        sender.setId(id_sender);
        return sender;
    }
    private Utilizator getReciever(ResultSet resultSet) throws SQLException {
        Long id_reciver = resultSet.getLong("id_reciever");
        String firstNameR = resultSet.getString("first_nameR");
        String lastNameR = resultSet.getString("last_nameR");
        String usernameR = resultSet.getString("usernameR");
        String passwordR = resultSet.getString("passwordR");

        Utilizator reciever = new Utilizator(firstNameR, lastNameR, usernameR, passwordR,null,null);
        reciever.setId(id_reciver);
        return reciever;
    }
    private Message getMessageFromStatement(ResultSet resultSet) throws SQLException {
        //getting data of message
        Long id_mes = resultSet.getLong("id_message");
        LocalDateTime dateTime = resultSet.getTimestamp("data").toLocalDateTime();
        String message = resultSet.getString("message");
        //creating sender
        Utilizator sender = getOwner(resultSet);

        //celalalt user
        List<Utilizator> users = new ArrayList<>();
        Utilizator reciever = getReciever(resultSet);
        users.add(reciever);
        //continui
        while (resultSet.next()) {

            reciever = getReciever(resultSet);
            users.add(reciever);
        }
        Message messageNew = new Message(sender, message, dateTime, users);
        messageNew.setId(id_mes);
        return messageNew;
    }

}