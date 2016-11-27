using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using Managed.Graphics.Forms;
using Managed.Graphics.Direct2D;

namespace Managed.Graphics
{
    public partial class MainWindow : Direct2DWindow
    {
        public MainWindow()
        {
            InitializeComponent();
        }
        SolidColorBrush _brush;
        protected override void OnRender(WindowRenderTarget renderTarget)
        {
            renderTarget.FillEllipse(this._brush, new Ellipse(ClientSize.Width / 2, ClientSize.Height / 2, ClientSize.Width / 2, ClientSize.Height / 2));
        }

        protected override void OnCreateDeviceResources(WindowRenderTarget renderTarget)
        {
            base.OnCreateDeviceResources(renderTarget);
            this._brush = renderTarget.CreateSolidColorBrush(Color.FromKnown(Colors.Bisque, 1));
        }

        protected override void OnCleanUpDeviceResources()
        {
            base.OnCleanUpDeviceResources();
            SafeDispose(ref this._brush);
        }
    }
}
