package com.example.taximetrie2.controller;

import com.example.taximetrie2.domeniu.*;
import com.example.taximetrie2.events.UtilizatorEntityChangeEvent;
import com.example.taximetrie2.observer.Observer;
import com.example.taximetrie2.service.Service;
import javafx.beans.property.ReadOnlyObjectWrapper;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.*;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.layout.HBox;
import javafx.stage.Stage;

import java.time.LocalDateTime;
import java.util.List;
import java.util.stream.Collectors;
import java.util.stream.StreamSupport;

public class ClientController implements Observer<UtilizatorEntityChangeEvent> {
    private Service service;
    private Stage dialogStage;
    private Persoana persoana;
    @FXML
    private TextField locatie;
    @FXML
    private TableView<Oferta> tabel;
    @FXML
    private TableColumn<Oferta, String> indicativ;
    @FXML
    private TableColumn<Oferta, Integer> minute;
    @FXML
    private TableColumn<Oferta, Boolean> actiuni;
    private ObservableList<Oferta> model = FXCollections.observableArrayList();
    public void setService(Service service, Stage dialogStage, Persoana client) {
        this.service = service;
        this.dialogStage = dialogStage;
        this.persoana = client;
        initmodel();
        this.service.addObserver(this);
    }

    @Override
    public void update(UtilizatorEntityChangeEvent utilizatorEntityChangeEvent) {
        initmodel();
    }

    @FXML
    public void initialize() {
        indicativ.setCellValueFactory(cellData -> {
            Long idSofer = cellData.getValue().getId_sofer();
            String sofer = service.getSoferId(idSofer).getIndicativMasina();
            return new ReadOnlyObjectWrapper<>(sofer);
        });
        minute.setCellValueFactory(new PropertyValueFactory<>("minute"));

        actiuni.setCellFactory(param -> new TableCell<>() {
            private final Button btnAccepta = new Button("Acceptă");
            private final Button btnRefuza = new Button("Refuză");

            {
                btnAccepta.setOnAction(event -> {
                    Oferta oferta = getTableView().getItems().get(getIndex());
                    handleAcceptaOferta(oferta);
                });

                btnRefuza.setOnAction(event -> {
                    Oferta oferta = getTableView().getItems().get(getIndex());
                    handleRefuzaOferta(oferta);
                });
            }

            @Override
            protected void updateItem(Boolean item, boolean empty) {
                super.updateItem(item, empty);
                if (empty) {
                    setGraphic(null);
                } else {
                    HBox pane = new HBox(btnAccepta, btnRefuza);
                    setGraphic(pane);
                }
            }
        });
        tabel.setItems(model);
    }

    public void initmodel() {
        model.clear();
        model.setAll(service.getAllOferteId(persoana.getId()));
    }

    public void handleCauta(ActionEvent actionEvent) {
        String adresa = locatie.getText();
        if (adresa.isEmpty()) {
            showErrorMessage("Adresa nu poate fi goală!");
            return;
        }
        service.save_cerere(new Cerere(persoana.getId(), adresa));
        showConfirmationMessage("Cerere trimisă!");
    }

    private void handleAcceptaOferta(Oferta oferta) {
        System.out.println("Oferta acceptată: " + oferta);
        showConfirmationMessage("Ai acceptat oferta de la " + service.getSoferId(oferta.getId_sofer()).getNume() + "!");
        service.delete_oferta(oferta.getId());
        service.saveComanda(new Comanda(service.getPersoanaId(persoana.getId()),service.getSoferId(oferta.getId_sofer()), LocalDateTime.now()));
        service.delete_cerere(oferta.getId_cerere());
        initmodel();
    }

    // Refuză o ofertă
    private void handleRefuzaOferta(Oferta oferta) {
        System.out.println("Oferta refuzata: " + oferta);
        showConfirmationMessage("Ai refuzat oferta de la " + service.getSoferId(oferta.getId_sofer()).getNume() + "!");
        System.out.println(oferta.getId());
        service.delete_oferta(oferta.getId());
        initmodel();
    }
    private void showErrorMessage(String message) {
        Alert alert = new Alert(Alert.AlertType.ERROR);
        alert.setTitle("Eroare");
        alert.setHeaderText(null);
        alert.setContentText(message);
        alert.showAndWait();
    }

    // Afișează un mesaj de confirmare
    private void showConfirmationMessage(String message) {
        Alert alert = new Alert(Alert.AlertType.INFORMATION);
        alert.setTitle("Confirmare");
        alert.setHeaderText(null);
        alert.setContentText(message);
        alert.showAndWait();
    }
}