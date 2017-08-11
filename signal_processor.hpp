#ifndef IG_SIGNAL_PROCESSOR_HPP
#define IG_SIGNAL_PROCESSOR_HPP

#include "math_constant.hpp"
#include "signal.hpp"

namespace momiage
{
	// data �̍ŏ� length �T���v���ԂŃt�F�[�h�C��������
	void fadeIn(signal &data, unsigned int length)
	{
		double a = 1.0 / static_cast<double>(length);

		for (unsigned int i = 0; i < length; ++i)
		{
			data[data.indexMin() + i] *= i * a;
		}
	}

	// data �̍Ō� length �T���v���ԂŃt�F�[�h�A�E�g������
	void fadeOut(signal &data, unsigned int length)
	{
		double a = -1.0 / static_cast<double>(length - 1);

		unsigned int starting_position = data.indexMax() - length + 1;

		for (unsigned int i = 0; i < length; ++i)
		{
			data[starting_position + i] *= i * a + 1;
		}
	}

	// ���U�t�[���G�ϊ� (destination �� source �𗣎U�t�[���G�ϊ��������̂����������Ddestination �̐M���������`�擙�͕ύX�����Ȃ�)
	void DFT(signal &destination, signal &source)
	{
		double N = static_cast<double>(source.length());

		std::complex<double> temp;

		for (int t = destination.indexMin(); t <= destination.indexMax(); ++t)
		{
			destination[t] = 0.0;
			for (int x = source.indexMin(); x <= source.indexMax(); ++x)
			{
				destination[t] += source[x] * exp(std::complex<double>(0.0, -1.0 * PI_2 * static_cast<double>(t * x) / N));
			}
		}
	}

	// �t���U�t�[���G�ϊ� (destination �� source �𗣎U�t�[���G�ϊ��������̂����������Ddestination �̐M���������`�擙�͕ύX�����Ȃ�)
	void IDFT(signal &destination, signal &source)
	{
		double N = static_cast<double>(source.length());

		std::complex<double> temp;

		for (int x = destination.indexMin(); x <= destination.indexMax(); ++x)
		{
			destination[x] = 0.0;
			for (int t = source.indexMin(); t <= source.indexMax(); ++t)
			{
				destination[x] += source[t] * exp(std::complex<double>(0.0, PI_2 * static_cast<double>(x * t) / N));
			}
			destination[x] = destination[x] / N;
		}
	}


}

#endif
