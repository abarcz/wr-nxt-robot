#include "debug.h"

struct pid_str
{
	int kp;
	int kd;
	int ki;
	long last_e;
	long sum_e;		// sum of all e's since start of the algorithm
};

void pid_init(pid_str &p)
{
	p.kp=5;
	p.kd=20;
	p.ki=0;
	p.last_e = 0;
	p.sum_e = 0;
}

long pid_getval(pid_str &p, long e)
{
	long val;
	p.sum_e += e;
	val = p.kp * e + p.kd*(e-p.last_e) + p.ki * p.sum_e;
	p.last_e = e;
	return val;
}
	


