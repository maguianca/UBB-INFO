using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Laborator13
{
    internal class Service
    {
        private IRepository<int, Echipa> RepoEchipa;
        private IRepository<int, Elev> RepoElev;
        private IRepository<int, Meci> RepoMeci;
        private IRepository<int, Jucator> RepoJucator;
        private IRepository<int, JucatorActiv> RepoJucatorActiv;
        public Service(IRepository<int,Elev>repoElev,IRepository<int, Echipa> repoEchipa, IRepository<int, Meci> repoMeci, IRepository<int, Jucator> repoJucator, IRepository<int, JucatorActiv> jucatorActiv)
        {
            RepoEchipa = repoEchipa;
            RepoElev = repoElev;
            RepoMeci = repoMeci;
            RepoJucator = repoJucator;
            RepoJucatorActiv = jucatorActiv;
        }
        public IEnumerable<Jucator>jucatorii_echipei(Echipa echipa)
        {
            return RepoJucator.FindAll().Where(j =>
            {
                Jucator jucator = (Jucator)j;
                return j.echipa.Equals(echipa);
            });
        }
        public IEnumerable<Jucator>jucatori_activi_meci(Echipa echipa, Meci meci)
        {
                return
                    from jucatorActiv in RepoJucatorActiv.FindAll()
                    join jucator in RepoJucator.FindAll()
                    on jucatorActiv.IdJucator equals jucator.Id
                    where jucatorActiv.IdMeci == meci.Id
                          && jucator.echipa.Id == echipa.Id
                    select jucator;

        }
        public IEnumerable<Meci> meciuri_data(DateTime beginingDate, DateTime endingDate)
        {
            return
                from meci in RepoMeci.FindAll()
                where meci.Data >= beginingDate && meci.Data <= endingDate
                select meci;
        }

        public string scor_meci(Meci meci)
        {
            int scorEchipa1 = 0;
            try
            {
                scorEchipa1 =
                (from jucatorActiv in RepoJucatorActiv.FindAll()
                 join jucator in RepoJucator.FindAll()
                 on jucatorActiv.IdJucator equals jucator.Id
                 join echipa in RepoEchipa.FindAll()
                 on jucator.echipa.Id equals echipa.Id
                 where jucatorActiv.IdMeci == meci.Id
                        && meci.Echipa1.Id == echipa.Id
                 select jucatorActiv.NrPuncte).Sum();
            }
            catch { }

            int scorEchipa2 = 0;
            try
            {
                scorEchipa2 =
                (from jucatorActiv in RepoJucatorActiv.FindAll()
                 join jucator in RepoJucator.FindAll()
                 on jucatorActiv.IdJucator equals jucator.Id
                 join echipa in RepoEchipa.FindAll()
                 on jucator.echipa.Id equals echipa.Id
                 where jucatorActiv.IdMeci == meci.Id
                        && meci.Echipa2.Id == echipa.Id
                 select jucatorActiv.NrPuncte).Sum();
            }
            catch { }

            return scorEchipa1.ToString() + " - " + scorEchipa2.ToString();
        }


        public Echipa findEchipa(int id)
        {
            return RepoEchipa.FindOne(id);
        }

        public Meci findMeci(int id)
        {
            return RepoMeci.FindOne(id);
        }
        public IEnumerable<Meci> findAll()
        {
            return RepoMeci.FindAll();
        }
    }
}
