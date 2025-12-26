package com.example.guiex1.domain;

import java.time.LocalDateTime;

import java.time.LocalDateTime;
import static java.lang.Math.max;
import static java.lang.Math.min;
public class Friendship extends Entity<Long>{
    //LocalDateTime date;
    Long idUser1;
    Long idUser2;
    LocalDateTime date;
    public Friendship( Long idUser1, Long idUser2,LocalDateTime date) {
        this.idUser1=idUser1;
        this.idUser2=idUser2;
        this.date=date;
    }

    public Friendship() {

    }

    public LocalDateTime getDate() {
        return date;
    }
    public Long getIdUser1() {
        return idUser1;
    }

    public Long getIdUser2() {
        return idUser2;
    }
    @Override
    public String toString() {
        return "Friendship{" +
                "id user1='" + idUser1 + '\'' +
                ",id user 2=" + idUser2 + '\'' +
                ", date=" + date +
                '}';
    }

}
