using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Managed.D2DSharp.Math;
using Managed.Graphics.Direct2D;
using System.Diagnostics;

namespace Managed.D2DSharp.Math
{
    class Program
    {
        static void Main(string[] args)
        {
            Matrix4x4 m1 = Matrix4x4.RotationX(100);
            Matrix4x4 m2 = Matrix4x4.RotationY(45);
            // warm up
            {
                Matrix4x4 m4 = new Matrix4x4();
                for (int index = 0; index < 10000000; ++index)
                {
                    m4.SetProduct(m1, m2);
                }
            }
            {
                Stopwatch stopwatch = new Stopwatch();
                stopwatch.Start();

                Matrix4x4 m4 = new Matrix4x4();
                for (int index = 0; index < 10000000; ++index)
                {
                    m2.SetProduct(m2, m2);
                    m1.SetProduct(m1, m1);
                    m4.SetProduct(m1, m2);
                }
                stopwatch.Stop();
                Console.WriteLine("Elapsed time: {0} ms", stopwatch.ElapsedMilliseconds);
            }
        }
    }
}
