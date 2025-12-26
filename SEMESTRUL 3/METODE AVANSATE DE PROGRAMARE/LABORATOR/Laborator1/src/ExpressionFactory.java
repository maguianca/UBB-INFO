import java.util.ArrayList;
public class ExpressionFactory {
    private static ExpressionFactory instance;
    public static ExpressionFactory getInstance() {
        if(instance == null) {
            instance=new ExpressionFactory();
        }
        return instance;
    }
    public ComplexExpression createExpression(Operation operation,ComplexNumber[] args) {
        switch(operation) {
            case ADDITION:
                return new AddOperation(args);
            case SUBSTRACTION:
                return new SubOperation(args);
            case DIVISION:
                return new DivOperation(args);
            case MULTIPLICATION:
                return new MulOperation(args);
            default:
                throw new IllegalArgumentException("Invalid operator!");
        }
    }
}
