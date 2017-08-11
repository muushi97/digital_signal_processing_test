#ifndef IG_SIGNAL_GENERATOR_HPP
#define IG_SIGNAL_GENERATOR_HPP

#include "math_constant.hpp"

#include "signal.hpp"

namespace momiage
{
	// length,origin �ɂď��������ꂽ data �� �U�� amplitude, ���� period ��sin�g�𐶐�
	void generateSinWave(signal &data, unsigned int length, int origin, double period, double amplitude)
	{
		data.initialize(length, origin);

		for (int i = data.indexMin(); i <= data.indexMax(); ++i)
		{
			data[i] = sin((static_cast<double>(i) / period) * PI_2) * amplitude;
		}
	}

	// length,origin �ɂď��������ꂽ data �� �U�� amplitude, ���� period ��cos�g�𐶐�
	void generateCosWave(signal &data, unsigned int length, int origin, double period, double amplitude)
	{
		data.initialize(length, origin);

		for (int i = data.indexMin(); i <= data.indexMax(); ++i)
		{
			data[i] = cos((static_cast<double>(i) / period) * PI_2) * amplitude;
		}
	}


}

#endif
