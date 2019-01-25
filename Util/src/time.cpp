#include "time.h"

hr_clock::time_point time::_start_point;
hr_clock::time_point time::_last_time;
time_in_seconds time::_delta_time;

void time::init()
{
	_start_point = hr_clock::now();
	_last_time = _start_point;
	_delta_time = time_in_seconds(0);
}

void time::tick()
{
	auto now = hr_clock::now();
	_delta_time = std::chrono::duration_cast<time_in_seconds>(now - _last_time);
	_last_time = now;
}

time_in_seconds time::elapsed_time()
{
	return std::chrono::duration_cast<time_in_seconds>(hr_clock::now() - _start_point);
}

time_in_seconds time::delta_time()
{
	return _delta_time;
}