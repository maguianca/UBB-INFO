package ro.mpp2025.Repository;

import ro.mpp2025.Domain.Angajat;

public interface IAngajatRepo extends IRepo<Integer, Angajat> {
    Angajat findByCredentials(String username, String password) throws EntityRepoException;
}
