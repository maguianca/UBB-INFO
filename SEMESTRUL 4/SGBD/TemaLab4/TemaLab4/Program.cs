using System;
using System.Threading;
using Microsoft.Data.SqlClient;

namespace TemaLab4
{
    internal class Program
    {
        static int retry_number = 3;
        static string connectionString = @"Server=ANCA-LAPTOP\SQLEXPRESS;Database=JewelryShop;Integrated Security=True;TrustServerCertificate=True;";

        static void Main(string[] args)
        {
            Thread t1 = new Thread(() => ExecuteTransaction("DeadLock1"));
            Thread t2 = new Thread(() => ExecuteTransaction("DeadLock2"));
            t1.Start();
            t2.Start();
            t1.Join();
            t2.Join();

            Console.WriteLine("Executed");
        }

        static void ExecuteTransaction(string procedureName)
        {
            int count = 0;
            bool success = false;

            while (count < retry_number)
            {
                success = RunTransaction(procedureName, count);
                if (success)
                {
                    break;
                }

                count++;
                if (count == retry_number)
                {
                    Console.WriteLine($"{Timestamp()} [{Thread.CurrentThread.ManagedThreadId}] {procedureName} aborted after {retry_number} attempts.");
                    break;
                }

                Thread.Sleep(1000);
            }
        }

        static bool RunTransaction(string procedureName, int attempt)
        {
            Console.WriteLine($"{Timestamp()} [{Thread.CurrentThread.ManagedThreadId}] Attempt {attempt + 1}: Starting {procedureName}...");

            try
            {
                using (SqlConnection con = new SqlConnection(connectionString))
                {
                    con.Open();
                    using (SqlCommand cmd = new SqlCommand($"EXEC {procedureName}", con))
                    {
                        cmd.ExecuteNonQuery();
                        Console.WriteLine($"{Timestamp()} [{Thread.CurrentThread.ManagedThreadId}] {procedureName} completed successfully.");
                        return true;
                    }
                }
            }
            catch (SqlException ex)
            {
                if (ex.Number == 1205)
                {
                    Console.WriteLine($"{Timestamp()} [{Thread.CurrentThread.ManagedThreadId}] Deadlock detected in {procedureName}. Retrying...");
                    return false;
                }
                else
                {
                    Console.WriteLine($"{Timestamp()} [{Thread.CurrentThread.ManagedThreadId}] SQL Error in {procedureName}: {ex.Message}");
                    return false;
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine($"{Timestamp()} [{Thread.CurrentThread.ManagedThreadId}] General error in {procedureName}: {ex.Message}");
                return false;
            }
        }

        static string Timestamp()
        {
            return DateTime.Now.ToString("HH:mm:ss.fff");
        }
    }
}
