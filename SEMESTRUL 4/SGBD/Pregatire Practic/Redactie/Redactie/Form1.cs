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

namespace Redactie
{
    public partial class Form1 : Form
    {
        DataSet ds = new DataSet();
        SqlDataAdapter adapter;
        string connectionString = @"Server=ANCA-LAPTOP\SQLEXPRESS;Database=Practic_Redactie;
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
                    adapter.SelectCommand = new SqlCommand("SELECT * FROM Tip", con);
                    if (ds.Tables.Contains("Tip"))
                        ds.Tables["Tip"].Clear();
                    adapter.Fill(ds, "Tip");
                    dataGridView1.DataSource = ds.Tables["Tip"];
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
                SqlCommand cmd = new SqlCommand("SELECT * FROM Articole WHERE id_tip = @id", con);
                cmd.Parameters.AddWithValue("@id", selectedId);

                adapter.SelectCommand = cmd;
                if (ds.Tables.Contains("Articole"))
                    ds.Tables["Articole"].Clear();

                adapter.Fill(ds, "Articole");
                dataGridView2.DataSource = ds.Tables["Articole"];
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
                    SqlCommand cmd = new SqlCommand("SELECT * FROM Articole WHERE id_tip = @id", con);
                    cmd.Parameters.AddWithValue("@id", selectedId);

                    adapter.SelectCommand = cmd;
                    if (ds.Tables.Contains("Articole"))
                        ds.Tables["Articole"].Clear();

                    adapter.Fill(ds, "Articole");
                    dataGridView2.DataSource = ds.Tables["Articole"];
                }

            }
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            LoadData();
        }

        private void update_Click(object sender, EventArgs e)
        {
            DateTime data;
            if (dataGridView2.SelectedRows.Count == 0)
            {
                MessageBox.Show("Selectati un rand pentru actualizare!");
                return;
            }
            DataGridViewRow select = dataGridView2.SelectedRows[0];
            if (string.IsNullOrWhiteSpace(text_autor.Text) || string.IsNullOrWhiteSpace(text_data_aparitie.Text) || string.IsNullOrWhiteSpace(text_numar_citiri.Text))
            {
                MessageBox.Show("Toate campurile trebuie sa fie completate");
                return;
            }
            try
            {
                data = DateTime.Parse(text_data_aparitie.Text);
            }
            catch
            {
                MessageBox.Show("Introduceti data de tipul yyyy-mm-dd");
                return;
            }
            int id = int.Parse(select.Cells[0].Value.ToString());
            string autor = text_autor.Text;
            int numar_citiri = int.Parse(text_numar_citiri.Text);
            
            try
            {
                using (SqlConnection con = new SqlConnection(connectionString))
                {
                    con.Open();
                    SqlCommand cmd = new SqlCommand("UPDATE Articole SET autor=@nume, data_aparitie = @data, numar_citiri= @nr WHERE id_articol = @id", con);
                    cmd.Parameters.AddWithValue("@nume", autor);
                    cmd.Parameters.AddWithValue("@data", data);
                    cmd.Parameters.AddWithValue("@nr", numar_citiri);
                    cmd.Parameters.AddWithValue("@id", id);

                    int rowsAffected = cmd.ExecuteNonQuery();
                    if (rowsAffected > 0)
                    {
                        MessageBox.Show("Actualizare cu succes!");
                        LoadData2();
                        text_autor.Clear();
                        text_numar_citiri.Clear();
                        text_data_aparitie.Clear();
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
            DateTime data;
            if (dataGridView1.SelectedRows.Count == 0 || dataGridView1.RowCount == 0)
            {
                MessageBox.Show("Selectati un rand pentru adaugare sau introduceti macar un rand");
                return;
            }
            DataGridViewRow select = dataGridView1.SelectedRows[0];
            int cod= int.Parse(select.Cells[0].Value.ToString());
            if (string.IsNullOrWhiteSpace(text_data_aparitie.Text))
            {
                MessageBox.Show("Toate campurile trebuie sa fie completate");
                return;
            }
            if (string.IsNullOrWhiteSpace(text_data_aparitie.Text) || string.IsNullOrWhiteSpace(text_autor.Text) || string.IsNullOrWhiteSpace(text_numar_citiri.Text))
            {
                MessageBox.Show("Toate campurile trebuie sa fie completate");
                return;
            }
            try
            {
                data = DateTime.Parse(text_data_aparitie.Text);
            }
            catch
            {
                MessageBox.Show("Introduceti data de tipul yyyy-mm-dd");
                return;
            }
            string autor = text_autor.Text;
            int numar_citiri = int.Parse(text_numar_citiri.Text);
            try
            {
                using (SqlConnection con = new SqlConnection(connectionString))
                {
                    con.Open();
                    SqlCommand cmd = new SqlCommand("Insert into Articole(autor,data_aparitie,numar_citiri,id_tip) values(@nume,@data,@nr,@cod)", con);
                    cmd.Parameters.AddWithValue("@nume", autor);
                    cmd.Parameters.AddWithValue("@data", data);
                    cmd.Parameters.AddWithValue("@nr", numar_citiri);
                    cmd.Parameters.AddWithValue("@cod", cod);

                    int rowsAffected = cmd.ExecuteNonQuery();
                    if (rowsAffected > 0)
                    {
                        MessageBox.Show("Adaugare cu succes!");
                        LoadData2();
                        LoadData2();
                        text_autor.Clear();
                        text_numar_citiri.Clear();
                        text_data_aparitie.Clear();
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
                    SqlCommand cmd = new SqlCommand("Delete Articole WHERE id_articol = @id", con);
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
