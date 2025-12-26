package com.example.guiex1.controller;

import com.example.guiex1.domain.Page;
import com.example.guiex1.domain.Pageable;
import com.example.guiex1.domain.UserWithDateDTO;
import com.example.guiex1.domain.Utilizator;
import com.example.guiex1.services.ChatService;
import com.example.guiex1.services.UserAccountService;
import com.example.guiex1.utils.events.UtilizatorEntityChangeEvent;
import com.example.guiex1.utils.observer.Observer;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.Label;
import javafx.scene.control.SplitPane;
import javafx.scene.layout.*;
import javafx.stage.Stage;
import javafx.scene.control.Button;

import java.io.IOException;
import java.time.LocalDate;
import java.util.List;
import java.util.Optional;

public class AccountViewController implements Observer<UtilizatorEntityChangeEvent> {
    @FXML
    private Button previousButton;
    @FXML
    private Button nextButton;
    @FXML
    private VBox addFriendsList;
    @FXML
    private VBox requestList;
    @FXML
    private VBox friendList;
    @FXML
    private Label pageLabel;

    Utilizator user;
    Stage primaryStage;
    UserAccountService service;
    Integer currentPage = 1;
    private static final Integer PAGE_SIZE = 2;


    public void setNecessaryAtributes(Stage primaryStage, UserAccountService utilizatorAccountService, Utilizator usr) {
        this.primaryStage = primaryStage;
        this.service = utilizatorAccountService;
        service.addObserver(this);
        this.user = usr;
        populateFriendList();
        populateFriendshipRequestList();
        populateAddFriendList();
    }

    private void populateAddFriendList() {
        List<Utilizator> usersToAddAsFriends = service.usersWhoAreNotFriendsOrRequestedForAUserId(user.getId());
        for(Utilizator userToAddToList: usersToAddAsFriends){
            createAddFriendsRow(userToAddToList);
        }
    }


    private void populateFriendshipRequestList() {
        List<UserWithDateDTO> usersWhoRequestedFriendship = service.allUsersWhoRequestedFriendship(user.getId());
        for(UserWithDateDTO userDTO: usersWhoRequestedFriendship){
            createFriendshipRequestRow(userDTO.getUser(),userDTO.getDate());
        }
    }

