/* 
* MainWindow.cs
* 
* Authors: 
*  Dmitry Kolchev <dmitrykolchev@msn.com>
*  
* Copyright (C) 2018 Dmitry Kolchev
*
* This sourcecode is licenced under The GNU Lesser General Public License
* 
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
* OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN
* NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
* DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
* OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
* USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
using System;
using System.Numerics;
using System.Windows.Forms;
using Managed.Graphics.Direct2D;
using Managed.Graphics.DirectWrite;
using Managed.Graphics.Dxgi;
using Meta.Numerics.Functions;

namespace Managed.D2DSharp.Riemann
{
    public partial class MainWindow : Form
    {
        private const float VelocityMax = 0.020f;
        private const float VelocityMin = 0.005f;
        private const int PointCount = 128 * 4;
        private const int NeighborCount = 8;

        private DxgiDevice _dxgiDevice;
        private Direct2DFactory _factory;
        private DxgiSwapChain1 _swapChain;
        private DeviceContext _deviceContext;
        private DxgiSurface _surface;
        private Bitmap1 _bitmap;
        private SolidColorBrush _brush;
        private SolidColorBrush _brush1;
        private DirectWriteFactory _directWriteFactory;

        private readonly PointF[] _points = new PointF[PointCount];
        private readonly PointF[] _vectors = new PointF[PointCount];
        private readonly float[] _velocity = new float[PointCount];
        private readonly int[,] _neighbors = new int[PointCount, NeighborCount];

        public MainWindow()
        {
            SetStyle(ControlStyles.AllPaintingInWmPaint |
                ControlStyles.Opaque |
                ControlStyles.UserPaint, true);
            Load += MainWindow_Load;
            FormClosed += MainWindow_FormClosed;
            Paint += MainWindow_Paint;
            Resize += MainWindow_Resize;
            InitializeComponent();
        }

        private void MainWindow_Resize(object sender, EventArgs e)
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
            }
        }

        private void MainWindow_Paint(object sender, PaintEventArgs e)
        {
            Render();
        }

        private void MainWindow_FormClosed(object sender, FormClosedEventArgs e)
        {
            CleanUp();
        }

        private void CleanUp()
        {
            SafeDispose(ref _bitmap);
            SafeDispose(ref _brush);
            SafeDispose(ref _brush1);
            SafeDispose(ref _deviceContext);
            SafeDispose(ref _surface);
            SafeDispose(ref _swapChain);
            SafeDispose(ref _dxgiDevice);
            SafeDispose(ref _factory);
        }

        private const double MinX = -10.0d;
        private const double MaxX = 10.0d;

        private const double MinY = -10.0d;
        private const double MaxY = 10.0d;

        private PointF TranslateToScreen(double x, double y)
        {
            float rx = (float)((x - MinX) * ClientSize.Width / (MaxX - MinX));
            float ry = (float)(ClientSize.Height - (y - MinY) * ClientSize.Height / (MaxY - MinY));
            return new PointF(rx, ry);
        }

        private void Render()
        {
            DeviceContext renderTarget = _deviceContext;

            renderTarget.BeginDraw();

            renderTarget.Clear(Color.FromKnown(Colors.Black, 1f));

            for (double re = 0.5; re <= 2; re += 0.1d)
            {
                for (double im = -2; im <= 2; im += 0.1d)
                {
                    Complex s = new Complex(re, im);
                    Complex z = AdvancedComplexMath.RiemannZeta(s);
                    PointF rs = TranslateToScreen(s.Real, s.Imaginary);
                    PointF rz = TranslateToScreen(z.Real, z.Imaginary);
                    renderTarget.DrawLine(_brush1, 1, rs, rz);
                }
            }

            renderTarget.EndDraw();

            _swapChain.Present(1, 0);
        }

        protected override void OnMouseDown(MouseEventArgs e)
        {
            base.OnMouseDown(e);
        }

        protected override void OnMouseDoubleClick(MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Left)
            {
                if (FormBorderStyle != FormBorderStyle.None)
                {
                    WindowState = FormWindowState.Normal;
                    FormBorderStyle = FormBorderStyle.None;
                    TopMost = true;
                    WindowState = FormWindowState.Maximized;
                }
                else
                {
                    WindowState = FormWindowState.Normal;
                    TopMost = false;
                    FormBorderStyle = FormBorderStyle.Sizable;
                }
            }
            base.OnMouseDoubleClick(e);
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
                d = default;
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
                    _brush1 = _deviceContext.CreateSolidColorBrush(Color.FromRGB(0.1f, 0.5f, 0.75f, 1f));
                }
            }
            _directWriteFactory = DirectWriteFactory.Create(DirectWriteFactoryType.Shared);
        }
    }
}
