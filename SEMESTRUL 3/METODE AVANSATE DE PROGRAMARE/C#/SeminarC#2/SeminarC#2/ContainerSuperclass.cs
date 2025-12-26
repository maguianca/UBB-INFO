using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SeminarC_
{
        public abstract class ContainerSuperclass : Container
        {
            protected readonly List<Task> tasks = new List<Task>();

            public abstract Task Remove();

            public void Add(Task task)
            {
                tasks.Add(task);
            }

            public int Size()
            {
                return tasks.Count;
            }

            public bool IsEmpty()
            {
                return tasks.Count == 0;
            }
        }

}
