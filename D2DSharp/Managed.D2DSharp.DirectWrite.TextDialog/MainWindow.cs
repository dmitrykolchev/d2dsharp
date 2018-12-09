using Managed.Graphics.DirectWrite;
using System;
using System.Collections.Generic;
using System.Globalization;
using System.Windows.Forms;

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
            foreach (string fontName in fontNames)
            {
                comboFont.Items.Add(fontName);
            }
            comboFont.Text = sampleTextControl1.FontName;
            textText.Text = sampleTextControl1.Text;
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
            sampleTextControl1.FontName = comboFont.Text;
        }

        private void textText_TextChanged(object sender, EventArgs e)
        {
            sampleTextControl1.Text = textText.Text;
        }

        private void trackFontSize_ValueChanged(object sender, EventArgs e)
        {
            sampleTextControl1.FontSize = trackFontSize.Value;
            labelFontSize.Text = trackFontSize.Value.ToString();
        }

        private void checkBold_CheckedChanged(object sender, EventArgs e)
        {
            if (sender == checkBold)
            {
                sampleTextControl1.Bold = checkBold.Checked;
            }
            else if (sender == checkItalic)
            {
                sampleTextControl1.Italic = checkItalic.Checked;
            }
            else if (sender == checkUnderline)
            {
                sampleTextControl1.Underline = checkUnderline.Checked;
            }
        }
    }
}
