namespace Practic_Premii
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
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.text_nume = new System.Windows.Forms.TextBox();
            this.text_sponsor = new System.Windows.Forms.TextBox();
            this.text_an = new System.Windows.Forms.TextBox();
            this.text_nume_castigator = new System.Windows.Forms.TextBox();
            this.text_varsta = new System.Windows.Forms.TextBox();
            this.update = new System.Windows.Forms.Button();
            this.add = new System.Windows.Forms.Button();
            this.delete = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView2)).BeginInit();
            this.SuspendLayout();
            // 
            // dataGridView1
            // 
            this.dataGridView1.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridView1.Location = new System.Drawing.Point(68, 47);
            this.dataGridView1.Name = "dataGridView1";
            this.dataGridView1.RowHeadersWidth = 82;
            this.dataGridView1.RowTemplate.Height = 33;
            this.dataGridView1.Size = new System.Drawing.Size(695, 464);
            this.dataGridView1.TabIndex = 0;
            // 
            // dataGridView2
            // 
            this.dataGridView2.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridView2.Location = new System.Drawing.Point(982, 47);
            this.dataGridView2.Name = "dataGridView2";
            this.dataGridView2.RowHeadersWidth = 82;
            this.dataGridView2.RowTemplate.Height = 33;
            this.dataGridView2.Size = new System.Drawing.Size(666, 449);
            this.dataGridView2.TabIndex = 1;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(123, 566);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(65, 25);
            this.label1.TabIndex = 2;
            this.label1.Text = "nume";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(123, 632);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(89, 25);
            this.label2.TabIndex = 3;
            this.label2.Text = "sponsor";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(123, 682);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(36, 25);
            this.label3.TabIndex = 4;
            this.label3.Text = "an";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(123, 745);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(165, 25);
            this.label4.TabIndex = 5;
            this.label4.Text = "nume castigator";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(123, 807);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(71, 25);
            this.label5.TabIndex = 6;
            this.label5.Text = "varsta";
            // 
            // text_nume
            // 
            this.text_nume.Location = new System.Drawing.Point(246, 563);
            this.text_nume.Name = "text_nume";
            this.text_nume.Size = new System.Drawing.Size(365, 31);
            this.text_nume.TabIndex = 7;
            // 
            // text_sponsor
            // 
            this.text_sponsor.Location = new System.Drawing.Point(246, 632);
            this.text_sponsor.Name = "text_sponsor";
            this.text_sponsor.Size = new System.Drawing.Size(365, 31);
            this.text_sponsor.TabIndex = 8;
            // 
            // text_an
            // 
            this.text_an.Location = new System.Drawing.Point(246, 682);
            this.text_an.Name = "text_an";
            this.text_an.Size = new System.Drawing.Size(365, 31);
            this.text_an.TabIndex = 9;
            // 
            // text_nume_castigator
            // 
            this.text_nume_castigator.Location = new System.Drawing.Point(323, 739);
            this.text_nume_castigator.Name = "text_nume_castigator";
            this.text_nume_castigator.Size = new System.Drawing.Size(365, 31);
            this.text_nume_castigator.TabIndex = 10;
            // 
            // text_varsta
            // 
            this.text_varsta.Location = new System.Drawing.Point(264, 807);
            this.text_varsta.Name = "text_varsta";
            this.text_varsta.Size = new System.Drawing.Size(365, 31);
            this.text_varsta.TabIndex = 11;
            // 
            // update
            // 
            this.update.Location = new System.Drawing.Point(795, 567);
            this.update.Name = "update";
            this.update.Size = new System.Drawing.Size(187, 36);
            this.update.TabIndex = 12;
            this.update.Text = "update";
            this.update.UseVisualStyleBackColor = true;
            this.update.Click += new System.EventHandler(this.update_Click);
            // 
            // add
            // 
            this.add.Location = new System.Drawing.Point(1032, 563);
            this.add.Name = "add";
            this.add.Size = new System.Drawing.Size(187, 36);
            this.add.TabIndex = 13;
            this.add.Text = "add";
            this.add.UseVisualStyleBackColor = true;
            this.add.Click += new System.EventHandler(this.add_Click);
            // 
            // delete
            // 
            this.delete.Location = new System.Drawing.Point(1283, 563);
            this.delete.Name = "delete";
            this.delete.Size = new System.Drawing.Size(187, 36);
            this.delete.TabIndex = 14;
            this.delete.Text = "delete";
            this.delete.UseVisualStyleBackColor = true;
            this.delete.Click += new System.EventHandler(this.delete_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(12F, 25F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.ActiveCaption;
            this.ClientSize = new System.Drawing.Size(1721, 1019);
            this.Controls.Add(this.delete);
            this.Controls.Add(this.add);
            this.Controls.Add(this.update);
            this.Controls.Add(this.text_varsta);
            this.Controls.Add(this.text_nume_castigator);
            this.Controls.Add(this.text_an);
            this.Controls.Add(this.text_sponsor);
            this.Controls.Add(this.text_nume);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
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
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.TextBox text_nume;
        private System.Windows.Forms.TextBox text_sponsor;
        private System.Windows.Forms.TextBox text_an;
        private System.Windows.Forms.TextBox text_nume_castigator;
        private System.Windows.Forms.TextBox text_varsta;
        private System.Windows.Forms.Button update;
        private System.Windows.Forms.Button add;
        private System.Windows.Forms.Button delete;
    }
}

