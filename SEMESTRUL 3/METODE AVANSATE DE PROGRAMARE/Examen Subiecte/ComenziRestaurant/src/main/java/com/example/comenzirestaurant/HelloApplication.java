package com.example.comenzirestaurant;

import com.example.comenzirestaurant.controller.StaffController;
import com.example.comenzirestaurant.controller.TableController;
import com.example.comenzirestaurant.domeniu.*;
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.stage.Stage;

import java.io.IOException;
import java.util.stream.StreamSupport;
import com.example.comenzirestaurant.repository.*;
import com.example.comenzirestaurant.service.Service;

public class HelloApplication extends Application {
    public static void main(String[] args) {
        launch();
    }
    Service service;
    @Override
    public void start(Stage stage) throws IOException {
        Repository<Long, Table> tableRepo = new DBTable();
        Repository<Long, Angajat>angajatRepo=new DBStaff();
        Repository<Long,MenuItem>menuItemRepo=new DBMenu(tableRepo);
        Repository<Long,Order>orderRepo=new DBComanda(tableRepo);
        service=new Service(angajatRepo,menuItemRepo,tableRepo,orderRepo);

        for (Angajat angajat : service.getAngajati()) {
            FXMLLoader fxmlLoader = new FXMLLoader(HelloApplication.class.getResource("/com/example/comenzirestaurant/Staff.fxml"));
            Scene scene = new Scene(fxmlLoader.load(), 400, 400);
            Stage staffStage = new Stage();
            staffStage.setTitle("Staff:  " + angajat.getNume());
            staffStage.setScene(scene);
            staffStage.setWidth(600);
            StaffController staffController = fxmlLoader.getController();
            staffController.setService(service, staffStage, angajat);
            staffStage.show();
        }
        for (Table table : service.getTables()) {
            FXMLLoader fxmlLoader = new FXMLLoader(HelloApplication.class.getResource("/com/example/comenzirestaurant/Table.fxml"));
            Scene scene = new Scene(fxmlLoader.load(), 400, 400);
            Stage staffStage = new Stage();
            staffStage.setTitle("Table:  " + table.getId());
            staffStage.setScene(scene);
            staffStage.setWidth(600);
            TableController staffController = fxmlLoader.getController();
            staffController.setService(service, staffStage, table);
            staffStage.show();
        }

    }
}