using System;
using System.Threading;

namespace SeminarC_
{
    public class DelayTaskRunner : AbstractTaskRunner
    {
        public DelayTaskRunner(TaskRunner taskRunner) : base(taskRunner) { }

        public override void executeOneTask()
        {
            Console.WriteLine();
            Console.WriteLine("Delaying task execution for 3 seconds...");
            Thread.Sleep(3000); 

            base.executeOneTask(); 
            Console.WriteLine("Executed at: " + DateTime.Now.ToString()); 
        }
    }
}
