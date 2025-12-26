using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Data.SqlClient;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Biscuiti
{
    public partial class Form1 : Form
    {
        DataSet ds = new DataSet();
        SqlDataAdapter adapter;
        string connectionString = @"Server=ANCA-LAPTOP\SQLEXPRESS;Database=Practic_Biscuiti;
        Integrated Security=True;TrustServerCertificate=True;";
        private int selectedCofetarieId = -1;

        public Form1()
        {
            InitializeComponent();
            dataGridView1.CellClick += dataGridView1_CellClick;
            adapter = new SqlDataAdapter();
            LoadData();
        }
        private void LoadData()
        {
            try
            {
                using (SqlConnection con = new SqlConnection(connectionString))
                {
                    con.Open();
                    adapter.SelectCommand = new SqlCommand("SELECT * FROM Producatori", con);
                    if (ds.Tables.Contains("Producatori"))
                        ds.Tables["Producatori"].Clear();
                    adapter.Fill(ds, "Producatori");
                    dataGridView1.DataSource = ds.Tables["Producatori"];
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show("Eroare: " + ex.Message);
            }
        }
        private void LoadData2()
        {
            using (SqlConnection con = new SqlConnection(connectionString))
            {
                con.Open();
                SqlCommand cmd = new SqlCommand("SELECT * FROM Biscuiti WHERE cod_p= @id", con);
                cmd.Parameters.AddWithValue("@id", selectedCofetarieId);

                adapter.SelectCommand = cmd;
                if (ds.Tables.Contains("Biscuiti"))
                    ds.Tables["Biscuiti"].Clear();

                adapter.Fill(ds, "Biscuiti");
                dataGridView2.DataSource = ds.Tables["Biscuiti"];
            }
        }
        private void Form1_Load(object sender, EventArgs e)
        {
            LoadData();

        }
        private void dataGridView1_CellClick(object sender, DataGridViewCellEventArgs e)
        {
            if (e.RowIndex >= 0)
            {
                selectedCofetarieId = int.Parse(dataGridView1.Rows[e.RowIndex].Cells[0].Value.ToString());
                using (SqlConnection con = new SqlConnection(connectionString))
                {
                    con.Open();
                    SqlCommand cmd = new SqlCommand("SELECT * FROM Biscuiti WHERE cod_p = @id", con);
                    cmd.Parameters.AddWithValue("@id", selectedCofetarieId);

                    adapter.SelectCommand = cmd;
                    if (ds.Tables.Contains("Biscuiti"))
                        ds.Tables["Biscuiti"].Clear();

                    adapter.Fill(ds, "Biscuiti");
                    dataGridView2.DataSource = ds.Tables["Biscuiti"];
                }

            }
        }

        private void update_Click(object sender, EventArgs e)
        {
            if (dataGridView2.SelectedRows.Count == 0)
            {
                MessageBox.Show("Selectati un rand pentru actualizare!");
                return;
            }
            DataGridViewRow select = dataGridView2.SelectedRows[0];
            if (string.IsNullOrWhiteSpace(text_pret.Text) || string.IsNullOrWhiteSpace(text_calorii.Text) || string.IsNullOrWhiteSpace(text_nume.Text))
            {
                MessageBox.Show("Toate campurile trebuie sa fie completate");
                return;
            }
            int id = int.Parse(select.Cells[0].Value.ToString());
            double pret = double.Parse(text_pret.Text);
            string calorii = text_calorii.Text;
            string nume = text_nume.Text;

            try
            {
                using (SqlConnection con = new SqlConnection(connectionString))
                {
                    con.Open();
                    SqlCommand cmd = new SqlCommand("UPDATE Biscuiti SET nume_b=@nume, pret = @pret, nr_calorii= @calorii WHERE cod_b = @cod_b", con);
                    cmd.Parameters.AddWithValue("@nume", nume);
                    cmd.Parameters.AddWithValue("@pret", pret);
                    cmd.Parameters.AddWithValue("@calorii", calorii);
                    cmd.Parameters.AddWithValue("@cod_b", id);

                    int rowsAffected = cmd.ExecuteNonQuery();
                    if (rowsAffected > 0)
                    {
                        MessageBox.Show("Actualizare cu succes!");
                        LoadData2();
                        text_pret.Clear();
                        text_calorii.Clear();
                        text_nume.Clear();
                    }
                    else
                    {
                        MessageBox.Show("Actualizarea a esuat!");
                    }
                }
                LoadData2();
            }
            catch (Exception ex)
            {
                MessageBox.Show("Eroare la actualizare: " + ex.Message);
            }

        }

        private void add_Click(object sender, EventArgs e)
        {
            if (dataGridView1.SelectedRows.Count == 0 || dataGridView1.RowCount == 0)
            {
                MessageBox.Show("Selectati un rand pentru adaugare sau introduceti macar un rand");
                return;
            }
            DataGridViewRow select = dataGridView1.SelectedRows[0];
            int cod_prod = int.Parse(select.Cells[0].Value.ToString());
            if (string.IsNullOrWhiteSpace(text_pret.Text))
            {
                MessageBox.Show("Toate campurile trebuie sa fie completate");
                return;
            }
            if (string.IsNullOrWhiteSpace(text_pret.Text) || string.IsNullOrWhiteSpace(text_calorii.Text) || string.IsNullOrWhiteSpace(text_nume.Text))
            {
                MessageBox.Show("Toate campurile trebuie sa fie completate");
                return;
            }
            double pret = double.Parse(text_pret.Text);
            string calorii = text_calorii.Text;
            string nume = text_nume.Text;
            try
            {
                using (SqlConnection con = new SqlConnection(connectionString))
                {
                    con.Open();
                    SqlCommand cmd = new SqlCommand("Insert into Biscuiti(nume_B,pret,nr_calorii,cod_p) values(@nume,@pret,@calorii,@id)", con);
                    cmd.Parameters.AddWithValue("@nume", nume);
                    cmd.Parameters.AddWithValue("@pret", pret);
                    cmd.Parameters.AddWithValue("@calorii", calorii);
                    cmd.Parameters.AddWithValue("@id", cod_prod);

                    int rowsAffected = cmd.ExecuteNonQuery();
                    if (rowsAffected > 0)
                    {
                        MessageBox.Show("Adaugare cu succes!");
                        LoadData2();
                        text_pret.Clear();
                        text_calorii.Clear();
                        text_nume.Clear();
                    }
                    else
                    {
                        MessageBox.Show("Adaugarea a esuat!");
                    }
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show("Eroare la adaugare: " + ex.Message);
            }
        }

        private void delete_Click(object sender, EventArgs e)
        {

            if (dataGridView2.SelectedRows.Count == 0 || dataGridView2.RowCount == 0)
            {
                MessageBox.Show("Selectati un rand pentru actualizare sau introduceti macar o coloana");
                return;
            }
            DataGridViewRow select = dataGridView2.SelectedRows[0];
            string id = select.Cells[0].Value.ToString();
            try
            {
                using (SqlConnection con = new SqlConnection(connectionString))
                {
                    con.Open();
                    SqlCommand cmd = new SqlCommand("Delete Biscuiti WHERE cod_b = @id", con);
                    cmd.Parameters.AddWithValue("@id", id);

                    int rowsAffected = cmd.ExecuteNonQuery();
                    if (rowsAffected > 0)
                    {
                        MessageBox.Show("Stergere cu succes!");
                        LoadData2();
                    }
                    else
                    {
                        MessageBox.Show("Stergerea a esuat!");
                    }
                }
                LoadData2();
            }
            catch (Exception ex)
            {
                MessageBox.Show("Eroare la stergere: " + ex.Message);
            }
        }
    }
}
