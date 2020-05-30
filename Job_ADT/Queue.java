//Queue.java
//pa4
//

public class Queue implements QueueInterface{
	
	private class Node{
		Object newItem;
		Node next;
		
		Node(Object newItem){
			this.newItem = newItem;
			next = null;
		}
	}
	
	private Node head;
	private int numItems;

	public Queue(){
		head = null;
		numItems = 0;
	}

	public boolean isEmpty(){
		//head = null;
		return(numItems == 0);
	}

	public int length(){
		return numItems;
	}

	public void enqueue(Object newItem){
		Node N;
		if(head == null){ //isEmpty()
			head = new Node(newItem);
		}
		else{
			N = head;
			while(N.next != null){
			N = N.next;
			}
		N.next = new Node(newItem);
		}
		numItems++;
	}
	
	public Object dequeue() throws QueueEmptyException{
		Node N;
		if(head == null){ //isEmpty();
			throw new QueueEmptyException("cannot dequeue() empty queue");
		}
		else{ //deleting?
			N = head;
			head = N.next;
			numItems--;
			return N.newItem; //node class is of type object and return types are objects
		}
	}

	public Object peek() throws QueueEmptyException{
		Node N;
		if(head == null){ //isEmpty()
			throw new QueueEmptyException("cannot peek() on an empty Queue");
		}
		else{
			return head.newItem;
		}
	}	 

	public void dequeueAll() throws QueueEmptyException{
		if(head == null){ //isEmpty()
			throw new QueueEmptyException("cannot dequeueAll() empty queue");
		}
		else{
			//.isEmpty()
			head = null;
			numItems = 0;
		}
	}
	
	public String toString(){
		String s = "";
		Node N;
		N = head;
		for(int i = 0; i < numItems; i++){ //not int, if object is null
			s = s + N.newItem + " ";
			N = N.next;
		}
		return s;
	}

}
