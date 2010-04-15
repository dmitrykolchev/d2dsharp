using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using DykBits.Graphics.Direct2D;

namespace DykBits.D2DSharp.Sample3
{
    public partial class MainWindow : Form
    {
        private Direct2DFactory _factory;
        private WindowRenderTarget _renderTarget;
        private PathGeometry _leftMountainGeometry;
        private PathGeometry _rightMountainGeometry;
        private PathGeometry _sunGeometry;
        private PathGeometry _riverGeometry;
        private SolidColorBrush _sceneBrush;
        private RadialGradientBrush _radialGradientBrush;
        private BitmapBrush _gridPatternBrush;

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

        void MainWindow_Paint(object sender, PaintEventArgs e)
        {
            this._renderTarget.BeginDraw();
            RectF bounds = new RectF(new PointF(), _renderTarget.Size);
            this._renderTarget.Clear(Color.FromARGB(Colors.White, 1));
            this._renderTarget.FillRect(_gridPatternBrush, bounds);

            this._renderTarget.FillGeometry(this._radialGradientBrush, this._sunGeometry);

            this._sceneBrush.Color = Color.FromARGB(Colors.Black, 1);
            this._renderTarget.DrawGeometry(this._sceneBrush, 1, _sunGeometry);

            this._sceneBrush.Color = Color.FromARGB(Colors.OliveDrab, 1);
            this._renderTarget.FillGeometry(this._sceneBrush, this._leftMountainGeometry);

            this._sceneBrush.Color = Color.FromARGB(Colors.Black, 1);
            this._renderTarget.DrawGeometry(this._sceneBrush, 1, this._leftMountainGeometry);

            this._sceneBrush.Color = Color.FromARGB(Colors.LightSkyBlue, 1);
            this._renderTarget.FillGeometry(this._sceneBrush, this._riverGeometry);

            this._sceneBrush.Color = Color.FromARGB(Colors.Black, 1);
            this._renderTarget.DrawGeometry(this._sceneBrush, 1, this._riverGeometry);

            this._sceneBrush.Color = Color.FromARGB(Colors.YellowGreen, 1);
            this._renderTarget.FillGeometry(this._sceneBrush, this._rightMountainGeometry);

            this._sceneBrush.Color = Color.FromARGB(Colors.Black, 1);
            this._renderTarget.DrawGeometry(this._sceneBrush, 1, this._rightMountainGeometry);

            this._renderTarget.EndDraw();
        }

