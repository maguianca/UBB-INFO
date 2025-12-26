using System.Configuration;
using System.Data;
using Microsoft.Data.SqlClient;
using System.Diagnostics;
using System.Windows.Forms;
namespace Tema_L2
{
    public partial class Form1 : Form
    {
        static string con = ConfigurationManager.ConnectionStrings["cn"].ConnectionString;
        static string tabel_parinte = ConfigurationManager.AppSettings["tabel_parinte"];
        static string tabel_copil = ConfigurationManager.AppSettings["tabel_copil"];
        static int nr_coloane = int.Parse(ConfigurationManager.AppSettings["nrcoloane"]);
        static string add_querry = ConfigurationManager.AppSettings["add_query"];
        static string delete_querry = ConfigurationManager.AppSettings["delete_query"];
        static string update_querry = ConfigurationManager.AppSettings["update_query"];

        static string argumente = ConfigurationManager.AppSettings["argumente"];

        static string nume_coloane = ConfigurationManager.AppSettings["nume_coloane"];
        static string tip_coloane = ConfigurationManager.AppSettings["tip_coloane"];
        static string coloana_copil = ConfigurationManager.AppSettings["coloana_copil"];
        private string id_tabel;
        SqlConnection cs = new SqlConnection(con);
        SqlDataAdapter da = new SqlDataAdapter();
        BindingSource bsP = new BindingSource();
        BindingSource bsC = new BindingSource();
        DataSet dsP = new DataSet();
        DataSet dsC = new DataSet();

        TextBox[] textBoxes = new TextBox[nr_coloane];
        Label[] labels = new Label[nr_coloane];
        public Form1()
        {
            InitializeComponent();
            string[] names = nume_coloane.Split(',');
            for (int i = 0; i < nr_coloane; i++)
            {
                labels[i] = new Label();
                textBoxes[i] = new TextBox();


                labels[i].Text = names[i];
                labels[i].Location = new Point(i * 150 + 300, 690);

                textBoxes[i].Text = "";
                textBoxes[i].Location = new Point(i * 150 + 300, 750);
                textBoxes[i].Size = new Size(100, 50);
                labels[i].Size = new Size(100, 40);
                this.Controls.Add(labels[i]);
                this.Controls.Add(textBoxes[i]);
            }
        }

