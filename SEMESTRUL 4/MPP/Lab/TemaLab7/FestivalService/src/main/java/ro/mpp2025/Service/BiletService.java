package ro.mpp2025.Service;

import ro.mpp2025.Domain.Bilet;
import ro.mpp2025.Domain.Spectacol;
import ro.mpp2025.Repository.EntityRepoException;
import ro.mpp2025.Repository.IBiletRepo;

public class BiletService extends AbstractService<Integer, Bilet, IBiletRepo>
    implements IBiletService {
    public BiletService(IBiletRepo repo) {
        super(repo);
    }

    @Override
    public Iterable<Bilet> getBySpectacol(Spectacol spectacol) throws EntityRepoException {
        return getRepo().getBySpectacol(spectacol);
    }
}
