using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using Managed.Graphics.Direct2D;

namespace Managed.D2DSharp.Bezier
{
    public partial class MainWindow : Managed.Graphics.Forms.Direct2DWindow
    {
        private SolidColorBrush _brush;
        private ControlPointArray _points;
        private StrangeAttractor _attractor = new StrangeAttractor();
        private float _time;
        private float _baseHue;
        public MainWindow()
        {
            InitializeComponent();
        }

        public ControlPointArray Points
        {
            get
            {
                if (this._points == null)
                    this._points = ControlPointArray.Generate(65, -200, ClientSize.Width + 200, -200, ClientSize.Height + 200);
                return this._points;
            }
        }

        protected override void OnMouseDown(MouseEventArgs e)
        {
            base.OnMouseDown(e);
            this.Close();
        }

        protected override void OnKeyDown(KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Escape)
            {
                e.Handled = true;
                this.Close();
            }
            base.OnKeyDown(e);
        }

        protected override void OnRender(WindowRenderTarget renderTarget)
        {
            if (this._time == 0.1f)
                renderTarget.Clear(Color.FromARGB(Colors.Black, 1f));
            using (SolidColorBrush b = renderTarget.CreateSolidColorBrush(Color.FromARGB(Colors.Black, 0.25f)))
            {
                renderTarget.FillRect(b, new RectF(0, 0, ClientSize.Width, ClientSize.Height));
            }

            ControlPointArray temp = Points;
            int count = Points.Count;

            for (int index = 0; index < count - 1; ++index)
            {
                ControlPointArray array = temp.Reduce(this._time);
                using (Geometry geometry = array.CreateGeometry(this.Direct2DFactory))
                {
                    float hue = (this._baseHue + (float)(index + 1) / (float)(count + 1)) % 1;
                    Managed.DirectXMath.Vector4 hsla = new DirectXMath.Vector4(hue, 1.0f, 0.5f, 1);
                    Managed.DirectXMath.Vector4 rgba = Managed.DirectXMath.XMath.ColorHslToRgb(hsla);
                    using (SolidColorBrush brush = renderTarget.CreateSolidColorBrush((Color)rgba))
                    {
                        renderTarget.DrawGeometry(brush, 0.1f, geometry);
                    }
                }
                temp = array;
            }
        }

        protected override void OnResize(EventArgs e)
        {
            base.OnResize(e);
            Reset();
        }

        protected override void OnCreateDeviceIndependentResources(Direct2DFactory factory)
        {
            base.OnCreateDeviceIndependentResources(factory);
        }

        protected override void OnCreateDeviceResources(WindowRenderTarget renderTarget)
        {
            base.OnCreateDeviceResources(renderTarget);
            this._brush = renderTarget.CreateSolidColorBrush(Managed.Graphics.Direct2D.Color.FromARGB(Managed.Graphics.Direct2D.Colors.Brown, 1));
        }

        protected override void OnCleanUpDeviceIndependentResources()
        {
            base.OnCleanUpDeviceIndependentResources();
        }

        protected override void OnCleanUpDeviceResources()
        {
            base.OnCleanUpDeviceResources();
            if (this._brush != null)
            {
                this._brush.Dispose();
                this._brush = null;
            }
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            this._time += 0.005f;
            if (this._time > 0.9f)
            {
                Reset();
            }
            else
            {
                Invalidate();
            }
        }

        private void Reset()
        {
            this._time = 0.1f;
            this._points = null;
            Random random = new Random();
            this._baseHue = (float)random.NextDouble();
            Invalidate();
        }
    }
}
