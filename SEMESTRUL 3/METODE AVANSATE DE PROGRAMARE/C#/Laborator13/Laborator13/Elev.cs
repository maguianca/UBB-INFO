using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Laborator13
{
    internal class Elev: Entity<int>
    {
        private string nume;
        private string scoala;

        public Elev(int id,string nume, string scoala):base(id)
        {
            this.nume = nume;
            this.scoala = scoala;
        }

        public string elev_nume
        {
            get { return nume; }
            set { nume = value; }
        }
        public string elev_scoala
        {
            get { return scoala; }
            set { scoala = value; }
        }
        public override string ToString()
        {
            return $"id: {Id} |nume: {nume} |scoala: {scoala} ";
        }


    }
}
