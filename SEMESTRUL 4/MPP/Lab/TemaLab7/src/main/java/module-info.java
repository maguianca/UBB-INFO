module ro.mpp2025.laborator7 {
    requires javafx.controls;
    requires javafx.fxml;


    opens ro.mpp2025.laborator7 to javafx.fxml;
    exports ro.mpp2025.laborator7;
}