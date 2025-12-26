namespace FestivalSellpoint.UI.Forms
{
    partial class SpectacoleViewForm
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
            this.splitContainer1 = new System.Windows.Forms.SplitContainer();
            this.SpectacoleView = new System.Windows.Forms.DataGridView();
            this.panel1 = new System.Windows.Forms.Panel();
            this.DatePicker = new System.Windows.Forms.DateTimePicker();
            this.FilteredSpectacoleView = new System.Windows.Forms.DataGridView();
            this.panel2 = new System.Windows.Forms.Panel();
            this.NrLocuriDoriteBox = new System.Windows.Forms.NumericUpDown();
            this.ReserveButton = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.NumeCumparatorBox = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer1)).BeginInit();
            this.splitContainer1.Panel1.SuspendLayout();
            this.splitContainer1.Panel2.SuspendLayout();
            this.splitContainer1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.SpectacoleView)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.FilteredSpectacoleView)).BeginInit();
            this.panel2.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.NrLocuriDoriteBox)).BeginInit();
            this.SuspendLayout();
            // 
            // splitContainer1
            // 
            this.splitContainer1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.splitContainer1.Location = new System.Drawing.Point(0, 0);
            this.splitContainer1.Margin = new System.Windows.Forms.Padding(6);
            this.splitContainer1.Name = "splitContainer1";
            // 
            // splitContainer1.Panel1
            // 
            this.splitContainer1.Panel1.Controls.Add(this.SpectacoleView);
            this.splitContainer1.Panel1.Controls.Add(this.panel1);
            // 
            // splitContainer1.Panel2
            // 
            this.splitContainer1.Panel2.Controls.Add(this.DatePicker);
            this.splitContainer1.Panel2.Controls.Add(this.FilteredSpectacoleView);
            this.splitContainer1.Panel2.Controls.Add(this.panel2);
            this.splitContainer1.Size = new System.Drawing.Size(1534, 731);
            this.splitContainer1.SplitterDistance = 912;
            this.splitContainer1.SplitterWidth = 8;
            this.splitContainer1.TabIndex = 0;
            // 
            // SpectacoleView
            // 
            this.SpectacoleView.AllowUserToAddRows = false;
            this.SpectacoleView.AllowUserToDeleteRows = false;
            this.SpectacoleView.AllowUserToResizeRows = false;
            this.SpectacoleView.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.SpectacoleView.Dock = System.Windows.Forms.DockStyle.Fill;
            this.SpectacoleView.Location = new System.Drawing.Point(0, 0);
            this.SpectacoleView.Margin = new System.Windows.Forms.Padding(6);
            this.SpectacoleView.MultiSelect = false;
            this.SpectacoleView.Name = "SpectacoleView";
            this.SpectacoleView.RowHeadersWidth = 82;
            this.SpectacoleView.Size = new System.Drawing.Size(912, 731);
            this.SpectacoleView.TabIndex = 1;
            this.SpectacoleView.CellContentClick += new System.Windows.Forms.DataGridViewCellEventHandler(this.SpectacoleView_CellContentClick);
            this.SpectacoleView.CellFormatting += new System.Windows.Forms.DataGridViewCellFormattingEventHandler(this.SpectacoleView_CellFormatting);
            this.SpectacoleView.SelectionChanged += new System.EventHandler(this.SpectacoleView_SelectionChanged);
            // 
            // panel1
            // 
            this.panel1.AutoSize = true;
            this.panel1.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.panel1.Dock = System.Windows.Forms.DockStyle.Top;
            this.panel1.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.panel1.Location = new System.Drawing.Point(0, 0);
            this.panel1.Margin = new System.Windows.Forms.Padding(6);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(912, 0);
            this.panel1.TabIndex = 0;
            // 
            // DatePicker
            // 
            this.DatePicker.Location = new System.Drawing.Point(12, 23);
            this.DatePicker.Margin = new System.Windows.Forms.Padding(6);
            this.DatePicker.Name = "DatePicker";
            this.DatePicker.Size = new System.Drawing.Size(576, 31);
            this.DatePicker.TabIndex = 2;
            this.DatePicker.ValueChanged += new System.EventHandler(this.DatePicker_ValueChanged);
            // 
            // FilteredSpectacoleView
            // 
            this.FilteredSpectacoleView.AllowUserToAddRows = false;
            this.FilteredSpectacoleView.AllowUserToDeleteRows = false;
            this.FilteredSpectacoleView.AllowUserToResizeRows = false;
            this.FilteredSpectacoleView.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.FilteredSpectacoleView.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.FilteredSpectacoleView.Location = new System.Drawing.Point(12, 73);
            this.FilteredSpectacoleView.Margin = new System.Windows.Forms.Padding(6);
            this.FilteredSpectacoleView.Name = "FilteredSpectacoleView";
            this.FilteredSpectacoleView.RowHeadersWidth = 82;
            this.FilteredSpectacoleView.Size = new System.Drawing.Size(574, 306);
            this.FilteredSpectacoleView.TabIndex = 4;
            this.FilteredSpectacoleView.CellFormatting += new System.Windows.Forms.DataGridViewCellFormattingEventHandler(this.FilteredSpectacoleView_CellFormatting);
            this.FilteredSpectacoleView.SelectionChanged += new System.EventHandler(this.FilteredSpectacoleView_SelectionChanged);
            // 
            // panel2
            // 
            this.panel2.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.panel2.Controls.Add(this.NrLocuriDoriteBox);
            this.panel2.Controls.Add(this.ReserveButton);
            this.panel2.Controls.Add(this.label1);
            this.panel2.Controls.Add(this.NumeCumparatorBox);
            this.panel2.Controls.Add(this.label3);
            this.panel2.Controls.Add(this.label2);
            this.panel2.Location = new System.Drawing.Point(12, 390);
            this.panel2.Margin = new System.Windows.Forms.Padding(6);
            this.panel2.Name = "panel2";
            this.panel2.Size = new System.Drawing.Size(574, 317);
            this.panel2.TabIndex = 3;
            this.panel2.Paint += new System.Windows.Forms.PaintEventHandler(this.panel2_Paint);
            // 
            // NrLocuriDoriteBox
            // 
            this.NrLocuriDoriteBox.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.NrLocuriDoriteBox.Location = new System.Drawing.Point(202, 138);
            this.NrLocuriDoriteBox.Margin = new System.Windows.Forms.Padding(6);
            this.NrLocuriDoriteBox.Name = "NrLocuriDoriteBox";
            this.NrLocuriDoriteBox.Size = new System.Drawing.Size(366, 31);
            this.NrLocuriDoriteBox.TabIndex = 6;
            this.NrLocuriDoriteBox.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            // 
            // ReserveButton
            // 
            this.ReserveButton.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.ReserveButton.Location = new System.Drawing.Point(224, 229);
            this.ReserveButton.Margin = new System.Windows.Forms.Padding(6);
            this.ReserveButton.Name = "ReserveButton";
            this.ReserveButton.Size = new System.Drawing.Size(344, 44);
            this.ReserveButton.TabIndex = 5;
            this.ReserveButton.Text = "Rezerva bilet";
            this.ReserveButton.UseVisualStyleBackColor = true;
            this.ReserveButton.Click += new System.EventHandler(this.ReserveButton_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.Location = new System.Drawing.Point(6, 19);
            this.label1.Margin = new System.Windows.Forms.Padding(6, 0, 6, 0);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(173, 31);
            this.label1.TabIndex = 0;
            this.label1.Text = "Rezerva bilet";
            // 
            // NumeCumparatorBox
            // 
            this.NumeCumparatorBox.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.NumeCumparatorBox.Location = new System.Drawing.Point(202, 88);
            this.NumeCumparatorBox.Margin = new System.Windows.Forms.Padding(6);
            this.NumeCumparatorBox.Name = "NumeCumparatorBox";
            this.NumeCumparatorBox.Size = new System.Drawing.Size(362, 31);
            this.NumeCumparatorBox.TabIndex = 3;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(22, 144);
            this.label3.Margin = new System.Windows.Forms.Padding(6, 0, 6, 0);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(168, 25);
            this.label3.TabIndex = 2;
            this.label3.Text = "Nr. Locuri Dorite";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(6, 94);
            this.label2.Margin = new System.Windows.Forms.Padding(6, 0, 6, 0);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(186, 25);
            this.label2.TabIndex = 1;
            this.label2.Text = "Nume Cumparator";
            // 
            // SpectacoleViewForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(12F, 25F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1534, 731);
            this.Controls.Add(this.splitContainer1);
            this.Margin = new System.Windows.Forms.Padding(6);
            this.Name = "SpectacoleViewForm";
            this.Text = "Vizualizare spectacole";
            this.splitContainer1.Panel1.ResumeLayout(false);
            this.splitContainer1.Panel1.PerformLayout();
            this.splitContainer1.Panel2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer1)).EndInit();
            this.splitContainer1.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.SpectacoleView)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.FilteredSpectacoleView)).EndInit();
            this.panel2.ResumeLayout(false);
            this.panel2.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.NrLocuriDoriteBox)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.SplitContainer splitContainer1;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.DataGridView SpectacoleView;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Panel panel2;
        private System.Windows.Forms.TextBox NumeCumparatorBox;
        private System.Windows.Forms.Button ReserveButton;
        private System.Windows.Forms.NumericUpDown NrLocuriDoriteBox;
        private System.Windows.Forms.DateTimePicker DatePicker;
        private System.Windows.Forms.DataGridView FilteredSpectacoleView;
    }
}