package com.example.zboruri2.controller;

import com.example.zboruri2.domeniu.Client;
import com.example.zboruri2.domeniu.Flight;
import com.example.zboruri2.domeniu.Ticket;
import com.example.zboruri2.domeniu.MessageAlert;
import com.example.zboruri2.events.UtilizatorEntityChangeEvent;
import com.example.zboruri2.observer.Observer;
import com.example.zboruri2.paging.Page;
import com.example.zboruri2.paging.Pageable;
import com.example.zboruri2.service.Service;
import javafx.beans.property.ReadOnlyObjectWrapper;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.*;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.stage.Stage;

import javafx.scene.control.Alert.AlertType;
import java.time.LocalDate;
import java.time.LocalDateTime;

public class ClientController implements Observer<UtilizatorEntityChangeEvent> {
    private Service service;
    private Client client;
    private Stage dialogStage;
    @FXML
    private Label labelpage;
    @FXML
    private Button prev;
    @FXML
    private Button next;
    @FXML
    private TableColumn<Ticket, String> flight;
    @FXML
    private TableColumn<Ticket, LocalDateTime> purchase;
    @FXML
    private TableView<Ticket> table;
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
    Integer currentPage = 1;
    private static final Integer PAGE_SIZE = 5;

    private ObservableList<Ticket> model = FXCollections.observableArrayList();
    private ObservableList<Flight> modelzbor = FXCollections.observableArrayList();
    private String from1;
    private String to1;;
    private LocalDate departuretime1;
    public void setService(Service service, Stage dialogStage, Client client) {
        this.service = service;
        this.dialogStage = dialogStage;
        this.client = client;
        initModel();
        this.service.addObserver(this);
    }

    public void initModel() {
        model.setAll(service.getAllTicketsClient(client.getUsername()));
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
            from1=from;
            to1=to;
            departuretime1=selectedDate;
            modelzbor.setAll(service.getAllFlightsFiltered(from, to, selectedDate));
            populatePersonList(selectedDate,from,to);
        } else {
            modelzbor.clear();
        }
    }

    public void handlebuy(ActionEvent actionEvent) {
        Flight selectedFlight = tabelzbor.getSelectionModel().getSelectedItem();
        if (selectedFlight != null && service.getAvailableSeats(selectedFlight) > 0) {
            service.saveTicket(new Ticket(client.getUsername(), selectedFlight.getId(), LocalDateTime.now()));
            MessageAlert.showMessage(dialogStage, Alert.AlertType.INFORMATION, "Success", "Ticket purchased successfully!");
        }
        else{
            MessageAlert.showErrorMessage(dialogStage, "No available seats or no flight selected");
        }
    }
    public void handlenext(ActionEvent actionEvent) {
        currentPage++;
        populatePersonList(departuretime1,from1,to1);
    }

    public void handleprev(ActionEvent actionEvent) {
        currentPage--;
        populatePersonList(departuretime1,from1,to1);
    }
    private void createPersonRow(Flight p) {
        if (p != null && !modelzbor.contains(p)) { // Exclude duplicatele
            modelzbor.add(p);
        }
    }
    private void populatePersonList(LocalDate departuretime,String from,String to){
        modelzbor.clear();
        Pageable pageable=new Pageable(currentPage,PAGE_SIZE);
        Page<Flight> lista=service.getPageFlightsId(departuretime,from,to,pageable);
        for(Flight f:lista.getElementsOnPage()){
            createPersonRow(f);
        }
        Integer totalNumberOfPages = (int)(Math.ceil((double)lista.getTotalNumberElements() / PAGE_SIZE));
        labelpage.setText("Page "+ currentPage + "/" + totalNumberOfPages);
        if(currentPage == 1)
            prev.setDisable(true);
        else
            prev.setDisable(false);
        if(currentPage == totalNumberOfPages)
            next.setDisable(true);
        else
            next.setDisable(false);
    }
}