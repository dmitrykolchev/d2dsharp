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
using Managed.Graphics.DirectWrite;
using Managed.Graphics.Forms;

namespace Managed.D2DSharp.CombineGeometries
{
    public partial class MainWindow : Direct2DWindow
    {
        private TextFormat _textFormat;
        private StrokeStyle _strokeStyle;
        private EllipseGeometry _circleGeometry1;
        private EllipseGeometry _circleGeometry2;
        private PathGeometry _geometryUnion;
        private PathGeometry _geometryIntersect;
        private PathGeometry _geometryXor;
        private PathGeometry _geometryExclude;

        private SolidColorBrush _outlineBrush;
        private SolidColorBrush _shapeFillBrush;
        private SolidColorBrush _textFillBrush;
        private BitmapBrush _gridPatternBrush;

        public MainWindow()
        {
            InitializeComponent();
        }

        protected override void OnCreateDeviceIndependentResources(Direct2DFactory factory)
        {
            base.OnCreateDeviceIndependentResources(factory);
            _textFormat = DirectWriteFactory.CreateTextFormat("Verdana", 10.5f, FontWeight.Normal, FontStyle.Normal, FontStretch.Normal);
            _textFormat.TextAlignment = TextAlignment.Center;

            float[] dashes = new float[] { 1, 1, 2, 3, 5 };
            _strokeStyle = factory.CreateStrokeStyle(
                new StrokeStyleProperties(LineCapStyle.Flat, LineCapStyle.Flat, LineCapStyle.Round, LineJoin.Round, 10, DashStyle.Custom, 0),
                dashes);
            CreateGeometries(factory);
        }

        private void CreateGeometries(Direct2DFactory factory)
        {
            Ellipse circle1 = new Ellipse(75, 75, 50, 50);
            _circleGeometry1 = factory.CreateEllipseGeometry(circle1);

            Ellipse circle2 = new Ellipse(125, 75, 50, 50);
            _circleGeometry2 = factory.CreateEllipseGeometry(circle2);
            // Union
            _geometryUnion = factory.CreatePathGeometry();
            using (GeometrySink sink = _geometryUnion.Open())
            {
                _circleGeometry1.CombineWithGeometry(_circleGeometry2, CombineMode.Union, Matrix3x2.Identity, 0.25f, sink);
                sink.Close();
            }
            // Intersect
            _geometryIntersect = factory.CreatePathGeometry();
            using (GeometrySink sink = _geometryIntersect.Open())
            {
                _circleGeometry1.CombineWithGeometry(_circleGeometry2, CombineMode.Intersect, Matrix3x2.Identity, 0.25f, sink);
                sink.Close();
            }
            // Xor
            _geometryXor = factory.CreatePathGeometry();
            using (GeometrySink sink = _geometryXor.Open())
            {
                _circleGeometry1.CombineWithGeometry(_circleGeometry2, CombineMode.Xor, Matrix3x2.Identity, 0.25f, sink);
                sink.Close();
            }
            // Exclude
            _geometryExclude = factory.CreatePathGeometry();
            using (GeometrySink sink = _geometryExclude.Open())
            {
                _circleGeometry1.CombineWithGeometry(_circleGeometry2, CombineMode.Exclude, Matrix3x2.Identity, 0.25f, sink);
                sink.Close();
            }
        }

        protected override void OnCleanUpDeviceIndependentResources()
        {
            base.OnCleanUpDeviceIndependentResources();
            _strokeStyle.Dispose();
            _textFormat.Dispose();
            _circleGeometry1.Dispose();
            _circleGeometry2.Dispose();
            _geometryUnion.Dispose();
            _geometryIntersect.Dispose();
            _geometryXor.Dispose();
            _geometryExclude.Dispose();
        }

        protected override void OnCreateDeviceResources(WindowRenderTarget renderTarget)
        {
            base.OnCreateDeviceResources(renderTarget);

            _outlineBrush = renderTarget.CreateSolidColorBrush(Color.FromKnown(Colors.DarkSlateBlue, 1), 1);
            _shapeFillBrush = renderTarget.CreateSolidColorBrush(Color.FromKnown(Colors.CornflowerBlue, 1), 0.5f);
            _textFillBrush = renderTarget.CreateSolidColorBrush(Color.FromKnown(Colors.Black, 1), 1);
            _gridPatternBrush = renderTarget.CreateGridPatternBrush(new SizeF(10, 10), Color.FromRGB(0.93f, 0.94f, 0.96f));
        }

        protected override void OnCleanUpDeviceResources()
        {
            base.OnCleanUpDeviceResources();
            _outlineBrush.Dispose();
            _shapeFillBrush.Dispose();
            _textFillBrush.Dispose();
            _gridPatternBrush.Dispose();
        }

