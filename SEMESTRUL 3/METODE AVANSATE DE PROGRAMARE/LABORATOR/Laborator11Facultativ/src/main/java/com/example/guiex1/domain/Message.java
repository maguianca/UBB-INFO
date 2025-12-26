package com.example.guiex1.domain;

import java.time.LocalDateTime;
import java.util.List;
import java.util.Objects;

public class Message extends Entity<Long> {
    private Utilizator userSender;
    private String message;
    private LocalDateTime data;
    private List<Utilizator> users;

    public Message(Utilizator userSender, String message, LocalDateTime data, List<Utilizator> users) {
        this.userSender = userSender;
        this.message = message;
        this.data = data;
        this.users = users;
    }

    public Utilizator getUserSender() {
        return userSender;
    }

    public void setUserSender(Utilizator userSender) {
        this.userSender = userSender;
    }


    public String getMessage() {
        return message;
    }

    public void setMessage(String message) {
        this.message = message;
    }

    public LocalDateTime getData() {
        return data;
    }

    public void setData(LocalDateTime data) {
        this.data = data;
    }

    public List<Utilizator> getUsers() {
        return users;
    }

    public void setUsers(List<Utilizator> users) {
        this.users = users;
    }


    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof Message message1)) return false;
        if (!super.equals(o)) return false;
        return Objects.equals(getUserSender(), message1.getUserSender()) && Objects.equals(getMessage(), message1.getMessage()) && Objects.equals(getData(), message1.getData()) && Objects.equals(getUsers(), message1.getUsers());
    }

    @Override
    public int hashCode() {
        return Objects.hash(super.hashCode(), getUserSender(), getMessage(), getData(), getUsers());
    }

    @Override
    public String toString() {
        String toS= "Message{" +
                "userSender=" + userSender +
                ", message='" + message + '\'' +
                ", data=" + data +
                ", users=" ;
        for (Utilizator u : users) {
            toS += u.getFirstName()+" "+u.getLastName()+"\n";
        }
        toS+="}";
        return toS;}
}