using Microsoft.Data.SqlClient;
using System.Data;
using System.Windows.Forms;

namespace Tema_L1
{
    public partial class Form2 : Form
    {
        string id;
        string connectionString = @"Server=ANCA-LAPTOP\SQLEXPRESS;Database=MagazinDeBijuterii;
        Integrated Security=True;TrustServerCertificate=True;";
        DataSet ds;
        SqlDataAdapter adapter;
        Form1 parent;
        public Form2(string id,DataSet ds,SqlDataAdapter adapter,Form1 parent)
        {
            InitializeComponent();
            this.id = id;
            this.ds = ds;
            this.adapter = adapter;
            this.parent = parent;
            this.parent.DataUpdated += OnDataUpdated;
        }
        private void OnDataUpdated()
        {
            LoadData();
        }

        private void Form2_Load(object sender, EventArgs e)
        {
            LoadData();
        }

        private void LoadData()
        {
            try
            {
                using (SqlConnection con = new SqlConnection(connectionString))
                {
                    con.Open();
                    SqlCommand cmd = new SqlCommand("SELECT * FROM Bijuterie WHERE id_borderou = @id", con);
                    cmd.Parameters.AddWithValue("@id", id);

                    adapter.SelectCommand = cmd;
                    if (ds.Tables.Contains("Bijuterie"))
                        ds.Tables["Bijuterie"].Clear();

                    adapter.Fill(ds, "Bijuterie");
                    dataGridView1.DataSource = ds.Tables["Bijuterie"];
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show("Eroare: " + ex.Message);
            }
        }



        private void label3_Click(object sender, EventArgs e)
        {

        }

        private void dataGridView1_CellClick(object sender, DataGridViewCellEventArgs e)
        {
            if (e.RowIndex >= 0)
            {
                string id = dataGridView1.Rows[e.RowIndex].Cells[0].Value.ToString();

            }
        }

        private void button_update_Click(object sender, EventArgs e)
        {
            if (dataGridView1.SelectedRows.Count == 0)
            {
                MessageBox.Show("Selectati un rand pentru actualizare!");
                return;
            }
            DataGridViewRow select = dataGridView1.SelectedRows[0];
            if (string.IsNullOrWhiteSpace(pret_box.Text) || string.IsNullOrWhiteSpace(descriere_box.Text) || string.IsNullOrWhiteSpace(gramaj_box.Text))
            {
                MessageBox.Show("Toate campurile trebuie sa fie completate");
                return;
            }
            string id = select.Cells[0].Value.ToString();
            double pret = double.Parse(pret_box.Text);
            string descriere = descriere_box.Text;
            double gramaj = double.Parse(gramaj_box.Text);

            try
            {
                using (SqlConnection con = new SqlConnection(connectionString))
                {
                    con.Open();
                    SqlCommand cmd = new SqlCommand("UPDATE Bijuterie SET pret_bij = @pret, descriere_bij = @descriere, gramaj_bij = @gramaj WHERE id_bij = @id", con);
                    cmd.Parameters.AddWithValue("@pret", pret);
                    cmd.Parameters.AddWithValue("@descriere", descriere);
                    cmd.Parameters.AddWithValue("@gramaj", gramaj);
                    cmd.Parameters.AddWithValue("@id", id);

                    int rowsAffected = cmd.ExecuteNonQuery();
                    if (rowsAffected > 0)
                    {
                        MessageBox.Show("Actualizare cu succes!");
                        LoadData();
                    }
                    else
                    {
                        MessageBox.Show("Actualizarea a esuat!");
                    }
                }
                LoadData();
            }
            catch (Exception ex)
            {
                MessageBox.Show("Eroare la actualizare: " + ex.Message);
            }

        }

        private void button_delete_Click(object sender, EventArgs e)
        {
            if (dataGridView1.SelectedRows.Count == 0 || dataGridView1.RowCount == 0)
            {
                MessageBox.Show("Selectati un rand pentru actualizare sau introduceti macar o coloana");
                return;
            }
            DataGridViewRow select = dataGridView1.SelectedRows[0];
            string id = select.Cells[0].Value.ToString();
            try
            {
                using (SqlConnection con = new SqlConnection(connectionString))
                {
                    con.Open();
                    SqlCommand cmd = new SqlCommand("Delete Bijuterie WHERE id_bij = @id", con);
                    cmd.Parameters.AddWithValue("@id", id);

                    int rowsAffected = cmd.ExecuteNonQuery();
                    if (rowsAffected > 0)
                    {
                        MessageBox.Show("Stergere cu succes!");
                        LoadData();
                    }
                    else
                    {
                        MessageBox.Show("Stergerea a esuat!");
                    }
                }
                LoadData();
            }
            catch (Exception ex)
            {
                MessageBox.Show("Eroare la stergere: " + ex.Message);
            }
        }

        private void dataGridView1_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {

        }
    }
}
