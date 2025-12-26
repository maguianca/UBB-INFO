package ro.mpp2025;

import javafx.stage.Stage;
import ro.mpp2025.controller.Utils;
import ro.mpp2025.client.ServiceObjectProxy;
import ro.mpp2025.Service.*;

import java.io.FileReader;
import java.io.IOException;
import java.util.Properties;

public class Application extends javafx.application.Application {
    @Override
    public void start(Stage stage) {
        var props= loadProperties();
        var ip = props.getProperty("ip");
        var port = Integer.parseInt(props.getProperty("port"));
        var server=new ServiceObjectProxy(ip, port);

        Utils.createLoginWindow(server).show();
        //server.closeConnection();
    }

    public static Properties loadProperties() {
        Properties props=new Properties();
        try {
            props.load(new FileReader("C:\\MPP\\Java\\Laborator7\\FestivalClient\\bd.config"));
        } catch (IOException e) {
            System.out.println("Cannot find bd.config "+e);
        }
        return props;
    }

    public static void main(String[] args){
        Application.launch();
    }
}
