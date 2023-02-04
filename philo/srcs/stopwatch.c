#include "../includes/philosophers.h"

long convert_us_in_ms(suseconds_t *micro_nb)
{
	return (*micro_nb / 1000);
}

long convert_s_in_ms(time_t *s_nb)
{
	return (*s_nb / 0.001);
}

long	get_mls_time()
{
	struct timeval present_time;

	gettimeofday(&present_time, NULL);
	return (convert_s_in_ms(&(present_time.tv_sec)) + convert_us_in_ms(&(present_time.tv_usec)));
}

long get_time_since(long base_time)
{
	return (get_mls_time() - base_time);
}
