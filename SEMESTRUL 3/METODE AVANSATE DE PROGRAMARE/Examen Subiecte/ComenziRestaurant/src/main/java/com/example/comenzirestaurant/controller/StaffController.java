package com.example.comenzirestaurant.controller;

import com.example.comenzirestaurant.domeniu.Angajat;
import com.example.comenzirestaurant.domeniu.*;
import com.example.comenzirestaurant.events.UtilizatorEntityChangeEvent;
import com.example.comenzirestaurant.observer.Observer;
import com.example.comenzirestaurant.service.Service;
import javafx.beans.property.SimpleStringProperty;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.stage.Stage;

import java.time.LocalDateTime;
import java.util.List;
import java.util.Objects;
import java.util.stream.Collectors;

public class StaffController implements Observer<UtilizatorEntityChangeEvent> {
    private Angajat angajat;
    private Service service;
    private Stage dialogStage;
    @FXML
    private TableView<Order> tabel;
    @FXML
    private TableColumn<Order,String>produse;
    @FXML
    private TableColumn<Order, LocalDateTime>data;
    @FXML
    private TableColumn<Order,Long>masa;
    @FXML
    private TableColumn<Order, String>status;
    private ObservableList<Order> model = FXCollections.observableArrayList();

    @FXML
    private TableView<Order> tabel1;
    @FXML
    private TableColumn<Order,String>produse1;
    @FXML
    private TableColumn<Order, LocalDateTime>data1;
    @FXML
    private TableColumn<Order,Long>masa1;
    @FXML
    private TableColumn<Order, String>status1;
    private ObservableList<Order> model1 = FXCollections.observableArrayList();

    public void setService(Service service, Stage dialogStage, Angajat angajat) {
        this.service = service;
        this.dialogStage = dialogStage;
        this.angajat=angajat;
        initModel();
        this.service.addObserver(this);
    }
    @FXML
    public void initialize()
    {
        tabel.setItems(model);
        tabel1.setItems(model1);
    }

    public void initModel() {
        model.setAll(service.getOrders());
        data.setCellValueFactory(new PropertyValueFactory<>("date"));
        masa.setCellValueFactory(new PropertyValueFactory<>("tableId"));
        produse.setCellValueFactory(cellData -> {
            List<String> itemNames = cellData.getValue().getMenuItems().stream()
                    .map(id -> service.MenufindOne(id))
                    .filter(Objects::nonNull)
                    .map(MenuItem::getItem)
                    .collect(Collectors.toList());
            return new SimpleStringProperty(String.join(", ", itemNames));
        });
        status.setCellValueFactory(new PropertyValueFactory<>("status"));

        model1.setAll(service.getOrdersPrepering());
        data1.setCellValueFactory(new PropertyValueFactory<>("date"));
        masa1.setCellValueFactory(new PropertyValueFactory<>("tableId"));
        produse1.setCellValueFactory(cellData -> {
            List<String> itemNames = cellData.getValue().getMenuItems().stream()
                    .map(id -> service.MenufindOne(id))
                    .filter(Objects::nonNull)
                    .map(MenuItem::getItem)
                    .collect(Collectors.toList());
            return new SimpleStringProperty(String.join(", ", itemNames));
        });
        status1.setCellValueFactory(new PropertyValueFactory<>("status"));


    }
    public void update(UtilizatorEntityChangeEvent utilizatorEntityChangeEvent) {
        initModel();
    }

    public void handleprepering(ActionEvent actionEvent) {
            Order selectedOrder = tabel.getSelectionModel().getSelectedItem();
            if (selectedOrder != null) {
                selectedOrder.setStatus(Order.Status.PREPARING);
                service.updateOrder(selectedOrder);
                initModel();
            } else {
                System.out.println("No order selected.");
            }
    }
    public void handledelivered(ActionEvent actionEvent) {
        Order selectedOrder = tabel1.getSelectionModel().getSelectedItem();
        if (selectedOrder != null) {
            selectedOrder.setStatus(Order.Status.DELIVERED);
            service.updateOrder(selectedOrder);
            initModel();
        } else {
            System.out.println("No order selected.");
        }

    }
}
