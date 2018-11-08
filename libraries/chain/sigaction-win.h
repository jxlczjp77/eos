#pragma once

#define SIGALRM 23
#define ITIMER_REAL 1
typedef int sigset_t;

struct timeval_ {
	long tv_sec;
	long tv_usec;
};

struct itimerval {
	struct timeval_ it_interval;
	struct timeval_ it_value;
};

struct sigaction
{
	void(*sa_handler)(int);
	sigset_t sa_mask;
	int sa_flags;
};

int setitimer(int which, const struct itimerval *new_value, struct itimerval *old_value);
unsigned alarm(unsigned seconds);
int sigfillset(sigset_t *set);
int sigemptyset(sigset_t *set);
int sigaddset(sigset_t *set, int sig);
int sigaction(int sig, const struct sigaction *act, struct sigaction *oact);
