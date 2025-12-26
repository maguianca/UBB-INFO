using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab2.Domain
{
    internal class Entity<ID>
    {
        private ID id;
        public Entity()
        {

        }
        public Entity(ID id)
        {
            this.id = id;
        }
        public ID Id
        {
            get { return id; }
            set { id = value; }
        }
    }
}
