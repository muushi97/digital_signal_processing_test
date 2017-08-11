all:
	g++ -std=c++14 ./main.cpp ./filter_generator.hpp ./filter.hpp ./graph.hpp ./line_drawer.hpp ./math_constant.hpp ./signal_generator.hpp ./signal_processor.hpp ./signal_writer.hpp ./signal.hpp -o fuga.exe -mwindows -lwinmm -lcomctl32 -lmingw32 -static
	@echo finished
