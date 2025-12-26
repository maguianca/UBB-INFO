package com.example.taximetrie.domeniu;

public class Sofer extends Persoana{
    private String indicativMasina;
    public Sofer(String username,String nume,String indicativMasina){
        super(username,nume);
        this.indicativMasina = indicativMasina;
    }

    public String getIndicativMasina() {
        return indicativMasina;
    }

    public void setIndicativMasina(String indicativMasina) {
        this.indicativMasina = indicativMasina;
    }

    @Override
    public String toString() {
        return "Sofer{" + super.toString() +
                "indicativMasina='" + indicativMasina + '\'' +
                '}';
    }
}
