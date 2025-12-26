package ro.mpp2025.Service;

import ro.mpp2025.Domain.Entity;
import ro.mpp2025.Repository.EntityRepoException;

public interface IService<ID, E extends Entity<ID>> {
    void add(E e) throws EntityRepoException;
    void update(E e) throws EntityRepoException;
    void remove(ID id) throws EntityRepoException;
    E getById(ID id) throws EntityRepoException;
    Iterable<E> getAll() throws EntityRepoException;
}
