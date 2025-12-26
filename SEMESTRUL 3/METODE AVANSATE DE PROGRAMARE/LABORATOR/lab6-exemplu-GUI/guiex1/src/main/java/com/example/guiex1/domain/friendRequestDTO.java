package com.example.guiex1.domain;

import java.time.LocalDate;

public class friendRequestDTO {
    LocalDate requestDate;
    Long userWhoRequestsFriendshipId;

    public friendRequestDTO(LocalDate requestDate, Long userWhoRequestsFriendshipId){
        this.requestDate = requestDate;
        this.userWhoRequestsFriendshipId = userWhoRequestsFriendshipId;
    }

    public Long getUserWhoRequestsFriendshipId() {
        return userWhoRequestsFriendshipId;
    }

    public LocalDate getRequestDate() {
        return requestDate;
    }
}
