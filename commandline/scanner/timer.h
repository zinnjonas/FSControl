#ifndef TIMER_H_
#define TIMER_H_

#include <iostream>
#include <time.h>


class Timer
{
    public:
        Timer();

		void           start();
		void           stop();
		void           reset();

		bool           isRunning();
		unsigned long  getTime();
		bool           isOver(unsigned long seconds);
	private:

		bool           resetted;
		bool           running;
		unsigned long  beg;
		unsigned long  end;
};

#endif // TIMER_H_
