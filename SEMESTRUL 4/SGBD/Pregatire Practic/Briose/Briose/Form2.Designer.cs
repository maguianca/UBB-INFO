namespace Briose
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
            this.comboBox = new System.Windows.Forms.ComboBox();
            this.dataGridView1 = new System.Windows.Forms.DataGridView();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.text_nume = new System.Windows.Forms.TextBox();
            this.text_descriere = new System.Windows.Forms.TextBox();
            this.text_pret = new System.Windows.Forms.TextBox();
            this.Update = new System.Windows.Forms.Button();
            this.add = new System.Windows.Forms.Button();
            this.delete = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView1)).BeginInit();
            this.SuspendLayout();
            // 
            // comboBox
            // 
            this.comboBox.FormattingEnabled = true;
            this.comboBox.Location = new System.Drawing.Point(124, 152);
            this.comboBox.Name = "comboBox";
            this.comboBox.Size = new System.Drawing.Size(364, 33);
            this.comboBox.TabIndex = 0;
            // 
            // dataGridView1
            // 
            this.dataGridView1.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridView1.Location = new System.Drawing.Point(782, 87);
            this.dataGridView1.Name = "dataGridView1";
            this.dataGridView1.RowHeadersWidth = 82;
            this.dataGridView1.RowTemplate.Height = 33;
            this.dataGridView1.Size = new System.Drawing.Size(720, 561);
            this.dataGridView1.TabIndex = 1;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(131, 329);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(0, 25);
            this.label1.TabIndex = 2;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(131, 288);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(71, 25);
            this.label2.TabIndex = 3;
            this.label2.Text = "nume ";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(131, 367);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(101, 25);
            this.label3.TabIndex = 4;
            this.label3.Text = "descriere";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(131, 436);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(49, 25);
            this.label4.TabIndex = 7;
            this.label4.Text = "pret";
            // 
            // text_nume
            // 
            this.text_nume.Location = new System.Drawing.Point(274, 288);
            this.text_nume.Name = "text_nume";
            this.text_nume.Size = new System.Drawing.Size(302, 31);
            this.text_nume.TabIndex = 8;
            // 
            // text_descriere
            // 
            this.text_descriere.Location = new System.Drawing.Point(274, 367);
            this.text_descriere.Name = "text_descriere";
            this.text_descriere.Size = new System.Drawing.Size(302, 31);
            this.text_descriere.TabIndex = 9;
            // 
            // text_pret
            // 
            this.text_pret.Location = new System.Drawing.Point(274, 430);
            this.text_pret.Name = "text_pret";
            this.text_pret.Size = new System.Drawing.Size(302, 31);
            this.text_pret.TabIndex = 10;
            // 
            // Update
            // 
            this.Update.Location = new System.Drawing.Point(124, 556);
            this.Update.Name = "Update";
            this.Update.Size = new System.Drawing.Size(212, 48);
            this.Update.TabIndex = 11;
            this.Update.Text = "update";
            this.Update.UseVisualStyleBackColor = true;
            this.Update.Click += new System.EventHandler(this.Update_Click);
            // 
            // add
            // 
            this.add.Location = new System.Drawing.Point(124, 642);
            this.add.Name = "add";
            this.add.Size = new System.Drawing.Size(212, 48);
            this.add.TabIndex = 12;
            this.add.Text = "add";
            this.add.UseVisualStyleBackColor = true;
            this.add.Click += new System.EventHandler(this.add_Click);
            // 
            // delete
            // 
            this.delete.Location = new System.Drawing.Point(124, 736);
            this.delete.Name = "delete";
            this.delete.Size = new System.Drawing.Size(212, 48);
            this.delete.TabIndex = 13;
            this.delete.Text = "delete";
            this.delete.UseVisualStyleBackColor = true;
            this.delete.Click += new System.EventHandler(this.delete_Click);
            // 
            // Form2
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(12F, 25F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1555, 900);
            this.Controls.Add(this.delete);
            this.Controls.Add(this.add);
            this.Controls.Add(this.Update);
            this.Controls.Add(this.text_pret);
            this.Controls.Add(this.text_descriere);
            this.Controls.Add(this.text_nume);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.dataGridView1);
            this.Controls.Add(this.comboBox);
            this.Name = "Form2";
            this.Text = "Form2";
            this.Load += new System.EventHandler(this.Form2_Load);
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView1)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ComboBox comboBox;
        private System.Windows.Forms.DataGridView dataGridView1;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.TextBox text_nume;
        private System.Windows.Forms.TextBox text_descriere;
        private System.Windows.Forms.TextBox text_pret;
        private System.Windows.Forms.Button Update;
        private System.Windows.Forms.Button add;
        private System.Windows.Forms.Button delete;
    }
}