using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Managed.Graphics.DirectWrite;
using Managed.Graphics.Direct2D;

namespace Managed.D2DSharp.SimpleText
{
    class CustomTextRenderer : ITextRenderer
    {
        private Direct2DFactory _factory;
        private WindowRenderTarget _renderTarget;
        private SolidColorBrush _outlineBrush;
        private BitmapBrush _fillBrush;

        public CustomTextRenderer(Direct2DFactory factory, WindowRenderTarget renderTarget, SolidColorBrush outlineBrush, BitmapBrush fillBrush)
        {
            _factory = factory;
            _renderTarget = renderTarget;
            _outlineBrush = outlineBrush;
            _fillBrush = fillBrush;
        }

        #region ITextRenderer Members

        public Matrix3x2 CurrentTransform
        {
            get { return _renderTarget.Transform; }
        }

        public void DrawGlyphRun(float baselineOriginX, float baselineOriginY, Graphics.Direct2D.MeasuringMode measuringMode, GlyphRun glyphRun, GlyphRunDescription glyphRunDescription, object clientDrawingEffect)
        {
            using (PathGeometry pathGeometry = _factory.CreatePathGeometry())
            {

                using (GeometrySink sink = pathGeometry.Open())
                {
                    glyphRun.FontFace.GetGlyphRunOutline(
                        glyphRun.EmSize,
                        glyphRun.GlyphIndices,
                        glyphRun.GlyphAdvances,
                        glyphRun.GlyphOffsets,
                        glyphRun.IsSideways,
                        glyphRun.BidiLevel != 0,
                        sink);
                    sink.Close();
                }
                
                CustomGeometrySink customSink = new CustomGeometrySink();
                pathGeometry.Stream(customSink);
                customSink.Close();
                System.Diagnostics.Debug.WriteLine(customSink.ToString());

                Matrix3x2 matrix = new Matrix3x2(1, 0, 0, 1, baselineOriginX, baselineOriginY);
                using (TransformedGeometry transformedGeometry = _factory.CreateTransformedGeometry(pathGeometry, matrix))
                {
                    _renderTarget.DrawGeometry(_outlineBrush, 5, transformedGeometry);
                    _renderTarget.FillGeometry(_fillBrush, transformedGeometry);
                }
            }
        }

        public void DrawInlineObject(float originX, float originY, InlineObject inlineObject, bool isSideways, bool isRightToLeft, object clientDrawingEffect)
        {
            throw new NotImplementedException();
        }

        public void DrawStrikethrough(float baselineOriginX, float baselineOriginY, Strikethrough strikethrough, object clientDrawingEffect)
        {
            throw new NotImplementedException();
        }

        public void DrawUnderline(float baselineOriginX, float baselineOriginY, Underline underline, object clientDrawingEffect)
        {
            RectF rect = new RectF(0, underline.Offset, underline.Width, underline.Thickness);
            using (RectangleGeometry rectangleGeometry = _factory.CreateRectangleGeometry(rect))
            {
                Matrix3x2 matrix = new Matrix3x2(1, 0, 0, 1, baselineOriginX, baselineOriginY);
                using (TransformedGeometry transformedGeometry = _factory.CreateTransformedGeometry(rectangleGeometry, matrix))
                {
                    _renderTarget.DrawGeometry(_outlineBrush, 5, transformedGeometry);
                    _renderTarget.FillGeometry(_fillBrush, transformedGeometry);
                }
            }
        }

        public bool IsPixelSnappingDisabled
        {
            get { return false; }
        }

        public float PixelsPerDip
        {
            get
            {
                return _renderTarget.DpiX / 96;
            }
        }

        #endregion
    }
}
