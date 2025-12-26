namespace Tema_L1
{
    partial class Form2
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
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
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form2));
            dataGridView1 = new DataGridView();
            label1 = new Label();
            button_delete = new Button();
            button_update = new Button();
            pret_box = new TextBox();
            label2 = new Label();
            label3 = new Label();
            label4 = new Label();
            descriere_box = new TextBox();
            gramaj_box = new TextBox();
            ((System.ComponentModel.ISupportInitialize)dataGridView1).BeginInit();
            SuspendLayout();
            // 
            // dataGridView1
            // 
            dataGridView1.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            dataGridView1.Location = new Point(269, 314);
            dataGridView1.Name = "dataGridView1";
            dataGridView1.RowHeadersWidth = 82;
            dataGridView1.Size = new Size(1142, 285);
            dataGridView1.TabIndex = 0;
            dataGridView1.CellContentClick += dataGridView1_CellContentClick;
            // 
            // label1
            // 
            label1.AutoSize = true;
            label1.BackColor = Color.Transparent;
            label1.Font = new Font("Segoe UI Black", 24F, FontStyle.Bold, GraphicsUnit.Point, 238);
            label1.ForeColor = Color.FromArgb(128, 64, 64);
            label1.Location = new Point(684, 79);
            label1.Name = "label1";
            label1.Size = new Size(310, 86);
            label1.TabIndex = 1;
            label1.Text = "Bijuterii ";
            // 
            // button_delete
            // 
            button_delete.BackColor = Color.NavajoWhite;
            button_delete.Font = new Font("Segoe UI Black", 10.125F, FontStyle.Bold, GraphicsUnit.Point, 238);
            button_delete.ForeColor = Color.FromArgb(128, 64, 64);
            button_delete.Location = new Point(303, 802);
            button_delete.Name = "button_delete";
            button_delete.Size = new Size(212, 77);
            button_delete.TabIndex = 2;
            button_delete.Text = "Delete";
            button_delete.UseVisualStyleBackColor = false;
            button_delete.Click += button_delete_Click;
            // 
            // button_update
            // 
            button_update.BackColor = Color.NavajoWhite;
            button_update.Font = new Font("Segoe UI Black", 10.125F, FontStyle.Bold, GraphicsUnit.Point, 238);
            button_update.ForeColor = Color.FromArgb(128, 64, 64);
            button_update.Location = new Point(584, 802);
            button_update.Name = "button_update";
            button_update.Size = new Size(212, 77);
            button_update.TabIndex = 3;
            button_update.Text = "Update";
            button_update.UseVisualStyleBackColor = false;
            button_update.Click += button_update_Click;
            // 
            // pret_box
            // 
            pret_box.BackColor = Color.FromArgb(255, 224, 192);
            pret_box.Location = new Point(1036, 785);
            pret_box.Name = "pret_box";
            pret_box.Size = new Size(200, 39);
            pret_box.TabIndex = 4;
            // 
            // label2
            // 
            label2.AutoSize = true;
            label2.BackColor = Color.NavajoWhite;
            label2.Font = new Font("Segoe UI Black", 9F, FontStyle.Bold, GraphicsUnit.Point, 238);
            label2.ForeColor = Color.FromArgb(128, 64, 64);
            label2.Location = new Point(898, 792);
            label2.Name = "label2";
            label2.Size = new Size(63, 32);
            label2.TabIndex = 5;
            label2.Text = "Pret";
            // 
            // label3
            // 
            label3.AutoSize = true;
            label3.BackColor = Color.NavajoWhite;
            label3.Font = new Font("Segoe UI Black", 9F, FontStyle.Bold, GraphicsUnit.Point, 238);
            label3.ForeColor = Color.FromArgb(128, 64, 64);
            label3.Location = new Point(898, 847);
            label3.Name = "label3";
            label3.Size = new Size(97, 32);
            label3.TabIndex = 6;
            label3.Text = "Gramaj";
            label3.Click += label3_Click;
            // 
            // label4
            // 
            label4.AutoSize = true;
            label4.BackColor = Color.NavajoWhite;
            label4.Font = new Font("Segoe UI Black", 9F, FontStyle.Bold, GraphicsUnit.Point, 238);
            label4.ForeColor = Color.FromArgb(128, 64, 64);
            label4.Location = new Point(898, 901);
            label4.Name = "label4";
            label4.Size = new Size(122, 32);
            label4.TabIndex = 8;
            label4.Text = "Descriere";
            // 
            // descriere_box
            // 
            descriere_box.BackColor = Color.FromArgb(255, 224, 192);
            descriere_box.Location = new Point(1036, 898);
            descriere_box.Name = "descriere_box";
            descriere_box.Size = new Size(200, 39);
            descriere_box.TabIndex = 9;
            // 
            // gramaj_box
            // 
            gramaj_box.BackColor = Color.FromArgb(255, 224, 192);
            gramaj_box.Location = new Point(1036, 844);
            gramaj_box.Name = "gramaj_box";
            gramaj_box.Size = new Size(200, 39);
            gramaj_box.TabIndex = 10;
            // 
            // Form2
            // 
            AutoScaleDimensions = new SizeF(13F, 32F);
            AutoScaleMode = AutoScaleMode.Font;
            BackgroundImage = (Image)resources.GetObject("$this.BackgroundImage");
            ClientSize = new Size(1684, 1050);
            Controls.Add(gramaj_box);
            Controls.Add(descriere_box);
            Controls.Add(label4);
            Controls.Add(label3);
            Controls.Add(label2);
            Controls.Add(pret_box);
            Controls.Add(button_update);
            Controls.Add(button_delete);
            Controls.Add(label1);
            Controls.Add(dataGridView1);
            Name = "Form2";
            Text = "Bijuterii";
            Load += Form2_Load;
            ((System.ComponentModel.ISupportInitialize)dataGridView1).EndInit();
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private DataGridView dataGridView1;
        private Label label1;
        private Button button_delete;
        private Button button_update;
        public TextBox pret_box;
        private Label label2;
        private Label label3;
        private Label label4;
        public TextBox descriere_box;
        public TextBox gramaj_box;
    }
}