import java.util.ArrayList;
public class DivOperation extends ComplexExpression{
    public DivOperation(ComplexNumber[] args) {
        super(Operation.DIVISION,args);
    }
    @Override
    protected ComplexNumber executeOneOperation(ComplexNumber a, ComplexNumber b) {
       return a.divide(b);
    }
}
