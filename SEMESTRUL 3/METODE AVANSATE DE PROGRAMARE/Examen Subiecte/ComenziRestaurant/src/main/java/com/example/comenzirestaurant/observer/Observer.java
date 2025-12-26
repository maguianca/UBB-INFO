package com.example.comenzirestaurant.observer;


import com.example.comenzirestaurant.events.Event;

public interface Observer<E extends Event> {
    void update(E e);
}