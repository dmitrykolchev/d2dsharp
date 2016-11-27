using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Managed.Graphics
{
    public struct Point
    {
        internal float _x;
        internal float _y;
        public Point(float x, float y)
        {
            this._x = x;
            this._y = y;
        }
        public float X
        {
            get { return this._x; }
            set { this._x = value; }
        }
        public float Y
        {
            get { return this._y; }
            set { this._y = value; }
        }
        public static bool operator ==(Point p1, Point p2)
        {
            return p1.X == p2.X && p1.Y == p2.Y;
        }
        public static bool operator !=(Point p1, Point p2)
        {
            return p1.X != p2.X || p1.Y != p2.Y;
        }
        public static bool Equals(Point p1, Point p2)
        {
            return p1.X.Equals(p2.X) && p1.Y.Equals(p2.Y);
        }
        public override bool Equals(object o)
        {
            if (o == null || !(o is Point))
                return false;
            return Equals(this, (Point)o);
        }
        public bool Equals(Point value)
        {
            return Equals(this, value);
        }
        public override int GetHashCode()
        {
            return this.X.GetHashCode() ^ this.Y.GetHashCode();
        }
    }
}
