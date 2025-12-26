package com.example.taximetrie.service;

import com.example.taximetrie.domeniu.*;
import com.example.taximetrie.events.ChangeEventType;
import com.example.taximetrie.events.UtilizatorEntityChangeEvent;
import com.example.taximetrie.observer.Observable;
import com.example.taximetrie.observer.Observer;
import com.example.taximetrie.paging.Page;
import com.example.taximetrie.paging.Pageable;
import com.example.taximetrie.repository.PagingComenzi;
import com.example.taximetrie.repository.Repository;

import java.time.LocalDate;
import java.time.LocalDateTime;
import java.util.*;
import java.util.stream.Collectors;
import java.util.stream.StreamSupport;

public class Service implements Observable<UtilizatorEntityChangeEvent> {
    private Repository<Long, Persoana> repoPersoana;
    private Repository<Long, Sofer>repoSofer;
    private PagingComenzi<Long, Comanda> repoComanda;
    private Repository<Long, Cerere> repoCerere;
    private Repository<Long, Oferta> repoOferta;
    private List<Observer<UtilizatorEntityChangeEvent>>observers=new ArrayList<>();
    public Service(Repository<Long,Persoana>repoPersoana,Repository<Long,Sofer>repoSofer,PagingComenzi<Long,Comanda>repoComanda,Repository<Long,Cerere>repoCerere,Repository<Long,Oferta>repoOferta) {
        this.repoPersoana = repoPersoana;
        this.repoSofer = repoSofer;
        this.repoComanda = repoComanda;
        this.repoCerere = repoCerere;
        this.repoOferta = repoOferta;

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
    public Iterable<Persoana>getPersoane(){
        return repoPersoana.findAll();
    }
    public Iterable<Sofer>getSofer(){
        return repoSofer.findAll();
    }
    public Iterable<Comanda>getComanda(){
        return repoComanda.findAll();
    }
    public Persoana getPersoana(Long id){
        return repoPersoana.findOne(id).orElse(null);
    }
    public Sofer getSofer(Long id){
        return repoSofer.findOne(id).orElse(null);
    }
    public Comanda findComanda(Long id){
        return repoComanda.findOne(id).orElse(null);
    }
    public void saveComanda(Comanda comanda){
        repoComanda.save(comanda);
        notifyObservers(new UtilizatorEntityChangeEvent(ChangeEventType.ADD,null));
    }
    public Persoana findPersoana(String username) {

        return StreamSupport.stream(repoPersoana.findAll().spliterator(), false)
                .filter(p -> p.getUsername().equals(username))
                .findFirst()
                .orElse(null);
    }
    public Sofer findSofer(String username) {

        return StreamSupport.stream(repoSofer.findAll().spliterator(), false)
                .filter(p -> p.getUsername().equals(username))
                .findFirst()
                .orElse(null);
    }
    public void save_cerere(Cerere cerere) {
        repoCerere.save(cerere);
        notifyObservers(new UtilizatorEntityChangeEvent(ChangeEventType.ADD,null));
    }
    public void save_oferta(Oferta oferta) {
        repoOferta.save(oferta);
        notifyObservers(new UtilizatorEntityChangeEvent(ChangeEventType.ADD,null));
    }
    public Iterable<Cerere>getCerere(){
        return repoCerere.findAll();
    }
    public Iterable<Oferta>getOferta(){
        return repoOferta.findAll();
    }
    public Oferta findOferta(Long id){
        return repoOferta.findOne(id).orElse(null);
    }
    public Cerere findCerere(Long id){
        return repoCerere.findOne(id).orElse(null);
    }
    public void delete_oferta(Long id){
        repoOferta.delete(id);
        notifyObservers(new UtilizatorEntityChangeEvent(ChangeEventType.DELETE,null));
    }
    public void delete_cerere(Long id){
        repoCerere.delete(id);
        notifyObservers(new UtilizatorEntityChangeEvent(ChangeEventType.DELETE,null));
    }


    public void delete_cerere_id(Long id_client) {

        Iterable<Cerere> cereriFiltrate = StreamSupport.stream(repoCerere.findAll().spliterator(), false)
                .filter(cerere -> cerere.getId_client().equals(id_client))
                .collect(Collectors.toList());

        if (!((List<Cerere>) cereriFiltrate).isEmpty()) {
            Cerere cerereDeSters = ((List<Cerere>) cereriFiltrate).get(0);
            System.out.println("Ștergerea cererii cu ID-ul: " + cerereDeSters.getId());
            delete_cerere(cerereDeSters.getId());
        } else {
            System.out.println("Nu s-au găsit cereri pentru clientul cu ID-ul: " + id_client);
        }
        //notifyObservers(new UtilizatorEntityChangeEvent(ChangeEventType.DELETE,null));
    }
    public Page<Persoana> getPagedPersoaneForSoferID(Long userID, Pageable pageable){

        Page<Long> page = repoComanda.getPagedPersoaneForSoferID(userID,pageable);
        List<Persoana> personList = new ArrayList<>();

        for(Long ID: page.getElementsOnPage()){
            Optional<Persoana> user = repoPersoana.findOne(ID);
            user.ifPresent(personList::add);
        }
        return new Page<>(page.getTotalNumberElements(),personList);
    }
    public Iterable<Comanda> getComenziData(LocalDate data, Long idSofer) {
        return StreamSupport.stream(repoComanda.findAll().spliterator(), false)
                .filter(comanda -> comanda.getData().toLocalDate().equals(data) && comanda.getTaximetrist().getId().equals(idSofer))
                .collect(Collectors.toList());
    }
    public Integer media_comenzi(LocalDate data, Long idSofer) {
        LocalDate threeMonthsAgo = data.minusMonths(3);
        List<Comanda> comenzi = StreamSupport.stream(repoComanda.findAll().spliterator(), false)
                .filter(comanda -> !comanda.getData().toLocalDate().isBefore(threeMonthsAgo) && !comanda.getData().toLocalDate().isAfter(data) && comanda.getTaximetrist().getId().equals(idSofer))
                .collect(Collectors.toList());

        long daysBetween = java.time.temporal.ChronoUnit.DAYS.between(threeMonthsAgo, data) + 1; // +1 to include the end date
        return (int)(comenzi.size() / (double) daysBetween);
    }
    public String client_fidel(Long idSofer) {
        Map<Long, Integer> clienti = new HashMap<>();
        StreamSupport.stream(repoComanda.findAll().spliterator(), false)
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
        return repoPersoana.findOne(idClientFidel).get().getNume();
    }
}