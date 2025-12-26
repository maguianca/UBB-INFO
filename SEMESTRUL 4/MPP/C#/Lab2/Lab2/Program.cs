using Lab2.Domain;
using Lab2.Repository;
using log4net;
using log4net.Config;
using System.Configuration;
using System.Reflection;

namespace Lab2
{
    internal class Program
    {
        static string GetConnectionStringByName(string name)
        {
            string returnValue = null;
            ConnectionStringSettings settings = ConfigurationManager.ConnectionStrings[name];
            if (settings != null)
                returnValue = settings.ConnectionString;

            return returnValue;
        }
        private static readonly log4net.ILog logger = log4net.LogManager.GetLogger(System.Reflection.MethodBase.GetCurrentMethod().DeclaringType);
        
        static void Main(string[] args)
        {
            string configFilePath = Path.Combine(AppDomain.CurrentDomain.BaseDirectory, "log4net.config");
            FileInfo fileInfo;

            try
            {
                fileInfo = new System.IO.FileInfo(configFilePath);
            }
            catch (Exception e)
            {
                Console.WriteLine(e);
                throw;
            }

            // XmlConfigurator.Configure(fileInfo);
            XmlConfigurator.Configure(new FileInfo("log4net.config"));
            var logRepository = LogManager.GetRepository(Assembly.GetEntryAssembly());
            log4net.Util.LogLog.InternalDebugging = true;
            //XmlConfigurator.Configure(logRepository, new FileInfo("./log4net.config"));
            //Console.WriteLine("Configuration Settings for tasksDB {0}", GetConnectionStringByName("ticket_sales"));
            
            //Console.WriteLine($"Current Directory: {Environment.CurrentDirectory}");
            //Console.WriteLine($"Base Directory: {AppDomain.CurrentDomain.BaseDirectory}");

            IDictionary<String, string> props = new SortedList<String, String>();
            props.Add("ConnectionString", GetConnectionStringByName("festival"));
            Console.WriteLine("festival Repository DB ...");
            AngajatRepo angajatRepository = new DBAngajatRepo(props);
            BiletRepo biletRepository = new DBBiletRepo(props);
            SpectacolRepo spectacolRepository = new DBSpectacolRepo(props);
            //angajatRepository.Add(new Angajat("Ma", "00", "Mac"));
            //angajatRepository.Add(new Angajat("Maricica", "0000", "Mari"));
            var angajati = angajatRepository.FindAll();
            Console.WriteLine("Angajati:");
            foreach (var angajat in angajati)
            {
                Console.WriteLine(angajat);
            }
            //angajatRepository.Delete(8);
            Angajat a = new Angajat("Ela", "0000", "Marcela");
            a.Id = 7;
            //angajatRepository.Update(a);
            // Console.WriteLine(biletRepository.FindAll());
            DateTime dataSpectacol = DateTime.Parse("2025-12-12T20:00");
            //spectacolRepository.Add(new Spectacol(dataSpectacol, "Mures", "Conecte-R", 30, 100));
            var spectacole = spectacolRepository.FindAll();
            Console.WriteLine("Spectacole:");
            foreach (var spectacol in spectacole)
            {
                Console.WriteLine(spectacol);
            }
            
            var bilete = biletRepository.FindAll();
            Console.WriteLine("Bilete:");
            foreach (var bil in bilete)
            {
                Console.WriteLine(bil);
            }

            //Spectacol spectacols = new Spectacol();
            //spectacols.Id = 4;

            //biletRepository.Save(new Bilet("heh", "jgg", spectacols, 2))
            logger.Info("Hello world- Friday 21th March");

        }
    }
}
