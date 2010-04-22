using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Managed.Graphics.DirectWrite;

namespace Managed.D2DSharp.DirectWrite.CustomLayout
{
    class MyTextSink: TextAnalysisSink
    {
        public override void SetBidiLevel(uint textPosition, uint textLength, byte explicitLevel, byte resolvedLevel)
        {
            throw new NotImplementedException();
        }

        public override void SetLineBreakpoints(uint textPosition, uint textLength, LineBreakpoint lineBreakPoints)
        {
            //throw new NotImplementedException();
        }

        public override void SetNumberSubstitution(uint textPosition, uint textLength, NumberSubstitution numberSubstitution)
        {
            throw new NotImplementedException();
        }

        public override void SetScriptAnalysis(uint textPosition, uint textLength, ScriptAnalysis scriptAnalysis)
        {
            throw new NotImplementedException();
        }
    }
}
