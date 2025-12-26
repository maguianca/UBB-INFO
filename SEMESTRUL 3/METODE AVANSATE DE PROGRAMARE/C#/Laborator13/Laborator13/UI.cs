using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Laborator13
{
    internal class UI
    {
        private Service service;
        public UI(Service service)
        {
            this.service = service;
        }
        private int readId()
        {
            int id;
            while (true)
            {
                Console.WriteLine("Id-ul:");
                string input = Console.ReadLine();

                if (int.TryParse(input, out id))
                {
                    return id;
                }
                else
                {
                    Console.WriteLine("Input invalid. Introduceți un număr întreg.");
                }
            }
        }
        private DateTime readDate()
        {
            Console.WriteLine("Data (formatul trebuie sa fie YYYY-MM-dd):");
            string input = Console.ReadLine();
            string format = "yyyy-MM-dd";
            DateTime parsedDate;
            if (DateTime.TryParseExact(input, format, null, System.Globalization.DateTimeStyles.None, out parsedDate))
            {
                return parsedDate;
            }
            else
            {
                Console.WriteLine("Data introdusa nu este valida. Te rog sa folosesti formatul YYYY-MM-dd.");
                return readDate();
            }
        }

        public void run()
        {
            while (true)
            {
                Console.WriteLine("\n");
                Console.WriteLine("---------------------MENIU-----------------------------");
                Console.WriteLine("0.Exit");
                Console.WriteLine("1.Jucatorii unei echipe");
                Console.WriteLine("2.Jucatorii activi ai unei echipe de la un anumit meci");
                Console.WriteLine("3.Meciurile dintr-o anumita perioada calendaristica");
                Console.WriteLine("4.Scorul de la un anumit meci");
                Console.WriteLine("5.Meciuri");
                Console.WriteLine("--------------------------------------------------");
                Console.WriteLine("\n");

                Console.Write("Dati o comanda : ");
                try
                {
                    int cmd = int.Parse(Console.ReadLine());
                    Echipa e;
                    Meci m;
                    switch (cmd)
                    {
                        case 0:
                            return;
                        case 1:
                            e = service.findEchipa(readId());
                            if (e == null) 
                            {
                                Console.WriteLine("Echipa nu a fost gasita!");
                                break;
                            }
                            Console.WriteLine($"Jucatorii echipei {e.echipa_nume} sunt:");
                            foreach (var jucator in service.jucatorii_echipei(e))
                                Console.WriteLine(jucator.elev_nume + " , " + jucator.elev_scoala);
                            break;
                        case 2:
                            e = service.findEchipa(readId());
                            if (e == null)
                            {
                                Console.WriteLine("Echipa nu a fost gasita!");
                                break;
                            }
                            m = service.findMeci(readId());
                            if (m == null) 
                            {
                                Console.WriteLine("Meciul nu a fost găsit!");
                                break;
                            }
                            Console.WriteLine($"Jucatorii activi ai echipei {e.echipa_nume} din meciul din {m.Data} sunt:");
                            foreach (var jucator in service.jucatori_activi_meci(e, m))
                            {
                                Console.WriteLine(jucator.elev_nume + " , " + jucator.elev_scoala);
                            }
                            break;
                        case 3:
                            DateTime d1 = readDate();
                            DateTime d2 = readDate();
                            foreach (var meci in
                                service.meciuri_data(d1, d2))
                            {
                                Console.WriteLine(meci.Echipa1.echipa_nume + " vs " + meci.Echipa2.echipa_nume + " din " + meci.Data);
                            }
                            break;
                        case 4:
                            m = service.findMeci(readId());
                            if (m == null) 
                            {
                                Console.WriteLine("Meciul nu a fost gasit!");
                                break;
                            }
                            Console.WriteLine($"Scorul meciului dintre {m.Echipa1} si {m.Echipa2} din {m.Data:yyyy-MM-dd} este: " +service.scor_meci(m));
                            break;
                        case 5:
                            int cont = 1;
                            foreach(var meci  in service.findAll())
                            {
                                Console.WriteLine(cont.ToString()+". "+ meci);
                                cont++;
                            }
                            break;
                    }
                }
                catch
                {
                    Console.WriteLine("Va rugam sa introduceti o comanda valida!");
                }
            }
        }
    }
}
