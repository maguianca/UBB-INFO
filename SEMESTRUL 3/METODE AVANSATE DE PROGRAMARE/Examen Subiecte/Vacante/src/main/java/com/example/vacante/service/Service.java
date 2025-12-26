package com.example.vacante.service;

import com.example.vacante.domeniu.*;
import com.example.vacante.events.ChangeEventType;
import com.example.vacante.events.UtilizatorEntityChangeEvent;
import com.example.vacante.observer.Observable;
import com.example.vacante.observer.Observer;
import com.example.vacante.repository.DBClient;
import com.example.vacante.repository.DBHotel;
import com.example.vacante.repository.DBReservation;
import com.example.vacante.repository.DBSpecialOffer;

import java.time.LocalDate;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.stream.Collectors;
import java.util.stream.StreamSupport;

public class Service implements Observable<UtilizatorEntityChangeEvent> {
    DBClient dbClient;
    DBSpecialOffer dbSpecialOffer;
    DBHotel dbHotel;
    DBReservation dbReservation;
    private final List<Observer<UtilizatorEntityChangeEvent>> observers = new ArrayList<>();
    private final Map<Long, DTO> activeClients = new HashMap<>();
    public Service(DBClient dbClient, DBSpecialOffer dbSpecialOffer, DBHotel dbHotel, DBReservation dbReservation) {
        this.dbClient = dbClient;
        this.dbHotel = dbHotel;
        this.dbReservation = dbReservation;
        this.dbSpecialOffer = dbSpecialOffer;
    }

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

    public void removeActiveClient(Long id) {
        activeClients.remove(id);
        notifyObservers(new UtilizatorEntityChangeEvent(ChangeEventType.DELETE, null, null));
    }
    public void addActiveClient(Long id,DTO client){
        activeClients.put(id, client);
        notifyObservers(new UtilizatorEntityChangeEvent(ChangeEventType.ADD, null, null));
    }

    public int getActiveUsers(Long id) {
        DTO currentClient = activeClients.get(id);
        if (currentClient == null) {
            return 0;
        }
        return (int) activeClients.entrySet().stream()
                .filter(entry -> !entry.getKey().equals(id))
                .map(Map.Entry::getValue)
                .filter(client -> {
                    System.out.println(client);
                    return client.getLocatie().equals(currentClient.getLocatie()) &&
                            client.getData1().equals(currentClient.getData1()) &&
                            client.getData2().equals(currentClient.getData2()) &&
                            dbClient.findOne(client.getClientId()).map(Client::getHobbies).orElse(null)
                                    .equals(dbClient.findOne(currentClient.getClientId()).map(Client::getHobbies).orElse(null));
                })
                .count();
    }

    public Client findClient(Long id) {
        return dbClient.findOne(id).orElse(null);
    }

    public List<SpecialOffer> getAllOferteData(int fidelitygrade) {
        Iterable<SpecialOffer> oferte = dbSpecialOffer.findAllOffer();
        LocalDate now = LocalDate.now();
        return StreamSupport.stream(oferte.spliterator(), false)
                .filter(offer -> !offer.getStartDate().isBefore(now) && !offer.getEndDate().isBefore(now) && offer.getPercents() < fidelitygrade)
                .collect(Collectors.toList());
    }

    public Hotel findHotel(Double id) {
        return dbHotel.findOne(id).orElse(null);
    }

    public List<SpecialOffer> getAllOferteFilt(Long id,String locatie, LocalDate data1, LocalDate data2) {
        addActiveClient(id,new DTO(id,locatie,data1,data2));
        Iterable<SpecialOffer> oferte = dbSpecialOffer.findAllOffer();
        return StreamSupport.stream(oferte.spliterator(), false)
                .filter(offer -> offer.getStartDate().equals(data1) && offer.getEndDate().equals(data2) && findHotel(offer.getHotelId()).getLocationName().equals(locatie))
                .collect(Collectors.toList());
    }

    public List<String> findLocatii() {
        Iterable<Hotel> hotel = dbHotel.findAll();
        return StreamSupport.stream(hotel.spliterator(), false)
                .map(Hotel::getLocationName)
                .distinct()
                .collect(Collectors.toList());
    }
    public void saveRezervare(Reservation r){
        dbReservation.save(r);
    }
    public Double getLastReservationId(){
        return dbReservation.getLastReservationId()+1;
    }
    public int getRezervari(Double hotelId, LocalDate startDate, LocalDate endDate) {
        Iterable<Reservation> reservations = dbReservation.findAll();
        return (int) StreamSupport.stream(reservations.spliterator(), false)
                .filter(reservation -> reservation.getHotelId().equals(hotelId) &&
                        reservation.getStartDate().toLocalDate().isAfter(startDate.minusDays(1)) &&
                        !reservation.getStartDate().toLocalDate().plusDays(reservation.getNoNights()).isBefore(startDate))
                .peek(System.out::println)
                .count();
    }
    public int getGrad(Double hotelId, LocalDate x) {
        Iterable<Reservation> reservations = dbReservation.findAll();
        return (int) StreamSupport.stream(reservations.spliterator(), false)
                .filter(reservation -> reservation.getHotelId().equals(hotelId) &&
                        !x.isBefore(reservation.getStartDate().toLocalDate()) &&
                        !x.isAfter(reservation.getStartDate().toLocalDate().plusDays(reservation.getNoNights())))
                .peek(System.out::println)
                .count();
    }
}