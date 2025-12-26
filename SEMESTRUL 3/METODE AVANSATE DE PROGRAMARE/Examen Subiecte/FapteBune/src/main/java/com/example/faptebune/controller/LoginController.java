package com.example.faptebune.controller;

import com.example.faptebune.domeniu.Persoana;
import com.example.faptebune.events.UtilizatorEntityChangeEvent;
import com.example.faptebune.observer.Observer;
import com.example.faptebune.service.Service;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.stage.Stage;

import java.io.IOException;

public class LoginController implements Observer<UtilizatorEntityChangeEvent> {
    private Service service;
    private Stage dialogStage;
    private ObservableList<Persoana> model = FXCollections.observableArrayList();
    @FXML
    private TableView<Persoana> tabel;
    @FXML
    private TableColumn<Persoana, String> nume;
    @FXML
    private TableColumn<Persoana, String> prenume;
    @FXML
    private TableColumn<Persoana, String> username;
    @FXML
    private TextField fnume;
    @FXML
    private TextField fprenume;
    @FXML
    private TextField fusername;
    @FXML
    private TextField fparola;
    @FXML
    private TextField fparola1;
    @FXML
    private TextField fstrada;
    @FXML
    private TextField fnumar;
    @FXML
    private TextField ftelefon;
    @FXML
    private ComboBox<String> oras;

    public void setService(Service service, Stage dialogStage) {
        this.service = service;
        this.dialogStage = dialogStage;
        initModel();
        this.service.addObserver(this);
    }

    private void initModel() {
        model.setAll(service.getAllPersoane());
    }

    public void update(UtilizatorEntityChangeEvent event) {
        initModel();
    }

    @FXML
    private void initialize() {
        nume.setCellValueFactory(new PropertyValueFactory<>("nume"));
        prenume.setCellValueFactory(new PropertyValueFactory<>("prenume"));
        username.setCellValueFactory(new PropertyValueFactory<>("username"));
        oras.setItems(FXCollections.observableArrayList("BUCURESTI", "CLUJ", "IASI", "TIMISOARA", "ORADEA"));
        tabel.setItems(model);
        tabel.setOnMouseClicked(event -> {
            if (event.getClickCount() == 1 && tabel.getSelectionModel().getSelectedItem() != null) {
                Persoana selectedPersoana = tabel.getSelectionModel().getSelectedItem();
                showPersoanaDetails(selectedPersoana);
            }
        });
    }

    private void showPersoanaDetails(Persoana persoana) {
        try {
            FXMLLoader loader = new FXMLLoader(getClass().getResource("/com/example/faptebune/Fereastra.fxml"));
            Parent root = loader.load();

            FereastraController controller = loader.getController();
            controller.setService(service, new Stage(), persoana);

            Stage stage = new Stage();
            stage.setTitle("Persoana Details");
            stage.setScene(new Scene(root));
            stage.show();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void handlecont(ActionEvent actionEvent) {
        String nume = fnume.getText();
        String prenume = fprenume.getText();
        String username = fusername.getText();
        String parola = fparola.getText();
        String parola1 = fparola1.getText();
        String strada = fstrada.getText();
        String numar = fnumar.getText();
        String telefon = ftelefon.getText();
        String oras = this.oras.getValue();
        if (parola.equals(parola1)) {
            Persoana p = new Persoana(nume, prenume, username, parola, Persoana.Oras.valueOf(oras.toUpperCase()), strada, numar, telefon);
            service.savePersoana(p);
        } else {
            Alert alert = new Alert(Alert.AlertType.ERROR);
            alert.setTitle("Error");
            alert.setHeaderText(null);
            alert.setContentText("Parolele nu sunt la fel!");
            alert.showAndWait();
        }
    }
}