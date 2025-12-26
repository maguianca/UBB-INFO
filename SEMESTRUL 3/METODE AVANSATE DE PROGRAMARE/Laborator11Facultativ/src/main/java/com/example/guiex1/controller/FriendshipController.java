package com.example.guiex1.controller;
import com.example.guiex1.domain.MessageManager;
import com.example.guiex1.domain.Utilizator;
import com.example.guiex1.services.MessageService;
import com.example.guiex1.services.UtilizatorService;
import com.example.guiex1.utils.paging.Page;
import com.example.guiex1.utils.paging.Pageable;
import javafx.scene.control.*;
import javafx.scene.layout.HBox;
import javafx.application.Platform;
import java.util.Optional;
import com.example.guiex1.domain.Friendship;
import com.example.guiex1.utils.events.UtilizatorEntityChangeEvent;
import com.example.guiex1.utils.observer.Observer;
import javafx.beans.property.SimpleStringProperty;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.TextField;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.layout.AnchorPane;
import javafx.stage.Stage;
import javafx.scene.control.Alert;
import javafx.scene.control.ButtonType;

import java.io.IOException;
import java.time.LocalDateTime;
import java.util.*;
import java.util.stream.Collectors;

import javafx.scene.image.ImageView;
import javafx.util.Pair;


public class FriendshipController implements Observer<UtilizatorEntityChangeEvent> {
    UtilizatorService service;
    MessageService messageService;
    ObservableList<Utilizator> modelRequest= FXCollections.observableArrayList();
    ObservableList<Utilizator> modelFriends = FXCollections.observableArrayList();
    Stage dialogStage;
    Utilizator utilizator;
    private List<LocalDateTime> dateList = new ArrayList<>();
    private List<LocalDateTime> dateRequest = new ArrayList<>();
    @FXML
    private Button previousButton;
    @FXML
    private Button nextButton;
    @FXML
    TableView<Utilizator> FriendsRequest;
    @FXML
    TableView<Utilizator> FriendsList;
    @FXML
    TableColumn<Utilizator,String> LFirstName;
    @FXML
    TableColumn<Utilizator,String> LLastName;
    @FXML
    TableColumn<Utilizator,String> LDate;
    @FXML
    TableColumn<Utilizator,String> RFirstName;
    @FXML
    TableColumn<Utilizator,String> RLastName;
    @FXML
    TableColumn<Utilizator,String> RDate;
    @FXML
    TableColumn<Utilizator,String> RStatus;
    @FXML
    TextField profilefield;
    @FXML
    ImageView profilepic;
    @FXML
    private Label pageLabel;
    @FXML
    private TableColumn<Utilizator, Void> actionsColumn;  // Corrected type
    MessageManager messageManager;
    Integer currentPage = 1;
    private static final Integer PAGE_SIZE = 2;


    public void setService(UtilizatorService service, Stage stage, Utilizator u, MessageService messageService,MessageManager messageManager) {
        this.service = service;
        this.dialogStage=stage;
        this.utilizator =u;
        initModel();
        if (null != u) {
            setFields(u);

        }
        this.service.addObserver(this);
        this.messageService=messageService;
        this.messageManager=messageManager;
        showNewFriendRequests();
        populateFriendList();
    }
    private void setFields(Utilizator u)
    {
        profilefield.setText(u.getFirstName()+" "+u.getLastName());
        profilepic.setImage(new javafx.scene.image.Image(getClass().getResource("/com/example/guiex1/images/mpp_pic.png").toString()));

    }

