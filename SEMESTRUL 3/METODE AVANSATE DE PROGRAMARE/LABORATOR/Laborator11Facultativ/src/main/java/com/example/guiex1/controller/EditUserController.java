package com.example.guiex1.controller;

import com.example.guiex1.domain.Utilizator;
import com.example.guiex1.domain.ValidationException;
import com.example.guiex1.services.UtilizatorService;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.Alert;
import javafx.scene.control.TextField;
import javafx.scene.image.Image;
import javafx.stage.FileChooser;
import javafx.stage.Stage;

import java.io.File;


public class EditUserController {

    @FXML
    private TextField fieldUpdateFirst;
    @FXML
    private TextField fieldUpdateLast;
    @FXML
    private TextField bio;


    private UtilizatorService service;
    Stage dialogStage;
    Utilizator utilizator;

    @FXML
    private void initialize() {
    }

    public void setService(UtilizatorService service,  Stage stage, Utilizator u) {
        this.service = service;
        this.dialogStage=stage;
        this.utilizator =u;
        if (null != u) {
            setFields(u);

        }
    }


    private void clearFields() {
        fieldUpdateLast.setText("");
        fieldUpdateFirst.setText("");

    }
    private void setFields(Utilizator u)
    {
        fieldUpdateFirst.setText(u.getFirstName());
        fieldUpdateLast.setText(u.getLastName());
        bio.setText(u.getDescriere());

    }

    public void handleUpdateSave(ActionEvent actionEvent) {
        String firstName = fieldUpdateFirst.getText();
        String lastName = fieldUpdateLast.getText();
        String descriere = bio.getText();
        Utilizator updatedUser = new Utilizator(firstName, lastName, utilizator.getPassword(),utilizator.getUsername(),descriere, utilizator.getUrl());
        updatedUser.setId(utilizator.getId());
        try {
            Utilizator result = service.updateUtilizator(updatedUser);

            if (result != null) {
                MessageAlert.showMessage(dialogStage, Alert.AlertType.INFORMATION, "User Updated", "The user has been successfully updated.");
                dialogStage.close();
            }
        } catch (ValidationException e) {
            MessageAlert.showErrorMessage(dialogStage, e.getMessage());
        }
    }


    public void handleUpdateCancel(ActionEvent actionEvent) {
        dialogStage.close();
    }

    public void handlephoto(ActionEvent actionEvent) {
        FileChooser fileChooser = new FileChooser();
        fileChooser.setTitle("Select Profile Photo");
        fileChooser.getExtensionFilters().addAll(
                new FileChooser.ExtensionFilter("Image Files", "*.png", "*.jpg", "*.jpeg")
        );
        File selectedFile = fileChooser.showOpenDialog(dialogStage);
        if (selectedFile != null) {
            try {
                String imagePath = selectedFile.toURI().toString();
                utilizator.setUrl(imagePath);
                service.updateUtilizator(utilizator);

                MessageAlert.showMessage(dialogStage, Alert.AlertType.INFORMATION, "Photo Uploaded", "Profile photo has been updated.");

            } catch (Exception e) {
                MessageAlert.showErrorMessage(dialogStage, "Error uploading photo: " + e.getMessage());
            }
        }
    }
}
