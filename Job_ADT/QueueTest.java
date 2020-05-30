//QueueTest.java
//pa4
//skasrali

public class QueueTest{
	public static void main (String[] args){
		Queue X = new Queue();
		X.enqueue( (int)1);
		X.enqueue( (int)2);
		X.enqueue( (int)3);
		
		System.out.println(X);

		X.dequeue();
		
		System.out.println(X.isEmpty());
		System.out.println("Length of queue: " + X.length());
		System.out.println(X);

		X.dequeueAll();

		System.out.println(X.isEmpty());
                System.out.println("Length of queue: " + X.length());
                System.out.println(X);

	}
}
