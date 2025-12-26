package com.example.guiex1.controller;

import com.example.guiex1.domain.Utilizator;
import com.example.guiex1.domain.ValidationException;
import com.example.guiex1.services.UtilizatorService;
import com.example.guiex1.utils.events.UtilizatorEntityChangeEvent;
import com.example.guiex1.utils.observer.Observer;
import javafx.beans.property.SimpleStringProperty;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.*;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.util.Pair;

import java.util.HashMap;
import java.util.Optional;
import java.time.LocalDateTime;
import java.util.ArrayList;



import java.util.List;
import java.util.stream.Collectors;
import java.util.stream.StreamSupport;
import java.util.*;
public class UtilizatorController implements Observer<UtilizatorEntityChangeEvent> {
    public TextField fieldNume;
    public TextField fieldPrenume;
    UtilizatorService service;
    ObservableList<Utilizator> model = FXCollections.observableArrayList();
    ObservableList<Utilizator> modelFriends = FXCollections.observableArrayList();

    @FXML
    TableView<Utilizator> tableView;
    @FXML
    TableView<Utilizator> tableFriendship;
    @FXML
    TableColumn<Utilizator,String> tableColumnFirstName;
    @FXML
    TableColumn<Utilizator,String> tableColumnLastName;
    @FXML
    TableColumn<Utilizator,String> tableColumnId;
    @FXML
    TableColumn<Utilizator,String> tableColumnFirstName1;
    @FXML
    TableColumn<Utilizator,String> tableColumnLastName1;
    @FXML
    TableColumn<Utilizator,String> tableColumnId1;
    @FXML
    TableColumn<Utilizator,String> tableColumnDate;
    private List<LocalDateTime> dateList = new ArrayList<>();
    private final Map<Utilizator, Pair<Long,Long>> friendshipMap = new HashMap<>();

    public void setUtilizatorService(UtilizatorService service) {
        this.service = service;
        initModel();
        this.service.addObserver(this);
    }

    @FXML
    public void initialize() {
        tableColumnId.setCellValueFactory(new PropertyValueFactory<>("Id"));
        tableColumnFirstName.setCellValueFactory(new PropertyValueFactory<>("firstName"));
        tableColumnLastName.setCellValueFactory(new PropertyValueFactory<>("lastName"));
        tableView.setItems(model);

        tableColumnId1.setCellValueFactory(new PropertyValueFactory<>("Id"));
        tableColumnFirstName1.setCellValueFactory(new PropertyValueFactory<>("firstName"));
        tableColumnLastName1.setCellValueFactory(new PropertyValueFactory<>("lastName"));
        tableColumnDate.setCellValueFactory(new PropertyValueFactory<>("Date"));
        tableFriendship.setItems(modelFriends);

        tableView.getSelectionModel().selectedItemProperty().addListener((observable, oldValue, newValue) -> {
            if (newValue != null) {
                fieldNume.setText(newValue.getLastName());
                fieldPrenume.setText(newValue.getFirstName());
            }
            else{
                fieldNume.setText("");
                fieldPrenume.setText("");
            }
        });
        tableColumnDate.setCellValueFactory(data -> {
            int index = modelFriends.indexOf(data.getValue());
            if (index >= 0 && index < dateList.size()) {
                return new SimpleStringProperty(dateList.get(index).toString());
            }
            return new SimpleStringProperty("");
        });
    }

    private void initModel() {
        List<Utilizator> all_users=StreamSupport.stream(service.getAll().spliterator(), false).collect(Collectors.toList());
        model.setAll(all_users);
    }

    @Override
    public void update(UtilizatorEntityChangeEvent utilizatorEntityChangeEvent) {
        initModel();
    }

    public void handleDeleteUtilizator(ActionEvent actionEvent) {
        Utilizator user=(Utilizator) tableView.getSelectionModel().getSelectedItem();
        if (user!=null) {
            Utilizator deleted= service.deleteUtilizator(user.getId());
            initModel();
        }
    }

    public void handleUpdateUtilizator(ActionEvent actionEvent) {
        Utilizator user=tableView.getSelectionModel().getSelectedItem();
        if(user!=null){
            Utilizator updatedUser=new Utilizator(fieldPrenume.getText(),fieldNume.getText());
            updatedUser.setId(user.getId());
            try{
                service.updateUtilizator(updatedUser);
                initModel();
            }catch(ValidationException e){
                MessageAlert.showErrorMessage(null, e.getMessage());
            }
        }
    }

    public void handleAddUtilizator(ActionEvent actionEvent) {
        Utilizator addUser=new Utilizator(fieldPrenume.getText(),fieldNume.getText());
        try{
            service.addUtilizator(addUser);
            initModel();
        }catch(ValidationException e){
            MessageAlert.showErrorMessage(null, e.getMessage());
        }
    }

