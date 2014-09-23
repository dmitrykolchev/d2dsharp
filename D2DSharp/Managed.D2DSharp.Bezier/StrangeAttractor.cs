/* 
* StrangeAttractor.cs
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
    class StrangeAttractor
    {
        private double x;
        private double y;
        private double z;

        PointF[] _points;
        public StrangeAttractor()
        {
            x = 3.051522;
            y = 1.582542;
            z = 15.62388;
        }
        public void Generate(int count)
        {
            this._points = new PointF[count];

            double dt = 0.0001;
            double a = 5;
            double b = 15;
            double c = 1;
            for(int index = 0; index < count; ++index)
            {
                double x1 = x + a * (-x + y) * dt;
                double y1 = y + (b * x - y - z * x) * dt;
                double z1 = z + (-c * z + x * y) * dt;
                x = x1; y = y1; z = z1;
                this[index] = new PointF((float)(60 * (y - x * 0.292893) + 800), (float)(-40 * (z + x * 0.292893) + 1000));
            }
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
        public Geometry CreateGeometry(Direct2DFactory factory)
        {
            PathGeometry geometry = factory.CreatePathGeometry();

            using (GeometrySink sink = geometry.Open())
            {
                sink.BeginFigure(this._points[0], FigureBegin.Hollow);
                for (int index = 1; index < this._points.Length; ++index)
                    sink.AddLine(this._points[index]);
                sink.EndFigure(FigureEnd.Open);
                sink.Close();
            }
            return geometry;
            //List<Geometry> list = new List<Geometry>();
            //for (int index = 0; index < this.Count; ++index)
            //{
            //    EllipseGeometry ellipse = factory.CreateEllipseGeometry(new Ellipse(this[index], 5, 5));
            //    list.Add(ellipse);
            //}
            //return factory.CreateGeometryGroup(FillMode.Winding, list.ToArray());
        }

    }
}
