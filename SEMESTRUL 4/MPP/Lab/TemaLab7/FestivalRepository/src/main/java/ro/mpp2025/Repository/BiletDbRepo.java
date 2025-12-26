package ro.mpp2025.Repository;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import ro.mpp2025.Domain.Bilet;
import ro.mpp2025.Domain.Spectacol;

import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.Properties;

public class BiletDbRepo extends DatabaseRepoUtils<Integer, Bilet>
        implements IBiletRepo {

    private static final Logger logger = LogManager.getLogger(BiletDbRepo.class);

    ISpectacolRepo spectacolRepo;
    private JdbcUtils dbUtils;

    public BiletDbRepo(Properties props, ISpectacolRepo spectacolRepo) {
        super(props);
        this.spectacolRepo = spectacolRepo;
        dbUtils=new JdbcUtils(props);
    }

    @Override
    public Bilet decodeResult(ResultSet result) throws SQLException, EntityRepoException {
        var id = result.getInt("id");
        var numeCumparator = result.getString("numeCumparator");
        var nrLocuri = result.getInt("nrLocuri");
        var spectacolId = result.getInt("spectacol");
        var spectacol = spectacolRepo.getById(spectacolId);
        var bilet = new Bilet(numeCumparator, nrLocuri, spectacol);
        bilet.setId(id);
        return bilet;
    }

    @Override
    public Iterable<Bilet> getBySpectacol(Spectacol spectacol) throws EntityRepoException {
        return select("SELECT * FROM Bilet WHERE spectacol = ?", spectacol);
    }

    @Override
    public void add(Bilet bilet) throws EntityRepoException {
        logger.trace("Inserting {}", bilet);

        executeNonQuery("INSERT INTO Bilet (numeCumparator, nrLocuri, spectacol) VALUES (?, ?, ?)",
                bilet.getNumeCumparator(),
                bilet.getNrLocuri(),
                bilet.getSpectacol().getId());

        logger.info("Inserted successfully");
        logger.traceExit();
    }

    @Override
    public void update(Bilet bilet) throws EntityRepoException {
        logger.trace("Updating bilet {}", bilet);
        executeNonQuery("UPDATE Bilet SET " +
                        "numeCumparator = ?, " +
                        "nrLocuri = ?, " +
                        "spectacol = ? " +
                        "WHERE id = ?",
                bilet.getNumeCumparator(),
                bilet.getNrLocuri(),
                bilet.getSpectacol().getId(),
                bilet.getId());
        logger.info("Updated bilet {}", bilet);
        logger.traceExit();
    }

    @Override
    public void remove(Integer id) throws EntityRepoException {
        logger.trace("Removing bilet id={}", id);
        executeNonQuery("DELETE FROM Bilet WHERE id = ?", id);
        logger.info("Removed bilet id={}", id);
        logger.traceExit();
    }

    @Override
    public Bilet getById(Integer id) throws EntityRepoException {
        return selectFirst("SELECT * FROM Bilet WHERE id = ?", id);
    }

    @Override
    public Iterable<Bilet> getAll() throws EntityRepoException {
        return select("SELECT * FROM Bilet");
    }
}
