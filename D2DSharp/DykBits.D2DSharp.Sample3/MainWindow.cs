/* 
* MainWindow.cs 
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
using Managed.Graphics.Forms;

namespace Managed.D2DSharp.AdvancedPathGeometries
{
    public partial class MainWindow : Direct2DWindow
    {
        private PathGeometry _leftMountainGeometry;
        private PathGeometry _rightMountainGeometry;
        private PathGeometry _sunGeometry;
        private PathGeometry _riverGeometry;
        private SolidColorBrush _sceneBrush;
        private RadialGradientBrush _radialGradientBrush;
        private BitmapBrush _gridPatternBrush;

        public MainWindow()
        {
            InitializeComponent();
        }

        protected override void OnRender(WindowRenderTarget renderTarget)
        {
            RectF bounds = new RectF(new PointF(), renderTarget.Size);
            renderTarget.FillRect(_gridPatternBrush, bounds);

            renderTarget.FillGeometry(_radialGradientBrush, _sunGeometry);

            _sceneBrush.Color = Color.FromKnown(Colors.Black, 1);
            renderTarget.DrawGeometry(_sceneBrush, 1, _sunGeometry);

            _sceneBrush.Color = Color.FromKnown(Colors.OliveDrab, 1);
            renderTarget.FillGeometry(_sceneBrush, _leftMountainGeometry);

            _sceneBrush.Color = Color.FromKnown(Colors.Black, 1);
            renderTarget.DrawGeometry(_sceneBrush, 1, _leftMountainGeometry);

            _sceneBrush.Color = Color.FromKnown(Colors.LightSkyBlue, 1);
            renderTarget.FillGeometry(_sceneBrush, _riverGeometry);

            _sceneBrush.Color = Color.FromKnown(Colors.Black, 1);
            renderTarget.DrawGeometry(_sceneBrush, 1, _riverGeometry);

            _sceneBrush.Color = Color.FromKnown(Colors.YellowGreen, 1);
            renderTarget.FillGeometry(_sceneBrush, _rightMountainGeometry);

            _sceneBrush.Color = Color.FromKnown(Colors.Black, 1);
            renderTarget.DrawGeometry(_sceneBrush, 1, _rightMountainGeometry);
        }

        protected override void OnCreateDeviceIndependentResources(Direct2DFactory factory)
        {
            base.OnCreateDeviceIndependentResources(factory);
            _leftMountainGeometry = factory.CreatePathGeometry();
            using (GeometrySink sink = _leftMountainGeometry.Open())
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

            _rightMountainGeometry = factory.CreatePathGeometry();
            using (GeometrySink sink = _rightMountainGeometry.Open())
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

            _sunGeometry = factory.CreatePathGeometry();
            using (GeometrySink sink = _sunGeometry.Open())
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
            _riverGeometry = factory.CreatePathGeometry();
            using (GeometrySink sink = _riverGeometry.Open())
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
        }

        protected override void OnCleanUpDeviceIndependentResources()
        {
            base.OnCleanUpDeviceIndependentResources();
            _leftMountainGeometry.Dispose();
            _rightMountainGeometry.Dispose();
            _sunGeometry.Dispose();
            _riverGeometry.Dispose();
        }

        protected override void OnCreateDeviceResources(WindowRenderTarget renderTarget)
        {
            base.OnCreateDeviceResources(renderTarget);
            // Create an array of gradient stops to put in the gradient stop
            // collection that will be used in the gradient brush.
            GradientStop[] stops = new GradientStop[] {
                new GradientStop(0, Color.FromKnown(Colors.Gold, 1)),
                new GradientStop(0.85f, Color.FromKnown(Colors.Orange, 1)),
                new GradientStop(1, Color.FromKnown(Colors.OrangeRed, 1))
            };

            using (GradientStopCollection gradiendStops = renderTarget.CreateGradientStopCollection(stops, Gamma.Gamma22, ExtendMode.Clamp))
            {
                // The center of the gradient is in the center of the box.
                // The gradient origin offset was set to zero(0, 0) or center in this case.
                _radialGradientBrush = renderTarget.CreateRadialGradientBrush(
                    new RadialGradientBrushProperties(
                        new PointF(330, 330),
                        new PointF(140, 140),
                        140,
                        140),
                        BrushProperties.Default,
                        gradiendStops);
            }

            _sceneBrush = renderTarget.CreateSolidColorBrush(Color.FromKnown(Colors.Black, 1));
            _gridPatternBrush = renderTarget.CreateGridPatternBrush(new SizeF(10, 10), Color.FromRGB(0.93f, 0.94f, 0.96f));
        }

        protected override void OnCleanUpDeviceResources()
        {
            base.OnCleanUpDeviceResources();
            _radialGradientBrush.Dispose();
            _sceneBrush.Dispose();
            _gridPatternBrush.Dispose();
        }
    }
}
