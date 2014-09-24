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
        private Matrix4x4 _projection;
        private Vector4[] _points;

        private ControlPointArrayDx(int count)
        {
            this._points = new Vector4[count];
        }
        public static ControlPointArrayDx Generate(int count, float minX, float maxX, float minY, float maxY)
        {
            ControlPointArrayDx p = new ControlPointArrayDx(count);
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
        //public Vector4 this[int index]
        //{
        //    get { return this._points[index]; }
        //    set { this._points[index] = value; }
        //}
        private void Generate(float minX, float maxX, float minY, float maxY, float minZ, float maxZ)
        {
            //_projection = Matrix4x4.PerspectiveProjection(10);
            _projection = ComputeFOVProjection((float)(90 * Math.PI / 180), 1, 50, 100);
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
            result._projection = this._projection;
            int count = this.Count;
            for (var index = 0; index < count - 1; ++index)
            {
                result._points[index] = Vector4.Lerp(this._points[index], this._points[index + 1], t);
            }
            return result;
        }

        PointF Project(Vector4 p)
        {
            Vector4 r = _projection * p;
            return new PointF(r.X, r.Y);
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

        static Matrix4x4 ComputeFOVProjection(float fov, float aspect, float nearDist, float farDist, bool leftHanded = true)
        {
            //
            // General form of the Projection Matrix
            //
            // uh = Cot( fov/2 ) == 1/Tan(fov/2)
            // uw / uh = 1/aspect
            // 
            //   uw         0       0       0
            //    0        uh       0       0
            //    0         0      f/(f-n)  1
            //    0         0    -fn/(f-n)  0
            //
            // Make result to be identity first

            // check for bad parameters to avoid divide by zero:
            // if found, assert and return an identity matrix.
            if (fov <= 0 || aspect == 0)
            {
                throw new ArgumentException();
                //Assert( fov > 0 && aspect != 0 );
                //return ;
            }

            float frustumDepth = farDist - nearDist;
            float oneOverDepth = 1 / frustumDepth;

            float m11 = (float)(1.0 / Math.Tan(0.5f * fov));
            float m00 = (leftHanded ? 1 : -1) * m11 / aspect;
            float m22 = farDist * oneOverDepth;
            float m32 = (-farDist * nearDist) * oneOverDepth;
            float m23 = 1;
            float m33 = 0;
            return new Matrix4x4(
                m00, 0, 0, 0,
                0, m11, 0, 0,
                0, 0, m22, m23,
                0, 0, m32, m33);
        }
    }
}
