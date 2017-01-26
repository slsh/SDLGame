//
// Created by johan eriksson on 26/01/2017.
//

#ifndef SDLGAME_TIMER_H
#define SDLGAME_TIMER_H

#endif //SDLGAME_TIMER_H

#include <chrono>
/*
	Klass lånad från:
	https://gist.github.com/gongzhitaao/7062087

*/

class Timer
{
public:
    Timer() : beg_(clock_::now()) {}
    void reset() { beg_ = clock_::now(); }
    double elapsed() const {
        return std::chrono::duration_cast<second_>
                (clock_::now() - beg_).count();
    }

private:
    typedef std::chrono::high_resolution_clock clock_;
    typedef std::chrono::duration<double, std::ratio<1> > second_;
    std::chrono::time_point<clock_> beg_;
};