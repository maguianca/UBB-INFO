package ro.mpp2025.objectprotocol;

import ro.mpp2025.dto.SpectacolDTO;

public class ReserveBiletRequest implements IRequest {
    SpectacolDTO spectacol;
    String cumparatorName;
    int seats;

    public SpectacolDTO getSpectacol() {
        return spectacol;
    }

    public String getCumparatorName() {
        return cumparatorName;
    }

    public int getSeats() {
        return seats;
    }

    public ReserveBiletRequest(SpectacolDTO spectacol, String cumparatorName, int seats) {
        this.spectacol = spectacol;
        this.cumparatorName = cumparatorName;
        this.seats = seats;
    }
}
