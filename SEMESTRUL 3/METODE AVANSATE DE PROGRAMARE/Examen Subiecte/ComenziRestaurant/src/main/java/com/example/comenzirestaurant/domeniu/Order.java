package com.example.comenzirestaurant.domeniu;

import java.time.LocalDateTime;
import java.util.List;

public class Order extends Entity<Long> {
    private Long tableId;
    private List<Long> menuItems;
    private LocalDateTime date;
    private Status status;

    public enum Status {
        PLACED, PREPARING, DELIVERED,NONE
    }

    public Order(Long tableId, List<Long> menuItems, LocalDateTime date,Status status) {
        this.tableId = tableId;
        this.menuItems = menuItems;
        this.date = date;
        this.status = status;
    }

    public Long getTableId() {
        return tableId;
    }

    public void setTableId(Long tableId) {
        this.tableId = tableId;
    }

    public List<Long> getMenuItems() {
        return menuItems;
    }

    public void setMenuItems(List<Long> menuItems) {
        this.menuItems = menuItems;
    }

    public LocalDateTime getDate() {
        return date;
    }

    public void setDate(LocalDateTime date) {
        this.date = date;
    }

    public Status getStatus() {
        return status;
    }

    public void setStatus(Status status) {
        this.status = status;
    }

    @Override
    public String toString() {
        return "Order{" +
                "tableId=" + tableId +
                ", menuItems=" + menuItems +
                ", date=" + date +
                ", status=" + status +
                '}';
    }
}