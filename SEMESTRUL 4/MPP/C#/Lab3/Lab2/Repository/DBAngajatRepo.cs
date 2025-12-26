using Lab2.Domain;
using System;
using System.Collections.Generic;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Data.SQLite;
using log4net;
namespace Lab2.Repository
{
    internal class DBAngajatRepo : AngajatRepo
    {
        private static readonly ILog log = LogManager.GetLogger(typeof(DBAngajatRepo));
        private IDictionary<string, string> props;
        public DBAngajatRepo(IDictionary<string, string> props)
        {
            log.Info("Initializing DBAngajatRepo");
            this.props = props;

        }

        public void Add(Angajat elem)
        {
            log.Info($"Saving angajat {elem}");
            IDbConnection con = DBUtils.GetConnection(props);
            using (var comm = con.CreateCommand())
            {

                comm.CommandText = "INSERT INTO angajat (username, password, numeclient) VALUES (@username, @password, @numeclient)";

                var paramUsername = comm.CreateParameter();
                paramUsername.ParameterName = "@username";
                paramUsername.Value = elem.Username;
                comm.Parameters.Add(paramUsername);

                var paramPassword = comm.CreateParameter();
                paramPassword.ParameterName = "@password";
                paramPassword.Value = elem.Password;
                comm.Parameters.Add(paramPassword);

                var paramNume = comm.CreateParameter();
                paramNume.ParameterName = "@numeclient";
                paramNume.Value = elem.Nume;
                comm.Parameters.Add(paramNume);

                var result = comm.ExecuteNonQuery();
                if (result == 0)
                    throw new Exception("No angajat added!");

                log.InfoFormat("Angajat saved {0}", elem);
            }
        }
        public void Update(Angajat elem)
        {
            log.InfoFormat("Updating angajat with id {0}", elem.Id);
            IDbConnection con = DBUtils.GetConnection(props);
            using (var comm = con.CreateCommand())
            {
                comm.CommandText = "UPDATE angajat SET username = @username, password = @password, numeclient = @nume WHERE id = @id";

                var paramUsername = comm.CreateParameter();
                paramUsername.ParameterName = "@username";
                paramUsername.Value = elem.Username;
                comm.Parameters.Add(paramUsername);

                var paramPassword = comm.CreateParameter();
                paramPassword.ParameterName = "@password";
                paramPassword.Value = elem.Password;
                comm.Parameters.Add(paramPassword);

                var paramNume = comm.CreateParameter();
                paramNume.ParameterName = "@nume";
                paramNume.Value = elem.Nume;
                comm.Parameters.Add(paramNume);

                var paramId = comm.CreateParameter();
                paramId.ParameterName = "@id";
                paramId.Value = elem.Id;
                comm.Parameters.Add(paramId);

                var result = comm.ExecuteNonQuery();
                log.InfoFormat("Updated {0} records", result);
            }
        }

        public IEnumerable<Angajat> FindAll()
        {
            log.Info("Finding all angajati");
            IList<Angajat> angajati = new List<Angajat>();
            IDbConnection con = DBUtils.GetConnection(props);
            using (var comm = con.CreateCommand())
            {
                comm.CommandText = "SELECT * FROM angajat";
                using (var dataR = comm.ExecuteReader())
                {
                    while (dataR.Read())
                    {
                        int id = dataR.GetInt32(0);
                        string username = dataR.GetString(1);
                        string password = dataR.GetString(2);
                        string nume = dataR.GetString(3);
                        Angajat a = new Angajat(username, password, nume) { Id = id };
                        angajati.Add(a);
                    }
                }
            }
            return angajati;
      }

        public void Delete(int id)
        {
            log.InfoFormat("Deleting angajat with id {0}", id);
            IDbConnection con = DBUtils.GetConnection(props);
            using (var comm = con.CreateCommand())
            {
                    comm.CommandText = "DELETE FROM angajat WHERE id = @id";

                    var paramId = comm.CreateParameter();
                    paramId.ParameterName = "@id";
                    paramId.Value = id;
                    comm.Parameters.Add(paramId);

                    var result = comm.ExecuteNonQuery();
                    if (result == 0)
                        throw new Exception("No angajat deleted!");

                    log.InfoFormat("Deleted {0} records", result);
            }
        }

        public Angajat FindOne(int id)
        {
            log.InfoFormat("Finding angajat with id {0}", id);
            IDbConnection con = DBUtils.GetConnection(props);
            using (var comm = con.CreateCommand())
                {
                    comm.CommandText = "SELECT * FROM angajat WHERE id = @id";

                    var paramId = comm.CreateParameter();
                    paramId.ParameterName = "@id";
                    paramId.Value = id;
                    comm.Parameters.Add(paramId);

                    using (var dataR = comm.ExecuteReader())
                    {
                        if (dataR.Read())
                        {
                            string username = dataR.GetString(1);
                            string password = dataR.GetString(2);
                            string nume = dataR.GetString(3);
                            Angajat angajat = new Angajat(username, password, nume) { Id = id };
                            return angajat;
                        }
                    }
                }
            log.Info("Angajat not found");
            return null;
        }

        public Angajat FindByUsernamePass(string username, string password)
        {
            log.InfoFormat("Finding angajat with username {0} and password {1}", username, password);
            IDbConnection con = DBUtils.GetConnection(props);
            using (var comm = con.CreateCommand())
                {
                    comm.CommandText = "SELECT * FROM angajat WHERE username = @username AND password = @password";

                    var paramUsername = comm.CreateParameter();
                    paramUsername.ParameterName = "@username";
                    paramUsername.Value = username;
                    comm.Parameters.Add(paramUsername);

                    var paramPassword = comm.CreateParameter();
                    paramPassword.ParameterName = "@password";
                    paramPassword.Value = password;
                    comm.Parameters.Add(paramPassword);

                    using (var dataR = comm.ExecuteReader())
                    {
                        if (dataR.Read())
                        {
                            int id = dataR.GetInt32(0);
                            string nume = dataR.GetString(3);
                            Angajat angajat = new Angajat(username, password, nume) { Id = id };
                            return angajat;
                        }
                    }
            }
            log.Info("Angajat not found");
            return null;
        }
    }
}

