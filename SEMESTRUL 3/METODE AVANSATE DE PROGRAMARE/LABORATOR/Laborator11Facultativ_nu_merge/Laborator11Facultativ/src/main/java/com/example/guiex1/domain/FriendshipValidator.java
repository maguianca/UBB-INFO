package com.example.guiex1.domain;

import java.util.Optional;
import com.example.guiex1.repository.*;

public class FriendshipValidator implements Validator<Friendship> {

    private Repository<Long, Utilizator> repo;

    public FriendshipValidator(Repository<Long,Utilizator>repo) {
        this.repo = repo;
    }

    @Override
    public void validate(Friendship entity) throws ValidationException {

        Optional<Utilizator> u1 = repo.findOne(entity.getIdUser1());
        Optional<Utilizator> u2 = repo.findOne(entity.getIdUser2());

        if (entity.getIdUser1() == null || entity.getIdUser2() == null)
            throw new ValidationException("The id can't be null! ");
        if (u1.isEmpty() || u2.isEmpty())
            throw new ValidationException("The id doesn't exist! ");
    }
}