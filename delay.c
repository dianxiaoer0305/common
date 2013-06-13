#include "defines.h"
#include "config.h"
#include "delay.h"




//delay time based on a specific time.
void delay_specifictime( struct timeval *specifictime,delta_t *fortimeajust)
{
    struct timespec adjuster = { 0, 0 };
    struct timespec nap = { 0, 0 }, delta_time = {0, 0};
    struct timeval nap_for;
    struct timespec nap_this_time;
   
    adjuster.tv_nsec = 0;

    TIMEVAL_TO_TIMESPEC(specifictime, &nap);
    dbgx(3, "specific time for delaying: " TIMESPEC_FORMAT, nap.tv_sec, nap.tv_nsec);
    /*
     * since we apply the adjuster to the sleep time, we can't modify nap
     */
    memcpy(&nap_this_time, &nap, sizeof(nap_this_time));

    dbgx(2, "nap_time before rounding:   " TIMESPEC_FORMAT, nap_this_time.tv_sec, nap_this_time.tv_nsec);

    
    if (timesisset(&adjuster)) {
        if (timescmp(&nap_this_time, &adjuster, >)) {
            timessub(&nap_this_time, &adjuster, &nap_this_time);
        } else { 
            timesclear(&nap_this_time);
        }
    }

    dbgx(2, "Sleeping:   " TIMESPEC_FORMAT, nap_this_time.tv_sec, nap_this_time.tv_nsec);
    
    get_delta_time(fortimeajust, &delta_time);
    dbgx(2, "delta:                      " TIMESPEC_FORMAT, delta_time.tv_sec, delta_time.tv_nsec);
    
    //ajust time
    if (timesisset(&delta_time)) {
        if (timescmp(&nap_this_time, &delta_time, >)) {
            timessub(&nap_this_time, &delta_time, &nap_this_time);
            dbgx(3, "timesub: %lu %lu", delta_time.tv_sec, delta_time.tv_nsec);
        } else { 
            timesclear(&nap_this_time);
            dbgx(3, "timesclear: " TIMESPEC_FORMAT, delta_time.tv_sec, delta_time.tv_nsec);
        }
    }
    /* don't sleep if nap = {0, 0} */
    if (!timesisset(&nap_this_time))
        return;

    do_sleep(nap_this_time);
	
    dbgx(2, "sleep delta: " TIMESPEC_FORMAT, delta_time.tv_sec, delta_time.tv_nsec);

}


//delay time based on the real packet interval time.
void delay_realinterval(struct timeval *currenttimestamp, struct timeval *lasttimestamp,delta_t *fortimeajust)
{
    struct timespec adjuster = { 0, 0 };
    struct timespec nap = { 0, 0 }, delta_time = {0, 0};
    struct timeval nap_for;
    struct timespec nap_this_time;
    adjuster.tv_nsec = 0;

    dbgx(4, "This packet time: " TIMEVAL_FORMAT, currenttimestamp->tv_sec, currenttimestamp->tv_usec);
    dbgx(4, "Last packet time: " TIMEVAL_FORMAT, lasttimestamp->tv_sec, lasttimestamp->tv_usec);

    //Replay packets a factor of the time they were originally sent.
    if (timerisset(lasttimestamp)) 
    {
        if (timercmp(currenttimestamp, lasttimestamp, <))
        {
            /* Packet has gone back in time!  Don't sleep and warn user */
           // warnx("The current Packet has gone back in time!");
            timesclear(&nap); 
        } 
	else
        {
            /* time has increased or is the same, so handle normally */
            timersub(currenttimestamp, lasttimestamp, &nap_for);
            dbgx(3, "original packet delta time: " TIMEVAL_FORMAT, nap_for.tv_sec, nap_for.tv_usec);

            TIMEVAL_TO_TIMESPEC(&nap_for, &nap);
            dbgx(3, "original packet delta timv: " TIMESPEC_FORMAT, nap.tv_sec, nap.tv_nsec);
                
        }
    } 
    else
    {
        /* Don't sleep if this is our first packet */
        timesclear(&nap);
    }
        
    //since we apply the adjuster to the sleep time, we can't modify nap 
    memcpy(&nap_this_time, &nap, sizeof(nap_this_time));

    dbgx(2, "nap_time before rounding:   " TIMESPEC_FORMAT, nap_this_time.tv_sec, nap_this_time.tv_nsec);

   
    if (timesisset(&adjuster)) 
    {
        if (timescmp(&nap_this_time, &adjuster, >)) 
	{
            timessub(&nap_this_time, &adjuster, &nap_this_time);
        } 
	else 
	{ 
            timesclear(&nap_this_time);
        }
    }

    dbgx(2, "Sleeping:                   " TIMESPEC_FORMAT, nap_this_time.tv_sec, nap_this_time.tv_nsec);
     get_delta_time(fortimeajust, &delta_time);
    dbgx(2, "delta:                      " TIMESPEC_FORMAT, delta_time.tv_sec, delta_time.tv_nsec);

    //ajust time
    if (timesisset(&delta_time))
    {
	if (timescmp(&nap_this_time, &delta_time, >)) 
	{
            timessub(&nap_this_time, &delta_time, &nap_this_time);
            dbgx(3, "timesub: %lu %lu", delta_time.tv_sec, delta_time.tv_nsec);
        } 
	else 
	{ 
            timesclear(&nap_this_time);
            dbgx(3, "timesclear: " TIMESPEC_FORMAT, delta_time.tv_sec, delta_time.tv_nsec);
        }
    }
    /* don't sleep if nap = {0, 0} */
    if (!timesisset(&nap_this_time))
        return;

    do_sleep(nap_this_time);

    dbgx(2, "sleep delta: " TIMESPEC_FORMAT, delta_time.tv_sec, delta_time.tv_nsec);
}

