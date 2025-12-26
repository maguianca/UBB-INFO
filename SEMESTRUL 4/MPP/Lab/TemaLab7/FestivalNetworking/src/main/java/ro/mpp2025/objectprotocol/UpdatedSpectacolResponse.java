package ro.mpp2025.objectprotocol;

import ro.mpp2025.dto.SpectacolDTO;

public class UpdatedSpectacolResponse extends UpdateResponse{
    SpectacolDTO spectacol;

    public SpectacolDTO getSpectacol() {
        return spectacol;
    }

    public UpdatedSpectacolResponse(SpectacolDTO spectacol) {
        this.spectacol = spectacol;
    }
}
