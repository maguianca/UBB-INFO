package com.example.guiex1.domain;

public class Page<E> {
    Iterable<E> elementsOnPage;
    int totalNumberOfElements;

    public Page(int totalNumberOfElements, Iterable<E> elementsOnPage) {
        this.totalNumberOfElements = totalNumberOfElements;
        this.elementsOnPage = elementsOnPage;
    }

    public Iterable<E> getElementsOnPage() {
        return elementsOnPage;
    }

    public int getTotalNumberOfElements() {
        return totalNumberOfElements;
    }
}
