package ro.mpp2025.Server;

import ro.mpp2025.client.ClientObjectWorker;
import ro.mpp2025.Service.IAppService;

import java.net.Socket;
///trateaza mai multi clienti o data
public class ObjectConcurrentServer extends ConcurrentServer {
    private final IAppService server;
    public ObjectConcurrentServer(int port, IAppService service) {
        super(port);
        this.server=service;
    }

    @Override
    protected Thread createWorker(Socket client) {
        ClientObjectWorker worker=new ClientObjectWorker(server, client);
        return new Thread(worker);
    }
}
///fiecare client va avea un worker care va lucra cu serverul

