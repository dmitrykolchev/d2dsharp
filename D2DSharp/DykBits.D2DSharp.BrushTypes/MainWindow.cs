/* 
* MainWindow.cs 
* 
* Authors: 
*  Dmitry Kolchev <dmitrykolchev@msn.com>
*  
* Copyright (C) 2010 Dmitry Kolchev
*
* This sourcecode is licenced under The GNU Lesser General Public License
* 
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
* OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN
* NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
* DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
* OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
* USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using Managed.Graphics.Direct2D;
using Managed.Graphics.DirectWrite;
using Managed.Graphics.Imaging;

namespace Managed.D2DSharp.BrushTypes
{
    public partial class MainWindow : Managed.Graphics.Forms.Direct2DWindow
    {
        private TextFormat _textFormat;
        private SolidColorBrush _blackBrush;
        private SolidColorBrush _yellowGreenBrush;
        private LinearGradientBrush _linearGradientBrush;
        private RadialGradientBrush _radialGradientBrush;
        private BitmapBrush _bitmapBrush;
        private BitmapBrush _gridPatternBrush;

        public MainWindow()
        {
            InitializeComponent();
        }

        protected override void OnCreateDeviceIndependentResources(Direct2DFactory factory)
        {
            base.OnCreateDeviceIndependentResources(factory);
            this._textFormat = DirectWriteFactory.CreateTextFormat("Verdana", null, FontWeight.Bold, FontStyle.Normal, FontStretch.Normal, 10.5f, "en-us");
            this._textFormat.ParagraphAlignment = ParagraphAlignment.Near;
            this._textFormat.TextAlignment = TextAlignment.Center;
        }

        protected override void OnCleanUpDeviceIndependentResources()
        {
            base.OnCleanUpDeviceIndependentResources();
            this._textFormat.Dispose();
        }

        protected override void OnCreateDeviceResources(WindowRenderTarget renderTarget)
        {
            base.OnCreateDeviceResources(renderTarget);
            this._blackBrush = renderTarget.CreateSolidColorBrush(Color.FromARGB(Colors.Black, 1));
            this._yellowGreenBrush = renderTarget.CreateSolidColorBrush(Color.FromARGB(0x9ACD32, 1));

            GradientStop[] stops = new GradientStop[] {
                new GradientStop(0, Color.FromARGB(Colors.Yellow, 1)),
                new GradientStop(1, Color.FromARGB(Colors.ForestGreen, 1))
            };

            using (GradientStopCollection collection = renderTarget.CreateGradientStopCollection(stops, Gamma.Gamma22, ExtendMode.Clamp))
            {
                this._linearGradientBrush = renderTarget.CreateLinearGradientBrush(
                    new LinearGradientBrushProperties(new PointF(0, 0), new PointF(150, 150)), 
                    BrushProperties.Default, 
                    collection);
                this._radialGradientBrush = renderTarget.CreateRadialGradientBrush(
                    new RadialGradientBrushProperties(new PointF(75, 75), new PointF(0, 0), 75, 75), 
                    BrushProperties.Default, 
                    collection);
            }

            using (Bitmap bitmap = RenderTarget.CreateBitmap(this.GetType(), "fern.jpg"))
            {
                this._bitmapBrush = renderTarget.CreateBitmapBrush(bitmap,
                    new BitmapBrushProperties(ExtendMode.Wrap, ExtendMode.Wrap, BitmapInterpolationMode.Linear),
                    BrushProperties.Default);
            }

            this._gridPatternBrush = renderTarget.CreateGridPatternBrush(new SizeF(10, 10), Color.FromARGB(1, 0.93f, 0.94f, 0.96f));
        }

        protected override void OnCleanUpDeviceResources()
        {
            base.OnCleanUpDeviceResources();
            this._blackBrush.Dispose();
            this._yellowGreenBrush.Dispose();
            this._linearGradientBrush.Dispose();
            this._radialGradientBrush.Dispose();
            this._bitmapBrush.Dispose();
            this._gridPatternBrush.Dispose();
        }

        protected override void OnRender(WindowRenderTarget renderTarget)
        {
            RectF bounds = new RectF(new PointF(), renderTarget.Size);
            renderTarget.FillRect(_gridPatternBrush, bounds);

            RectF brushRect = new RectF(0, 0, 150, 150);
            RectF textRect = new RectF(0, 165, 150, 35);
            renderTarget.Transform = Matrix3x2.Translation(new SizeF(5.5f, 5.5f));
            renderTarget.FillRect(_yellowGreenBrush, brushRect);
            renderTarget.DrawRect(_blackBrush, 1, brushRect);
            renderTarget.DrawText("SolidColorBrush", this._textFormat, textRect, this._blackBrush, DrawTextOptions.None, MeasuringMode.Natural);

            renderTarget.Transform = Matrix3x2.Translation(new SizeF(200.5f, 5.5f));
            renderTarget.FillRect(_linearGradientBrush, brushRect);
            renderTarget.DrawRect(_blackBrush, 1, brushRect);
            renderTarget.DrawText("LinearGradientBrush", this._textFormat, textRect, this._blackBrush, DrawTextOptions.None, MeasuringMode.Natural);

            renderTarget.Transform = Matrix3x2.Translation(new SizeF(5.5f, 200.5f));
            renderTarget.FillEllipse(_radialGradientBrush, new Ellipse(brushRect));
            renderTarget.DrawEllipse(_blackBrush, 1, new Ellipse(brushRect));
            renderTarget.DrawText("RadialGradientBrush", this._textFormat, textRect, this._blackBrush, DrawTextOptions.None, MeasuringMode.Natural);

            renderTarget.Transform = Matrix3x2.Translation(new SizeF(200.5f, 200.5f));
            renderTarget.FillRect(_bitmapBrush, brushRect);
            renderTarget.DrawRect(_blackBrush, 1, brushRect);
            renderTarget.DrawText("BitmapBrush", this._textFormat, textRect, this._blackBrush, DrawTextOptions.None, MeasuringMode.Natural);
        }
    }
}
