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

namespace Managed.D2DSharp.Marquee
{
    public partial class MainWindow : Managed.Graphics.Forms.Direct2DWindow
    {
        private SolidColorBrush _brush;
        private SolidColorBrush _semiTransparentBrush;
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

        private float _x = 0;
        private TextFormat _textFormat;
        private TextLayout _textLayout;
        private string _text = "Hello World using  DirectWrite!";

        protected override void OnRender(WindowRenderTarget renderTarget)
        {
            //renderTarget.Clear(Color.FromARGB(Colors.Black, 1));
            renderTarget.FillRect(this._semiTransparentBrush, new RectF(0, 0, ClientSize.Width, ClientSize.Height));
            renderTarget.DrawText(this._text, this._textFormat,
                new RectF(_x, (ClientSize.Height - this._textLayout.Metrics.Height) / 2, ClientSize.Width, ClientSize.Height), 
                _brush, 
                DrawTextOptions.None, 
                MeasuringMode.Natural);
            if (this._x < 0)
            {
                renderTarget.DrawText(this._text, this._textFormat,
                    new RectF(ClientSize.Width + _x, (ClientSize.Height - this._textLayout.Metrics.Height) / 2, ClientSize.Width, ClientSize.Height),
                    _brush,
                    DrawTextOptions.None,
                    MeasuringMode.Natural);
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
            this._textFormat = DirectWriteFactory.CreateTextFormat("Arial", 96);
            this._textLayout = DirectWriteFactory.CreateTextLayout(this._text, this._textFormat, float.MaxValue, float.MaxValue);
           
        }
        protected override void OnCreateDeviceResources(WindowRenderTarget renderTarget)
        {
            base.OnCreateDeviceResources(renderTarget);
            this._brush = renderTarget.CreateSolidColorBrush(Managed.Graphics.Direct2D.Color.FromARGB(Managed.Graphics.Direct2D.Colors.LimeGreen, 1));
            this._semiTransparentBrush = renderTarget.CreateSolidColorBrush(Color.FromARGB(Colors.Black, 0.25f));
        }
        protected override void OnCleanUpDeviceIndependentResources()
        {
            base.OnCleanUpDeviceIndependentResources();
            SafeDispose(ref this._textLayout);
            SafeDispose(ref this._textFormat);
        }
        protected override void OnCleanUpDeviceResources()
        {
            base.OnCleanUpDeviceResources();
            SafeDispose(ref this._semiTransparentBrush);
            SafeDispose(ref this._brush);
        }
        Random rand = new Random();
        private void timer1_Tick(object sender, EventArgs e)
        {
            this._x -= 5;
            if (this._x < 0 && Math.Abs(this._x) > this._textLayout.Metrics.Width)
                this._x += ClientSize.Width;
            Invalidate();
        }

        private void Reset()
        {
            Invalidate();
        }
    }
}
