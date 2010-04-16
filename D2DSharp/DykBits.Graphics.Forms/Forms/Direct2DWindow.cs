using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using DykBits.Graphics.Direct2D;
using DykBits.Graphics.DirectWrite;
using DykBits.Graphics.Imaging;

namespace DykBits.Graphics.Forms
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
                ControlStyles.ResizeRedraw |
                ControlStyles.UserPaint, true);

            InitializeComponent();
            this.Disposed += new EventHandler(Direct2DWindow_Disposed);
        }

        void Direct2DWindow_Disposed(object sender, EventArgs e)
        {
            CleanUpResources();
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
            CreateDeviceResources();
            base.OnLoad(e);
        }

        private void CreateDeviceIndependentResources()
        {
            this._factory = Direct2DFactory.CreateFactory(FactoryType.SingleThreaded, DebugLevel.None);
            OnCreateDeviceIndependentResources(this._factory);
        }

        private void CleanUpResources()
        {
            OnCleanUpDeviceResources();
            if (this._renderTarget != null)
            {
                this._renderTarget.Dispose();
                this._renderTarget = null;
            }
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
        }

        protected virtual void OnCleanUpDeviceResources()
        {
        }

        protected virtual void OnCleanUpDeviceIndependentResources()
        {
        }

        private void CreateDeviceResources()
        {
            this._renderTarget = this._factory.CreateWindowRenderTarget(this);
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

        protected virtual void OnRender(WindowRenderTarget renderTarget)
        {
        }

        protected override void OnResize(EventArgs e)
        {
            base.OnResize(e);
            if (this.RenderTarget != null)
            {
                this.RenderTarget.Resize(new SizeU { Width = (uint)ClientSize.Width, Height = (uint)ClientSize.Height });
            }
        }
    }
}
