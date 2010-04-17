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
using Managed.Graphics.Forms;
using Managed.Graphics.Direct2D;
using Managed.Graphics.DirectWrite;
using Managed.Graphics.Imaging;

namespace Managed.D2DSharp.ClipWithLayers
{
    public partial class MainWindow : Direct2DWindow
    {
        private PathGeometry _pathGeometry;
        private Bitmap _bitmap;
        private BitmapBrush _gridPatternBrush;
        private SolidColorBrush _brush;

        public MainWindow()
        {
            InitializeComponent();
        }

        protected override void OnCreateDeviceIndependentResources(Direct2DFactory factory)
        {
            base.OnCreateDeviceIndependentResources(factory);
            this._pathGeometry = factory.CreatePathGeometry();
            using (GeometrySink sink = this._pathGeometry.Open())
            {
                sink.SetFillMode(FillMode.Winding);
                sink.BeginFigure(new PointF(20, 50), FigureBegin.Filled);
                sink.AddLine(new PointF(130, 50));
                sink.AddLine(new PointF(20, 130));
                sink.AddLine(new PointF(80, 0));
                sink.AddLine(new PointF(130, 130));
                sink.EndFigure(FigureEnd.Closed);
                sink.Close();
            }
        }

        protected override void OnCleanUpDeviceIndependentResources()
        {
            base.OnCleanUpDeviceIndependentResources();
            this._pathGeometry.Dispose();
        }

        protected override void OnCreateDeviceResources(WindowRenderTarget renderTarget)
        {
            base.OnCreateDeviceResources(renderTarget);
            this._bitmap = renderTarget.CreateBitmap(this.GetType(), "fern.jpg");
            this._brush = renderTarget.CreateSolidColorBrush(Color.FromARGB(Colors.Orange, 1));
            this._brush.Opacity = 0.75f;
            this._gridPatternBrush = renderTarget.CreateGridPatternBrush(new SizeF(10, 10), Color.FromARGB(1, 0.93f, 0.94f, 0.96f));
        }

        protected override void OnCleanUpDeviceResources()
        {
            base.OnCleanUpDeviceResources();
            this._bitmap.Dispose();
            this._brush.Dispose();
            this._gridPatternBrush.Dispose();
        }

        protected override void OnRender(WindowRenderTarget renderTarget)
        {
            RectF bounds = new RectF(new PointF(), renderTarget.Size);
            renderTarget.FillRect(_gridPatternBrush, bounds);

            renderTarget.Transform = Matrix3x2.Translation(50, 50);
            RenderScene(renderTarget);
            RenderWithLayer(renderTarget);
        }

        private void RenderScene(WindowRenderTarget renderTarget)
        {
            renderTarget.DrawBitmap(_bitmap, new RectF(0, 0, 200, 133), 1, BitmapInterpolationMode.Linear);
            renderTarget.FillRect(_brush, new RectF(0, 0, 25, 25));
            renderTarget.FillRect(_brush, new RectF(25, 25, 25, 25));
            renderTarget.FillRect(_brush, new RectF(50, 50, 25, 25));
            renderTarget.FillRect(_brush, new RectF(75, 75, 25, 25));
            renderTarget.FillRect(_brush, new RectF(100, 100, 25, 25));
            renderTarget.FillRect(_brush, new RectF(125, 125, 25, 25));
        }

        private void RenderWithLayer(WindowRenderTarget renderTarget)
        {
            using (Layer layer = renderTarget.CreateLayer())
            {
                renderTarget.Transform = Matrix3x2.Translation(350, 50);
                LayerParameters layerParameters = new LayerParameters { Bounds = RectF.Infinite, Mask = this._pathGeometry };
                renderTarget.PushLayer(layerParameters, layer);

                RenderScene(renderTarget);

                renderTarget.PopLayer();
            }
        }
    }
}
