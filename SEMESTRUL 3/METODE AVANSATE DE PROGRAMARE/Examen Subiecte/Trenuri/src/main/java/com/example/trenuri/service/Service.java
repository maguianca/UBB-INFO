package com.example.trenuri.service;

import com.example.trenuri.domeniu.City;
import com.example.trenuri.domeniu.Client;
import com.example.trenuri.domeniu.TrainStation;
import com.example.trenuri.events.ChangeEventType;
import com.example.trenuri.events.UtilizatorEntityChangeEvent;
import com.example.trenuri.observer.Observable;
import com.example.trenuri.observer.Observer;
import com.example.trenuri.repository.DBCity;
import com.example.trenuri.repository.DBTrainStation;

import java.util.*;
import java.util.stream.Collectors;
import java.util.stream.Stream;
import java.util.*;
import java.util.stream.Collectors;
import java.util.stream.Stream;

public class Service implements Observable<UtilizatorEntityChangeEvent> {
    private final DBCity cityRepo;
    private final DBTrainStation trainStationRepo;

    private final List<Observer<UtilizatorEntityChangeEvent>> observers = new ArrayList<>();

    private final Map<Integer, Client> activeClients = new HashMap<>();

    public Service(DBCity cityRepo, DBTrainStation trainStationRepo) {
        this.cityRepo = cityRepo;
        this.trainStationRepo = trainStationRepo;
    }

    // Implementare Observer
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

    public void removeActiveClient(int id) {
        activeClients.remove(id);
        notifyObservers(new UtilizatorEntityChangeEvent(ChangeEventType.DELETE, null, null));
    }
    public void addActiveClient(int id,Client client){
        activeClients.put(id, client);
        notifyObservers(new UtilizatorEntityChangeEvent(ChangeEventType.ADD, null, null));
    }

    public int getActiveUsers(int id) {
        Client currentClient = activeClients.get(id);
        if (currentClient == null) {
            return 0;
        }
        return (int) activeClients.entrySet().stream()
                .filter(entry -> !entry.getKey().equals(id))
                .map(Map.Entry::getValue)
                .filter(client -> client.equals(currentClient))
                .count();
    }

    public List<City> getAllCities() {
        Iterable<City> iterable = cityRepo.findAll();
        List<City> list = new ArrayList<>();
        iterable.forEach(list::add);
        return list;
    }

    public List<TrainStation> getAllTrainStations() {
        Iterable<TrainStation> iterable = trainStationRepo.findAll();
        List<TrainStation> list = new ArrayList<>();
        iterable.forEach(list::add);
        return list;
    }

    public City findCityById(String id) {
        return cityRepo.findOne(id).orElse(null);
    }

    public List<String> findRoutesSimple(int id_fereastra, String departureCity, String destinationCity, boolean directRoutesOnly) {
        notifyObservers(new UtilizatorEntityChangeEvent(ChangeEventType.ADD, null, null));
        Client client = new Client(id_fereastra, departureCity, destinationCity);
        addActiveClient(id_fereastra, client);

        List<TrainStation> trainStations = getAllTrainStations();
        Map<String, String> cityIdToName = trainStations.stream()
                .flatMap(station -> Stream.of(station.getDepartureCityId(), station.getDestinationCityId()))
                .distinct()
                .collect(Collectors.toMap(id -> id, id -> findCityById(id).getName()));

        List<String> routes = new ArrayList<>();

        if (directRoutesOnly) {
            for (TrainStation station : trainStations) {
                if (cityIdToName.get(station.getDepartureCityId()).equals(departureCity) &&
                        cityIdToName.get(station.getDestinationCityId()).equals(destinationCity)) {
                    double price = 10.0;
                    routes.add(departureCity + "-" + station.getid() + "->" + destinationCity + ", price: " + price);
                }
            }
        } else {
            Set<String> visitedCities = new HashSet<>();
            backtrack(departureCity, destinationCity, trainStations, cityIdToName, new ArrayList<>(), visitedCities, routes);
        }

        return routes;
    }

    private void backtrack(String currentCity, String destinationCity, List<TrainStation> trainStations,
                           Map<String, String> cityIdToName, List<String> currentRoute, Set<String> visitedCities, List<String> routes) {
        if (currentCity.equals(destinationCity)) {
            String routeString = String.join("->", currentRoute) + "->" + destinationCity;
            double price = 10.0 * currentRoute.size();
            routes.add(routeString + ", price: " + price);
            return;
        }

        visitedCities.add(currentCity);

        for (TrainStation station : trainStations) {
            if (cityIdToName.get(station.getDepartureCityId()).equals(currentCity) && !visitedCities.contains(cityIdToName.get(station.getDestinationCityId()))) {
                currentRoute.add(currentCity + "-" + station.getid());
                backtrack(cityIdToName.get(station.getDestinationCityId()), destinationCity, trainStations, cityIdToName, currentRoute, visitedCities, routes);
                currentRoute.remove(currentRoute.size() - 1);
            }
        }

        visitedCities.remove(currentCity);
    }



}
