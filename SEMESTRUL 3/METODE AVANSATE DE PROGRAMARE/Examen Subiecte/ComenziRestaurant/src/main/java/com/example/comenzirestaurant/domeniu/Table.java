package com.example.comenzirestaurant.domeniu;

public class Table extends Entity<Long>{
    private Long id;
    public Table(Long Id){
        this.id=Id;
    }
    public Long getId(){
        return id;
    }
    public void setId(Long id){
        this.id=id;
    }
    @Override
    public String toString() {
        return "Table{" +
                "id=" + id +
                '}';
    }
}
