module com.example.trenuri {
    requires javafx.controls;
    requires javafx.fxml;

    requires org.controlsfx.controls;
    requires com.dlsc.formsfx;
    requires org.kordamp.bootstrapfx.core;
    requires java.sql;

    opens com.example.trenuri to javafx.fxml;
    exports com.example.trenuri;
    exports com.example.trenuri.controller;
    opens com.example.trenuri.controller to javafx.fxml;
}