package ro.mpp2025.Service;

import ro.mpp2025.Domain.Spectacol;
import ro.mpp2025.Repository.EntityRepoException;
import ro.mpp2025.Repository.ISpectacolRepo;

import java.time.LocalDateTime;

public class SpectacolService extends AbstractService<Integer, Spectacol, ISpectacolRepo>
    implements ISpectacolService {
    public SpectacolService(ISpectacolRepo repo) {
        super(repo);
    }

    @Override
    public Iterable<Spectacol> getBetweenDates(LocalDateTime start, LocalDateTime end) throws EntityRepoException {
        return getRepo().getBetweenDates(start, end);
    }
}
