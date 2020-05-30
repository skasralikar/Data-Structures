//-----------------------------------------
//QueueInterface.java
//interface for the Queue ADT
//-----------------------------------------


public interface QueueInterface{
	//is Empty()
	//pre:none
	//post: returns true if this Queue is empty, false otherwise
	public boolean isEmpty();

	//length()
	//pre:none
	//post: returns the length of this Queue.
	public int length();

	//enqueue()
	//adds newItem to back of this Queue
	//pre: none
	//post: !isEmpty()
	public void enqueue(Object newItem);

	//dequeue()
	//deletes and returns item from front of this Queue
	//pre: !isEmpty()
	public Object dequeue() throws QueueEmptyException;

	//peek()
	//pre: !isEmpty()
	//post: returns item at front of Queue
	public Object peek() throws QueueEmptyException;

	//dequeueAll()
	//sets this Queue to the empty state
	//pre: !isEmpty()
	//post: isEmpty()
	public void dequeueAll() throws QueueEmptyException;

	//toString()
	//oversides Object's toSTring method
	public String toString();
}
