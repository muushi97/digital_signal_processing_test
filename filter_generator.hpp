#ifndef IG_FILTER_GENERATOR_HPP
#define IG_FILTER_GENERATOR_HPP

#include "math_constant.hpp"
#include "signal.hpp"

namespace momiage
{
	// ���K���J�b�g�I�t���g��(fc)�ƃt�B���^�̎���(N)���w�肵���[�p�X�t�B���^�̌W���𐶐�
	// 0 < fc < 1  �łȂ���LPF�ɂȂ��񂺂�
	void generateLowPassFilterCoefficient(signal &output, double fc, unsigned int N)
	{
		int t;
		double wc = fc * PI_1;
		// fc = wc / pi �Ƃ������ƂɂȂ�

		output.initialize(N, -1 * (N >> 1));

		for (t = output.indexMin(); t < 0; ++t)
		{
			output[t] = sin(wc * t) / (PI_1 * t);
		}
		output[0] = fc;
		for (t = 1; t <= output.indexMax(); ++t)
		{
			output[t] = sin(wc * t) / (PI_1 * t);
		}
	}

	// ���K���J�b�g�I�t���g��(fc)�ƃt�B���^�̎���(N)���w�肵�n�C�p�X�t�B���^�̌W���𐶐�
	// 0 < fc < 1  �łȂ���HPF�ɂȂ��񂺂�
	void generateHighPassFilterCoefficient(signal &output, double fc, unsigned int N)
	{
		int t;
		double wc = fc * PI_1;
		// fc = wc / pi �Ƃ������ƂɂȂ�

		output.initialize(N, -1 * (N >> 1));

		for (t = output.indexMin(); t < 0; ++t)
		{
			output[t] = -sin(wc * t) / (PI_1 * t);
		}
		output[0] = 1.0 - fc;
		for (t = 1; t <= output.indexMax(); ++t)
		{
			output[t] = -sin(wc * t) / (PI_1 * t);
		}
	}

	// ���K���J�b�g�I�t���g��(fc1,fc2)�ƃt�B���^�̎���(N)���w�肵�o���h�p�X�t�B���^�̌W���𐶐�
	// 0 < fc1 < fc2 < 1  �łȂ���BPF�ɂȂ��񂺂�
	void generateBandPassFilterCoefficient(signal &output, double fc1, double fc2, unsigned int N)
	{
		int t;
		double wc1 = fc1 * PI_1;
		double wc2 = fc2 * PI_1;
		// fc1 = wc1 / pi
		// fc2 = wc2 / pi �Ƃ������ƂɂȂ�

		output.initialize(N, N >> 1);

		for (t = output.indexMin(); t < 0; ++t)
		{
			output[t] = (sin(wc2 * t) - sin(wc1 * t)) / (PI_1 * t);
		}
		output[0] = fc2 - fc1;
		for (t = 1; t <= output.indexMax(); ++t)
		{
			output[t] = (sin(wc2 * t) - sin(wc1 * t)) / (PI_1 * t);
		}
	}
}

#endif
