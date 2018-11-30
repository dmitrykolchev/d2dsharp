/* 
* MainWindow.cs 
* 
* Authors: 
*  Dmitry Kolchev <dmitrykolchev@msn.com>
*  
* Copyright (C) 2010 Dmitry Kolchev
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
using System;
using System.Windows.Forms;

namespace Managed.D2DSharp.Sample2
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
            Load += new EventHandler(MainWindow_Load);
            Paint += new PaintEventHandler(MainWindow_Paint);
        }

        private void MainWindow_Paint(object sender, PaintEventArgs e)
        {
            _renderTarget.BeginDraw();
            _renderTarget.Clear(Color.FromKnown(Colors.Black, 1));
            if (_cache != null)
            {
                _renderTarget.DrawBitmap(_cache, new RectF(0, 0, ClientSize.Width, ClientSize.Height),
                    1, BitmapInterpolationMode.Linear);
            }
            _renderTarget.EndDraw();
        }

        private void MainWindow_Load(object sender, EventArgs e)
        {
            _factory = Direct2DFactory.CreateFactory(FactoryType.SingleThreaded, DebugLevel.None);
            StrokeStyleProperties ssp = new StrokeStyleProperties(LineCapStyle.Round, LineCapStyle.Round,
                LineCapStyle.Round, LineJoin.Round, 10, DashStyle.Solid, 0);
            _strokeStyle = _factory.CreateStrokeStyle(ssp, null);
            _renderTarget = _factory.CreateWindowRenderTarget(this);
            Resize += new EventHandler(MainWindow_Resize);
        }

        private void MainWindow_Resize(object sender, EventArgs e)
        {
            if (_renderTarget != null)
            {
                _renderTarget.Resize(new SizeU((uint)ClientSize.Width, (uint)ClientSize.Height));
            }
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            timer1.Enabled = false;
            Random rand = new Random();
            _renderTarget.BeginDraw();
            for (int index = 0; index < 20; ++index)
            {
                Color color = Color.FromRGB((float)rand.NextDouble(), (float)rand.NextDouble(), (float)rand.NextDouble());
                using (SolidColorBrush brush = _renderTarget.CreateSolidColorBrush(color))
                {
                    float strokeWidth = rand.Next(1, 5);
                    float patch = strokeWidth / 2 - (int)(strokeWidth / 2);
                    _renderTarget.DrawRect(brush, strokeWidth, _strokeStyle,
                        new RectF(
                        new PointF(rand.Next(0, ClientSize.Width) + patch, rand.Next(0, ClientSize.Height) + patch),
                        new PointF(rand.Next(0, ClientSize.Width) + patch, rand.Next(0, ClientSize.Height) + patch)));
                }
            }
            _cache = _renderTarget.CreateBitmap(new SizeU((uint)ClientSize.Width, (uint)ClientSize.Height), IntPtr.Zero, 0,
                new BitmapProperties(new PixelFormat(DxgiFormat.B8G8R8A8_UNORM, AlphaMode.Ignore), 96, 96));
            _cache.CopyFromRenderTarget(new PointU(0, 0), _renderTarget, new RectU(0, 0, (uint)ClientSize.Width, (uint)ClientSize.Height));
            _renderTarget.EndDraw();
        }
    }
}
