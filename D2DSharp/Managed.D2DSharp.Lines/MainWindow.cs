using Managed.Graphics.Direct2D;
using Managed.Graphics.Dxgi;
using System;
using System.Windows.Forms;

namespace Managed.D2DSharp.Lines
{
    public partial class MainWindow : Form
    {
        private DxgiDevice _dxgiDevice;
        private Direct2DFactory _factory;
        private DxgiSwapChain1 _swapChain;
        private DeviceContext _deviceContext;
        private DxgiSurface _surface;
        private Bitmap1 _bitmap;
        private SolidColorBrush _brush;
        private const float Velocity = 0.015f;
        private const int PointCount = 128*3;
        private const int NeighborCount = 8;
        private PointF[] _points = new PointF[PointCount];
        private PointF[] _vectors = new PointF[PointCount];
        private int[,] _neighbors = new int[PointCount, NeighborCount];

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

        protected override void OnPaint(PaintEventArgs e)
        {
            Render();
        }

        private void Render()
        {
            DeviceContext renderTarget = _deviceContext;

            renderTarget.BeginDraw();

            renderTarget.Clear(Color.FromKnown(Colors.Black, 1f));


            for (int index = 0; index < PointCount; ++index)
            {
                renderTarget.DrawEllipse(_brush, 0.5f, new Ellipse(_points[index], 2, 2));
                for(int n = 0; n < NeighborCount; ++n)
                {
                    renderTarget.DrawLine(_brush, (NeighborCount - n) / (float)(10 * NeighborCount), _points[index], _points[_neighbors[index, n]]);
                }
            }

            renderTarget.EndDraw();

            _swapChain.Present(1, 0);

            MovePoints();
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

        protected static void SafeDispose<T>(ref T d) where T : class, IDisposable
        {
            if (d != null)
            {
                d.Dispose();
                d = default(T);
            }
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
                    _brush = _deviceContext.CreateSolidColorBrush(Color.FromRGB(0.1f, 0.75f, 0.5f, 1f));
                }
            }
            CreatePoints();
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            Invalidate();
        }

        private void Reset()
        {
            CreatePoints();
            Invalidate();
        }

        private void CreatePoints()
        {
            Random random = new Random();

            for (int index = 0; index < PointCount; ++index)
            {
                float x = (float)(random.NextDouble() * ClientRectangle.Width);
                float y = (float)(random.NextDouble() * ClientRectangle.Height);
                _points[index] = new PointF(x, y);

                x = (float)(random.NextDouble() * 100) - 50f;
                y = (float)(random.NextDouble() * 100) - 50f;
                _vectors[index] = new PointF(x, y);
            }
        }
        private void MovePoints()
        {
            for (int index = 0; index < PointCount; ++index)
            {

                float x = (float)(_points[index].X + _vectors[index].X * Velocity);
                float y = (float)(_points[index].Y + _vectors[index].Y * Velocity);

                if (x < 0)
                {
                    x = -x;
                    _vectors[index] = new PointF(-_vectors[index].X, _vectors[index].Y);
                }
                else if (x > ClientRectangle.Width)
                {
                    x = ClientRectangle.Width * 2 - x;
                    _vectors[index] = new PointF(-_vectors[index].X, _vectors[index].Y);
                }

                if (y < 0)
                {
                    y = -y;
                    _vectors[index] = new PointF(_vectors[index].X, -_vectors[index].Y);
                }
                else if (y > ClientRectangle.Height)
                {
                    y = ClientRectangle.Height * 2 - y;
                    _vectors[index] = new PointF(_vectors[index].X, -_vectors[index].Y);
                }

                _points[index] = new PointF(x, y);
            }
            FindNeighbors();
        }

        private void FindNeighbors()
        {
            for (int index = 0; index < PointCount; ++index)
            {
                int[] indexes = GetOrderedIndexes(_points[index]);
                for (int n = 0; n < NeighborCount; n++)
                {
                    _neighbors[index, n] = indexes[n + 1];
                }
            }
        }

        private int[] GetOrderedIndexes(PointF point)
        {
            float[] distance = new float[PointCount];
            int[] indexes = new int[PointCount];
            for (int index = 0; index < PointCount; ++index)
            {
                float dx = point.X - _points[index].X;
                float dy = point.Y - _points[index].Y;
                distance[index] = dx * dx + dy * dy;
                indexes[index] = index;
            }
            Array.Sort(distance, indexes);
            return indexes;
        }

    }
}
