public class Car {

    private int year;
    private double price;

    //default constructor
    public Car() {

    }

    //constructor with parameters
    public Car(int year, double price) {
        this.year = year;
        this.price = price;
    }

    public int getYear() {
        return year;
    }

    public double getPrice() {
        return price;
    }

    public String toString() {
        return "This car is made in " + this.year + " and it costs " + this.price;
    }
}
