package com.example.trenuri.controller;

import com.example.trenuri.domeniu.City;
import com.example.trenuri.domeniu.TrainStation;
import com.example.trenuri.events.UtilizatorEntityChangeEvent;
import com.example.trenuri.observer.Observer;
import com.example.trenuri.service.Service;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.CheckBox;
import javafx.scene.control.ComboBox;
import javafx.scene.control.Label;
import javafx.scene.control.ListView;
import javafx.stage.Stage;

import java.util.List;
import java.util.stream.Collectors;

public class ClientController implements Observer<UtilizatorEntityChangeEvent> {

    @FXML
    private ComboBox<String> departure;
    @FXML
    private ComboBox<String> destination;
    @FXML
    private CheckBox direct;
    @FXML
    private ListView<String> tabel;

    private Service service;
    private Stage dialogStage;
    private int id;
    private int active_users;
    @FXML
    private Label label;

    public void setService(int id,Service service, Stage dialogStage) {
        this.id=id;
        this.service = service;
        this.dialogStage = dialogStage;
        initModel();
        this.service.addObserver(this);
        this.dialogStage.setOnCloseRequest(event -> {
            handleWindowClose();
        });
    }
    private void handleWindowClose() {
        System.out.println("Window with ID " + id + " is closing...");
        service.removeActiveClient(id);
        service.removeObserver(this);
    }
    private void initModel() {
        List<City> cities = service.getAllCities();
        ObservableList<String> cityNames = FXCollections.observableArrayList(
                cities.stream().map(City::getName).collect(Collectors.toList())
        );
        departure.setItems(cityNames);
        destination.setItems(cityNames);
    }

    public void update(UtilizatorEntityChangeEvent event) {
        active_users=service.getActiveUsers(id);
        label.setText(active_users+" other users are currently looking at the same route.");
    }

    @FXML
    private void initialize() {
        // Initialization code if needed
    }

    public void handleSearch(ActionEvent actionEvent) {
        String departureCity = departure.getValue();
        String destinationCity = destination.getValue();
        update(null);
        boolean directRoutesOnly = direct.isSelected();

        if (departureCity == null || destinationCity == null) {
            System.out.println("Please select both departure and destination cities.");
            return;
        }
        List<String> routes = service.findRoutesSimple(id,departureCity, destinationCity, directRoutesOnly);

        if (routes.isEmpty()) {
            tabel.setItems(null);
            System.out.println("No routes found.");
        } else {
            ObservableList<String> observableRoutes = FXCollections.observableArrayList(routes);
            tabel.setItems(observableRoutes);
        }
    }
}