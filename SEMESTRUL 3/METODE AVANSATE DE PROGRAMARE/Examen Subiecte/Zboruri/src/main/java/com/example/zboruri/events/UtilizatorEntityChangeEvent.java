package com.example.zboruri.events;


//import com.example.controller.domeniu.Persoana;

import com.example.zboruri.domeniu.Flight;

public class UtilizatorEntityChangeEvent implements Event {
    private ChangeEventType type;
    private Flight data, oldData;

    public UtilizatorEntityChangeEvent(ChangeEventType type, Flight data) {
        this.type = type;
        this.data = data;
    }
    public UtilizatorEntityChangeEvent(ChangeEventType type, Flight data, Flight oldData) {
        this.type = type;
        this.data = data;
        this.oldData=oldData;
    }

    public ChangeEventType getType() {
        return type;
    }

    public Flight getData() {
        return data;
    }

    public Flight getOldData() {
        return oldData;
    }

    public ChangeEventType getEventType() {
        return type;
    }
}