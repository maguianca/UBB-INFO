package com.example.guiex1.controller;

import com.example.guiex1.domain.Utilizator;
import com.example.guiex1.domain.UtilizatorValidator;
import com.example.guiex1.repository.dbrepo.UtilizatorDbRepository;
import com.example.guiex1.services.SignInService;
import com.example.guiex1.services.UserAccountService;
import com.example.guiex1.services.UtilizatorService;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.Alert;
import javafx.scene.control.PasswordField;
import javafx.scene.control.TextField;
import javafx.scene.layout.AnchorPane;
import javafx.stage.Stage;

import java.io.IOException;
import java.util.Optional;

public class SignInController {
    @FXML
    private TextField textFieldFirstName;
    @FXML
    private TextField textFieldLastName;
    @FXML
    private PasswordField passwordFieldPassword;

    SignInService service;
    Stage primaryStage;

    public void setSignInService(SignInService service) {
        this.service = service;
    }

    public void setPrimaryStage(Stage primaryStage)
    {
        this.primaryStage = primaryStage;
    }

    private void changeStageToAccountView(Utilizator usr) throws IOException {
        UserAccountService utilizatorAccountService = UserAccountService.getInstance();
        FXMLLoader fxmlLoader = new FXMLLoader(SignInController.class.getResource("../views/account-view.fxml"));
        AnchorPane accountLayout = fxmlLoader.load();
        primaryStage.setScene(new Scene(accountLayout));

        AccountViewController accountViewController = fxmlLoader.getController();
        accountViewController.setNecessaryAtributes(primaryStage,utilizatorAccountService,usr);
    }

    public void handleLogIn() throws IOException {
        String firstName = textFieldFirstName.getText();
        String lastName = textFieldLastName.getText();
        String password = passwordFieldPassword.getText();

        Optional<Utilizator> usr = service.findOne(firstName,lastName,password);

        if(usr.isPresent()){
            changeStageToAccountView(usr.get());
        }
        else{
            MessageAlert.showMessage(null, Alert.AlertType.INFORMATION,"Eroare la logare","Ati introdus datele gresit");
        }

    }
}
