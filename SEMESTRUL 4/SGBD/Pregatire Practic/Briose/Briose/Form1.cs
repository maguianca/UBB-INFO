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

namespace Briose
{
    public partial class Form1 : Form
    {
        DataSet ds = new DataSet();
        SqlDataAdapter adapter;
        string connectionString = @"Server=ANCA-LAPTOP\SQLEXPRESS;Database=Practic_Briose;
        Integrated Security=True;TrustServerCertificate=True;";
        private int selectedCofetarieId = -1;

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
                    adapter.SelectCommand = new SqlCommand("SELECT * FROM Cofetarii", con);
                    if (ds.Tables.Contains("Cofetarii"))
                        ds.Tables["Cofetarii"].Clear();
                    adapter.Fill(ds, "Cofetarii");
                    dataGridView1.DataSource = ds.Tables["Cofetarii"];
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
                SqlCommand cmd = new SqlCommand("SELECT * FROM Briose WHERE cod_cofetarie = @id", con);
                cmd.Parameters.AddWithValue("@id", selectedCofetarieId);

                adapter.SelectCommand = cmd;
                if (ds.Tables.Contains("Briose"))
                    ds.Tables["Briose"].Clear();

                adapter.Fill(ds, "Briose");
                dataGridView2.DataSource = ds.Tables["Briose"];
            }
        }
        private void dataGridView1_CellClick(object sender, DataGridViewCellEventArgs e)
        {
            if (e.RowIndex >= 0)
            {
                selectedCofetarieId = int.Parse(dataGridView1.Rows[e.RowIndex].Cells[0].Value.ToString());
                using (SqlConnection con = new SqlConnection(connectionString))
                {
                    con.Open();
                    SqlCommand cmd = new SqlCommand("SELECT * FROM Briose WHERE cod_cofetarie = @id", con);
                    cmd.Parameters.AddWithValue("@id", selectedCofetarieId);

                    adapter.SelectCommand = cmd;
                    if (ds.Tables.Contains("Briose"))
                        ds.Tables["Briose"].Clear();

                    adapter.Fill(ds, "Briose");
                    dataGridView2.DataSource = ds.Tables["Briose"];
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

        private void Update_Click(object sender, EventArgs e)
        {
            if (dataGridView2.SelectedRows.Count == 0)
            {
                MessageBox.Show("Selectati un rand pentru actualizare!");
                return;
            }
            DataGridViewRow select = dataGridView2.SelectedRows[0];
            if (string.IsNullOrWhiteSpace(text_pret.Text) || string.IsNullOrWhiteSpace(text_descriere.Text) || string.IsNullOrWhiteSpace(text_nume.Text))
            {
                MessageBox.Show("Toate campurile trebuie sa fie completate");
                return;
            }
            int id = int.Parse(select.Cells[0].Value.ToString());
            double pret = double.Parse(text_pret.Text);
            string descriere = text_descriere.Text;
            string nume= text_nume.Text;

            try
            {
                using (SqlConnection con = new SqlConnection(connectionString))
                {
                    con.Open();
                    SqlCommand cmd = new SqlCommand("UPDATE Briose SET nume_briosa=@nume, pret = @pret, descriere= @descriere WHERE cod_briosa = @cod_briosa", con);
                    cmd.Parameters.AddWithValue("@nume",nume);
                    cmd.Parameters.AddWithValue("@pret", pret);
                    cmd.Parameters.AddWithValue("@descriere", descriere);
                    cmd.Parameters.AddWithValue("@cod_briosa", id);

                    int rowsAffected = cmd.ExecuteNonQuery();
                    if (rowsAffected > 0)
                    {
                        MessageBox.Show("Actualizare cu succes!");
                        LoadData2();
                        text_pret.Clear();
                        text_descriere.Clear();
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
            int cod_cofetarie = int.Parse(select.Cells[0].Value.ToString());
            if (string.IsNullOrWhiteSpace(text_pret.Text))
            {
                MessageBox.Show("Toate campurile trebuie sa fie completate");
                return;
            }
            if (string.IsNullOrWhiteSpace(text_pret.Text) || string.IsNullOrWhiteSpace(text_descriere.Text) || string.IsNullOrWhiteSpace(text_nume.Text))
            {
                MessageBox.Show("Toate campurile trebuie sa fie completate");
                return;
            }
            double pret = double.Parse(text_pret.Text);
            string descriere = text_descriere.Text;
            string nume=text_nume.Text;
            try
            {
                using (SqlConnection con = new SqlConnection(connectionString))
                {
                    con.Open();
                    SqlCommand cmd = new SqlCommand("Insert into Briose(nume_briosa,descriere,pret,cod_cofetarie) values(@nume,@descriere,@pret,@cod)", con);
                    cmd.Parameters.AddWithValue("@nume", nume);
                    cmd.Parameters.AddWithValue("@pret", pret);
                    cmd.Parameters.AddWithValue("@descriere", descriere);
                    cmd.Parameters.AddWithValue("@cod", cod_cofetarie);

                    int rowsAffected = cmd.ExecuteNonQuery();
                    if (rowsAffected > 0)
                    {
                        MessageBox.Show("Adaugare cu succes!");
                        LoadData2();
                        text_pret.Clear();
                        text_descriere.Clear();
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
                    SqlCommand cmd = new SqlCommand("Delete Briose WHERE cod_briosa = @id", con);
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