        private void button_delete_Click(object sender, EventArgs e)
        {
            try
            {
                if (dataGridViewChild.CurrentCell != null)
                {
                    string id = dataGridViewChild.Rows[dataGridViewChild.CurrentCell.RowIndex].Cells[0].Value.ToString();
                    da.DeleteCommand = new SqlCommand(delete_querry, cs);
                    da.DeleteCommand.Parameters.Add("@id", SqlDbType.NVarChar).Value = id;
                    cs.Open();
                    da.DeleteCommand.ExecuteNonQuery();
                    cs.Close();
                    //update
                    da.SelectCommand = new SqlCommand($"SELECT * FROM {tabel_copil} WHERE {coloana_copil} = @id", cs);
                    da.SelectCommand.Parameters.Add("@id", SqlDbType.NVarChar).Value = id_tabel;
                    dsC.Clear();
                    da.Fill(dsC);
                    dataGridViewChild.DataSource = dsC.Tables[0];
                }
                else
                {
                    MessageBox.Show("Vă rugăm să selectați un rând pentru a-l șterge.");
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show($"A apărut o eroare: {ex.Message}");
            }
        }


        private void dataGridViewParent_CellClick(object sender, DataGridViewCellEventArgs e)
        {
            if (e.RowIndex >= 0) 
            {
                string id = dataGridViewParent.Rows[e.RowIndex].Cells[0].Value.ToString();
                da.SelectCommand = new SqlCommand("SELECT * from " + tabel_copil +
                    " where " + coloana_copil + " = @id", cs);
                id_tabel = id;
                da.SelectCommand.Parameters.AddWithValue("@id", id);
                dsC.Clear();
                da.Fill(dsC);
                dataGridViewChild.DataSource = dsC.Tables[0];
                bsC.DataSource = dsC.Tables[0];
            }
        }


        private void Form1_Load(object sender, EventArgs e)
        {
            da.SelectCommand = new SqlCommand("SELECT * FROM " + tabel_parinte, cs);
            dsP.Clear();
            da.Fill(dsP);
            dataGridViewParent.DataSource = dsP.Tables[0];
            bsP.DataSource = dsP.Tables[0];
            bsP.MoveLast();
        }

        private void button_add_Click(object sender, EventArgs e)
        {
            if (dataGridViewParent.SelectedCells.Count == 0)
            {
                MessageBox.Show("NU ati selectat nicio linie.");
                return;
            }
            da.InsertCommand = new
               SqlCommand(add_querry, cs);
            var id = dataGridViewParent.Rows[dataGridViewParent.CurrentCell.RowIndex].Cells[0].Value.ToString();
            da.InsertCommand.Parameters.Add("@id_b", SqlDbType.NVarChar).Value = id;
            string[] args = argumente.Split(",");
            string[] types =tip_coloane.Split(",");
            try
            {
                for (int i = 0; i <nr_coloane; i++)
                {
                    switch (types[i])
                    {
                        case "string":
                            da.InsertCommand.Parameters.Add(args[i], SqlDbType.VarChar).Value = textBoxes[i].Text;
                            break;
                        case "int":
                            da.InsertCommand.Parameters.Add(args[i], SqlDbType.Int).Value = int.Parse(textBoxes[i].Text);
                            break;
                        case "float":
                            da.InsertCommand.Parameters.Add(args[i], SqlDbType.Float).Value = float.Parse(textBoxes[i].Text);
                            break;
                        case "double":
                            da.InsertCommand.Parameters.Add(args[i], SqlDbType.Float).Value = double.Parse(textBoxes[i].Text);
                            break;
                        default:
                            MessageBox.Show("Tip de date necunoscut!");
                            return;
                    }
                }

                cs.Open();
                da.InsertCommand.ExecuteNonQuery();
                cs.Close();
                dsC.Clear();
                da.Fill(dsC);
            }

            catch
            {
                MessageBox.Show("Input gresit!");
            }
        }
        private void dataGridViewChild_CellClick(object sender, DataGridViewCellEventArgs e)
        {
            if (e.RowIndex < 0) return;

            for (int i = 0; i < nr_coloane; i++)
            {
                var cellValue = dataGridViewChild.Rows[e.RowIndex].Cells[i].Value;
                textBoxes[i].Text = cellValue != null ? cellValue.ToString() : "";
            }
            id_tabel = dataGridViewChild.Rows[e.RowIndex].Cells[nr_coloane].Value.ToString();
        }
        private void button_update_Click(object sender, EventArgs e)
        {
            if (dataGridViewChild.SelectedCells.Count == 0)
            {
                MessageBox.Show("NU ati selectat nicio linie.");
                return;
            }
            try
            {

                string id = id_tabel;
                da.UpdateCommand = new SqlCommand(update_querry, cs);
                da.UpdateCommand.Parameters.Add("@id_b", SqlDbType.NVarChar).Value = id;
                string[] args = argumente.Split(",");
                string[] types =tip_coloane.Split(",");

                for (int i = 0; i <nr_coloane; i++)
                {
                    switch (types[i])
                    {
                        case "string":
                            da.UpdateCommand.Parameters.Add(args[i], SqlDbType.VarChar).Value = textBoxes[i].Text;
                            break;
                        case "int":
                            da.UpdateCommand.Parameters.Add(args[i], SqlDbType.Int).Value = int.Parse(textBoxes[i].Text);
                            break;
                        case "float":
                            da.UpdateCommand.Parameters.Add(args[i], SqlDbType.Float).Value = float.Parse(textBoxes[i].Text);
                            break;
                        case "double":
                            da.UpdateCommand.Parameters.Add(args[i], SqlDbType.Float).Value = double.Parse(textBoxes[i].Text);
                            break;
                        default:
                            MessageBox.Show("Tip de date necunoscut!");
                            return;
                    }
                }
                cs.Open();
                int x = da.UpdateCommand.ExecuteNonQuery();
                cs.Close();
                dsC.Clear();
                da.Fill(dsC);
            }
            catch (Exception ex)
            {
                MessageBox.Show($"Eroare: {ex.Message}");
            }
        }

    }
}
