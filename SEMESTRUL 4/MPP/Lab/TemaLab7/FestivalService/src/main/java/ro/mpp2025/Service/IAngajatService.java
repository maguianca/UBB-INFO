package ro.mpp2025.Service;

import ro.mpp2025.Domain.Angajat;
import ro.mpp2025.Repository.EntityRepoException;

public interface IAngajatService extends IService<Integer, Angajat> {
    void register(Angajat angajat) throws EntityRepoException;
    Angajat login(String username, String password) throws EntityRepoException;
}
