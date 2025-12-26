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

namespace Fructe
{
    public partial class Form1 : Form
    {
        DataSet ds = new DataSet();
        SqlDataAdapter adapter;
        string connectionString = @"Server=ANCA-LAPTOP\SQLEXPRESS;Database=Practic_Fructe;
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
                    adapter.SelectCommand = new SqlCommand("SELECT * FROM Tipuri", con);
                    if (ds.Tables.Contains("Tipuri"))
                        ds.Tables["Tipuri"].Clear();
                    adapter.Fill(ds, "Tipuri");
                    dataGridView1.DataSource = ds.Tables["Tipuri"];
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
                SqlCommand cmd = new SqlCommand("SELECT * FROM Fructe WHERE id_tip = @id", con);
                cmd.Parameters.AddWithValue("@id", selectedId);

                adapter.SelectCommand = cmd;
                if (ds.Tables.Contains("Fructe"))
                    ds.Tables["Fructe"].Clear();

                adapter.Fill(ds, "Fructe");
                dataGridView2.DataSource = ds.Tables["Fructe"];
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
                    SqlCommand cmd = new SqlCommand("SELECT * FROM Fructe WHERE id_tip = @id", con);
                    cmd.Parameters.AddWithValue("@id", selectedId);

                    adapter.SelectCommand = cmd;
                    if (ds.Tables.Contains("Fructe"))
                        ds.Tables["Fructe"].Clear();

                    adapter.Fill(ds, "Fructe");
                    dataGridView2.DataSource = ds.Tables["Fructe"];
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
            if (string.IsNullOrWhiteSpace(text_nume.Text) || string.IsNullOrWhiteSpace(text_numar_calorii.Text) )
            {
                MessageBox.Show("Toate campurile trebuie sa fie completate");
                return;
            }
            int id = int.Parse(select.Cells[0].Value.ToString());
            string nume = text_nume.Text;
            int numar_calorii = int.Parse(text_numar_calorii.Text);

            try
            {
                using (SqlConnection con = new SqlConnection(connectionString))
                {
                    con.Open();
                    SqlCommand cmd = new SqlCommand("UPDATE Fructe SET nume=@nume, numar_calorii= @nr WHERE id_fruct = @id", con);
                    cmd.Parameters.AddWithValue("@nume", nume);
                    cmd.Parameters.AddWithValue("@nr", numar_calorii);
                    cmd.Parameters.AddWithValue("@id", id);

                    int rowsAffected = cmd.ExecuteNonQuery();
                    if (rowsAffected > 0)
                    {
                        MessageBox.Show("Actualizare cu succes!");
                        LoadData2();
                        text_nume.Clear();
                        text_numar_calorii.Clear();
                        
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
            int cod = int.Parse(select.Cells[0].Value.ToString());
            if (string.IsNullOrWhiteSpace(text_nume.Text) || string.IsNullOrWhiteSpace(text_numar_calorii.Text))
            {
                MessageBox.Show("Toate campurile trebuie sa fie completate");
                return;
            }
            int id = int.Parse(select.Cells[0].Value.ToString());
            string nume = text_nume.Text;
            int numar_calorii = int.Parse(text_numar_calorii.Text);
            try
            {
                using (SqlConnection con = new SqlConnection(connectionString))
                {
                    con.Open();
                    SqlCommand cmd = new SqlCommand("Insert into Fructe(nume,numar_calorii,id_tip) values(@nume,@nr,@cod)", con);
                    cmd.Parameters.AddWithValue("@nume", nume);
                    cmd.Parameters.AddWithValue("@nr", numar_calorii);
                    cmd.Parameters.AddWithValue("@cod", cod);

                    int rowsAffected = cmd.ExecuteNonQuery();
                    if (rowsAffected > 0)
                    {
                        MessageBox.Show("Adaugare cu succes!");
                        LoadData2();
                        text_nume.Clear();
                        text_numar_calorii.Clear();
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
                    SqlCommand cmd = new SqlCommand("Delete Fructe WHERE id_fruct = @id", con);
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

        private void Form1_Load(object sender, EventArgs e)
        {
            LoadData();
        }
    }
}
