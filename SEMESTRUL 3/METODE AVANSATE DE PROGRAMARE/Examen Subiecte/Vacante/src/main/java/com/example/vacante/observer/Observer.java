package com.example.vacante.observer;


import com.example.vacante.events.Event;

public interface Observer<E extends Event> {
    void update(E e);
}