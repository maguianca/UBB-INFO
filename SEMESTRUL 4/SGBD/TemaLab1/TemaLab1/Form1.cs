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

namespace TemaLab1
{
    public partial class Form1 : Form
    {
        DataSet ds = new DataSet();
        SqlDataAdapter adapter;
        string connectionString = @"Server=ANCA-LAPTOP\SQLEXPRESS;Database=JewelryShop;
        Integrated Security=True;TrustServerCertificate=True;";
        private int selectedId = -1;

        public Form1()
        {
            InitializeComponent();
            dataGridView1.CellClick += dataGridView1_CellClick;
            adapter = new SqlDataAdapter();
        }
        private void LoadData()
        {
            try
            {
                using (SqlConnection con = new SqlConnection(connectionString))
                {
                    con.Open();
                    adapter.SelectCommand = new SqlCommand("SELECT * FROM Borderou", con);
                    if (ds.Tables.Contains("Borderou"))
                        ds.Tables["Borderou"].Clear();
                    adapter.Fill(ds, "Borderou");
                    dataGridView1.DataSource = ds.Tables["Borderou"];
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
                SqlCommand cmd = new SqlCommand("SELECT * FROM Bijuterie WHERE id_borderou = @id", con);
                cmd.Parameters.AddWithValue("@id", selectedId);

                adapter.SelectCommand = cmd;
                if (ds.Tables.Contains("Bijuterie"))
                    ds.Tables["Bijuterie"].Clear();

                adapter.Fill(ds, "Bijuterie");
                dataGridView2.DataSource = ds.Tables["Bijuterie"];
            }
        }
        private void dataGridView1_CellClick(object sender, DataGridViewCellEventArgs e)
        {
            if (e.RowIndex >= 0)
            {
                selectedId = int.Parse(dataGridView1.Rows[e.RowIndex].Cells[0].Value.ToString());
                using (SqlConnection con = new SqlConnection(connectionString))
                {
                    con.Open();
                    SqlCommand cmd = new SqlCommand("SELECT * FROM Bijuterie WHERE id_borderou= @id", con);
                    cmd.Parameters.AddWithValue("@id", selectedId);

                    adapter.SelectCommand = cmd;
                    if (ds.Tables.Contains("Bijuterie"))
                        ds.Tables["Bijuterie"].Clear();

                    adapter.Fill(ds, "Bijuterie");
                    dataGridView2.DataSource = ds.Tables["Bijuterie"];
                }

            }
        }
        private void Form1_Load(object sender, EventArgs e)
        {
            LoadData();
        }

        private void add_Click(object sender, EventArgs e)
        {
            if (dataGridView1.SelectedRows.Count == 0 || dataGridView1.RowCount == 0)
            {
                MessageBox.Show("Selectati un rand pentru adaugare sau introduceti macar un rand");
                return;
            }
            DataGridViewRow select = dataGridView1.SelectedRows[0];
            int cod = int.Parse(select.Cells[0].Value.ToString());
            if (string.IsNullOrWhiteSpace(text_pret.Text))
            {
                MessageBox.Show("Toate campurile trebuie sa fie completate");
                return;
            }
            if (string.IsNullOrWhiteSpace(text_pret.Text) || string.IsNullOrWhiteSpace(text_descriere.Text) || string.IsNullOrWhiteSpace(text_gramaj.Text))
            {
                MessageBox.Show("Toate campurile trebuie sa fie completate");
                return;
            }
            int id; double pret; string descriere; double gramaj;
            try
            {
                id = int.Parse(select.Cells[0].Value.ToString());
                pret = double.Parse(text_pret.Text);
                descriere = text_descriere.Text;
                gramaj = double.Parse(text_gramaj.Text);
                if (pret <= 0 || gramaj <= 0) { MessageBox.Show("Gramajul si pretul trb sa fie mai mari decat 0"); return; }
            }
            catch
            {
                MessageBox.Show("Toate campurile trebuie sa fie completate corect");
                return;
            }
            try
            {
                using (SqlConnection con = new SqlConnection(connectionString))
                {
                    con.Open();
                    SqlCommand cmd = new SqlCommand("Insert into Bijuterie(pret_bij,descriere_bij,gramaj_bij,id_borderou) values(@pret,@descriere,@gramaj,@cod)", con);
                    cmd.Parameters.AddWithValue("@gramaj", gramaj);
                    cmd.Parameters.AddWithValue("@pret", pret);
                    cmd.Parameters.AddWithValue("@descriere", descriere);
                    cmd.Parameters.AddWithValue("@cod", cod);

                    int rowsAffected = cmd.ExecuteNonQuery();
                    if (rowsAffected > 0)
                    {
                        MessageBox.Show("Adaugare cu succes!");
                        LoadData2();
                        text_pret.Clear();
                        text_descriere.Clear();
                        text_gramaj.Clear();
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
                    SqlCommand cmd = new SqlCommand("Delete Bijuterie WHERE id_bij = @id", con);
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

        private void update_Click(object sender, EventArgs e)
        {
            if (dataGridView2.SelectedRows.Count == 0)
            {
                MessageBox.Show("Selectati un rand pentru actualizare!");
                return;
            }
            DataGridViewRow select = dataGridView2.SelectedRows[0];
            if (string.IsNullOrWhiteSpace(text_pret.Text) || string.IsNullOrWhiteSpace(text_descriere.Text) || string.IsNullOrWhiteSpace(text_gramaj.Text))
            {
                MessageBox.Show("Toate campurile trebuie sa fie completate");
                return;
            }
            int id;double pret;string descriere;double gramaj;
            try
            {
                id = int.Parse(select.Cells[0].Value.ToString());
                pret = double.Parse(text_pret.Text);
                descriere = text_descriere.Text;
                gramaj = double.Parse(text_gramaj.Text);
                if (pret <= 0 || gramaj <= 0) { MessageBox.Show("Gramajul si pretul trb sa fie mai mari decat 0"); return; }
            }
            catch
            {
                MessageBox.Show("Toate campurile trebuie sa fie completate corect");
                return;
            }

            try
            {
                using (SqlConnection con = new SqlConnection(connectionString))
                {
                    con.Open();
                    SqlCommand cmd = new SqlCommand("UPDATE Bijuterie SET gramaj_bij=@nume, pret_bij = @pret, descriere_bij= @descriere WHERE id_bij = @cod", con);
                    cmd.Parameters.AddWithValue("@nume", gramaj);
                    cmd.Parameters.AddWithValue("@pret", pret);
                    cmd.Parameters.AddWithValue("@descriere", descriere);
                    cmd.Parameters.AddWithValue("@cod", id);

                    int rowsAffected = cmd.ExecuteNonQuery();
                    if (rowsAffected > 0)
                    {
                        MessageBox.Show("Actualizare cu succes!");
                        LoadData2();
                        text_pret.Clear();
                        text_descriere.Clear();
                        text_gramaj.Clear();
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
    }
}
