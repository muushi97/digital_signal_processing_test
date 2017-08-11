// ここで windows10 であると指定
// 右のサイトにバージョンごとの値が乗ってる (https://msdn.microsoft.com/ja-jp/library/6sehtctf.aspx)
#define WINVER 0x0A00
#define _WIN32_WINNT 0x0A00

#define UNICODE

#include <windows.h>
#include <Commctrl.h>
#include <mmsystem.h>

#include <vector>
#include <complex>
#include <cmath>

#include "math_constant.hpp"

#include "signal.hpp"
#include "signal_generator.hpp"
#include "signal_processor.hpp"
#include "signal_writer.hpp"

#include "filter.hpp"
#include "filter_generator.hpp"

#include "line_drawer.hpp"

#include "graph.hpp"

class f_lags
{
private:

	int process(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		PAINTSTRUCT peint;
		HDC hdc;

		switch (uMsg)
		{
		case WM_PAINT:
			hdc = BeginPaint(hwnd, &peint);

			G->setDC(hdc);
			G->update(hoge);
			G->draw(hdc, 10, 10);

			EndPaint(hwnd, &peint);

			return 0;
		}
		return -114514;
	}

	momiage::signal hoge;

	momiage::signal c;
	momiage::signal c_;
	momiage::signal c_2;

	momiage::graph *G;
	void initialize()
	{
		G = new momiage::graph(1500, 300);

		momiage::generateCosWave(c, 1000 - 003, 0, 1000, 50);
		momiage::generateCosWave(c_, 1000 - 003, 0, 5, 50);

		for (int i = c.indexMin(); i <= c.indexMax(); ++i)
		{
			c[i] = c[i] + c_[i];
		}

		c_2.initialize(c.length(), (c.length() >> 1) * -1);
		momiage::DFT(c_2, c);

		hoge = c_2;
		G->setRange(hoge.indexMin() - 5.0, hoge.indexMax() + 5.0, -1.0 * hoge.maxAbs() - 5.0, hoge.maxAbs() + 5.0);

		momiage::signal_writer w;
		//w.write_real("cos_fr_100_1000-500.txt", c_2, c_2.indexMin(), -1);
		//w.write_imaginary("cos_fi_100_1000-500.txt", c_2, c_2.indexMin(), -1);


		G->setOrder(true);
	}

public:
	f_lags()
	{
		initialize();
	}

	static LRESULT CALLBACK SubclassProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
	{
		int result = ((f_lags *)dwRefData)->process(hwnd, uMsg, wParam, lParam);

		switch (uMsg)
		{
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		}

		if(result == -114514)
			return DefSubclassProc(hwnd, uMsg, wParam, lParam);

		return result;
	}
};

//�E�B���h�E�v���V�[�W��
LRESULT CALLBACK MomiageProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, msg, wp, lp);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, int nCmdShow)
{
	WNDCLASS wc;
	HWND hwnd;
	MSG msg;
	f_lags hata;

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = MomiageProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hCursor = NULL;
	wc.hIcon = NULL;
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszClassName = TEXT("momiage");
	wc.lpszMenuName = NULL;

	if (!RegisterClass(&wc))
		return -1;

	hwnd = CreateWindow(TEXT("momiage"), TEXT("���݂����H�ׂ���"), WS_VISIBLE | WS_SYSMENU | WS_CAPTION | WS_MINIMIZEBOX, CW_USEDEFAULT, CW_USEDEFAULT, 1600, 400, NULL, NULL, hInstance, NULL);

	if (hwnd == NULL)
		return 0;

	SetWindowSubclass(hwnd, hata.SubclassProc, 1, (DWORD_PTR)(&hata));

	while (GetMessage(&msg, NULL, 0, 0))
		DispatchMessage(&msg);

	return msg.wParam;
}
