package com.example.guiex1.controller;

import com.example.guiex1.domain.*;
import com.example.guiex1.services.MessageService;
import com.example.guiex1.services.UtilizatorService;
import com.example.guiex1.utils.events.UtilizatorEntityChangeEvent;
import com.example.guiex1.utils.observer.Observer;
import javafx.beans.property.SimpleStringProperty;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.collections.transformation.FilteredList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.*;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.util.Pair;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.layout.AnchorPane;
import javafx.stage.Stage;
import java.io.IOException;

import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.time.LocalDateTime;
import java.util.*;
import java.util.stream.Collectors;
import java.util.stream.StreamSupport;

public class UtilizatoriController implements Observer<UtilizatorEntityChangeEvent>{
    UtilizatorService service;
    MessageService messageService;
    MessageManager messageManager;
    @FXML
    TextField fieldpass;
    @FXML
    TextField fieldusername;
    /*@FXML
    TextField fieldNume;
    @FXML
    TextField fieldPrenume;*/


    public void setUtilizatorService(UtilizatorService service,MessageService messageService,MessageManager sessionManager) {
        this.service = service;
        initModel();
        this.service.addObserver(this);
        this.messageService = messageService;
        this.messageManager = sessionManager;
    }

    @FXML
    public void initialize() {

    }

    private void initModel() {
        //List<Utilizator> all_users= StreamSupport.stream(service.getAll().spliterator(), false).collect(Collectors.toList());

    }

    @Override
    public void update(UtilizatorEntityChangeEvent utilizatorEntityChangeEvent) {
        initModel();
    }

    public void handleConnectButton(ActionEvent actionEvent) {
        //String firstName = fieldNume.getText();
        //String lastName = fieldPrenume.getText();
        String password = hashPassword(fieldpass.getText());
        String username = fieldusername.getText();
        Utilizator user = service.findbyName(username).orElse(null);
        if (user != null && user.getPassword().equals(password)) {
            try {
                FXMLLoader loader = new FXMLLoader(getClass().getResource("/com/example/guiex1/views/FriendshipsView.fxml"));
                AnchorPane root = loader.load();
                FriendshipController editUserController = loader.getController();
                Stage dialogStage = new Stage();
                dialogStage.setTitle("Friendship Manager");
                editUserController.setService(service, dialogStage, user,messageService,messageManager);
                dialogStage.setScene(new Scene(root));
                dialogStage.show();
            } catch (IOException e) {
                e.printStackTrace();
                Alert alert = new Alert(Alert.AlertType.ERROR);
                alert.setTitle("Error");
                alert.setHeaderText("Could not load the Friendship window");
                alert.setContentText(e.getMessage());
                alert.showAndWait();
            }
        } else {
            Alert noSelectionAlert = new Alert(Alert.AlertType.WARNING);
            noSelectionAlert.setTitle("The name or password field is incorrect");
            noSelectionAlert.setHeaderText("Please put a valid user to connect.");
            noSelectionAlert.setContentText("Error");
            noSelectionAlert.showAndWait();
        }
    }

    public void handleDeleteUser(ActionEvent actionEvent) {
            //String firstName = fieldPrenume.getText();
            //String lastName = fieldNume.getText();
            String username = fieldusername.getText();
            String password = fieldpass.getText();
            Utilizator user = service.findbyName(username).orElse(null);
            if (user != null && user.getPassword().equals(password)) {
                Alert alert = new Alert(Alert.AlertType.CONFIRMATION);
                alert.setTitle("Delete User");
                alert.setHeaderText("Are you sure you want to delete this user?");
                alert.setContentText("This action cannot be undone.");

                Optional<ButtonType> result = alert.showAndWait();
                if (result.isPresent() && result.get() == ButtonType.OK) {
                    Utilizator deleted = service.deleteUtilizator(user.getId());
                    //initModel();
                }
            } else {
                Alert noSelectionAlert = new Alert(Alert.AlertType.WARNING);
                noSelectionAlert.setTitle("No User Selected");
                noSelectionAlert.setHeaderText("Please select a user to delete.");
                noSelectionAlert.setContentText("You must select a user before deleting.");
                noSelectionAlert.showAndWait();
            }
    }
    public void handleUpdateUser(ActionEvent actionEvent) {
        //String firstName = fieldPrenume.getText();
        //String lastName = fieldNume.getText();
        String username = fieldusername.getText();
        String password = hashPassword(fieldpass.getText());
        Utilizator user = service.findbyName(username).orElse(null);
        if (user != null && user.getPassword().equals(password)) {
            try {
                FXMLLoader loader = new FXMLLoader(getClass().getResource("/com/example/guiex1/views/UpdateUsers.fxml"));
                AnchorPane root = loader.load();
                EditUserController editUserController = loader.getController();
                Stage dialogStage = new Stage();
                dialogStage.setTitle("Edit User");
                editUserController.setService(service, dialogStage, user);
                dialogStage.setScene(new Scene(root));
                dialogStage.show();
            } catch (IOException e) {
                e.printStackTrace();
                Alert alert = new Alert(Alert.AlertType.ERROR);
                alert.setTitle("Error");
                alert.setHeaderText("Could not load the Edit User window");
                alert.setContentText(e.getMessage());
                alert.showAndWait();
            }
        } else {
            Alert noSelectionAlert = new Alert(Alert.AlertType.WARNING);
            noSelectionAlert.setTitle("No User Selected");
            noSelectionAlert.setHeaderText("Please select a user to update.");
            noSelectionAlert.setContentText("You must select a user before updating.");
            noSelectionAlert.showAndWait();
        }
    }


    public void handleAddUser(ActionEvent actionEvent) {
        try {
            FXMLLoader loader = new FXMLLoader(getClass().getResource("/com/example/guiex1/views/AddUsers.fxml"));
            AnchorPane root = loader.load();
            AddUserController editUserController = loader.getController();
            Stage dialogStage = new Stage();
            dialogStage.setTitle("Add New User");
            editUserController.setService(service, dialogStage);
            dialogStage.setScene(new Scene(root));
            dialogStage.show();
        } catch (IOException e) {
            e.printStackTrace();
            Alert alert = new Alert(Alert.AlertType.ERROR);
            alert.setTitle("Error");
            alert.setHeaderText("Could not load the Edit User window");
            alert.setContentText(e.getMessage());
            alert.showAndWait();
        }
    }
    public static String hashPassword(String password) {
        try {
            MessageDigest md = MessageDigest.getInstance("SHA-256");
            byte[] hashedBytes = md.digest(password.getBytes());
            StringBuilder sb = new StringBuilder();
            for (byte b : hashedBytes) {
                sb.append(String.format("%02x", b));
            }
            return sb.toString();
        } catch (NoSuchAlgorithmException e) {
            throw new RuntimeException("Eroare la hash-uirea parolei", e);
        }
    }
}

   