package com.example.examen.domeniu;

public class Notificare {
    private Integer id;
    private Integer centruid;
    private Integer animalid;
    private Integer centrualocat;
    public Notificare(Integer id,Integer centruid,Integer animalid,Integer centrualocat){
        this.id=id;
        this.centruid=centruid;
        this.animalid=animalid;
        this.centrualocat=this.centrualocat;
    }

    public Integer getId() {
        return id;
    }

    public void setId(Integer id) {
        this.id = id;
    }

    public Integer getCentreid() {
        return centruid;
    }

    public void setCentreid(Integer centruid) {
        this.centruid = centruid;
    }

    public Integer getAnimalid() {
        return animalid;
    }

    public void setAnimalid(Integer animalid) {
        this.animalid = animalid;
    }

    public Integer getCentruid() {
        return centruid;
    }

    public void setCentruid(Integer centruid) {
        this.centruid = centruid;
    }

    public Integer getCentrualocat() {
        return centrualocat;
    }

    public void setCentrualocat(Integer centrualocat) {
        this.centrualocat = centrualocat;
    }

    @Override
    public String toString() {
        return "Notificare{" +
                "id=" + id +
                ", centruid=" + centruid +
                ", animalid=" + animalid +
                '}';
    }
}
