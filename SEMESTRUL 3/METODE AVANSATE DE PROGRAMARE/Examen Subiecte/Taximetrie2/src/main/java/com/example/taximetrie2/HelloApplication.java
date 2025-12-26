package com.example.taximetrie2;

import com.example.taximetrie2.controller.LoginController;
import com.example.taximetrie2.repository.*;
import com.example.taximetrie2.service.Service;
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.stage.Stage;

import java.io.IOException;

public class HelloApplication extends Application {
    @Override
    public void start(Stage stage) throws IOException {
        DBRepoPersoana dbRepoPersoana=new DBRepoPersoana();
        DBRepoSofer dbRepoSofer=new DBRepoSofer();
        DBRepoComanda dbRepoComanda=new DBRepoComanda(dbRepoPersoana,dbRepoSofer);
        DBRepoCerere dbRepoCerere=new DBRepoCerere();
        DBRepoOferta dbRepoOferta=new DBRepoOferta();
        Service service=new Service(dbRepoPersoana,dbRepoSofer,dbRepoComanda,dbRepoCerere,dbRepoOferta);

        FXMLLoader fxmlLoader = new FXMLLoader(HelloApplication.class.getResource("/com/example/taximetrie2/Login.fxml"));

        Scene scene = new Scene(fxmlLoader.load(), 400, 400);
        stage.setTitle("Hello!");
        stage.setScene(scene);
        stage.setWidth(600);
        LoginController login = fxmlLoader.getController();
        login.setUtilizatorService(service);
        stage.show();
    }

    public static void main(String[] args) {
        launch();
    }
}