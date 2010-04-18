using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using Managed.Graphics.Direct2D;
using Managed.Graphics.DirectWrite;
using Managed.Graphics.Imaging;

namespace Managed.D2DSharp.SimpleText
{
    public class BitmapInlineObject: InlineObject
    {
        private Bitmap _bitmap;
        private InlineObjectMetrics metrics;
        private WindowRenderTarget _renderer;

        public BitmapInlineObject(WindowRenderTarget renderer, Bitmap bitmap)
        {
            this._renderer = renderer;
            this._bitmap = bitmap;
            SizeF size = this._bitmap.Size;

            this.metrics = new InlineObjectMetrics(size.Width, size.Height, size.Height * 2 / 3, false);
        }

        public override BreakCondition BreakConditionAfter
        {
            get { return BreakCondition.Neutral; }
        }

        public override BreakCondition BreakConditionBefore
        {
            get { return BreakCondition.Neutral; }
        }

        public override void Draw(ITextRenderer renderer, float originX, float originY, bool isSideways, bool isRtl, ClientDrawingEffect clientDrawingEffect)
        {
            SizeF size = this._bitmap.Size;
            this._renderer.DrawBitmap(this._bitmap, new RectF(originX, originY, size.Width, size.Height), 1, BitmapInterpolationMode.Linear);
        }

        public override InlineObjectMetrics Metrics
        {
            get 
            { 
                return metrics; 
            }
        }

        public override OverhangMetrics OverhangMetrics
        {
            get { return new OverhangMetrics(); }
        }
    }
}
