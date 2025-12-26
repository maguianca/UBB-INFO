package com.example.vacante;

import com.example.vacante.controller.ClientController;
import com.example.vacante.domeniu.Client;
import com.example.vacante.repository.DBClient;
import com.example.vacante.repository.DBHotel;
import com.example.vacante.repository.DBReservation;
import com.example.vacante.repository.DBSpecialOffer;
import com.example.vacante.service.Service;
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.stage.Stage;

import java.io.IOException;
import java.util.List;

import java.util.List;
import java.util.stream.Collectors;

public class HelloApplication extends Application {
    @Override
    public void start(Stage primaryStage) throws IOException {
        DBClient dbClient = new DBClient();
        DBReservation dbReservation = new DBReservation();
        DBHotel dbHotel = new DBHotel();
        DBSpecialOffer dbSpecialOffer = new DBSpecialOffer();
        Service service = new Service(dbClient, dbSpecialOffer, dbHotel, dbReservation);

        Parameters params = getParameters();
        List<String> rawClientIds = params.getRaw();
        List<String> clientIds = rawClientIds.stream()
                .map(s -> s.replaceAll("client:", ""))
                .collect(Collectors.toList());

        clientIds.forEach(System.out::println);

        for (String clientId : clientIds) {
            try {
                Long clientIdLong = Long.parseLong(clientId.trim()); // Convertire în Long
                Client client = service.findClient(clientIdLong);
                if (client != null) {
                    FXMLLoader fxmlLoader = new FXMLLoader(HelloApplication.class.getResource("Client.fxml"));
                    Scene scene = new Scene(fxmlLoader.load(), 500, 600);
                    Stage stage = new Stage();
                    ClientController controller = fxmlLoader.getController();
                    controller.setService(service, stage, client);
                    stage.setTitle("Client: " + clientId);
                    stage.setScene(scene);
                    stage.show();
                }
            } catch (NumberFormatException e) {
                System.err.println("Eroare: ID invalid " + clientId);
            }
        }
    }

    public static void main(String[] args) {
        launch(args);
    }
}
