package com.example.trenuri.domeniu;

import java.util.Objects;

public class Client{
    private Integer id;
    private String iddeparturecity;
    private String iddestinationcity;
    public Client(Integer id, String iddeparturecity, String iddestinationcity) {
        this.id = id;
        this.iddeparturecity = iddeparturecity;
        this.iddestinationcity = iddestinationcity;
    }

    public Integer getId() {
        return id;
    }

    public void setId(Integer id) {
        this.id = id;
    }

    public String getIddeparturecity() {
        return iddeparturecity;
    }

    public void setIddeparturecity(String iddeparturecity) {
        this.iddeparturecity = iddeparturecity;
    }

    public String getIddestinationcity() {
        return iddestinationcity;
    }

    public void setIddestinationcity(String iddestinationcity) {
        this.iddestinationcity = iddestinationcity;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Client client = (Client) o;
        return Objects.equals(iddeparturecity, client.iddeparturecity) && Objects.equals(iddestinationcity, client.iddestinationcity);
    }

    @Override
    public int hashCode() {
        return Objects.hash(iddeparturecity, iddestinationcity);
    }
}
