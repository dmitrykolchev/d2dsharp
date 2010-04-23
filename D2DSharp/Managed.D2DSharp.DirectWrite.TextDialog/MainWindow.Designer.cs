namespace Managed.D2DSharp.DirectWrite.TextDialog
{
    partial class MainWindow
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
            this.label1 = new System.Windows.Forms.Label();
            this.textText = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.comboFont = new System.Windows.Forms.ComboBox();
            this.checkBold = new System.Windows.Forms.CheckBox();
            this.checkItalic = new System.Windows.Forms.CheckBox();
            this.checkUnderline = new System.Windows.Forms.CheckBox();
            this.trackFontSize = new System.Windows.Forms.TrackBar();
            this.label3 = new System.Windows.Forms.Label();
            this.labelFontSize = new System.Windows.Forms.Label();
            this.sampleTextControl1 = new Managed.D2DSharp.DirectWrite.TextDialog.SampleTextControl();
            ((System.ComponentModel.ISupportInitialize)(this.trackFontSize)).BeginInit();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(9, 15);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(29, 13);
            this.label1.TabIndex = 0;
            this.label1.Text = "Text";
            // 
            // textText
            // 
            this.textText.Location = new System.Drawing.Point(12, 31);
            this.textText.Name = "textText";
            this.textText.Size = new System.Drawing.Size(181, 21);
            this.textText.TabIndex = 1;
            this.textText.TextChanged += new System.EventHandler(this.textText_TextChanged);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(9, 55);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(29, 13);
            this.label2.TabIndex = 2;
            this.label2.Text = "Font";
            // 
            // comboFont
            // 
            this.comboFont.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboFont.FormattingEnabled = true;
            this.comboFont.Location = new System.Drawing.Point(12, 71);
            this.comboFont.Name = "comboFont";
            this.comboFont.Size = new System.Drawing.Size(181, 21);
            this.comboFont.TabIndex = 3;
            this.comboFont.SelectedIndexChanged += new System.EventHandler(this.comboFont_SelectedIndexChanged);
            // 
            // checkBold
            // 
            this.checkBold.AutoSize = true;
            this.checkBold.Location = new System.Drawing.Point(12, 98);
            this.checkBold.Name = "checkBold";
            this.checkBold.Size = new System.Drawing.Size(46, 17);
            this.checkBold.TabIndex = 4;
            this.checkBold.Text = "Bold";
            this.checkBold.UseVisualStyleBackColor = true;
            this.checkBold.CheckedChanged += new System.EventHandler(this.checkBold_CheckedChanged);
            // 
            // checkItalic
            // 
            this.checkItalic.AutoSize = true;
            this.checkItalic.Location = new System.Drawing.Point(12, 121);
            this.checkItalic.Name = "checkItalic";
            this.checkItalic.Size = new System.Drawing.Size(49, 17);
            this.checkItalic.TabIndex = 5;
            this.checkItalic.Text = "Italic";
            this.checkItalic.UseVisualStyleBackColor = true;
            this.checkItalic.CheckedChanged += new System.EventHandler(this.checkBold_CheckedChanged);
            // 
            // checkUnderline
            // 
            this.checkUnderline.AutoSize = true;
            this.checkUnderline.Location = new System.Drawing.Point(12, 144);
            this.checkUnderline.Name = "checkUnderline";
            this.checkUnderline.Size = new System.Drawing.Size(71, 17);
            this.checkUnderline.TabIndex = 6;
            this.checkUnderline.Text = "Underline";
            this.checkUnderline.UseVisualStyleBackColor = true;
            this.checkUnderline.CheckedChanged += new System.EventHandler(this.checkBold_CheckedChanged);
            // 
            // trackFontSize
            // 
            this.trackFontSize.Location = new System.Drawing.Point(12, 196);
            this.trackFontSize.Maximum = 256;
            this.trackFontSize.Minimum = 1;
            this.trackFontSize.Name = "trackFontSize";
            this.trackFontSize.Size = new System.Drawing.Size(181, 45);
            this.trackFontSize.TabIndex = 7;
            this.trackFontSize.TickStyle = System.Windows.Forms.TickStyle.None;
            this.trackFontSize.Value = 72;
            this.trackFontSize.ValueChanged += new System.EventHandler(this.trackFontSize_ValueChanged);
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(9, 180);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(55, 13);
            this.label3.TabIndex = 8;
            this.label3.Text = "Font Size:";
            // 
            // labelFontSize
            // 
            this.labelFontSize.AutoSize = true;
            this.labelFontSize.Location = new System.Drawing.Point(70, 180);
            this.labelFontSize.Name = "labelFontSize";
            this.labelFontSize.Size = new System.Drawing.Size(19, 13);
            this.labelFontSize.TabIndex = 9;
            this.labelFontSize.Text = "72";
            // 
            // sampleTextControl1
            // 
            this.sampleTextControl1.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.sampleTextControl1.BackColor = System.Drawing.Color.White;
            this.sampleTextControl1.Location = new System.Drawing.Point(215, 12);
            this.sampleTextControl1.Name = "sampleTextControl1";
            this.sampleTextControl1.Size = new System.Drawing.Size(633, 311);
            this.sampleTextControl1.TabIndex = 10;
            // 
            // MainWindow
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(860, 335);
            this.Controls.Add(this.sampleTextControl1);
            this.Controls.Add(this.labelFontSize);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.trackFontSize);
            this.Controls.Add(this.checkUnderline);
            this.Controls.Add(this.checkItalic);
            this.Controls.Add(this.checkBold);
            this.Controls.Add(this.comboFont);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.textText);
            this.Controls.Add(this.label1);
            this.Font = new System.Drawing.Font("Tahoma", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.Name = "MainWindow";
            this.Text = "Text Dialog Sample";
            ((System.ComponentModel.ISupportInitialize)(this.trackFontSize)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox textText;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.ComboBox comboFont;
        private System.Windows.Forms.CheckBox checkBold;
        private System.Windows.Forms.CheckBox checkItalic;
        private System.Windows.Forms.CheckBox checkUnderline;
        private System.Windows.Forms.TrackBar trackFontSize;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label labelFontSize;
        private SampleTextControl sampleTextControl1;
    }
}

