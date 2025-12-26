package com.example.trenuri.controller;

import com.example.trenuri.events.UtilizatorEntityChangeEvent;
import com.example.trenuri.observer.Observer;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.Label;
import javafx.stage.Stage;
import com.example.trenuri.service.Service;

import java.io.IOException;

public class HelloController {
    @FXML
    private Label welcomeText;
    private Service service;
    private Stage stage;
    private int count=1;
    public void setService(Service service, Stage stage) {
        this.service=service;
        this.stage=stage;
    }
    @FXML
    protected void onHelloButtonClick() {
        welcomeText.setText("Open New Client Window!");
        try {
            // Încarcă fișierul FXML pentru noua fereastră
            FXMLLoader fxmlLoader = new FXMLLoader(HelloController.class.getResource("/com/example/trenuri/Client.fxml"));
            Scene scene = new Scene(fxmlLoader.load());

            // Creează un nou stage
            Stage stage1 = new Stage();
            stage1.setScene(scene);

            // Setează controlerul și serviciul pentru fereastra nouă
            ClientController clientController = fxmlLoader.getController();
            clientController.setService(count,service, stage1);

            // Personalizează fereastra
            stage1.setTitle("Client Window: " + count);
            count++;

            // Afișează noul stage
            stage1.show();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

}