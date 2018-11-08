#include <signal.h>
#include <stdio.h>
#include "sigaction-win.h"
#include <windows.h>

TIMECALLBACK winhacktimeEventHandler;
void winhackmaskedSignalHandler(int);

struct sigaction winhackmaskedSignalTable[24] = { {NULL, 0, 0}, {NULL, 0, 0},
{NULL, 0, 0}, //INT
{NULL, 0, 0},
{NULL, 0, 0}, //ILL
{NULL, 0, 0}, {NULL, 0, 0}, {NULL, 0, 0},
{NULL, 0, 0}, //FPE
{NULL, 0, 0}, {NULL, 0, 0},
{NULL, 0, 0}, //SEGV
{NULL, 0, 0}, {NULL, 0, 0}, {NULL, 0, 0},
{NULL, 0, 0}, //TERM
{NULL, 0, 0}, {NULL, 0, 0}, {NULL, 0, 0}, {NULL, 0, 0}, {NULL, 0, 0},
{NULL, 0, 0}, //BREAK
{NULL, 0, 0}, //ABRT
{NULL, 0, 0} }; //ALRM

void winhackmaskedSignalHandler(int sig)
{
	struct sigaction * p = &winhackmaskedSignalTable[sig];
	struct sigaction a1, a2, a3, a4, a5, a6, a7, a8, ai;
	sigset_t m = p->sa_mask;
	void(*f)(int) = p->sa_handler;
	ai.sa_handler = SIG_IGN;
	ai.sa_mask = 0;
	ai.sa_flags = 0;
	if (m & 1) sigaction(SIGINT, &ai, &a1);
	if (m & 2) sigaction(SIGILL, &ai, &a2);
	if (m & 4) sigaction(SIGFPE, &ai, &a3);
	if (m & 8) sigaction(SIGSEGV, &ai, &a4);
	if (m & 16) sigaction(SIGTERM, &ai, &a5);
	if (m & 32) sigaction(SIGBREAK, &ai, &a6);
	if (m & 64) sigaction(SIGABRT, &ai, &a7);
	if (m & 128) sigaction(SIGALRM, &ai, &a8);
	f(sig);
	if (m & 128) sigaction(SIGALRM, &a8, NULL);
	if (m & 64) sigaction(SIGABRT, &a7, NULL);
	if (m & 32) sigaction(SIGBREAK, &a6, NULL);
	if (m & 16) sigaction(SIGTERM, &a5, NULL);
	if (m & 8) sigaction(SIGSEGV, &a4, NULL);
	if (m & 4) sigaction(SIGFPE, &a3, NULL);
	if (m & 2) sigaction(SIGILL, &a2, NULL);
	if (m & 1) sigaction(SIGINT, &a1, NULL);
}

void __stdcall winhacktimeEventHandler(UINT uTimerID, UINT uMsg, DWORD_PTR dwUser, DWORD_PTR dw1, DWORD_PTR dw2)
{
	if (winhackmaskedSignalTable[SIGALRM].sa_handler > SIG_ACK)
		winhackmaskedSignalHandler(SIGALRM);
}

int setitimer(int which, const struct itimerval *new_value, struct itimerval *old_value) {
	long tv_sec = new_value->it_value.tv_sec;
	long tv_usec = new_value->it_value.tv_usec;
	if (tv_sec == 0 && tv_usec == 0) {
		return 0;
	}
	timeSetEvent(tv_usec / 1000 + tv_sec * 1000, 500, winhacktimeEventHandler, 0, TIME_ONESHOT | TIME_CALLBACK_FUNCTION);
	return 1;
}

unsigned alarm(unsigned seconds)
{
	timeSetEvent(seconds * 1000, 500, winhacktimeEventHandler, 0, TIME_ONESHOT | TIME_CALLBACK_FUNCTION);
	return 0;
}

int sigfillset(sigset_t *set)
{
	*set = 255;
	return 0;
}

int sigemptyset(sigset_t *set)
{
	*set = 0;
	return 0;
}

int sigaddset(sigset_t *set, int sig)
{
	*set = sig;
	return 0;
}

int sigaction(int sig, const struct sigaction *act, struct sigaction *oact)
{
	if (sig < 0 || sig >= SIGALRM) {
		if (sig == SIGALRM) {
			if (oact) *oact = winhackmaskedSignalTable[sig];
			winhackmaskedSignalTable[sig] = *act;
			return 0;
		}
		else {
			return -1;
		}
	}
	struct sigaction o;
	o = winhackmaskedSignalTable[sig];
	winhackmaskedSignalTable[sig] = *act;
	void(*x)(int);
	if (act->sa_mask > 0) {
		x = signal(
			sig, act->sa_handler > SIG_ACK ?
			winhackmaskedSignalHandler : act->sa_handler);
	}
	else {
		x = signal(sig, act->sa_handler);
	}
	if (x == SIG_ERR) {
		winhackmaskedSignalTable[sig] = o;
		return -1;
	}
	if (oact) {
		*oact = o;
		if (x == winhackmaskedSignalHandler) return 0;
		oact->sa_handler = x;
		oact->sa_mask = -1;
	}
	return 0;
}