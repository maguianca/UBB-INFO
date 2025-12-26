package ro.mpp2025.objectprotocol;

import ro.mpp2025.Constants;

import java.time.LocalDateTime;

public class FilterSpectacoleRequest implements IRequest{
    String day;

    public FilterSpectacoleRequest(LocalDateTime day) {
        this.day = day.format(Constants.DTO_FORMATTER);
    }

    public LocalDateTime getDay() {
        return LocalDateTime.parse(day, Constants.DTO_FORMATTER);
    }
}
