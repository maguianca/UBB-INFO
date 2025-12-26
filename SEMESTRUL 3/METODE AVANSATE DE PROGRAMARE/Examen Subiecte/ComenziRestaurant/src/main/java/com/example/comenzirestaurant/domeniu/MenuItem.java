package com.example.comenzirestaurant.domeniu;

public class MenuItem extends Entity<Long>{
    private String categorie;
    private Float pret;
    private String item;
    private String moneda;
    public MenuItem(String categorie, Float pret, String item, String moneda){
        this.categorie=categorie;
        this.pret=pret;
        this.item=item;
        this.moneda=moneda;
    }
    public String getCategorie(){
        return categorie;
    }
    public void setCategorie(String categorie){
        this.categorie=categorie;
    }
    public Float getPret(){
        return pret;
    }
    public void setPret(Float pret){
        this.pret=pret;
    }
    public String getItem(){
        return item;
    }
    public void setItem(String item){
        this.item=item;
    }
    public String getMoneda(){
        return moneda;
    }
    public void setMoneda(String moneda){
        this.moneda=moneda;
    }
    @Override
    public String toString() {
        return "MenuItem{" +
                "categorie='" + categorie + '\'' +
                ", pret=" + pret +
                ", item='" + item + '\'' +
                ", moneda='" + moneda + '\'' +
                '}';
    }

}
