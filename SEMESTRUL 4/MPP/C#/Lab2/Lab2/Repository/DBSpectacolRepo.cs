using Lab2.Domain;
using System;
using System.Collections.Generic;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Lab2.Repository;
using log4net;
using System.Data.Common;
namespace Lab2.Repository
{
    internal class DBSpectacolRepo:SpectacolRepo
    {
        private static readonly ILog log = LogManager.GetLogger(typeof(DBSpectacolRepo));
        private readonly IDictionary<string, string> props;

        public DBSpectacolRepo(IDictionary<string, string> props)
        {
            log.Info("Initializing DBSpectacolRepo");
            this.props = props;
        }

        public void Add(Spectacol spectacol)
        {
            log.InfoFormat("Saving spectacol {0}", spectacol);
            IDbConnection con = DBUtils.GetConnection(props);
            using (var comm = con.CreateCommand())
                {
                    comm.CommandText = "INSERT INTO spectacol(data, locatie, artist, nrlocuridisponibile, nrlocuriocupate) VALUES (@data, @locatie, @artist, @nrlocuridisponibile, @nrlocuriocupate)";
                    var dataParam = comm.CreateParameter();
                    dataParam.ParameterName = "@data";
                    dataParam.Value = spectacol.Data.ToString("yyyy-MM-dd HH:mm:ss");
                    comm.Parameters.Add(dataParam);

                    var locatieParam = comm.CreateParameter();
                    locatieParam.ParameterName = "@locatie";
                    locatieParam.Value = spectacol.Locatie;
                    comm.Parameters.Add(locatieParam);

                    var artistParam = comm.CreateParameter();
                    artistParam.ParameterName = "@artist";
                    artistParam.Value = spectacol.Artist;
                    comm.Parameters.Add(artistParam);

                    var nrLocuriDisponibileParam = comm.CreateParameter();
                    nrLocuriDisponibileParam.ParameterName = "@nrlocuridisponibile";
                    nrLocuriDisponibileParam.Value = spectacol.NrLocuriDisponibile;
                    comm.Parameters.Add(nrLocuriDisponibileParam);

                    var nrLocuriOcupateParam = comm.CreateParameter();
                    nrLocuriOcupateParam.ParameterName = "@nrlocuriocupate";
                    nrLocuriOcupateParam.Value = spectacol.NrLocuriOcupate;
                    comm.Parameters.Add(nrLocuriOcupateParam);

                    var result = comm.ExecuteNonQuery();
                    log.InfoFormat("Saved {0} instances", result);
                }
            
        }

        public void Update(Spectacol spectacol)
        {
            log.InfoFormat("Updating spectacol with id {0}", spectacol.Id);
            IDbConnection con = DBUtils.GetConnection(props);
            using (var comm = con.CreateCommand())
                {
                    comm.CommandText = "UPDATE spectacol SET data=@data, locatie=@locatie, artist=@artist, nrlocuridisponibile=@nrlocuridisponibile, nrlocuriocupate=@nrlocuriocupate WHERE id=@id";

                    var dataParam = comm.CreateParameter();
                    dataParam.ParameterName = "@data";
                    dataParam.Value = spectacol.Data.ToString("yyyy-MM-dd HH:mm:ss");
                    comm.Parameters.Add(dataParam);

                    var locatieParam = comm.CreateParameter();
                    locatieParam.ParameterName = "@locatie";
                    locatieParam.Value = spectacol.Locatie;
                    comm.Parameters.Add(locatieParam);

                    var artistParam = comm.CreateParameter();
                    artistParam.ParameterName = "@artist";
                    artistParam.Value = spectacol.Artist;
                    comm.Parameters.Add(artistParam);

                    var nrLocuriDisponibileParam = comm.CreateParameter();
                    nrLocuriDisponibileParam.ParameterName = "@nrlocuridisponibile";
                    nrLocuriDisponibileParam.Value = spectacol.NrLocuriDisponibile;
                    comm.Parameters.Add(nrLocuriDisponibileParam);

                    var nrLocuriOcupateParam = comm.CreateParameter();
                    nrLocuriOcupateParam.ParameterName = "@nrlocuriocupate";
                    nrLocuriOcupateParam.Value = spectacol.NrLocuriOcupate;
                    comm.Parameters.Add(nrLocuriOcupateParam);

                    var idParam = comm.CreateParameter();
                    idParam.ParameterName = "@id";
                    idParam.Value = spectacol.Id;
                    comm.Parameters.Add(idParam);

                    var result = comm.ExecuteNonQuery();
                    log.InfoFormat("Updated {0} records", result);
                }
            
        }

