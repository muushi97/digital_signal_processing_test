#ifndef IG_GRAPH_HPP
#define IG_GRAPH_HPP

#include <windows.h>
#include <mmsystem.h>
#pragma comment (lib, "winmm.lib")

#include "signal.hpp"
#include "line_drawer.hpp"

namespace momiage
{
	class graph
	{
	private:
		unsigned int m_XSize, m_YSize;

		HDC m_BackGraund;
		HBITMAP m_MemoryBM;
		HGDIOBJ m_OldBM_BG;

		double m_xMin, m_xMax, m_yMin, m_yMax;
		bool m_Order;

		bool m_DCflag;

	public:
		graph(unsigned int x_size, unsigned int y_size)
		{
			m_XSize = x_size;
			m_YSize = y_size;

			m_Order = true;

			m_DCflag = false;
		}
		graph(unsigned int x_size, unsigned int y_size, HDC hdc)
		{
			m_XSize = x_size;
			m_YSize = y_size;

			m_Order = true;

			m_BackGraund = CreateCompatibleDC(hdc);
			m_MemoryBM = CreateCompatibleBitmap(hdc, m_XSize, m_YSize);
			m_OldBM_BG = SelectObject(m_BackGraund, m_MemoryBM);
			m_DCflag = true;
		}

		void setSize(unsigned int x_size, unsigned int y_size)
		{
			m_XSize = x_size;
			m_YSize = y_size;
		}
		void setDC(HDC hdc)
		{
			if (m_DCflag)
			{
				SelectObject(m_BackGraund, m_OldBM_BG);
				DeleteObject(m_OldBM_BG);
				DeleteDC(m_BackGraund);
			}

			m_BackGraund = CreateCompatibleDC(hdc);
			m_MemoryBM = CreateCompatibleBitmap(hdc, m_XSize, m_YSize);
			m_OldBM_BG = SelectObject(m_BackGraund, m_MemoryBM);

			m_DCflag = true;
		}
		void setRange(double x_min, double x_max, double y_min, double y_max)
		{
			m_xMin = x_min;
			m_xMax = x_max;
			m_yMin = y_min;
			m_yMax = y_max;
		}
		void setOrder(bool Order)
		{
			m_Order = Order;
		}

		void update(const signal &data)
		{
			// �q�[�h������
			HPEN pen, hoge;
			HBRUSH brush;
			HGDIOBJ pen_, brush_;

			pen = CreatePen(PS_SOLID, 1, 0x000000);
			brush = CreateSolidBrush(0xffffff);

			pen_ = SelectObject(m_BackGraund, pen);
			brush_ = SelectObject(m_BackGraund, brush);

			Rectangle(m_BackGraund, 0, 0, m_XSize, m_YSize);

			SelectObject(m_BackGraund, pen_);
			SelectObject(m_BackGraund, brush_);

			DeleteObject(pen);
			DeleteObject(brush);

			// �O���t�`��
			int x, y;
			int x_n, y_n;

			double x_unit = (m_xMax - m_xMin) / static_cast<double>(m_XSize - 1);
			double y_unit = (m_yMax - m_yMin) / static_cast<double>(m_YSize - 1);

			x_unit = 1 / x_unit;
			y_unit = 1 / y_unit;

			x_unit = x_unit > 0 ? x_unit : x_unit * -1;
			y_unit = y_unit < 0 ? y_unit : y_unit * -1;

			double x_b = m_xMin * x_unit * -1.0;
			double y_b = m_yMax * y_unit * -1.0;

			line_drawer writer;

			for (int i = data.indexMin(); i + 1 <= data.indexMax(); ++i)
			{
				x = static_cast<int>(round(i * x_unit + x_b));
				x_n = static_cast<int>(round((i + 1) * x_unit + x_b));

				if (!m_Order)
				{
					y = (data[i].real() * y_unit) + y_b;
					y_n = (data[i + 1].real() * y_unit) + y_b;
					writer.draw(m_BackGraund, x, y, x_n, y_n, 000, 128, 000);

					y = (data[i].imag() * y_unit) + y_b;
					y_n = (data[i + 1].imag() * y_unit) + y_b;
					writer.draw(m_BackGraund, x, y, x_n, y_n, 128, 000, 000);
				}
				else
				{
					y = (data[i].imag() * y_unit) + y_b;
					y_n = (data[i + 1].imag() * y_unit) + y_b;
					writer.draw(m_BackGraund, x, y, x_n, y_n, 128, 000, 000);

					y = (data[i].real() * y_unit) + y_b;
					y_n = (data[i + 1].real() * y_unit) + y_b;
					writer.draw(m_BackGraund, x, y, x_n, y_n, 000, 128, 000);
				}
			}
		}

		void update(const signal &data, double x_min, double x_max, double y_min, double y_max, bool Order)
		{
			setRange(x_min, x_max, y_min, y_max);
			setOrder(m_Order);

			update(data);
		}

		void draw(HDC hdc, int x_position, int y_position)
		{
			BitBlt(hdc, x_position, y_position, m_XSize, m_YSize, m_BackGraund, 0, 0, SRCCOPY);
		}

		~graph()
		{
			SelectObject(m_BackGraund, m_OldBM_BG);
			DeleteObject(m_OldBM_BG);
			DeleteDC(m_BackGraund);
		}
	};
}

#endif
