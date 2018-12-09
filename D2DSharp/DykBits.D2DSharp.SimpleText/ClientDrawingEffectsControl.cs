using Managed.Graphics.Direct2D;
using Managed.Graphics.DirectWrite;
using Managed.Graphics.Forms;
using System;

namespace Managed.D2DSharp.SimpleText
{
    public partial class ClientDrawingEffectsControl : Direct2DControl
    {
        private static string _text = "Hello World using   DirectWrite!";
        private static float _dpiScaleX;
        private static float _dpiScaleY;

        private TextFormat _textFormat;
        private TextLayout _textLayout;
        private SolidColorBrush _blackBrush;

        private ColorDrawingEffect _redColorDrawingEffect;
        private ColorDrawingEffect _greenColorDrawingEffect;
        private ColorDrawingEffect _blueColorDrawingEffect;

        private CustomTextRendererWithEffects _customRenderer;

        static ClientDrawingEffectsControl()
        {
            DirectWriteFactory.GetDpiScale(out _dpiScaleX, out _dpiScaleY);
        }

        public ClientDrawingEffectsControl()
        {
            InitializeComponent();
        }

        protected override void OnCreateDeviceIndependentResources(Direct2DFactory factory)
        {
            base.OnCreateDeviceIndependentResources(factory);

            _redColorDrawingEffect = new ColorDrawingEffect(Color.FromKnown(Colors.Red, 1));
            _greenColorDrawingEffect = new ColorDrawingEffect(Color.FromKnown(Colors.Green, 1));
            _blueColorDrawingEffect = new ColorDrawingEffect(Color.FromKnown(Colors.Blue, 1));

            _textFormat = DirectWriteFactory.CreateTextFormat("Gabriola", 72);

            _textFormat.TextAlignment = TextAlignment.Center;
            _textFormat.ParagraphAlignment = ParagraphAlignment.Center;

            float width = ClientSize.Width / _dpiScaleX;
            float height = ClientSize.Height / _dpiScaleY;

            _textLayout = DirectWriteFactory.CreateTextLayout(
                _text,
                _textFormat,
                width,
                height);

            _textLayout.SetFontSize(100, new TextRange(20, 6));

            _textLayout.SetDrawingEffect(_blueColorDrawingEffect, new TextRange(6, 5));
            _textLayout.SetDrawingEffect(_redColorDrawingEffect, new TextRange(20, 6));
            _textLayout.SetDrawingEffect(_greenColorDrawingEffect, new TextRange(26, 5));

            ClientDrawingEffect effect = _textLayout.GetDrawingEffect(7);

            _textLayout.SetUnderline(true, new TextRange(20, 11));
            _textLayout.SetFontWeight(FontWeight.Bold, new TextRange(20, 11));

            using (Typography typography = DirectWriteFactory.CreateTypography())
            {
                typography.AddFontFeature(FontFeatureTag.StylisticSet7, 1);
                _textLayout.SetTypography(typography, new TextRange(0, _text.Length));
            }
        }

        protected override void OnCleanUpDeviceIndependentResources()
        {
            base.OnCleanUpDeviceIndependentResources();
            _textFormat.Dispose();
            _textLayout.Dispose();
            _blueColorDrawingEffect.Dispose();
            _redColorDrawingEffect.Dispose();
            _greenColorDrawingEffect.Dispose();
        }

        protected override void OnCreateDeviceResources(WindowRenderTarget renderTarget)
        {
            base.OnCreateDeviceResources(renderTarget);

            _blackBrush = renderTarget.CreateSolidColorBrush(Color.FromKnown(Colors.Black, 1));
            _customRenderer = new CustomTextRendererWithEffects(Direct2DFactory, renderTarget, _blackBrush);
        }

        protected override void OnCleanUpDeviceResources()
        {
            base.OnCleanUpDeviceResources();
            _blackBrush.Dispose();
        }

        protected override void OnRender(WindowRenderTarget renderTarget)
        {
            PointF origin = new PointF(0, 0);
            _textLayout.Draw(_customRenderer, origin.X, origin.Y);
        }

        protected override void OnResize(EventArgs e)
        {
            base.OnResize(e);
            if (_textLayout != null)
            {
                _textLayout.MaxWidth = ClientSize.Width / _dpiScaleX;
                _textLayout.MaxHeight = ClientSize.Height / _dpiScaleY;
            }
        }
    }
}
