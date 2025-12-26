package com.example.comenzirestaurant.controller;

import com.example.comenzirestaurant.domeniu.MenuItem;
import com.example.comenzirestaurant.domeniu.Order;
import com.example.comenzirestaurant.domeniu.Table;
import com.example.comenzirestaurant.events.UtilizatorEntityChangeEvent;
import com.example.comenzirestaurant.observer.Observer;
import com.example.comenzirestaurant.service.Service;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.*;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.layout.VBox;
import javafx.stage.Stage;

import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.stream.Collectors;

public class TableController implements Observer<UtilizatorEntityChangeEvent> {
    private Table table;
    private Service service;
    private Stage dialogStage;

    @FXML
    private VBox tableContainer;

    @FXML
    private Button order;

    private List<MenuItem> selectedItems = new ArrayList<>();
    @FXML
    private Label statuslabel;

    public void setService(Service service, Stage dialogStage, Table table) {
        this.service = service;
        this.dialogStage = dialogStage;
        this.table = table;
        initModel();
        this.service.addObserver(this);
    }

    @FXML
    public void initialize() {
    }

    public void initModel() {
        tableContainer.getChildren().clear();
        selectedItems.clear();
        Map<String, List<MenuItem>> menuByCategory = service.getMenuGroupedByCategory();
        for (Map.Entry<String, List<MenuItem>> entry : menuByCategory.entrySet()) {
            String category = entry.getKey();
            List<MenuItem> items = entry.getValue();

            Label categoryLabel = new Label(category);
            categoryLabel.setStyle("-fx-font-size: 16px; -fx-font-weight: bold; -fx-padding: 10 0 5 0;");

            TableView<MenuItem> tableView = new TableView<>();
            tableView.setPrefWidth(400);
            tableView.getSelectionModel().setSelectionMode(SelectionMode.MULTIPLE);

            TableColumn<MenuItem, String> itemColumn = new TableColumn<>("Item");
            itemColumn.setCellValueFactory(new PropertyValueFactory<>("item"));

            TableColumn<MenuItem, Float> priceColumn = new TableColumn<>("Price");
            priceColumn.setCellValueFactory(new PropertyValueFactory<>("pret"));

            TableColumn<MenuItem, String> currencyColumn = new TableColumn<>("Currency");
            currencyColumn.setCellValueFactory(new PropertyValueFactory<>("moneda"));

            tableView.getColumns().addAll(itemColumn, priceColumn, currencyColumn);
            tableView.getItems().addAll(items);
            tableView.setOnMouseClicked(event -> {
                if (event.getClickCount() == 2) {
                    MenuItem clickedItem = tableView.getSelectionModel().getSelectedItem();
                    if (clickedItem != null) {
                        if (selectedItems.contains(clickedItem)) {
                            selectedItems.remove(clickedItem);
                            System.out.println("Removed: " + clickedItem.getItem());
                        } else {
                            selectedItems.add(clickedItem);
                            System.out.println("Added: " + clickedItem.getItem());
                        }
                    }
                }
            });
            tableContainer.getChildren().add(categoryLabel);
            tableContainer.getChildren().add(tableView);
        }
    }

    public void update(UtilizatorEntityChangeEvent utilizatorEntityChangeEvent) {
        initModel();
        Order.Status status=service.getStatusOrder(table.getId());
        if(status== Order.Status.DELIVERED)
            statuslabel.setText("Your order has been delivered to your table");
        else if(status==Order.Status.PREPARING)
            statuslabel.setText("Your order is being prepered");
        else if(status==Order.Status.PLACED)
            statuslabel.setText("Your order has been placed");
        else
            statuslabel.setText("Status: None");

    }

    public void handle_place_order(ActionEvent actionEvent) {

        /*for (javafx.scene.Node node : tableContainer.getChildren()) {
            if (node instanceof TableView<?>) {
                TableView<MenuItem> tableView = (TableView<MenuItem>) node;
                selectedItems.addAll(tableView.getSelectionModel().getSelectedItems());
            }
        }*/

        if (!selectedItems.isEmpty()) {
            System.out.println("Order placed for the following items:");
            selectedItems.forEach(item -> System.out.println("- " + item.getItem() + " (" + item.getPret() + " " + item.getMoneda() + ")"));
            List<Long> itemIds = selectedItems.stream()
                    .map(MenuItem::getId)
                    .collect(Collectors.toList());
            service.saveOrder(new Order(table.getId(), itemIds, LocalDateTime.now(), Order.Status.PLACED));
        } else {
            System.out.println("No items selected. Cannot place order.");
        }
        selectedItems.clear();
    }
}