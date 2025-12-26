package ro.mpp2025.objectprotocol;

import ro.mpp2025.dto.AngajatDTO;

public class LoginAngajatResponse implements IResponse {
    private AngajatDTO angajat;

    public AngajatDTO getAngajat() {
        return angajat;
    }

    public LoginAngajatResponse(AngajatDTO angajat) {
        this.angajat = angajat;
    }

    @Override
    public String toString() {
        return "LoginAngajatResponse{" +
                "angajat=" + angajat +
                '}';
    }
}
