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
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using Managed.Graphics;
using Managed.Graphics.Direct2D;

namespace Managed.D2DSharp.Bezier
{
    public partial class MainWindow : Managed.Graphics.Forms.Direct2DWindow
    {
        private SolidColorBrush _brush;
        private StrangeAttractor _attractor = new StrangeAttractor();
        private float _time;
        private float _baseHue;
        private Vector4 _pointOfView;
        public MainWindow()
        {
            InitializeComponent();
            this._pointOfView = new Vector4(960, 540, -10, 0);
        }

        private ControlPointArray _points;
        public ControlPointArray Points
        {
            get
            {
                if (this._points == null)
                {
                    this._points = ControlPointArray.Generate(65, 0, ClientSize.Width, 0, ClientSize.Height);
                }
                return this._points;
            }
        }
        protected override void OnMouseDown(MouseEventArgs e)
        {
            if (e.Button == System.Windows.Forms.MouseButtons.Right)
                this.timer1.Enabled = !this.timer1.Enabled;
            else
                this.Close();
            base.OnMouseDown(e);
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
                renderTarget.Clear(Color.FromKnown(Colors.Black, 1f));
            using (SolidColorBrush b = renderTarget.CreateSolidColorBrush(Color.FromKnown(Colors.Black, 0.2f)))
            {
                renderTarget.FillRect(b, new RectF(0, 0, ClientSize.Width, ClientSize.Height));
            }

            var temp = Points;
            int count = Points.Count;

            for (int index = 0; index < count - 1; ++index)
            {
                var array = temp.Reduce(this._time);
                using (Geometry geometry = array.CreateGeometry(this.Direct2DFactory))
                {
                    float hue = (this._baseHue + (float)(index + 1) / (float)(count + 1)) % 1;
                    Vector4 hsv = new Vector4(hue, 1.0f, 1f, 1);
                    Vector4 rgba = XMath.ColorHsvToRgb(hsv);
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
            this._brush = renderTarget.CreateSolidColorBrush(Color.FromKnown(Colors.Brown, 1));
        }
        protected override void OnCleanUpDeviceIndependentResources()
        {
            base.OnCleanUpDeviceIndependentResources();
        }
        protected override void OnCleanUpDeviceResources()
        {
            base.OnCleanUpDeviceResources();
            SafeDispose(ref this._brush);
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            this._time += 0.003f;
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
