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

namespace Practic_Premii
{

    public partial class Form1 : Form
    {
        DataSet ds = new DataSet();
        SqlDataAdapter adapter;
        string connectionString = @"Server=ANCA-LAPTOP\SQLEXPRESS;Database=Practic_Premii;
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
                SqlCommand cmd = new SqlCommand("SELECT * FROM Premiu WHERE id_tip = @id", con);
                cmd.Parameters.AddWithValue("@id", selectedId);

                adapter.SelectCommand = cmd;
                if (ds.Tables.Contains("Premiu"))
                    ds.Tables["Premiu"].Clear();

                adapter.Fill(ds, "Premiu");
                dataGridView2.DataSource = ds.Tables["Premiu"];
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
                    SqlCommand cmd = new SqlCommand("SELECT * FROM Premiu WHERE id_tip= @id", con);
                    cmd.Parameters.AddWithValue("@id", selectedId);

                    adapter.SelectCommand = cmd;
                    if (ds.Tables.Contains("Premiu"))
                        ds.Tables["Premiu"].Clear();

                    adapter.Fill(ds, "Premiu");
                    dataGridView2.DataSource = ds.Tables["Premiu"];
                }

            }
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            LoadData();
        }

        private void update_Click(object sender, EventArgs e)
        {
            if (dataGridView2.SelectedRows.Count == 0)
            {
                MessageBox.Show("Selectati un rand pentru actualizare!");
                return;
            }
            DataGridViewRow select = dataGridView2.SelectedRows[0];
            if (string.IsNullOrWhiteSpace(text_nume.Text) || string.IsNullOrWhiteSpace(text_sponsor.Text) || string.IsNullOrWhiteSpace(text_an.Text)|| string.IsNullOrWhiteSpace(text_nume_castigator.Text)|| string.IsNullOrWhiteSpace(text_varsta.Text))
            {
                MessageBox.Show("Toate campurile trebuie sa fie completate");
                return;
            }
            int id; string nume;string sponsor;DateTime an;string nume_castigator;int varsta;
            try
            {
                id = int.Parse(select.Cells[0].Value.ToString());
                nume = text_nume.Text;
                sponsor = text_sponsor.Text;
                an=DateTime.Parse(text_an.Text);
                nume_castigator = text_nume_castigator.Text;
                varsta=int.Parse(text_varsta.Text);
                if (varsta<18) { MessageBox.Show("Varsta trb sa fie mai mare decat 18"); return; }
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
                    SqlCommand cmd = new SqlCommand("UPDATE Premiu SET nume=@nume, sponsor = @sponsor, an= @an,nume_castigator=@nume_c,varsta=@varsta WHERE id_premiu = @cod", con);
                    cmd.Parameters.AddWithValue("@nume", nume);
                    cmd.Parameters.AddWithValue("@sponsor", sponsor);
                    cmd.Parameters.AddWithValue("@nume_c", nume_castigator);
                    cmd.Parameters.AddWithValue("@varsta", varsta);
                    cmd.Parameters.AddWithValue("@an", an);
                    cmd.Parameters.AddWithValue("@cod", id);

                    int rowsAffected = cmd.ExecuteNonQuery();
                    if (rowsAffected > 0)
                    {
                        MessageBox.Show("Actualizare cu succes!");
                        LoadData2();
                        text_nume.Clear();
                        text_varsta.Clear();
                        text_an.Clear();
                        text_nume_castigator.Clear();
                        text_sponsor.Clear();
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
            if (string.IsNullOrWhiteSpace(text_nume.Text) || string.IsNullOrWhiteSpace(text_sponsor.Text) || string.IsNullOrWhiteSpace(text_an.Text) || string.IsNullOrWhiteSpace(text_nume_castigator.Text) || string.IsNullOrWhiteSpace(text_varsta.Text))
            {
                MessageBox.Show("Toate campurile trebuie sa fie completate");
                return;
            }
            string nume; string sponsor; DateTime an; string nume_castigator; int varsta;
            try
            { 
                nume = text_nume.Text;
                sponsor = text_sponsor.Text;
                an = DateTime.Parse(text_an.Text);
                nume_castigator = text_nume_castigator.Text;
                varsta = int.Parse(text_varsta.Text);
                if (varsta <1) { MessageBox.Show("Varsta trb sa fie mai mare decat 1"); return; }
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
                    SqlCommand cmd = new SqlCommand("Insert into Premiu(nume,varsta,nume_castigator,an,sponsor,id_tip) values(@nume,@varsta,@nume_c,@an,@sponsor,@cod)", con);
                    cmd.Parameters.AddWithValue("@nume", nume);
                    cmd.Parameters.AddWithValue("@sponsor", sponsor);
                    cmd.Parameters.AddWithValue("@nume_c", nume_castigator);
                    cmd.Parameters.AddWithValue("@varsta", varsta);
                    cmd.Parameters.AddWithValue("@an", an);
                    cmd.Parameters.AddWithValue("@cod", cod);

                    int rowsAffected = cmd.ExecuteNonQuery();
                    if (rowsAffected > 0)
                    {
                        MessageBox.Show("Adaugare cu succes!");
                        LoadData2();
                        text_nume.Clear();
                        text_varsta.Clear();
                        text_an.Clear();
                        text_nume_castigator.Clear();
                        text_sponsor.Clear();
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
                    SqlCommand cmd = new SqlCommand("Delete Premiu WHERE id_premiu = @id", con);
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
