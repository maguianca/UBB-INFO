import java.util.ArrayList;

public class SubOperation extends ComplexExpression {
    public SubOperation(ComplexNumber[] args) {
        super(Operation.SUBSTRACTION,args);

    }

    @Override
    protected ComplexNumber executeOneOperation(ComplexNumber a, ComplexNumber b) {
        return a.subtract(b);
    }
}
