package com.example.trenuri.domeniu;

public class TrainStation extends Entity<Long> {
    private String id;
    private String departureCityId;
    private String destinationCityId;
    public TrainStation(String id, String departureCityId, String destinationCityId) {
        this.id = id;
        this.departureCityId = departureCityId;
        this.destinationCityId = destinationCityId;
    }

    public String getid() {
        return id;
    }

    public void setid(String id) {
        this.id = id;
    }

    public String getDepartureCityId() {
        return departureCityId;
    }

    public void setDepartureCityId(String departureCityId) {
        this.departureCityId = departureCityId;
    }

    public String getDestinationCityId() {
        return destinationCityId;
    }

    public void setDestinationCityId(String destinationCityId) {
        this.destinationCityId = destinationCityId;
    }
    @Override
    public String toString() {
        return "TrainStation{" +
                "id='" + id + '\'' +
                ", departureCityId='" + departureCityId + '\'' +
                ", destinationCityId='" + destinationCityId + '\'' +
                '}';
    }
}
