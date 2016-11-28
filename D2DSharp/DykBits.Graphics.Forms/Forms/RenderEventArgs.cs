using Managed.Graphics.Direct2D;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Managed.Graphics.Forms
{
    public class RenderTargetEventArgs: EventArgs
    {
        private WindowRenderTarget _renderTarget;
        public RenderTargetEventArgs(WindowRenderTarget renderTarget)
        {
            _renderTarget = renderTarget;
        }
        public WindowRenderTarget RenderTarget
        {
            get { return _renderTarget; }
        }
    }
}
