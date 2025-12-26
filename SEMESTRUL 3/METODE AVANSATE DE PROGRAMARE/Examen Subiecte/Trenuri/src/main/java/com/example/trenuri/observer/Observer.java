package com.example.trenuri.observer;


import com.example.trenuri.events.Event;

public interface Observer<E extends Event> {
    void update(E e);
}