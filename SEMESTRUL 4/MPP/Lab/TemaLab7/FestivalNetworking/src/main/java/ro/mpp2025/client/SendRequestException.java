package ro.mpp2025.client;

import ro.mpp2025.Service.ServiceException;

public class SendRequestException extends ServiceException {
    public SendRequestException(String s) {
        super(s);
    }
}
