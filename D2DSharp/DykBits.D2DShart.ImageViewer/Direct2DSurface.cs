/* 
* Direct2DSurface.cs 
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
        private float _rotationAngle;
        private bool _showBorder;

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
                    this._renderTarget.Transform = Matrix3x2.Rotation(this.RotationAngle, new PointF(ClientSize.Width / 2, ClientSize.Height /2));
                    SizeU imageSize = this._image.PixelSize;
                    double scale = Math.Min((double)(ClientSize.Width - 20) / imageSize.Width, (double)(ClientSize.Height - 20) / imageSize.Height);
                    int imageWidth = (int)(imageSize.Width * scale);
                    int imageHeight = (int)(imageSize.Height * scale);
                    RectF imageBounds = new RectF((ClientSize.Width - imageWidth) / 2, (ClientSize.Height - imageHeight) / 2, imageWidth, imageHeight);
                    this._renderTarget.DrawBitmap(this._image, imageBounds, 1, BitmapInterpolationMode.Linear);
                    if(ShowBorder)
                        this._renderTarget.DrawRect(this._borderBrush, 8, imageBounds);
                }
            }
            finally
            {
                this._renderTarget.EndDraw();
            }
        }

        [Browsable(false)]
        [DesignerSerializationVisibility(DesignerSerializationVisibility.Hidden)]
        public string ImagePath
        {
            get { return this._imagePath ?? string.Empty; }
            set
            {
                value = value ?? string.Empty;
                if (this.ImagePath != value)
                {
                    this._imagePath = value;
                    this.RotationAngle = 0;
                    OnImagePathChanged(EventArgs.Empty);
                }
            }
        }

        public bool ShowBorder
        {
            get { return _showBorder; }
            set
            {
                if (this._showBorder != value)
                {
                    this._showBorder = value;
                    Invalidate();
                }
            }
        }

        [Browsable(false)]
        [DesignerSerializationVisibility(DesignerSerializationVisibility.Hidden)]
        public float RotationAngle
        {
            get { return this._rotationAngle; }
            set
            {
                if (this._rotationAngle != value)
                {
                    this._rotationAngle = value;
                    Invalidate();
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
