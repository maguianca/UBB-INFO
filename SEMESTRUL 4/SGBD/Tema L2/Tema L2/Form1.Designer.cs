namespace Tema_L2
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
            dataGridViewParent = new DataGridView();
            dataGridViewChild = new DataGridView();
            button_add = new Button();
            button_delete = new Button();
            button_update = new Button();
            ((System.ComponentModel.ISupportInitialize)dataGridViewParent).BeginInit();
            ((System.ComponentModel.ISupportInitialize)dataGridViewChild).BeginInit();
            SuspendLayout();
            // 
            // dataGridViewParent
            // 
            dataGridViewParent.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            dataGridViewParent.Location = new Point(12, 38);
            dataGridViewParent.Name = "dataGridViewParent";
            dataGridViewParent.RowHeadersWidth = 82;
            dataGridViewParent.Size = new Size(476, 606);
            dataGridViewParent.TabIndex = 0;
            dataGridViewParent.CellClick += dataGridViewParent_CellClick;
            // 
            // dataGridViewChild
            // 
            dataGridViewChild.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            dataGridViewChild.Location = new Point(494, 38);
            dataGridViewChild.Name = "dataGridViewChild";
            dataGridViewChild.RowHeadersWidth = 82;
            dataGridViewChild.Size = new Size(985, 606);
            dataGridViewChild.TabIndex = 1;
            dataGridViewChild.CellClick += dataGridViewChild_CellClick;
            // 
            // button_add
            // 
            button_add.BackColor = SystemColors.Info;
            button_add.Location = new Point(56, 690);
            button_add.Name = "button_add";
            button_add.Size = new Size(150, 46);
            button_add.TabIndex = 2;
            button_add.Text = "Add";
            button_add.UseVisualStyleBackColor = false;
            button_add.Click += button_add_Click;
            // 
            // button_delete
            // 
            button_delete.BackColor = SystemColors.Info;
            button_delete.Location = new Point(56, 778);
            button_delete.Name = "button_delete";
            button_delete.Size = new Size(150, 46);
            button_delete.TabIndex = 3;
            button_delete.Text = "Delete";
            button_delete.UseVisualStyleBackColor = false;
            button_delete.Click += button_delete_Click;
            // 
            // button_update
            // 
            button_update.BackColor = SystemColors.Info;
            button_update.Location = new Point(56, 873);
            button_update.Name = "button_update";
            button_update.Size = new Size(150, 46);
            button_update.TabIndex = 4;
            button_update.Text = "Update";
            button_update.UseVisualStyleBackColor = false;
            button_update.Click += button_update_Click;
            // 
            // Form1
            // 
            AutoScaleDimensions = new SizeF(13F, 32F);
            AutoScaleMode = AutoScaleMode.Font;
            BackgroundImage = (Image)resources.GetObject("$this.BackgroundImage");
            ClientSize = new Size(1491, 975);
            Controls.Add(button_update);
            Controls.Add(button_delete);
            Controls.Add(button_add);
            Controls.Add(dataGridViewChild);
            Controls.Add(dataGridViewParent);
            Name = "Form1";
            Text = "Form1";
            Load += Form1_Load;
            ((System.ComponentModel.ISupportInitialize)dataGridViewParent).EndInit();
            ((System.ComponentModel.ISupportInitialize)dataGridViewChild).EndInit();
            ResumeLayout(false);
        }

        #endregion

        private DataGridView dataGridViewParent;
        private DataGridView dataGridViewChild;
        private Button button_add;
        private Button button_delete;
        private Button button_update;
    }
}
