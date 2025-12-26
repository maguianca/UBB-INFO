package com.example.comenzirestaurant.events;


import com.example.comenzirestaurant.domeniu.Order;

public class UtilizatorEntityChangeEvent implements Event {
    private ChangeEventType type;
    private Order data, oldData;

    public UtilizatorEntityChangeEvent(ChangeEventType type, Order data) {
        this.type = type;
        this.data = data;
    }
    public UtilizatorEntityChangeEvent(ChangeEventType type, Order data, Order oldData) {
        this.type = type;
        this.data = data;
        this.oldData=oldData;
    }

    public ChangeEventType getType() {
        return type;
    }

    public Order getData() {
        return data;
    }

    public Order getOldData() {
        return oldData;
    }

    public ChangeEventType getEventType() {
        return type;
    }
}