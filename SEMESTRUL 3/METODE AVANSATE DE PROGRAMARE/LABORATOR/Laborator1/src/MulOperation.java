import java.util.ArrayList;

public class MulOperation extends ComplexExpression{
    public MulOperation(ComplexNumber[] args) {
        super(Operation.MULTIPLICATION,args);
    }

    @Override
    protected ComplexNumber executeOneOperation(ComplexNumber a, ComplexNumber b) {
        return a.multiply(b);
    }
}
