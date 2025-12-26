package com.example.faptebune.controller;

import com.example.faptebune.domeniu.Nevoie;
import com.example.faptebune.domeniu.Persoana;
import com.example.faptebune.events.UtilizatorEntityChangeEvent;
import com.example.faptebune.observer.Observer;
import com.example.faptebune.service.Service;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.*;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.stage.Stage;

import java.time.LocalDateTime;
import java.util.List;
import java.util.stream.Collectors;
import java.util.stream.StreamSupport;

public class FereastraController implements Observer<UtilizatorEntityChangeEvent> {
    private Service service;
    private Stage dialogStage;
    private Persoana persoana;
    private Persoana.Oras oras;
    @FXML
    private TableView<Nevoie> tabel1;
    @FXML
    private TableView<Nevoie>tabel2;
    @FXML
    private TableColumn<Nevoie, String> titlu;
    @FXML
    private TableColumn<Nevoie, String> descriere;
    @FXML
    private TableColumn<Nevoie, String> deadline;
    @FXML
    private TableColumn<Nevoie, String> titlu2;
    @FXML
    private TableColumn<Nevoie, String> descriere2;
    @FXML
    private TableColumn<Nevoie, String> deadline2;
    @FXML
    private TableColumn<Nevoie, String> status;
    @FXML
    private TableColumn<Nevoie, Integer> omnevoie;
    @FXML
    private Button ajut;
    @FXML private Button inregistrare;
    @FXML
    private TextField titlufield;
    @FXML
    private TextField descrierefield;
    @FXML
    private DatePicker deadlinefield;

    private ObservableList<Nevoie> model = FXCollections.observableArrayList();
    private ObservableList<Nevoie> model2 = FXCollections.observableArrayList();
    public void setService(Service service, Stage dialogStage,Persoana persoana) {
        this.service = service;
        this.dialogStage = dialogStage;
        this.service.addObserver(this);
        this.persoana=persoana;
        this.oras=persoana.getOras();
        initModel();
    }

    private void initModel() {
       List<Nevoie> lista = service.getAllNevoi().stream()
                .filter(nevoie -> !nevoie.getOmInNevoie().equals(persoana.getId()) &&
               service.findPersoana(nevoie.getOmInNevoie()).getOras().equals(persoana.getOras()))
                .collect(Collectors.toList());
        //model.setAll(service.getAllNevoi());
        model.setAll(lista);
      //model.setAll(service.getAllNevoiId(persoana.getId()));
        model2.setAll(service.getAllNevoiId(persoana.getId()));

    }

    public void update(UtilizatorEntityChangeEvent event) {
        initModel();
    }

    @FXML
    private void initialize() {
        titlu.setCellValueFactory(new PropertyValueFactory<>("titlu"));
        descriere.setCellValueFactory(new PropertyValueFactory<>("descriere"));
        deadline.setCellValueFactory(new PropertyValueFactory<>("deadline"));
        status.setCellValueFactory(new PropertyValueFactory<>("status"));
        omnevoie.setCellValueFactory(new PropertyValueFactory<>("omInNevoie"));
        titlu2.setCellValueFactory(new PropertyValueFactory<>("titlu"));
        descriere2.setCellValueFactory(new PropertyValueFactory<>("descriere"));
        deadline2.setCellValueFactory(new PropertyValueFactory<>("deadline"));
        tabel1.setItems(model);
        tabel2.setItems(model2);
    }

    public void handleAjut(ActionEvent actionEvent) {
        Nevoie nevoie = tabel1.getSelectionModel().getSelectedItem();
        if(nevoie!=null && nevoie.getOmSalvator()==null){
            service.updateNevoie(nevoie.getId(),persoana.getId());
        }else{
            Alert alert = new Alert(Alert.AlertType.ERROR);
            alert.setTitle("Error");
            alert.setHeaderText(null);
            alert.setContentText("Are deja salvator!");
            alert.showAndWait();
        }
    }

    public void handleAjutat(ActionEvent actionEvent) {
        LocalDateTime dateTime = deadlinefield.getValue().atStartOfDay();
        String titlu = titlufield.getText();
        String descriere = descrierefield.getText();
        String status = "Caut Erou!";
        System.out.println(dateTime+" "+titlu+" "+descriere);
        if(dateTime !=null && titlu!=null && descriere!=null) {
            Nevoie nevoie = new Nevoie(titlu, descriere, dateTime, persoana.getId(), 0L, status);
            service.saveNevoie(nevoie);
            Alert alert = new Alert(Alert.AlertType.INFORMATION);
            alert.setTitle("Error");
            alert.setHeaderText(null);
            alert.setContentText("Am adaugat nevoia!");
            alert.showAndWait();
        }
        else{
            Alert alert = new Alert(Alert.AlertType.ERROR);
            alert.setTitle("Error");
            alert.setHeaderText(null);
            alert.setContentText("Adaugati date!");
            alert.showAndWait();
        }
    }
}