package com.example.taximetrie2.service;

import com.example.taximetrie2.domeniu.*;
import com.example.taximetrie2.events.ChangeEventType;
import com.example.taximetrie2.events.UtilizatorEntityChangeEvent;
import com.example.taximetrie2.observer.Observable;
import com.example.taximetrie2.observer.Observer;
import com.example.taximetrie2.paging.Page;
import com.example.taximetrie2.paging.Pageable;
import com.example.taximetrie2.repository.*;

import java.time.LocalDate;
import java.util.*;
import java.util.stream.Collectors;
import java.util.stream.StreamSupport;

public class Service implements Observable<UtilizatorEntityChangeEvent> {
    DBRepoComanda dbRepoComanda;
    DBRepoSofer dbRepoSofer;
    DBRepoPersoana dbRepoPersoana;
    DBRepoCerere dbRepoCerere;
    DBRepoOferta dbRepoOferta;
    private List<Observer<UtilizatorEntityChangeEvent>> observers=new ArrayList<>();
    public Service(DBRepoPersoana dbRepoPersoana,DBRepoSofer dbRepoSofer,DBRepoComanda dbRepoComanda,DBRepoCerere dbRepoCerere,DBRepoOferta dbRepoOferta){
        this.dbRepoComanda=dbRepoComanda;
        this.dbRepoSofer=dbRepoSofer;
        this.dbRepoPersoana=dbRepoPersoana;
        this.dbRepoOferta=dbRepoOferta;
        this.dbRepoCerere=dbRepoCerere;
    }
    public Persoana findPersoana(String id){
        return dbRepoPersoana.findOne(id).orElse(null);
    }
    public Sofer findSofer(String id){
        return dbRepoSofer.findOne(id).orElse(null);
    }
    public Persoana getPersoanaId(Long id){
        return dbRepoPersoana.findOneId(id).orElse(null);
    }
    public Sofer getSoferId(Long id){
        return dbRepoSofer.findOneId(id).orElse(null);
    }
    @Override
    public void addObserver(Observer<UtilizatorEntityChangeEvent> e) {
        observers.add(e);
    }
    public void save_cerere(Cerere cerere) {
        dbRepoCerere.save(cerere);
        notifyObservers(new UtilizatorEntityChangeEvent(ChangeEventType.ADD,null));
    }
    public void save_oferta(Oferta oferta) {
        dbRepoOferta.save(oferta);
        notifyObservers(new UtilizatorEntityChangeEvent(ChangeEventType.ADD,null));
    }
    public void delete_oferta(Long id){
        dbRepoOferta.delete(id);
        notifyObservers(new UtilizatorEntityChangeEvent(ChangeEventType.DELETE,null));
    }
    public void delete_cerere(Long id){
        dbRepoCerere.delete(id);
        notifyObservers(new UtilizatorEntityChangeEvent(ChangeEventType.DELETE,null));
    }

    @Override
    public void removeObserver(Observer<UtilizatorEntityChangeEvent> e) {

    }
    public void saveComanda(Comanda comanda){
        dbRepoComanda.save(comanda);
        notifyObservers(new UtilizatorEntityChangeEvent(ChangeEventType.ADD,null));
    }
    @Override
    public void notifyObservers(UtilizatorEntityChangeEvent t) {
        observers.stream().forEach(x->x.update(t));
    }
    public List<Oferta>getAllOferteId(Long id){
        List<Oferta> allOferte = StreamSupport.stream(dbRepoOferta.findAll().spliterator(), false)
                .filter(oferta -> oferta.getId_client().equals(id))
                .collect(Collectors.toList());
        allOferte.forEach(oferta -> System.out.println("Oferta ID: " + oferta.getId()));
        return allOferte;
    }
    public List<Cerere>getAllCerere(){
        List<Cerere> allCerere = StreamSupport.stream(dbRepoCerere.findAll().spliterator(), false)
                .collect(Collectors.toList());
        allCerere.forEach(cerere -> System.out.println(cerere.getAdresa()));
        return allCerere;
    }
    public Page<Persoana> getPagedPersoaneForSoferID(Long userID, Pageable pageable){

        Page<Long> page = dbRepoComanda.getPagedPersoaneForSoferID(userID,pageable);
        List<Persoana> personList = new ArrayList<>();

        for(Long ID: page.getElementsOnPage()){
            Optional<Persoana> user = dbRepoPersoana.findOneId(ID);
            user.ifPresent(personList::add);
        }
        return new Page<>(page.getTotalNumberElements(),personList);
    }
    public Iterable<Comanda> getComenziData(LocalDate data, Long idSofer) {
        return StreamSupport.stream(dbRepoComanda.findAll().spliterator(), false)
                .filter(comanda -> comanda.getData().toLocalDate().equals(data) && comanda.getTaximetrist().getId().equals(idSofer))
                .collect(Collectors.toList());
    }
    public Integer media_comenzi(LocalDate data, Long idSofer) {
        LocalDate threeMonthsAgo = data.minusMonths(3);
        List<Comanda> comenzi = StreamSupport.stream(dbRepoComanda.findAll().spliterator(), false)
                .filter(comanda -> !comanda.getData().toLocalDate().isBefore(threeMonthsAgo) && !comanda.getData().toLocalDate().isAfter(data) && comanda.getTaximetrist().getId().equals(idSofer))
                .collect(Collectors.toList());

        long daysBetween = java.time.temporal.ChronoUnit.DAYS.between(threeMonthsAgo, data) + 1; // +1 to include the end date
        return (int)(comenzi.size() / (double) daysBetween);
    }
    public String client_fidel(Long idSofer) {
        Map<Long, Integer> clienti = new HashMap<>();
        StreamSupport.stream(dbRepoComanda.findAll().spliterator(), false)
                .filter(comanda -> comanda.getTaximetrist().getId().equals(idSofer))
                .forEach(comanda -> {
                    Long idClient = comanda.getPersoana().getId();
                    if (clienti.containsKey(idClient)) {
                        clienti.put(idClient, clienti.get(idClient) + 1);
                    } else {
                        clienti.put(idClient, 1);
                    }
                });

        Long idClientFidel = Collections.max(clienti.entrySet(), Map.Entry.comparingByValue()).getKey();
        return dbRepoPersoana.findOneId(idClientFidel).get().getNume();
    }



}
