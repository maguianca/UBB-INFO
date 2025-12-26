package com.example.examen.service;

import com.example.examen.domeniu.AdoptionCentre;
import com.example.examen.domeniu.Animal;
import com.example.examen.domeniu.Notificare;
import com.example.examen.events.ChangeEventType;
import com.example.examen.events.UtilizatorEntityChangeEvent;
import com.example.examen.observer.Observable;
import com.example.examen.observer.Observer;
import com.example.examen.repository.DBRepoAdoptionCentre;
import com.example.examen.repository.DBRepoAnimal;
import com.example.examen.repository.DBRepoNotificare;

import java.util.ArrayList;
import java.util.List;
import java.util.stream.Collectors;
import java.util.stream.StreamSupport;

public class Service implements Observable<UtilizatorEntityChangeEvent> {
    DBRepoAdoptionCentre dbRepoAdoptionCentre;
    DBRepoAnimal dbRepoAnimal;
    DBRepoNotificare dbRepoNotificare;
    private final List<Observer<UtilizatorEntityChangeEvent>> observers = new ArrayList<>();

    @Override
    public void addObserver(Observer<UtilizatorEntityChangeEvent> e) {
        observers.add(e);
    }

    @Override
    public void removeObserver(Observer<UtilizatorEntityChangeEvent> e) {
        observers.remove(e);
    }

    @Override
    public void notifyObservers(UtilizatorEntityChangeEvent t) {
        observers.forEach(x -> x.update(t));
    }

    public Service(DBRepoAdoptionCentre dbRepoAdoptionCentre, DBRepoAnimal dbRepoAnimal, DBRepoNotificare dbRepoNotificare) {
        this.dbRepoAdoptionCentre = dbRepoAdoptionCentre;
        this.dbRepoAnimal = dbRepoAnimal;
        this.dbRepoNotificare = dbRepoNotificare;
    }

    public List<Animal> getAllAnimale(Integer id) {
            Iterable<Animal> animale = dbRepoAnimal.findAll(id);
            return StreamSupport.stream(animale.spliterator(), false)
                    .collect(Collectors.toList());
    }

    public List<AdoptionCentre> getAllCentre() {
        Iterable<AdoptionCentre> centre = dbRepoAdoptionCentre.findAll();
        return StreamSupport.stream(centre.spliterator(), false)
                .collect(Collectors.toList());
    }

    public Integer getProcent(Integer id) {
        Iterable<Animal> animale = dbRepoAnimal.findAll(id);
        return (int) StreamSupport.stream(animale.spliterator(), false)
                .count() * 100;
    }

    public List<Animal> filtreaza_tip(Integer id, String tip) {
        Iterable<Animal> animale = dbRepoAnimal.find_filtrare(id, tip);
        return StreamSupport.stream(animale.spliterator(), false)
                .collect(Collectors.toList());
    }

    public void saveNotificare(Notificare notif) {
        dbRepoNotificare.save(notif);
        notifyObservers(new UtilizatorEntityChangeEvent(ChangeEventType.ADD, null, notif));
    }

    public void deleteNotificare(Integer id) {
        dbRepoNotificare.delete(id);
        notifyObservers(new UtilizatorEntityChangeEvent(ChangeEventType.ADD, null, null));
    }
    public List<Notificare> getAllFiltered(Integer id) {
        String locatie = dbRepoAdoptionCentre.findOne(id).orElseThrow(() -> new RuntimeException("Adoption Centre not found")).getLocation();
        System.out.println(locatie + " " + id);
        Iterable<Notificare> not = dbRepoNotificare.findAll(id, locatie);
        return StreamSupport.stream(not.spliterator(), false)
                .filter(notificare -> !notificare.getCentruid().equals(id))
                .peek(x -> System.out.println(x))
                .collect(Collectors.toList());
    }
    public void updateanimal(Integer idvechi,Integer idnou){
        dbRepoAnimal.updateCentreId(idvechi,idnou);
        notifyObservers(new UtilizatorEntityChangeEvent(ChangeEventType.ADD, null, null));
    }
    public Animal findAnimal(Integer id){
        return dbRepoAnimal.findOne(id).orElse(null);
    }
    public AdoptionCentre findCentru(Integer id){
        return dbRepoAdoptionCentre.findOne(id).orElse(null);
    }
}