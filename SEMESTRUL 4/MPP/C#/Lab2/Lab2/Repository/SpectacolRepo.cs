using Lab2.Domain;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab2.Repository
{
    internal interface SpectacolRepo:IRepository<int,Spectacol>
    {
        //Spectacol findByDataandArtist(String data, String artist);
    }
}
