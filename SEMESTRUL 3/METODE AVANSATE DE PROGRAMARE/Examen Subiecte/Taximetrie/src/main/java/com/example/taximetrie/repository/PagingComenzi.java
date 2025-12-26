package com.example.taximetrie.repository;

import com.example.taximetrie.repository.Repository;
import com.example.taximetrie.paging.Pageable;
import com.example.taximetrie.paging.Page;
import com.example.taximetrie.domeniu.Entity;
public interface PagingComenzi<ID, E extends Entity<ID>> extends Repository<ID, E> {
    Page<ID> getPagedPersoaneForSoferID(ID id, Pageable pageable);
}
