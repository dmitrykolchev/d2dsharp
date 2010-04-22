using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Managed.Graphics.DirectWrite;

namespace Managed.D2DSharp.DirectWrite.CustomLayout
{
    class MyTextSource : TextAnalysisSource
    {
        private string _text;

        public MyTextSource(string text)
            : base(text)
        {
            _text = text;
        }

        public override System.Globalization.CultureInfo GetCulture(uint textPosition, out uint textLength)
        {
            textLength = (uint)_text.Length;
            return System.Globalization.CultureInfo.CurrentUICulture;
        }

        public override NumberSubstitution GetNumberSubstitution(uint textPosition, out uint textLength)
        {
            throw new NotImplementedException();
        }

        protected override void OnSetBidiLevel(uint textPosition, uint textLength, byte explicitLevel, byte resolvedLevel)
        {
            base.OnSetBidiLevel(textPosition, textLength, explicitLevel, resolvedLevel);
        }

        protected override void OnSetLineBreakpoints(uint textPosition, uint textLength, LineBreakpoint lineBreakPoints)
        {
            base.OnSetLineBreakpoints(textPosition, textLength, lineBreakPoints);
        }

        protected override void OnSetNumberSubstitution(uint textPosition, uint textLength, NumberSubstitution numberSubstitution)
        {
            base.OnSetNumberSubstitution(textPosition, textLength, numberSubstitution);
        }

        protected override void OnSetScriptAnalysis(uint textPosition, uint textLength, ScriptAnalysis scriptAnalysis)
        {
            base.OnSetScriptAnalysis(textPosition, textLength, scriptAnalysis);
        }
    }
}
