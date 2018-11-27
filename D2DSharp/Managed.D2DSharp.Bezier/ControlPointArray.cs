/* 
* ControlPointArray.cs
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
using System;
using System.Collections.Generic;

namespace Managed.D2DSharp.Bezier
{
    public class ControlPointArray
    {
        private PointF[] _points;

        private ControlPointArray(int count)
        {
            _points = new PointF[count];
        }
        public static ControlPointArray Generate(int count, float minX, float maxX, float minY, float maxY)
        {
            ControlPointArray p = new ControlPointArray(count);
            p.Generate(minX, maxX, minY, maxY);
            return p;
        }
        public IEnumerable<PointF> Points
        {
            get { return _points; }
        }
        public int Count
        {
            get { return _points.Length; }
        }
        public PointF this[int index]
        {
            get { return _points[index]; }
            set { _points[index] = value; }
        }
        private void Generate(float minX, float maxX, float minY, float maxY)
        {
            Random random = new Random();
            for (int index = 0; index < _points.Length; ++index)
            {
                _points[index].X = (float)(minX + random.NextDouble() * (maxX - minX));
                _points[index].Y = (float)(minY + random.NextDouble() * (maxY - minY));
            }
        }
        public ControlPointArray Reduce(float t)
        {
            ControlPointArray result = new ControlPointArray(Count - 1);
            int count = Count;
            for (var index = 0; index < count - 1; ++index)
            {
                var point1 = _points[index];
                var point2 = _points[index + 1];
                result[index] = new PointF(point1.X + (point2.X - point1.X) * t, point1.Y + (point2.Y - point1.Y) * t);
            }
            return result;
        }

        public Geometry CreateGeometry(Direct2DFactory factory)
        {

            PathGeometry geometry = factory.CreatePathGeometry();

            using (GeometrySink sink = geometry.Open())
            {
                sink.BeginFigure(_points[0], FigureBegin.Hollow);
                sink.AddLines(_points);
                sink.EndFigure(FigureEnd.Open);
                sink.Close();
            }
            Geometry[] list = new Geometry[_points.Length + 1];
            list[0] = geometry;

            for (int index = 0; index < _points.Length; ++index)
            {
                list[index + 1] = factory.CreateEllipseGeometry(new Ellipse(_points[index], 5, 5));
            }
            GeometryGroup group = factory.CreateGeometryGroup(FillMode.Winding, list);

            return group;
        }
    }
}
