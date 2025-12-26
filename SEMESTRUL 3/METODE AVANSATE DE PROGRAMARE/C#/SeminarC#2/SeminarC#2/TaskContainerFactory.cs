using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SeminarC_
{

    public class TaskContainerFactory : Factory
    {
            private static TaskContainerFactory _instance;
            private TaskContainerFactory() { }
            public static TaskContainerFactory Instance
            {
                get
                {
                    if (_instance == null)
                    {
                        _instance = new TaskContainerFactory();
                    }
                    return _instance;
                }
            }
            public Container CreateContainer(Strategy strategy)
            {
                switch (strategy)
                {
                    case Strategy.LIFO:
                        return new StackContainer(); 
                    case Strategy.FIFO:
                        return new QueueContainer(); 
                    default:
                        throw new ArgumentException("Invalid strategy");
                }
            }
    }
    
}
