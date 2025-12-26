using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Laborator13
{
    internal class JucatorActiv:Entity<int>
    {
        private int idJucator;
        private int idMeci;
        private int nrPuncte;
        private string tip;
        public JucatorActiv(int id,int idJucator, int idMeci, int nrPuncte, string tip):base(id)
        {
            this.idJucator = idJucator;
            this.idMeci = idMeci;
            this.nrPuncte = nrPuncte;
            this.tip = tip;
        }
        public int IdJucator
        {
            set { idJucator = value; }
            get { return idJucator; }
        }
        public int IdMeci
        {
            set { nrPuncte = value; }
            get { return idMeci; }
        }
        public int NrPuncte
        {
            set { nrPuncte = value; }
            get { return nrPuncte; }
        }
        public string Tip
        {
            set { tip = value; }
            get { return tip; }
        }
        public override string ToString()
        {
            return $"idJucator: {idJucator} |idMeci: {idMeci} |nrPuncte: {nrPuncte} |tip: {tip} ";
        }

    }
}
