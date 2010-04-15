using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using DykBits.Graphics.Direct2D;

namespace DykBits.D2DSharp.Sample2
{
    public partial class MainWindow : Form
    {
        private Direct2DFactory _factory;
        private WindowRenderTarget _renderTarget;
        private StrokeStyle _strokeStyle;
        private Bitmap _cache;

        public MainWindow()
        {
            SetStyle(
                ControlStyles.AllPaintingInWmPaint |
                ControlStyles.Opaque |
                ControlStyles.ResizeRedraw |
                ControlStyles.UserPaint, true);
            InitializeComponent();
            this.Load += new EventHandler(MainWindow_Load);
            this.Paint += new PaintEventHandler(MainWindow_Paint);
        }

        void MainWindow_Paint(object sender, PaintEventArgs e)
        {
            this._renderTarget.BeginDraw();
            this._renderTarget.Clear(Colors.Black);
            if (this._cache != null)
            {
                this._renderTarget.DrawBitmap(this._cache, new RectF(0, 0, ClientSize.Width, ClientSize.Height),
                    1, BitmapInterpolationMode.Linear);
            }
            this._renderTarget.EndDraw();
        }

        void MainWindow_Load(object sender, EventArgs e)
        {
            this._factory = Direct2DFactory.CreateFactory(FactoryType.SingleThreaded, DebugLevel.None);
            StrokeStyleProperties ssp = new StrokeStyleProperties(LineCapStyle.Round, LineCapStyle.Round,
                LineCapStyle.Round, LineJoin.Round, 10, DashStyle.Solid, 0);
            this._strokeStyle = this._factory.CreateStrokeStyle(ssp, null);
            this._renderTarget = this._factory.CreateWindowRenderTarget(this);
            this.Resize += new EventHandler(MainWindow_Resize);
        }

        void MainWindow_Resize(object sender, EventArgs e)
        {
            if (this._renderTarget != null)
            {
                if (this._cache != null)
                {
                    this._cache.Dispose();
                    this._cache = null;
                }
                this._renderTarget.Resize(new SizeU { Width = (uint)ClientSize.Width, Height = (uint)ClientSize.Height });
                timer1_Tick(null, EventArgs.Empty);
            }
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            this.timer1.Enabled = false;
            Random rand = new Random();
            this._renderTarget.BeginDraw();
            for (int index = 0; index < 1000; ++index)
            {
                Color color = Color.FromARGB(1, (float)rand.NextDouble(), (float)rand.NextDouble(), (float)rand.NextDouble());
                using (SolidColorBrush brush = this._renderTarget.CreateSolidColorBrush(color))
                {
                    this._renderTarget.DrawLine(brush, 1, this._strokeStyle,
                        new PointF(rand.Next(0, ClientSize.Width), rand.Next(0, ClientSize.Height)),
                        new PointF(rand.Next(0, ClientSize.Width), rand.Next(0, ClientSize.Height)));
                }
            }
            this._cache = this._renderTarget.CreateBitmap(new SizeU((uint)ClientSize.Width, (uint)ClientSize.Height), IntPtr.Zero, 0, 
                new BitmapProperties(new PixelFormat(DxgiFormat.B8G8R8A8_UNORM, AlphaMode.Ignore), 96, 96));
            this._cache.CopyFromRenderTarget(new PointU(0, 0), this._renderTarget, new RectU(0, 0, (uint)ClientSize.Width, (uint)ClientSize.Height));
            this._renderTarget.EndDraw();
        }
    }
}
