package com.example.guiex1.repository.dbrepo;

import com.example.guiex1.repository.Repository;
import com.example.guiex1.utils.paging.Pageable;
import com.example.guiex1.utils.paging.Page;
import com.example.guiex1.domain.Entity;
public interface PagingFriendship<ID, E extends Entity<ID>> extends Repository<ID, E> {
    Page<ID> getPagedFriendsForUserID(ID id, Pageable pageable);
}
