package com.example.taximetrie.controller;

import com.example.taximetrie.domeniu.Persoana;
import com.example.taximetrie.domeniu.Sofer;
import com.example.taximetrie.service.Service;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.Alert;
import javafx.scene.control.TextField;
import javafx.scene.layout.AnchorPane;
import javafx.stage.Stage;

import java.io.IOException;

public class Login{
    @FXML
    private TextField username_field;
    private Service service;
    Stage dialogStage;
    public void setUtilizatorService(Service service) {
        this.service = service;
        initModel();
    }
    @FXML
    public void initialize() {

    }

    private void initModel() {
        //List<Utilizator> all_users= StreamSupport.stream(service.getAll().spliterator(), false).collect(Collectors.toList());

    }
    public void handleLogIn(ActionEvent actionEvent) {
        String username = this.username_field.getText();
        Persoana persoana=service.findPersoana(username);
        Sofer sofer=service.findSofer(username);
        if(persoana!=null){
            try {
                FXMLLoader loader = new FXMLLoader(getClass().getResource("/com/example/taximetrie/ClientView.fxml"));
                AnchorPane root = loader.load();
                ClientController editUserController = loader.getController();
                Stage dialogStage = new Stage();
                dialogStage.setTitle("Client "+persoana.getNume());
                editUserController.setService(service, dialogStage,persoana);
                dialogStage.setScene(new Scene(root));
                dialogStage.show();
            } catch (IOException e) {
                e.printStackTrace();
                Alert alert = new Alert(Alert.AlertType.ERROR);
                alert.setTitle("Error");
                alert.setHeaderText("Could not load the Client window");
                alert.setContentText(e.getMessage());
                alert.showAndWait();
            }
        }else if(sofer!=null){
            try {
                FXMLLoader loader = new FXMLLoader(getClass().getResource("/com/example/taximetrie/SoferView.fxml"));
                AnchorPane root = loader.load();
                SoferController editUserController = loader.getController();
                Stage dialogStage = new Stage();
                dialogStage.setTitle("Sofer "+sofer.getNume());
                editUserController.setService(service, dialogStage, sofer);
                dialogStage.setScene(new Scene(root));
                dialogStage.show();
            } catch (IOException e) {
                e.printStackTrace();
                Alert alert = new Alert(Alert.AlertType.ERROR);
                alert.setTitle("Error");
                alert.setHeaderText("Could not load the Sofer window");
                alert.setContentText(e.getMessage());
                alert.showAndWait();
            }
        }else{
            System.out.println(username);
        }
    }
}
