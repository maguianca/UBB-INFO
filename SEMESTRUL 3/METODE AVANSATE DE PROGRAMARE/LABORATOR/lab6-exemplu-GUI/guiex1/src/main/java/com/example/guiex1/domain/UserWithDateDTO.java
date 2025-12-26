package com.example.guiex1.domain;

import java.time.LocalDate;

public class UserWithDateDTO {
    Utilizator user;
    LocalDate date;

    public UserWithDateDTO(Utilizator user, LocalDate date) {
        this.user = user;
        this.date = date;
    }

    public Utilizator getUser() {
        return user;
    }

    public LocalDate getDate() {
        return date;
    }
}
