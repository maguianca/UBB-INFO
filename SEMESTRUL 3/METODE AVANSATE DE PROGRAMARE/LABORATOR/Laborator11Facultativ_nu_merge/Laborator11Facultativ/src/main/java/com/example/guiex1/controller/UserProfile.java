package com.example.guiex1.controller;

import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.control.Label;
import javafx.scene.layout.AnchorPane;
import javafx.scene.shape.Circle;
import javafx.stage.Stage;

import java.io.IOException;

public class UserProfile {
    private Stage stage;
    private AnchorPane root;
    private ImageView profileImageView;
    private Label userLabel;
    private Label nameLabel;
    private Label prieteniLabel;
    private Label prietenicLabel;
    private Label bio;

    public UserProfile(String username, String Nume, int prieteni, int prieteni_comuni, String profileImageUrl,String descriere) {
        try {
            FXMLLoader loader = new FXMLLoader(getClass().getResource("/com/example/guiex1/views/UserProfile.fxml"));
            root = loader.load();

            profileImageView = (ImageView) root.lookup("#imagine");
            nameLabel = (Label) root.lookup("#nameLabel");
            userLabel = (Label) root.lookup("#userLabel");
            prieteniLabel = (Label) root.lookup("#prieteniLabel");
            prietenicLabel = (Label) root.lookup("#prietenicLabel");
            bio = (Label) root.lookup("#bio");

            userLabel.setText("•"+username);
            nameLabel.setText(Nume);
            prieteniLabel.setText("Prieteni:"+prieteni);
            if(prieteni_comuni>0)
                prietenicLabel.setText("Prieteni comuni:"+prieteni_comuni);
            else{
                prietenicLabel.setText("");
            }
            if(descriere.isEmpty()){
                bio.setText("");
            }else{
                bio.setText("Bio"+descriere);
            }

            if (profileImageUrl != null && !profileImageUrl.isEmpty()) {
                Image imag = new Image(profileImageUrl);
                profileImageView.setImage(imag);

                Circle clip = new Circle();
                clip.setCenterX(profileImageView.getFitWidth() / 2); // Centrul cercului pe orizontală
                clip.setCenterY(profileImageView.getFitHeight() / 2); // Centrul cercului pe verticală
                clip.setRadius(profileImageView.getFitWidth() / 2); // Raza cercului

                profileImageView.setClip(clip);
            }

            Scene scene = new Scene(root, 400, 300);
            stage = new Stage();
            stage.setScene(scene);
            stage.setTitle("Profil Utilizator");

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void show() {
        stage.show();
    }
}
