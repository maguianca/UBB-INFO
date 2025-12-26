package com.example.taximetrie.domeniu;

import java.time.LocalDateTime;

public class Comanda extends Entity<Long>{
    private Persoana persoana;
    private Sofer taximetrist;
    private LocalDateTime data;
    public Comanda(Persoana persoana, Sofer taximetrist, LocalDateTime data) {
        this.persoana = persoana;
        this.taximetrist = taximetrist;
        this.data = data;
    }

    public Persoana getPersoana() {
        return persoana;
    }

    public void setPersoana(Persoana persoana) {
        this.persoana = persoana;
    }

    public Sofer getTaximetrist() {
        return taximetrist;
    }

    public void setTaximetrist(Sofer taximetrist) {
        this.taximetrist = taximetrist;
    }

    public LocalDateTime getData() {
        return data;
    }

    public void setData(LocalDateTime data) {
        this.data = data;
    }

    @Override
    public String toString() {
        return "Comanda{" +
                "persoana=" + persoana +
                ", taximetrist=" + taximetrist +
                ", data=" + data +
                '}';
    }
}
