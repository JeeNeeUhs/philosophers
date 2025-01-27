#include "philo.h"

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

// time_t	get_time_ms(t_tv tv)
// {
// 	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
// }

// time_t	get_current_time(void)
// {
// 	t_tv	now;

// 	gettimeofday(&now, NULL);
// 	return (now.tv_sec * 1000 + now.tv_usec / 1000);
// }

time_t	get_deltatime_ms(struct timeval tv)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return ((now.tv_sec - tv.tv_sec) * 1000
		+ (now.tv_usec - tv.tv_usec) / 1000);
}