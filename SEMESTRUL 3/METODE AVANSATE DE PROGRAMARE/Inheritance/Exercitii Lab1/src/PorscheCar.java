public class PorscheCar extends Car{

    private String model;

    public PorscheCar(int year, double price, String model){
        super(year, price);
        this.model = model;
    }

    public String toString(){
        return "Porsche "+ this.model +" is made in "+this.getYear()+ " and it cots "+this.getPrice();
    }
}
