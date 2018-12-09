using Managed.Graphics.Direct2D;
using Managed.Graphics.DirectWrite;
using Managed.Graphics.Forms;
using System;
using System.ComponentModel;

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
            _blackBrush = renderTarget.CreateSolidColorBrush(Color.FromKnown(Colors.Black, 1));
        }

        protected override void OnCleanUpDeviceResources()
        {
            base.OnCleanUpDeviceResources();
            _blackBrush.Dispose();
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
            get { return _bold; }
            set
            {
                _bold = value;
                OnPropertyChanged();
            }
        }

        [Browsable(false)]
        [DesignerSerializationVisibility(DesignerSerializationVisibility.Hidden)]
        public bool Italic
        {
            get { return _italic; }
            set
            {
                _italic = value;
                OnPropertyChanged();
            }
        }

        [Browsable(false)]
        [DesignerSerializationVisibility(DesignerSerializationVisibility.Hidden)]
        public bool Underline
        {
            get { return _underline; }
            set
            {
                _underline = value;
                OnPropertyChanged();
            }
        }

        [Browsable(false)]
        [DesignerSerializationVisibility(DesignerSerializationVisibility.Hidden)]
        public int FontSize
        {
            get { return _fontSize; }
            set
            {
                _fontSize = value;
                OnPropertyChanged();
            }
        }

        protected override void OnRender(WindowRenderTarget renderTarget)
        {
            if (_textLayout != null)
            {
                renderTarget.DrawTextLayout(new PointF(), _textLayout, _blackBrush, DrawTextOptions.None);
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
            if (_textLayout != null)
            {
                _textLayout.Dispose();
                _textLayout = null;
            }
            if (_textFormat != null)
            {
                _textFormat.Dispose();
                _textFormat = null;
            }
        }

        private void CreateResources()
        {
            _textFormat = DirectWriteFactory.CreateTextFormat(
                FontName,
                FontSize,
                Bold ? FontWeight.Bold : FontWeight.Normal,
                Italic ? FontStyle.Italic : FontStyle.Normal);
            _textFormat.ParagraphAlignment = ParagraphAlignment.Center;
            _textFormat.TextAlignment = TextAlignment.Center;

            float width = ClientSize.Width / dpiScaleX;
            float height = ClientSize.Height / dpiScaleY;

            _textLayout = DirectWriteFactory.CreateTextLayout(
                Text,
                _textFormat,
                width,
                height);
            if (Underline)
            {
                _textLayout.SetUnderline(true, new TextRange(0, Text.Length));
            }
        }

        protected override void OnResize(EventArgs e)
        {
            base.OnResize(e);
            if (_textLayout != null)
            {
                _textLayout.MaxWidth = ClientSize.Width / dpiScaleX;
                _textLayout.MaxHeight = ClientSize.Height / dpiScaleY;
            }
        }
    }
}
