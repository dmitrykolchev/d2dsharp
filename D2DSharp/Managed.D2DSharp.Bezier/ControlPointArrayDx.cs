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
using Managed.Graphics;

namespace Managed.D2DSharp.Bezier
{
    public class ControlPointArrayDx
    {
        private Vector4[] _points;

        private ControlPointArrayDx(int count)
        {
            this._points = new Vector4[count];
        }
        public static ControlPointArrayDx Generate(int count, float minX, float maxX, float minY, float maxY, Vector4 pointOfView)
        {
            ControlPointArrayDx p = new ControlPointArrayDx(count);
            p.PointOfView = pointOfView;
            p.Generate(minX, maxX, minY, maxY, minY, maxY);
            return p;
        }
        public IEnumerable<Vector4> Points
        {
            get { return this._points; }
        }
        public int Count
        {
            get { return this._points.Length; }
        }
        private void Generate(float minX, float maxX, float minY, float maxY, float minZ, float maxZ)
        {
            Random random = new Random();
            for (int index = 0; index < this._points.Length; ++index)
            {
                this._points[index] = new Vector4(
                    (float)(minX + random.NextDouble() * (maxX - minX)),
                    (float)(minY + random.NextDouble() * (maxY - minY)),
                    (float)(minZ + random.NextDouble() * (maxZ - minZ)),
                    1);
            }
        }
        public ControlPointArrayDx Reduce(float t)
        {
            ControlPointArrayDx result = new ControlPointArrayDx(this.Count - 1);
            result.PointOfView = this.PointOfView;
            int count = this.Count;
            for (var index = 0; index < count - 1; ++index)
            {
                result._points[index] = Vector4.Lerp(this._points[index], this._points[index + 1], t);
            }
            return result;
        }

        public Vector4 PointOfView { get; set; }

        PointF Project(Vector4 p)
        {
            Vector4 pv = PointOfView;
            double t = - pv.Z / (p.Z - pv.Z);
            double x = pv.X + (p.X - pv.X) * t;
            double y = pv.Y + (p.Y - pv.Y) * t;
            return new PointF((float)x, (float)y);
        }
        public Geometry CreateGeometry(Direct2DFactory factory)
        {
            PathGeometry geometry = factory.CreatePathGeometry();

            using (GeometrySink sink = geometry.Open())
            {
                sink.BeginFigure(Project(this._points[0]), FigureBegin.Hollow);
                for (int index = 1; index < this._points.Length; ++index)
                {
                    sink.AddLine(Project(this._points[index]));
                }
                sink.EndFigure(FigureEnd.Open);
                sink.Close();
            }
            List<Geometry> list = new List<Geometry>();
            list.Add(geometry);

            for (int index = 0; index < this._points.Length; ++index)
            {
                EllipseGeometry ellipse = factory.CreateEllipseGeometry(new Ellipse(Project(this._points[index]), 5, 5));
                list.Add(ellipse);
            }

            GeometryGroup group = factory.CreateGeometryGroup(FillMode.Winding, list.ToArray());

            return group;
        }

    }
}
