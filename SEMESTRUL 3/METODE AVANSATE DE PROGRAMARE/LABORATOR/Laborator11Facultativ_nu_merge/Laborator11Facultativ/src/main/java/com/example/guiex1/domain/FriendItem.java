package com.example.guiex1.domain;

import com.example.guiex1.domain.Utilizator;

public class FriendItem {
    private String displayName; // Full name to display
    private Utilizator utilizator; // The actual Utilizator object

    public FriendItem(String displayName, Utilizator utilizator) {
        this.displayName = displayName;
        this.utilizator = utilizator;
    }

    public String getDisplayName() {
        return displayName;
    }

    public Utilizator getUtilizator() {
        return utilizator;
    }

    @Override
    public String toString() {
        return displayName; // Display only the full name in the ListView
    }
}
