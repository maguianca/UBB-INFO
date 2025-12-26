package com.example.guiex1.domain;

import java.util.List;
import java.util.Objects;

public class Utilizator extends Entity<Long>{
    private String firstName;
    private String lastName;
    private String password;
    private List<Long> friends;

    public Utilizator(){}
    public Utilizator(String firstName, String lastName,String password) {
        this.firstName = firstName;
        this.lastName = lastName;
        this.password = password;
    }

    public Utilizator(String firstName, String lastName, String password, List<Long> friends)
    {
        this.firstName = firstName;
        this.lastName = lastName;
        this.password = password;
        this.friends = friends;
    }

    public String getPassword() {
        return password;
    }

    public void setFriends(List<Long> friends) {
        this.friends = friends;
    }

    public void setPassword(String password) {
        this.password = password;
    }
    public String getFirstName() {
        return firstName;
    }

    public void setFirstName(String firstName) {
        this.firstName = firstName;
    }

    public String getLastName() {
        return lastName;
    }

    public void setLastName(String lastName) {
        this.lastName = lastName;
    }

    public List<Long> getFriends() {
        return friends;
    }

    @Override
    public String toString() {
        return "Utilizator{" +
                "firstName='" + firstName + '\'' +
                ", lastName='" + lastName + '\'' +
                ", friends=" + friends +
                '}';
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof Utilizator)) return false;
        Utilizator that = (Utilizator) o;
        return getId().equals(that.getId());
    }

    @Override
    public int hashCode() {
        return Objects.hash(getFirstName(), getLastName(), getFriends());
    }
}