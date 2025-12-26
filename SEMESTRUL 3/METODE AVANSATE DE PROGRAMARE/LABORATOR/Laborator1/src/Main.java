import java.security.InvalidParameterException;

public class Main {
    public static void main(String[] args) {
        try{
            ComplexNumber res=new ExpressionParser(args).parse();
            System.out.println(res.toString());
        }catch(InvalidParameterException mes){
            System.out.println(mes);
        }
    }
}