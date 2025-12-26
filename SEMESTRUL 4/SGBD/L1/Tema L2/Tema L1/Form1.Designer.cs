namespace Tema_L1
{
    partial class Form1
    {
        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        ///  Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            label1 = new Label();
            dataGridView1 = new DataGridView();
            add_button = new Button();
            label2 = new Label();
            id = new Label();
            label3 = new Label();
            label4 = new Label();
            pret_box = new TextBox();
            gramaj_box = new TextBox();
            descriere_box = new TextBox();
            id_box = new TextBox();
            ((System.ComponentModel.ISupportInitialize)dataGridView1).BeginInit();
            SuspendLayout();
            // 
            // label1
            // 
            label1.AutoSize = true;
            label1.Font = new Font("Segoe UI Black", 24F, FontStyle.Bold | FontStyle.Italic, GraphicsUnit.Point, 238);
            label1.Location = new Point(673, 60);
            label1.Name = "label1";
            label1.Size = new Size(379, 86);
            label1.TabIndex = 0;
            label1.Text = "Borderouri";
            // 
            // dataGridView1
            // 
            dataGridView1.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            dataGridView1.Location = new Point(525, 214);
            dataGridView1.Name = "dataGridView1";
            dataGridView1.RowHeadersWidth = 82;
            dataGridView1.Size = new Size(692, 406);
            dataGridView1.TabIndex = 1;
            dataGridView1.CellContentClick += dataGridView1_CellClick;
            // 
            // add_button
            // 
            add_button.BackColor = Color.Lavender;
            add_button.Font = new Font("Segoe UI Black", 9F, FontStyle.Bold, GraphicsUnit.Point, 238);
            add_button.Location = new Point(585, 718);
            add_button.Name = "add_button";
            add_button.Size = new Size(162, 53);
            add_button.TabIndex = 2;
            add_button.Text = "Add";
            add_button.UseVisualStyleBackColor = false;
            add_button.Click += add_button_Click;
            // 
            // label2
            // 
            label2.AutoSize = true;
            label2.Font = new Font("Segoe UI Black", 9F, FontStyle.Bold, GraphicsUnit.Point, 238);
            label2.Location = new Point(884, 778);
            label2.Name = "label2";
            label2.Size = new Size(63, 32);
            label2.TabIndex = 4;
            label2.Text = "Pret";
            label2.Click += label2_Click;
            // 
            // id
            // 
            id.AutoSize = true;
            id.Font = new Font("Segoe UI Black", 9F, FontStyle.Bold, GraphicsUnit.Point, 238);
            id.Location = new Point(884, 718);
            id.Name = "id";
            id.Size = new Size(37, 32);
            id.TabIndex = 5;
            id.Text = "Id";
            id.Click += label3_Click;
            // 
            // label3
            // 
            label3.AutoSize = true;
            label3.Font = new Font("Segoe UI Black", 9F, FontStyle.Bold, GraphicsUnit.Point, 238);
            label3.Location = new Point(884, 827);
            label3.Name = "label3";
            label3.Size = new Size(97, 32);
            label3.TabIndex = 6;
            label3.Text = "Gramaj";
            // 
            // label4
            // 
            label4.AutoSize = true;
            label4.Font = new Font("Segoe UI Black", 9F, FontStyle.Bold, GraphicsUnit.Point, 238);
            label4.Location = new Point(884, 878);
            label4.Name = "label4";
            label4.Size = new Size(122, 32);
            label4.TabIndex = 7;
            label4.Text = "Descriere";
            // 
            // pret_box
            // 
            pret_box.BackColor = SystemColors.Info;
            pret_box.Location = new Point(1017, 771);
            pret_box.Name = "pret_box";
            pret_box.Size = new Size(200, 39);
            pret_box.TabIndex = 8;
            // 
            // gramaj_box
            // 
            gramaj_box.BackColor = SystemColors.Info;
            gramaj_box.Location = new Point(1017, 824);
            gramaj_box.Name = "gramaj_box";
            gramaj_box.Size = new Size(200, 39);
            gramaj_box.TabIndex = 9;
            // 
            // descriere_box
            // 
            descriere_box.BackColor = SystemColors.Info;
            descriere_box.Location = new Point(1017, 871);
            descriere_box.Name = "descriere_box";
            descriere_box.Size = new Size(200, 39);
            descriere_box.TabIndex = 10;
            // 
            // id_box
            // 
            id_box.BackColor = SystemColors.Info;
            id_box.Location = new Point(1017, 711);
            id_box.Name = "id_box";
            id_box.Size = new Size(200, 39);
            id_box.TabIndex = 11;
            // 
            // Form1
            // 
            AutoScaleDimensions = new SizeF(13F, 32F);
            AutoScaleMode = AutoScaleMode.Font;
            BackColor = Color.Lavender;
            BackgroundImage = Properties.Resources.Wallpaper_KH_Leapord_Jungle_1_jpg_optimal;
            ClientSize = new Size(1684, 1050);
            Controls.Add(id_box);
            Controls.Add(descriere_box);
            Controls.Add(gramaj_box);
            Controls.Add(pret_box);
            Controls.Add(label4);
            Controls.Add(label3);
            Controls.Add(id);
            Controls.Add(label2);
            Controls.Add(add_button);
            Controls.Add(dataGridView1);
            Controls.Add(label1);
            Name = "Form1";
            Text = "Borderouri";
            Load += Form1_Load;
            ((System.ComponentModel.ISupportInitialize)dataGridView1).EndInit();
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private Label label1;
        private DataGridView dataGridView1;
        private Button add_button;
        private TextBox pret_box;
        private Label label2;
        private Label id;
        private Label label3;
        private Label label4;
        private TextBox gramaj_box;
        private TextBox descriere_box;
        private TextBox id_box;
    }
}
