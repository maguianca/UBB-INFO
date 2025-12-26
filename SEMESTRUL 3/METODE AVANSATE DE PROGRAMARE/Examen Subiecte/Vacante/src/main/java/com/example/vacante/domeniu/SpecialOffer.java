package com.example.vacante.domeniu;

import java.time.LocalDate;
import java.util.Date;

public class SpecialOffer extends Entity<Long>{
    private Double specialOfferId;
    private Double hotelId;
    private LocalDate startDate;
    private LocalDate endDate;
    private Integer percents;
    public SpecialOffer(Double specialOfferId, Double hotelId, LocalDate startDate, LocalDate endDate, Integer percents) {
        this.specialOfferId = specialOfferId;
        this.hotelId = hotelId;
        this.startDate = startDate;
        this.endDate = endDate;
        this.percents = percents;
    }

    public Double getSpecialOfferId() {
        return specialOfferId;
    }

    public void setSpecialOfferId(Double specialOfferId) {
        this.specialOfferId = specialOfferId;
    }

    public Double getHotelId() {
        return hotelId;
    }

    public void setHotelId(Double hotelId) {
        this.hotelId = hotelId;
    }

    public LocalDate getStartDate() {
        return startDate;
    }

    public void setStartDate(LocalDate startDate) {
        this.startDate = startDate;
    }

    public LocalDate getEndDate() {
        return endDate;
    }

    public void setEndDate(LocalDate endDate) {
        this.endDate = endDate;
    }

    public Integer getPercents() {
        return percents;
    }

    public void setPercents(Integer percents) {
        this.percents = percents;
    }
    @Override
    public String toString() {
        return "SpecialOffer{" +
                "specialOfferId=" + specialOfferId +
                ", hotelId=" + hotelId +
                ", startDate=" + startDate +
                ", endDate=" + endDate +
                ", percents=" + percents +
                '}';
    }
}
