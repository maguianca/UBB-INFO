using Lab2.Domain;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab2.Repository
{
    internal interface AngajatRepo:IRepository<int,Angajat>
    {
        Angajat FindByUsernamePass(string username, string password);
    }
}
