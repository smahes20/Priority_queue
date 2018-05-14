
Name: Sakshi Maheshwari

Answer each of the questions below to the best of your
ability.  If you didn't complete the part of the assignment
relevant to a particular question, just say so.
-----------------------------------------------

Briefly describe how you modified the basic heap organization (as
presented in class ans in section 5.9 of Aho/Ullman) to support
the specifications for this assignment -- in particular how was
the idea of an ID incorporated.  


I created a struct NODE that contains an id, priority and a position. most of the functions in the assignment modify the heap based on the id of thhe node.
so to achieve that i created an array of node pointers that is initialized to NULL in the begining when we create the PQ.this is useful as we always know where our 
Id is and they correspond to the ID in the array of node pointers. the priority queue also contains variables like size and capacity that meet the constant runtime. 
this was used because of the size and the capacity functions which just return the size and capacity of PQ. these variable are updated when anything is inserted or 
removed from the priority queue. 


-----------------------------------------------
How did your modifications above affect your implementation of
pq_insert (vs. the standard implementation of insert)?

the implementation of pq_insert, inserts the value at the end of the heap and uses a helper function that perculates up.the above modifications helped keeping a track of 
node pointers in an array called node pointers. it also required checking for failure when the id was not in range and the id entered was currently in use or not. 
since, it was an array it was easier to reach up to the given id without actually going through each id in the list and this also meet the runtime requirements 
of O(log n). After which we call function perculate up that swaps the id's, priorities and node pointers. 



-----------------------------------------------
How did your modifications above affect your implementation of
pq_delete_top (vs. the standard implementation of delete_max)?

The implementation of pq_delete_top is almost similar to remove_by_id. we can just remove the first index element using the function remove_by_id, as we already
know the position and id of the first node in the heap. after the value is deleted the we decrease the size of the priority queue. based on the what is the type of the
heap and if the priority is greater then or less then the new priority it perculates up or down.


-----------------------------------------------
Explain how your implementation of pq_change_priority worked,
why it is correct and why it achieves the runtime requirement.

when i started implementing the function i first error checked to make sure if the id was in range or not and also made sure that te id is in the priority queue or not.
after these checks i checked for success conditions. if the heap was a min heap then i compared the current priority that was being changed to the new priority that 
was passed within the function. the priority was then changed to the new priority and based on if the current priority was less then new priority ,i called 
the function perculate down otherwise the function perculate up is called. this helped me achievethe runtime requirements of the sunction which was O(logn).


-----------------------------------------------
How did your implementation enable O(1) runtime for pq_get_priority?
    I created a node pointer that corresponded to the id's in the heap for each of the 
    node that was created. since, i directly access the the node with the specific id it makes the function achieve a constant runtime. 








