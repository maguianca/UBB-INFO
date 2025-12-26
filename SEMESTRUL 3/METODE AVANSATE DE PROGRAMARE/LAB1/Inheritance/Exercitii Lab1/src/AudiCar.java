public class AudiCar extends Car{

    private String market;

    public AudiCar(int year, double price, String market) {
        super(year, price);
        this.market = market;
    }

    public String toString(){
        return "The audi car from the market "+this.market+ " is made in "+this.getYear()+ " and it costs "+ this.getPrice();
    }
}
