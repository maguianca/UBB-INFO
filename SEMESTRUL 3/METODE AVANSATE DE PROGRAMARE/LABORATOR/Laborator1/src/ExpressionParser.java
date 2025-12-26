
import java.security.InvalidParameterException;
import java.util.ArrayList;
import java.util.regex.Pattern;

public class ExpressionParser {
    private final String[] args;

    public ExpressionParser(String[] args) {
        this.args = args;
    }

    private boolean isComplexNumberValid(String toParse) {
        if (Pattern.matches("^i$", toParse)) {
            return true;
        }
        //+- (a+b*i)
        if (Pattern.matches("^(-{0,1}([0-9]+(.[0-9]+)*))*[+-]{0,1}([0-9]+(.[0-9]+)*\\*i+)*$", toParse)) {
            return true;
        }
        // +- (a+i)
        return Pattern.matches("^(-{0,1}([0-9]+(.[0-9]+)*))*[+-]{0,1}(i+)*$", toParse);
    }

    private boolean isOperatorValid(String toCheck) {
        return "+".equals(toCheck) || "-".equals(toCheck) || "*".equals(toCheck) || "/".equals(toCheck);
    }
    private Operation OperatorType(String toCheck) {
        switch (toCheck) {
            case "+":
                return Operation.ADDITION;
            case "-":
                return Operation.SUBSTRACTION;
            case "*":
                return Operation.MULTIPLICATION;
            case "/":
                return Operation.DIVISION;
            default:
                return null;
        }
    }
    private void verifyExpression() {
        if(args.length%2==0||args.length<3)
        {
            throw new InvalidParameterException("Invalid Expression");
        }

        for(int i=0;i<args.length;i++)
        {
            if(i%2==0)
            {
                if(!isComplexNumberValid(args[i]))
                {
                    throw new InvalidParameterException("Invalid Expression: Invalid complex number at index " + i + ": " + args[i]);
                }
            }
            else
            {
                if (!isOperatorValid(args[i])) {
                    throw new InvalidParameterException("Invalid Expression: Invalid operator at index " + i + ": " + args[i]);
                }
            }
        }

    }
    public ComplexNumber parse() {
        verifyExpression();
        Operation op = OperatorType(args[1]);
        ComplexNumber[] numbers = new ComplexNumber[(args.length +1)/ 2];
        for (int i = 0; i < args.length; i++) {
            if (i % 2 == 0) {
                int neg = 0;
                String[] el = args[i].split("[+]",2);
                if (el.length != 2) {
                    el = args[i].split("-", 2);
                    neg = 1;
                }
                double re = Double.parseDouble(el[0]);
                String[] ima = el[1].split("[*]", 2);
                double im = Double.parseDouble(ima[0]);
                if (neg == 1) {
                    im = -im;
                }
                //System.out.println("iteratia :"+i +"re: "+ re+ " im: "+ im);
                ComplexNumber nr = new ComplexNumber(re, im);
                numbers[i / 2] = nr;
            } else {
                op = OperatorType(args[i]);
            }
        }
        return ExpressionFactory.getInstance().createExpression(op, numbers).execute();
    }

}
/*
import java.security.InvalidParameterException;
import java.util.regex.Pattern;

public class ExpressionParser {
    private final String[] args;

    public ExpressionParser(String[] args) {
        this.args = args;
    }
    private boolean isComplexNumberValid(String toParse) {
        //i
        if (Pattern.matches("^i$", toParse)) {
            return true;
        }
        // +- (a+b*i)
        if (Pattern.matches("^(-{0,1}([0-9]+(.[0-9]+)*))*[+-]{0,1}([0-9]+(.[0-9]+)*\\*i+)*$", toParse)) {
            return true;
        }
        //+- (a+i)
        return Pattern.matches("^(-{0,1}([0-9]+(.[0-9]+)*))*[+-]{0,1}(i+)*$", toParse);

    }

    private boolean isOperatorValid(String toCheck) {
        return "+".equals(toCheck) || "-".equals(toCheck) || "*".equals(toCheck) || "/".equals(toCheck);
    }

    private void verifyExpression() {
        if (args.length % 2 == 0 || args.length < 3) {
            throw new InvalidParameterException("Invalid Expression");
        }

        for (int i = 0; i < args.length; i++) {
            if (i % 2 == 0) {
                if (!isComplexNumberValid(args[i])) {
                    throw new InvalidParameterException("Invalid complex number at index " + i + ": " + args[i]);
                }
            } else {
                if (!isOperatorValid(args[i])) {
                    throw new InvalidParameterException("Invalid operator at index " + i + ": " + args[i]);
                }
            }
        }
    }

    private ComplexNumber complexNumberParser(String toParse) {
        double real = 0, imag = 0;
        String[] parts = toParse.split("(?=[+-])");

        for (String part : parts) {
            part = part.trim();
            if (part.contains("*i")) {
                imag = Double.parseDouble(part.replace("*i", ""));
            } else if (part.equals("i")) {
                imag = 1.0;
            } else {
                real = Double.parseDouble(part);
            }
        }

        return new ComplexNumber(real, imag);
    }
    public ComplexNumber parse() {
        verifyExpression();

        ComplexNumber result = complexNumberParser(args[0]);

        for (int i = 1; i < args.length; i += 2) {
            String operator = args[i];
            ComplexNumber nextNumber = complexNumberParser(args[i + 1]);

            switch (operator) {
                case "+":
                    result = result.add(nextNumber);
                    break;
                case "-":
                    result = result.subtract(nextNumber);
                    break;
                case "*":
                    result = result.multiply(nextNumber);
                    break;
                case "/":
                    result = result.divide(nextNumber);
                    break;
                default:
                    throw new InvalidParameterException("Invalid operator: " + operator);
            }
        }

        return result;
    }
}
 */