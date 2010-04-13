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

namespace D2DWrapper.Sample
{
    public partial class MainWindow : Form
    {
        private Direct2DFactory _factory;
        private WindowRenderTarget _renderTarget;
        private SolidColorBrush _brush;
        private SolidColorBrush _strokeBrush;
        private StrokeStyle _strokeStyle;
        private TextFormat _textFormat;
        private Bitmap _photo;

        public MainWindow()
        {
            SetStyle(
                ControlStyles.AllPaintingInWmPaint | 
                ControlStyles.Opaque | 
                ControlStyles.ResizeRedraw | 
                ControlStyles.UserPaint, true);
            InitializeComponent();
            this.Load += new EventHandler(MainWindow_Load);
            this.Paint += new PaintEventHandler(MainWindow_Paint);
        }

        void MainWindow_Resize(object sender, EventArgs e)
        {
            if(IsHandleCreated)
                this._renderTarget.Resize(new SizeU { Width = (uint)ClientSize.Width, Height = (uint)ClientSize.Height });
        }

        SolidColorBrush RectBrush
        {
            get
            {
                if (this._brush == null)
                {

                    this._brush = _renderTarget.CreateSolidColorBrush(Colors.Red, BrushProperties.Default);
                    this._brush.Opacity = 1f;
                }
                return this._brush;
            }
        }

        int _angle = 0;

        void MainWindow_Paint(object sender, PaintEventArgs e)
        {
            this._renderTarget.BeginDraw();
            this._renderTarget.Clear(Colors.Blue);

            this._renderTarget.DrawBitmap(this._photo, new RectF(0, 0, ClientSize.Width, ClientSize.Height), 1, BitmapInterpolationMode.Linear);

            //this._renderTarget.PushAxisAlignedClip(new RectF(80, 80, ClientSize.Width - 160, ClientSize.Height - 160), AntialiasMode.PerPrimitive);
            //this._renderTarget.AntialiasMode = AntialiasMode.PerPrimitive;

            PointF center = new PointF(ClientSize.Width / 2, ClientSize.Height / 2);
            this._renderTarget.Transform = Matrix3x2.Rotation(_angle, center);

            //RoundedRect rr = new RoundedRect(new RectF(30, 30, ClientSize.Width - 60, ClientSize.Height - 60), ClientSize.Width / 2.5f, ClientSize.Height / 2.5f);
            //this._renderTarget.FillRoundedRect(RectBrush, rr);
            //this._renderTarget.DrawRoundedRect(_strokeBrush, 5, _strokeStyle, rr);

            //Ellipse ellipse = new Ellipse(ClientSize.Width / 2, ClientSize.Height / 2, ClientSize.Width / 4, ClientSize.Height / 4);
            //using (EllipseGeometry eg = this._factory.CreateEllipseGeometry(ellipse))
            //{
            //    using (Brush b = CreateEllipseBrush(ellipse))
            //    {
            //        this._renderTarget.FillGeometry(b, eg);
            //        this._renderTarget.DrawGeometry(_strokeBrush, 5, _strokeStyle, eg);
            //    }
            //}
            //RectF textBounds = new RectF(0, 0, ClientSize.Width, ClientSize.Height);
            
            //this._renderTarget.DrawText("Hello, world!", _textFormat, textBounds, _strokeBrush, DrawTextOptions.None, MeasuringMode.Natural);

            //this._renderTarget.DrawLine(_strokeBrush, 5, _strokeStyle, new PointF(0, 0), new PointF(ClientSize.Width, ClientSize.Height));
            
            //this._renderTarget.PopAxisAlignedClip();
            this._renderTarget.EndDraw();
        }

        private Brush CreateEllipseBrush(Ellipse ellipse)
        {
            RectF bounds = ellipse.Bounds;

            RadialGradientBrushProperties properties = new RadialGradientBrushProperties(bounds.Center, 
                new PointF(), 
                ellipse.RadiusX, 
                ellipse.RadiusY);
            using (GradientStopCollection collection = _renderTarget.CreateGradientStopCollection(new GradientStop[] { 
                        new GradientStop(0, Colors.Blue), 
                        new GradientStop(0.5f, Colors.Green), 
                        new GradientStop(1, Colors.Blue)
                    }))
            {
                Brush brush = _renderTarget.CreateRadialGradientBrush(properties, BrushProperties.Default, collection);
                brush.Transform = Matrix3x2.Rotation(_angle, bounds.Center);
                return brush;
            }
        }

        void MainWindow_Load(object sender, EventArgs e)
        {
            DirectWriteFactory f = DirectWriteFactory.Create(DirectWriteFactoryType.Shared);
            _textFormat = f.CreateTextFormat("Verdana", null, FontWeight.Normal, FontStyle.Normal, FontStretch.Normal, 110, null);
            _textFormat.ParagraphAlignment = ParagraphAlignment.Far;
            _textFormat.TextAlignment = TextAlignment.Center;

            //this.ClientSize = new System.Drawing.Size(600, 600);
            this._factory = Direct2DFactory.CreateFactory(FactoryType.SingleThreaded, DebugLevel.None);

            this._renderTarget = this._factory.CreateWindowRenderTarget(this, PresentOptions.None, RenderTargetProperties.Default);
            AntialiasMode amode = this._renderTarget.AntialiasMode;
            TextAntialiasMode tamode = this._renderTarget.TextAntialiasMode;
            this._strokeBrush = this._renderTarget.CreateSolidColorBrush(Colors.Cyan);
            this._strokeStyle = this._factory.CreateStrokeStyle(new StrokeStyleProperties(LineCapStyle.Flat,
                LineCapStyle.Flat, LineCapStyle.Round, LineJoin.Miter, 10, DashStyle.Dot, 0), null);


            using (WicImagingFactory wif = WicImagingFactory.Create())
            {
                using (WicBitmapDecoder decoder = wif.CreateDecoderFromFilename(@"D:\Photo\alina.jpg", Guid.Empty, System.IO.FileAccess.Read, DecodeOptions.MetadataCacheOnDemand))
                {
                    using (WicBitmapFrameDecode frame = decoder.GetFrame(0))
                    {
                        using (WicFormatConverter converter = wif.CreateFormatConverter())
                        {
                            converter.Convert(frame, WicPixelFormats.PixelFormat32bppPBGRA, BitmapDitherType.None, null, 0, BitmapPaletteType.Custom);
                            this._photo = _renderTarget.CreateBitmap(converter, new BitmapProperties());
                        }
                    }
                }
            }
            this.Resize += new EventHandler(MainWindow_Resize);
            SizeU photoSize = this._photo.PixelSize;
            this.ClientSize = new System.Drawing.Size((int)photoSize.Width, (int)photoSize.Height);
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            _angle += 4;
            _angle %= 360;
            Invalidate();
            Update();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            timer1.Enabled = !timer1.Enabled;
        }
    }
}
