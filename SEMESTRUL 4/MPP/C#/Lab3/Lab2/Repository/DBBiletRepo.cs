using Lab2.Domain;
using System;
using System.Collections.Generic;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using static Lab2.Repository.DBBiletRepo;
using log4net;
namespace Lab2.Repository
{
    internal class DBBiletRepo:BiletRepo
    {
        private static readonly ILog log = LogManager.GetLogger(typeof(DBBiletRepo));
        private IDictionary<string, string> props;

        public DBBiletRepo(IDictionary<string, string> props)
        {
            log.Info("Initializing DBBiletRepo");
            this.props = props;
        }

        public void Add(Bilet elem)
        {
            log.InfoFormat("Saving bilet {0}", elem);
            IDbConnection con = DBUtils.GetConnection(props);
            using (var comm = con.CreateCommand())
                {
                    comm.CommandText = "INSERT INTO bilet(numeclient, nrlocuri, id_spectacol) VALUES (@numeclient, @nrlocuri, @id_spectacol)";

                    var paramNume = comm.CreateParameter();
                    paramNume.ParameterName = "@numeclient";
                    paramNume.Value = elem.NumeClient;
                    comm.Parameters.Add(paramNume);

                    var paramLocuri = comm.CreateParameter();
                    paramLocuri.ParameterName = "@nrlocuri";
                    paramLocuri.Value = elem.NrLocuri;
                    comm.Parameters.Add(paramLocuri);

                    var paramSpectacol = comm.CreateParameter();
                    paramSpectacol.ParameterName = "@id_spectacol";
                    paramSpectacol.Value = elem.Spectacol.Id;
                    comm.Parameters.Add(paramSpectacol);

                    var result = comm.ExecuteNonQuery();
                    log.InfoFormat("Saved {0} instances", result);
                }
        }

        public void Update(Bilet elem)
        {
            log.InfoFormat("Updating bilet with id {0}", elem.Id);
            IDbConnection con = DBUtils.GetConnection(props);
            
            using (var comm = con.CreateCommand())
                {
                    comm.CommandText = "UPDATE bilet SET numeclient = @numeclient, nrlocuri = @nrlocuri, id_spectacol = @id_spectacol WHERE id = @id";

                    var paramNume = comm.CreateParameter();
                    paramNume.ParameterName = "@numeclient";
                    paramNume.Value = elem.NumeClient;
                    comm.Parameters.Add(paramNume);

                    var paramLocuri = comm.CreateParameter();
                    paramLocuri.ParameterName = "@nrlocuri";
                    paramLocuri.Value = elem.NrLocuri;
                    comm.Parameters.Add(paramLocuri);

                    var paramSpectacol = comm.CreateParameter();
                    paramSpectacol.ParameterName = "@id_spectacol";
                    paramSpectacol.Value = elem.Spectacol.Id;
                    comm.Parameters.Add(paramSpectacol);

                    var paramId = comm.CreateParameter();
                    paramId.ParameterName = "@id";
                    paramId.Value = elem.Id;
                    comm.Parameters.Add(paramId);

                    var result = comm.ExecuteNonQuery();
                    log.InfoFormat("Updated {0} records", result);
                }
            
        }

        public void Delete(int id)
        {
            log.InfoFormat("Deleting bilet with id {0}", id);
            IDbConnection con = DBUtils.GetConnection(props);
            using (var comm = con.CreateCommand())
            {
                    comm.CommandText = "DELETE FROM bilet WHERE id = @id";
                    var paramId = comm.CreateParameter();
                    paramId.ParameterName = "@id";
                    paramId.Value = id;
                    comm.Parameters.Add(paramId);

                    var result = comm.ExecuteNonQuery();
                    log.InfoFormat("Deleted {0} records", result);
            }
        }

