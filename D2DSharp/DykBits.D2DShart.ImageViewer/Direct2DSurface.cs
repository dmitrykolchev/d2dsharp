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

namespace DykBits.D2DShart.ImageViewer
{
    public partial class Direct2DSurface : Control
    {
        private Direct2DFactory _factory;
        private WicImagingFactory _imagingFactory;
        private WindowRenderTarget _renderTarget;
        private Bitmap _image;
        private SolidColorBrush _borderBrush;
        private string _imagePath;

        public Direct2DSurface()
        {
            SetStyle(
                ControlStyles.AllPaintingInWmPaint |
                ControlStyles.Opaque |
                ControlStyles.ResizeRedraw |
                ControlStyles.UserPaint, true);
            InitializeComponent();
            this.Disposed += new EventHandler(Direct2DSurface_Disposed);
        }

        void Direct2DSurface_Disposed(object sender, EventArgs e)
        {
            // 
            // CleanUp
            if (this._borderBrush != null)
                this._borderBrush.Dispose();

            if (this._image != null)
                this._image.Dispose();

            if (this._imagingFactory != null)
                this._imagingFactory.Dispose();
            if (this._factory != null)
                this._factory.Dispose();
            if (this._renderTarget != null)
                this._renderTarget.Dispose();
        }

        protected override void OnHandleCreated(EventArgs e)
        {
            base.OnHandleCreated(e);
            this._factory = Direct2DFactory.CreateFactory(FactoryType.SingleThreaded, DebugLevel.None);
            this._renderTarget = this._factory.CreateWindowRenderTarget(this, PresentOptions.None, RenderTargetProperties.Default);
            this._imagingFactory = WicImagingFactory.Create();
            this._borderBrush = this._renderTarget.CreateSolidColorBrush(Colors.White);
            this.Paint += new PaintEventHandler(Direct2DSurface_Paint);
            this.Resize += new EventHandler(Direct2DSurface_Resize);
        }

        void Direct2DSurface_Resize(object sender, EventArgs e)
        {
            this._renderTarget.Resize(new SizeU { Width = (uint)ClientSize.Width, Height = (uint)ClientSize.Height });
        }

        protected override void OnPaintBackground(PaintEventArgs pevent)
        {

        }

        void Direct2DSurface_Paint(object sender, PaintEventArgs e)
        {
            this._renderTarget.BeginDraw();
            try
            {
                this._renderTarget.Clear(Colors.Black);
                if (this._image != null)
                {
                    SizeU imageSize = this._image.PixelSize;
                    double scale = Math.Min((double)(ClientSize.Width - 20) / imageSize.Width, (double)(ClientSize.Height - 20) / imageSize.Height);
                    int imageWidth = (int)(imageSize.Width * scale);
                    int imageHeight = (int)(imageSize.Height * scale);
                    RectF imageBounds = new RectF((ClientSize.Width - imageWidth) / 2, (ClientSize.Height - imageHeight) / 2, imageWidth, imageHeight);
                    this._renderTarget.DrawBitmap(this._image, imageBounds, 1, BitmapInterpolationMode.Linear);
                    this._renderTarget.DrawRect(this._borderBrush, 8, imageBounds);
                }
            }
            finally
            {
                this._renderTarget.EndDraw();
            }
        }

        public string ImagePath
        {
            get { return this._imagePath ?? string.Empty; }
            set
            {
                value = value ?? string.Empty;
                if (this.ImagePath != value)
                {
                    this._imagePath = value;
                    OnImagePathChanged(EventArgs.Empty);
                }
            }
        }

        private void OnImagePathChanged(EventArgs e)
        {
            using (WicBitmapDecoder decoder = this._imagingFactory.CreateDecoderFromFilename(ImagePath, Guid.Empty, System.IO.FileAccess.Read, DecodeOptions.MetadataCacheOnDemand))
            {
                using (WicBitmapFrameDecode frame = decoder.GetFrame(0))
                {
                    using (WicFormatConverter converter = this._imagingFactory.CreateFormatConverter())
                    {
                        converter.Convert(frame, WicPixelFormats.PixelFormat32bppPBGRA, BitmapDitherType.None, null, 0, BitmapPaletteType.Custom);
                        Bitmap bitmap = _renderTarget.CreateBitmap(converter, new BitmapProperties());
                        if (this._image != null)
                            this._image.Dispose();
                        this._image = bitmap;
                        Invalidate();
                    }
                }
            }
        }
    }
}
