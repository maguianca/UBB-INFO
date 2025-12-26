package com.example.taximetrie2.observer;


import com.example.taximetrie2.events.Event;

public interface Observer<E extends Event> {
    void update(E e);
}