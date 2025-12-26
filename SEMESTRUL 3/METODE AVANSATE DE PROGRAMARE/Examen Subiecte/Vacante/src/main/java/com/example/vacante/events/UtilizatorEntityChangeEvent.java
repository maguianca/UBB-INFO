package com.example.vacante.events;


//import com.example.controller.domeniu.Persoana;

import com.example.vacante.domeniu.Client;
import com.example.vacante.domeniu.DTO;

public class UtilizatorEntityChangeEvent implements Event {
    private ChangeEventType type;
    private DTO data, oldData;

    public UtilizatorEntityChangeEvent(ChangeEventType type, DTO data) {
        this.type = type;
        this.data = data;
    }
    public UtilizatorEntityChangeEvent(ChangeEventType type, DTO data, DTO oldData) {
        this.type = type;
        this.data = data;
        this.oldData=oldData;
    }

    public ChangeEventType getType() {
        return type;
    }

    public DTO getData() {
        return data;
    }

    public DTO getOldData() {
        return oldData;
    }

    public ChangeEventType getEventType() {
        return type;
    }
}