using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using D2D = Managed.Graphics.Direct2D;

namespace Managed.Graphics.Media
{
    public abstract class DrawingContext
    {

        public abstract void DrawEllipse(Brush brush, Pen pen, Point center, float radiusX, float radiusY);
        public abstract void DrawLine(Pen pen, Point p1, Point p2);
        public abstract void DrawRectangele(Brush brush, Pen pen, Rect rect);
        public abstract void DrawRoundedRectangle(Brush brush, Pen pen, Rect rect, float radiusX, float radiusY);
        public abstract void DrawGeometry(Brush brush, Pen pen, Geometry geometry);
    }
}
