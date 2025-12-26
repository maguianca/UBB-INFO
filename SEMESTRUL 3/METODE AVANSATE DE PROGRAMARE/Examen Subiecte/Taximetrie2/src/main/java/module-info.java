module com.example.taximetrie2 {
    requires javafx.controls;
    requires javafx.fxml;

    requires org.controlsfx.controls;
    requires com.dlsc.formsfx;
    requires org.kordamp.bootstrapfx.core;
    requires java.sql;

    opens com.example.taximetrie2 to javafx.fxml;
    exports com.example.taximetrie2;
}