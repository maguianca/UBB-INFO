package com.example.trenuri;

import com.example.trenuri.controller.HelloController;
import com.example.trenuri.repository.DBCity;
import com.example.trenuri.repository.DBTrainStation;
import com.example.trenuri.service.Service;
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.stage.Stage;

import java.io.IOException;

public class HelloApplication extends Application {
    @Override
    public void start(Stage stage) throws IOException {
        DBCity repoCity=new DBCity();
        DBTrainStation repoTrainStation=new DBTrainStation(repoCity);
        Service service=new Service(repoCity,repoTrainStation);
        FXMLLoader fxmlLoader = new FXMLLoader(HelloApplication.class.getResource("hello-view.fxml"));
        Scene scene = new Scene(fxmlLoader.load(), 320, 240);
        stage.setTitle("Hello!");
        HelloController login = fxmlLoader.getController();
        login.setService(service, stage);
        stage.setScene(scene);
        stage.show();
    }

    public static void main(String[] args) {
        launch();
    }
}