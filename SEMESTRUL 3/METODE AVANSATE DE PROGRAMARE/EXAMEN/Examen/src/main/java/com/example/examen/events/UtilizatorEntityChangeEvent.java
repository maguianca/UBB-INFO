package com.example.examen.events;


//import com.example.examen.domeniu.Notificare;

import com.example.examen.domeniu.Notificare;

public class UtilizatorEntityChangeEvent implements Event {

    private ChangeEventType type;
    private Notificare data, oldData;

    public UtilizatorEntityChangeEvent(ChangeEventType type, Notificare data) {
        this.type = type;
        this.data = data;
    }
    public UtilizatorEntityChangeEvent(ChangeEventType type, Notificare data, Notificare oldData) {
        this.type = type;
        this.data = data;
        this.oldData=oldData;
    }

    public ChangeEventType getType() {
        return type;
    }

    public Notificare getData() {
        return data;
    }

    public Notificare getOldData() {
        return oldData;
    }

    public ChangeEventType getEventType() {
        return type;
    }
}