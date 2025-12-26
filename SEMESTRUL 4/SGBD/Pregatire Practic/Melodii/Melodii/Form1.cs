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

namespace Melodii
{
    public partial class Form1 : Form
    {
        DataSet ds = new DataSet();
        SqlDataAdapter adapter;
        string connectionString = @"Server=ANCA-LAPTOP\SQLEXPRESS;Database=Practic_Melodii;
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
                    adapter.SelectCommand = new SqlCommand("SELECT * FROM Artisti", con);
                    if (ds.Tables.Contains("Artisti"))
                        ds.Tables["Artisti"].Clear();
                    adapter.Fill(ds, "Artisti");
                    dataGridView1.DataSource = ds.Tables["Artisti"];
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
                SqlCommand cmd = new SqlCommand("SELECT * FROM Melodii WHERE cod_artist = @id", con);
                cmd.Parameters.AddWithValue("@id", selectedId);

                adapter.SelectCommand = cmd;
                if (ds.Tables.Contains("Melodii"))
                    ds.Tables["Melodii"].Clear();

                adapter.Fill(ds, "Melodii");
                dataGridView2.DataSource = ds.Tables["Melodii"];
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
                    SqlCommand cmd = new SqlCommand("SELECT * FROM Melodii WHERE cod_artist = @id", con);
                    cmd.Parameters.AddWithValue("@id", selectedId);

                    adapter.SelectCommand = cmd;
                    if (ds.Tables.Contains("Melodii"))
                        ds.Tables["Melodii"].Clear();

                    adapter.Fill(ds, "Melodii");
                    dataGridView2.DataSource = ds.Tables["Melodii"];
                }

            }
        }


        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void Form1_Load(object sender, EventArgs e)
        {
            LoadData();

        }


    

        private void update_Click_1(object sender, EventArgs e)
        {
            if (dataGridView2.SelectedRows.Count == 0)
            {
                MessageBox.Show("Selectati un rand pentru actualizare!");
                return;
            }
            DataGridViewRow select = dataGridView2.SelectedRows[0];
            if (string.IsNullOrWhiteSpace(text_titlu.Text) || string.IsNullOrWhiteSpace(text_an.Text) || string.IsNullOrWhiteSpace(text_durata.Text))
            {
                MessageBox.Show("Toate campurile trebuie sa fie completate");
                return;
            }
            int id = int.Parse(select.Cells[0].Value.ToString());
            string titlu = text_titlu.Text;
            int an = int.Parse(text_an.Text);
            int durata = int.Parse(text_durata.Text);
            try
            {
                using (SqlConnection con = new SqlConnection(connectionString))
                {
                    con.Open();
                    SqlCommand cmd = new SqlCommand("UPDATE Melodii SET titlu=@titlu, an_lansare = @an, durata= @durata WHERE cod_melodie = @id", con);
                    cmd.Parameters.AddWithValue("@titlu", titlu);
                    cmd.Parameters.AddWithValue("@an", an);
                    cmd.Parameters.AddWithValue("@durata", durata);
                    cmd.Parameters.AddWithValue("@id", id);

                    int rowsAffected = cmd.ExecuteNonQuery();
                    if (rowsAffected > 0)
                    {
                        MessageBox.Show("Actualizare cu succes!");
                        LoadData2();
                        text_titlu.Clear();
                        text_an.Clear();
                        text_durata.Clear();
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

        private void add_Click_1(object sender, EventArgs e)
        {
            if (dataGridView1.SelectedRows.Count == 0 || dataGridView1.RowCount == 0)
            {
                MessageBox.Show("Selectati un rand pentru adaugare sau introduceti macar un rand");
                return;
            }
            DataGridViewRow select = dataGridView1.SelectedRows[0];
            int cod_artist = int.Parse(select.Cells[0].Value.ToString());
            if (string.IsNullOrWhiteSpace(text_titlu.Text))
            {
                MessageBox.Show("Toate campurile trebuie sa fie completate");
                return;
            }
            if (string.IsNullOrWhiteSpace(text_durata.Text) || string.IsNullOrWhiteSpace(text_an.Text))
            {
                MessageBox.Show("Toate campurile trebuie sa fie completate");
                return;
            }
            string titlu = text_titlu.Text;
            int an = int.Parse(text_an.Text);
            int durata = int.Parse(text_durata.Text);
            try
            {
                using (SqlConnection con = new SqlConnection(connectionString))
                {
                    con.Open();
                    SqlCommand cmd = new SqlCommand("Insert into Melodii(titlu,an_lansare,durata,cod_artist) values(@titlu,@an,@durata,@id)", con);
                    cmd.Parameters.AddWithValue("@titlu", titlu);
                    cmd.Parameters.AddWithValue("@an", an);
                    cmd.Parameters.AddWithValue("@durata", durata);
                    cmd.Parameters.AddWithValue("@id", cod_artist);
                    int rowsAffected = cmd.ExecuteNonQuery();
                    if (rowsAffected > 0)
                    {
                        MessageBox.Show("Adaugare cu succes!");
                        LoadData2();
                        text_titlu.Clear();
                        text_durata.Clear();
                        text_an.Clear();
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

        private void delete_Click_1(object sender, EventArgs e)
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
                    SqlCommand cmd = new SqlCommand("Delete Melodii WHERE cod_melodie = @id", con);
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
