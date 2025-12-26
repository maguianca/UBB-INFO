package com.example.taximetrie.domeniu;

public class Oferta extends Entity<Long>{
    private Long id_client;
    private Long id_sofer;
    private int minute;
    public Oferta(Long id_client, Long id_sofer, int minute) {
        this.id_client = id_client;
        this.id_sofer = id_sofer;
        this.minute = minute;
    }

    public Long getId_client() {
        return id_client;
    }

    public void setId_client(Long id_client) {
        this.id_client = id_client;
    }

    public Long getId_sofer() {
        return id_sofer;
    }

    public void setId_sofer(Long id_sofer) {
        this.id_sofer = id_sofer;
    }

    public int getMinute() {
        return minute;
    }

    public void setMinute(int minute) {
        this.minute = minute;
    }
}
