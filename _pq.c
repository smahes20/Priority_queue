
#include <stdio.h>
#include <stdlib.h>
#include "pq.h"

/**
* General description:  priority queue which stores pairs
*   <id, priority>.  Top of queue is determined by priority
*   (min or max depending on configuration).
*
*   There can be only one (or zero) entry for a particular id.
*
*   Capacity is fixed on creation.
*
*   IDs are integers in the range [0..N-1] where N is the capacity
*   of the priority queue set on creation.  Any values outside this
*   range are not valid IDs.
**/



// "Opaque type" -- definition of pq_struct hidden in pq.c
typedef struct _pq_struct _PQ;

typedef struct {
  double pr;  // priority
  int    active;
} ENTRY;

struct _pq_struct {
  ENTRY *data;
  int cap;
  int min_first;
};



/**
* Function: _pq_create
* Parameters: capacity - self-explanatory
*             min_heap - if 1 (really non-zero), then it is a min-heap
*                        if 0, then a max-heap
*                        
* Returns:  Pointer to empty priority queue with given capacity and
*           min/max behavior as specified.
*
*/
_PQ * _pq_create(int capacity, int min_heap) {

  int i;
  _PQ * q = malloc(sizeof(_PQ));

  q->data = malloc(capacity * sizeof(ENTRY));
  q->cap = capacity;
  q->min_first = min_heap;
  for(i=0; i<q->cap; i++) {
    q->data[i].active = 0;
  }
  return q;
}


/**
* Function: _pq_free
* Parameters: _PQ * pq
* Returns: --
* Desc: deallocates all memory associated with passed priority 
*       queue.
*
*/
void _pq_free(_PQ * pq) {
  free(pq->data);
  free(pq);
}

/**
* Function: pq_insert
* Parameters: priority queue pq
*             id of entry to insert
*             priority of entry to insert
* Returns: 1 on success; 0 on failure.
*          fails if id is out of range or
*            there is already an entry for id
*          succeeds otherwise.
*          
* Desc: self-explanatory
*
*/
int _pq_insert(_PQ * pq, int id, double priority){
  if(id < 0 || id >= pq->cap || pq->data[id].active)
    return 0;
  pq->data[id].pr = priority;
  pq->data[id].active = 1;
  return 1;
}



/**
* Function: pq_change_priority
* Parameters: priority queue ptr pq
*             element id
*             new_priority
* Returns: 1 on success; 0 on failure
* Desc: If there is an entry for the given id, its associated
*       priority is changed to new_priority and the data 
*       structure is modified accordingly.
*       Otherwise, it is a failure (id not in pq or out of range)
* Runtime:  O(log n)
*       
*/
int _pq_change_priority(_PQ * pq, int id, double new_priority) {
  if(id < 0 || id >= pq->cap || !pq->data[id].active)
    return 0;
  pq->data[id].pr = new_priority;
  return 1;
}


/**
* Function: pq_remove_by_id
* Parameters: priority queue pq, 
*             element id
* Returns: 1 on success; 0 on failure
* Desc: if there is an entry associated with the given id, it is
*       removed from the priority queue.
*       Otherwise the data structure is unchanged and 0 is returned.
* Runtime:  O(log n)
*
*/
int _pq_remove_by_id(_PQ * pq, int id) {
  if(id < 0 || id >= pq->cap || !pq->data[id].active)
    return 0;
  pq->data[id].active = 0;
  return 1;
}

/**
* Function: _pq_get_priority
* Parameters: priority queue pq
*             elment id
*             double pointer priority ("out" param)
* Returns: 1 on success; 0 on failure
* Desc: if there is an entry for given id, *priority is assigned 
*       the associated priority and 1 is returned.
*       Otherwise 0 is returned and *priority has no meaning.
* Runtime:  O(1)
*
*/
int _pq_get_priority(_PQ * pq, int id, double *priority) {
  if(id < 0 || id >= pq->cap || !pq->data[id].active)
    return 0;
  *priority = pq->data[id].pr;
  return 1;
}

/**
* Function: pq_delete_top
* Parameters: priority queue pq
*             int pointers id and priority ("out" parameters)
* Returns: 1 on success; 0 on failure (empty priority queue)
* Desc: if queue is non-empty the "top" element is deleted and
*       its id and priority are stored in *id and *priority; 
*       The "top" element will be either min or max (wrt priority)
*       depending on how the priority queue was configured.
*    
*       If queue is empty, 0 is returned.
*
* Runtime:  O(log n)
*
*
*/
int _pq_delete_top(_PQ * pq, int *id, double *priority) {
  int top_id = -1;
  int i;
  double top_p;
  double coeff = 1.0;

  if(!pq->min_first)
    coeff = -1;


  for(i=0; i<pq->cap; i++) {
    if(pq->data[i].active && (top_id==-1 || coeff*(pq->data[i].pr) < coeff*top_p)){
      top_id = i;
      top_p = pq->data[i].pr;
    }
  }
  if(top_id == -1) 
    return 0;
  else {
    *priority = top_p;
    *id = top_id;
    pq->data[top_id].active = 0;
    return 1;
  }
}


