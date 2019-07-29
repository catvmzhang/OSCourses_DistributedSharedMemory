#include <stdlib.h>
#include <stdio.h>

struct param_d{
	int fd;
	int times;
};

struct list_d{
	int listIndex;
	int *array;
	pthread_mutex_t mutex;

	int (*atomic_pop)(struct list_d*);
};

void listInit(struct list_d **self, int num);
int atomic_pop_impl(struct list_d *self);
