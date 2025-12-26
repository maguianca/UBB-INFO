package com.example.examen.domeniu;

public class Animal {
    private Integer id;
    private String name;
    private Integer centreId;
    private Type type;

    public enum Type {
        DOG, CAT
    }

    public Animal(Integer id, String name, Integer centreId, Type type) {
        this.id = id;
        this.name = name;
        this.centreId = centreId;
        this.type = type;
    }

    public Integer getId() {
        return id;
    }

    public void setId(Integer id) {
        this.id = id;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public Integer getCentreId() {
        return centreId;
    }

    public void setCentreId(Integer centreId) {
        this.centreId = centreId;
    }

    @Override
    public String toString() {
        return "Animal{" +
                "id=" + id +
                ", name='" + name + '\'' +
                ", centreId=" + centreId +
                ", type=" + type +
                '}';
    }

    public Type getType() {
        return type;
    }

    public void setType(Type type) {
        this.type = type;
    }
}