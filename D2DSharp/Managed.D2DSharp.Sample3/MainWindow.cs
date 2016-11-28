using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
//using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using Managed.Graphics;
using Managed.Graphics.Direct2D;
using Managed.Graphics.DirectWrite;

namespace Managed.D2DSharp.Sample3
{
    public partial class MainWindow : Form
    {
        private SolidColorBrush _brush;
        private SolidColorBrush _semiTransparentBrush;
        private float _x = 0;
        private TextFormat _textFormat;
        private TextLayout _textLayout;
        private string _text = "Hello World!";

        private SolidColorBrush _ellipseBrush;

        public MainWindow()
        {
            InitializeComponent();
            this.canvas.CreateDeviceIndependentResources += canvas_CreateDeviceIndependentResources;
            this.canvas.CreateDeviceResources += canvas_CreateDeviceResources;
            this.canvas.CleanUpDeviceIndependentResources += canvas_CleanUpDeviceIndependentResources;
            this.canvas.CleanUpDeviceResources += canvas_CleanUpDeviceResources;
            this.canvas.Render += canvas_Render;
            this.canvas2.Render += Canvas2_Render;
            this.canvas2.CreateDeviceResources += Canvas2_CreateDeviceResources;
            this.canvas2.CleanUpDeviceResources += Canvas2_CleanUpDeviceResources;
        }

        private void Canvas2_CleanUpDeviceResources(object sender, EventArgs e)
        {
            SafeDispose(ref this._ellipseBrush);
        }

        private void Canvas2_CreateDeviceResources(object sender, Graphics.Forms.RenderTargetEventArgs e)
        {
            this._ellipseBrush = e.RenderTarget.CreateSolidColorBrush(Color.FromKnown(Colors.Red, 1f));
        }

        private void Canvas2_Render(object sender, Graphics.Forms.RenderTargetEventArgs e)
        {
            e.RenderTarget.FillEllipse(this._ellipseBrush, new Ellipse(new PointF(canvas2.ClientSize.Width / 2, canvas2.ClientSize.Height / 2),
                canvas2.ClientSize.Width / 2,
                canvas2.ClientSize.Height / 2));
        }

        private void canvas_Render(object sender, Managed.Graphics.Forms.RenderTargetEventArgs e)
        {
            var renderTarget = e.RenderTarget;

            renderTarget.FillRect(this._semiTransparentBrush, new RectF(0, 0, ClientSize.Width, ClientSize.Height));
            renderTarget.DrawText(this._text, this._textFormat,
                new RectF(_x, (canvas.ClientSize.Height - this._textLayout.Metrics.Height) / 2, canvas.ClientSize.Width, canvas.ClientSize.Height),
                _brush,
                DrawTextOptions.None,
                MeasuringMode.Natural);
            if (this._x < 0)
            {
                renderTarget.DrawText(this._text, this._textFormat,
                    new RectF(canvas.ClientSize.Width + _x, (canvas.ClientSize.Height - this._textLayout.Metrics.Height) / 2, canvas.ClientSize.Width, canvas.ClientSize.Height),
                    _brush,
                    DrawTextOptions.None,
                    MeasuringMode.Natural);
            }
        }

        private void canvas_CleanUpDeviceResources(object sender, EventArgs e)
        {
            SafeDispose(ref this._semiTransparentBrush);
            SafeDispose(ref this._brush);
        }

        private void canvas_CleanUpDeviceIndependentResources(object sender, EventArgs e)
        {
            SafeDispose(ref this._textLayout);
            SafeDispose(ref this._textFormat);
        }

        private void canvas_CreateDeviceResources(object sender, Graphics.Forms.RenderTargetEventArgs e)
        {
            var renderTarget = e.RenderTarget;
            this._brush = renderTarget.CreateSolidColorBrush(Color.FromKnown(Colors.LimeGreen, 1));
            this._semiTransparentBrush = renderTarget.CreateSolidColorBrush(Color.FromKnown(Colors.Black, 0.25f));
        }

        private void canvas_CreateDeviceIndependentResources(object sender, EventArgs e)
        {
            this._textFormat = canvas.DirectWriteFactory.CreateTextFormat("Gabriola", 96);
            this._textLayout = canvas.DirectWriteFactory.CreateTextLayout(this._text, this._textFormat, float.MaxValue, float.MaxValue);
        }
        private static void SafeDispose<T>(ref T d) where T : class, IDisposable
        {
            if (d != null)
            {
                ((IDisposable)d).Dispose();
                d = default(T);
            }
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            this._x -= 5;
            if (this._x < 0 && Math.Abs(this._x) > this._textLayout.Metrics.Width)
                this._x += canvas.ClientSize.Width;
            canvas.InvokeRender();
        }
    }
}
