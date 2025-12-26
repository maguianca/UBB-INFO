namespace Fructe
{
    partial class Form1
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
            this.dataGridView1 = new System.Windows.Forms.DataGridView();
            this.dataGridView2 = new System.Windows.Forms.DataGridView();
            this.update = new System.Windows.Forms.Button();
            this.add = new System.Windows.Forms.Button();
            this.delete = new System.Windows.Forms.Button();
            this.nume = new System.Windows.Forms.Label();
            this.label = new System.Windows.Forms.Label();
            this.text_nume = new System.Windows.Forms.TextBox();
            this.text_numar_calorii = new System.Windows.Forms.TextBox();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView2)).BeginInit();
            this.SuspendLayout();
            // 
            // dataGridView1
            // 
            this.dataGridView1.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridView1.Location = new System.Drawing.Point(73, 80);
            this.dataGridView1.Name = "dataGridView1";
            this.dataGridView1.RowHeadersWidth = 82;
            this.dataGridView1.Size = new System.Drawing.Size(625, 370);
            this.dataGridView1.TabIndex = 0;
            // 
            // dataGridView2
            // 
            this.dataGridView2.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridView2.Location = new System.Drawing.Point(798, 80);
            this.dataGridView2.Name = "dataGridView2";
            this.dataGridView2.RowHeadersWidth = 82;
            this.dataGridView2.RowTemplate.Height = 33;
            this.dataGridView2.Size = new System.Drawing.Size(622, 370);
            this.dataGridView2.TabIndex = 1;
            // 
            // update
            // 
            this.update.Location = new System.Drawing.Point(776, 512);
            this.update.Name = "update";
            this.update.Size = new System.Drawing.Size(159, 58);
            this.update.TabIndex = 2;
            this.update.Text = "update";
            this.update.UseVisualStyleBackColor = true;
            this.update.Click += new System.EventHandler(this.update_Click);
            // 
            // add
            // 
            this.add.Location = new System.Drawing.Point(985, 512);
            this.add.Name = "add";
            this.add.Size = new System.Drawing.Size(159, 58);
            this.add.TabIndex = 3;
            this.add.Text = "add";
            this.add.UseVisualStyleBackColor = true;
            this.add.Click += new System.EventHandler(this.add_Click);
            // 
            // delete
            // 
            this.delete.Location = new System.Drawing.Point(1189, 512);
            this.delete.Name = "delete";
            this.delete.Size = new System.Drawing.Size(159, 58);
            this.delete.TabIndex = 4;
            this.delete.Text = "delete";
            this.delete.UseVisualStyleBackColor = true;
            this.delete.Click += new System.EventHandler(this.delete_Click);
            // 
            // nume
            // 
            this.nume.AutoSize = true;
            this.nume.Location = new System.Drawing.Point(103, 512);
            this.nume.Name = "nume";
            this.nume.Size = new System.Drawing.Size(65, 25);
            this.nume.TabIndex = 5;
            this.nume.Text = "nume";
            // 
            // label
            // 
            this.label.AutoSize = true;
            this.label.Location = new System.Drawing.Point(103, 574);
            this.label.Name = "label";
            this.label.Size = new System.Drawing.Size(141, 25);
            this.label.TabIndex = 6;
            this.label.Text = "numar_calorii";
            // 
            // text_nume
            // 
            this.text_nume.Location = new System.Drawing.Point(314, 505);
            this.text_nume.Name = "text_nume";
            this.text_nume.Size = new System.Drawing.Size(289, 31);
            this.text_nume.TabIndex = 7;
            // 
            // text_numar_calorii
            // 
            this.text_numar_calorii.Location = new System.Drawing.Point(314, 571);
            this.text_numar_calorii.Name = "text_numar_calorii";
            this.text_numar_calorii.Size = new System.Drawing.Size(289, 31);
            this.text_numar_calorii.TabIndex = 8;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(12F, 25F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.Khaki;
            this.ClientSize = new System.Drawing.Size(1451, 861);
            this.Controls.Add(this.text_numar_calorii);
            this.Controls.Add(this.text_nume);
            this.Controls.Add(this.label);
            this.Controls.Add(this.nume);
            this.Controls.Add(this.delete);
            this.Controls.Add(this.add);
            this.Controls.Add(this.update);
            this.Controls.Add(this.dataGridView2);
            this.Controls.Add(this.dataGridView1);
            this.Name = "Form1";
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.Form1_Load);
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView2)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.DataGridView dataGridView1;
        private System.Windows.Forms.DataGridView dataGridView2;
        private System.Windows.Forms.Button update;
        private System.Windows.Forms.Button add;
        private System.Windows.Forms.Button delete;
        private System.Windows.Forms.Label nume;
        private System.Windows.Forms.Label label;
        private System.Windows.Forms.TextBox text_nume;
        private System.Windows.Forms.TextBox text_numar_calorii;
    }
}

