//Simulation.java
//pa4


import java.io.*;
import java.util.Scanner;

public class Simulation{ 
	//storage queue 
	public static Job getJob(Scanner in){
		String[]s = in.nextLine().split(" ");
		int a = Integer.parseInt(s[0]);
		int d = Integer.parseInt(s[1]);
		return new Job(a, d);
	}

	public static void main(String[] args) throws IOException{
		PrintWriter report = null;
		PrintWriter trace = null;
		Scanner in = null;
		int n = 0;
		Job j = null;
		Queue initial = new Queue();
		Queue storage = new Queue();
		Queue complete = new Queue();
		//check command line arguments ??
		try{
			if(args.length != 3){
				System.out.println("Usage: Simulation infile");
				System.exit(1);
			}
		
		//open files for reading and writing
			in = new Scanner(new File(args[0]));
			report = new PrintWriter(new FileWriter(args[0] + ".rpt"));
			trace = new PrintWriter(new FileWriter(args[0] + ".trc"));
		
		}catch(FileNotFoundException e){
			System.out.println("Error: " + e);
			System.exit(1);
		}
		
		//read in m jobs from the input file
		int m = in.nextInt();

		trace.println("Trace file: " + args[0] + ".trc");
		trace.println(m + "Jobs: ");
		trace.println(initial.toString());
		trace.println();

		report.println("Report file: " + args[0] + ".rpt");
		report.println(m + " Jobs:");
		report.println(initial.toString());
		report.println();
		report.println("*********************************");
		
		//run simulation with n processors for n = 1 to n = m-1
		for(n = 1; n < m; n++){
			int totalWait = 0;
			int maxWait = 0;
			double averageWait = 0.0;
		}
		
		//create and array of n processor Queues and any necessary storage Queues
		for(int i = 1; i < initial.length()+1; i++){
			j = (Job)initial.dequeue();
			j.resetFinishTime();
			//enqueue back in
			storage.enqueue(j);
			initial.enqueue(j);
		}

		//processor queues
		int nprocessors = n; //number of processors

		Queue[] processor = new Queue[n+2]; //array of processors
		processor[0] = storage; //n
		processor[n+1] = complete;

		//make new processor queue per job
		for(int i = 0; i<n+1; i++){
			processor[i] = new Queue();
		}

		trace.println("**********************************");
		if(nprocessors == 1){
			trace.println(nprocessors + "1 processor:");
		}else{
			trace.println(nprocessors + " processors:");
		}
		trace.println("***********************************");

	}
}	

