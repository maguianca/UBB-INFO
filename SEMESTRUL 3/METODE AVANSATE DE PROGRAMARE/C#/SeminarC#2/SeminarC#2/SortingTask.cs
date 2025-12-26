using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SeminarC_
{
    public class SortingTask : Task
    {
        private int[] numbers;
        private AbstractSorter sorter;

        public SortingTask(string taskID, string descriere, int[] numbers, SortingStrategy sorter)
            : base(taskID, descriere)
        {
            this.numbers = numbers;
            if (sorter == SortingStrategy.QUICK)
            {
                this.sorter = new QuickSorter();
            }
            else if (sorter == SortingStrategy.BUBBLE)
            {
                this.sorter = new BubbleSorter();
            }
        }

        public override void Execute()
        {
            Console.WriteLine("Vector înainte de sortare: " + string.Join(", ", numbers));
            sorter.Sort(numbers);
            Console.WriteLine("Vector după sortare: " + string.Join(", ", numbers));
        }
    }

}
