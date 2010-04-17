using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;

using DykBits.Graphics.Direct2D;
using DykBits.Graphics.DirectWrite;
using DykBits.Graphics.Imaging;
using DykBits.Graphics.Forms;

namespace DykBits.D2DSharp.SimpleText
{
    public partial class MultiformattedTextControl : Direct2DControl
    {
        private TextFormat _textFormat;
        private TextLayout _textLayout;
        private SolidColorBrush _blackBrush;
        private float _dpiScaleX;
        private float _dpiScaleY;

        public MultiformattedTextControl()
        {
            InitializeComponent();
        }

        protected override void OnCreateDeviceIndependentResources(Direct2DFactory factory)
        {
            base.OnCreateDeviceIndependentResources(factory);
            this._textFormat = DirectWriteFactory.CreateTextFormat("Georgia",
                null,
                FontWeight.Normal,
                FontStyle.Normal,
                FontStretch.Normal,
                72,
                "en-us");
            
            this._textFormat.TextAlignment = TextAlignment.Center;
            this._textFormat.ParagraphAlignment = ParagraphAlignment.Center;

            
            DirectWriteFactory.GetDpiScale(out _dpiScaleX, out _dpiScaleY);
            
            float width = ClientSize.Width / _dpiScaleX;
            float height = ClientSize.Height / _dpiScaleY;

            this._textLayout = DirectWriteFactory.CreateTextLayout(
                "Hello World using   DirectWrite!",
                this._textFormat,
                width,
                height);

            this._textLayout.SetFontSize(100, new TextRange(20, 6));
            this._textLayout.SetUnderline(true, new TextRange(20, 11));
            this._textLayout.SetFontWeight(FontWeight.Bold, new TextRange(20, 11));
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

        protected override void OnCleanUpDeviceIndependentResources()
        {
            base.OnCleanUpDeviceIndependentResources();
            this._textLayout.Dispose();
            this._textLayout.Dispose();
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
            PointF origin = new PointF(0, 0);
            renderTarget.DrawTextLayout(origin, this._textLayout, _blackBrush, DrawTextOptions.None);
        }


    }
}
