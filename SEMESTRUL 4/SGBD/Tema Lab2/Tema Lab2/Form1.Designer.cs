namespace Tema_Lab2
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
            dataGridViewChild = new DataGridView();
            dataGridViewParent = new DataGridView();
            buttonConnect = new Button();
            buttonUpdate = new Button();
            buttonAdd = new Button();
            buttonDelete = new Button();
            ((System.ComponentModel.ISupportInitialize)dataGridViewChild).BeginInit();
            ((System.ComponentModel.ISupportInitialize)dataGridViewParent).BeginInit();
            SuspendLayout();
            // 
            // dataGridViewChild
            // 
            dataGridViewChild.AllowUserToAddRows = false;
            dataGridViewChild.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            dataGridViewChild.Location = new Point(804, 238);
            dataGridViewChild.Margin = new Padding(5, 5, 5, 5);
            dataGridViewChild.Name = "dataGridViewChild";
            dataGridViewChild.ReadOnly = true;
            dataGridViewChild.RowHeadersWidth = 51;
            dataGridViewChild.RowTemplate.Height = 29;
            dataGridViewChild.Size = new Size(760, 752);
            dataGridViewChild.TabIndex = 9;
            // 
            // dataGridViewParent
            // 
            dataGridViewParent.AllowUserToAddRows = false;
            dataGridViewParent.AllowUserToDeleteRows = false;
            dataGridViewParent.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            dataGridViewParent.Location = new Point(20, 238);
            dataGridViewParent.Margin = new Padding(5, 5, 5, 5);
            dataGridViewParent.MultiSelect = false;
            dataGridViewParent.Name = "dataGridViewParent";
            dataGridViewParent.ReadOnly = true;
            dataGridViewParent.RowHeadersWidth = 51;
            dataGridViewParent.RowTemplate.Height = 29;
            dataGridViewParent.Size = new Size(757, 752);
            dataGridViewParent.TabIndex = 8;
            dataGridViewParent.CellClick += dataGridViewParent_CellClick;
            // 
            // buttonConnect
            // 
            buttonConnect.BackColor = Color.WhiteSmoke;
            buttonConnect.Location = new Point(674, 1008);
            buttonConnect.Margin = new Padding(5, 5, 5, 5);
            buttonConnect.Name = "buttonConnect";
            buttonConnect.Size = new Size(242, 98);
            buttonConnect.TabIndex = 7;
            buttonConnect.Text = "Connect to DB";
            buttonConnect.UseVisualStyleBackColor = false;
            buttonConnect.Click += buttonConnect_Click;
            // 
            // buttonUpdate
            // 
            buttonUpdate.BackColor = Color.WhiteSmoke;
            buttonUpdate.Location = new Point(941, 144);
            buttonUpdate.Margin = new Padding(5, 5, 5, 5);
            buttonUpdate.Name = "buttonUpdate";
            buttonUpdate.Size = new Size(224, 69);
            buttonUpdate.TabIndex = 19;
            buttonUpdate.Text = "Update";
            buttonUpdate.UseVisualStyleBackColor = false;
            buttonUpdate.Click += buttonUpdate_Click;
            // 
            // buttonAdd
            // 
            buttonAdd.BackColor = Color.WhiteSmoke;
            buttonAdd.Location = new Point(440, 144);
            buttonAdd.Margin = new Padding(5, 5, 5, 5);
            buttonAdd.Name = "buttonAdd";
            buttonAdd.Size = new Size(224, 69);
            buttonAdd.TabIndex = 17;
            buttonAdd.Text = "Add";
            buttonAdd.UseVisualStyleBackColor = false;
            buttonAdd.Click += buttonAdd_Click;
            // 
            // buttonDelete
            // 
            buttonDelete.BackColor = Color.WhiteSmoke;
            buttonDelete.Location = new Point(692, 144);
            buttonDelete.Margin = new Padding(5, 5, 5, 5);
            buttonDelete.Name = "buttonDelete";
            buttonDelete.Size = new Size(224, 69);
            buttonDelete.TabIndex = 18;
            buttonDelete.Text = "Delete";
            buttonDelete.UseVisualStyleBackColor = false;
            buttonDelete.Click += buttonDelete_Click;
            // 
            // Form1
            // 
            AutoScaleDimensions = new SizeF(13F, 32F);
            AutoScaleMode = AutoScaleMode.Font;
            BackColor = Color.RosyBrown;
            ClientSize = new Size(1606, 1118);
            Controls.Add(buttonUpdate);
            Controls.Add(buttonAdd);
            Controls.Add(buttonDelete);
            Controls.Add(dataGridViewChild);
            Controls.Add(dataGridViewParent);
            Controls.Add(buttonConnect);
            Margin = new Padding(5, 5, 5, 5);
            Name = "Form1";
            Text = "Form1";
            Load += Form1_Load;
            ((System.ComponentModel.ISupportInitialize)dataGridViewChild).EndInit();
            ((System.ComponentModel.ISupportInitialize)dataGridViewParent).EndInit();
            ResumeLayout(false);
        }

        #endregion

        private DataGridView dataGridViewChild;
        private DataGridView dataGridViewParent;
        private Button buttonConnect;
        private Button buttonUpdate;
        private Button buttonAdd;
        private Button buttonDelete;
    }
}