#ifndef IG_FILTER_HPP
#define IG_FILTER_HPP

#include "math_constant.hpp"
#include "signal.hpp"

namespace momiage
{
	class filter
	{
	private:
		std::vector<std::complex<double>> m_Coefficient;
		std::vector<std::complex<double>> m_Input;

	public:
		filter(const signal &Coefficient)
		{
			m_Coefficient.resize(Coefficient.length());
			m_Input.resize(Coefficient.length());

			for (unsigned int i = 0; i < m_Coefficient.size(); ++i)
			{
				m_Coefficient[i] = Coefficient[Coefficient.indexMin() + i];
			}

			for (unsigned int i = 0; i < m_Input.size(); ++i)
			{
				m_Input[i] = 0;
			}
		}

		std::complex<double> input(const std::complex<double> &Data)
		{
			std::complex<double> Output(0.0, 0.0);

			m_Input[m_Input.size() - 1] = Data;
			for (unsigned int i = 0; i < m_Coefficient.size(); ++i)
			{
				Output += m_Input[i] * m_Coefficient[i];
				if (i != 0)
					m_Input[i - 1] = m_Input[i];
			}

			return Output;
		}

		void input(signal &Output, const signal &Data)
		{
			Output.initialize(Data.length(), 0);

			int n = Data.indexMin();

			for (unsigned int i = 0; i < (m_Coefficient.size() >> 1); ++i)
			{
				input(Data.read(n));
				++n;
			}
			for (unsigned int i = 0; i < Data.length(); ++i)
			{
				Output[i] = input(Data.read(n));
				++n;
			}
		}
	};
}

#endif
