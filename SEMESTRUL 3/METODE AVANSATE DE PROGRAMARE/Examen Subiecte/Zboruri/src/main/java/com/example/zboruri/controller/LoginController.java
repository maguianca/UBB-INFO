package com.example.zboruri.controller;

import com.example.zboruri.HelloApplication;
import com.example.zboruri.domeniu.Client;
import com.example.zboruri.service.Service;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.Alert;
import javafx.scene.control.TextField;
import javafx.stage.Stage;

public class LoginController {
    @FXML
    private TextField usernamefield;
    private Service service;
    private Stage dialogStage;
    public void setService(Service service, Stage dialogStage) {
        this.service = service;
        this.dialogStage = dialogStage;
    }

    public void handleLogin(ActionEvent actionEvent) {
        String nume = usernamefield.getText();
        Client client=service.findClient(nume);
        if(client!=null ){
            try {
                FXMLLoader fxmlLoader = new FXMLLoader(HelloApplication.class.getResource("/com/example/zboruri/Client.fxml"));
                Scene scene = new Scene(fxmlLoader.load(), 500, 450);
                Stage stage1 = new Stage();
                stage1.setScene(scene);
                ClientController login = fxmlLoader.getController();
                login.setService(service, stage1,client);
                stage1.setTitle(nume);
                stage1.show();
            } catch (Exception e) {
                e.printStackTrace();
            }
        }else{
            Alert alert = new Alert(Alert.AlertType.ERROR);
            alert.setTitle("Error");
            alert.setHeaderText(null);
            alert.setContentText("Userul nu exista!");
            alert.showAndWait();
        }
    }
}
