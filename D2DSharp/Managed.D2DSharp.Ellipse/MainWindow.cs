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
using Managed.Graphics.DirectWrite;

namespace Managed.D2DSharp.Ellipse
{
    public partial class MainWindow : Managed.Graphics.Forms.Direct2DWindow
    {
        public MainWindow()
        {
            InitializeComponent();
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
            renderTarget.Clear(Color.FromKnown(Colors.Black, 1));
            using (EllipseGeometry geometry = Direct2DFactory.CreateEllipseGeometry(new Graphics.Direct2D.Ellipse(ClientSize.Width / 2, ClientSize.Height / 2, ClientSize.Width / 2 - 25, ClientSize.Height / 2 - 25)))
            {
                using (SolidColorBrush brush = renderTarget.CreateSolidColorBrush(Color.FromKnown(Colors.Red, 1)))
                {
                    renderTarget.DrawGeometry(brush, 50, geometry);
                }
            }
        }
        protected override void OnResize(EventArgs e)
        {
            base.OnResize(e);
            Invalidate();
        }
        protected override void OnCreateDeviceIndependentResources(Direct2DFactory factory)
        {
            base.OnCreateDeviceIndependentResources(factory);

        }
        protected override void OnCreateDeviceResources(WindowRenderTarget renderTarget)
        {
            base.OnCreateDeviceResources(renderTarget);
        }
        protected override void OnCleanUpDeviceIndependentResources()
        {
            base.OnCleanUpDeviceIndependentResources();
        }
        protected override void OnCleanUpDeviceResources()
        {
            base.OnCleanUpDeviceResources();
        }
        private void timer1_Tick(object sender, EventArgs e)
        {
            Invalidate();
        }
    }
}
