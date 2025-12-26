package ro.mpp2025.Service;

import ro.mpp2025.Domain.Bilet;
import ro.mpp2025.Domain.Spectacol;
import ro.mpp2025.Repository.EntityRepoException;

public interface IBiletService extends IService<Integer, Bilet> {
    Iterable<Bilet> getBySpectacol(Spectacol spectacol) throws EntityRepoException;
}
