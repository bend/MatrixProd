#include "my_sem.h"


int 
my_sem_init(my_sem** sem, unsigned int nb){
	*sem = malloc(sizeof(my_sem));
	if(*sem == NULL){
		perror("malloc failed");
		return -1;
	}
	sem_unlink(MUTEX);
	(*sem)->mutex = sem_open(MUTEX, O_CREAT|O_EXCL, 0666,1);
	if((*sem)->mutex == NULL){
		perror("sem_open error");
		return -1;
	}
	(*sem)->mutex_free = sem_open(MUTEX_FREE, O_CREAT|O_EXCL, 0666, 1);
	if((*sem)->mutex_free  == NULL){
		sem_close((*sem)->mutex);
		perror("sem_open error");
		return -1;
	}
	(*sem)->value = nb;
	return 0;
}

int
my_sem_wait(my_sem *sem, unsigned int nb){
	if(sem_wait(sem->mutex) == -1){
		perror("sem_wait error");
		return -1;
	}
	sem->value+=nb;
	if((sem->value -(int)nb) >=0){
		sem->value-=nb;
		return 0;
	}
	if(sem_post(sem->mutex) == -1){
		perror("sem_error");
		return -1;
	}
	if(sem_wait(sem->mutex_free) ==-1){
		perror("wait error");
		return -1;
	}
	return 0;
}

int
my_sem_post(my_sem *sem, unsigned int nb){
	if(sem_wait(sem->mutex) == -1){
		perror("sem_wait error");
		return -1;
	}
	sem->value+=nb;
	if(sem->value > 0){
		if(sem_post(sem->mutex_free)==-1){
			perror("sem_post error");
			return -1;
		}
	}
	if(sem_post(sem->mutex)==0){
		perror("sem_wait error");
		return -1;
	}
	return 0;
}

int
my_sem_close(my_sem *sem){
	if(sem_close(sem->mutex_free) == -1){
		perror("sem_close error");
		return -1;
	}
	if(sem_close(sem->mutex) == -1){
		perror("sem_close error");
		return -1;
	}
	free(sem);
	return 0;
}
