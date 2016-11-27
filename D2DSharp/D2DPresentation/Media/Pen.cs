using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Managed.Graphics.Media
{
    public class Pen
    {
        private Brush _brush;
        private float _thickness;
        public Pen()
        {
        }
        public Pen(Brush brush, float thickness = 1.0f)
        {
            this._brush = brush;
            this._thickness = thickness;
        }
        public Brush Brush
        {
            get { return this._brush; }
            set { this._brush = value; }
        }
        public float Thickness
        {
            get { return this._thickness; }
            set
            {
                if (value <= 0)
                    throw new ArgumentOutOfRangeException("value");
                this._thickness = value;
            }
        }
    }
}
