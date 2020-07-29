#ifndef __TIMER_HPP__
#define __TIMER_HPP__

#include <chrono>
#include <ctime>

class Timer
{
public:
    Timer()
    {
        this->Update();
    }

    time_t getNowTime()
    {
        // 等同于 time(nullptr)
        return system_clock::to_time_t(system_clock::now());
    }

    const char* getCurTimeFormat()
    {
        time_t now_time = this->getNowTime();
        return ctime(&now_time);
    }

    //获取秒
    double getTimerSecond()
    {
        return this->getTimerMicroSec() * 0.000001;
    }

    //获取毫秒
    double getTimerMillSecond()
    {
        return this->getTimerMicroSec() * 0.001;
    }

    //获取微妙  
    long long getTimerMicroSec()
    {
        //当前时钟减去开始时钟的count
        return std::chrono::duration_cast<std::chrono::microseconds>(high_resolution_clock::now() - _start).count();
    }

private:
    void Update()
    {
        _start = high_resolution_clock::now();
    }

private:
using high_resolution_clock = std::chrono::high_resolution_clock;      // 提供最高精度的计时周期(可能是steady_clock或者system_clock的一种
using system_clock = std::chrono::system_clock;                        // 依据系统的当前时间(可被调整)
using steady_clock = std::chrono::steady_clock;                        // 以统一的速率运行(不能被调整)

std::chrono::time_point<high_resolution_clock> _start;
};

#endif