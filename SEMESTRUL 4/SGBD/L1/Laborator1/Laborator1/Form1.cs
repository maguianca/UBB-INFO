using Microsoft.Data.SqlClient;
using System.Data;
namespace Laborator1
{
    public partial class Form1 : Form
    {
        string connectionString = @"Server=ANCA-LAPTOP\SQLEXPRESS;Database=Lab1_SGBD;
        Integrated Security = True;TrustServerCertificate=True;";
        DataSet ds = new DataSet();
        SqlDataAdapter adapter = new SqlDataAdapter();

        
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            try
            {
                using(SqlConnection con=new SqlConnection(connectionString))
                {
             
                    con.Open();
                    label2.Text = con.State.ToString();
                    adapter.SelectCommand = new SqlCommand("SELECT * from Motociclete;", con);
                    adapter.Fill(ds, "Motociclete");
                    dataGridView1.DataSource = ds.Tables["Motociclete"];
                }
            }
            catch(Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }
    }
}
