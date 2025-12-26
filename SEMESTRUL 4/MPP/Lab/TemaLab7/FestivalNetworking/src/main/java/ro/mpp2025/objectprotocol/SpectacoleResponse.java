package ro.mpp2025.objectprotocol;

import ro.mpp2025.Domain.Spectacol;
import ro.mpp2025.dto.DTOFactory;
import ro.mpp2025.dto.SpectacolDTO;

import java.util.Arrays;
import java.util.List;

public class SpectacoleResponse implements IResponse {
    private final SpectacolDTO[] spectacole;

    protected SpectacoleResponse(Spectacol[] spectacole){
        this.spectacole = DTOFactory.getDTO(Arrays.asList(spectacole));
    }

    public List<SpectacolDTO> getSpectacole() {
        return Arrays.asList(spectacole);
    }
}
