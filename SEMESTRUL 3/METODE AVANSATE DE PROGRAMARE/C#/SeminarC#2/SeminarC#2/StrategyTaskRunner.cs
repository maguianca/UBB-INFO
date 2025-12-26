using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SeminarC_
{
    public class StrategyTaskRunner : TaskRunner
    {
        private Container _container;
        public StrategyTaskRunner(Strategy strategy)
        {
            _container = TaskContainerFactory.Instance.CreateContainer(strategy);
        }
        public void addTask(Task t)
        {
            _container.Add(t);
        }
        public bool hasTask()
        {
            return !_container.IsEmpty();
        }
        public void executeOneTask()
        {
            if (hasTask())
            {
                Task task = _container.Remove();
                task.Execute();
            }
            else
            {
                Console.WriteLine("No tasks to execute.");
            }
        }

        public void executeAll()
        {
            while (hasTask())
            {
                executeOneTask();
            }
        }
    }

}
