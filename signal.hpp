#ifndef IG_SIGNAL_HPP
#define IG_SIGNAL_HPP

#include <vector>
#include <complex>

namespace momiage
{
	class signal
	{
	private:
		std::vector<std::complex<double>> m_data;
		int m_origin;

		// �����ɃR�s�[
		void copy(const signal &source)
		{
			this->initialize(source.m_data.size(), source.m_origin);

			for (unsigned int i = 0; i < m_data.size(); ++i)
			{
				this->m_data[i] = source.m_data[i];
			}
		}

	public:
		// ���`�� t �͈̔͂� origin <= t < origin + lenght �ł��闣�U�M���𐶐�
		signal(unsigned int length, int origin)
		{
			initialize(length, origin);
		}
		signal() : signal(0, 0)
		{

		}

		// �������Z�q
		const signal &operator = (const signal &source)
		{
			this->copy(source);

			return (*this);
		}

		// ���`�� t �͈̔͂� origin <= t < origin + lenght �ł��闣�U�M���Ƃ��ď����� (�M�����ƒ��`���݂̂�������)
		void initialize(unsigned int length, int origin)
		{
			m_data.resize(length);
			m_origin = origin;
		}

		// ���`���̍ŏ��l���Ԃ�
		int indexMin() const
		{
			return m_origin;
		}
		// ���`���̍ő��l���Ԃ�
		int indexMax() const
		{
			return m_origin + m_data.size() - 1;
		}
		// �M���̒������Ԃ�
		unsigned int length() const
		{
			return m_data.size();
		}

		// �ŏ��l���Ԃ�
		double minAbs() const
		{
			double min = abs(m_data[0]);

			for (unsigned int i = 1; i < m_data.size(); ++i)
			{
				if (min > abs(m_data[i]))
					min = abs(m_data[i]);
			}

			return min;
		}
		// �ő��l���Ԃ�
		double maxAbs() const
		{
			double max = abs(m_data[0]);

			for (unsigned int i = 1; i < m_data.size(); ++i)
			{
				if (max < abs(m_data[i]))
					max = abs(m_data[i]);
			}

			return max;
		}

		// �A�N�Z�X
		std::complex<double> &operator [] (int i)
		{
			return m_data[i - m_origin];
		}
		const std::complex<double> &operator [] (int i) const
		{
			return m_data[i - m_origin];
		}
		// �ǂ݂Ƃ� (�͈͊O�ł� 0)
		const std::complex<double> read(int i) const
		{
			if (m_origin <= i && i < m_origin + m_data.size())
				return m_data[i - m_origin];
			else
				return 0;
		}



	};
}

#endif
