package com.example.guiex1.dto;

import com.example.guiex1.domain.Entity;
import com.example.guiex1.domain.Utilizator;

import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.List;
import java.util.Objects;
import java.util.Optional;

public class UtilizatorDTO {
        private String firstName;
        private String lastName;
        private LocalDateTime datefriendship;
        public UtilizatorDTO(String firstName, String lastName,LocalDateTime datefriendship) {
            this.firstName = firstName;
            this.lastName = lastName;
            this.datefriendship = datefriendship;
        }
       /* public String getUsername(){
            return username;
        }
        public void setUsername(String username){
            this.username = username;
        }*/
        public String getFirstName() {
            return firstName;
        }
        public void setFirstName(String firstName) {
            this.firstName = firstName;
        }
        public String getLastName() {
            return lastName;
        }
        public LocalDateTime getDatefriendship() {
            return datefriendship;
        }
        public void setDatefriendship(LocalDateTime datefriendship) {
            this.datefriendship = datefriendship;
        }
        public void setLastName(String lastName) {
            this.lastName = lastName;
        }

}

