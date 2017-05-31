/*-
 * Copyright (c) 1997 Brian Somers <brian@Awfulhak.org>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * $FreeBSD: src/usr.sbin/ppp/throughput.c,v 1.18 2002/08/27 20:11:58 brian Exp $
 */

#include "PPP/Inc/ppp_public.h"
#include "PPP/Inc/throughput.h"

/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_THROUGHPUT_C



void
throughput_init(struct pppThroughput *t, int period)
{
  t->OctetsIn = t->OctetsOut = t->PacketsIn = t->PacketsOut = 0;
  t->SamplePeriod = period;
  t->out.OctetsPerSecond = 0;
  t->BestOctetsPerSecond = 0;
  t->nSample = 0;
/*  time(&t->BestOctetsPerSecondTime);*/
/*  PS_MEM_SET(&t->Timer, '\0', sizeof t->Timer);
  t->Timer.name = "throughput";
  t->uptime = 0;
  t->downtime = 0;*/
  t->rolling = 0;
  t->callback.data = VOS_NULL_PTR;
  t->callback.fn = VOS_NULL_PTR;
  throughput_stop(t);
}

void
throughput_destroy(struct pppThroughput *t)
{
}

int
throughput_uptime(struct pppThroughput *t)
{

  return 0;
}

void
throughput_disp(struct pppThroughput *t/*, struct prompt *prompt*/)
{
}


void
throughput_log(struct pppThroughput *t, int level, const char *title)
{
}

void
throughput_sampler(void *v)
{
  struct pppThroughput *t = (struct pppThroughput *)v;
  int uptime, divisor;
  VOS_UINT32 octets;

/*  timer_Stop(&t->Timer);*/

  uptime = throughput_uptime(t);
  divisor = uptime < t->SamplePeriod ? uptime + 1 : t->SamplePeriod;
  octets = t->in.OctetsPerSecond + t->out.OctetsPerSecond;
  if (t->BestOctetsPerSecond < octets) {
    t->BestOctetsPerSecond = octets;
 /*   time(&t->BestOctetsPerSecondTime);*/
  }

  if (++t->nSample == t->SamplePeriod)
    t->nSample = 0;

  if (t->callback.fn != VOS_NULL && uptime >= t->SamplePeriod)
    (*t->callback.fn)(t->callback.data);

/*  timer_Start(&t->Timer);*/
}

void
throughput_start(struct pppThroughput *t, const char *name, int rolling)
{
  t->nSample = 0;
  t->OctetsIn = t->OctetsOut = 0;
  t->in.OctetsPerSecond = t->out.OctetsPerSecond = t->BestOctetsPerSecond = 0;
/*  time(&t->BestOctetsPerSecondTime);
  t->downtime = 0;
  time(&t->uptime);*/
  throughput_restart(t, name, rolling);
}

void
throughput_restart(struct pppThroughput *t, const char *name, int rolling)
{
/*  timer_Stop(&t->Timer);*/
  t->rolling = rolling ? 1 : 0;
}

void
throughput_stop(struct pppThroughput *t)
{
    /*
  if (t->Timer.state != TIMER_STOPPED)
    time(&t->downtime);
  timer_Stop(&t->Timer);
  */
}

void
throughput_addin(struct pppThroughput *t, VOS_INT32 n)
{
  t->OctetsIn += n;
  t->PacketsIn++;
}

void
throughput_addout(struct pppThroughput *t, VOS_INT32 n)
{
  t->OctetsOut += n;
  t->PacketsOut++;
}

void
throughput_clear(struct pppThroughput *t, int clear_type/*, struct prompt *prompt*/)
{
  if (clear_type & (THROUGHPUT_OVERALL|THROUGHPUT_CURRENT)) {
    t->nSample = 0;
  }

  if (clear_type & THROUGHPUT_OVERALL) {
    int divisor;

    if ((divisor = throughput_uptime(t)) == 0)
      divisor = 1;
    PPP_MNTN_LOG1(PS_PID_APP_PPP, 0, PS_PRINT_NORMAL,"overall cleared (was %6qu bytes/sec)",
                  (t->OctetsIn + t->OctetsOut) / divisor);
    t->OctetsIn = t->OctetsOut = 0;
/*    t->downtime = 0;
    time(&t->uptime);*/
  }

  if (clear_type & THROUGHPUT_CURRENT) {
    PPP_MNTN_LOG2(PS_PID_APP_PPP, 0, PS_PRINT_NORMAL,
                "current cleared (bytes/sec in);(bytes/sec out)",
                  t->in.OctetsPerSecond, t->out.OctetsPerSecond);
    t->in.OctetsPerSecond = t->out.OctetsPerSecond = 0;
  }

  if (clear_type & THROUGHPUT_PEAK) {
/*
    char *time_buf, *last;
    time_buf = ctime(&t->BestOctetsPerSecondTime);
    last = time_buf + strlen(time_buf);
    if (last > time_buf && *--last == '\n')
      *last = '\0';
    prompt_Printf(prompt, "peak    cleared (was %6qu bytes/sec on %s)\n",
                  t->BestOctetsPerSecond, time_buf);
    t->BestOctetsPerSecond = 0;
    time(&t->BestOctetsPerSecondTime);*/
  }
}

void
throughput_callback(struct pppThroughput *t, void (*fn)(void *), void *data)
{
  t->callback.fn = fn;
  t->callback.data = data;
}

