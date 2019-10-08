/*
 * Copyright (c) 2013 Bucknell University
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Author: L. Felipe Perrone (perrone@bucknell.edu)
 */

#include <stdlib.h>
#include "circular-list.h" 
#include <pthread.h>
#include <semaphore.h>

sem_t empty;
sem_t full;
pthread_mutex_t lock; 

int circular_list_create(struct circular_list *l, int size) {
  sem_init(&empty, 0, size);
  sem_init(&full, 0, size);
  pthread_mutex_init(&lock, NULL);

  l->buffer = calloc(size, sizeof(item));
  l->start = -1;
  l->end = -1;
  l->elems = 0;
  l->size = size;
  return 0;
}


int circular_list_insert(struct circular_list *l, item i) {
  //wait on empty
  sem_wait(&empty);

  //wait for lock to be available and lock this thread
  pthread_mutex_lock(&lock);

  if (l->elems == l->size){
    return -1;
  }
  if (l->start == -1) {
    l->start = 0;
  }
  l->elems += 1;
  l->end = (l->end + 1) % l->size;
  l->buffer[l->end] = i;
  
  //unlock
  pthread_mutex_unlock(&lock);

  //signal full
  sem_post(&full);

  return 0;
}


int circular_list_remove(struct circular_list *l, item *i) {
  //wait on full
  sem_wait(&full);

  //wait for lock to be available and lock this thread
  pthread_mutex_lock(&lock);

  if (l->elems == 0) {
    return -1;
  }
  *i = l->buffer[l->start];
  l->elems -= 1;
  l->start = (l->start + 1) % l->size;

  //unlock the thread
  pthread_mutex_unlock(&lock);
  
  //signal empty
  sem_post(&empty);

  return 0;
}
