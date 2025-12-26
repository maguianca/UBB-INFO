package ro.mpp2025.controller;


import javafx.application.Platform;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.PasswordField;
import javafx.scene.control.TextField;
import javafx.stage.Stage;
import ro.mpp2025.Domain.Angajat;
import ro.mpp2025.Service.ServiceException;

public class LoginViewController extends Controller {
    @FXML
    TextField usernameBox;
    @FXML
    PasswordField passwordBox;
    @FXML
    Button loginButton;

    public void onLoginButtonClicked() {
        var username = usernameBox.getText();
        var password = passwordBox.getText();
        Angajat angajat=null;
        Stage window=null;
        try {
            window = Utils.createSpectacoleWindow(appService);
            SpectacoleViewController controller = Utils.getController(window);
            angajat = appService.loginAngajat(username, password, controller);
        }
        catch (ServiceException e){

        }
        if(angajat==null){
            displayException(new RuntimeException("Wrong username or password"));
            Platform.exit();
        }
        else {
            Angajat thisAngajat = angajat;
            window.setOnCloseRequest(t -> {
                appService.logout(thisAngajat);
                /*if(appService instanceof ServiceObjectProxy) {
                    ((ServiceObjectProxy)appService).closeConnection();
                }*/
                Platform.exit();
                System.exit(0);
            });

            window.show();
            loginButton.getScene().getWindow().hide();
        }
    }
}