    private void populateFriendList() {
        Pageable pageable = new Pageable(currentPage,PAGE_SIZE);
        Page<Utilizator> friendList = service.getFriendsForUserID(user.getId(),pageable);
        clearFriendList();
        for(Utilizator friend: friendList.getElementsOnPage()){
            createFriendRow(friend);
        }
        Integer totalNumberOfPages = (int)(Math.ceil((double)friendList.getTotalNumberOfElements() / PAGE_SIZE));
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
    Long getUserIdFromLabelWithFirstAndLastName(Label firstAndLastNameLabel){
        String[] tokenizeUserToUnfriend = firstAndLastNameLabel.getText().split(" ");
        String userToUnfriendFirstName = tokenizeUserToUnfriend[0];
        String userToUnfriendLastName = tokenizeUserToUnfriend[1];
        return service.findIdByName(userToUnfriendFirstName, userToUnfriendLastName);
    }
    private void createFriendshipRequestRow(Utilizator friend, LocalDate requestDate){
        HBox friendshipRow = new HBox();
        friendshipRow.setPrefWidth(300);
        friendshipRow.setMaxWidth(300);
        friendshipRow.setMinWidth(300);
        Region spacer = new Region();
        HBox.setHgrow(spacer, Priority.ALWAYS);
        Label requestDateLabel = new Label(requestDate.toString());
        Label friendNameLabel = new Label(friend.getFirstName() + " " + friend.getLastName());
        Button deleteRequest = new Button("✗");
        Button acceptRequest = new Button("✓");
        deleteRequest.setOnAction(this::handleDeleteFriendshipRequest);
        acceptRequest.setOnAction(this::handleAcceptFriendshipRequest);
        friendshipRow.getChildren().addAll(requestDateLabel,spacer,friendNameLabel,acceptRequest,deleteRequest);
        requestList.getChildren().add(friendshipRow);
    }

    private void createAddFriendsRow(Utilizator friend){
        HBox addFriendsRow = new HBox();
        addFriendsRow.setPrefWidth(300);
        addFriendsRow.setMaxWidth(300);
        addFriendsRow.setMinWidth(300);
        Region spacer = new Region();
        HBox.setHgrow(spacer,Priority.ALWAYS);

        Label userName = new Label(friend.getFirstName() + " " + friend.getLastName());
        Button buttonToRequest = new Button("Add");
        buttonToRequest.setOnAction(this::handleAddFriend);
        addFriendsRow.getChildren().addAll(userName,buttonToRequest);
        addFriendsList.getChildren().add(addFriendsRow);
    }

    private void handleAddFriend(ActionEvent actionEvent) {
        Button clickButton = (Button) actionEvent.getSource();

        HBox parentBox = (HBox) clickButton.getParent();

        Label nameOfUserToRequest = (Label) parentBox.getChildren().get(0);

        Long IDOfUserToRequest = getUserIdFromLabelWithFirstAndLastName(nameOfUserToRequest);
        if(IDOfUserToRequest != null){
            service.requestFriendship(user.getId(),IDOfUserToRequest);
        }
    }

    private void handleAcceptFriendshipRequest(ActionEvent actionEvent) {
        Button clickButton = (Button) actionEvent.getSource();

        HBox parentBox = (HBox) clickButton.getParent();

        Label userToAcceptFriendshipRequest = (Label) parentBox.getChildren().get(2);

        Long userToAcceptFriendshipRequestId = getUserIdFromLabelWithFirstAndLastName(userToAcceptFriendshipRequest);
        if(userToAcceptFriendshipRequestId != null){
            service.acceptFriendRequest(user.getId(),userToAcceptFriendshipRequestId);
        }
    }

    private void handleDeleteFriendshipRequest(ActionEvent actionEvent) {
        Button clickButton = (Button) actionEvent.getSource();

        HBox parentBox = (HBox) clickButton.getParent();

        Label userToDeleteFriendship = (Label) parentBox.getChildren().get(2);

        Long userToDeleteFriendshipId = getUserIdFromLabelWithFirstAndLastName(userToDeleteFriendship);
        if(userToDeleteFriendshipId != null){
            service.deleteFriendRequest(userToDeleteFriendshipId,user.getId());
        }
    }

    private void createFriendRow(Utilizator friend){
        HBox friendRow = new HBox();
        friendRow.setPrefWidth(200);
        friendRow.setMaxWidth(200);
        friendRow.setMinWidth(200);
        Region spacer = new Region();
        HBox.setHgrow(spacer, Priority.ALWAYS);

        Label friendNameLabel = new Label(friend.getFirstName() + " " + friend.getLastName());
        Button deleteFriend = new Button("Unfriend");
        deleteFriend.setOnAction(this::handleUnfriend);
        friendRow.getChildren().addAll(friendNameLabel,spacer,deleteFriend);
        friendList.getChildren().add(friendRow);
    }


    private void handleUnfriend(ActionEvent actionEvent) {
        Button clickButton = (Button) actionEvent.getSource();

        HBox parentBox = (HBox) clickButton.getParent();

        Label userToUnfriend = (Label) parentBox.getChildren().get(0);

        Long userToUnfriendId = getUserIdFromLabelWithFirstAndLastName(userToUnfriend);
        if(userToUnfriendId != null){
            service.removeFriendship(user.getId(),userToUnfriendId);
        }
    }



    @Override
    public void update(UtilizatorEntityChangeEvent utilizatorEntityChangeEvent) {
        user = service.findOne(user.getId()).get();
        clearFriendList();
        populateFriendList();

        clearFriendshipRequestList();
        populateFriendshipRequestList();

        clearAddFriendsList();
        populateAddFriendList();
    }

    private void clearFriendList() {
        friendList.getChildren().clear();
    }

    private void clearFriendshipRequestList(){
        requestList.getChildren().clear();
    }

    private void clearAddFriendsList(){
        addFriendsList.getChildren().clear();
    }

    public void handleChatButton(ActionEvent actionEvent) throws IOException {
        changeStageToChatView();
    }

    private void changeStageToChatView() throws IOException {
        FXMLLoader fxmlLoader = new FXMLLoader(SignInController.class.getResource("../views/chat-view.fxml"));
        SplitPane chatLayout = fxmlLoader.load();
        primaryStage.setScene(new Scene(chatLayout));

        ChatViewController chatViewController = fxmlLoader.getController();
        chatViewController.setNecessaryAtributes(primaryStage, ChatService.getInstance(),user);
    }

    public void handlePreviousButton(ActionEvent actionEvent) {
        currentPage--;
        populateFriendList();
    }

    public void handleNextButton(ActionEvent actionEvent) {
        currentPage++;
        populateFriendList();
    }
}
