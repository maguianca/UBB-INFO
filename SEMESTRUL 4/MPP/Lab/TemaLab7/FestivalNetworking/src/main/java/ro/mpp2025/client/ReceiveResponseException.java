package ro.mpp2025.client;

import ro.mpp2025.Service.ServiceException;

public class ReceiveResponseException extends ServiceException {
    public ReceiveResponseException(String msg) {
        super(msg);
    }
}
