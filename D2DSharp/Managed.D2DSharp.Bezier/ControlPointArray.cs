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
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Managed.Graphics.Direct2D;

namespace Managed.D2DSharp.Bezier
{
    public class ControlPointArray
    {
        private PointF[] _points;

        private ControlPointArray(int count)
        {
            this._points = new PointF[count];
        }
        public static ControlPointArray Generate(int count, float minX, float maxX, float minY, float maxY)
        {
            ControlPointArray p = new ControlPointArray(count);
            p.Generate(minX, maxX, minY, maxY);
            return p;
        }
        public IEnumerable<PointF> Points
        {
            get { return this._points; }
        }
        public int Count
        {
            get { return this._points.Length; }
        }
        public PointF this[int index]
        {
            get { return this._points[index]; }
            set { this._points[index] = value; }
        }
        private void Generate(float minX, float maxX, float minY, float maxY)
        {
            Random random = new Random();
            for (int index = 0; index < this._points.Length; ++index)
            {
                this._points[index].X = (float)(minX + random.NextDouble() * (maxX - minX));
                this._points[index].Y = (float)(minY + random.NextDouble() * (maxY - minY));
            }
        }
        public ControlPointArray Reduce(float t)
        {
            ControlPointArray result = new ControlPointArray(this.Count - 1);
            int count = this.Count;
            for (var index = 0; index < count - 1; ++index)
            {
                var point1 = this._points[index];
                var point2 = this._points[index + 1];
                result[index] = new PointF(point1.X + (point2.X - point1.X) * t, point1.Y + (point2.Y - point1.Y) * t);
            }
            return result;
        }

        public Geometry CreateGeometry(Direct2DFactory factory)
        {

            PathGeometry geometry = factory.CreatePathGeometry();

            using (GeometrySink sink = geometry.Open())
            {
                sink.BeginFigure(this._points[0], FigureBegin.Hollow);
                sink.AddLines(this._points);
                sink.EndFigure(FigureEnd.Open);
                sink.Close();
            }
            List<Geometry> list = new List<Geometry>();
            list.Add(geometry);

            for (int index = 0; index < this._points.Length; ++index)
            {
                EllipseGeometry ellipse = factory.CreateEllipseGeometry(new Ellipse(this._points[index], 5, 5));
                list.Add(ellipse);
            }

            GeometryGroup group = factory.CreateGeometryGroup(FillMode.Winding, list.ToArray());

            return group;
        }
    }
}
