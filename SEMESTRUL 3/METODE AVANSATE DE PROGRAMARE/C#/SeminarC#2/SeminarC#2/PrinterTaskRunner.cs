using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SeminarC_
{
    public class PrinterTaskRunner : AbstractTaskRunner
    {
        public PrinterTaskRunner(TaskRunner taskRunner) : base(taskRunner) { }
        public override void executeOneTask()
        {
            base.executeOneTask();
            Console.WriteLine($"Executing task at {DateTime.Now}");
        }

    }
}
