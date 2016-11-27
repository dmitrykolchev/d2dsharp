using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Managed.Graphics
{
    public struct Rect
    {
        internal float _x;
        internal float _y;
        internal float _width;
        internal float _height;
        public Rect(float x, float y, float width, float height)
        {
            this._x = x;
            this._y = y;
            this._width = width;
            this._height = height;
        }
        public Rect(Point location, Size size)
        {
            this._x = location.X;
            this._y = location.Y;
            this._width = size.Width;
            this._height = size.Height;
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
        public float Width
        {
            get { return this._width; }
            set { this._width = value; }
        }
        public float Height
        {
            get { return this._height; }
            set { this._height = value; }
        }
        public float Left
        {
            get { return this.X; }
        }
        public float Top
        {
            get { return this.Y; }
        }
        public float Right
        {
            get { return this.X + this.Width; }
        }
        public float Bottom
        {
            get { return this.Y + this.Height; }
        }
        public Point Location
        {
            get { return new Point(this.X, this.Y); }
            set
            {
                this._x = value.X;
                this._y = value.Y;
            }
        }
        public Size Size
        {
            get { return new Size(this.Width, this.Height); }
            set
            {
                this._width = value.Width;
                this._height = value.Height;
            }
        }
    }
}
