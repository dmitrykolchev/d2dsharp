/* 
* MainWindow.cs
* 
* Authors: 
*  Dmitry Kolchev <dmitrykolchev@msn.com>
*  
* Copyright (C) 2014 Dmitry Kolchev
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
using System.Windows.Forms;
using Managed.Graphics.Direct2D;

namespace Managed.D2DSharp.StarField
{
    public partial class MainWindow : Managed.Graphics.Forms.Direct2DWindow
    {
        private SolidColorBrush _brush;
        private float _time;
        private Universe _universe;

        public MainWindow()
        {
            InitializeComponent();
            Bounds = Screen.FromPoint(Form.MousePosition).Bounds;
        }

        protected override void OnMouseMove(MouseEventArgs e)
        {
            if (Form.ModifierKeys == Keys.Control)
            {
                _angleY = -((float)(e.X - ClientSize.Width / 2) / ClientSize.Width) * 90;
                _angleX = ((float)(e.Y - ClientSize.Height / 2) / ClientSize.Height) * 90;
            }
            else if (Form.ModifierKeys == Keys.Shift)
            {
                _shiftX = e.X - ClientSize.Width / 2;
                _shiftY = e.Y - ClientSize.Height / 2;
            }
            base.OnMouseMove(e);
        }

        protected override void OnMouseDown(MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Right)
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

        protected override void OnRender(WindowRenderTarget renderTarget)
        {
            using (SolidColorBrush b = renderTarget.CreateSolidColorBrush(Color.FromKnown(Colors.Black, 0.75f)))
            {
                renderTarget.FillRect(b, new RectF(0, 0, ClientSize.Width, ClientSize.Height));
            }
            _universe.Render(renderTarget);
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
            _brush = renderTarget.CreateSolidColorBrush(Color.FromKnown(Colors.Brown, 1));
        }

        protected override void OnCleanUpDeviceIndependentResources()
        {
            base.OnCleanUpDeviceIndependentResources();
        }

        protected override void OnCleanUpDeviceResources()
        {
            base.OnCleanUpDeviceResources();
            if (_brush != null)
            {
                _brush.Dispose();
                _brush = null;
            }
        }

        private float _angleX;
        private float _angleY;
        private float _angleZ;
        private float _shiftX;
        private float _shiftY;
        private float _z;
        private float _delta = 10;
        private readonly Random _rand = new Random();

        private void timer1_Tick(object sender, EventArgs e)
        {
            _time += 0.003f;
            _angleZ = (float)(_angleZ + 0.2) % 360;
            float a = (float)(Math.Sin(_angleZ * Math.PI / 180) * 20);
            _z -= _delta;
            if (_z < -200000 || _z > 10000)
            {
                _delta = -_delta;
            }
            Matrix4x4 transform = Matrix4x4.Translation(_shiftX, _shiftY, _z) * Matrix4x4.RotationX(_angleX) * Matrix4x4.RotationY(_angleY) * Matrix4x4.RotationZ(a);
            _universe.Transform = transform;
            Invalidate();
        }


        private void Reset()
        {
            _universe = new Universe();
            float halfWidth = 5500;
            float halfHeight = 5500;

            _universe.Generate(20000, -halfWidth, halfWidth, -halfHeight, halfHeight, 0, 200000);
            _universe.PointOfView = -1000;
            _universe.ViewPortSize = new SizeF(ClientSize.Width, ClientSize.Height);
            Invalidate();
        }
    }
}
