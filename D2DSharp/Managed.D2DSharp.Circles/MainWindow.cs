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
using Managed.Graphics.Direct2D;
using Managed.Graphics.DirectWrite;
using Managed.Graphics.Dxgi;
using System;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Managed.D2DSharp.Circles
{
    public partial class MainWindow : Form
    {
        private const float Velocity = 0.015f;
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

        private SolidColorBrush[] _brushes = new SolidColorBrush[1000];
        private SolidColorBrush[] _pens = new SolidColorBrush[1000];
        private Random _random = new Random(1000);

        public MainWindow()
        {
            SetStyle(ControlStyles.AllPaintingInWmPaint | ControlStyles.ResizeRedraw |
                ControlStyles.Opaque |
                ControlStyles.UserPaint, true);
            Load += MainWindow_Load;
            FormClosed += MainWindow_FormClosed;
            Paint += MainWindow_Paint;
            Resize += MainWindow_Resize;
            InitializeComponent();
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
                for(int index = 0; index < _brushes.Length; ++index)
                {
                    _pens[index] = _deviceContext.CreateSolidColorBrush(GetRandomColor(_random, 1));
                    _brushes[index] = _deviceContext.CreateSolidColorBrush(GetRandomColor(_random, 0.25f));
                }
            }
            _directWriteFactory = DirectWriteFactory.Create(DirectWriteFactoryType.Shared);
        }


        private static Color GetRandomColor(Random random, float alpha)
        {
            return Color.FromRGB((float)random.NextDouble(), (float)random.NextDouble(), (float)random.NextDouble(), alpha);
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

        private void Render()
        {
            DeviceContext renderTarget = _deviceContext;

            renderTarget.BeginDraw();

            renderTarget.Clear(Color.FromKnown(Colors.Black, 1f));

            _random = new Random(19292);
            for (int index = 0; index < _brushes.Length; ++index)
            {
                float x = _random.Next(0, (int)ClientRectangle.Width);
                float y = _random.Next(0, (int)ClientRectangle.Height);
                Ellipse ellipse = new Ellipse(x, y, 50, 50);
                renderTarget.FillEllipse(_brushes[index], ellipse);
                renderTarget.DrawEllipse(_pens[index], 1, ellipse);
            }

            string text = "Press <Esc> to exit...";
            using (TextFormat textFormat = _directWriteFactory.CreateTextFormat("Segoe UI", 13, FontWeight.Normal))
            using (TextLayout textLayout = _directWriteFactory.CreateTextLayout(text, textFormat, float.MaxValue, float.MaxValue))
            using (SolidColorBrush textBrush = renderTarget.CreateSolidColorBrush(Color.FromKnown(Colors.White, 1)))
            {
                renderTarget.DrawText(
                    text,
                    textFormat,
                    new RectF(10, 10, ClientRectangle.Width, ClientRectangle.Height),
                    textBrush,
                    DrawTextOptions.None,
                    MeasuringMode.Natural
                    );
            }

            renderTarget.EndDraw();

            _swapChain.Present(1, 0);
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
                d = default(T);
            }
        }
    }
}
