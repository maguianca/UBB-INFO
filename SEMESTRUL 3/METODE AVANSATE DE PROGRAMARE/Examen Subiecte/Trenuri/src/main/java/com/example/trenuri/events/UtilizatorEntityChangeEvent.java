package com.example.trenuri.events;


import com.example.trenuri.domeniu.City;
import com.example.trenuri.domeniu.Client;

public class UtilizatorEntityChangeEvent implements Event {

    private ChangeEventType type;
    private Client data, oldData;

    public UtilizatorEntityChangeEvent(ChangeEventType type, Client data) {
        this.type = type;
        this.data = data;
    }
    public UtilizatorEntityChangeEvent(ChangeEventType type, Client data, Client oldData) {
        this.type = type;
        this.data = data;
        this.oldData=oldData;
    }

    public ChangeEventType getType() {
        return type;
    }

    public Client getData() {
        return data;
    }

    public Client getOldData() {
        return oldData;
    }

    public ChangeEventType getEventType() {
        return type;
    }
}