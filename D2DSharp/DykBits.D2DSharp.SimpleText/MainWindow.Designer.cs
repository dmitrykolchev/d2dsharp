﻿namespace DykBits.D2DSharp.SimpleText
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
            this.tabControl1 = new System.Windows.Forms.TabControl();
            this.tabPage1 = new System.Windows.Forms.TabPage();
            this.simpleTextControl1 = new DykBits.D2DSharp.SimpleText.SimpleTextControl();
            this.tabPage2 = new System.Windows.Forms.TabPage();
            this.multiformattedTextControl1 = new DykBits.D2DSharp.SimpleText.MultiformattedTextControl();
            this.tabControl1.SuspendLayout();
            this.tabPage1.SuspendLayout();
            this.tabPage2.SuspendLayout();
            this.SuspendLayout();
            // 
            // tabControl1
            // 
            this.tabControl1.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.tabControl1.Controls.Add(this.tabPage1);
            this.tabControl1.Controls.Add(this.tabPage2);
            this.tabControl1.Location = new System.Drawing.Point(12, 12);
            this.tabControl1.Name = "tabControl1";
            this.tabControl1.SelectedIndex = 0;
            this.tabControl1.Size = new System.Drawing.Size(773, 559);
            this.tabControl1.TabIndex = 0;
            // 
            // tabPage1
            // 
            this.tabPage1.Controls.Add(this.simpleTextControl1);
            this.tabPage1.Location = new System.Drawing.Point(4, 22);
            this.tabPage1.Name = "tabPage1";
            this.tabPage1.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage1.Size = new System.Drawing.Size(765, 533);
            this.tabPage1.TabIndex = 0;
            this.tabPage1.Text = "Simple Text";
            this.tabPage1.UseVisualStyleBackColor = true;
            // 
            // simpleTextControl1
            // 
            this.simpleTextControl1.BackColor = System.Drawing.Color.White;
            this.simpleTextControl1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.simpleTextControl1.Location = new System.Drawing.Point(3, 3);
            this.simpleTextControl1.Name = "simpleTextControl1";
            this.simpleTextControl1.Size = new System.Drawing.Size(759, 527);
            this.simpleTextControl1.TabIndex = 0;
            this.simpleTextControl1.Text = "simpleTextControl1";
            // 
            // tabPage2
            // 
            this.tabPage2.Controls.Add(this.multiformattedTextControl1);
            this.tabPage2.Location = new System.Drawing.Point(4, 22);
            this.tabPage2.Name = "tabPage2";
            this.tabPage2.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage2.Size = new System.Drawing.Size(765, 533);
            this.tabPage2.TabIndex = 1;
            this.tabPage2.Text = "Multiformatted Text";
            this.tabPage2.UseVisualStyleBackColor = true;
            // 
            // multiformattedTextControl1
            // 
            this.multiformattedTextControl1.BackColor = System.Drawing.Color.White;
            this.multiformattedTextControl1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.multiformattedTextControl1.Location = new System.Drawing.Point(3, 3);
            this.multiformattedTextControl1.Name = "multiformattedTextControl1";
            this.multiformattedTextControl1.Size = new System.Drawing.Size(759, 527);
            this.multiformattedTextControl1.TabIndex = 0;
            this.multiformattedTextControl1.Text = "multiformattedTextControl1";
            // 
            // MainWindow
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(792, 580);
            this.Controls.Add(this.tabControl1);
            this.Font = new System.Drawing.Font("Tahoma", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.Name = "MainWindow";
            this.Text = "Direct2D# Multiformatted Text";
            this.tabControl1.ResumeLayout(false);
            this.tabPage1.ResumeLayout(false);
            this.tabPage2.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.TabControl tabControl1;
        private System.Windows.Forms.TabPage tabPage1;
        private System.Windows.Forms.TabPage tabPage2;
        private SimpleTextControl simpleTextControl1;
        private MultiformattedTextControl multiformattedTextControl1;
    }
}

