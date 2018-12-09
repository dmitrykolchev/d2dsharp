using Managed.Graphics.Direct2D;
using Managed.Graphics.DirectWrite;
using Managed.Graphics.Forms;
using System;
using System.Globalization;

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
            _textFormat = DirectWriteFactory.CreateTextFormat("Gabriola", 72);
            _textFormat.TextAlignment = TextAlignment.Center;
            _textFormat.ParagraphAlignment = ParagraphAlignment.Center;
            float width = ClientSize.Width / dpiScaleX;
            float height = ClientSize.Height / dpiScaleY;
            _textLayout = DirectWriteFactory.CreateTextLayout("Click on this text Click on this text", _textFormat, width, height);
            _textAnalyzer = DirectWriteFactory.CreateTextAnalyzer();
            _source = new MyTextSource("Click on this text Click on this text");
            using (FontCollection coll = _textFormat.FontCollection)
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
                            if (cultureIndex >= 0)
                            {
                                string faceName = ls[cultureIndex];
                                FontMetrics metrics = font.Metrics;
                            }
                        }
                    }
                }
            }
            _textAnalyzer.AnalyzeLineBreakpoints(_source, 0, (uint)_source.Text.Length);
            _textAnalyzer.AnalyzeScript(_source, 0, (uint)_source.Text.Length);
        }

        protected override void OnCleanUpDeviceIndependentResources()
        {
            base.OnCleanUpDeviceIndependentResources();
            _textAnalyzer.Dispose();
            _textLayout.Dispose();
            _textFormat.Dispose();
        }

        protected override void OnCreateDeviceResources(WindowRenderTarget renderTarget)
        {
            base.OnCreateDeviceResources(renderTarget);
            _blackBrush = renderTarget.CreateSolidColorBrush(Color.FromKnown(Colors.Black, 1));
        }

        protected override void OnCleanUpDeviceResources()
        {
            base.OnCleanUpDeviceResources();
            _blackBrush.Dispose();
        }

        protected override void OnRender(WindowRenderTarget renderTarget)
        {
            PointF origin = new PointF();
            renderTarget.DrawTextLayout(origin, _textLayout, _blackBrush, DrawTextOptions.None);
        }

        protected override void OnResize(EventArgs e)
        {
            base.OnResize(e);
            if (_textLayout != null)
            {
                _textLayout.MaxWidth = ClientSize.Width / dpiScaleX;
                _textLayout.MaxHeight = ClientSize.Height / dpiScaleY;
            }
        }
    }
}
