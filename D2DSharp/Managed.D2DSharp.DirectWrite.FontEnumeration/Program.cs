using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Globalization;
using Managed.Graphics.DirectWrite;

namespace Managed.D2DSharp.DirectWrite.FontEnumeration
{
    class Program
    {
        static void Main(string[] args)
        {
            List<string> fonts = new List<string>();
            using (DirectWriteFactory factory = DirectWriteFactory.Create(DirectWriteFactoryType.Shared))
            {
                using (FontCollection fontCollection = factory.GetSystemFontCollection(false))
                {
                    for (int index = 0; index < fontCollection.Count; ++index)
                    {
                        using (FontFamily fontFamily = fontCollection[index])
                        {
                            using (LocalizedStrings names = fontFamily.FamilyNames)
                            {
                                int cultureIndex = names.FindCulture(CultureInfo.CurrentUICulture);
                                if(cultureIndex < 0)
                                {
                                    cultureIndex = names.FindCulture(new CultureInfo("en-us"));
                                }
                                fonts.Add(names[cultureIndex]);
                            }
                        }
                    }
                }
            }
            fonts.Sort();
            foreach (string fontName in fonts)
            {
                Console.WriteLine(fontName);
            }
        }
    }
}
