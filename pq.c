#include "pq.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct node_struct {
	int id; 	//integers in the range 
	int position; //values 
	double priority; //index in the heap
	
}NODE;

struct pq_struct{
	NODE *heap;		//array of nodes that hold an id and a priority
	NODE **nodePtrs;//array of pointers to corresponding ids
	int size;		//current size
	int capacity;	//capacity of the nodes
	int type; 		//max or min heap depending on the configration
};


PQ * pq_create(int capacity, int min_heap){
	if(0 >= capacity){
		printf("Capacity must be greater than 0!\n");
		exit(1);
	}
	//create priority queue
	PQ *p = malloc(sizeof(PQ));
	
	//create heap
	p->heap = malloc(sizeof(NODE) * capacity+1);
	//set index 0 of heap to -1
	p->heap[0].id = -1;
	p->heap[0].priority = -1;
	
	//create node pointer array
	p->nodePtrs = malloc(sizeof(NODE*) *capacity);
	//set pointers to point to NULL
	int i = 0;
	for(i = 0; i < capacity; i++)
		p->nodePtrs[i] = NULL;
	
	//set capacity, size, and heap type
	p->capacity = capacity; //set max capacity
	p->size = 0; //set starting number of elements in tree to 0
	p->type = min_heap; //starts at 0 so 

	return p;
}


void pq_free(PQ * pq){	
	free(pq->heap);
	free(pq->nodePtrs);
	free(pq);
}


void perculate_up(PQ *pq, int i){
	//hold priority and id temporarily
	double x = pq->heap[i].priority;
	int d = pq->heap[i].id;
	int pos = pq->heap[i].position;
	//get the root node
	int value = i/2;
	
	
	//for max-heap
	if(pq->type == 0){
		while(x > pq->heap[value].priority && value >= 1){
			//swap the values 
			pq->heap[i] = pq->heap[value];
			pq->nodePtrs[pq->heap[value].id] = &(pq->heap[i]);
			pq->nodePtrs[pq->heap[value].id] = &(pq->heap[i]);
			//set the new value
			i = value;
			value = i/2;
		}
	}
	//for min-heap 
	else {	
		while(x < pq->heap[value].priority && value >= 1){
			//swap the values
			pq->heap[i].priority = pq->heap[value].priority;
			pq->heap[i].id = pq->heap[value].id;
			pq->nodePtrs[pq->heap[value].id] = &(pq->heap[i]);
			//set the new values of i and value
			i = value;
			value = i/2;
		}
	}
	//set the index to temporary variables
	pq->heap[i].priority = x;
	pq->heap[i].id = d;
	pq->nodePtrs[d] = &(pq->heap[i]);
}

int pq_insert(PQ * pq, int id, double priority){
	//id is out of range
    if (id < 0 || pq->capacity <= id){  
		printf("ERROR: ID is out of Range!\n");
		return 0;
	}
	//entry for the id already exists
    if(pq->nodePtrs[id] != NULL){
		printf("ERROR: ID is already occupied at the given position.\n");
		return 0;
	}
	
	//increase the size
	pq->size = pq->size + 1;
	pq->heap[pq->size].position = pq->size;
	
	//modify heap and array
	pq->heap[pq->size].priority = priority;
	pq->heap[pq->size].id = id;	
	pq->nodePtrs[id] = &(pq->heap[pq->size]);
	pq->heap[pq->size].position = pq->size;
	
	//function call to perculate up to reach the last node in the tree
	perculate_up(pq, pq->size);
	return 1;
}
 
int pq_capacity(PQ * pq){
	return pq->capacity;
}

