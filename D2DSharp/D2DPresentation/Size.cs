using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Managed.Graphics
{
    public struct Size
    {
        internal float _width;
        internal float _height;
        public Size(float width, float height)
        {
            this._width = width;
            this._height = height;
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
    }
}
