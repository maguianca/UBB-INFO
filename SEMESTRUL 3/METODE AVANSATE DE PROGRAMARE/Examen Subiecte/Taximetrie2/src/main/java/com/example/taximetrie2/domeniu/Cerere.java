package com.example.taximetrie2.domeniu;

public class Cerere extends Entity<Long>{
    private Long id_client;
    private String adresa;
    public Cerere(Long id_client, String adresa) {
        this.id_client = id_client;
        this.adresa = adresa;
    }

    public Long getId_client() {
        return id_client;
    }

    public void setId_client(Long id_client) {
        this.id_client = id_client;
    }

    public String getAdresa() {
        return adresa;
    }

    public void setAdresa(String adresa) {
        this.adresa = adresa;
    }
}
