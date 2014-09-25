using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;

using Managed.Graphics.Direct2D;
using Managed.Graphics.DirectWrite;
using Managed.Graphics.Imaging;
using Managed.Graphics.Forms;


namespace Managed.D2DSharp.SimpleText
{
    public partial class CustomTextControl : Direct2DControl
    {
        private static string _text = "Hello World using   DirectWrite!";
        private static float _dpiScaleX;
        private static float _dpiScaleY;

        private TextFormat _textFormat;
        private TextLayout _textLayout;
        private SolidColorBrush _blackBrush;
        private BitmapBrush _bitmapBrush;
        private CustomTextRenderer _customRenderer;

        static CustomTextControl()
        {
            DirectWriteFactory.GetDpiScale(out _dpiScaleX, out _dpiScaleY);
        }

        public CustomTextControl()
        {
            InitializeComponent();
        }

        protected override void OnCreateDeviceIndependentResources(Direct2DFactory factory)
        {
            base.OnCreateDeviceIndependentResources(factory);

            this._textFormat = DirectWriteFactory.CreateTextFormat("Gabriola",
                FontWeight.Normal,
                FontStyle.Normal,
                FontStretch.Normal,
                72);

            this._textFormat.TextAlignment = TextAlignment.Center;
            this._textFormat.ParagraphAlignment = ParagraphAlignment.Center;

            float width = ClientSize.Width / _dpiScaleX;
            float height = ClientSize.Height / _dpiScaleY;

            this._textLayout = DirectWriteFactory.CreateTextLayout(
                _text,
                this._textFormat,
                width,
                height);

            this._textLayout.SetFontSize(100, new TextRange(20, 6));
            this._textLayout.SetUnderline(true, new TextRange(20, 11));
            this._textLayout.SetFontWeight(FontWeight.Bold, new TextRange(20, 11));

            using (Typography typography = DirectWriteFactory.CreateTypography())
            {
                typography.AddFontFeature(FontFeatureTag.StylisticSet7, 1);
                this._textLayout.SetTypography(typography, new TextRange(0, _text.Length));
            }

        }

        protected override void OnCleanUpDeviceIndependentResources()
        {
            base.OnCleanUpDeviceIndependentResources();
            this._textLayout.Dispose();
            this._textLayout.Dispose();
        }

        protected override void OnCreateDeviceResources(WindowRenderTarget renderTarget)
        {
            base.OnCreateDeviceResources(renderTarget);
            this._blackBrush = renderTarget.CreateSolidColorBrush(Color.FromKnown(Colors.Black, 1));
            using (Bitmap bitmap = renderTarget.CreateBitmap(this.GetType(), "flowers.jpg"))
            {
                this._bitmapBrush = renderTarget.CreateBitmapBrush(bitmap, new BitmapBrushProperties(ExtendMode.Wrap, ExtendMode.Wrap, BitmapInterpolationMode.NearestNeighbor), BrushProperties.Default);
            }
            _customRenderer = new CustomTextRenderer(this.Direct2DFactory, renderTarget, this._blackBrush, this._bitmapBrush);
        }

        protected override void OnCleanUpDeviceResources()
        {
            base.OnCleanUpDeviceResources();
            this._blackBrush.Dispose();
            this._bitmapBrush.Dispose();
        }

        protected override void OnRender(WindowRenderTarget renderTarget)
        {
            PointF origin = new PointF(0, 0);
            this._textLayout.Draw(this._customRenderer, origin.X, origin.Y);
        }

        protected override void OnResize(EventArgs e)
        {
            base.OnResize(e);
            if (this._textLayout != null)
            {
                this._textLayout.MaxWidth = ClientSize.Width / _dpiScaleX;
                this._textLayout.MaxHeight = ClientSize.Height / _dpiScaleY;
            }
        }

    }
}
