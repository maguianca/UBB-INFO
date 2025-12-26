using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SeminarC_
{
    public interface Container
    {
        Task Remove();
        void Add(Task task);
        int Size();
        bool IsEmpty();
    }

}
