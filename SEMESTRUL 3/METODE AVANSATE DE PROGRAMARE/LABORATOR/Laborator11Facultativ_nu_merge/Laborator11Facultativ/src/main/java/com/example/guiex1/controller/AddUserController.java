package com.example.guiex1.controller;

import com.example.guiex1.domain.Utilizator;
import com.example.guiex1.domain.ValidationException;
import com.example.guiex1.services.UtilizatorService;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.Alert;
import javafx.scene.control.TextField;
import javafx.stage.Stage;

public class AddUserController {

    @FXML
    private TextField fieldSaveFirst;
    @FXML
    private TextField fieldSaveLast;
    @FXML
    private TextField fieldpass;
    @FXML
    private TextField fieldusername;


    private UtilizatorService service;
    Stage dialogStage;
    Utilizator utilizator;

    @FXML
    private void initialize() {
    }

    public void setService(UtilizatorService service,  Stage stage) {
        this.service = service;
        this.dialogStage=stage;
    }


    private void clearFields() {
        fieldSaveLast.setText("");
        fieldSaveFirst.setText("");

    }
    private void setFields(Utilizator u)
    {
        fieldSaveFirst.setText(u.getFirstName());
        fieldSaveLast.setText(u.getLastName());

    }

    public void handleSave(ActionEvent actionEvent) {
        String firstName = fieldSaveFirst.getText();
        String lastName = fieldSaveLast.getText();
        String password = fieldpass.getText();
        String username = fieldusername.getText();
        //String password ="0000";
        String descriere="Hello!Text me <3!!";
        String poza="/com/example/guiex1/images/mpp_pic.png";
        Utilizator updatedUser = new Utilizator(firstName, lastName,password,username,descriere,poza);
        updatedUser.setPassword(password);
        try {
            Utilizator result = service.addUtilizator(updatedUser);

            if (result != null) {
                MessageAlert.showMessage(dialogStage, Alert.AlertType.INFORMATION, "User Save", "The user has been successfully saved.");
                dialogStage.close();
            }
        } catch (ValidationException e) {
            MessageAlert.showErrorMessage(dialogStage, e.getMessage());
        }
    }


    public void handleUpdateCancel(ActionEvent actionEvent) {
        dialogStage.close();
    }


}
