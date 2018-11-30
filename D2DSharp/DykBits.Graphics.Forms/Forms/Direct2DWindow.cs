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
using Managed.Graphics.Direct2D;
using Managed.Graphics.DirectWrite;
using Managed.Graphics.Imaging;
using System;
using System.ComponentModel;
using System.Windows.Forms;

namespace Managed.Graphics.Forms
{
    public partial class Direct2DWindow : Form
    {
        private Direct2DFactory _factory;
        private DirectWriteFactory _directWriteFactory;
        private WicImagingFactory _imagingFactory;
        private WindowRenderTarget _renderTarget;
        private bool _clearBackground = true;
        public Direct2DWindow()
        {
            SetStyle(ControlStyles.AllPaintingInWmPaint |
                ControlStyles.Opaque |
                ControlStyles.UserPaint, true);
            CreateDeviceIndependentResources();
            InitializeComponent();
            Disposed += Direct2DWindow_Disposed;
        }

        private void Direct2DWindow_Disposed(object sender, EventArgs e)
        {
            CleanUpDeviceResources();
            CleanUpDeviceIndependentResources();
        }

        protected Direct2DFactory Direct2DFactory
        {
            get
            {
                return _factory;
            }
        }

        protected DirectWriteFactory DirectWriteFactory
        {
            get
            {
                if (_directWriteFactory == null)
                {
                    _directWriteFactory = DirectWriteFactory.Create(DirectWriteFactoryType.Shared);
                }
                return _directWriteFactory;
            }
        }

        protected WicImagingFactory ImagingFactory
        {
            get
            {
                if (_imagingFactory == null)
                {
                    _imagingFactory = WicImagingFactory.Create();
                }
                return _imagingFactory;
            }
        }

        [DefaultValue(true)]
        public bool ClearBackground
        {
            get { return _clearBackground; }
            set
            {
                if (_clearBackground != value)
                {
                    _clearBackground = value;
                    Invalidate();
                }
            }
        }

        protected WindowRenderTarget RenderTarget
        {
            get
            {
                return _renderTarget;
            }
        }
        private void CreateDeviceIndependentResources()
        {
            _factory = Direct2DFactory.CreateFactory(FactoryType.SingleThreaded, DebugLevel.None);
            OnCreateDeviceIndependentResources(_factory);
        }
        private void CleanUpDeviceIndependentResources()
        {
            OnCleanUpDeviceIndependentResources();
            SafeDispose(ref _imagingFactory);
            SafeDispose(ref _directWriteFactory);
            SafeDispose(ref _factory);
        }

        protected virtual void OnCleanUpDeviceIndependentResources()
        {
        }

        private void CleanUpDeviceResources()
        {
            if (_renderTarget != null)
            {
                OnCleanUpDeviceResources();
                SafeDispose(ref _renderTarget);
            }
        }

        protected virtual void OnCleanUpDeviceResources()
        {
        }

        private void CreateDeviceResources()
        {
            if (_factory != null)
            {
                if (_renderTarget == null)
                {
                    _renderTarget = _factory.CreateWindowRenderTarget(this);
                    OnCreateDeviceResources(_renderTarget);
                }
            }
        }

        protected virtual void OnCreateDeviceResources(WindowRenderTarget renderTarget)
        {
        }

        protected virtual void OnCreateDeviceIndependentResources(Direct2DFactory factory)
        {
        }

        protected sealed override void OnPaint(PaintEventArgs e)
        {
            CreateDeviceResources();
            if (_renderTarget != null)
            {
                RenderInternal(_renderTarget);
            }
        }
        private void RenderInternal(WindowRenderTarget renderTarget)
        {
            renderTarget.BeginDraw();
            try
            {
                renderTarget.Transform = Matrix3x2.Identity;
                if (ClearBackground)
                {
                    _renderTarget.Clear(Color.FromRGB(BackColor.R, BackColor.G, BackColor.B));
                }

                OnRender(renderTarget);
            }
            finally
            {
                if (!renderTarget.EndDraw())
                {
                    CleanUpDeviceResources();
                }
            }
        }

        public void Render()
        {
            OnPaint(null);
        }

        protected virtual void OnRender(WindowRenderTarget renderTarget)
        {
        }

        protected static void SafeDispose<T>(ref T d) where T : class, IDisposable
        {
            if (d != null)
            {
                d.Dispose();
                d = default(T);
            }
        }

        protected override void OnResize(EventArgs e)
        {
            base.OnResize(e);
            if (RenderTarget != null)
            {
                RenderTarget.Resize(new SizeU((uint)ClientSize.Width, (uint)ClientSize.Height));
                Invalidate();
            }
        }
    }
}
