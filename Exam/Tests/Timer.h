#pragma once
#include <chrono>
#include <memory>
#include <iostream>
class Timer {
public:
	Timer() {
		Start_timepoint=std::chrono::high_resolution_clock::now();
	}
	~Timer() {
		Stop();
	}
	Stop() {
		auto End_timepoint = std::chrono::high_resolution_clock::now();;
		auto start = std::chrono::time_point_cast<std::chrono::microseconds>(Start_timepoint).time_since_epoch().count();
		auto end = std::chrono::time_point_cast<std::chrono::microseconds>(End_timepoint).time_since_epoch().count();
		auto duration = end - start;
		double ms = duration * 0.001;
		std::cout << duration << "us (" << ms << " ms)" << endl;
	}
private:
	std::chrono::time_point<std::chrono::high_resolution_clock> Start_timepoint;
};