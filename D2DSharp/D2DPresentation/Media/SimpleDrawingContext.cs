using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Managed.Graphics.Media
{
    class SimpleDrawingContext: DrawingContext
    {
        public override void DrawEllipse(Brush brush, Pen pen, Point center, float radiusX, float radiusY)
        {
            throw new NotImplementedException();
        }

        public override void DrawLine(Pen pen, Point p1, Point p2)
        {
            throw new NotImplementedException();
        }

        public override void DrawRectangele(Brush brush, Pen pen, Rect rect)
        {
            throw new NotImplementedException();
        }

        public override void DrawRoundedRectangle(Brush brush, Pen pen, Rect rect, float radiusX, float radiusY)
        {
            throw new NotImplementedException();
        }

        public override void DrawGeometry(Brush brush, Pen pen, Geometry geometry)
        {
            throw new NotImplementedException();
        }
    }
}
