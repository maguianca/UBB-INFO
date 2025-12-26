package com.example.examen.controller;

import com.example.examen.domeniu.AdoptionCentre;
import com.example.examen.domeniu.Animal;
import com.example.examen.domeniu.Notificare;
import com.example.examen.events.UtilizatorEntityChangeEvent;
import com.example.examen.observer.Observer;
import javafx.beans.property.SimpleStringProperty;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import com.example.examen.service.Service;
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

public class CentruController implements Observer<UtilizatorEntityChangeEvent> {
    private Service service;
    private Stage dialogStage;
    private AdoptionCentre centru;
    @FXML
    private TableView<Animal> tabelanimale;
    @FXML
    private TableColumn<Animal, Integer> id;
    @FXML
    private TableColumn<Animal, String> nume;
    @FXML
    private TableColumn<Animal, Integer> centruid;
    @FXML
    private TableColumn<Animal, String> tip;
    @FXML
    private Label numelocatiecentru;
    @FXML
    private Label procent;
    private ObservableList<Animal> model = FXCollections.observableArrayList();
    private ObservableList<Notificare> modelnotificare = FXCollections.observableArrayList();
    @FXML
    private ComboBox<String> animaletip;
    @FXML
    private TableView<Notificare> tabelnotificare;
    @FXML
    private TableColumn<Notificare, Integer> idcentru;
    @FXML
    private TableColumn<Notificare, Integer> idanimal;
    @FXML
    private TableColumn<Notificare, Boolean> actiuni;
    @FXML
    private TableColumn<Notificare, String> text;
    @FXML
    private TableColumn<Animal, Boolean> animalactiuni;

    public void setService(Service service, Stage dialogStage, AdoptionCentre centru) {
        this.service = service;
        this.dialogStage = dialogStage;
        this.centru = centru;
        initModel();
        numelocatiecentru.setText("Nume:" + centru.getName() + " locatie:" + centru.getLocation() + " capacitate: " + centru.getCapacity());
        this.service.addObserver(this);
    }

    @Override
    public void update(UtilizatorEntityChangeEvent event) {
        initModel();
    }

    public void initialize() {
        nume.setCellValueFactory(new PropertyValueFactory<>("name"));
        centruid.setCellValueFactory(new PropertyValueFactory<>("centreId"));
        tip.setCellValueFactory(new PropertyValueFactory<>("type"));
        tabelanimale.setItems(model);
        id.setCellValueFactory(new PropertyValueFactory<>("id"));
        animaletip.setItems(FXCollections.observableArrayList("All Types", "DOG", "CAT"));
        animaletip.getSelectionModel().select("All Types");

        animaletip.getSelectionModel().selectedItemProperty().addListener((options, oldValue, newValue) -> {
            filterTable(newValue);
        });
        text.setCellValueFactory(cellData -> {
            Notificare notificare = cellData.getValue();
            String textValue = String.format("%s requested to transfer %s", service.findCentru(notificare.getCentreid()).getName(), service.findAnimal(notificare.getAnimalid()).getName());
            return new SimpleStringProperty(textValue);
        });
        tabelnotificare.setItems(modelnotificare);
        idcentru.setCellValueFactory(new PropertyValueFactory<>("centruid"));
        idanimal.setCellValueFactory(new PropertyValueFactory<>("animalid"));
        actiuni.setCellFactory(param -> new TableCell<Notificare, Boolean>() {
            private final Button btnAccepta = new Button("Acceptă");
            private final Button btnRefuza = new Button("Ignore");

            {
                btnAccepta.setOnAction(event -> {
                    Notificare notificare = getTableView().getItems().get(getIndex());
                    handleAccepta(notificare);
                });

                btnRefuza.setOnAction(event -> {
                    Notificare notificare = getTableView().getItems().get(getIndex());
                    handleIgnore(notificare);
                });
            }

            @Override
            protected void updateItem(Boolean item, boolean empty) {
                super.updateItem(item, empty);
                if (empty) {
                    setGraphic(null);
                } else {
                    HBox buttonsBox = new HBox(10, btnAccepta, btnRefuza);
                    setGraphic(buttonsBox);
                }
            }
        });

        animalactiuni.setCellFactory(param -> new TableCell<Animal, Boolean>() {
            private final Button btnRequestTransfer = new Button("Request Transfer");

            {
                btnRequestTransfer.setOnAction(event -> {
                    Animal animal = getTableView().getItems().get(getIndex());
                    handleRequestTransfer(animal);
                });
            }

            @Override
            protected void updateItem(Boolean item, boolean empty) {
                super.updateItem(item, empty);
                if (empty) {
                    setGraphic(null);
                } else {
                    setGraphic(btnRequestTransfer);
                }
            }
        });
    }

    private void handleAccepta(Notificare notificare) {
        System.out.println("acceptată: " + notificare);
        showConfirmationMessage("Ai acceptat notificarea!");
        service.updateanimal(notificare.getAnimalid(), centru.getId());
        service.deleteNotificare(notificare.getId());
        initModel();
    }

    private void handleIgnore(Notificare notificare) {
        System.out.println("Notificare refuzată: " + notificare);
        showConfirmationMessage("Ai refuzat notificarea!");
        modelnotificare.remove(notificare);
    }

    private void handleRequestTransfer(Animal animal) {
        System.out.println("Request Transfer for: " + animal);
        Notificare notificare = new Notificare(null, animal.getCentreId(), animal.getId(), null);
        service.saveNotificare(notificare);
        showMessage("Transfer Request", "Transfer request has been made.");
    }

    private void showConfirmationMessage(String message) {
        Alert alert = new Alert(Alert.AlertType.INFORMATION);
        alert.setTitle("Confirmation");
        alert.setHeaderText(null);
        alert.setContentText(message);
        alert.showAndWait();
    }

    private void initModel() {
        model.clear();
        model.setAll(service.getAllAnimale(centru.getId()));
        if (service.getProcent(centru.getId()) != 0)
            procent.setText("Occupancy:" + (double) service.getProcent(centru.getId()) / centru.getCapacity() + "%");
        else {
            procent.setText("Occupancy:" + 0 + "%");
        }
        modelnotificare.setAll(service.getAllFiltered(centru.getId()));
    }

    private void filterTable(String type) {
        if (type.equals("All Types")) {
            model.setAll(service.getAllAnimale(centru.getId()));
        } else {
            model.setAll(service.filtreaza_tip(centru.getId(), type));
        }
    }

    @FXML
    public void handleRequestTransfer(ActionEvent actionEvent) {
        Animal selectedAnimal = tabelanimale.getSelectionModel().getSelectedItem();
        if (selectedAnimal == null) {
            showError("No animal selected", "Please select an animal to request transfer.");
        } else {
            Notificare notificare = new Notificare(null, selectedAnimal.getCentreId(), selectedAnimal.getId(), null);
            service.saveNotificare(notificare);
            showMessage("Transfer Request", "Transfer request has been made.");
        }
    }

    private void showError(String title, String message) {
        Alert alert = new Alert(Alert.AlertType.ERROR);
        alert.initOwner(dialogStage);
        alert.setTitle(title);
        alert.setHeaderText(null);
        alert.setContentText(message);
        alert.showAndWait();
    }

    private void showMessage(String title, String message) {
        Alert alert = new Alert(Alert.AlertType.INFORMATION);
        alert.initOwner(dialogStage);
        alert.setTitle(title);
        alert.setHeaderText(null);
        alert.setContentText(message);
        alert.showAndWait();
    }
}