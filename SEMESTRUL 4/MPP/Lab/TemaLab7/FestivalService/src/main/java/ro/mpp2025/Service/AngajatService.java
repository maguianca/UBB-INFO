package ro.mpp2025.Service;

import ro.mpp2025.Domain.Angajat;
import ro.mpp2025.Repository.EntityRepoException;
import ro.mpp2025.Repository.IAngajatRepo;

public class AngajatService extends AbstractService<Integer, Angajat, IAngajatRepo>
    implements IAngajatService {
    public AngajatService(IAngajatRepo repo) {
        super(repo);
    }

    @Override
    public void register(Angajat angajat) throws EntityRepoException {
        var username = angajat.getUsername();
        var password = angajat.getPassword();
        var email = angajat.getEmail();
        add(new Angajat(username, password, email));
    }

    @Override
    public Angajat login(String username, String password) throws EntityRepoException {
        return getRepo().findByCredentials(username, password);
    }
}