int pq_size(PQ * pq){
	return pq->size;
}
void perculate_down(PQ *pq, int i){
	
	int left = 2 * i; //left child
	int right = left + 1; //right child
	int done = 0;
	int min = left;
	int max = left; 

	//min-heap perc down
	if(pq->type != 0){		
		while(left <= pq->size && !done){
			min = left;
			//check to see if the right child is min
			if(right <= pq->size && pq->heap[right].priority < pq->heap[left].priority)
				min = right;
			if(pq->heap[min].priority < pq->heap[i].priority){
				//swap
				int id = pq->heap[min].id;
				double priority = pq->heap[min].priority;
				int pos = pq->heap[min].position;
				int id2 = pq->heap[i].id;
				double priority2 = pq->heap[i].priority;
				int pos2 = pq->heap[i].position;

				//modify the heap 
				pq->heap[min].id = id2;
				pq->heap[min].priority = priority2;
				pq->heap[min].position = pos;
				pq->heap[i].id = id;
				pq->heap[i].priority = priority;
				pq->heap[i].position = pos2;
				//modify the array 
				pq->nodePtrs[id] = &(pq->heap[i]);
				pq->nodePtrs[id2] = &(pq->heap[min]); 

				i = min;
			}
			else{
				done = 1;
			}
			left = 2 * i;
			right = left + 1;
		}	
	}
	// max heap perc down
	else {	
		while(left <= pq->size && !done){
			max = left;
			//check to see if the right child is max
			if(right <= pq->size && pq->heap[right].priority > pq->heap[left].priority)
				max = right;
			if(pq->heap[max].priority > pq->heap[i].priority){
				//swap
				int id = pq->heap[min].id;
				double priority = pq->heap[min].priority;
				int pos = pq->heap[min].position;
				int id2 = pq->heap[i].id;
				double priority2 = pq->heap[i].priority;
				int pos2 = pq->heap[i].position;

				//modify the heap
				pq->heap[min].id = id2;
				pq->heap[min].priority = priority2;
				pq->heap[min].position = pos;
				pq->heap[i].id = id;
				pq->heap[i].priority = priority;
				pq->heap[i].position = pos2;
				//modify the array of node pointers 
				pq->nodePtrs[id] = &(pq->heap[i]);
				pq->nodePtrs[id2] = &(pq->heap[min]); 

				i = max;
			}
			else{
				done = 1;
			}
			left = 2 * i;
			right = left + 1;
		}	
	}
}
int pq_change_priority(PQ * pq, int id, double new_priority){
	//conditions for failure
	//id not in pq
	if(pq->nodePtrs[id] == NULL){
		printf("ERROR: There is no such ID in PQ.\n");
		return 0;
	}
	//out of range
	if(id < 0 || pq->capacity <= id){
		printf("ERROR:The value is out of range.\n");
		return 0;
	}
	//consition for success
	//check if there is an entry for the given id
	if(pq->nodePtrs[id] != NULL){
		//check if min heap
		if(pq->type != 0){
			//check if old priority < new 
			if(new_priority > pq->nodePtrs[id]->priority ){
				//change priority to new priority
				pq->nodePtrs[id]->priority = new_priority;
				//perc down
				perculate_down(pq, pq->nodePtrs[id]->position);
			}
			else{
				//change priority to new priority
				pq->nodePtrs[id]->priority = new_priority;
				//perc up
				perculate_up(pq, pq->nodePtrs[id]->position);
			}
		}
		//check if max heap
		else{
			//check if old priority < new 
			if(new_priority < pq->nodePtrs[id]->priority ){
				//change priority to new priority
				pq->nodePtrs[id]->priority = new_priority;
				//perc down
				perculate_down(pq, pq->nodePtrs[id]->position);
			}
			else{
				//change priority to new priority
				pq->nodePtrs[id]->priority = new_priority;
				//perc up
				perculate_up(pq, pq->nodePtrs[id]->position);
			}
		}
	}
	return 1;
}

int pq_remove_by_id(PQ * pq, int id){
	//failure conditions
	//id not in pq
	if(pq->nodePtrs[id] == NULL){
		printf("ERROR: There is no such ID in PQ.\n");
		return 0;
	}
	//out of range
	if(id < 0 || pq->capacity  <= id ){
		printf("ERROR: The value is out of Range!.\n");
		return 0;
	}
	
	//success conditions
	//check if there is an entry with the given id
	if(pq->nodePtrs[id] != NULL){
		NODE *target = (pq->nodePtrs[id]);
		NODE *replacement = &(pq->heap[pq->size]);
		
		int oldPriority = target->priority;		
		int newPriority = replacement->priority;
		int position = target->position;
		
		pq->heap[position].priority = replacement->priority;
		pq->heap[position].id = replacement->id;
		
		pq->heap[pq->size].priority = 0;
		pq->heap[pq->size].id = 0;
		pq->heap[pq->size].position = 0;
		replacement->position = position;
		
		//decrease the size
		pq->size = pq->size -1;
		//check if min heap
		if(pq->type != 0){
			if(oldPriority > newPriority){
				perculate_up(pq, replacement->position);
			}
			if(oldPriority < newPriority){
				perculate_down(pq, replacement->position);
			}
			
		}
		//check if max heap
		else{
			if(oldPriority < newPriority){
				perculate_up(pq, replacement->position);
			}	
			if(oldPriority > newPriority){
				perculate_down(pq, replacement->position);
			}
		}
	}
	//modify pointer
	pq->nodePtrs[id] = NULL;
	return 1;
}


int pq_get_priority(PQ * pq, int id, double *priority){
	if(pq->nodePtrs[id] == NULL){
		printf("ERROR: There is no such ID in PQ.\n");
		return 0;
	}
	//out of range
	else if(id < 0 || pq->capacity <= id){
		printf("ERROR: The value is out of Range!\n");
		return 0;
	}
	//check if there is an entry with the given id
	else if(pq->nodePtrs[id] != NULL){
		//*priority is assigned the associated priority
		*priority = pq->nodePtrs[id]->priority;
		return 1;
	}
}

int pq_delete_top(PQ * pq, int *id, double *priority){
	if(0 >= pq->size ){
		printf("ERROR: The heap is empty!!\n");
		return 0;
	}
	else { 
		//set *id and *priority to the id and priority of the top of the heap
		*priority = pq->heap[1].priority;
		*id = pq->heap[1].id;
		//element is deleted (remove_by_id)
		pq_remove_by_id(pq, pq->heap[1].id);
		return 1;
	}	
}

int pq_peek_top(PQ * pq, int *id, double *priority){
	if(pq->nodePtrs[*id] == NULL){
		printf("ERROR: There is no such ID in PQ.\n");
		return 0;
	}
	//out of range
	else if(id < 0 || pq->capacity <= *id){
		printf("ERROR: The value is out of Range!\n");
		return 0;
	}
	//check if there is an entry with the given id
	else if(pq->nodePtrs[*id] != NULL){
		//*priority is assigned the associated priority
		*priority = pq->nodePtrs[0]->priority;
		return 1;
	}
}