    @FXML
    public void initialize() {

        LFirstName.setCellValueFactory(new PropertyValueFactory<>("firstName"));
        LLastName.setCellValueFactory(new PropertyValueFactory<>("lastName"));
        FriendsList.setItems(modelFriends);


        RFirstName.setCellValueFactory(new PropertyValueFactory<>("firstName"));
        RLastName.setCellValueFactory(new PropertyValueFactory<>("lastName"));
        RDate.setCellValueFactory(new PropertyValueFactory<>("date"));
        RStatus.setCellValueFactory(new PropertyValueFactory<>("status"));
        actionsColumn.setCellValueFactory(new PropertyValueFactory<>("actions"));

        //actionsColumn.setCellFactory(new FriendRequestCellFactory(utilizator,service));
        /*LDate.setCellValueFactory(data -> {
            int index = modelFriends.indexOf(data.getValue());
            if (index >= 0 && index < dateList.size()) {
                return new SimpleStringProperty(dateList.get(index).toString());
            }
            return new SimpleStringProperty("");
        });*/
        RDate.setCellValueFactory(data -> {
            int index = modelRequest.indexOf(data.getValue());
            if (index >= 0 && index < dateRequest.size()) {
                return new SimpleStringProperty(dateRequest.get(index).toString());
            }
            return new SimpleStringProperty("");
        });
        RStatus.setCellValueFactory(data -> new SimpleStringProperty("pending"));
        actionsColumn.setCellFactory(param -> new TableCell<Utilizator, Void>() {
            private final Button acceptButton = new Button("✓");
            private final Button declineButton = new Button("X");
            {
                acceptButton.setStyle("-fx-background-color: #4CAF50; -fx-text-fill: white;");
                declineButton.setStyle("-fx-background-color: #F44336; -fx-text-fill: white;");

                acceptButton.setOnAction(event -> handleAccept(getTableView().getItems().get(getIndex())));
                declineButton.setOnAction(event -> handleDecline(getTableView().getItems().get(getIndex())));
            }

            @Override
            protected void updateItem(Void item, boolean empty) {
                super.updateItem(item, empty);
                if (empty) {
                    setGraphic(null);
                } else {
                    HBox actionButtons = new HBox(5, acceptButton, declineButton);
                    setGraphic(actionButtons);
                }
            }
        });

    }
    private void handleAccept(Utilizator friendRequest) {
        Long id = friendRequest.getId();
        System.out.println("Accepted: " + friendRequest + " Id: " + id);

        service.addFriendship(utilizator.getId(), id);
        Long requestIdToDelete = service.getRequestId(utilizator.getId(), id).orElse(null);
        if (requestIdToDelete != null) {
            service.deleteRequest(requestIdToDelete);
        }
        Platform.runLater(() -> {
            modelRequest.remove(friendRequest);
            FriendsRequest.refresh();
        });
    }

    private void handleDecline(Utilizator friendRequest) {
        Long id = friendRequest.getId();
        System.out.println("Declined: " + friendRequest + " Id: " + id);

        Long requestIdToDelete = service.getRequestId(utilizator.getId(), id).orElse(null);
        if (requestIdToDelete != null) {
            service.deleteRequest(requestIdToDelete);
        }

        Platform.runLater(() -> {
            modelRequest.remove(friendRequest);
            FriendsRequest.refresh();
        });
    }
    private void clearFriendList() {
        FriendsList.getItems().clear();
    }
    private void createFriendRow(Utilizator friend) {
        if (friend != null && !modelFriends.contains(friend)) { // Exclude duplicatele
            modelFriends.add(friend);
        }
    }

    private void populateFriendList(){
        Pageable pageable = new Pageable(currentPage,PAGE_SIZE);
        Page<Utilizator> friendList = service.getFriendsForUserID(utilizator.getId(),pageable);
        clearFriendList();
        for(Utilizator friend: friendList.getElementsOnPage()){
            createFriendRow(friend);
        }
        dateList = service.getDates(utilizator.getId())
                .stream()
                .skip((currentPage - 1) * PAGE_SIZE)
                .limit(PAGE_SIZE)
                .collect(Collectors.toList());
        LDate.setCellValueFactory(data -> {
            int index = modelFriends.indexOf(data.getValue());
            if (index >= 0 && index < dateList.size()) {
                return new SimpleStringProperty(dateList.get(index).toString());
            }
            return new SimpleStringProperty("");
        });
        Integer totalNumberOfPages = (int)(Math.ceil((double)friendList.getTotalNumberElements() / PAGE_SIZE));
        pageLabel.setText("Page "+ currentPage + "/" + totalNumberOfPages);
        if(currentPage == 1)
            previousButton.setDisable(true);
        else
            previousButton.setDisable(false);
        if(currentPage == totalNumberOfPages)
            nextButton.setDisable(true);
        else
            nextButton.setDisable(false);
    }
    private void initModel() {
        /*List<Long> friendIds = service.getFriends(utilizator.getId());
        dateList=service.getDates(utilizator.getId());
        List<Utilizator> friends = friendIds.stream()
                .map(id -> service.getUserById(id)) // Get user by ID
                .filter(Optional::isPresent)
                .map(Optional::get)
                .collect(Collectors.toList());
        modelFriends.setAll(friends);
        FriendsList.setItems(modelFriends);
        */

        List<Long> requestIds = service.getRequests(utilizator.getId());
        dateRequest=service.getRequestDates(utilizator.getId());
        List<Utilizator> request = requestIds.stream()
                .map(id -> service.getUserById(id)) // Get user by ID
                .filter(Optional::isPresent)
                .map(Optional::get)
                .collect(Collectors.toList());
        modelRequest.setAll(request);
        FriendsRequest.setItems(modelRequest);

    }

