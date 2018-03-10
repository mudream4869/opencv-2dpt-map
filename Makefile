a.out: main.cpp Win2dptMap.h
	g++ main.cpp `pkg-config opencv --cflags --libs` -std=c++11
