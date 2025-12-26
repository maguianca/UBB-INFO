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
    public partial class Form2 : Form
    {
        DataSet ds = new DataSet();
        SqlDataAdapter adapter;
        string connectionString = @"Server=ANCA-LAPTOP\SQLEXPRESS;Database=Practic_Briose;
        Integrated Security=True;TrustServerCertificate=True;";
        private int selectedCofetarieId = -1;
        public Form2()
        {
            InitializeComponent();
            comboBox.SelectedIndexChanged += comboBox_SelectedIndexChanged;
            adapter = new SqlDataAdapter();
        }
        private void LoadData()
        {
            try
            {
                using (SqlConnection con = new SqlConnection(connectionString))
                {
                    SqlCommand cmd = new SqlCommand("SELECT cod_cofetarie,nume_cofetarie FROM Cofetarii", con);
                    adapter = new SqlDataAdapter(cmd);
                    DataTable dt = new DataTable();
                    adapter.Fill(dt);

                    comboBox.DisplayMember = "nume_cofetarie";
                    comboBox.ValueMember = "cod_cofetarie";
                    comboBox.DataSource = dt;
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
                dataGridView1.DataSource = ds.Tables["Briose"];
            }
        }
        private void comboBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (comboBox.SelectedValue != null && int.TryParse(comboBox.SelectedValue.ToString(), out int id))
            {
                selectedCofetarieId = id;
                LoadData2(); 
            }
        }

        private void Form2_Load(object sender, EventArgs e)
        {
            LoadData();
        }

        private void Update_Click(object sender, EventArgs e)
        {
            if (dataGridView1.SelectedRows.Count == 0)
            {
                MessageBox.Show("Selectați o brioșă din listă pentru actualizare.");
                return;
            }

            if (string.IsNullOrWhiteSpace(text_pret.Text) ||
                string.IsNullOrWhiteSpace(text_descriere.Text) ||
                string.IsNullOrWhiteSpace(text_nume.Text))
            {
                MessageBox.Show("Toate câmpurile trebuie completate.");
                return;
            }

            double pret;
            if (!double.TryParse(text_pret.Text, out pret))
            {
                MessageBox.Show("Preț invalid.");
                return;
            }

            DataGridViewRow selected = dataGridView1.SelectedRows[0];
            int id = Convert.ToInt32(selected.Cells["cod_briosa"].Value);
            string descriere = text_descriere.Text;
            string nume = text_nume.Text;

            try
            {
                using (SqlConnection con = new SqlConnection(connectionString))
                {
                    con.Open();
                    SqlCommand cmd = new SqlCommand("UPDATE Briose SET nume_briosa=@nume, pret=@pret, descriere=@descriere WHERE cod_briosa=@id", con);
                    cmd.Parameters.AddWithValue("@nume", nume);
                    cmd.Parameters.AddWithValue("@pret", pret);
                    cmd.Parameters.AddWithValue("@descriere", descriere);
                    cmd.Parameters.AddWithValue("@id", id);

                    int rows = cmd.ExecuteNonQuery();
                    if (rows > 0)
                    {
                        MessageBox.Show("Actualizare realizată cu succes.");
                        LoadData2();
                        text_pret.Clear();
                        text_descriere.Clear();
                        text_nume.Clear();
                    }
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show("Eroare la actualizare: " + ex.Message);
            }
        }


        private void add_Click(object sender, EventArgs e)
        {
            if (selectedCofetarieId == -1)
            {
                MessageBox.Show("Selectați o cofetărie din listă.");
                return;
            }

            if (string.IsNullOrWhiteSpace(text_pret.Text) ||
                string.IsNullOrWhiteSpace(text_descriere.Text) ||
                string.IsNullOrWhiteSpace(text_nume.Text))
            {
                MessageBox.Show("Toate câmpurile trebuie completate.");
                return;
            }

            double pret;
            if (!double.TryParse(text_pret.Text, out pret))
            {
                MessageBox.Show("Prețul trebuie să fie un număr valid.");
                return;
            }

            string descriere = text_descriere.Text;
            string nume = text_nume.Text;

            try
            {
                using (SqlConnection con = new SqlConnection(connectionString))
                {
                    con.Open();
                    SqlCommand cmd = new SqlCommand("INSERT INTO Briose (nume_briosa, descriere, pret, cod_cofetarie) VALUES (@nume, @descriere, @pret, @cod)", con);
                    cmd.Parameters.AddWithValue("@nume", nume);
                    cmd.Parameters.AddWithValue("@descriere", descriere);
                    cmd.Parameters.AddWithValue("@pret", pret);
                    cmd.Parameters.AddWithValue("@cod", selectedCofetarieId);

                    int rows = cmd.ExecuteNonQuery();
                    if (rows > 0)
                    {
                        MessageBox.Show("Brioșa a fost adăugată cu succes.");
                        LoadData2();
                        text_pret.Clear();
                        text_descriere.Clear();
                        text_nume.Clear();
                    }
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show("Eroare la adăugare: " + ex.Message);
            }
        }
        private void delete_Click(object sender, EventArgs e)
        {
            if (dataGridView1.SelectedRows.Count == 0)
            {
                MessageBox.Show("Selectați o brioșă pentru ștergere.");
                return;
            }

            DataGridViewRow selected = dataGridView1.SelectedRows[0];
            int id = Convert.ToInt32(selected.Cells["cod_briosa"].Value);

            var confirm = MessageBox.Show("Sigur doriți să ștergeți această brioșă?", "Confirmare", MessageBoxButtons.YesNo);
            if (confirm != DialogResult.Yes) return;

            try
            {
                using (SqlConnection con = new SqlConnection(connectionString))
                {
                    con.Open();
                    SqlCommand cmd = new SqlCommand("DELETE FROM Briose WHERE cod_briosa=@id", con);
                    cmd.Parameters.AddWithValue("@id", id);

                    int rows = cmd.ExecuteNonQuery();
                    if (rows > 0)
                    {
                        MessageBox.Show("Brioșa a fost ștearsă.");
                        LoadData2();
                    }
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show("Eroare la ștergere: " + ex.Message);
            }
        }



    }
}
