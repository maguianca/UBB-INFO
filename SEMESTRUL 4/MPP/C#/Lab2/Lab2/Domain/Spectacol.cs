using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab2.Domain
{
    internal class Spectacol:Entity<int>
    {
        private DateTime data;
        private string locatie;
        private string artist;
        private int nrLocuriDisponibile;
        private int nrLocuriOcupate;

        public Spectacol(DateTime data, string locatie, string artist, int nrLocuriDisponibile, int nrLocuriOcupate)
        {
            this.data = data;
            this.locatie = locatie;
            this.artist = artist;
            this.nrLocuriDisponibile = nrLocuriDisponibile;
            this.nrLocuriOcupate = nrLocuriOcupate;
        }
        public String Artist
        {
            get { return this.artist; }
            set { this.artist = value; }
        }
        public DateTime Data
        {
            get { return this.data; }
            set { this.data = value; }
        }
        public int NrLocuriDisponibile
        {
            get { return this.nrLocuriDisponibile; }
            set { this.nrLocuriDisponibile = value; }
        }
        public int NrLocuriOcupate
        {
            get { return this.nrLocuriOcupate; }
            set { this.nrLocuriOcupate = value; }
        }
        public string Locatie
        {
            get { return this.locatie; }
            set { this.locatie = value; }
        }

        public override string ToString()
        {
            return $"Spectacol: {this.artist} - {this.locatie} | Data: {this.data.ToString("yyyy-MM-dd HH:mm:ss")} | Locuri Disponibile: {this.nrLocuriDisponibile} | Locuri Ocupate: {this.nrLocuriOcupate}";
        }
    }
}
