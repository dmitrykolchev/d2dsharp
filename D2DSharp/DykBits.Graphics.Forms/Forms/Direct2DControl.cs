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
    public partial class Direct2DControl : Control
    {
        private Direct2DFactory _factory;
        private DirectWriteFactory _directWriteFactory;
        private WicImagingFactory _imagingFactory;
        private WindowRenderTarget _renderTarget;
        private bool _clearBackground = true;
        private bool _resourcesCreated;

        public Direct2DControl()
        {
            SetStyle(
                ControlStyles.AllPaintingInWmPaint |
                ControlStyles.Opaque |
                ControlStyles.UserPaint, true);
            InitializeComponent();
            this.Disposed += new EventHandler(Direct2DControl_Disposed);
        }

        void Direct2DControl_Disposed(object sender, EventArgs e)
        {
            this.Disposed -= new EventHandler(Direct2DControl_Disposed);
            CleanUpDeviceResourcesInternal();
            CleanUpDeviceIndependentResourcesInternal();
        }

        public Direct2DFactory Direct2DFactory
        {
            get
            {
                return this._factory;
            }
        }

        public DirectWriteFactory DirectWriteFactory
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

        public WicImagingFactory ImagingFactory
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

        [DefaultValue(true)]
        public bool ClearBackground
        {
            get { return this._clearBackground; }
            set
            {
                if (this._clearBackground != value)
                {
                    this._clearBackground = value;
                    Invalidate();
                }
            }
        }

        protected WindowRenderTarget RenderTarget
        {
            get
            {
                return this._renderTarget;
            }
        }
        private void CreateDeviceIndependentResourcesInternal()
        {
            this._factory = Direct2DFactory.CreateFactory(FactoryType.SingleThreaded, DebugLevel.None);
            OnCreateDeviceIndependentResources(this._factory);
        }
        private void CleanUpDeviceIndependentResourcesInternal()
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
            if (this._factory != null)
            {
                this._factory.Dispose();
                this._factory = null;
            }
            _resourcesCreated = false;
        }

        protected virtual void OnCleanUpDeviceIndependentResources()
        {
            if (CleanUpDeviceIndependentResources != null)
                CleanUpDeviceIndependentResources(this, EventArgs.Empty);
        }

        public event EventHandler CleanUpDeviceIndependentResources;

        private void CleanUpDeviceResourcesInternal()
        {
            if (this._renderTarget != null)
            {
                OnCleanUpDeviceResources();
                this._renderTarget.Dispose();
                this._renderTarget = null;
            }
        }

        protected virtual void OnCleanUpDeviceResources()
        {
            if (CleanUpDeviceResources != null)
                CleanUpDeviceResources(this, EventArgs.Empty);
        }

        public event EventHandler CleanUpDeviceResources;

        private void CreateDeviceResourcesInternal()
        {
            if (this._renderTarget == null)
            {
                this._renderTarget = this._factory.CreateWindowRenderTarget(this);
                OnCreateDeviceResources(this._renderTarget);
            }
        }

        protected virtual void OnCreateDeviceResources(WindowRenderTarget renderTarget)
        {
            if (CreateDeviceResources != null)
                CreateDeviceResources(this, new RenderTargetEventArgs(renderTarget));
        }

        public event EventHandler<RenderTargetEventArgs> CreateDeviceResources;

        protected virtual void OnCreateDeviceIndependentResources(Direct2DFactory factory)
        {
            if (CreateDeviceIndependentResources != null)
                CreateDeviceIndependentResources(this, EventArgs.Empty);
        }
        public event EventHandler CreateDeviceIndependentResources;

        protected override void OnPaint(PaintEventArgs e)
        {
            if (!_resourcesCreated)
            {
                CreateDeviceIndependentResourcesInternal();
                _resourcesCreated = true;
            }
            CreateDeviceResourcesInternal();
            RenderInternal(this._renderTarget);
        }

        private void RenderInternal(WindowRenderTarget renderTarget)
        {
            renderTarget.BeginDraw();
            try
            {
                renderTarget.Transform = Matrix3x2.Identity;
                if (this.ClearBackground)
                    this._renderTarget.Clear(Color.FromRGB(this.BackColor.R, this.BackColor.G, this.BackColor.B));
                OnRender(renderTarget);
            }
            finally
            {
                if (!renderTarget.EndDraw())
                    CleanUpDeviceResourcesInternal();
            }
        }

        public void InvokeRender()
        {
            OnPaint(null);
        }

        protected virtual void OnRender(WindowRenderTarget renderTarget)
        {
            if (Render != null)
                Render(this, new RenderTargetEventArgs(renderTarget));
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

        public event EventHandler<RenderTargetEventArgs> Render;
    }
}
