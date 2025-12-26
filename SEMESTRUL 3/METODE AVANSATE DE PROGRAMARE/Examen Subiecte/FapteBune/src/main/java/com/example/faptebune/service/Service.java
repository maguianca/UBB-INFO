package com.example.faptebune.service;
import com.example.faptebune.events.ChangeEventType;
import com.example.faptebune.events.UtilizatorEntityChangeEvent;
import com.example.faptebune.observer.Observable;
import com.example.faptebune.observer.Observer;
import com.example.faptebune.repository.RepoNevoie;
import com.example.faptebune.repository.RepoPersoana;
import com.example.faptebune.domeniu.*;

import java.util.ArrayList;
import java.util.List;
import java.util.stream.Collectors;
import java.util.stream.StreamSupport;

public class Service implements Observable<UtilizatorEntityChangeEvent> {
    private List<Observer<UtilizatorEntityChangeEvent>> observers=new ArrayList<>();
    RepoPersoana repoPersoana=new RepoPersoana();
    RepoNevoie repoNevoie=new RepoNevoie(repoPersoana);
    public Service(RepoPersoana repopersoana,RepoNevoie reponevoie){
        this.repoPersoana=repopersoana;
        this.repoNevoie=reponevoie;
    }
    public void savePersoana(Persoana p){
        repoPersoana.save(p);
        notifyObservers(new UtilizatorEntityChangeEvent(ChangeEventType.ADD, null, p));
    }
    public List<Persoana> getAllPersoane() {
        Iterable<Persoana> iterable = repoPersoana.findAll();
        return StreamSupport.stream(iterable.spliterator(), false)
                .collect(Collectors.toList());
    }
    public List<Nevoie> getAllNevoi() {
        Iterable<Nevoie> iterable = repoNevoie.findAll();
        return StreamSupport.stream(iterable.spliterator(), false)
                .collect(Collectors.toList());
    }
   /* public List<Nevoie>getAllNevoiId(Long id){
        Iterable<Nevoie> iterable = repoNevoie.findAll();
        return StreamSupport.stream(iterable.spliterator(), false)
                .filter(nevoie -> !nevoie.getOmInNevoie().equals(id)
                && findPersoana(nevoie.getOmInNevoie()).getOras().equals(findPersoana(id).getOras()))
                .collect(Collectors.toList());
    }*/
    public void saveNevoie(Nevoie n){
        System.out.println(n);
        repoNevoie.save(n);
        notifyObservers(new UtilizatorEntityChangeEvent(ChangeEventType.ADD, null, null));
    }
    public void updateNevoie(Long id1,Long id2){
        repoNevoie.update(id1,id2);
        notifyObservers(new UtilizatorEntityChangeEvent(ChangeEventType.UPDATE, null, null));
    }
    public Persoana findPersoana(Long id){
        return repoPersoana.findOne(id).orElse(null);
    }
    public List<Nevoie> getAllNevoiId(Long id) {
        if (id == null) {
            throw new IllegalArgumentException("Id-ul nu poate fi null.");
        }

        System.out.println("Fetching all Nevoi...");
        Iterable<Nevoie> iterable = repoNevoie.findAll();

        List<Nevoie> result = StreamSupport.stream(iterable.spliterator(), false)
                .filter(nevoie -> {
                    System.out.println("Filtering nevoie: " + nevoie);
                    return nevoie.getOmSalvator() != null && nevoie.getOmSalvator().longValue() == id.longValue();
                })
                .collect(Collectors.toList());

        System.out.println("Filtered Nevoi: " + result);
        return result;
    }

    @Override
    public void addObserver(Observer<UtilizatorEntityChangeEvent> e) {
        observers.add(e);
    }

    @Override
    public void removeObserver(Observer<UtilizatorEntityChangeEvent> e) {

    }

    @Override
    public void notifyObservers(UtilizatorEntityChangeEvent t) {
        observers.stream().forEach(x->x.update(t));
    }



}
