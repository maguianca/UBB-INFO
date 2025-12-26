public class ComplexNumber
{
    private double real,imaginary;

    public ComplexNumber(double real, double imaginary) {
        this.real = real;
        this.imaginary = imaginary;
    }
    public ComplexNumber() {
        this.real = 0.0;
        this.imaginary = 0.0;
    }

    public double getReal() {
        return real;
    }

    public double getImaginary() {
        return imaginary;
    }

    public void setReal(double real) {
        this.real = real;
    }

    public void setImaginary(double imaginary) {
        this.imaginary = imaginary;
    }

    @Override
    public String toString() {
        if(imaginary>=0){
            return this.real+"+"+this.imaginary+"*i";
        }else{
            return this.real+""+this.imaginary+"*i";
        }
    }
    public ComplexNumber add(ComplexNumber other) {
        return new ComplexNumber(real+other.real, imaginary+other.imaginary);
    }
    public ComplexNumber subtract(ComplexNumber other) {
        return new ComplexNumber(real-other.real, imaginary-other.imaginary);
    }
    public ComplexNumber multiply(ComplexNumber other) {
        return new ComplexNumber(real*other.real-other.imaginary*imaginary, imaginary*other.real+other.imaginary*real);
    }
    public ComplexNumber divide(ComplexNumber other) {
       ComplexNumber numarator=multiply(conjugate(other));
       double numitor=other.real*other.real +other.imaginary*other.imaginary;
       return new ComplexNumber(numarator.real/numitor, numarator.imaginary/numitor);
    }
    public ComplexNumber conjugate(ComplexNumber other) {
        return new ComplexNumber(other.real,other.imaginary*(-1));
    }
}
