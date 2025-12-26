using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Laborator13
{
    internal class Echipa: Entity<int>
    {
        private string nume;
        public Echipa(int id,string nume): base(id)
        {
            this.nume = nume;
        }
        public string echipa_nume
        {
            get { return nume; }
            set { nume = value; }
        }
        public override string ToString()
        {
            return $"id: {Id} |nume: {nume} ";        
        }
        public override bool Equals(object obj)
        {
            if (obj == null || GetType() != obj.GetType())
                return false;

            Echipa other = (Echipa)obj;
            return nume.Equals(other.echipa_nume);
        }
        public override int GetHashCode()
        {
            return nume.GetHashCode();
        }


    }
}
