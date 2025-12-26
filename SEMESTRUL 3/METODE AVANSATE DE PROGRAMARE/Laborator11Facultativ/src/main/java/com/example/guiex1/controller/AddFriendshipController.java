package com.example.guiex1.controller;

import com.example.guiex1.domain.Friendship;
import com.example.guiex1.domain.MessageManager;
import com.example.guiex1.domain.Utilizator;
import com.example.guiex1.services.UtilizatorService;
import com.example.guiex1.utils.events.UtilizatorEntityChangeEvent;
import com.example.guiex1.utils.observer.Observer;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.collections.transformation.FilteredList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.*;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.image.ImageView;
import javafx.stage.Stage;

import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.List;
import java.util.Optional;
import java.util.stream.Collectors;

public class AddFriendshipController {
    UtilizatorService service;
    ObservableList<Utilizator> modelFriends = FXCollections.observableArrayList();
    Stage dialogStage;
    Utilizator utilizator;
    List<Utilizator> friends;
    @FXML
    TableView<Utilizator> tableUsers;
    @FXML
    TableColumn<Utilizator,String> tableColumnFirstName;
    @FXML
    TableColumn<Utilizator,String> tableColumnLastName;
    @FXML
    TextField fieldNume;
    @FXML
    TextField fieldPrenume;
    MessageManager messageManager;
    public void setService(UtilizatorService service, Stage stage, Utilizator u, List<Utilizator> friends, MessageManager messageManager) {
        this.service = service;
        this.dialogStage=stage;
        this.utilizator =u;
        this.friends=friends;
        this.messageManager = messageManager;
        initModel();

    }
    @FXML

    public void initialize() {
        tableColumnFirstName.setCellValueFactory(new PropertyValueFactory<>("firstName"));
        tableColumnLastName.setCellValueFactory(new PropertyValueFactory<>("lastName"));
        tableUsers.setItems(modelFriends);
        tableUsers.getSelectionModel().selectedItemProperty().addListener((observable, oldValue, newValue) -> {
            if (newValue != null) {
                fieldNume.setText(newValue.getFirstName());
                fieldPrenume.setText(newValue.getLastName());
            }
            else{
                fieldNume.setText("");
                fieldPrenume.setText("");
            }
        });
        FilteredList<Utilizator> filteredData = new FilteredList<>(modelFriends, b -> true);

    }
    private void initModel() {

        friends.forEach(friend -> System.out.println(friend.getId()));
        modelFriends.setAll(friends);
        tableUsers.setItems(modelFriends);
    }
    public void handleAddFriend(ActionEvent actionEvent) {
        Utilizator selectedUser = tableUsers.getSelectionModel().getSelectedItem();
        if (selectedUser != null) {
            try {
                service.addRequest(utilizator.getId(), selectedUser.getId());
                System.out.println(utilizator.getId());
                System.out.println(selectedUser.getId());
                Alert alert = new Alert(Alert.AlertType.INFORMATION);
                alert.setTitle("Success");
                alert.setHeaderText(null);
                alert.setContentText("The Friend Request was sent !");
                alert.showAndWait();
                this.dialogStage.close();
            } catch (Exception e) {
                Alert alert = new Alert(Alert.AlertType.ERROR);
                alert.setTitle("Error");
                alert.setHeaderText("Could not add friendship");
                alert.setContentText(e.getMessage());
                alert.showAndWait();
            }
            messageManager.addFriendRequest(utilizator,selectedUser);
        } else {
            Alert alert = new Alert(Alert.AlertType.WARNING);
            alert.setTitle("Warning");
            alert.setHeaderText("No User Selected");
            alert.setContentText("Please select a user to add as a friend.");
            alert.showAndWait();
        }
    }

    public void handleBack(ActionEvent actionEvent) {
        this.dialogStage.close();
    }
}
