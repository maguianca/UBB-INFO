module com.example.faptebune {
    requires javafx.controls;
    requires javafx.fxml;
    requires java.sql;
    requires org.controlsfx.controls;
    requires com.dlsc.formsfx;
    requires net.synedra.validatorfx;
    requires org.kordamp.bootstrapfx.core;
    requires java.desktop;
    requires jdk.jshell;

    opens com.example.faptebune to javafx.fxml;
    exports com.example.faptebune;
}