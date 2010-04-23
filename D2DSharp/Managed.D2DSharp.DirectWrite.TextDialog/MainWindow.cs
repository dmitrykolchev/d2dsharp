using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Globalization;

using Managed.Graphics.DirectWrite;

namespace Managed.D2DSharp.DirectWrite.TextDialog
{
    public partial class MainWindow : Form
    {
        public MainWindow()
        {
            InitializeComponent();
        }

        protected override void OnLoad(EventArgs e)
        {
            base.OnLoad(e);
            List<string> fontNames = GetFontNames();
            foreach(string fontName in fontNames)
            {
                this.comboFont.Items.Add(fontName);
            }
            this.comboFont.Text = this.sampleTextControl1.FontName;
            this.textText.Text = this.sampleTextControl1.Text;
        }

        private static List<string> GetFontNames()
        {
            List<string> fonts = new List<string>();
            using (DirectWriteFactory factory = DirectWriteFactory.Create(DirectWriteFactoryType.Shared))
            {
                using (FontCollection fontCollection = factory.GetSystemFontCollection(false))
                {
                    for (int index = 0; index < fontCollection.Count; ++index)
                    {
                        using (FontFamily fontFamily = fontCollection[index])
                        {
                            using (LocalizedStrings names = fontFamily.FamilyNames)
                            {
                                int cultureIndex = names.FindCulture(CultureInfo.CurrentUICulture);
                                if (cultureIndex < 0)
                                {
                                    cultureIndex = names.FindCulture(new CultureInfo("en-us"));
                                }
                                fonts.Add(names[cultureIndex]);
                            }
                        }
                    }
                }
            }
            fonts.Sort();
            return fonts;
        }

        private void comboFont_SelectedIndexChanged(object sender, EventArgs e)
        {
            this.sampleTextControl1.FontName = this.comboFont.Text;
        }

        private void textText_TextChanged(object sender, EventArgs e)
        {
            this.sampleTextControl1.Text = this.textText.Text;
        }

        private void trackFontSize_ValueChanged(object sender, EventArgs e)
        {
            this.sampleTextControl1.FontSize = this.trackFontSize.Value;
            this.labelFontSize.Text = this.trackFontSize.Value.ToString();
        }

        private void checkBold_CheckedChanged(object sender, EventArgs e)
        {
            if (sender == this.checkBold)
                this.sampleTextControl1.Bold = this.checkBold.Checked;
            else if (sender == this.checkItalic)
                this.sampleTextControl1.Italic = this.checkItalic.Checked;
            else if (sender == this.checkUnderline)
                this.sampleTextControl1.Underline = this.checkUnderline.Checked;
        }
    }
}
