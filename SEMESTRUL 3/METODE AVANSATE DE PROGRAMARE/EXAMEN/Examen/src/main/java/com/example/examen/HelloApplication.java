package com.example.examen;

import com.example.examen.controller.CentruController;
import com.example.examen.domeniu.AdoptionCentre;
import com.example.examen.repository.DBRepoAdoptionCentre;
import com.example.examen.repository.DBRepoAnimal;
import com.example.examen.repository.DBRepoNotificare;
import com.example.examen.service.Service;
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.stage.Stage;

import java.io.IOException;

public class HelloApplication extends Application {
    @Override
    public void start(Stage primaryStage) throws IOException {
        DBRepoAnimal dbRepoAnimal = new DBRepoAnimal();
        DBRepoAdoptionCentre dbRepoAdoptionCentre = new DBRepoAdoptionCentre();
        DBRepoNotificare dbRepoNotificare=new DBRepoNotificare(dbRepoAdoptionCentre);
        Service service = new Service(dbRepoAdoptionCentre, dbRepoAnimal,dbRepoNotificare);

        for (AdoptionCentre centru : service.getAllCentre()) {
            FXMLLoader fxmlLoader = new FXMLLoader(HelloApplication.class.getResource("/com/example/examen/Centru.fxml"));

            Scene scene = new Scene(fxmlLoader.load(), 800, 800);
            Stage stage = new Stage();
            stage.setTitle(centru.getName() + " " + centru.getLocation() + " " + centru.getCapacity());
            stage.setScene(scene);
            stage.setWidth(600);
            CentruController login = fxmlLoader.getController();
            login.setService(service, stage, centru);
            stage.show();
        }
    }

    public static void main(String[] args) {
        launch();
    }
}