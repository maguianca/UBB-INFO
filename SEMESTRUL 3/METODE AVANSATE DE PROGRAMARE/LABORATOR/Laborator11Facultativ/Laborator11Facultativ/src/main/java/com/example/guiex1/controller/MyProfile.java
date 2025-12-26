package com.example.guiex1.controller;

import com.example.guiex1.domain.Utilizator;
import com.example.guiex1.services.UtilizatorService;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.Alert;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.layout.AnchorPane;
import javafx.scene.shape.Circle;
import javafx.stage.Stage;

import java.io.IOException;
import java.net.URL;

public class MyProfile {

    @FXML
    public Stage stage;
    @FXML
    public AnchorPane root;
    @FXML
    public ImageView profileImageView;
    @FXML
    public Label userLabel;
    @FXML
    public Label nameLabel;
    @FXML
    public Label prieteniLabel;
    @FXML
    public Label prietenicLabel;
    @FXML
    public Label bio;
    @FXML
    public TextField bioField;

    private UtilizatorService service;
    private Utilizator utilizator;

    public void setService(UtilizatorService service, Stage stage, Utilizator utilizator) {
        this.service = service;
        this.stage = stage;
        this.utilizator = utilizator;

        try {
            FXMLLoader loader = new FXMLLoader(getClass().getResource("/com/example/guiex1/views/MyProfile.fxml"));
            root = loader.load();
            profileImageView = (ImageView) root.lookup("#imagine");
            nameLabel = (Label) root.lookup("#nameLabel");
            userLabel = (Label) root.lookup("#userLabel");
            prieteniLabel = (Label) root.lookup("#prieteniLabel");
            prietenicLabel = (Label) root.lookup("#prietenicLabel");
            bio = (Label) root.lookup("#bio");
            userLabel.setText("•" + utilizator.getUsername());
            nameLabel.setText(utilizator.getFirstName() + " " + utilizator.getLastName());
            prieteniLabel.setText("Prieteni: " + service.getFriends(utilizator.getId()).size());
            bioField.setText(utilizator.getDescriere());

            int prieteniComuni = service.getNumberMutualFriends(utilizator.getId(), utilizator.getId()); // folosește ID-ul corespunzător
            if (prieteniComuni > 0) {
                prietenicLabel.setText("Prieteni comuni: " + prieteniComuni);
            } else {
                prietenicLabel.setText("");
            }

            String profileImageUrl = utilizator.getUrl();
            if (profileImageUrl != null && !profileImageUrl.isEmpty()) {
                URL imageUrl = getClass().getResource(profileImageUrl);
                if (imageUrl != null) {
                    Image imag = new Image(imageUrl.toExternalForm());
                    profileImageView.setImage(imag);

                    // Setare clip circular
                    Circle clip = new Circle();
                    clip.setCenterX(profileImageView.getFitWidth() / 2);
                    clip.setCenterY(profileImageView.getFitHeight() / 2);
                    clip.setRadius(profileImageView.getFitWidth() / 2);
                    profileImageView.setClip(clip);

                    System.out.println("Imaginea a fost încărcată cu succes.");
                } else {
                    System.out.println("Imaginea nu a fost găsită la: " + profileImageUrl);
                }
            }else{
                System.out.println("NULL");
            }

            Scene scene = new Scene(root, 400, 300);
            stage.setScene(scene);
            stage.setTitle("Profil Utilizator");

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void show() {
        stage.show();
    }

    public void handlePoza(javafx.event.ActionEvent actionEvent) {
    }

    public void handleDescriere(ActionEvent actionEvent) {
        String Descriere = bioField.getText();
        utilizator.setDescriere(Descriere);

        service.update(utilizator);
        Alert alert = new Alert(Alert.AlertType.INFORMATION);
        alert.setTitle("Descriere actualizată");
        alert.setHeaderText(null);
        alert.setContentText("Descrierea a fost schimbată cu succes!");
        alert.showAndWait();
    }
}
