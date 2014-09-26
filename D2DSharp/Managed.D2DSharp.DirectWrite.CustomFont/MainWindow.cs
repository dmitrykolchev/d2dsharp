using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;

using Managed.Graphics.Direct2D;
using Managed.Graphics.DirectWrite;
using Managed.Graphics.Forms;

namespace Managed.D2DSharp.DirectWrite.CustomFont
{
    public partial class MainWindow : Direct2DWindow
    {
        private static float DpiScaleX;
        private static float DpiScaleY;
        private SolidColorBrush _blackBrush;

        private float _marginLeft = 20;
        private float _marginRight = 20;
        private List<TextParagraph> _paragraphs = new List<TextParagraph> 
        {
            new TextParagraph 
            { 
                FontFamily="Cambria", 
                Text = "DirectWrite Custom Font Loader Sample", 
                FontSize = 15, 
                Weight = FontWeight.Bold, 
                SpaceBefore = 16, 
                SpaceAfter = 10, 
                TextAlignment = TextAlignment.Center 
            },
            new TextParagraph 
            { 
                FontFamily="Colibri", 
                Text = "The text in this application is rendered using fonts that are embedded as resources. The fonts are sample fonts supplied under license from Ascender Corporation. The heading is rendered in Pericles and the body text in Kootenay. For more information, search for “Sample OpenType Font Pack” on MSDN.", 
                FontSize = 10f, 
                Weight = FontWeight.Normal, 
                SpaceBefore = 10, 
                SpaceAfter = 10,
                TextAlignment = TextAlignment.Leading,
                LineSpacing = 22
            },
            new TextParagraph 
            { 
                FontFamily="Colibri", 
                Text = "The application implements a custom font file loader to provide access to the embedded font data. This enables DirectWrite to access the fonts even though they do not exist as discrete files.", 
                FontSize = 10f, 
                Weight = FontWeight.Normal, 
                SpaceBefore = 10, 
                SpaceAfter = 10,
                TextAlignment = TextAlignment.Leading,
                LineSpacing = 22
            },
            new TextParagraph 
            { 
                FontFamily="Colibri", 
                Text = "The application also implements a custom font collection loader. This enables DirectWrite to recognize the family names \"Pericles\" and \"Kootenay\" even though these fonts are not installed on the system - i.e., not part of the system font collection.", 
                FontSize = 10f, 
                Weight = FontWeight.Normal, 
                SpaceBefore = 10, 
                SpaceAfter = 10,
                TextAlignment = TextAlignment.Leading,
                LineSpacing = 22
            }
        };
        static MainWindow()
        {
            DirectWriteFactory.GetDpiScale(out DpiScaleX, out DpiScaleY);
        }

        public MainWindow()
        {
            InitializeComponent();
            this.ClientSize = new System.Drawing.Size((int)(DpiScaleX * 7 * 96), (int)(DpiScaleY * 3f * 96));
        }

        protected override void OnCreateDeviceResources(WindowRenderTarget renderTarget)
        {
            base.OnCreateDeviceResources(renderTarget);
            this._blackBrush = renderTarget.CreateSolidColorBrush(Color.FromKnown(Colors.Black, 1));
        }

        protected override void OnCleanUpDeviceResources()
        {
            base.OnCleanUpDeviceResources();
            this._blackBrush.Dispose();
        }

        protected override void OnRender(WindowRenderTarget renderTarget)
        {
            float y = 0;

            for (int index = 0; index < this._paragraphs.Count; ++index)
            {
                using (TextFormat textFormat = DirectWriteFactory.CreateTextFormat(
                    this._paragraphs[index].FontFamily,
                    this._paragraphs[index].FontSize * 96f / 72f,
                    this._paragraphs[index].Weight))
                {

                    textFormat.TextAlignment = _paragraphs[index].TextAlignment;
                    LineSpacing lineSpacing = textFormat.LineSpacing;
                    
                    if (_paragraphs[index].LineSpacing == 0)
                        textFormat.LineSpacing = LineSpacing.Default;
                    else
                        textFormat.LineSpacing = new LineSpacing(_paragraphs[index].LineSpacing);

                    float width = ClientSize.Width / DpiScaleX - (_marginLeft + _marginRight);

                    using (TextLayout textLayout = DirectWriteFactory.CreateTextLayout(
                        this._paragraphs[index].Text,
                        textFormat,
                        width,
                        0))
                    {

                        y += _paragraphs[index].SpaceBefore;

                        renderTarget.DrawTextLayout(
                            new PointF(_marginLeft, y),
                            textLayout,
                            _blackBrush,
                            DrawTextOptions.None);

                        TextMetrics metrics = textLayout.Metrics;

                        y += metrics.Height + _paragraphs[index].SpaceAfter;
                    }
                }
            }
        }
    }
}
