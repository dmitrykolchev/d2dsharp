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
using Managed.Graphics;
using Managed.Graphics.Direct2D;
using System;
using System.Collections.Generic;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Managed.D2DSharp.Bezier
{
    public partial class MainWindow : Managed.Graphics.Forms.Direct2DWindow
    {
        private float _time;
        private float _baseHue;
        private SolidColorBrush _brush;
        public MainWindow()
        {
            InitializeComponent();
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

        private List<Tuple<Geometry, Color>> _geometries = new List<Tuple<Geometry, Color>>();
        private Task _task;

        protected override void OnRender(WindowRenderTarget renderTarget)
        {
            if (_task != null)
            {
                _task.Wait();
                _task.Dispose();
            }
            List<Tuple<Geometry, Color>> copy = _geometries;
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
            copy.Clear();
            _time += 0.002f;
        }

        private Task CreateGeometries(float time)
        {
            Task task = new Task(() =>
            {
                var temp = Points;
                int count = Points.Count;
                _geometries = new List<Tuple<Geometry, Color>>();
                for (int index = 0; index < count - 1; ++index)
                {
                    float hue = (_baseHue + (index + 1) / (float)(count + 1)) % 1;
                    Vector4 hsv = new Vector4(hue, 1.0f, 1f, 1);
                    Color rgba = XMath.ColorHsvToRgb(hsv);
                    var array = temp.Reduce(time);
                    _geometries.Add(new Tuple<Geometry, Color>(array.CreateGeometry(Direct2DFactory), rgba));
                    temp = array;
                }
            });
            task.Start();
            return task;
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
            _brush = RenderTarget.CreateSolidColorBrush(Color.FromKnown(Colors.Black, 0.4f));
        }
        protected override void OnCleanUpDeviceIndependentResources()
        {
            base.OnCleanUpDeviceIndependentResources();
        }
        protected override void OnCleanUpDeviceResources()
        {
            base.OnCleanUpDeviceResources();
            SafeDispose(ref _brush);
        }
        private void timer1_Tick(object sender, EventArgs e)
        {
            if (_time > 0.9f)
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
            _time = 0.1f;
            _points = null;
            Random random = new Random();
            _baseHue = (float)random.NextDouble();
            Invalidate();
        }
    }
}
