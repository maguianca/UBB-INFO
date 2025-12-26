package com.example.zboruri2.service;

import com.example.zboruri2.domeniu.Client;
import com.example.zboruri2.domeniu.Flight;
import com.example.zboruri2.domeniu.Ticket;
import com.example.zboruri2.events.ChangeEventType;
import com.example.zboruri2.events.UtilizatorEntityChangeEvent;
import com.example.zboruri2.observer.Observable;
import com.example.zboruri2.observer.Observer;
import com.example.zboruri2.paging.Page;
import com.example.zboruri2.paging.Pageable;
import com.example.zboruri2.repository.DBRepoClient;
import com.example.zboruri2.repository.DBRepoFlight;
import com.example.zboruri2.repository.DBRepoTicket;

import java.time.LocalDate;
import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.List;
import java.util.Optional;
import java.util.stream.Collectors;
import java.util.stream.StreamSupport;

public class Service implements Observable<UtilizatorEntityChangeEvent> {
    DBRepoClient repoClient;
    DBRepoFlight repoFlight;
    DBRepoTicket repoTicket;
    public Service(DBRepoClient repoClient, DBRepoFlight repoFlight, DBRepoTicket repoTicket) {
        this.repoClient = repoClient;
        this.repoFlight = repoFlight;
        this.repoTicket = repoTicket;
    }
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
    public Client findClient(String username) {
        return repoClient.findOne(username).orElse(null);
    }
    public List<Ticket> getAllTicketsClient(String username){
        return StreamSupport.stream(repoTicket.findAllTicketClient(username).spliterator(), false)
                .collect(Collectors.toList());
    }
    public List<Ticket>getAllTicketsClient24(String username) {
        return StreamSupport.stream(repoTicket.findAllTicketClient(username).spliterator(), false)
                .filter(ticket -> ticket.getPurchaseTime().toLocalDate().equals(LocalDate.of(2024, 1, 24)))
                .collect(Collectors.toList());
    }
    public List<Flight> getAllFlights(){
        return StreamSupport.stream(repoFlight.findAll().spliterator(), false)
                .collect(Collectors.toList());
    }
    public List<Flight>getAllFlightsFiltered(String from, String to,LocalDate date){
        return StreamSupport.stream(repoFlight.findAll().spliterator(), false)
                .filter(flight -> flight.getFrom().equals(from) && flight.getTo().equals(to)
                && flight.getDepartureTime().toLocalDate().equals(date))
                .collect(Collectors.toList());
    }
    public List<String>getAllLocationsFrom(){
        return StreamSupport.stream(repoFlight.findAll().spliterator(), false)
                .map(Flight::getFrom)
                .distinct()
                .collect(Collectors.toList());
    }
    public List<String>getAllLocationsTo(){
        return StreamSupport.stream(repoFlight.findAll().spliterator(), false)
                .map(Flight::getTo)
                .distinct()
                .collect(Collectors.toList());
    }
    public void saveTicket(Ticket t){
        repoTicket.save(t);
        notifyObservers(new UtilizatorEntityChangeEvent(ChangeEventType.ADD, null, null));
    }
    public int getAvailableSeats(Flight f) {
        long ticketCount = StreamSupport.stream(repoTicket.findAllTicket(f.getId()).spliterator(), false)
                .count();
        return f.getSeats() - (int) ticketCount;
    }
    public Page<Flight> getPageFlightsId(LocalDate departuretime, String from, String to, Pageable pageable){
        System.out.println("service"+departuretime+" "+from+" "+to);
        Page<Long> page = repoFlight.getPagedFlightsId(departuretime,from,to,pageable);
        List<Flight> personList = new ArrayList<>();

        for(Long ID: page.getElementsOnPage()){
            Optional<Flight> user = repoFlight.findOne(ID);
            user.ifPresent(personList::add);
            System.out.println(user);
        }
        return new Page<>(page.getTotalNumberElements(),personList);
    }


}
