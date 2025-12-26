package com.example.vacante.domeniu;

public class Hotel extends Entity<Long>{
    private Double hotelId;
    private String locationName ;
    private String hotelName;
    private Integer noRooms;
    private Double pricePerNight;
    public Hotel(Double hotelId, String locationName, String hotelName, Integer noRooms, Double pricePerNight) {
        this.hotelId = hotelId;
        this.locationName = locationName;
        this.hotelName = hotelName;
        this.noRooms = noRooms;
        this.pricePerNight = pricePerNight;
    }

    public Double getHotelId() {
        return hotelId;
    }

    public void setHotelId(Double hotelId) {
        this.hotelId = hotelId;
    }

    public String getLocationName() {
        return locationName;
    }

    public void setLocationName(String locationName) {
        this.locationName = locationName;
    }

    public String getHotelName() {
        return hotelName;
    }

    public void setHotelName(String hotelName) {
        this.hotelName = hotelName;
    }

    public Integer getNoRooms() {
        return noRooms;
    }

    public void setNoRooms(Integer noRooms) {
        this.noRooms = noRooms;
    }

    public Double getPricePerNight() {
        return pricePerNight;
    }

    public void setPricePerNight(Double pricePerNight) {
        this.pricePerNight = pricePerNight;
    }
    @Override
    public String toString() {
        return "Hotel{" +
                "hotelId=" + hotelId +
                ", locationName='" + locationName + '\'' +
                ", hotelName='" + hotelName + '\'' +
                ", noRooms=" + noRooms +
                ", pricePerNight=" + pricePerNight +
                '}';
    }
}
