using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using Managed.Graphics.Direct2D;
using Managed.Graphics.DirectWrite;
using Managed.Graphics.Forms;

namespace Managed.D2DSharp.DirectWrite.TextDialog
{
    public partial class SampleTextControl : Direct2DControl
    {
        private static float dpiScaleX;
        private static float dpiScaleY;

        static SampleTextControl()
        {
            DirectWriteFactory.GetDpiScale(out dpiScaleX, out dpiScaleY);
        }

        private string _fontName = "Arial";
        private bool _bold;
        private bool _italic;
        private bool _underline;
        private int _fontSize = 72;
        private string _text = "Formatted Text";

        private TextFormat _textFormat;
        private TextLayout _textLayout;
        private SolidColorBrush _blackBrush;

        public SampleTextControl()
        {
            InitializeComponent();
        }

        protected override void OnCreateDeviceIndependentResources(Direct2DFactory factory)
        {
            base.OnCreateDeviceIndependentResources(factory);
            CreateResources();
        }

        protected override void OnCleanUpDeviceIndependentResources()
        {
            base.OnCleanUpDeviceIndependentResources();
            CleanUpResources();
        }

        protected override void OnCreateDeviceResources(WindowRenderTarget renderTarget)
        {
            base.OnCreateDeviceResources(renderTarget);
            this._blackBrush = renderTarget.CreateSolidColorBrush(Color.FromKnown(Colors.Black, 1));
        }

        protected override void OnCleanUpDeviceResources()
        {
            base.OnCleanUpDeviceResources();
            this._blackBrush.Dispose();
        }

        [Browsable(false)]
        [DesignerSerializationVisibility(DesignerSerializationVisibility.Hidden)]
        public override string Text
        {
            get
            {
                return _text;
            }
            set
            {
                _text = value ?? string.Empty;
                OnPropertyChanged();
            }
        }

        [Browsable(false)]
        [DesignerSerializationVisibility(DesignerSerializationVisibility.Hidden)]
        public string FontName
        {
            get { return _fontName; }
            set
            {
                _fontName = value;
                OnPropertyChanged();
            }
        }

        [Browsable(false)]
        [DesignerSerializationVisibility(DesignerSerializationVisibility.Hidden)]
        public bool Bold
        {
            get { return this._bold; }
            set
            {
                this._bold = value;
                OnPropertyChanged();
            }
        }

        [Browsable(false)]
        [DesignerSerializationVisibility(DesignerSerializationVisibility.Hidden)]
        public bool Italic
        {
            get { return this._italic; }
            set
            {
                this._italic = value;
                OnPropertyChanged();
            }
        }

        [Browsable(false)]
        [DesignerSerializationVisibility(DesignerSerializationVisibility.Hidden)]
        public bool Underline
        {
            get { return this._underline; }
            set
            {
                this._underline = value;
                OnPropertyChanged();
            }
        }

        [Browsable(false)]
        [DesignerSerializationVisibility(DesignerSerializationVisibility.Hidden)]
        public int FontSize
        {
            get { return this._fontSize; }
            set
            {
                this._fontSize = value;
                OnPropertyChanged();
            }
        }

        protected override void OnRender(WindowRenderTarget renderTarget)
        {
            if (this._textLayout != null)
            {
                renderTarget.DrawTextLayout(new PointF(), this._textLayout, _blackBrush, DrawTextOptions.None);
            }
        }

        private void OnPropertyChanged()
        {
            CleanUpResources();
            CreateResources();
            Invalidate();
        }

        private void CleanUpResources()
        {
            if (this._textLayout != null)
            {
                this._textLayout.Dispose();
                this._textLayout = null;
            }
            if (this._textFormat != null)
            {
                this._textFormat.Dispose();
                this._textFormat = null;
            }
        }

        private void CreateResources()
        {
            this._textFormat = DirectWriteFactory.CreateTextFormat(
                FontName,
                Bold ? FontWeight.Bold : FontWeight.Normal,
                Italic ? FontStyle.Italic : FontStyle.Normal,
                FontSize);
            this._textFormat.ParagraphAlignment = ParagraphAlignment.Center;
            this._textFormat.TextAlignment = TextAlignment.Center;

            float width = ClientSize.Width / dpiScaleX;
            float height = ClientSize.Height / dpiScaleY;

            this._textLayout = DirectWriteFactory.CreateTextLayout(
                Text,
                _textFormat,
                width,
                height);
            if (Underline)
                this._textLayout.SetUnderline(true, new TextRange(0, Text.Length));
        }

        protected override void OnResize(EventArgs e)
        {
            base.OnResize(e);
            if (this._textLayout != null)
            {
                this._textLayout.MaxWidth = ClientSize.Width / dpiScaleX;
                this._textLayout.MaxHeight = ClientSize.Height / dpiScaleY;
            }
        }
    }
}
