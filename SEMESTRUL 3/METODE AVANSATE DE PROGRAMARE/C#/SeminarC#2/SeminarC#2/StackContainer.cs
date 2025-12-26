using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SeminarC_
{
    public class StackContainer : ContainerSuperclass
    {
        public override Task Remove()
        {
            if (IsEmpty()) throw new InvalidOperationException("The stack is empty.");
            Task task = tasks[tasks.Count - 1];
            tasks.RemoveAt(tasks.Count - 1);
            return task;
        }
    }


}
