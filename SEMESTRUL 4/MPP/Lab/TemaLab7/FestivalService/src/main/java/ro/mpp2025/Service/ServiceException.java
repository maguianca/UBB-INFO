package ro.mpp2025.Service;

import ro.mpp2025.Repository.EntityRepoException;

public class ServiceException extends Exception {
    public ServiceException(String message) {
        super(message);
    }

    public ServiceException(EntityRepoException e) {
        super(e);
    }
}
