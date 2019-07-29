#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "def.h"
 
int atomic_pop_impl(struct list_d *self){
	int index;
	pthread_mutex_lock(&(self->mutex));	
	index = self->listIndex;
	self->listIndex ++;
	pthread_mutex_unlock(&(self->mutex));
	
	return (self->array)[index];
}

void listInit(struct list_d **self, int num){
	(*self) = (struct list_d*)malloc(sizeof(struct list_d));

	(*self)->listIndex = 0;
	(*self)->array = (int*)malloc(sizeof(int) * num);
	pthread_mutex_init(&((*self)->mutex), 0);
	(*self)->atomic_pop = atomic_pop_impl;


	for(int i=0;i<num;i++){
		((*self)->array)[i] = i;
	}

	return ;	
}
