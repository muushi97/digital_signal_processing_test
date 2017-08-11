#ifndef IG_SIGNAL_WRITER_HPP
#define IG_SIGNAL_WRITER_HPP

#include <string>
#include <fstream>

#include "signal.hpp"

namespace momiage
{
	class signal_writer
	{
	private:
		std::ofstream m_file;

	public:

		void write_real(const std::string &file_name, const signal signal_data, int min, int max)
		{
			m_file.open(file_name, std::ios::out);

			for (int i = min; i <= max; ++i)
			{
				m_file << i << "   " << signal_data[i].real() << std::endl;
			}

			m_file.close();
		}
		void write_imaginary(const std::string &file_name, const signal signal_data, int min, int max)
		{
			m_file.open(file_name, std::ios::out);

			for (int i = min; i <= max; ++i)
			{
				m_file << i << "   " << signal_data[i].imag() << std::endl;
			}

			m_file.close();
		}

	};
}

#endif
