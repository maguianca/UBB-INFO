package com.example.guiex1.controller;

import com.example.guiex1.domain.ChatUserDTO;
import com.example.guiex1.domain.Message;
import com.example.guiex1.domain.Utilizator;
import com.example.guiex1.services.ChatService;
import com.example.guiex1.services.UserAccountService;
import com.example.guiex1.utils.events.UtilizatorEntityChangeEvent;
import com.example.guiex1.utils.observer.Observer;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.ListView;
import javafx.scene.control.TextField;
import javafx.scene.layout.*;
import javafx.stage.Stage;

import java.io.IOException;
import java.util.List;

public class ChatViewController implements Observer<UtilizatorEntityChangeEvent> {
    @FXML
    private Button backToAccountViewButton;
    @FXML
    private VBox messageListVBox;
    @FXML
    private TextField textFieldChat;
    @FXML
    private Button sendMessageButton;
    @FXML
    private ListView<String> friendListView;
    @FXML
    private VBox messageVBox;
    ChatService service;
    Stage currentStage;
    Utilizator user;

    public void setNecessaryAtributes(Stage currentStage, ChatService service, Utilizator user){
        this.service = service;
        this.currentStage = currentStage;
        this.user = user;
        service.addObserver(this);
        loadUI();
    }

    private void loadUI() {
        loadFriendChatList();
    }

    private void loadFriendChatList() {
        List<ChatUserDTO> chatOptions = service.getChatOptions(user.getId());

        for(ChatUserDTO chatOption: chatOptions){
            createChatOptionRow(chatOption.getFirstName(),chatOption.getLastName());
        }
    }

    private void createChatOptionRow(String firstName, String lastName) {
        friendListView.getItems().add(firstName + " " + lastName);
    }

    public void handleSelection() {
        String selectedUser = friendListView.getSelectionModel().getSelectedItem();
        Long idToChatWith = getUserIdWithFirstAndLastName(selectedUser);
        clearMessageVBox();
        loadMessages(user.getId(),idToChatWith);

    }

    private void loadMessages(Long id, Long idToChatWith) {
        List<Message> messageList = service.getMessagesSorted(id,idToChatWith);
        for(Message message: messageList){
            if(message.getSender().getId() == user.getId())
                createSentMessageRow(message.getMessageContent());
            else
                createReceivedMessageRow(message.getMessageContent());
        }
    }

    private void createSentMessageRow(String messageContent) {
        HBox messageHBox = new HBox();
        messageHBox.getStyleClass().add("received-message");
        Region spacer = new Region();
        HBox.setHgrow(spacer, Priority.ALWAYS);

        Label messageBody = new Label();
        messageBody.setText(messageContent);
        messageHBox.getChildren().addAll(spacer,messageBody);
        messageListVBox.getChildren().add(messageHBox);
    }


    private void createReceivedMessageRow(String messageContent) {
        HBox messageHBox = new HBox();
        messageHBox.getStyleClass().add("sent-message");
        Region spacer = new Region();
        HBox.setHgrow(spacer, Priority.ALWAYS);

        Label messageBody = new Label();
        messageBody.setText(messageContent);
        messageHBox.getChildren().addAll(messageBody,spacer);
        messageListVBox.getChildren().add(messageHBox);
    }

    Long getUserIdWithFirstAndLastName(String firstAndLAstName){
        String[] tokenizedUser = firstAndLAstName.split(" ");
        String firstName = tokenizedUser[0];
        String lastName = tokenizedUser[1];

        return service.findIdByName(firstName,lastName);
    }

    public void handleMessageSend(ActionEvent actionEvent) {
        String userToChatWithFullName = friendListView.getSelectionModel().getSelectedItem();
        String messageContent = textFieldChat.getText();
        service.addMessageFrom(user.getId(),getUserIdWithFirstAndLastName(userToChatWithFullName),messageContent);
        textFieldChat.clear();
    }

    public void handleBackButton(ActionEvent actionEvent)  {
        try{
            changeStageToAccountView(user);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
    private void changeStageToAccountView(Utilizator usr) throws IOException {
        UserAccountService utilizatorAccountService = UserAccountService.getInstance();
        FXMLLoader fxmlLoader = new FXMLLoader(SignInController.class.getResource("../views/account-view.fxml"));
        AnchorPane accountLayout = fxmlLoader.load();
        currentStage.setScene(new Scene(accountLayout));

        AccountViewController accountViewController = fxmlLoader.getController();
        accountViewController.setNecessaryAtributes(currentStage,utilizatorAccountService,usr);
    }

    @Override
    public void update(UtilizatorEntityChangeEvent utilizatorEntityChangeEvent) {
        clearMessageVBox();

        handleSelection();

    }

    private void clearMessageVBox(){
        messageListVBox.getChildren().clear();
    }
}
