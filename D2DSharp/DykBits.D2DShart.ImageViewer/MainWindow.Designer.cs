namespace Managed.D2DShart.ImageViewer
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
            this.components = new System.ComponentModel.Container();
            this.buttonNext = new System.Windows.Forms.Button();
            this.buttonPrev = new System.Windows.Forms.Button();
            this.buttonOpenFolder = new System.Windows.Forms.Button();
            this.labelFolder = new System.Windows.Forms.Label();
            this.folderBrowserDialog1 = new System.Windows.Forms.FolderBrowserDialog();
            this.buttonRotateLeft = new System.Windows.Forms.Button();
            this.buttonRotateRight = new System.Windows.Forms.Button();
            this.checkBox1 = new System.Windows.Forms.CheckBox();
            this.direct2DSurface1 = new Managed.D2DShart.ImageViewer.Direct2DSurface();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.SuspendLayout();
            // 
            // buttonNext
            // 
            this.buttonNext.Anchor = System.Windows.Forms.AnchorStyles.Bottom;
            this.buttonNext.Location = new System.Drawing.Point(443, 592);
            this.buttonNext.Name = "buttonNext";
            this.buttonNext.Size = new System.Drawing.Size(75, 23);
            this.buttonNext.TabIndex = 1;
            this.buttonNext.Text = ">>";
            this.buttonNext.UseVisualStyleBackColor = true;
            this.buttonNext.Click += new System.EventHandler(this.buttonNext_Click);
            // 
            // buttonPrev
            // 
            this.buttonPrev.Anchor = System.Windows.Forms.AnchorStyles.Bottom;
            this.buttonPrev.Location = new System.Drawing.Point(362, 592);
            this.buttonPrev.Name = "buttonPrev";
            this.buttonPrev.Size = new System.Drawing.Size(75, 23);
            this.buttonPrev.TabIndex = 2;
            this.buttonPrev.Text = "<<";
            this.buttonPrev.UseVisualStyleBackColor = true;
            this.buttonPrev.Click += new System.EventHandler(this.buttonPrev_Click);
            // 
            // buttonOpenFolder
            // 
            this.buttonOpenFolder.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.buttonOpenFolder.Location = new System.Drawing.Point(13, 592);
            this.buttonOpenFolder.Name = "buttonOpenFolder";
            this.buttonOpenFolder.Size = new System.Drawing.Size(27, 23);
            this.buttonOpenFolder.TabIndex = 3;
            this.buttonOpenFolder.Text = "...";
            this.buttonOpenFolder.UseVisualStyleBackColor = true;
            this.buttonOpenFolder.Click += new System.EventHandler(this.buttonOpenFolder_Click);
            // 
            // labelFolder
            // 
            this.labelFolder.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.labelFolder.AutoSize = true;
            this.labelFolder.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(224)))), ((int)(((byte)(224)))), ((int)(((byte)(224)))));
            this.labelFolder.Location = new System.Drawing.Point(46, 597);
            this.labelFolder.Name = "labelFolder";
            this.labelFolder.Size = new System.Drawing.Size(104, 13);
            this.labelFolder.TabIndex = 4;
            this.labelFolder.Text = "press to open folder";
            // 
            // buttonRotateLeft
            // 
            this.buttonRotateLeft.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.buttonRotateLeft.Location = new System.Drawing.Point(775, 12);
            this.buttonRotateLeft.Name = "buttonRotateLeft";
            this.buttonRotateLeft.Size = new System.Drawing.Size(93, 23);
            this.buttonRotateLeft.TabIndex = 5;
            this.buttonRotateLeft.Text = "Rotate Left";
            this.buttonRotateLeft.UseVisualStyleBackColor = true;
            this.buttonRotateLeft.Click += new System.EventHandler(this.buttonRotateLeft_Click);
            // 
            // buttonRotateRight
            // 
            this.buttonRotateRight.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.buttonRotateRight.Location = new System.Drawing.Point(775, 41);
            this.buttonRotateRight.Name = "buttonRotateRight";
            this.buttonRotateRight.Size = new System.Drawing.Size(93, 23);
            this.buttonRotateRight.TabIndex = 6;
            this.buttonRotateRight.Text = "Rotate Right";
            this.buttonRotateRight.UseVisualStyleBackColor = true;
            this.buttonRotateRight.Click += new System.EventHandler(this.buttonRotateRight_Click);
            // 
            // checkBox1
            // 
            this.checkBox1.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.checkBox1.AutoSize = true;
            this.checkBox1.Checked = true;
            this.checkBox1.CheckState = System.Windows.Forms.CheckState.Checked;
            this.checkBox1.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(224)))), ((int)(((byte)(224)))), ((int)(((byte)(224)))));
            this.checkBox1.Location = new System.Drawing.Point(775, 70);
            this.checkBox1.Name = "checkBox1";
            this.checkBox1.Size = new System.Drawing.Size(87, 17);
            this.checkBox1.TabIndex = 7;
            this.checkBox1.Text = "Show Border";
            this.checkBox1.UseVisualStyleBackColor = true;
            this.checkBox1.CheckedChanged += new System.EventHandler(this.checkBox1_CheckedChanged);
            // 
            // direct2DSurface1
            // 
            this.direct2DSurface1.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.direct2DSurface1.BackColor = System.Drawing.Color.Black;
            this.direct2DSurface1.Location = new System.Drawing.Point(12, 12);
            this.direct2DSurface1.Name = "direct2DSurface1";
            this.direct2DSurface1.ShowBorder = true;
            this.direct2DSurface1.Size = new System.Drawing.Size(757, 574);
            this.direct2DSurface1.TabIndex = 0;
            this.direct2DSurface1.Text = "direct2DSurface1";
            // 
            // timer1
            // 
            this.timer1.Tick += new System.EventHandler(this.timer1_Tick);
            // 
            // MainWindow
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(64)))), ((int)(((byte)(64)))), ((int)(((byte)(64)))));
            this.ClientSize = new System.Drawing.Size(880, 627);
            this.Controls.Add(this.checkBox1);
            this.Controls.Add(this.buttonRotateRight);
            this.Controls.Add(this.buttonRotateLeft);
            this.Controls.Add(this.labelFolder);
            this.Controls.Add(this.buttonOpenFolder);
            this.Controls.Add(this.buttonPrev);
            this.Controls.Add(this.buttonNext);
            this.Controls.Add(this.direct2DSurface1);
            this.Font = new System.Drawing.Font("Tahoma", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.Name = "MainWindow";
            this.Text = "Direct2D# Image Viewer";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private Direct2DSurface direct2DSurface1;
        private System.Windows.Forms.Button buttonNext;
        private System.Windows.Forms.Button buttonPrev;
        private System.Windows.Forms.Button buttonOpenFolder;
        private System.Windows.Forms.Label labelFolder;
        private System.Windows.Forms.FolderBrowserDialog folderBrowserDialog1;
        private System.Windows.Forms.Button buttonRotateLeft;
        private System.Windows.Forms.Button buttonRotateRight;
        private System.Windows.Forms.CheckBox checkBox1;
        private System.Windows.Forms.Timer timer1;
    }
}

