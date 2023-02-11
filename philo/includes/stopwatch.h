#ifndef STOPWATCH_H
# define STOPWATCH_H

# include <stddef.h>
# include <sys/time.h>

long convert_us_in_ms(long micro_nb);
long convert_s_in_ms(unsigned long s_nb);
long	get_mls_time();
long get_time_since(struct timeval *base_time);

#endif
