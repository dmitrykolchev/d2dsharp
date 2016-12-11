using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
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
            InitializeComponent();
        }

        protected override void CreateHandle()
        {
            base.CreateHandle();
            try
            {
                _factory = Direct2DFactory.CreateFactory(FactoryType.SingleThreaded, DebugLevel.Information);
                DxgiDevice dxgiDevice = DxgiDevice.CreateDevice();
                Device device = _factory.CreateDevice(dxgiDevice);

                _deviceContext = device.CreateDeviceContext(DeviceContextOptions.None);

                DxgiAdapter adapter = dxgiDevice.Adapter;
                DxgiFactory factory = adapter.Factory;
                _swapChain = factory.CreateSwapChainForHwnd(dxgiDevice, this.Handle);
                dxgiDevice.MaximumFrameLatency = 1;

                _swapChain.GetBuffer(0, out _surface);
                _bitmap = _deviceContext.CreateBitmapFromDxgiSurface(_surface);
                _deviceContext.SetTarget(_bitmap);
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.ToString());
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
            using (SolidColorBrush brush = _deviceContext.CreateSolidColorBrush(Graphics.Direct2D.Color.FromKnown(Colors.Red, 1)))
            {
                _deviceContext.BeginDraw();
                _deviceContext.DrawRect(brush, 1, new RectF(10, 10, ClientSize.Width - 20, ClientSize.Height - 20));
                _deviceContext.EndDraw();
            }
            _swapChain.Present(1, 0);
            base.OnPaint(e);
        }
    }
}
