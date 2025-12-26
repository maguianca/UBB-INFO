package com.example.zboruri;

import com.example.zboruri.controller.LoginController;
import com.example.zboruri.repository.DBRepoClient;
import com.example.zboruri.repository.DBRepoFlight;
import com.example.zboruri.repository.DBRepoTicket;
import com.example.zboruri.service.Service;
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.stage.Stage;

import java.io.IOException;

public class HelloApplication extends Application {
    @Override
    public void start(Stage stage) throws IOException {
        DBRepoClient repoClient = new DBRepoClient();
        DBRepoTicket repoTicket = new DBRepoTicket();
        DBRepoFlight repoFlight = new DBRepoFlight();
        Service service=new Service(repoClient,repoFlight,repoTicket);
        FXMLLoader fxmlLoader = new FXMLLoader(HelloApplication.class.getResource("/com/example/zboruri/Login.fxml"));
        Scene scene = new Scene(fxmlLoader.load(), 500, 350);
        stage.setScene(scene);
        LoginController login = fxmlLoader.getController();
        login.setService(service, stage);
        stage.show();
    }

    public static void main(String[] args) {
        launch();
    }
}