using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Globalization;

using Managed.Graphics.DirectWrite;
using Managed.Graphics.Direct2D;
using Managed.Graphics.Forms;

namespace Managed.D2DSharp.DirectWrite.CustomLayout
{
    public partial class MainWindow : Direct2DWindow
    {
        private TextFormat _textFormat;
        private TextLayout _textLayout;
        private static float dpiScaleX;
        private static float dpiScaleY;
        private SolidColorBrush _blackBrush;
        private TextAnalyzer _textAnalyzer;
        private MyTextSource _source;

        static MainWindow()
        {
            DirectWriteFactory.GetDpiScale(out dpiScaleX, out dpiScaleY);
        }

        public MainWindow()
        {
            InitializeComponent();
        }

        protected override void OnCreateDeviceIndependentResources(Direct2DFactory factory)
        {
            base.OnCreateDeviceIndependentResources(factory);
            this._textFormat = DirectWriteFactory.CreateTextFormat("Gabriola", 72);
            this._textFormat.TextAlignment = TextAlignment.Center;
            this._textFormat.ParagraphAlignment = ParagraphAlignment.Center;
            float width = ClientSize.Width / dpiScaleX;
            float height = ClientSize.Height / dpiScaleY;
            this._textLayout = DirectWriteFactory.CreateTextLayout("Click on this text Click on this text", this._textFormat, width, height);
            this._textAnalyzer = DirectWriteFactory.CreateTextAnalyzer();
            this._source = new MyTextSource("Click on this text Click on this text");
            using (FontCollection coll = this._textFormat.FontCollection)
            {
                int count = coll.Count;
                for (int index = 0; index < count; ++index)
                {
                    using (FontFamily ff = coll[index])
                    {
                        using (Font font = ff.GetFirstMatchingFont(FontWeight.Normal, FontStretch.Normal, FontStyle.Normal))
                        {
                            LocalizedStrings ls = font.FaceNames;
                            LocalizedStrings desc = font.GetInformationalStrings(InformationalStringId.Designer);
                            
                            int cultureIndex = ls.FindCulture(CultureInfo.CurrentCulture);
                            string faceName = ls[cultureIndex];
                            FontMetrics metrics = font.Metrics;
                        }
                    }
                }
            }
            this._textAnalyzer.AnalyzeLineBreakpoints(_source, 0, (uint)_source.Text.Length);
            this._textAnalyzer.AnalyzeScript(_source, 0, (uint)_source.Text.Length);
        }

        protected override void OnCleanUpDeviceIndependentResources()
        {
            base.OnCleanUpDeviceIndependentResources();
            this._textAnalyzer.Dispose();
            this._textLayout.Dispose();
            this._textFormat.Dispose();
        }

        protected override void OnCreateDeviceResources(WindowRenderTarget renderTarget)
        {
            base.OnCreateDeviceResources(renderTarget);
            this._blackBrush = renderTarget.CreateSolidColorBrush(Color.FromARGB(Colors.Black, 1));
        }

        protected override void OnCleanUpDeviceResources()
        {
            base.OnCleanUpDeviceResources();
            this._blackBrush.Dispose();
        }

        protected override void OnRender(WindowRenderTarget renderTarget)
        {
            PointF origin = new PointF();
            renderTarget.DrawTextLayout(origin, this._textLayout, _blackBrush, DrawTextOptions.None);
        }

        protected override void OnResize(EventArgs e)
        {
            base.OnResize(e);
            if (this._textLayout != null)
            {
                this._textLayout.MaxWidth = ClientSize.Width / dpiScaleX;
                this._textLayout.MaxHeight = ClientSize.Height / dpiScaleY;
            }
        }
    }
}
