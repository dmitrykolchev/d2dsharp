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
using Managed.Graphics.DirectWrite;
using System;
using System.Windows.Forms;

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
            canvas.CreateDeviceIndependentResources += canvas_CreateDeviceIndependentResources;
            canvas.CreateDeviceResources += canvas_CreateDeviceResources;
            canvas.CleanUpDeviceIndependentResources += canvas_CleanUpDeviceIndependentResources;
            canvas.CleanUpDeviceResources += canvas_CleanUpDeviceResources;
            canvas.Render += canvas_Render;
            canvas2.Render += Canvas2_Render;
            canvas2.CreateDeviceResources += Canvas2_CreateDeviceResources;
            canvas2.CleanUpDeviceResources += Canvas2_CleanUpDeviceResources;
        }

        private void Canvas2_CleanUpDeviceResources(object sender, EventArgs e)
        {
            SafeDispose(ref _ellipseBrush);
        }

        private void Canvas2_CreateDeviceResources(object sender, Graphics.Forms.RenderTargetEventArgs e)
        {
            _ellipseBrush = e.RenderTarget.CreateSolidColorBrush(Color.FromKnown(Colors.Red, 1f));
        }

        private void Canvas2_Render(object sender, Graphics.Forms.RenderTargetEventArgs e)
        {
            e.RenderTarget.FillEllipse(_ellipseBrush, new Ellipse(new PointF(canvas2.ClientSize.Width / 2, canvas2.ClientSize.Height / 2),
                canvas2.ClientSize.Width / 2,
                canvas2.ClientSize.Height / 2));
        }

        private void canvas_Render(object sender, Managed.Graphics.Forms.RenderTargetEventArgs e)
        {
            var renderTarget = e.RenderTarget;

            renderTarget.FillRect(_semiTransparentBrush, new RectF(0, 0, ClientSize.Width, ClientSize.Height));
            renderTarget.DrawText(_text, _textFormat,
                new RectF(_x, (canvas.ClientSize.Height - _textLayout.Metrics.Height) / 2, canvas.ClientSize.Width, canvas.ClientSize.Height),
                _brush,
                DrawTextOptions.None,
                MeasuringMode.Natural);
            if (_x < 0)
            {
                renderTarget.DrawText(_text, _textFormat,
                    new RectF(canvas.ClientSize.Width + _x, (canvas.ClientSize.Height - _textLayout.Metrics.Height) / 2, canvas.ClientSize.Width, canvas.ClientSize.Height),
                    _brush,
                    DrawTextOptions.None,
                    MeasuringMode.Natural);
            }
        }

        private void canvas_CleanUpDeviceResources(object sender, EventArgs e)
        {
            SafeDispose(ref _semiTransparentBrush);
            SafeDispose(ref _brush);
        }

        private void canvas_CleanUpDeviceIndependentResources(object sender, EventArgs e)
        {
            SafeDispose(ref _textLayout);
            SafeDispose(ref _textFormat);
        }

        private void canvas_CreateDeviceResources(object sender, Graphics.Forms.RenderTargetEventArgs e)
        {
            var renderTarget = e.RenderTarget;
            _brush = renderTarget.CreateSolidColorBrush(Color.FromKnown(Colors.LimeGreen, 1));
            _semiTransparentBrush = renderTarget.CreateSolidColorBrush(Color.FromKnown(Colors.Black, 0.25f));
        }

        private void canvas_CreateDeviceIndependentResources(object sender, EventArgs e)
        {
            _textFormat = canvas.DirectWriteFactory.CreateTextFormat("Gabriola", 96);
            _textLayout = canvas.DirectWriteFactory.CreateTextLayout(_text, _textFormat, float.MaxValue, float.MaxValue);
        }
        private static void SafeDispose<T>(ref T d) where T : class, IDisposable
        {
            if (d != null)
            {
                d.Dispose();
                d = default(T);
            }
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            _x -= 5;
            if (_x < 0 && Math.Abs(_x) > _textLayout.Metrics.Width)
            {
                _x += canvas.ClientSize.Width;
            }

            canvas.InvokeRender();
        }
    }
}
