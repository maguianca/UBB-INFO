package com.example.faptebune;

import com.example.faptebune.controller.LoginController;
import com.example.faptebune.repository.RepoNevoie;
import com.example.faptebune.repository.RepoPersoana;
import com.example.faptebune.service.Service;
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.stage.Stage;

import java.io.IOException;

public class HelloApplication extends Application {
    Service service;
    @Override
    public void start(Stage stage) throws IOException {
        RepoPersoana persoanaRepo=new RepoPersoana();
        RepoNevoie repoNevoie=new RepoNevoie(persoanaRepo);
        service=new Service(persoanaRepo,repoNevoie);
        FXMLLoader fxmlLoader = new FXMLLoader(HelloApplication.class.getResource("/com/example/faptebune/Login.fxml"));
        Scene scene = new Scene(fxmlLoader.load(), 700, 450);
        stage.setScene(scene);
        LoginController login = fxmlLoader.getController();
        login.setService(service, stage);
        stage.show();
    }

    public static void main(String[] args) {
        launch();
    }
}