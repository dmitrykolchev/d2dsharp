using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using Managed.Graphics.DirectWrite;
using Managed.Graphics.Direct2D;
using Managed.Graphics.Forms;

namespace Managed.D2DSharp.DirectWrite.HitTesting
{
    public partial class MainWindow : Direct2DWindow
    {
        private TextFormat _textFormat;
        private TextLayout _textLayout;
        private static float dpiScaleX;
        private static float dpiScaleY;
        private SolidColorBrush _blackBrush;

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
            this._textLayout = DirectWriteFactory.CreateTextLayout("Click on this text", this._textFormat, width, height);
        }

        protected override void OnCleanUpDeviceIndependentResources()
        {
            base.OnCleanUpDeviceIndependentResources();
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

        protected override void OnMouseClick(MouseEventArgs e)
        {
            base.OnMouseClick(e);
            bool isTrailingHit;
            bool isInside;
            HitTestMetrics hitTestMetrics = this._textLayout.HitTestPoint(e.X, e.Y, out isTrailingHit, out isInside);
            if (isInside)
            {
                bool underline = _textLayout.GetUnderline((int)hitTestMetrics.TextPosition);

                _textLayout.SetUnderline(!underline, new TextRange((int)hitTestMetrics.TextPosition, 1));

                Render();
            }
        }
    }
}
