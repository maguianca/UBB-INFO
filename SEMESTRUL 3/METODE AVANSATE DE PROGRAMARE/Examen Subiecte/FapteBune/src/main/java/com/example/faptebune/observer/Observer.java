package com.example.faptebune.observer;


import com.example.faptebune.events.Event;

public interface Observer<E extends Event> {
    void update(E e);
}