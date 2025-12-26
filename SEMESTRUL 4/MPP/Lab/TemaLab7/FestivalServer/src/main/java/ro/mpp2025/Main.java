package ro.mpp2025;

import ro.mpp2025.Server.ObjectConcurrentServer;
import ro.mpp2025.Server.ServerException;
import ro.mpp2025.Repository.AngajatDbRepo;
import ro.mpp2025.Repository.BiletDbRepo;
import ro.mpp2025.Repository.SpectacolDbRepo;
import ro.mpp2025.Server.ServiceImplementation;
import ro.mpp2025.Service.*;

import java.io.FileReader;
import java.io.IOException;
import java.util.Properties;

public class Main {

    public static void main(String[] args) throws ServerException {
        var props = loadProperties();
        var angajatRepo = new AngajatDbRepo(props);
        var spectacolRepo =new SpectacolDbRepo(props);
        var biletRepo =new BiletDbRepo(props, spectacolRepo);

        var angajatService = new AngajatService(angajatRepo);
        var biletService = new BiletService(biletRepo);
        var spectacolService = new SpectacolService(spectacolRepo);

        var appService = new AppService(angajatService, biletService, spectacolService);
        var server = new ObjectConcurrentServer(15000, new ServiceImplementation(appService));
        server.start();
    }

    public static Properties loadProperties() {
        Properties props=new Properties();
        try {
            props.load(new FileReader("bd.conifg"));
        } catch (IOException e) {
            System.out.println("Cannot find bd.config "+e);
        }
        return props;
    }
}