using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Managed.Graphics.Direct2D;
using Managed.Graphics.DirectWrite;

namespace Managed.D2DSharp.SimpleText
{
    public class ColorDrawingEffect: ClientDrawingEffect
    {
        private Color _color;

        public ColorDrawingEffect(Color color)
        {
            this._color = color;    
        }

        public Color Color
        {
            get { return _color; }
        }
    }
}
