package com.example.taximetrie2.domeniu;

public class Oferta extends Entity<Long>{
    private Long id_client;
    private Long id_sofer;
    private int minute;
    private Long id_cerere;
    public Oferta(Long id_client, Long id_sofer,Long id_cerere, int minute) {
        this.id_client = id_client;
        this.id_sofer = id_sofer;
        this.id_cerere=id_cerere;
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

    public Long getId_cerere() {
        return id_cerere;
    }

    public void setId_cerere(Long id_cerere) {
        this.id_cerere = id_cerere;
    }
}
