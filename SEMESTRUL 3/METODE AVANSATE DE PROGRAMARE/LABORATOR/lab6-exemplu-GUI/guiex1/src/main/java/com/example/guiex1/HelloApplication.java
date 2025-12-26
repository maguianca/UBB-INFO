package com.example.guiex1;

import com.example.guiex1.controller.SignInController;
import com.example.guiex1.domain.Utilizator;
import com.example.guiex1.domain.UtilizatorValidator;
import com.example.guiex1.repository.Repository;
import com.example.guiex1.repository.dbrepo.UtilizatorDbRepository;
import com.example.guiex1.services.SignInService;
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.layout.AnchorPane;
import javafx.stage.Stage;

import java.io.IOException;

public class HelloApplication extends Application {

    Repository<Long, Utilizator> utilizatorRepository;
    SignInService service;


    public static void main(String[] args) {
        launch(args);
    }

    @Override
    public void start(Stage primaryStage) throws IOException {
        System.out.println("Reading data from db");
        String username="postgres";
        String pasword="1205";
        String url="jdbc:postgresql://localhost:5432/socialnetwork";
        UtilizatorDbRepository utilizatorRepository =
                new UtilizatorDbRepository(url,username, pasword,  new UtilizatorValidator());
        service =new SignInService(utilizatorRepository);
        initView(primaryStage);
        primaryStage.show();

        Stage secondaryStage = new Stage();
        initView(secondaryStage);
        secondaryStage.show();
    }

    private void initView(Stage stage) throws IOException {

        FXMLLoader fxmlLoader = new FXMLLoader(HelloApplication.class.getResource("views/sign-in-view.fxml"));

        AnchorPane userLayout = fxmlLoader.load();
        stage.setScene(new Scene(userLayout));

        SignInController signInController = fxmlLoader.getController();
        signInController.setPrimaryStage(stage);
        signInController.setSignInService(service);
    }
}