/**
* Function: pq_peek_top
* Parameters: priority queue pq
*             int pointers id and priority ("out" parameters)
* Returns: 1 on success; 0 on failure (empty priority queue)
* Desc: if queue is non-empty information about the "top" 
*       element (id and priority) is stored in *id and *priority; 
*       The "top" element will be either min or max (wrt priority)
*       depending on how the priority queue was configured.
*
*       The priority queue itself is unchanged (contrast with
*       pq_delete_top).!
*    
*       If queue is empty, 0 is returned.
*
* Runtime:  O(1)
*
*/
int _pq_peek_top(_PQ * pq, int *id, double *priority) {
  int success;

  success = _pq_delete_top(pq, id, priority);
  if(success)
    pq->data[*id].active = 1;  // cheat:  use delete_top and toggle back
                               //    to active.
  return success;
}


/**
* Function:  _pq_capacity
* Parameters: priority queue pq
* Returns: capacity of priority queue (as set on creation)
* Desc: see returns
*
*/
int _pq_capacity(_PQ * pq) {
  return pq->cap;
}

/**
* Function: _pq_size
* Parameters: priority queue pq
* Returns: number of elements currently in queue
* Desc: see above
*
*/
int _pq_size(_PQ * pq) {
  int n=0;
  int i;

  for(i=0; i < pq->cap; i++) {
    if(pq->data[i].active)
      n++;
  }
  return n;
}

int empty_and_check(PQ *q, _PQ *_q) {

  if(pq_size(q) != _pq_size(_q) ) {
    printf("empty-and-check ERROR TYPE 1: mismatched q size\n");
    printf("   SUBSEQUENT TESTS WILL BE QUESTIONABLE !!\n");
  }

  int id, _id;
  double p, _p;
  int bad;
  int passed = 1;

  while(pq_size(q) != 0){
    pq_delete_top(q, &id, &p);
    _pq_delete_top(_q, &_id, &_p);
    bad = 0;
    if(id != _id){ 
        bad = 1;
        printf("empty-and-check ERROR TYPE 2: mismatched IDs\n");
    }
    if(p != _p){ 
        bad = 1;
        printf("empty-and-check ERROR TYPE 3: mismatched priorities\n");
    }
    if(bad) {
      passed = 0;
      printf("        Expected <id=%i; p=%f>; received <id=%i, p=%f>\n", 
          _id, _p, id, p);
    }
  }
  return passed;
}



/**
 * desc:  performs a sequence of pq_change_priority operations
 *        to both q and _q.
 *
 *        Presumption:  both queues contain exactly same set of
 *        id-priority pairs when called and therefore will also 
 *        have the same contents afterwards.
 *
 *        Priorities are changed by whole numbers generated at random
 *        Canges may be positive or negative.
 *
 *        NOTE:  if gen_pairs was used to create initial data, altering
 *        priorities by whole numbers preserves uniqueness among priorities.
 *
 */
void change_priorities(PQ *q, _PQ *_q) {

  int n=pq_capacity(q);
  int id;

  if(_pq_size(_q) != pq_size(q)){
    printf("change_priorities ERROR TYPE 1 - size mismatch\n");
    printf("    ALL SUBSEQUENT TESTS WILL BE QUESTIONABLE\n");
  }
  for(id=0; id<n; id++) {
    double p, _p;

    if(_pq_get_priority(_q, id, &_p)) {
      if(!pq_get_priority(q, id, &p)) {

        printf("change_priorities ERROR TYPE 2 - ID %i in only one queue?\n", id);
      }
      else {
        if(_p != p) {
            printf("change_priorities ERROR TYPE 3 - priorities for ID %i do not match?\n", id);
        }
        else {


          double delta = rand()%1000;
          if(rand()%2)
            delta = -delta;

          p += delta;

          _pq_change_priority(_q,  id, p);
          pq_change_priority(q,  id, p);

        }
      }
    } // end if(_pq_get_priority(...))
  } // end for
}







/**
 * desc:  allocates and populates two arrays of length n.
 *        The first is a permutation of {0..n-1}
 *
 *        The priorities are generated so that they are all distinct
 *        (idea:  if priorities are distinct, there is only one possible
 *        outcome for most/all operations -- unique minimum, etc.)
 *
 * typical usage:  generate data to pass to init_qs to seed two identical
 *    queues.
 */
void gen_pairs(int n, int **p_ids, double **p_priorities) {

  int *ids = malloc(n*sizeof(int));
  double *priorities = malloc(n*sizeof(double));
  int i, j, tmp;

  for(i=0; i<n; i++) {
    ids[i] = i;
    priorities[i] = rand()%100 + i/(double)n;
  }
  for(i=0; i<n; i++) {
    j = rand()%n;
    tmp = ids[i];
    ids[i] = ids[j];
    ids[j] = tmp;
  }
  *p_ids = ids;
  *p_priorities = priorities;
}



/**
 * desc:  creates a PQ and a _PQ and populates both
 *        with the same colection of <id,priority> pairs
 *        as given by the two arrays ids[] and p[].
 *
 *        Pairs <ids[i], p[i]> are inserted into initially 
 *        empty queues.
 *
 *        Upon completion, both queues should have identical
 *        contents.
 *
 *        Note:  caller passes double pointers.
 */
void init_qs(int ids[], double p[], int n, int cap, 
                int minAtTop, PQ **q, _PQ **_q) {

  int i;
  *q = pq_create(cap, minAtTop);
  *_q = _pq_create(cap, minAtTop);


  for(i=0; i<n; i++) {
    pq_insert(*q, ids[i], p[i]);
    _pq_insert(*_q, ids[i], p[i]);
  }

}


