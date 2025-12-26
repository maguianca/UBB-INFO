package com.example.trenuri.domeniu;

public class City extends Entity<Long>{
    private String id;
    private String name;
    public City(String id,String name){
        this.id=id;
        this.name=name;
    }

    public String getid() {
        return id;
    }

    public void setid(String id) {
        this.id = id;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }
    @Override
    public String toString() {
        return "City{" +
                "id='" + id + '\'' +
                ", name='" + name + '\'' +
                '}';
    }
}
