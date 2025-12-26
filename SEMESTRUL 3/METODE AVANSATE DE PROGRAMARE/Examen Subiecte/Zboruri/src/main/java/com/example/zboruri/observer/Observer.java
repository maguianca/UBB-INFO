package com.example.zboruri.observer;


import com.example.zboruri.events.Event;

public interface Observer<E extends Event> {
    void update(E e);
}