        protected override void OnRender(WindowRenderTarget renderTarget)
        {
            RectF bounds = new RectF(new PointF(), renderTarget.Size);
            renderTarget.FillRect(_gridPatternBrush, bounds);

            // Draw the geomtries before merging.
            renderTarget.FillGeometry(_shapeFillBrush, _circleGeometry1);
            renderTarget.DrawGeometry(_outlineBrush, 1, _circleGeometry1);
            renderTarget.FillGeometry(_shapeFillBrush, _circleGeometry2);
            renderTarget.DrawGeometry(_outlineBrush, 1, _circleGeometry2);

            renderTarget.DrawText(
                "The circles before combining",
                _textFormat,
                new RectF(25, 130, 150, 170),
                _textFillBrush,
                DrawTextOptions.None, MeasuringMode.Natural);

            renderTarget.Transform = Matrix3x2.Translation(200, 0);

            // Draw the geometries merged using the union combine mode.
            renderTarget.FillGeometry(_shapeFillBrush, _geometryUnion);
            renderTarget.DrawGeometry(_outlineBrush, 1, _geometryUnion);

            renderTarget.DrawText(
                "CombineMode.Union",
                _textFormat,
                new RectF(25, 130, 150, 170),
                _textFillBrush,
                DrawTextOptions.None, MeasuringMode.Natural);

            renderTarget.Transform = Matrix3x2.Translation(400, 0);

            // Draw the geometries merged using the intersect combine mode.
            renderTarget.FillGeometry(_shapeFillBrush, _geometryIntersect);
            renderTarget.DrawGeometry(_outlineBrush, 1, _geometryIntersect);

            renderTarget.DrawText(
                "CombineMode.Intersect",
                _textFormat,
                new RectF(25, 130, 150, 170),
                _textFillBrush,
                DrawTextOptions.None, MeasuringMode.Natural);

            renderTarget.Transform = Matrix3x2.Translation(200, 150);

            // Draw the geometries merged using the XOR combine mode.
            renderTarget.FillGeometry(_shapeFillBrush, _geometryXor);
            renderTarget.DrawGeometry(_outlineBrush, 1, _geometryXor);

            renderTarget.DrawText(
                "CombineMode.Xor",
                _textFormat,
                new RectF(25, 130, 150, 170),
                _textFillBrush,
                DrawTextOptions.None, MeasuringMode.Natural);

            renderTarget.Transform = Matrix3x2.Translation(400, 150);

            // Draw the geometries merged using the Exclude combine mode.
            renderTarget.FillGeometry(_shapeFillBrush, _geometryExclude);
            renderTarget.DrawGeometry(_outlineBrush, 1, _geometryExclude);

            renderTarget.DrawText(
                "CombineMode.Exclude",
                _textFormat,
                new RectF(25, 130, 150, 170),
                _textFillBrush,
                DrawTextOptions.None, MeasuringMode.Natural);



            //// The following code demonstrates how to call various geometric operations. Depending on 
            //// your needs, it lets you decide how to use those output values.
            //D2D1_GEOMETRY_RELATION result = D2D1_GEOMETRY_RELATION_UNKNOWN;

            //// Compare circle1 with circle2
            //hr = m_pCircleGeometry1->CompareWithGeometry(
            //    m_pCircleGeometry2,
            //    D2D1::IdentityMatrix(),
            //    0.1f,
            //    &result
            //    );

            //if (SUCCEEDED(hr))
            //{
            //    static const WCHAR szGeometryRelation[] = L"Two circles overlap.";
            //    renderTarget.SetTransform(D2D1::IdentityMatrix());
            //    if (result == D2D1_GEOMETRY_RELATION_OVERLAP)
            //    {
            //        renderTarget.DrawText(
            //            szGeometryRelation,
            //            ARRAYSIZE(szGeometryRelation) - 1,
            //            m_pTextFormat,
            //            D2D1::RectF(25.0f, 160.0f, 200.0f, 300.0f),
            //            m_pTextBrush
            //            );
            //    }
            //}

            //float area;

            //// Compute the area of circle1
            //hr = m_pCircleGeometry1->ComputeArea(
            //    D2D1::IdentityMatrix(),
            //    &area
            //    );

            //float length;

            //// Compute the area of circle1
            //hr = m_pCircleGeometry1->ComputeLength(
            //    D2D1::IdentityMatrix(),
            //    &length
            //    );

            //if (SUCCEEDED(hr))
            //{
            //    // Process the length of the geometry.
            //}

            //D2D1_POINT_2F point;
            //D2D1_POINT_2F tangent;

            //hr = m_pCircleGeometry1->ComputePointAtLength(
            //    10, 
            //    NULL, 
            //    &point, 
            //    &tangent); 

            //if (SUCCEEDED(hr))
            //{
            //    // Retrieve the point and tangent point.
            //}

            //D2D1_RECT_F bounds;

            //hr = m_pCircleGeometry1->GetBounds(
            //      D2D1::IdentityMatrix(),
            //      &bounds
            //     );

            //if (SUCCEEDED(hr))
            //{
            //    // Retrieve the bounds.
            //}

            //D2D1_RECT_F bounds1;
            //hr = m_pCircleGeometry1->GetWidenedBounds(
            //      5.0,
            //      m_pStrokeStyle,
            //      D2D1::IdentityMatrix(),
            //      &bounds1
            //     );
            //if (SUCCEEDED(hr))
            //{
            //    // Retrieve the widened bounds.
            //}

            //BOOL containsPoint;

            //hr = m_pCircleGeometry1->StrokeContainsPoint(
            //    D2D1::Point2F(0,0),
            //    10,     // stroke width
            //    NULL,   // stroke style
            //    NULL,   // world transform
            //    &containsPoint
            //    );

            //if (SUCCEEDED(hr))
            //{
            //    // Process containsPoint.
            //}

            //BOOL containsPoint1;
            //hr = m_pCircleGeometry1->FillContainsPoint(
            //    D2D1::Point2F(0,0),
            //    D2D1::Matrix3x2F::Identity(),
            //    &containsPoint1
            //    );


        }
    }
}
