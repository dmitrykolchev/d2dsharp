using Managed.D2DSharp.Bezier;
using Managed.Graphics;
using Managed.Graphics.Direct2D;
using Managed.Graphics.Dxgi;
using System;
using System.Collections.Generic;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Managed.D2DSharp.DCSample
{
    public partial class MainWindow : Form
    {
        private DxgiDevice _dxgiDevice;
        private Direct2DFactory _factory;
        private DxgiSwapChain1 _swapChain;
        private DeviceContext _deviceContext;
        private DxgiSurface _surface;
        private Bitmap1 _bitmap;

        private float _time;
        private float _baseHue;
        private SolidColorBrush _brush;

        public MainWindow()
        {
            SetStyle(ControlStyles.AllPaintingInWmPaint |
                ControlStyles.Opaque |
                ControlStyles.UserPaint, true);
            Load += MainWindow_Load;
            FormClosed += MainWindow_FormClosed;
            InitializeComponent();
        }

        private void MainWindow_FormClosed(object sender, FormClosedEventArgs e)
        {
            CleanUp();
        }

        private void CleanUp()
        {
            SafeDispose(ref _bitmap);
            SafeDispose(ref _brush);
            SafeDispose(ref _deviceContext);
            SafeDispose(ref _surface);
            SafeDispose(ref _swapChain);
            SafeDispose(ref _dxgiDevice);
            SafeDispose(ref _factory);
        }

        private ControlPointArray _points;
        public ControlPointArray Points
        {
            get
            {
                if (_points == null)
                {
                    _points = ControlPointArray.Generate(60, 0, ClientSize.Width, 0, ClientSize.Height);
                }

                return _points;
            }
        }
        protected override void OnMouseDown(MouseEventArgs e)
        {
            if (e.Button == System.Windows.Forms.MouseButtons.Right)
            {
                timer1.Enabled = !timer1.Enabled;
            }
            else
            {
                Close();
            }

            base.OnMouseDown(e);
        }

        protected override void OnKeyDown(KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Escape)
            {
                e.Handled = true;
                Close();
            }
            base.OnKeyDown(e);
        }

        private Task<List<Tuple<Geometry, Color>>> _task;
        private void Render()
        {
            DeviceContext renderTarget = _deviceContext;

            renderTarget.BeginDraw();

            List<Tuple<Geometry, Color>> copy = _task == null
                ? new List<Tuple<Geometry, Color>>()
                : _task.Result;

            _task = CreateGeometries(_time);

            if (_time == 0.1f)
            {
                renderTarget.Clear(Color.FromKnown(Colors.Black, 1f));
            }

            renderTarget.FillRect(_brush, new RectF(0, 0, ClientSize.Width, ClientSize.Height));
            for (int index = 0; index < copy.Count; ++index)
            {
                Tuple<Geometry, Color> tuple = copy[index];
                using (Geometry geometry = tuple.Item1)
                {
                    using (SolidColorBrush brush = renderTarget.CreateSolidColorBrush(tuple.Item2.AdjustContrast(1.5f)))
                    {
                        renderTarget.DrawGeometry(brush, 0.1f, geometry);
                    }
                }
            }
            renderTarget.EndDraw();
            _swapChain.Present(1, 0);
            _time += 0.002f;
        }

        private Task<List<Tuple<Geometry, Color>>> CreateGeometries(float time)
        {
            return Task.Run(() =>
            {
                ControlPointArray temp = Points;
                int count = Points.Count;
                List<Tuple<Geometry, Color>> geometries = new List<Tuple<Geometry, Color>>();
                for (int index = 0; index < count - 1; ++index)
                {
                    float hue = (_baseHue + (index + 1) / (float)(count + 1)) % 1;
                    Vector4 hsv = new Vector4(hue, 1.0f, 1f, 1);
                    Color rgba = XMath.ColorHsvToRgb(hsv);
                    ControlPointArray array = temp.Reduce(time);
                    geometries.Add(new Tuple<Geometry, Color>(array.CreateGeometry(_factory), rgba));
                    temp = array;
                }
                return geometries;
            });
        }

        private void MainWindow_Load(object sender, EventArgs e)
        {
            if (_dxgiDevice != null)
            {
                CleanUp();
            }
            _dxgiDevice = DxgiDevice.CreateDevice();
            _factory = Direct2DFactory.CreateFactory(FactoryType.SingleThreaded, DebugLevel.None);
            using (Device device = _factory.CreateDevice(_dxgiDevice))
            {
                _deviceContext = device.CreateDeviceContext(DeviceContextOptions.None);
                using (DxgiAdapter adapter = _dxgiDevice.GetAdapter())
                using (DxgiFactory factory = adapter.GetFactory())
                {
                    _swapChain = factory.CreateSwapChainForHwnd(_dxgiDevice, Handle);
                    _dxgiDevice.MaximumFrameLatency = 1;
                    _swapChain.GetBuffer(0, out _surface);
                    _bitmap = _deviceContext.CreateBitmapFromDxgiSurface(_surface);
                    _deviceContext.SetTarget(_bitmap);
                    _brush = _deviceContext.CreateSolidColorBrush(Color.FromKnown(Colors.Black, 0.4f));
                }
            }
            uint value = _deviceContext.MaximumBitmapSize;
        }

        protected override void OnResize(EventArgs e)
        {
            if (_deviceContext != null)
            {
                _deviceContext.SetTarget(null);
                SafeDispose(ref _bitmap);
                SafeDispose(ref _surface);

                _swapChain.ResizeBuffers();

                _swapChain.GetBuffer(0, out _surface);
                _bitmap = _deviceContext.CreateBitmapFromDxgiSurface(_surface);
                _deviceContext.SetTarget(_bitmap);
                Reset();
            }
        }

        protected override void OnPaint(PaintEventArgs e)
        {
            Render();
        }

        protected static void SafeDispose<T>(ref T d) where T : class, IDisposable
        {
            if (d != null)
            {
                d.Dispose();
                d = default(T);
            }
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            if (_time > 0.9f)
            {
                Reset();
            }
            Invalidate();
        }

        private void Reset()
        {
            _time = 0.1f;
            _points = null;
            Random random = new Random((int)DateTime.Now.TimeOfDay.Ticks);
            _baseHue = (float)random.NextDouble();
            Invalidate();
        }
    }
}
