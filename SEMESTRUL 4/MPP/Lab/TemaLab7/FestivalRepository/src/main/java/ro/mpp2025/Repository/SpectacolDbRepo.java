package ro.mpp2025.Repository;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import ro.mpp2025.Domain.Spectacol;

import java.sql.ResultSet;
import java.sql.SQLException;
import java.time.LocalDateTime;
import java.util.Properties;

public class SpectacolDbRepo extends DatabaseRepoUtils<Integer, Spectacol>
        implements ISpectacolRepo {

    private static final Logger logger = LogManager.getLogger(SpectacolDbRepo.class);
    private JdbcUtils dbUtils;

    public SpectacolDbRepo(Properties props) {
        super(props);
        logger.info("Initializing SpectacolDbRepo with properties: {} ", props);
        dbUtils=new JdbcUtils(props);
    }

    @Override
    public Spectacol decodeResult(ResultSet result) throws SQLException {
        var artist = result.getString("artist");
        String showDateStr = result.getString("data");
        LocalDateTime data = LocalDateTime.parse(showDateStr);
        var locatie = result.getString("locatie");
        var nrLocuriDisponibile = result.getInt("nrLocuriDisponibile");
        var nrLocuriVandute = result.getInt("nrLocuriVandute");
        var id = result.getInt("id");
        var spectacol = new Spectacol(artist, data, locatie, nrLocuriDisponibile, nrLocuriVandute);
        spectacol.setId(id);
        return spectacol;
    }

    @Override
    public void add(Spectacol spectacol) throws EntityRepoException {
        logger.trace("Inserting {}", spectacol);
        executeNonQuery("INSERT INTO Spectacol " +
                        "(artist, data, locatie, nrLocuriDisponibile, nrLocuriVandute) " +
                        "VALUES (?, ?, ?, ?, ?)",
                spectacol.getArtist(),
                spectacol.getData(),
                spectacol.getLocatie(),
                spectacol.getNrLocuriDisponibile(),
                spectacol.getNrLocuriVandute());
        logger.info("Inserted successfully");
        logger.traceExit();
    }

    @Override
    public void update(Spectacol spectacol) throws EntityRepoException {
        var sql = "UPDATE Spectacol SET " +
                "artist = ?, " +
                "data = ?, " +
                "locatie = ?, " +
                "nrLocuriDisponibile = ?, " +
                "nrLocuriVandute = ? " +
                "WHERE id = ?";
        logger.trace("Updating spectacol {}", spectacol);
        executeNonQuery(sql,
                spectacol.getArtist(),
                spectacol.getData(),
                spectacol.getLocatie(),
                spectacol.getNrLocuriDisponibile(),
                spectacol.getNrLocuriVandute(),
                spectacol.getId());
        logger.info("Updated spectacol {}", spectacol);
        logger.traceExit();
    }

    @Override
    public void remove(Integer integer) throws EntityRepoException {
        throw new EntityRepoException("Spectacol removal is not allowed");
    }

    @Override
    public Spectacol getById(Integer id) throws EntityRepoException {
        return selectFirst("SELECT * FROM Spectacol WHERE id = ?", id);
    }

    @Override
    public Iterable<Spectacol> getAll() throws EntityRepoException {
        return select("SELECT * FROM Spectacol");
    }

    @Override
    public Iterable<Spectacol> getBetweenDates(LocalDateTime start, LocalDateTime end) throws EntityRepoException {
        return select("SELECT * FROM Spectacol WHERE data BETWEEN ? AND ?", start, end);
    }
}
