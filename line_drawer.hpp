#ifndef IG_LINE_DRAWER_HPP
#define IG_LINE_DRAWER_HPP

#include <Windows.h>
#include <cmath>

namespace momiage
{
	class line_drawer
	{
	private:
		HDC m_hdc;

		unsigned char m_Red, m_Green, m_Blue;

		// ���W(x,y)�ɋP�x(brightness)�œ_���`��
		void plot(int x, int y, double brightness)
		{
			unsigned int color;
			double sr, sg, sb, dr, dg, db;
			unsigned short r, g, b;

			color = GetPixel(m_hdc, x, y);
			dr = (color & 255) * (1 - brightness);
			dg = ((color >> 8) & 255) * (1 - brightness);
			db = ((color >> 16) & 255) * (1 - brightness);

			sr = m_Red * brightness;
			sg = m_Green * brightness;
			sb = m_Blue * brightness;

			r = static_cast<short>(round(sr + dr));
			if (sr + dr > 255)
				r = 255;
			g = static_cast<short>(round(sg + dg));
			if (sg + dg > 255)
				g = 255;
			b = static_cast<short>(round(sb + db));
			if (sb + db > 255)
				b = 255;

			color = (b << 16) + (g << 8) + (r);

			//color = 0x0;
			//SetPixel(m_hdc, x, y, GetPixel(m_hdc, x, y) + color);
			SetPixel(m_hdc, x, y, color);
		}

		// double��int�ɃL���X�g? �����炭�����_�ȉ����؂��̂Ă����邱�Ƃ��d�v?
		// integer part of i
		int ipart(double i)
		{
			return static_cast<int>(i);
		}

		// ?
		// fractional part of r
		double fpart(double r)
		{
			if (r < 0.0)
				return 1 - (r - floor(r));
			return r - floor(r);
		}

		// ?
		double rfpart(double r)
		{
			return 1 - fpart(r);
		}

		// �����ւ�
		void swap(int &a, int &b)
		{
			if (a == b)
				return;
			a ^= b;
			b ^= a;
			a ^= b;
		}
		void swap(double &a, double &b)
		{
			if (a == b)
				return;
			double hoge = a;
			a = b;
			b = hoge;
		}

	public:

		// (x0,y0) ���� (x1,y1) �܂ł� RGB=(red,green,blue) �ł��钼���� hdc �ɕ`��
		void draw(HDC hdc, double x0, double y0, double x1, double y1, unsigned char red, unsigned char green, unsigned char blue)
		{
			m_hdc = hdc;

			m_Red = red;
			m_Green = green;
			m_Blue = blue;

			bool steep = std::abs(y1 - y0) > std::abs(x1 - x0);

			if (steep)
			{
				swap(x0, y0);
				swap(x1, y1);
			}
			if (x0 > x1)
			{
				swap(x0, x1);
				swap(y0, y1);
			}

			double dx, dy;
			dx = x1 - x0;
			dy = y1 - y0;

			double gradient;
			gradient = dy / dx;

			double xend, yend, xgap;

			// handle first endpoint
			xend = round(x0);
			yend = y0 + gradient * (xend - x0);
			xgap = rfpart(x0 + 0.5);
			int xpxl1, ypxl1;
			xpxl1 = static_cast<int>(xend);
			ypxl1 = ipart(yend);
			if (steep)
			{
				plot(ypxl1, xpxl1, rfpart(yend) * xgap);
				plot(ypxl1 + 1, xpxl1, fpart(yend) * xgap);
			}
			else
			{
				plot(xpxl1, ypxl1, rfpart(yend) * xgap);
				plot(xpxl1, ypxl1 + 1, fpart(yend) * xgap);
			}
			double intery = yend + gradient;

			// handle second endpoint
			xend = round(x1);
			yend = y1 + gradient * (xend - x1);
			xgap = fpart(x1 + 0.5);
			int xpxl2, ypxl2;
			xpxl2 = static_cast<int>(xend);
			ypxl2 = ipart(yend);
			if (steep)
			{
				plot(ypxl2, xpxl2, rfpart(yend) * xgap);
				plot(ypxl2 + 1, xpxl2, fpart(yend) * xgap);
			}
			else
			{
				plot(xpxl2, ypxl2, rfpart(yend) * xgap);
				plot(xpxl2, ypxl2 + 1, fpart(yend) * xgap);
			}

			// main loop
			if (steep)
			{
				for (int i = xpxl1 + 1; i <= xpxl2 - 1; ++i)
				{
					plot(ipart(intery), i, rfpart(intery));
					plot(ipart(intery) + 1, i, fpart(intery));
					intery += gradient;
				}
			}
			else
			{
				for (int i = xpxl1 + 1; i <= xpxl2 - 1; ++i)
				{
					plot(i, ipart(intery), rfpart(intery));
					plot(i, ipart(intery) + 1, fpart(intery));
					intery += gradient;
				}
			}
		}

	};
}

#endif
