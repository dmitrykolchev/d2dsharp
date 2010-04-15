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
            if (IsHandleCreated)
                this._renderTarget.Resize(new SizeU { Width = (uint)ClientSize.Width, Height = (uint)ClientSize.Height });
        }

        SolidColorBrush RectBrush
        {
            get
            {
                if (this._brush == null)
                {

                    this._brush = _renderTarget.CreateSolidColorBrush(Color.FromARGB(Colors.Red, 1), BrushProperties.Default);
                    this._brush.Opacity = 1f;
                }
                return this._brush;
            }
        }

        int _angle = 0;

        void MainWindow_Paint(object sender, PaintEventArgs e)
        {
            this._renderTarget.BeginDraw();
            this._renderTarget.Clear(Color.FromARGB(Colors.Blue, 1));

            PointF center = new PointF(ClientSize.Width / 2, ClientSize.Height / 2);
            this._renderTarget.Transform = Matrix3x2.Rotation(_angle, center);

            RoundedRect rr = new RoundedRect(new RectF(30, 30, ClientSize.Width - 60, ClientSize.Height - 60), ClientSize.Width / 2.5f, ClientSize.Height / 2.5f);
            this._renderTarget.FillRoundedRect(RectBrush, rr);
            this._renderTarget.DrawRoundedRect(_strokeBrush, 5, _strokeStyle, rr);

            Ellipse ellipse = new Ellipse(ClientSize.Width / 2, ClientSize.Height / 2, ClientSize.Width / 4, ClientSize.Height / 4);
            using (EllipseGeometry eg = this._factory.CreateEllipseGeometry(ellipse))
            {
                using (Brush b = CreateEllipseBrush(ellipse))
                {
                    this._renderTarget.FillGeometry(b, eg);
                    this._renderTarget.DrawGeometry(_strokeBrush, 5, _strokeStyle, eg);
                }
            }
            RectF textBounds = new RectF(0, 0, ClientSize.Width, ClientSize.Height);

            this._renderTarget.DrawText("Hello, world!", _textFormat, textBounds, _strokeBrush, DrawTextOptions.None, MeasuringMode.Natural);

            this._renderTarget.DrawLine(_strokeBrush, 5, _strokeStyle, new PointF(0, 0), new PointF(ClientSize.Width, ClientSize.Height));

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
                        new GradientStop(0, Color.FromARGB(Colors.Blue,1)), 
                        new GradientStop(0.5f, Color.FromARGB(Colors.Green,1)), 
                        new GradientStop(1, Color.FromARGB(Colors.Blue,1))
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

            this.ClientSize = new System.Drawing.Size(600, 600);
            this._factory = Direct2DFactory.CreateFactory(FactoryType.SingleThreaded, DebugLevel.None);

            this._renderTarget = this._factory.CreateWindowRenderTarget(this, PresentOptions.None, RenderTargetProperties.Default);
            AntialiasMode amode = this._renderTarget.AntialiasMode;
            TextAntialiasMode tamode = this._renderTarget.TextAntialiasMode;
            this._strokeBrush = this._renderTarget.CreateSolidColorBrush(Color.FromARGB(Colors.Cyan, 1));
            this._strokeStyle = this._factory.CreateStrokeStyle(new StrokeStyleProperties(LineCapStyle.Flat,
                LineCapStyle.Flat, LineCapStyle.Round, LineJoin.Miter, 10, DashStyle.Dot, 0), null);


            this.Resize += new EventHandler(MainWindow_Resize);
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
            this.button1.Text = timer1.Enabled ? "Stop" : "Animate";
        }
    }
}
