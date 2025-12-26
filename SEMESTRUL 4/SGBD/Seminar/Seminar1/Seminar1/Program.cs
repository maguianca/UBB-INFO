using Microsoft.Data.SqlClient;

namespace Seminar1
{
    internal class Program
    {
        static void Main(string[] args)
        {
            Console.BackgroundColor = ConsoleColor.Magenta;
            Console.Clear();
            Console.ForegroundColor = ConsoleColor.Yellow;
            Console.WriteLine("Hello world of ADO.NET");
            try
            {
                string connectionString = "@Server=ANCA-LAPTOP\\SQLEXPRESS;Database=SEMINAR1;Integrated Security=True;TrustServerCertificate=True";
                using(SqlConnection con=new SqlConnection(connectionString))
                {
                    Console.WriteLine("Stare conexiune{0}",con.State);
                    con.Open();
                    Console.WriteLine("Stare conexiune{0}", con.State);
                    SqlCommand insertCommand=new SqlCommand("Insert into Produse(nume,pret,producator)VALUES (@nume1,@pret1,@prod1),(@nume2,@pret2,@prod2);",con);
                    insertCommand.Parameters.AddWithValue("@nume1", "Laptop");
                    insertCommand.Parameters.AddWithValue("@pret1", 5990);
                    insertCommand.Parameters.AddWithValue("@prod1", "Asus");
                    insertCommand.Parameters.AddWithValue("@nume1", "AirFryer");
                    insertCommand.Parameters.AddWithValue("@pret1", 400);
                    insertCommand.Parameters.AddWithValue("@prod1", "Xiaomi");
                    int insertRowCount=insertCommand.ExecuteNonQuery();
                }
            }
            catch(Exception ex)
            {
                Console.ForegroundColor = ConsoleColor.White;
                Console.WriteLine("Mesaj exceptie {0}",ex.Message);
            }
        }
    }
}