        public IEnumerable<Spectacol> FindAll()
        {
            log.Info("Finding all spectacole");
            IList<Spectacol> spectacole = new List<Spectacol>();
            IDbConnection con = DBUtils.GetConnection(props);
            using (var comm = con.CreateCommand())
                {
                    comm.CommandText = "SELECT * FROM spectacol";
                    using (var dataR = comm.ExecuteReader())
                    {
                        while (dataR.Read())
                        {
                            Spectacol spectacol = new Spectacol(
                        DateTime.Parse(dataR.GetString(dataR.GetOrdinal("data"))),
                        dataR.GetString(dataR.GetOrdinal("locatie")),
                        dataR.GetString(dataR.GetOrdinal("artist")),
                        dataR.GetInt32(dataR.GetOrdinal("nrlocuridisponibile")),
                        dataR.GetInt32(dataR.GetOrdinal("nrlocuriocupate"))
                    );
                            spectacole.Add(spectacol);
                        }
                    }
                }
            return spectacole;
        }

        public void Delete(int id)
        {
            log.InfoFormat("Deleting spectacol with id {0}", id);
            IDbConnection con = DBUtils.GetConnection(props);
            using (var comm = con.CreateCommand())
                {
                    comm.CommandText = "DELETE FROM spectacol WHERE id = @id";
                    var idParam = comm.CreateParameter();
                    idParam.ParameterName = "@id";
                    idParam.Value = id;
                    comm.Parameters.Add(idParam);

                    var result = comm.ExecuteNonQuery();
                    log.InfoFormat("Deleted {0} records", result);
                }
        }

        public Spectacol? FindByDataAndArtist(string data, string artist)
        {
            log.InfoFormat("Finding spectacol with data {0} and artist {1}", data, artist);
            IDbConnection con = DBUtils.GetConnection(props);
            using (var comm = con.CreateCommand())
                {
                    comm.CommandText = "SELECT * FROM spectacol WHERE data = @data AND artist = @artist";

                    var dataParam = comm.CreateParameter();
                    dataParam.ParameterName = "@data";
                    dataParam.Value = data;
                    comm.Parameters.Add(dataParam);

                    var artistParam = comm.CreateParameter();
                    artistParam.ParameterName = "@artist";
                    artistParam.Value = artist;
                    comm.Parameters.Add(artistParam);

                    using (var dataR = comm.ExecuteReader())
                    {
                        if (dataR.Read())
                        {
                           
                            return new Spectacol(
                                DateTime.Parse(dataR.GetString(dataR.GetOrdinal("data"))),
                                dataR.GetString(dataR.GetOrdinal("locatie")),
                                dataR.GetString(dataR.GetOrdinal("artist")),
                                dataR.GetInt32(dataR.GetOrdinal("nrlocuridisponibile")),
                                dataR.GetInt32(dataR.GetOrdinal("nrlocuriocupate"))
                            );
                        }
                        else
                        {
                            
                            return null;
                        }
                    }
                }
        }
        public Spectacol? FindOne(int id)
        {
            log.InfoFormat("Finding spectacol with id {0}", id);
            IDbConnection con = DBUtils.GetConnection(props);
            using (var comm = con.CreateCommand())
                {
       
                    comm.CommandText = "SELECT * FROM spectacol WHERE id = @id";
                    var idParam = comm.CreateParameter();
                    idParam.ParameterName = "@id";
                    idParam.Value = id;
                    comm.Parameters.Add(idParam);

                    using (var dataR = comm.ExecuteReader())
                    {
                        if (dataR.Read()) 
                        {
                
                            return new Spectacol(
                                DateTime.Parse(dataR.GetString(dataR.GetOrdinal("data"))),
                                dataR.GetString(dataR.GetOrdinal("locatie")),
                                dataR.GetString(dataR.GetOrdinal("artist")),
                                dataR.GetInt32(dataR.GetOrdinal("nrlocuridisponibile")),
                                dataR.GetInt32(dataR.GetOrdinal("nrlocuriocupate"))
                            );
                        }
                        else
                        {
                            
                            log.InfoFormat("Spectacol with id {0} not found", id);
                            return null;
                        }
                    }
                }
        }

    }

}

