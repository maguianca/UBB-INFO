module com.example.laborator7_map {
    requires javafx.controls;
    requires javafx.fxml;
    requires java.sql;
    requires org.controlsfx.controls;
    requires com.dlsc.formsfx;
    requires net.synedra.validatorfx;
    requires org.kordamp.bootstrapfx.core;
    requires java.desktop;
    requires jdk.jshell;

    opens com.example.laborator7networking to javafx.fxml;
    exports com.example.laborator7networking;

}
