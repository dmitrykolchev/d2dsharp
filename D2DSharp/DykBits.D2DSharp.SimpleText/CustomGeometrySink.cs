using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Managed.Graphics.Direct2D;

namespace Managed.D2DSharp.SimpleText
{
    class CustomGeometrySink: ICustomGeometrySink
    {
        StringBuilder _buffer;

        public CustomGeometrySink()
        {
            _buffer = new StringBuilder();
        }

        public override string ToString()
        {
            return _buffer.ToString();
        }

        #region ICustomGeometrySink Members

        public void AddArc(ArcSegment arc)
        {
            _buffer.AppendFormat("A {0},{1} {2},{3} ",
                arc.Size.Width, arc.Size.Height,
                arc.RotationAngle,
                (int)arc.ArcSize,
                (int)arc.SweepDirection,
                arc.Point.X, arc.Point.Y);
        }

        public void AddBezier(BezierSegment bezier)
        {
            _buffer.AppendFormat("C {0},{1} {2},{3} {4},{5} ",
                bezier.Point1.X, bezier.Point1.Y,
                bezier.Point2.X, bezier.Point2.Y,
                bezier.Point3.X, bezier.Point3.Y);
        }

        public void AddLine(PointF point)
        {
            _buffer.AppendFormat("L {0},{1} ", point.X, point.Y);
        }

        public void AddQuadraticBezier(QuadraticBezierSegment bezier)
        {
            _buffer.AppendFormat("Q {0},{1} {2},{3} ",
                bezier.Point1.X, bezier.Point1.Y,
                bezier.Point2.X, bezier.Point2.Y);
        }

        public void AddQuadraticBeziers(QuadraticBezierSegment[] beziers)
        {
            for (int index = 0; index < beziers.Length; ++index)
            {
                AddQuadraticBezier(beziers[index]);
            }
        }

        #endregion

        #region ICustomSimplifiedGeometrySink Members

        public void AddBeziers(BezierSegment[] beziers)
        {
            for (int index = 0; index < beziers.Length; ++index)
            {
                AddBezier(beziers[index]);
            }
        }

        public void AddLines(PointF[] points)
        {
            for (int index = 0; index < points.Length; ++index)
            {
                AddLine(points[index]);
            }
        }

        public void BeginFigure(PointF startPoint, FigureBegin figureBegin)
        {
            this._buffer.AppendFormat("M {0},{1} ", startPoint.X, startPoint.Y);
        }

        public void Close()
        {
            string text = this._buffer.ToString();
        }

        public void EndFigure(FigureEnd figureEnd)
        {
            if(figureEnd == FigureEnd.Closed)
                this._buffer.Append("Z ");
        }

        public void SetFillMode(FillMode fillMode)
        {
            this._buffer.AppendFormat("F{0} ", (int)fillMode);            
        }

        public void SetSegmentFlags(PathSegment vertexFlags)
        {
            
        }

        #endregion
    }
}
