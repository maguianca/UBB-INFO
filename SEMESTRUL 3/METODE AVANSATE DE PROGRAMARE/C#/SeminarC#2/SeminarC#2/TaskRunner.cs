using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SeminarC_
{
    public interface TaskRunner
    {
        void executeOneTask(); 
        void executeAll();
        void addTask(Task t); 
        bool hasTask();
    }

}
