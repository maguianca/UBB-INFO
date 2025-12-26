package com.example.comenzirestaurant.service;

import com.example.comenzirestaurant.domeniu.Angajat;
import com.example.comenzirestaurant.domeniu.Order;

import java.util.*;
import com.example.comenzirestaurant.domeniu.*;
import com.example.comenzirestaurant.events.UtilizatorEntityChangeEvent;
import com.example.comenzirestaurant.observer.Observable;
import com.example.comenzirestaurant.observer.Observer;
import com.example.comenzirestaurant.events.ChangeEventType;
import com.example.comenzirestaurant.repository.Repository;

import java.util.stream.Collectors;
import java.util.stream.StreamSupport;

public class Service implements Observable<UtilizatorEntityChangeEvent> {
    private Repository<Long, Angajat> repoAngajat;
    private List<Observer<UtilizatorEntityChangeEvent>> observers=new ArrayList<>();
    private Repository<Long, Order> repoOrder;
    private Repository<Long, MenuItem> repoMenuItem;
    private Repository<Long,Table>repoTable;
    public Service(Repository<Long,Angajat>repoAngajat,Repository<Long,MenuItem>repoMenuItem,Repository<Long,Table>repoTable,Repository<Long,Order>repoOrder) {
        this.repoAngajat = repoAngajat;
        this.repoOrder = repoOrder;
        this.repoMenuItem = repoMenuItem;
        this.repoTable=repoTable;
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
        observers.stream().forEach(x -> x.update(t));
    }
    public Iterable<Angajat>getAngajati(){
        return repoAngajat.findAll();
    }
    public Iterable<MenuItem>getMenuItems(){
        return repoMenuItem.findAll();
    }
    public Iterable<Table>getTables(){
        return repoTable.findAll();
    }
    public Map<String, List<MenuItem>> getMenuGroupedByCategory() {
        Map<String, List<MenuItem>> result = new HashMap<>();
        for (MenuItem menuItem : repoMenuItem.findAll()) {
            result.computeIfAbsent(menuItem.getCategorie(), k -> new ArrayList<>()).add(menuItem);
        }
        return result;
    }

    public void saveOrder(Order order) {
        repoOrder.save(order);
        notifyObservers(new UtilizatorEntityChangeEvent(ChangeEventType.ADD, order));
    }
    public List<Order> getOrders() {
        return StreamSupport.stream(repoOrder.findAll().spliterator(), false)
                .sorted(Comparator.comparing(Order::getDate))
                .filter(x->x.getStatus().equals(Order.Status.PLACED))
                .peek(x->System.out.println(x))
                .collect(Collectors.toList());
    }
    public List<Order> getOrdersPrepering() {
        return StreamSupport.stream(repoOrder.findAll().spliterator(), false)
                .sorted(Comparator.comparing(Order::getDate))
                .filter(x->x.getStatus().equals(Order.Status.PREPARING))
                .peek(x->System.out.println(x))
                .collect(Collectors.toList());
    }

    public MenuItem MenufindOne(Long id) {
        return repoMenuItem.findOne(id).orElse(null);
    }

    public void updateOrder(Order Entity){
        repoOrder.update(Entity);
        notifyObservers(new UtilizatorEntityChangeEvent(ChangeEventType.UPDATE, null,null));
    }

    public Order.Status getStatusOrder(Long id) {
        return StreamSupport.stream(repoOrder.findAll().spliterator(), false)
                .filter(order -> order.getTableId().equals(id))
                .sorted(Comparator.comparing(Order::getDate).reversed())
                .map(Order::getStatus)
                .findFirst()
                .orElse(Order.Status.NONE);
    }
}


