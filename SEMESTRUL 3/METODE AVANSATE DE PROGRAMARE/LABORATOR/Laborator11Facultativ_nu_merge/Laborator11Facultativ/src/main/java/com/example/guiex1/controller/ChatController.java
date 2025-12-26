package com.example.guiex1.controller;

import com.example.guiex1.domain.Utilizator;
import com.example.guiex1.services.UtilizatorService;
import com.example.guiex1.services.MessageService;
import com.example.guiex1.utils.events.MessageEntityChangeEvent;
import com.example.guiex1.utils.events.ChangeEventType;
import com.example.guiex1.utils.observer.Observer;

import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.ListCell;
import javafx.scene.control.ListView;
import javafx.scene.control.TextArea;
import javafx.scene.control.TextField;
import javafx.stage.Stage;

import java.util.List;
import java.util.Objects;

public class ChatController implements Observer<MessageEntityChangeEvent> {

    private UtilizatorService service;
    private MessageService messageService;
    private Stage dialogStage;
    private Utilizator utilizator;

    @FXML
    private ListView<Utilizator> friendsList;
    @FXML
    private TextField messageField;
    @FXML
    private TextArea chatArea;

    @FXML
    private void initialize() {

    }

    public void setService(UtilizatorService service, MessageService messageService, Stage stage, Utilizator u) {
        this.service = service;
        this.messageService = messageService;
        this.dialogStage = stage;
        this.utilizator = u;

        if (this.utilizator == null) {
            System.out.println("Utilizator is null in ChatController setService");
        } else {
            System.out.println("Utilizator is set in ChatController: " + this.utilizator.getFirstName());
        }
        loadFriends();
        messageService.addObserver(this);
    }

    private void loadFriends() {
        System.out.println("Loading friends for user: " + utilizator.getId());
        try {
            List<Long> friendIds = service.getFriends(utilizator.getId());
            List<Utilizator> friends = friendIds.stream()
                    .map(service::findOne)
                    .filter(Objects::nonNull) // Ensure null values are filtered out
                    .toList();

            ObservableList<Utilizator> observableFriends = FXCollections.observableArrayList(friends);
            friendsList.setItems(observableFriends);

            friendsList.setCellFactory(param -> new ListCell<Utilizator>() {
                @Override
                protected void updateItem(Utilizator item, boolean empty) {
                    super.updateItem(item, empty);
                    if (empty || item == null) {
                        setText(null);
                    } else {
                        setText(item.getFirstName() + " " + item.getLastName());
                    }
                }
            });

            friendsList.getSelectionModel().selectedItemProperty().addListener((observable, oldValue, newValue) -> {
                if (newValue != null) {
                    loadChatHistory(newValue);
                }
            });

        } catch (Exception e) {
            e.printStackTrace();
        }
    }
    private void loadChatHistory(Utilizator selectedFriend) {
        if (selectedFriend == null) return;

        System.out.println("Loading chat history for: " + selectedFriend.getFirstName() + " " + selectedFriend.getLastName());

        List<String> conversation = messageService.getConvo(utilizator.getUsername(), selectedFriend.getUsername());
        if (conversation == null || conversation.isEmpty()) {
            chatArea.setText("No messages yet.");
            return;
        }

        StringBuilder formattedChat = new StringBuilder();

        for (String message : conversation) {
            if (message.startsWith(utilizator.getUsername() + ":")) {
                formattedChat.append(String.format("%90s%n", message));
            } else {
                formattedChat.append(String.format("%-50s%n", message));
            }
        }

        chatArea.setText(formattedChat.toString());
    }

    public void sendMessage(ActionEvent actionEvent) {
         Utilizator selectedFriend = friendsList.getSelectionModel().getSelectedItem();
        if (selectedFriend == null) {
            System.out.println("No friend selected.");
            return;
        }

        String messageText = messageField.getText();
        if (messageText.isEmpty()) {
            System.out.println("Message is empty.");
            return;
        }

        messageService.addMessage(utilizator.getUsername(), messageText, selectedFriend.getUsername());
        messageField.clear();
    }

    public void handleBack(ActionEvent actionEvent) {
        dialogStage.close();
    }

    @Override
    public void update(MessageEntityChangeEvent event) {

        if (event.getType() == ChangeEventType.ADD) {
            Utilizator selectedFriend = friendsList.getSelectionModel().getSelectedItem();
            if (selectedFriend != null) {
                loadChatHistory(selectedFriend);
            }
        }
    }
}
