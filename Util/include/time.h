#pragma once

#include <chrono>

typedef std::chrono::steady_clock hr_clock;
typedef std::chrono::duration<float> time_in_seconds;

class time
{
public:
	static void init();
	static void tick();

	static time_in_seconds elapsed_time();
	static time_in_seconds delta_time();

private:
	time();

	static hr_clock::time_point _start_point;
	static hr_clock::time_point _last_time;
	static time_in_seconds _delta_time;
};