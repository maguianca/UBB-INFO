package com.example.faptebune.events;


import com.example.faptebune.domeniu.Persoana;

public class UtilizatorEntityChangeEvent implements Event {
    private ChangeEventType type;
    private Persoana data, oldData;

    public UtilizatorEntityChangeEvent(ChangeEventType type, Persoana data) {
        this.type = type;
        this.data = data;
    }
    public UtilizatorEntityChangeEvent(ChangeEventType type, Persoana data, Persoana oldData) {
        this.type = type;
        this.data = data;
        this.oldData=oldData;
    }

    public ChangeEventType getType() {
        return type;
    }

    public Persoana getData() {
        return data;
    }

    public Persoana getOldData() {
        return oldData;
    }

    public ChangeEventType getEventType() {
        return type;
    }
}