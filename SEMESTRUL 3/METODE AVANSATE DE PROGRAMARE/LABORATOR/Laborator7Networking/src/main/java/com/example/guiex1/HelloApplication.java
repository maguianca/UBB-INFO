package com.example.guiex1;

import com.example.guiex1.controller.UtilizatoriController;
import com.example.guiex1.domain.*;
import com.example.guiex1.repository.Repository;
import com.example.guiex1.repository.dbrepo.*;
import com.example.guiex1.services.MessageService;
import com.example.guiex1.services.UtilizatorService;
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.layout.AnchorPane;
import javafx.stage.Stage;
import java.io.IOException;

public class HelloApplication extends Application {
    UtilizatorService service;
    MessageService messageService;
    MessageManager messageManager=new MessageManager();
    public static void main(String[] args) {
        launch(args);
    }

    @Override
    public void start(Stage primaryStage) throws IOException {
        System.out.println("Reading data from database");
        Repository<Long, Utilizator> utilizatorRepository =
                new DBUserRepo(new UtilizatorValidator());
        PagingFriendship<Long, Friendship> friendshipRepository =
                new DBFriendshipRepo(new FriendshipValidator(utilizatorRepository));
        Repository<Long, Friendship> requestRepository =
                new DBRequestRepo(new FriendshipValidator(utilizatorRepository));
        Repository<Tuple<Long,Long>, ReplyMessage>replyRepository=
                new DBReplyRepo(new MessageValidator());
        Repository<Long, Message>messageRepository=
                new DBMessageRepo(new MessageValidator());

        service =new UtilizatorService(utilizatorRepository,friendshipRepository,requestRepository);
        messageService=new MessageService(service,messageRepository,replyRepository);
        initView(primaryStage);
        primaryStage.setWidth(460);
        primaryStage.show();
    }

    private void initView(Stage primaryStage) throws IOException {
        FXMLLoader fxmlLoader = new FXMLLoader(HelloApplication.class.getResource("/com/example/guiex1/views/UtilizatoriView.fxml"));

        AnchorPane userLayout = fxmlLoader.load();
        primaryStage.setScene(new Scene(userLayout));
        primaryStage.setTitle("User Management");
        UtilizatoriController userController = fxmlLoader.getController();
        userController.setUtilizatorService(service,messageService,messageManager);
    }
}