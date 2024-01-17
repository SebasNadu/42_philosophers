#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <pthread.h>

void	*roll_dice(__attribute__((unused)) void *arg)
{
	int	value;
	int	*dice;

	value = (rand() % 6) + 1;
	dice = malloc(sizeof(*dice));
	*dice = value;
	printf("Thread result: %p\n", dice);
	return ((void *) dice);
}

int	main(void)
{
	srand(time(NULL));
	pthread_t	th;
	int			*res;
	
	if (pthread_create(&th, NULL, &roll_dice, NULL))
		return (EXIT_FAILURE);
	if (pthread_join (th, (void **) &res))
		return (EXIT_FAILURE);
	printf("Thread result: %p\n", res);
	printf("Result: %d\n", *res);
	free(res);
	return (0);
}
