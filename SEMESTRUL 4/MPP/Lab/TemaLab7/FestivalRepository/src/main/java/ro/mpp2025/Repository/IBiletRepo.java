package ro.mpp2025.Repository;

import ro.mpp2025.Domain.Bilet;
import ro.mpp2025.Domain.Spectacol;

public interface IBiletRepo extends IRepo<Integer, Bilet> {
    Iterable<Bilet> getBySpectacol(Spectacol spectacol) throws EntityRepoException;
}
