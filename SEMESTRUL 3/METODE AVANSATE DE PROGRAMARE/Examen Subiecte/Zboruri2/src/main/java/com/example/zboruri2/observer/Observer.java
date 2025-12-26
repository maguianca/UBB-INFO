package com.example.zboruri2.observer;


import com.example.zboruri2.events.Event;

public interface Observer<E extends Event> {
    void update(E e);
}