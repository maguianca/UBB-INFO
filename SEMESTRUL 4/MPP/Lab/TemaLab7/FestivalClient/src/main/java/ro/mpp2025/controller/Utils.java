package ro.mpp2025.controller;

import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.Alert;
import javafx.scene.control.ButtonType;
import javafx.stage.Stage;
import ro.mpp2025.Application;
import ro.mpp2025.Service.IAppService;

import java.io.IOException;

public class Utils {
    public static Stage createLoginWindow(IAppService appService){
        return createWindow("loginView.fxml", 600, 400
            , "Conectare Angajat", appService);
    }

    public static Stage createSpectacoleWindow(IAppService appService){
        var window= createWindow("spectacoleView.fxml", 800, 600
                , "Spectacole", appService);
        return window;
    }

    public static Stage createWindow(String fxml, int width, int height) {
        try {
            var stage = new Stage();
            FXMLLoader fxmlLoader = getLoader(fxml);
            Scene scene = new Scene(fxmlLoader.load(), width, height);
            stage.setUserData(fxmlLoader);
            stage.setResizable(false);
            stage.setScene(scene);
            return stage;
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    public static Stage createWindow(String fxml, int width, int height
        ,String title, IAppService appService){
        var stage = createWindow(fxml, width, height);
        Controller controller = getController(stage);
        controller.setAppService(appService);
        stage.setTitle(title);
        return stage;
    }

    public static <C extends Controller> C getController(Stage stage){
        return ((FXMLLoader)stage.getUserData()).getController();
    }
    public static FXMLLoader getLoader(String name) {
        //return new FXMLLoader(Application.class.getResource(name));
        return new FXMLLoader(Application.class.getResource("/ro/mpp2025/view/" + name));
    }

    public static void showMessageBox(String message) {
        Alert alert = new Alert(Alert.AlertType.INFORMATION);
        alert.setTitle("Info");
        alert.setHeaderText("Message:");
        alert.setContentText(message);
        alert.showAndWait().ifPresent(rs -> {
            if (rs == ButtonType.OK) {
                System.out.println("Pressed OK.");
            }
        });
    }
}
