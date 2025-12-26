import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.Callable;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;

class EmailSender {
    private String message;
    public EmailSender(String s) { message=s;}
    public String run() {
        System.out.print(message+" ");
        return "done";
    }
}
public class G10 {
    public static void main(String[] args)
            throws InterruptedException {
        ExecutorService executor =
                Executors.newFixedThreadPool(3);
        List<Callable<String>> l=new ArrayList<>();
        for (int i = 1; i < 3; i++) {
            Callable<String> worker = new
                    EmailSender("meeting"+i)::run;
            l.add(worker);
        }
        List<Future<String>> futures = executor.invokeAll(l);
        executor.shutdown();
    }
}