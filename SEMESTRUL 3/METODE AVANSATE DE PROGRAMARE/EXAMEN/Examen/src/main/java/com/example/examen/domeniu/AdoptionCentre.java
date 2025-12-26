package com.example.examen.domeniu;

public class AdoptionCentre{
    private Integer id;
    private String name;
    private String location;
    private Integer capacity;
    public AdoptionCentre(Integer id,String name,String location,Integer capacity){
        this.id=id;
        this.name=name;
        this.location=location;
        this.capacity=capacity;
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

    public String getLocation() {
        return location;
    }

    public void setLocation(String location) {
        this.location = location;
    }

    public Integer getCapacity() {
        return capacity;
    }

    public void setCapacity(Integer capacity) {
        this.capacity = capacity;
    }

    @Override
    public String toString() {
        return super.toString();
    }
}
