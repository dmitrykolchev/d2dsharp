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
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using Managed.Graphics;
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
        }

        protected override void OnMouseMove(MouseEventArgs e)
        {
            if (Form.ModifierKeys == Keys.Control)
            {
                this.angleY = -((float)(e.X - ClientSize.Width / 2) / ClientSize.Width) * 90;
                this.angleX = ((float)(e.Y - ClientSize.Height / 2) / ClientSize.Height) * 90;
            }
            base.OnMouseMove(e);
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
            using (SolidColorBrush b = renderTarget.CreateSolidColorBrush(Color.FromKnown(Colors.Black, 0.75f)))
            {
                renderTarget.FillRect(b, new RectF(0, 0, ClientSize.Width, ClientSize.Height));
            }
            this._universe.Render(renderTarget);
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
            if (this._brush != null)
            {
                this._brush.Dispose();
                this._brush = null;
            }
        }

        float angleX;
        float angleY;
        float angleZ;
        float z;
        float delta = 10;
        Random rand = new Random();
        private void timer1_Tick(object sender, EventArgs e)
        {
            this._time += 0.003f;
            this.angleZ = (float)(this.angleZ + 0.2) % 360;
            float a = (float)(Math.Sin(this.angleZ * Math.PI / 180) * 20);
            this.z -= delta;
            if (this.z < -200000 || this.z > 10000)
                delta = -delta;
            Matrix4x4 transform = Matrix4x4.Translation(0, 0, z) * Matrix4x4.RotationX(angleX) * Matrix4x4.RotationY(angleY) * Matrix4x4.RotationZ(a);
            this._universe.Transform = transform;
            Invalidate();
        }


        private void Reset()
        {
            this._universe = new Universe();
            float halfWidth = 5500;
            float halfHeight = 5500;

            this._universe.Genrate(20000, -halfWidth, halfWidth, -halfHeight, halfHeight, 0, 200000);
            this._universe.PointOfView = -1000;
            this._universe.ViewPortSize = new SizeF(ClientSize.Width, ClientSize.Height);
            Invalidate();
        }
    }
}
