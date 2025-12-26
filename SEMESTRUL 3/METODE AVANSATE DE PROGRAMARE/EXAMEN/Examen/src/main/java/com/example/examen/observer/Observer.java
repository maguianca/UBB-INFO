package com.example.examen.observer;


import com.example.examen.events.Event;

public interface Observer<E extends Event> {
    void update(E e);
}