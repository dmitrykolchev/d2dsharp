/* 
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
using System.Windows.Forms;
using Managed.Graphics.Direct2D;
using Managed.Graphics.DirectWrite;
using Managed.Graphics.Imaging;

namespace Managed.Graphics.Forms
{
    public partial class Direct2DWindow : Form
    {
        private Direct2DFactory _factory;
        private DirectWriteFactory _directWriteFactory;
        private WicImagingFactory _imagingFactory;
        private WindowRenderTarget _renderTarget;

        public Direct2DWindow()
        {
            SetStyle(
                ControlStyles.AllPaintingInWmPaint |
                ControlStyles.Opaque |
                ControlStyles.UserPaint, true);

            InitializeComponent();
            this.Disposed += new EventHandler(Direct2DWindow_Disposed);
        }

        void Direct2DWindow_Disposed(object sender, EventArgs e)
        {
            this.Disposed -= new EventHandler(Direct2DWindow_Disposed);
            CleanUpDeviceIndependentResources();
        }

        protected Direct2DFactory Direct2DFactory
        {
            get
            {
                return this._factory;
            }
        }

        protected DirectWriteFactory DirectWriteFactory
        {
            get
            {
                if (this._directWriteFactory == null)
                {
                    this._directWriteFactory = DirectWriteFactory.Create(DirectWriteFactoryType.Shared);
                }
                return this._directWriteFactory;
            }
        }

        protected WicImagingFactory ImagingFactory
        {
            get
            {
                if (this._imagingFactory == null)
                {
                    this._imagingFactory = WicImagingFactory.Create();
                }
                return this._imagingFactory;
            }
        }

        protected WindowRenderTarget RenderTarget
        {
            get
            {
                return this._renderTarget;
            }
        }

        protected override void OnLoad(EventArgs e)
        {
            CreateDeviceIndependentResources();
            base.OnLoad(e);
        }

        private void CreateDeviceIndependentResources()
        {
            this._factory = Direct2DFactory.CreateFactory(FactoryType.SingleThreaded, DebugLevel.None);
            this._renderTarget = this._factory.CreateWindowRenderTarget(this);
            OnCreateDeviceIndependentResources(this._factory);
        }

        private void CleanUpDeviceIndependentResources()
        {
            OnCleanUpDeviceIndependentResources();
            if (this._imagingFactory != null)
            {
                this._imagingFactory.Dispose();
                this._imagingFactory = null;
            }
            if (this._directWriteFactory != null)
            {
                this._directWriteFactory.Dispose();
                this._directWriteFactory = null;
            }
            if (this._renderTarget != null)
            {
                this._renderTarget.Dispose();
                this._renderTarget = null;
            }
            if (this._factory != null)
            {
                this._factory.Dispose();
                this._factory = null;
            }
        }

        protected virtual void OnCleanUpDeviceIndependentResources()
        {
        }

        private void CleanUpDeviceResources()
        {
            OnCleanUpDeviceResources();
        }
        
        protected virtual void OnCleanUpDeviceResources()
        {
        }

        private void CreateDeviceResources()
        {
            OnCreateDeviceResources(this._renderTarget);
        }

        protected virtual void OnCreateDeviceResources(WindowRenderTarget renderTarget)
        {
        }

        protected virtual void OnCreateDeviceIndependentResources(Direct2DFactory factory)
        {
        }

        protected override void OnPaint(PaintEventArgs e)
        {
            CreateDeviceResources();
            try
            {
                this._renderTarget.BeginDraw();
                try
                {
                    this._renderTarget.Transform = Matrix3x2.Identity;
                    this._renderTarget.Clear(Color.FromRGB(this.BackColor.R, this.BackColor.G, this.BackColor.B));
                    OnRender(RenderTarget);
                }
                finally
                {
                    this._renderTarget.EndDraw();
                }
            }
            finally
            {
                CleanUpDeviceResources();
            }
        }

        protected virtual void OnRender(WindowRenderTarget renderTarget)
        {
        }

        protected override void OnResize(EventArgs e)
        {
            base.OnResize(e);
            if (this.RenderTarget != null)
            {
                this.RenderTarget.Resize(new SizeU { Width = (uint)ClientSize.Width, Height = (uint)ClientSize.Height });
                Invalidate();
            }
        }
    }
}
