package com.example.guiex1.domain;

import java.util.ArrayList;
import java.util.List;
import java.util.Objects;

public class Utilizator extends Entity<Long>{
    private String firstName;
    private String lastName;
    List<Utilizator>friends;
    private String password;
    private String username;
    private String descriere;
    private String url;
    public Utilizator(String firstName, String lastName,String password,String username,String descriere,String url) {
        this.firstName = firstName;
        this.lastName = lastName;
        friends = new ArrayList<Utilizator>();
        this.password = password;
        this.username = username;
        this.descriere = descriere;
        this.url = url;
    }

    public String getDescriere() {
        return descriere;
    }

    public void setDescriere(String descriere) {
        this.descriere = descriere;
    }

    public String getUrl() {
        return url;
    }

    public void setUrl(String url) {
        this.url = url;
    }

    public String getUsername(){
        return username;
    }
    public void setUsername(String username){
        this.username = username;
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

    public List<Utilizator> getFriends() {
        return friends;
    }
    public void addFriend(Utilizator friend) {
        friends.add(friend);
    }
    public void removeFriend(Utilizator friend) {
        friends.remove(friend);
    }
    public String getPassword() {
        return password;
    }
    public void setPassword(String password) {
        this.password = password;
    }
    @Override
    public String toString() {
        return "Utilizator{" +
                "firstName='" + firstName + '\'' +
                ", lastName='" + lastName + '\'' +
                ", username='" + username + '\'' +
                ", password='" + password + '\'' +
                '}';
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof Utilizator)) return false;
        Utilizator that = (Utilizator) o;
        return getFirstName().equals(that.getFirstName()) &&
                getLastName().equals(that.getLastName());// &&
                //getUsername().equals(that.getUsername())*;/


        //return username != null && username.equalsIgnoreCase(that.username);

    }

    @Override
    public int hashCode() {
        return Objects.hash(getFirstName(), getLastName());
        //return Objects.hash(username != null ? username.toLowerCase() : null);
    }
}