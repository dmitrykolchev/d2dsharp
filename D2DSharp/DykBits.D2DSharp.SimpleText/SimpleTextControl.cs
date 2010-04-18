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
            this._textFormat = DirectWriteFactory.CreateTextFormat("Magneto",
                null,
                FontWeight.Normal,
                FontStyle.Normal,
                FontStretch.Normal,
                72,
                "ru-ru");
            this._textFormat.TextAlignment = TextAlignment.Center;
            this._textFormat.ParagraphAlignment = ParagraphAlignment.Center;

            System.Globalization.CultureInfo ci = this._textFormat.Culture;
            Trimming trimming = this._textFormat.Trimming;
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
