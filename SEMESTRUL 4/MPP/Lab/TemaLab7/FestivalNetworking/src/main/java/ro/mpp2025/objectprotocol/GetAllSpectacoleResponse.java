package ro.mpp2025.objectprotocol;

import ro.mpp2025.Domain.Spectacol;


public class GetAllSpectacoleResponse extends SpectacoleResponse {
    public GetAllSpectacoleResponse(Spectacol[] spectacole) {
        super(spectacole);
    }
}
