package ro.mpp2025.Service;

import ro.mpp2025.Domain.Spectacol;
import ro.mpp2025.Repository.EntityRepoException;

import java.time.LocalDateTime;

public interface ISpectacolService extends IService<Integer, Spectacol> {
    Iterable<Spectacol> getBetweenDates(LocalDateTime start, LocalDateTime end) throws EntityRepoException;
}
