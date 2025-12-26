package ro.mpp2025.exceptions;

public class ServerProcessingException extends Throwable {
    public ServerProcessingException(Exception e) {
        super(e);
    }
}
