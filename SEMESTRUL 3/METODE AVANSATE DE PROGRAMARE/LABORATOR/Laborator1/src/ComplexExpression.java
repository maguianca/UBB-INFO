import java.util.ArrayList;

public abstract class ComplexExpression {
    protected Operation operation;
    protected ComplexNumber[]args;

    public ComplexExpression(Operation operation,ComplexNumber[]args) {
        this.args=args;
        this.operation=operation;
    }
    public ComplexNumber execute() {
        ComplexNumber res=args[0];
        for(int i=1;i<args.length;i++){
            res=executeOneOperation(res,args[i]);
            //System.out.println("iteratia i:"+i +"rezult:" +res);
        }
        return res;
    }
    protected abstract ComplexNumber executeOneOperation(ComplexNumber a, ComplexNumber b);
}
