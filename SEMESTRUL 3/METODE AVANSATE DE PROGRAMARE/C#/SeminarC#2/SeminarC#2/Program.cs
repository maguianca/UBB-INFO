using System;
using System.Collections.Generic;
using System.Globalization;
using System.Threading.Tasks;

namespace SeminarC_
{
    class Program
    {
        public static void test()
        {
            Console.WriteLine("***********TEST*********");
            Console.WriteLine("\n\nSTACK/QUEUE");
            MessageTask[] tasks = new MessageTask[5];
            tasks[0] = new MessageTask("1", "Feedback lab1", "Ai obtinut 9.60", "Gigi", "Ana", new DateTime(2018, 9, 27, 9, 29, 0));
            tasks[1] = new MessageTask("2", "Notificare", "Deadline-ul este maine", "Coordonator", "Student", new DateTime(2023, 12, 7, 10, 30, 0));
            tasks[2] = new MessageTask("3", "Rezultat examen", "Ai promovat examenul cu 8.50", "Profesor", "Alex", new DateTime(2023, 12, 1, 14, 15, 0));
            tasks[3] = new MessageTask("4", "Amintire proiect", "Prezentarea este programata pentru luni", "Manager", "Echipa", new DateTime(2023, 11, 30, 9, 0, 0));
            tasks[4] = new MessageTask("5", "Mesaj de sarbatori", "Sarbatori fericite tuturor!", "HR", "Angajati", new DateTime(2023, 12, 24, 12, 0, 0));
            // Testare StackContainer (LIFO)
            Container stack = new StackContainer();
            foreach (var task in tasks)
            {
                stack.Add(task);
            }

            Console.WriteLine("StackContainer:");
            while (!stack.IsEmpty())
            {
                Console.WriteLine(stack.Remove());
            }

            // Testare QueueContainer (FIFO)
            Container queue = new QueueContainer();
            foreach (var task in tasks)
            {
                queue.Add(task);
            }

            Console.WriteLine("\nQueueContainer:");
            while (!queue.IsEmpty())
            {
                Console.WriteLine(queue.Remove());
            }
            Console.WriteLine("*********Sfarsit TEST*************");

        }
        static void Main(string[] args)
        {
            int[] numbers = { 121, 23, 4, 2, 1, 56, 77, 89, 2 };
            SortingStrategy sorting_strategy=SortingStrategy.QUICK;
            SortingTask stask=new SortingTask("1","Task",numbers,sorting_strategy);
            stask.Execute();
            MessageTask[] tasks = new MessageTask[5];
            tasks[0] = new MessageTask("1", "Feedback lab1", "Ai obtinut 9.60", "Gigi", "Ana", new DateTime(2018, 9, 27, 9, 29, 0));
            tasks[1] = new MessageTask("2", "Notificare", "Deadline-ul este maine", "Coordonator", "Student", new DateTime(2023, 12, 7, 10, 30, 0));
            tasks[2] = new MessageTask("3", "Rezultat examen", "Ai promovat examenul cu 8.50", "Profesor", "Alex", new DateTime(2023, 12, 1, 14, 15, 0));
            tasks[3] = new MessageTask("4", "Amintire proiect", "Prezentarea este programata pentru luni", "Manager", "Echipa", new DateTime(2023, 11, 30, 9, 0, 0));
            tasks[4] = new MessageTask("5", "Mesaj de sarbatori", "Sarbatori fericite tuturor!", "HR", "Angajati", new DateTime(2023, 12, 24, 12, 0, 0));
            foreach (var task in tasks)
            {
                Console.WriteLine(task);
            }
            if (args.Length != 1)
            {
                Console.WriteLine("Please specify the strategy: 'LIFO' or 'FIFO'.");
                return;
            }
            Strategy strategy;
            if (args[0].ToUpper() == "LIFO")
            {
                strategy = Strategy.LIFO;
            }
            else if (args[0].ToUpper() == "FIFO")
            {
                strategy = Strategy.FIFO;
            }
            else
            {
                Console.WriteLine("Invalid strategy. Please use 'LIFO' or 'FIFO'.");
                return;
            }
            StrategyTaskRunner taskRunner = new StrategyTaskRunner(strategy);
            foreach (var task in tasks)
            {
                taskRunner.addTask(task);
            }
            Console.WriteLine($"\nExecuting tasks with strategy: {strategy}");
            taskRunner.executeAll();
            Console.WriteLine("LIFO/FIFO");
            StrategyTaskRunner runner = new StrategyTaskRunner(strategy);
            DelayTaskRunner printDelay = new DelayTaskRunner(runner);
            PrinterTaskRunner printPrinter = new PrinterTaskRunner(printDelay);
            foreach (var t in tasks)
            {
                printPrinter.addTask(t);
            }
            printPrinter.executeAll();

        }
    }
}
