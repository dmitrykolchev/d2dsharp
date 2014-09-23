/*
* D2DNative.h
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

	void WINAPI DxColorRgbToHsl(const FLOAT* rgb, FLOAT* hsl);
	void WINAPI DxColorHslToRgb(const FLOAT* hsl, FLOAT* rgb);

	void WINAPI DxColorRgbToHsv(const FLOAT* rgb, FLOAT* hsv);
	void WINAPI DxColorHsvToRgb(const FLOAT* hsv, FLOAT* rgb);

	void WINAPI DxColorRgbToXyz(const FLOAT* rgb, FLOAT* xyz);
	void WINAPI DxColorXyzToRgb(const FLOAT* xyz, FLOAT* rgb);

	void WINAPI DxColorRgbToYuv(const FLOAT* rgb, FLOAT* yuv);
	void WINAPI DxColorYuvToRgb(const FLOAT* yuv, FLOAT* rgb);
