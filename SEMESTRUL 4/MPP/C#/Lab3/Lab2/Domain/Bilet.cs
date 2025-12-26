using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab2.Domain
{
    internal class Bilet:Entity<int>
    {
        private int nrLocuri;
        private Spectacol spectacol;
        private string numeClient;

        public Bilet(int nrLocuri, Spectacol spectacol, string numeClient)
        {
            this.nrLocuri = nrLocuri;
            this.spectacol = spectacol;
            this.numeClient = numeClient;
        }

        public string NumeClient
        {
            get { return numeClient; }  
            set { numeClient = value; }     
        }

        public int NrLocuri
        {
            get { return nrLocuri; }
            set { nrLocuri = value; }
        }
        public Spectacol Spectacol
        {
            get { return spectacol; }
            set { spectacol = value; }
        }

        public override string ToString()
        {
            return $"Bilet: {this.numeClient} | Locuri: {this.nrLocuri} | Spectacol: {this.spectacol.Artist} la {this.spectacol.Locatie} pe {this.spectacol.Data.ToString("yyyy-MM-dd HH:mm:ss")}";
        }


    }
}
