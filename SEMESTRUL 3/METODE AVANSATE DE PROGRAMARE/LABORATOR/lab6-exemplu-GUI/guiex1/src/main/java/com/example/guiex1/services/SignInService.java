package com.example.guiex1.services;

import com.example.guiex1.domain.Utilizator;
import com.example.guiex1.repository.Repository;
import com.example.guiex1.repository.dbrepo.UtilizatorDbRepository;

import java.util.Optional;

public class SignInService {
    UtilizatorDbRepository userRepo;
    public SignInService(UtilizatorDbRepository userRepo){
        this.userRepo = userRepo;
    }

    public Optional<Utilizator> findOne(String firstName, String lastName, String password){
        return userRepo.findOne(firstName,lastName,password);
    }
}
