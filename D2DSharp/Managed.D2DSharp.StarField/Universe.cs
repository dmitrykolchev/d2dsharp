/* 
* Universe.cs
* 
* Authors: 
*  Dmitry Kolchev <dmitrykolchev@msn.com>
*  
* Copyright (C) 2014 Dmitry Kolchev
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
using Managed.Graphics;
using Managed.Graphics.Direct2D;
using System;
using System.Linq;

namespace Managed.D2DSharp.StarField
{
    public class Star
    {
        public Vector4 Location { get; set; }
        public float Radius { get; set; }
    }

    internal class Universe
    {
        private Star[] _stars;
        public Universe()
        {
            Transform = Matrix4x4.Identity;
        }
        public void Genrate(int count, float minX, float maxX, float minY, float maxY, float minZ, float maxZ)
        {
            Random random = new Random();
            _stars = new Star[count];
            for (int index = 0; index < count; ++index)
            {
                _stars[index] = new Star
                {
                    Location = new Vector4(
                        (float)(minX + random.NextDouble() * (maxX - minX)),
                        (float)(minY + random.NextDouble() * (maxY - minY)),
                        (float)(minZ + random.NextDouble() * (maxZ - minZ)),
                        1),
                    Radius = (float)(5 + random.NextDouble() * 10)
                };
            }
            _stars = _stars.OrderByDescending(t => t.Location.Z).ToArray();
        }
        public float PointOfView { get; set; }
        public SizeF ViewPortSize { get; set; }
        public Matrix4x4 Transform { get; set; }
        public Nullable<PointF> Project(Vector4 p)
        {
            Vector4 s = p;
            p = p * Transform;
            if (p.Z < PointOfView)
            {
                return null;
            }

            double t = -PointOfView / (p.Z - PointOfView);
            double x = p.X * t + ViewPortSize.Width / 2;
            double y = p.Y * t + ViewPortSize.Height / 2;
            return new PointF((float)x, (float)y);
        }
        public void Render(RenderTarget target)
        {
            Direct2DFactory factory = target.GetFactory();
            Color red = Color.FromRGB(128, 64, 64);
            Color white = Color.FromRGB(255, 255, 255);

            foreach (var star in _stars)
            {
                Vector4 location = star.Location;
                Nullable<PointF> locN = Project(location);
                if (locN != null)
                {
                    location = location * Transform;
                    PointF locV = locN.Value;
                    double r = Math.Sqrt(location.X * location.X + location.Y * location.Y + (location.Z - PointOfView) * (location.Z - PointOfView));
                    double rv = Math.Sqrt(locV.X * locV.X + locV.Y * locV.Y + PointOfView * PointOfView);
                    double k = (rv / r);
                    k = k > 1 ? 1 : (k < 0 ? 0 : k);
                    float radius = (float)(star.Radius * rv / r);
                    if (radius > 0.5f)
                    {
                        if (locV.X > 0 && locV.X < ViewPortSize.Width && locV.Y > 0 && locV.Y < ViewPortSize.Height)
                        {
                            using (EllipseGeometry ellipse = factory.CreateEllipseGeometry(new Ellipse(locV, radius, radius)))
                            {
                                float hue = (float)k;
                                Vector4 color = new Vector4((hue + 0.45f) % 1, 1f, 0.5f, 1);
                                Color rgb = XMath.ColorHslToRgb(color);
                                Color w = white.AdjustBrightness((float)Math.Sqrt(k));
                                rgb = Color.Lerp(w, rgb, (float)k);
                                if (radius > 3)
                                {
                                    Color rgb2 = rgb.AdjustBrightness(0.2f);
                                    using (GradientStopCollection coll = target.CreateGradientStopCollection(new GradientStop[] { new GradientStop(0, rgb), new GradientStop(1, rgb2) }))
                                    {
                                        using (Brush brush = target.CreateRadialGradientBrush(new RadialGradientBrushProperties(locV, new PointF(radius / 22f, -radius / 2f), radius, radius),
                                            new BrushProperties(1, Matrix3x2.Identity), coll))
                                        {
                                            target.FillGeometry(brush, ellipse);
                                        }
                                    }
                                }
                                else
                                {
                                    using (SolidColorBrush brush = target.CreateSolidColorBrush(rgb))
                                    {
                                        target.FillGeometry(brush, ellipse);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