    public void handleAddFriendship(ActionEvent actionEvent) {
    }
    /*
    public void handleDeleteFriendship(ActionEvent actionEvent) {
        Utilizator selectedUser = tableView.getSelectionModel().getSelectedItem();
        Utilizator selectedFriend = tableFriendship.getSelectionModel().getSelectedItem();
            if (selectedFriend != null) {
                Long friendshipId = service.getFrId(selectedUser.getId(), selectedFriend.getId()).orElse(null);

                if (friendshipId != null) {
                    service.deleteFriendship(friendshipId);
                    MessageAlert.showMessage(null, Alert.AlertType.INFORMATION, "Success", "Friendship deleted successfully!");
                    handleLoadFriendships(actionEvent); // Refresh friendship list
                } else {
                    MessageAlert.showErrorMessage(null, "No friendship found for the selected user.");
                }
            } else {
                MessageAlert.showErrorMessage(null, "Select a friendship to delete!");
            }

    }*/
    public void handleDeleteFriendship(ActionEvent actionEvent) {
        Utilizator selectedUser = tableView.getSelectionModel().getSelectedItem();
        Utilizator selectedFriend = tableFriendship.getSelectionModel().getSelectedItem();

        if (selectedFriend != null) {
            Alert confirmationAlert = new Alert(Alert.AlertType.CONFIRMATION);
            confirmationAlert.setTitle("Confirm Friendship Deletion");
            confirmationAlert.setHeaderText("Are you sure you want to delete this friendship?");
            confirmationAlert.setContentText("Once deleted, this action cannot be undone.");

            Optional<ButtonType> result = confirmationAlert.showAndWait();

            if (result.isPresent() && result.get() == ButtonType.OK) {
                Long friendshipId = service.getFrId(selectedUser.getId(), selectedFriend.getId()).orElse(null);

                if (friendshipId != null) {
                    service.deleteFriendship(friendshipId);
                    MessageAlert.showMessage(null, Alert.AlertType.INFORMATION, "Success", "Friendship deleted successfully!");
                    handleLoadFriendships(actionEvent); // Refresh friendship list
                } else {
                    MessageAlert.showErrorMessage(null, "No friendship found for the selected user.");
                }
            } else {
                MessageAlert.showMessage(null, Alert.AlertType.INFORMATION, "Cancelled", "Friendship deletion cancelled.");
            }

        } else {
            MessageAlert.showErrorMessage(null, "Select a friendship to delete!");
        }
    }



    /*public void handleLoadFriendships(ActionEvent actionEvent) {
        Utilizator selectedUser = tableView.getSelectionModel().getSelectedItem();
        if (selectedUser != null) {
            List<Long> friendIds = service.getFriends(selectedUser.getId()); // Get friend IDs
            List<Utilizator> friends = friendIds.stream()
                    .map(id -> service.getUserById(id)) // Fetch each friend by ID
                    .filter(Optional::isPresent)
                    .map(Optional::get)
                    .collect(Collectors.toList());
            modelFriends.setAll(friends); // Update the observable list
            dateList =service.getDates(selectedUser.getId());
            for (int i = 0; i < modelFriends.size(); i++) {
                Utilizator friend = modelFriends.get(i);
                int hiddenId1 = friend.getId();
                int hiddenId2=selectedUser.getId();

                // Attach the hidden ID as a user-defined property to the row (using a map)
                //tableFriendship.getItems().get(i).setUserData(hiddenId); // Attach hidden data here
            }

        } else {
            MessageAlert.showErrorMessage(null, "Select a user to load friends!");
        }
    }*/
    public void handleLoadFriendships(ActionEvent actionEvent) {
        Utilizator selectedUser = tableView.getSelectionModel().getSelectedItem();
        if (selectedUser != null) {
            // Fetch friend IDs
            List<Long> friendIds = service.getFriends(selectedUser.getId());
            // Fetch friend details and populate the map
            List<Utilizator> friends = friendIds.stream()
                    .map(id -> service.getUserById(id)) // Get user by ID
                    .filter(Optional::isPresent)
                    .map(Optional::get)
                    .collect(Collectors.toList());

            // Clear and populate the map
            friendshipMap.clear();
            for (Utilizator friend : friends) {
                friendshipMap.put(friend, new Pair<>(selectedUser.getId(), friend.getId()));
            }

            // Update the observable list
            modelFriends.setAll(friends);
            tableFriendship.setItems(modelFriends);

            // Update the dates
            dateList = service.getDates(selectedUser.getId());
        } else {
            MessageAlert.showErrorMessage(null, "Select a user to load friends!");
        }
    }


}
