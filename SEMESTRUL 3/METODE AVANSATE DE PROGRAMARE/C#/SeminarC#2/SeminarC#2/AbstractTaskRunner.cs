using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SeminarC_
{
    public abstract class AbstractTaskRunner : TaskRunner
    {
        protected TaskRunner _taskRunner;

        public AbstractTaskRunner(TaskRunner taskRunner)
        {
            _taskRunner = taskRunner;
        }

        public virtual void addTask(Task t)
        {
            _taskRunner.addTask(t);
        }

        public virtual bool hasTask()
        {
            return _taskRunner.hasTask();
        }

        public virtual void executeAll()
        {
            while (hasTask())
            {
                _taskRunner.executeOneTask();
            }
        }

        public virtual void executeOneTask()
        {
            _taskRunner.executeOneTask();
        }
    }
}
