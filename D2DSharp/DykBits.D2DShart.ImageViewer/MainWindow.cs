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
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO;

namespace DykBits.D2DShart.ImageViewer
{
    public partial class MainWindow : Form
    {
        private string _path;
        private string[] _files;
        private int _currentImage;

        public MainWindow()
        {
            InitializeComponent();
        }

        private void buttonOpenFolder_Click(object sender, EventArgs e)
        {
            if (this.folderBrowserDialog1.ShowDialog() == DialogResult.OK)
            {
                this._path = this.folderBrowserDialog1.SelectedPath;
                Initialize();
            }
        }

        private void Initialize()
        {
            this._files = Directory.GetFiles(this._path);
            this._currentImage = 0;
            this.direct2DSurface1.ImagePath = this._files[this._currentImage];
        }

        private bool PrevImage()
        {
            try
            {
                if (this._files != null && this._files.Length > 0)
                {
                    this._currentImage = (this._currentImage - 1 + this._files.Length) % this._files.Length;
                    this.direct2DSurface1.ImagePath = this._files[this._currentImage];
                }
                return true;
            }
            catch
            {
                return false;
            }
        }

        private bool NextImage()
        {
            try
            {
                if (this._files != null && this._files.Length > 0)
                {
                    this._currentImage = (this._currentImage + 1) % this._files.Length;
                    this.direct2DSurface1.ImagePath = this._files[this._currentImage];
                }
                return true;
            }
            catch
            {
                return false;
            }
        }

        private void buttonPrev_Click(object sender, EventArgs e)
        {
            int saveImage = this._currentImage;
            for (; ; )
            {
                if (PrevImage())
                    break;
                if (saveImage == this._currentImage)
                    break;
            }
        }

        private void buttonNext_Click(object sender, EventArgs e)
        {
            int saveImage = this._currentImage;
            for (; ; )
            {
                if (NextImage())
                    break;
                if (saveImage == this._currentImage)
                    break;
            }
        }
    }
}
