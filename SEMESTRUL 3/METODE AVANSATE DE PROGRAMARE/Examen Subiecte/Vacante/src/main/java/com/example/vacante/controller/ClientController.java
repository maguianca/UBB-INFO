package com.example.vacante.controller;

import com.example.vacante.domeniu.Client;
import com.example.vacante.domeniu.Reservation;
import com.example.vacante.domeniu.SpecialOffer;
import com.example.vacante.events.UtilizatorEntityChangeEvent;
import com.example.vacante.observer.Observer;
import com.example.vacante.service.Service;
import javafx.beans.property.ReadOnlyObjectWrapper;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.*;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.stage.Stage;

import java.time.LocalDate;
import java.time.ZoneId;
import java.time.temporal.ChronoUnit;
import java.util.Date;

public class ClientController {
    private Service service;
    private Client client;
    private Stage dialogStage;
    @FXML
    private TableColumn<SpecialOffer, String> numehotel;
    @FXML
    private TableColumn<SpecialOffer, Date> startdate;
    @FXML
    private TableColumn<SpecialOffer, Date> enddate;
    @FXML
    private TableColumn<SpecialOffer, String> numelocatie;
    @FXML
    private TableView<SpecialOffer> tabeloferte;
    private ObservableList<SpecialOffer> model = FXCollections.observableArrayList();
    private ObservableList<SpecialOffer> modelfilt = FXCollections.observableArrayList();
    @FXML
    private TableView<SpecialOffer> tabelfilt;
    @FXML
    private TableColumn<SpecialOffer, String> hotelnume;
    @FXML
    private TableColumn<SpecialOffer, Double> grad;
    @FXML
    private TableColumn<SpecialOffer, Double> pret;
    @FXML
    private DatePicker data1;
    @FXML
    private DatePicker data2;
    @FXML
    private ComboBox<String> locatie;
    @FXML
    private Label statuslabel;
    public void setService(Service service, Stage dialogStage, Client client) {
        this.service = service;
        this.dialogStage = dialogStage;
        this.client = client;
        initModel();
        this.service.addObserver(this);
        this.dialogStage.setOnCloseRequest(event -> {
            this.service.removeObserver(this);
            this.service.removeActiveClient(client.getClientId());
            System.out.println("Observer removed.");
        });
    }
    @Override
    public void update(UtilizatorEntityChangeEvent event) {
        int active_users = service.getActiveUsers(client.getClientId());
        statuslabel.setText(active_users+" other users(s) are looking at the same location");
        initModel();
    }

    public void initModel() {
        model.setAll(service.getAllOferteData(client.getFidelityGrade()));
        ObservableList<String> locatii = FXCollections.observableArrayList(service.findLocatii());
        locatie.setItems(locatii);
    }

    @FXML
    public void initialize() {
        numehotel.setCellValueFactory(cellData -> {
            SpecialOffer special = cellData.getValue();
            String nume = service.findHotel(special.getHotelId()).getHotelName();
            return new ReadOnlyObjectWrapper<>(nume);
        });
        numelocatie.setCellValueFactory(cellData -> {
            SpecialOffer special = cellData.getValue();
            String nume = service.findHotel(special.getHotelId()).getLocationName();
            return new ReadOnlyObjectWrapper<>(nume);
        });
        startdate.setCellValueFactory(new PropertyValueFactory<>("startDate"));
        enddate.setCellValueFactory(new PropertyValueFactory<>("endDate"));

        tabeloferte.setItems(model);
        tabelfilt.setItems(modelfilt);

        hotelnume.setCellValueFactory(cellData -> {
            SpecialOffer special = cellData.getValue();
            String nume = service.findHotel(special.getHotelId()).getHotelName();
            return new ReadOnlyObjectWrapper<>(nume);
        });
        grad.setCellValueFactory(cellData -> {
                //int numar = service.findHotel(special.getHotelId()).getNoRooms();
                //System.out.println(x);
                //System.out.println(numar);
                //int x=service.getRezervari(special.getHotelId(),special.getStartDate(),special.getStartDate());
                SpecialOffer special = cellData.getValue();
                int sum = 0;
                LocalDate startDate = special.getStartDate();
                LocalDate endDate = special.getEndDate();
            int noRooms = service.findHotel(special.getHotelId()).getNoRooms();
                for (LocalDate date = startDate; !date.isAfter(endDate); date = date.plusDays(1)) {
                    sum += service.getGrad(special.getHotelId(), date)*100/noRooms;
                }
                long numar = ChronoUnit.DAYS.between(startDate, endDate) + 1;
                return new ReadOnlyObjectWrapper<>((double) sum / numar);
            });
        pret.setCellValueFactory(cellData -> {
            SpecialOffer special = cellData.getValue();
            Double pret = service.findHotel(special.getHotelId()).getPricePerNight();
            return new ReadOnlyObjectWrapper<>(pret);
        });
    }

    public void handleserch(ActionEvent actionEvent) {
        if (data1.getValue() != null && data2.getValue() != null && locatie.getValue() != null) {
            LocalDate date1 = data1.getValue();
            LocalDate date2 = data2.getValue();
            modelfilt.setAll(service.getAllOferteFilt(client.getClientId(),locatie.getValue().toString(), date1, date2));
        } else {
            System.out.println("nu ati selectat tot!");
        }
    }


    public void handlebook(ActionEvent actionEvent) {
        SpecialOffer selectedOffer = tabelfilt.getSelectionModel().getSelectedItem();
        double id = service.getLastReservationId();
        if (selectedOffer != null && data1.getValue() != null && data2.getValue() != null &&
                (data1.getValue().isEqual(selectedOffer.getStartDate()) || data1.getValue().isAfter(selectedOffer.getStartDate())) &&
                (data2.getValue().isEqual(selectedOffer.getEndDate()) || data2.getValue().isBefore(selectedOffer.getEndDate()))) {

            LocalDate startDate = data1.getValue();
            LocalDate endDate = data2.getValue();
            Reservation reservation = new Reservation(
                    id,
                    client.getClientId(),
                    selectedOffer.getHotelId(),
                    startDate.atStartOfDay(),
                    (int) java.time.temporal.ChronoUnit.DAYS.between(startDate, endDate)
            );
            service.saveRezervare(reservation);
            System.out.println("Reservation saved: " + reservation);
        } else {
            System.out.println("Please select an offer and dates!");
        }
    }
}