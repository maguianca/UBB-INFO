package com.example.vacante.domeniu;

import java.time.LocalDateTime;

public class Reservation extends Entity<Long> {
    private Double reservationId;
    private Double hotelId;
    private Long clientId;
    private Integer noNights;
    private LocalDateTime startDate;
    public Reservation(Double reservationId,Long clientId, Double hotelId, LocalDateTime startDate,Integer noNights) {
        this.reservationId = reservationId;
        this.hotelId = hotelId;
        this.clientId = clientId;
        this.noNights = noNights;
        this.startDate = startDate;
    }

    public Double getReservationId() {
        return reservationId;
    }

    public void setReservationId(Double reservationId) {
        this.reservationId = reservationId;
    }

    public Double getHotelId() {
        return hotelId;
    }

    public void setHotelId(Double hotelId) {
        this.hotelId = hotelId;
    }

    public Long getClientId() {
        return clientId;
    }

    public void setClientId(Long clientId) {
        this.clientId = clientId;
    }

    public Integer getNoNights() {
        return noNights;
    }

    public void setNoNights(Integer noNights) {
        this.noNights = noNights;
    }

    public LocalDateTime getStartDate() {
        return startDate;
    }

    public void setStartDate(LocalDateTime startDate) {
        this.startDate = startDate;
    }
    @Override
    public String toString() {
        return "Reservation{" +
                "reservationId=" + reservationId +
                ", hotelId=" + hotelId +
                ", clientId=" + clientId +
                ", noNights=" + noNights +
                ", startDate=" + startDate +
                '}';
    }
}
