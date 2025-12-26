import java.util.ArrayList;

public class AddOperation extends ComplexExpression {
    public AddOperation(ComplexNumber[] args) {
        super(Operation.ADDITION,args);
    }
    @Override
    protected ComplexNumber executeOneOperation(ComplexNumber a,ComplexNumber b) {
        return a.add(b);
    }
}
