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
    public partial class SimpleTextControl : Direct2DControl
    {
        private TextFormat _textFormat;
        private SolidColorBrush _blackBrush;

        public SimpleTextControl()
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
                "");
            this._textFormat.TextAlignment = TextAlignment.Center;
            this._textFormat.ParagraphAlignment = ParagraphAlignment.Center;
        }

        protected override void OnCleanUpDeviceIndependentResources()
        {
            base.OnCleanUpDeviceIndependentResources();
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
            string text = "Hello World using  DirectWrite!";
            renderTarget.DrawText(text, this._textFormat,
                new RectF(0, 0, ClientSize.Width, ClientSize.Height),
                _blackBrush,
                DrawTextOptions.None, MeasuringMode.Natural);
        }
    }
}
