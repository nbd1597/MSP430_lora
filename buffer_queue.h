/*
 * buffer_queue.h
 *
 *  Created on: Jun 26, 2020
 *      Author: Duy
 */

#ifndef BUFFER_QUEUE_H_
#define BUFFER_QUEUE_H_
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define capacity 64

typedef struct{
    int8_t front, rear, size;
    //unsigned capacity;
    uint8_t array[capacity];
} Queue;
//Queue* createQueue(unsigned capacity);
uint8_t isFull(Queue* queue);
uint8_t isEmpty(Queue* queue);
void enqueue(Queue* queue, int item);
void enqueue_string(Queue* queue, uint8_t *string);
uint8_t dequeue(Queue* queue);
uint8_t front(Queue* queue);
uint8_t rear(Queue* queue);



#endif /* BUFFER_QUEUE_H_ */
