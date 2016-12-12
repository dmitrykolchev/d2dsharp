using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using Managed.Graphics.Direct2D;
using Managed.Graphics.Dxgi;
using Managed.Graphics.D3D11;

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
        public MainWindow()
        {
            SetStyle(ControlStyles.AllPaintingInWmPaint |
                ControlStyles.Opaque | 
                ControlStyles.UserPaint, true);
            this.Load += MainWindow_Load;
            this.FormClosed += MainWindow_FormClosed;
            InitializeComponent();
        }

        private void MainWindow_FormClosed(object sender, FormClosedEventArgs e)
        {
            CleanUp();
        }

        private void CleanUp()
        {
            SafeDispose(ref _bitmap);
            SafeDispose(ref _deviceContext);
            SafeDispose(ref _surface);
            SafeDispose(ref _swapChain);
            SafeDispose(ref _dxgiDevice);
            SafeDispose(ref _factory);
        }

        private void MainWindow_Load(object sender, EventArgs e)
        {
            if (_dxgiDevice != null)
            {
                CleanUp();
            }

            _dxgiDevice = DxgiDevice.CreateDevice();
            _factory = Direct2DFactory.CreateFactory(FactoryType.SingleThreaded, DebugLevel.Information);
            using (Device device = _factory.CreateDevice(_dxgiDevice))
            {
                _deviceContext = device.CreateDeviceContext(DeviceContextOptions.None);

                using (DxgiAdapter adapter = _dxgiDevice.Adapter)
                using (DxgiFactory factory = adapter.Factory)
                {
                    _swapChain = factory.CreateSwapChainForHwnd(_dxgiDevice, this.Handle);
                    _dxgiDevice.MaximumFrameLatency = 1;
                    _swapChain.GetBuffer(0, out _surface);
                    _bitmap = _deviceContext.CreateBitmapFromDxgiSurface(_surface);
                    _deviceContext.SetTarget(_bitmap);
                }
            }
        }
        protected override void OnResize(EventArgs e)
        {
            if (_deviceContext != null)
            {
                _deviceContext.SetTarget(null);
                _bitmap.Dispose();
                _surface.Dispose();

                _swapChain.ResizeBuffers();

                _swapChain.GetBuffer(0, out _surface);
                _bitmap = _deviceContext.CreateBitmapFromDxgiSurface(_surface);
                _deviceContext.SetTarget(_bitmap);
                Invalidate();
            }
        }
        protected override void OnPaint(PaintEventArgs e)
        {
            Render();
        }

        void Render()
        {
            using (SolidColorBrush brush = _deviceContext.CreateSolidColorBrush(Color.FromKnown(Colors.Red, 1)))
            {
                _deviceContext.BeginDraw();
                _deviceContext.Clear(Color.FromKnown(Colors.Black, 1));
                _deviceContext.DrawRect(brush, 1, new RectF(10.5f, 10.5f, ClientSize.Width - 20, ClientSize.Height - 20));
                _deviceContext.EndDraw();
            }
            _swapChain.Present(1, 0);
        }
        protected static void SafeDispose<T>(ref T d) where T : class, IDisposable
        {
            if (d != null)
            {
                ((IDisposable)d).Dispose();
                d = default(T);
            }
        }
    }
}
