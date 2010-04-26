using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Managed.Graphics.DirectWrite;

namespace Managed.D2DSharp.DirectWrite.CustomFont
{
    class TextParagraph
    {
        public string Text { get; set; }
        public FontWeight Weight { get; set; }
        public float FontSize { get; set; }
        public string FontFamily { get; set; }
        public float SpaceBefore { get; set; }
        public float SpaceAfter { get; set; }
        public TextAlignment TextAlignment { get; set; }
        public float LineSpacing { get; set; }
    }
}
