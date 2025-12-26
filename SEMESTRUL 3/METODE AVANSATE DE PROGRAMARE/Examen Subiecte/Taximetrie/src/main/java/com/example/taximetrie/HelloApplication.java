package com.example.taximetrie;

import com.example.taximetrie.controller.Login;
import com.example.taximetrie.domeniu.*;
import com.example.taximetrie.repository.*;
import com.example.taximetrie.service.Service;
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.layout.AnchorPane;
import javafx.stage.Stage;

import java.io.IOException;
import java.util.stream.StreamSupport;

public class HelloApplication extends Application {
    public static void main(String[] args) {
        launch();
    }
    Service service;


    @Override
    public void start(Stage stage) throws IOException {
        Repository<Long, Persoana> persoanaRepo=new DBPersoanaRepo();
        Repository<Long, Sofer>soferRepo=new DBSoferRepo();
        PagingComenzi<Long, Comanda>comandaRepo=new DBComandaRepo(persoanaRepo,soferRepo);
        Repository<Long, Cerere>cerereRepo=new DBCerereRepo();
        Repository<Long, Oferta>ofertaRepo=new DBOfertaRepo();
        service=new Service(persoanaRepo,soferRepo,comandaRepo,cerereRepo,ofertaRepo);

        StreamSupport.stream(service.getPersoane().spliterator(), false)
                .forEach(System.out::println);

        FXMLLoader fxmlLoader = new FXMLLoader(HelloApplication.class.getResource("/com/example/taximetrie/login.fxml"));

        Scene scene = new Scene(fxmlLoader.load(), 400, 400);
        stage.setTitle("Hello!");
        stage.setScene(scene);
        stage.setWidth(600);
        Login login = fxmlLoader.getController();
        login.setUtilizatorService(service);
        stage.show();

    }


}