    @Override
    public void update(UtilizatorEntityChangeEvent utilizatorEntityChangeEvent) {
        initModel();
        showNewFriendRequests();
        populateFriendList();
    }
    private void showNewFriendRequests() {
        List<Pair<Utilizator, Boolean>> newRequests = messageManager.getNewFriendRequests(utilizator);

        if (!newRequests.isEmpty()) {
            StringBuilder notificationMessage = new StringBuilder("You have new friend requests from:\n");
            for (Pair<Utilizator, Boolean> request : newRequests) {
                System.out.println(request);
                String cuv=request.getKey().getFirstName()+" "+request.getKey().getLastName();
                notificationMessage.append("- ").append(cuv).append("\n");
            }
            Alert alert = new Alert(Alert.AlertType.INFORMATION);
            alert.setTitle("New Friend Requests");
            alert.setHeaderText(null);
            alert.setContentText(notificationMessage.toString());
            alert.showAndWait();

            //messageManager.markRequestsAsSeen(utilizator);
            System.out.println("Before: " + messageManager.getNewFriendRequests(utilizator));
            messageManager.markRequestsAsSeen(utilizator);
            System.out.println("After: " + messageManager.getNewFriendRequests(utilizator));

        }
    }


    public void handleBack(ActionEvent actionEvent) {
        dialogStage.close();
    }

    public void handleDelete(ActionEvent actionEvent) {
        Utilizator selectedFriend = FriendsList.getSelectionModel().getSelectedItem();

        if (selectedFriend != null) {
            Alert alert = new Alert(Alert.AlertType.CONFIRMATION);
            alert.setTitle("Delete Friendship");
            alert.setHeaderText("Are you sure you want to remove this friend?");
            alert.setContentText("This action cannot be undone.");
            ButtonType yesButton = new ButtonType("Yes");
            ButtonType noButton = new ButtonType("No");
            alert.getButtonTypes().setAll(yesButton, noButton);
            Optional<ButtonType> result = alert.showAndWait();

            if (result.isPresent()) {
                ButtonType clickedButton = result.get();

                if (clickedButton == yesButton) {
                    try {
                        Long Id1 = selectedFriend.getId();
                        Long Id2 = utilizator.getId();

                        Long friendshipId = service.getFrId(Id1, Id2).orElse(null);
                        System.out.println("Id-ul prieteniei"+friendshipId);
                        if (friendshipId != null) {
                            Optional<Friendship> deletedFriendship = service.deleteFriendship(friendshipId);
                            if (deletedFriendship.isEmpty()) {
                                initModel();
                                System.out.println("Friend removed successfully.");
                            } else {
                                System.out.println("Failed to remove the friend. Please try again.");
                            }
                        } else {
                            System.out.println("No friendship found between the selected users.");
                        }
                        populateFriendList();
                    } catch (Exception e) {
                        System.err.println("Error occurred while deleting friendship: " + e.getMessage());
                        Alert errorAlert = new Alert(Alert.AlertType.ERROR);
                        errorAlert.setTitle("Error");
                        errorAlert.setHeaderText("Failed to remove friendship");
                        errorAlert.setContentText("An error occurred while trying to remove this friend. Please try again.");
                        errorAlert.showAndWait();
                    }
                } else if (clickedButton == noButton) {
                    System.out.println("Friendship deletion canceled.");
                } else {
                    System.out.println("Unexpected button clicked.");
                }
            } else {
                System.out.println("No result returned from the alert.");
            }
        } else {
            System.out.println("No friend selected.");
        }
    }



    public void handleAddNewFriend(ActionEvent actionEvent) {
        List<Utilizator>friends = service.getRestUsers(utilizator.getId());
        try {
            FXMLLoader loader = new FXMLLoader(getClass().getResource("/com/example/guiex1/views/AddNewFriendship.fxml"));
            AnchorPane root = loader.load();
            AddFriendshipController editUserController = loader.getController();
            Stage dialogStage = new Stage();
            dialogStage.setTitle("Add New Friendship");
            editUserController.setService(service, dialogStage, utilizator,friends,messageManager);
            dialogStage.setScene(new Scene(root));
            dialogStage.show();
        } catch (IOException e) {
            e.printStackTrace();
            Alert alert = new Alert(Alert.AlertType.ERROR);
            alert.setTitle("Error");
            alert.setHeaderText("Could not load the users window");
            alert.setContentText(e.getMessage());
            alert.showAndWait();
        }
    }

    public void handleChat(ActionEvent actionEvent) {
        System.out.println("aici");
        if (utilizator == null) {
            System.out.println("Utilizator is null in handleChat.");
        } else if (service == null) {
            System.out.println("UtilizatorService is null in handleChat.");
        } else {
            System.out.println("peste");
            try {
                FXMLLoader loader = new FXMLLoader(getClass().getResource("/com/example/guiex1/views/ChatView.fxml"));
                AnchorPane root = loader.load();
                ChatController chatController = loader.getController();
                Stage dialogStage = new Stage();
                dialogStage.setTitle("Chat Window");
                chatController.setService(service,messageService, dialogStage, utilizator);
                dialogStage.setScene(new Scene(root));
                dialogStage.show();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }

    }

    public void handlePrevious(ActionEvent actionEvent) {
        currentPage--;
        populateFriendList();
    }

    public void handleNext(ActionEvent actionEvent) {
        currentPage++;
        populateFriendList();

    }
}
