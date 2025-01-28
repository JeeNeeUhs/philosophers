#include "philo.h"
#include <unistd.h>

int	ft_atoi(const char *str)
{
	int	sign;
	int	total;

	sign = 1;
	total = 0;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		sign = 44 - *str;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		total *= 10;
		total += *str - '0';
		str++;
	}
	return (sign * total);
}

time_t	get_time_ms(struct timeval tv)
{
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

time_t	get_current_time_ms()
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return (get_time_ms(now));
}

time_t	get_deltatime_ms(struct timeval tv)
{
	return (get_current_time_ms() - get_time_ms(tv));
}

void	ft_sleep(time_t ms)
{
	time_t	start;
	start = get_current_time_ms();
	while ((get_current_time_ms() - start) < ms)
		usleep(500);
}
