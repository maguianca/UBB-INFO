package ro.mpp2025.Repository;

import ro.mpp2025.Domain.Spectacol;

import java.time.LocalDateTime;

public interface ISpectacolRepo extends IRepo<Integer, Spectacol> {
    Iterable<Spectacol> getBetweenDates(LocalDateTime start, LocalDateTime end) throws EntityRepoException;
}