        public IEnumerable<Bilet> FindAll()
        {
            log.Info("Finding all bilete");
            IList<Bilet> bilete = new List<Bilet>();
            IDbConnection con = DBUtils.GetConnection(props);
            using (var comm = con.CreateCommand())
            {
                    comm.CommandText = "SELECT * FROM bilet";
                    using (var dataR = comm.ExecuteReader())
                    {
                        while (dataR.Read())
                        {
                            int id = dataR.GetInt32(0);
                            string numeClient = dataR.GetString(2);
                            int nrLocuri = dataR.GetInt32(1);
                            int idSpectacol = dataR.GetInt32(3);
                            Spectacol spectacol = FindSpectacolById(idSpectacol);
                            Bilet bilet = new Bilet(nrLocuri, spectacol, numeClient) { Id = id };
                            bilete.Add(bilet);
                        }
                    }
                
            }
            return bilete;
        }

        public Bilet FindOne(int id)
        {
            log.InfoFormat("Finding bilet with id {0}", id);
            IDbConnection con = DBUtils.GetConnection(props);
            using (var comm = con.CreateCommand())
            {
                    comm.CommandText = "SELECT * FROM bilet WHERE id = @id";
                    var paramId = comm.CreateParameter();
                    paramId.ParameterName = "@id";
                    paramId.Value = id;
                    comm.Parameters.Add(paramId);

                    using (var dataR = comm.ExecuteReader())
                    {
                        if (dataR.Read())
                        {
                            string numeClient = dataR.GetString(1);
                            int nrLocuri = dataR.GetInt32(2);
                            int idSpectacol = dataR.GetInt32(3);
                            Spectacol spectacol = FindSpectacolById(idSpectacol);
                            return new Bilet(nrLocuri, spectacol, numeClient) { Id = id };
                        }
                    }
            }
            log.Info("Bilet not found");
            return null;
        }

        private Spectacol FindSpectacolById(int id)
        {
            log.InfoFormat("Finding spectacol with id {0}", id);
            IDbConnection con = DBUtils.GetConnection(props);
            using (var comm = con.CreateCommand())
                {
                    comm.CommandText = "SELECT * FROM spectacol WHERE id = @id";
                    var paramId = comm.CreateParameter();
                    paramId.ParameterName = "@id";
                    paramId.Value = id;
                    comm.Parameters.Add(paramId);

                    using (var dataR = comm.ExecuteReader())
                    {
                        if (dataR.Read())
                        {
                            DateTime data = DateTime.Parse(dataR.GetString(1));
                            string artist = dataR.GetString(2);
                            string locatie = dataR.GetString(3);
                            int nrLocuriDisponibile = dataR.GetInt32(4);
                            int nrLocuriOcupate = dataR.GetInt32(5);
                            return new Spectacol(data, artist, locatie, nrLocuriDisponibile, nrLocuriOcupate) { Id = id };
                        }
                    }
            }
            log.Info("Spectacol not found");
            return null;
        }

        public IEnumerable<Bilet> FindBySpectacol(Spectacol spectacol)
        {
            log.InfoFormat("Finding bilete for spectacol with id {0}", spectacol.Id);
            IList<Bilet> bilete = new List<Bilet>();
            IDbConnection con = DBUtils.GetConnection(props);
            using (var comm = con.CreateCommand())
                {
                    comm.CommandText = "SELECT * FROM bilet WHERE id_spectacol = @id_spectacol";

                    var paramIdSpectacol = comm.CreateParameter();
                    paramIdSpectacol.ParameterName = "@id_spectacol";
                    paramIdSpectacol.Value = spectacol.Id;
                    comm.Parameters.Add(paramIdSpectacol);

                    using (var dataR = comm.ExecuteReader())
                    {
                        while (dataR.Read())
                        {
                           
                            int id = dataR.GetInt32(0); 
                            string numeClient = dataR.GetString(1); 
                            int nrLocuri = dataR.GetInt32(2); 
                            int idSpectacol = dataR.GetInt32(3); 
                            Bilet bilet = new Bilet(nrLocuri, spectacol, numeClient) { Id = id };
                            bilete.Add(bilet);
                        }
                    }
            }
            return bilete;
        }
    }

}
