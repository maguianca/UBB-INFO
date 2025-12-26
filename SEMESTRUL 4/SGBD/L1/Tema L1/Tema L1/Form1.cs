using Microsoft.Data.SqlClient;
using System.Data;
namespace Tema_L1
{
    public partial class Form1 : Form
    {
        string connectionString = @"Server=ANCA-LAPTOP\SQLEXPRESS;Database=MagazinDeBijuterii;
        Integrated Security=True;TrustServerCertificate=True;";
        DataSet ds = new DataSet();
        SqlDataAdapter adapter;
        public delegate void DataUpdatedEventHandler();
        public event DataUpdatedEventHandler DataUpdated;

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
                    adapter.SelectCommand = new SqlCommand("SELECT * FROM BorderouMarcare", con);
                    if (ds.Tables.Contains("BorderouMarcare"))
                        ds.Tables["BorderouMarcare"].Clear();
                    adapter.Fill(ds, "BorderouMarcare");
                    dataGridView1.DataSource = ds.Tables["BorderouMarcare"];
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show("Eroare: " + ex.Message);
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
                string id = dataGridView1.Rows[e.RowIndex].Cells[0].Value.ToString();
                Form2 form2 = new Form2(id,ds,adapter,this);
                form2.Show();
            }
        }

        private void label2_Click(object sender, EventArgs e)
        {

        }
    
        private void add_button_Click(object sender, EventArgs e)
        {
            if (dataGridView1.SelectedRows.Count == 0 || dataGridView1.RowCount == 0)
            {
                MessageBox.Show("Selectati un rand pentru adaugare sau introduceti macar un rand");
                return;
            }
            DataGridViewRow select = dataGridView1.SelectedRows[0];
            string id_borderou = select.Cells[0].Value.ToString();
            if (string.IsNullOrWhiteSpace(pret_box.Text))
            {
                MessageBox.Show("Toate campurile trebuie sa fie completate");
                return;
            }
            if (string.IsNullOrWhiteSpace(pret_box.Text) || string.IsNullOrWhiteSpace(descriere_box.Text) || string.IsNullOrWhiteSpace(gramaj_box.Text)
                || string.IsNullOrWhiteSpace(this.id.Text))
            {
                MessageBox.Show("Toate campurile trebuie sa fie completate");
                return;
            }
            string id = this.id_box.Text;
            double pret = double.Parse(pret_box.Text);
            string descriere = descriere_box.Text;
            double gramaj = double.Parse(gramaj_box.Text);
            try
            {
                using (SqlConnection con = new SqlConnection(connectionString))
                {
                    con.Open();
                    SqlCommand cmd = new SqlCommand("Insert into Bijuterie(id_bij,descriere_bij,pret_bij,gramaj_bij,id_borderou) values(@id,@descriere,@pret,@gramaj,@id_b)", con);
                    cmd.Parameters.AddWithValue("@id", id);
                    cmd.Parameters.AddWithValue("@pret", pret);
                    cmd.Parameters.AddWithValue("@descriere", descriere);
                    cmd.Parameters.AddWithValue("@gramaj", gramaj);
                    cmd.Parameters.AddWithValue("@id_b", id_borderou);

                    int rowsAffected = cmd.ExecuteNonQuery();
                    if (rowsAffected > 0)
                    {
                        MessageBox.Show("Adaugare cu succes!");
                        DataUpdated?.Invoke();
                        LoadData();
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

        private void label3_Click(object sender, EventArgs e)
        {

        }
    }
}
