package com.example.vacante.domeniu;

public class Client{
    private Long clientId;
    private String name;
    private Integer fidelityGrade;
    private Integer age;
    private Hobby hobbies;
    public enum Hobby{
        reading,music,hiking,walking,extreme_sports;
    }
    public Client(Long clientId, String name, Integer fidelityGrade, Integer age, Hobby hobbies) {
        this.clientId = clientId;
        this.name = name;
        this.fidelityGrade = fidelityGrade;
        this.age = age;
        this.hobbies = hobbies;
    }

    public Long getClientId() {
        return clientId;
    }

    public void setClientId(Long clientId) {
        this.clientId = clientId;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public Integer getFidelityGrade() {
        return fidelityGrade;
    }

    public void setFidelityGrade(Integer fidelityGrade) {
        this.fidelityGrade = fidelityGrade;
    }

    public Integer getAge() {
        return age;
    }

    public void setAge(Integer age) {
        this.age = age;
    }

    public Hobby getHobbies() {
        return hobbies;
    }

    public void setHobbies(Hobby hobbies) {
        this.hobbies = hobbies;
    }

    @Override
    public String toString() {
        return "Client{" +
                "clientId=" + clientId +
                ", name='" + name + '\'' +
                ", fidelityGrade=" + fidelityGrade +
                ", age=" + age +
                ", hobbies=" + hobbies +
                '}';
    }
}