/*
 * delay time based on the specific Baud rate 
 * Ignore the time supplied by the capture file and send data at
 * a constant 'rate' (bytes per second).
 */
void delay_specificrate(float speed,int packetlen, delta_t *fortimeajust)
{ 
    struct timespec adjuster = { 0, 0 };
    struct timespec nap = { 0, 0 }, delta_time = {0, 0};
    struct timeval nap_for;
    struct timespec nap_this_time;
    float n;
            
    n = (float)packetlen / (speed * 1024 * 1024 / 8); /* convert Mbps to bps */
    nap.tv_sec = n;
    nap.tv_nsec = (n - nap.tv_sec)  * 1000000000;

    dbgx(3, "packet size %d\t\tequals %f bps\t\tnap " TIMESPEC_FORMAT, packetlen, n, 
                nap.tv_sec, nap.tv_nsec);
         
    /*
     * since we apply the adjuster to the sleep time, we can't modify nap
     */
    memcpy(&nap_this_time, &nap, sizeof(nap_this_time));

    dbgx(2, "nap_time before rounding:   " TIMESPEC_FORMAT, nap_this_time.tv_sec, nap_this_time.tv_nsec);

   
    if (timesisset(&adjuster)) 
    {
        if (timescmp(&nap_this_time, &adjuster, >)) 
	{
            timessub(&nap_this_time, &adjuster, &nap_this_time);
        } 
	else 
	{ 
            timesclear(&nap_this_time);
        }
    }

    dbgx(2, "Sleeping:                   " TIMESPEC_FORMAT, nap_this_time.tv_sec, nap_this_time.tv_nsec);
    
    get_delta_time(fortimeajust, &delta_time);
    dbgx(2, "delta:                      " TIMESPEC_FORMAT, delta_time.tv_sec, delta_time.tv_nsec);

    /*ajust time */
    if (timesisset(&delta_time))
    {
        if (timescmp(&nap_this_time, &delta_time, >)) 
	{
            timessub(&nap_this_time, &delta_time, &nap_this_time);
            dbgx(3, "timesub: %lu %lu", delta_time.tv_sec, delta_time.tv_nsec);
        } 
	else 
	{ 
            timesclear(&nap_this_time);
            dbgx(3, "timesclear: " TIMESPEC_FORMAT, delta_time.tv_sec, delta_time.tv_nsec);
        }
    }
    /* don't sleep if nap = {0, 0} */
    if (!timesisset(&nap_this_time))
        return;

   do_sleep(nap_this_time);

    dbgx(2, "sleep delta: " TIMESPEC_FORMAT, delta_time.tv_sec, delta_time.tv_nsec);

}

