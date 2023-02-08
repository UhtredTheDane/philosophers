#ifndef STOPWATCH_H
# define STOPWATCH_H

# include <sys/time.h>

long convert_us_in_ms(suseconds_t *micro_nb);
long convert_s_in_ms(time_t *s_nb);
long	get_mls_time();
long get_time_since(long base_time);

#endif