        void MainWindow_Load(object sender, EventArgs e)
        {
            this._factory = Direct2DFactory.CreateFactory(FactoryType.SingleThreaded, DebugLevel.None);
            StrokeStyleProperties ssp = new StrokeStyleProperties(LineCapStyle.Round, LineCapStyle.Round,
                LineCapStyle.Round, LineJoin.Round, 10, DashStyle.Solid, 0);

            this._leftMountainGeometry = this._factory.CreatePathGeometry();
            using (GeometrySink sink = this._leftMountainGeometry.Open())
            {
                sink.SetFillMode(FillMode.Winding);
                sink.BeginFigure(new PointF(346, 255), FigureBegin.Filled);
                sink.AddLines(
                    new PointF[] { 
                        new PointF(267, 177),
                        new PointF(236, 192),
                        new PointF(212, 160),
                        new PointF(156, 255),
                        new PointF(346, 255)
                    });
                sink.EndFigure(FigureEnd.Closed);
                sink.Close();
            }

            this._rightMountainGeometry = this._factory.CreatePathGeometry();
            using (GeometrySink sink = this._rightMountainGeometry.Open())
            {
                sink.SetFillMode(FillMode.Winding);
                sink.BeginFigure(new PointF(575, 263), FigureBegin.Filled);
                sink.AddLines(
                    new PointF[] { 
                        new PointF(481, 146),
                        new PointF(449, 181),
                        new PointF(433, 159),
                        new PointF(401, 214),
                        new PointF(381, 199), 
                        new PointF(323, 263), 
                        new PointF(575, 263)
                    });
                sink.EndFigure(FigureEnd.Closed);
                sink.Close();
            }

            this._sunGeometry = this._factory.CreatePathGeometry();
            using (GeometrySink sink = this._sunGeometry.Open())
            {
                sink.SetFillMode(FillMode.Winding);
                sink.BeginFigure(new PointF(270, 255), FigureBegin.Filled);
                sink.AddArc(
                    new ArcSegment(
                        new PointF(440, 255), // end point
                        new SizeF(85, 85),
                        0.0f, // rotation angle
                        SweepDirection.Clockwise,
                        ArcSize.Small));

                sink.EndFigure(FigureEnd.Closed);

                sink.BeginFigure(new PointF(299, 182), FigureBegin.Hollow);
                sink.AddBezier(
                    new BezierSegment(
                       new PointF(299, 182),
                       new PointF(294, 176),
                       new PointF(285, 178)
                       ));
                sink.AddBezier(
                   new BezierSegment(
                       new PointF(276, 179),
                       new PointF(272, 173),
                       new PointF(272, 173)
                       ));
                sink.EndFigure(FigureEnd.Open);

                sink.BeginFigure(
                    new PointF(354, 156),
                    FigureBegin.Hollow
                    );
                sink.AddBezier(
                   new BezierSegment(
                       new PointF(354, 156),
                       new PointF(358, 149),
                       new PointF(354, 142)
                       ));
                sink.AddBezier(
                   new BezierSegment(
                       new PointF(349, 134),
                       new PointF(354, 127),
                       new PointF(354, 127)
                       ));
                sink.EndFigure(FigureEnd.Open);

                sink.BeginFigure(
                    new PointF(322, 164),
                    FigureBegin.Hollow
                    );

                sink.AddBezier(
                   new BezierSegment(
                       new PointF(322, 164),
                       new PointF(322, 156),
                       new PointF(314, 152)
                       ));
                sink.AddBezier(
                   new BezierSegment(
                       new PointF(306, 149),
                       new PointF(305, 141),
                       new PointF(305, 141)
                       ));
                sink.EndFigure(FigureEnd.Open);

                sink.BeginFigure(
                    new PointF(385, 164),
                    FigureBegin.Hollow
                    );
                sink.AddBezier(
                   new BezierSegment(
                       new PointF(385, 164),
                       new PointF(392, 161),
                       new PointF(394, 152)
                       ));
                sink.AddBezier(
                   new BezierSegment(
                       new PointF(395, 144),
                       new PointF(402, 141),
                       new PointF(402, 142)
                       ));
                sink.EndFigure(FigureEnd.Open);

                sink.BeginFigure(
                    new PointF(408, 182),
                    FigureBegin.Hollow
                    );
                sink.AddBezier(
                   new BezierSegment(
                       new PointF(408, 182),
                       new PointF(416, 184),
                       new PointF(422, 178)
                       ));
                sink.AddBezier(
                   new BezierSegment(
                       new PointF(428, 171),
                       new PointF(435, 173),
                       new PointF(435, 173)
                       ));
                sink.EndFigure(FigureEnd.Open);
                sink.Close();
            }

            this._renderTarget = this._factory.CreateWindowRenderTarget(this);

            this._riverGeometry = this._factory.CreatePathGeometry();
            using (GeometrySink sink = this._riverGeometry.Open())
            {
                sink.SetFillMode(FillMode.Winding);
                sink.BeginFigure(
                    new PointF(183, 392),
                    FigureBegin.Filled
                    );
                sink.AddBezier(
                   new BezierSegment(
                       new PointF(238, 284),
                       new PointF(472, 345),
                       new PointF(356, 303)
                       ));
                sink.AddBezier(
                   new BezierSegment(
                       new PointF(237, 261),
                       new PointF(333, 256),
                       new PointF(333, 256)
                       ));
                sink.AddBezier(
                   new BezierSegment(
                       new PointF(335, 257),
                       new PointF(241, 261),
                       new PointF(411, 306)
                       ));
                sink.AddBezier(
                   new BezierSegment(
                       new PointF(574, 350),
                       new PointF(288, 324),
                       new PointF(296, 392)
                       ));
                sink.EndFigure(FigureEnd.Open);
                sink.Close();
            }

            // Create an array of gradient stops to put in the gradient stop
            // collection that will be used in the gradient brush.
            GradientStop[] stops = new GradientStop[] {
                new GradientStop(0, Color.FromARGB(Colors.Gold, 1)),
                new GradientStop(0.85f, Color.FromARGB(Colors.Orange, 1)),
                new GradientStop(1, Color.FromARGB(Colors.OrangeRed, 1))
            };

            using (GradientStopCollection gradiendStops = this._renderTarget.CreateGradientStopCollection(stops, Gamma.Gamma10, ExtendMode.Clamp))
            {
                // The center of the gradient is in the center of the box.
                // The gradient origin offset was set to zero(0, 0) or center in this case.
                this._radialGradientBrush = this._renderTarget.CreateRadialGradientBrush(
                    new RadialGradientBrushProperties(
                        new PointF(330, 330),
                        new PointF(140, 140),
                        140,
                        140),
                        BrushProperties.Default,
                        gradiendStops);
            }

            this._sceneBrush = this._renderTarget.CreateSolidColorBrush(Color.FromARGB(Colors.Black, 1));
            this._gridPatternBrush = this._renderTarget.CreateGridPatternBrush(new SizeF(10, 10), Color.FromARGB(1, 0.93f, 0.94f, 0.96f));

            this.Resize += new EventHandler(MainWindow_Resize);
        }

        void MainWindow_Resize(object sender, EventArgs e)
        {
            if (this._renderTarget != null)
            {
                this._renderTarget.Resize(new SizeU { Width = (uint)ClientSize.Width, Height = (uint)ClientSize.Height });
            }
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
        }
    }
}
