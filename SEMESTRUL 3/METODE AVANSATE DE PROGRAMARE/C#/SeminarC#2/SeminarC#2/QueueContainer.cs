using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SeminarC_
{
        public class QueueContainer : ContainerSuperclass
        {
            public override Task Remove()
            {
                if (IsEmpty()) throw new InvalidOperationException("The queue is empty.");
                Task task = tasks[0];
                tasks.RemoveAt(0);
                return task;
            }
        }


}
