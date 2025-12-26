package com.example.zboruri.controller;

import com.example.zboruri.domeniu.Client;
import com.example.zboruri.domeniu.Flight;
import com.example.zboruri.domeniu.Ticket;
import com.example.zboruri.events.UtilizatorEntityChangeEvent;
import com.example.zboruri.observer.Observer;
import com.example.zboruri.service.Service;
import javafx.application.Platform;
import javafx.beans.property.ReadOnlyObjectWrapper;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.ComboBox;
import javafx.scene.control.DatePicker;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.stage.Stage;

import java.time.LocalDate;
import java.time.LocalDateTime;

public class ClientController implements Observer<UtilizatorEntityChangeEvent> {
    private Service service;
    private Client client;
    private Stage dialogStage;
    @FXML
    private TableColumn<Ticket, String> flight;
    @FXML
    private TableColumn<Ticket, LocalDateTime> purchase;
    @FXML
    private TableColumn<Ticket, String> flight24;
    @FXML
    private TableColumn<Ticket, LocalDateTime> purchase24;
    @FXML
    private TableView<Ticket> table;
    @FXML
    private TableView<Ticket> table24;
    @FXML
    private TableView<Flight> tabelzbor;
    @FXML
    private TableColumn<Flight, String> from;
    @FXML
    private TableColumn<Flight, String> to;
    @FXML
    private TableColumn<Flight, LocalDateTime> departure;
    @FXML
    private TableColumn<Flight, LocalDateTime> landing;
    @FXML
    private TableColumn<Flight, Integer> seats;
    @FXML
    private ComboBox<String> frombox;
    @FXML
    private ComboBox<String> tobox;
    @FXML
    private DatePicker date;
    @FXML
    private TableColumn<Flight, Integer> disponibil;

    private ObservableList<Ticket> model = FXCollections.observableArrayList();
    private ObservableList<Ticket> model24 = FXCollections.observableArrayList();
    private ObservableList<Flight> modelzbor = FXCollections.observableArrayList();

    public void setService(Service service, Stage dialogStage, Client client) {
        this.service = service;
        this.dialogStage = dialogStage;
        this.client = client;
        initModel();
        this.service.addObserver(this);
    }

    public void initModel() {
        model.setAll(service.getAllTicketsClient(client.getUsername()));
        model24.setAll(service.getAllTicketsClient24(client.getUsername()));
        frombox.setItems(FXCollections.observableArrayList(service.getAllLocationsFrom()));
        tobox.setItems(FXCollections.observableArrayList(service.getAllLocationsTo()));
        filterFlights();
    }

    @Override
    public void update(UtilizatorEntityChangeEvent event) {
        initModel();
    }

    @FXML
    public void initialize() {
        flight.setCellValueFactory(new PropertyValueFactory<>("flightId"));
        purchase.setCellValueFactory(new PropertyValueFactory<>("purchaseTime"));
        flight24.setCellValueFactory(new PropertyValueFactory<>("flightId"));
        purchase24.setCellValueFactory(new PropertyValueFactory<>("purchaseTime"));
        from.setCellValueFactory(new PropertyValueFactory<>("from"));
        to.setCellValueFactory(new PropertyValueFactory<>("to"));
        departure.setCellValueFactory(new PropertyValueFactory<>("departureTime"));
        landing.setCellValueFactory(new PropertyValueFactory<>("landingTime"));
        seats.setCellValueFactory(new PropertyValueFactory<>("seats"));
        disponibil.setCellValueFactory(data -> {
            Flight flight = data.getValue();
            int availableSeats = service.getAvailableSeats(flight);
            return new ReadOnlyObjectWrapper<Integer>(availableSeats);
        });

        table.setItems(model);
        table24.setItems(model24);
        tabelzbor.setItems(modelzbor);

        frombox.valueProperty().addListener((obs, oldVal, newVal) -> filterFlights());
        tobox.valueProperty().addListener((obs, oldVal, newVal) -> filterFlights());
        date.valueProperty().addListener((obs, oldVal, newVal) -> filterFlights());
    }

    private void filterFlights() {
        String from = frombox.getValue();
        String to = tobox.getValue();
        LocalDate selectedDate = date.getValue();

        if (from != null && to != null && selectedDate != null) {
            modelzbor.setAll(service.getAllFlightsFiltered(from, to, selectedDate));
        } else {
            modelzbor.clear();
        }
    }

    public void handlebuy(ActionEvent actionEvent) {
        Flight selectedFlight = tabelzbor.getSelectionModel().getSelectedItem();
        if (selectedFlight != null && service.getAvailableSeats(selectedFlight) > 0) {
            service.saveTicket(new Ticket(client.getUsername(), selectedFlight.getId(), LocalDateTime.now()));
        }
        else{
            System.out.println("No available seats or no flight selected");
        }
    }
}