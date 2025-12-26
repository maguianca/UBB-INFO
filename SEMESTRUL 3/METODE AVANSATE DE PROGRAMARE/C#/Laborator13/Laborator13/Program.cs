using Npgsql;
using System;

namespace Laborator13
{
    class Program
    {
        static void Main(string[] args)
        {
            string connectionString= "Host=127.0.0.1;Port=5432;Database=baschet;User Id=postgres;Password=1205;";
            RepoEchipa repoEchipa = new RepoEchipa(connectionString);
            RepoElev repoElev = new RepoElev(connectionString);
            RepoJucator repoJucator=new RepoJucator(connectionString, repoEchipa);
            RepoJucatorActiv repoJucatorActiv = new RepoJucatorActiv(connectionString);
            RepoMeci repoMeci = new RepoMeci(connectionString, repoEchipa);
            Console.WriteLine("M-am conectat");
            Service service=new Service(repoElev,repoEchipa, repoMeci,repoJucator, repoJucatorActiv); 
            UI uI = new UI(service);
            uI.run();
        }
    }
    /*Echipa echipa1 = new Echipa(1, "LA Clippers");
           Echipa echipa2 = new Echipa(1, "Chicago Bulls");
           Echipa echipa3 = new Echipa(1, "Cleveland Cavaliers");
           Echipa echipa4 = new Echipa(1, "Utah Jazz");
           Echipa echipa5 = new Echipa(1, "Brooklyn Nets");
           Echipa echipa6 = new Echipa(1, "New Orleans Pelicans");
           Echipa echipa7 = new Echipa(1, "Indiana Pacers");
           Echipa echipa8 = new Echipa(1, "Toronto Raptors");
           Echipa echipa9 = new Echipa(1, "Charlotte Hornets");
           Echipa echipa10 = new Echipa(1, "Phoenix Suns");
           Echipa echipa11 = new Echipa(1, "Portland TrailBlazers");
           Echipa echipa12 = new Echipa(1, "Golden State Warriors");
           Echipa echipa13 = new Echipa(1, "Washington Wizards");
           Echipa echipa14 = new Echipa(1, "San Antonio Spurs");
           Echipa echipa15 = new Echipa(1, "Orlando Magic");
           Echipa echipa16 = new Echipa(1, "Denver Nuggets");
           Echipa echipa17 = new Echipa(1, "Detroit Pistons");
           Echipa echipa18 = new Echipa(1, "Atlanta Hawks");
           Echipa echipa19 = new Echipa(1, "Dallas Mavericks");
           Echipa echipa20 = new Echipa(1, "Sacramento Kings");
           Echipa echipa21 = new Echipa(1, "Oklahoma City Thunder");
           Echipa echipa22 = new Echipa(1, "Boston Celtics");
           Echipa echipa23 = new Echipa(1, "New York Knicks");
           Echipa echipa24 = new Echipa(1, "Minnesota Timberwolves");
           Echipa echipa25 = new Echipa(1, "Miami Heat");
           Echipa echipa26 = new Echipa(1, "Milwaukee Bucks");
           repoEchipa.Save(echipa1);
           repoEchipa.Save(echipa2);
           repoEchipa.Save(echipa3);
           repoEchipa.Save(echipa4);
           repoEchipa.Save(echipa5);
           repoEchipa.Save(echipa6);
           repoEchipa.Save(echipa7);
           repoEchipa.Save(echipa8);
           repoEchipa.Save(echipa9);
           repoEchipa.Save(echipa10);
           repoEchipa.Save(echipa11);
           repoEchipa.Save(echipa12);
           repoEchipa.Save(echipa13);
           repoEchipa.Save(echipa14);
           repoEchipa.Save(echipa15);
           repoEchipa.Save(echipa16);
           repoEchipa.Save(echipa17);
           repoEchipa.Save(echipa18);
           repoEchipa.Save(echipa19);
           repoEchipa.Save(echipa20);
           repoEchipa.Save(echipa21);
           repoEchipa.Save(echipa22);
           repoEchipa.Save(echipa23);
           repoEchipa.Save(echipa24);
           repoEchipa.Save(echipa25);
           repoEchipa.Save(echipa26);
           Console.ReadLine();
           Jucator elev1 = new Jucator(1, "Tatu", "Scoala Gimnaziala Internationala SPECTRUM",7);
           Jucator elev2 = new Jucator(1, "Iuli", "Scoala Gimnaziala Internationala SPECTRUM",7);
           Jucator elev3 = new Jucator(1, "Petri", "Scoala Gimnaziala Internationala SPECTRUM",7);
           Jucator elev4 = new Jucator(1, "Corni", "Scoala Gimnaziala Internationala SPECTRUM",7);
           Jucator elev5 = new Jucator(1, "Ioni", "Scoala Gimnaziala Internationala SPECTRUM");
           Jucator elev6 = new Jucator(1, "Popi", "Scoala Gimnaziala Internationala SPECTRUM");
           Jucator elev7 = new Jucator(1, "Cristi", "Scoala Gimnaziala Internationala SPECTRUM");
           Jucator elev8 = new Jucator(1, "Andreu", "Scoala Gimnaziala Internationala SPECTRUM");
           Jucator elev9 = new Jucator(1, "Andri", "Scoala Gimnaziala Internationala SPECTRUM");
           Jucator elev10 = new Jucator(1, "Mateiu", "Scoala Gimnaziala Internationala SPECTRUM");
           Jucator elev11 = new Jucator(1, "Mihaiu", "Scoala Gimnaziala Internationala SPECTRUM");
           Jucator elev12 = new Jucator(1, "Iuli", "Scoala Gimnaziala Internationala SPECTRUM");
           Jucator elev13 = new Jucator(1, "Emi ", "Scoala Gimnaziala Internationala SPECTRUM");
           Jucator elev14 = new Jucator(1, "Nati", "Scoala Gimnaziala Internationala SPECTRUM");
           Jucator elev15 = new Jucator(1, "Bine", "Scoala Gimnaziala Internationala SPECTRUM");
           repoElev.Save(elev1);
           repoElev.Save(elev2);
           repoElev.Save(elev3);
           repoElev.Save(elev4);
           repoElev.Save(elev5);
           repoElev.Save(elev6);
           repoElev.Save(elev7);
           repoElev.Save(elev8);
           repoElev.Save(elev9);
           repoElev.Save(elev10);
           repoElev.Save(elev11);
           repoElev.Save(elev12);
           repoElev.Save(elev13);
           repoElev.Save(elev14);
           repoElev.Save(elev15);*/
}
