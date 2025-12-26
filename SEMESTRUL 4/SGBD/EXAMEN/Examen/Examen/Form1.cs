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

namespace Examen
{
    public partial class Form1 : Form
    {

        DataSet ds = new DataSet();
        SqlDataAdapter adapter;
        string connectionString = @"Server=ANCA-LAPTOP\SQLEXPRESS;Database=Practic_Examen;
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
                SqlCommand cmd = new SqlCommand("SELECT * FROM Eveniment WHERE id_tip = @id", con);
                cmd.Parameters.AddWithValue("@id", selectedId);

                adapter.SelectCommand = cmd;
                if (ds.Tables.Contains("Eveniment"))
                    ds.Tables["Eveniment"].Clear();

                adapter.Fill(ds, "Eveniment");
                dataGridView2.DataSource = ds.Tables["Eveniment"];
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
                    SqlCommand cmd = new SqlCommand("SELECT * FROM Eveniment WHERE id_tip= @id", con);
                    cmd.Parameters.AddWithValue("@id", selectedId);

                    adapter.SelectCommand = cmd;
                    if (ds.Tables.Contains("Eveniment"))
                        ds.Tables["Eveniment"].Clear();

                    adapter.Fill(ds, "Eveniment");
                    dataGridView2.DataSource = ds.Tables["Eveniment"];
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
            if (string.IsNullOrWhiteSpace(text_titlu.Text) || string.IsNullOrWhiteSpace(text_organizator.Text) || string.IsNullOrWhiteSpace(text_data.Text) || string.IsNullOrWhiteSpace(text_locatie.Text) || string.IsNullOrWhiteSpace(text_numar.Text))
            {
                MessageBox.Show("Toate campurile trebuie sa fie completate");
                return;
            }
            int id; string titlu; string organizator; DateTime data; string locatie; int numar;
            try
            {
                id = int.Parse(select.Cells[0].Value.ToString());
                titlu = text_titlu.Text;
                organizator = text_organizator.Text;
                data = DateTime.Parse(text_data.Text);
                locatie = text_locatie.Text;
                numar = int.Parse(text_numar.Text);
                if (numar <= 0) { MessageBox.Show("Numar trb sa fie mai mari decat 0"); return; }
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
                    SqlCommand cmd = new SqlCommand("UPDATE Eveniment SET titlu=@titlu, organizator= @organizator, data_eveniment= @data,numar=@numar,@locatie=locatie WHERE id_eveniment = @cod", con);
                    cmd.Parameters.AddWithValue("@titlu", titlu);
                    cmd.Parameters.AddWithValue("@organizator", organizator);
                    cmd.Parameters.AddWithValue("@data", data);
                    cmd.Parameters.AddWithValue("@locatie", locatie);
                    cmd.Parameters.AddWithValue("@numar", numar);
                    cmd.Parameters.AddWithValue("@cod", id);

                    int rowsAffected = cmd.ExecuteNonQuery();
                    if (rowsAffected > 0)
                    {
                        MessageBox.Show("Actualizare cu succes!");
                        LoadData2();
                        text_titlu.Clear();
                        text_organizator.Clear();
                        text_locatie.Clear();
                        text_data.Clear();
                        text_numar.Clear();
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
            if (string.IsNullOrWhiteSpace(text_titlu.Text) || string.IsNullOrWhiteSpace(text_organizator.Text) || string.IsNullOrWhiteSpace(text_data.Text) || string.IsNullOrWhiteSpace(text_locatie.Text) || string.IsNullOrWhiteSpace(text_numar.Text))
            {
                MessageBox.Show("Toate campurile trebuie sa fie completate");
                return;
            }
            int id; string titlu;string organizator;DateTime data;string locatie;int numar;
            try
            {
                id = int.Parse(select.Cells[0].Value.ToString());
                titlu = text_titlu.Text;
                organizator = text_organizator.Text;
                data = DateTime.Parse(text_data.Text);
                locatie= text_locatie.Text;
                numar = int.Parse(text_numar.Text);
                if (numar <= 0 ) { MessageBox.Show("Numar trb sa fie mai mari decat 0"); return; }
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
                    SqlCommand cmd = new SqlCommand("Insert into Eveniment(titlu,organizator,data_eveniment,locatie,numar,id_tip) values(@titlu,@organizator,@data,@locatie,@numar,@cod)", con);
                    cmd.Parameters.AddWithValue("@titlu", titlu);
                    cmd.Parameters.AddWithValue("@organizator", organizator);
                    cmd.Parameters.AddWithValue("@data", data);
                    cmd.Parameters.AddWithValue("@locatie", locatie);
                    cmd.Parameters.AddWithValue("@numar", numar);
                    cmd.Parameters.AddWithValue("@cod", cod);

                    int rowsAffected = cmd.ExecuteNonQuery();
                    if (rowsAffected > 0)
                    {
                        MessageBox.Show("Adaugare cu succes!");
                        LoadData2();
                        text_titlu.Clear();
                        text_organizator.Clear();
                        text_locatie.Clear(); 
                        text_data.Clear();
                        text_numar.Clear();
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
                    SqlCommand cmd = new SqlCommand("Delete Eveniment WHERE id_eveniment = @id", con);
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
