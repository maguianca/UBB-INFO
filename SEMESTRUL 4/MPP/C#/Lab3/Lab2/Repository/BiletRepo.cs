using Lab2.Domain;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab2.Repository
{
    internal interface BiletRepo : IRepository<int, Bilet> {

        IEnumerable<Bilet> FindBySpectacol(Spectacol spectacol);
        //Spectacol FindSpectacolById(int id);
        
        // Spectacol FindSpectacolByParams(Spectacol spectacol);
    }
}
