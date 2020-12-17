#include<iostream>
#include<fstream>
#include <stdlib.h> 
using namespace std;
class Process
{
	int pid;								//Process ID 
	int at;									//Arrival Time of the Process
	int bt;									//Burst Time of the Process
	int ct;									//Completion Time of the Process	
	int tat;								//Turn Around Time of the Process	
	int wt;									//Waiting Time of the Process
	int rt;									//Response Time of the Process	
	int at_temp;							//Temp at 
	int bt_temp;							//Temp bt
	static int id;
	
	public:	
		Process()								
		//Constructor of class Process :: Sets the pid 
		{
	    	id++;
			pid = id;
			bt_temp = 0;
		}
		void Display();
		void setAT_BT(int, int);				//sets the value of at and bt
		void setCT(int, int);					//sets the value of ct
		void setTAT();							//sets the value of tat
		void setWT();							//sets the value of wt
		void setRT(int);						//srts the value of ct
		void run()								
		{
		/*increments bt_temp*/
			bt_temp+=1;
		}
		
		void run_AT(int quant)					
		{
		/*increments at_temp by quant*/
			at_temp+=quant;
		}
		
		int getAT()
		{							
		/*returns value of at*/
			return at;
		}
		
		int getCT(){							
		/*returns value of ct*/
			return ct;
		}
		
		int getBT(){							
		/*returns value of bt*/
			return bt;
		}
		
		int getRT()
		{							
		/*returns value of rt*/
			return rt;
		}
		
		int getWT()
		{							
		/*returns value of wt*/
			return wt;
		}
		
		int getPID()
		{							
		/*returns value of pid*/
			return pid;
		}
		
		int getTAT(){							
		/*returns value of tat*/
			return tat;
		}
		
		int getAT_temp()
		{						
		/*returns value of at_temp*/
			return at_temp;
		}
		
		int getTEMP()
		{							
		/*returns value of bt_temp*/
			return bt_temp;
		}
};

	int Process::id= 0;			    	//static int id defination
	
	void Process::Display()						
	/* This member function displays AT, BT, CT, TAT, WT and RT of the given process*/
	{
		cout<<"\nProcess ID: "<<pid;
		cout<<"\nArrival Time :"<<at;
		cout<<"\nBurst Time :"<<bt;
		cout<<"\nCompletion Time :"<<ct;
		cout<<"\nTurn Around Time :"<<tat;
		cout<<"\nWaiting Time :"<<wt;
		cout<<"\nResponse Time :"<<rt<<"\n";
	}
	
	void Process::setCT(int i, int j)			
	/*This member function is used to set CT and call thse setTAT() and setWT()*/
	{
		ct = i;            
		setTAT();
		setWT();
	}
	
	void Process::setTAT()						
	/*This member function is used to set TAT*/ 
	{
		tat = ct - at;
	}
	
	void Process::setWT()						
	/*This member function is used to set wT */
	{
		wt = tat - bt;
	}
	
	void Process::setRT(int t)					
	/*This member function is used to set RT */
	{
		rt= t-at;
	}
	
	void Process::setAT_BT(int i, int j)		
	/*This member function is used to set AT and BT*/
	{
		at = i;
		bt = j;
		at_temp = at;
	}
	
	void swap(Process *x, Process *y) 			
	/*Function to swap the postion of two processes*/
	{
	    Process temp = *x; 
	    *x = *y; 
	    *y = temp; 
	} 

	void sort(Process arr[], int n)				
	/*Function to sort the process array on the basis of AT*/
	{
		Process temp; 
		for (int i = 0; i < n-1; i++)
		{
	    	for (int j = 0; j < n-i-1; j++)
	    	{
	        	if (arr[j].getAT() > arr[j+1].getAT())
				{
	            	swap(&arr[j], &arr[j+1]); 
	        	}
	        }
	    }
	}

class Process_Creator
{
	Process process_array[20]; 
	public:
		
		Process_Creator()					
		/*Constructor of class Process_Creator: sets the value of at and bt for all processes*/
		{
			for(int j=0;j<20;j++)
			{
				process_array[j].setAT_BT(1 + (rand() % 20),1 + (rand() % 20));		//assigns random values between 1-20 to both at and bt
			}
			sort(process_array,20);
		}	
		
		Process* getarr()					
		/*returns process array's address*/
		{
			return process_array;
		}	
};

class Node 
/* QUEUE NODE*/ 
{ 
    public:
    	Process p;
    	Node* next; 
}; 

class Queue									
/*Datastructure Queue*/
{
	public:	
		Node* head;
		
		Queue()
		{
        	head = NULL;
    	}
    	
    	void enqueue(Process p);
	    Process dequeue(); 
};

	void Queue :: enqueue(Process p) 			
	/*member function that pushes a new process at the end of the queue*/
	{
	   Node* new_node = new Node();
	   new_node->p = p;
	   new_node->next = NULL;
	   Node* current = head;
	   if (head == NULL)
	   {
	   		head = new_node;
	   }
	   else
	   {
	   		while (current->next != NULL) 
	        	current = current->next; 
	    	current->next = new_node;
	   }
	}
	
	Process Queue :: dequeue() 					
	/*member function that pops the first process from the queue*/
	{
	   	Process temp;
	   if (head == NULL)
	   {
	   		cout<<"ERROR";
	   }
	   else
	   {
	   		temp = head->p;
	   		head = head->next;
	   }
	   
	   	return temp;
	} 

void PID_sort(Process arr[], int n) 		
/*fuction to sort the process array in the order of PID*/
{
	Process temp; 
	for (int i = 0; i < n-1; i++)
	{
    	for (int j = 0; j < n-i-1; j++)
    	{
        	if (arr[j].getPID() > arr[j+1].getPID())
			{
            	swap(&arr[j], &arr[j+1]); 
        	}
        }
    }
}

int sim_time;
void Status_txt(Process P, int T, int mode, int type)	
/*function that appends the status of the process at the given time period*/
{
	if(T <= sim_time)
	{
		fstream file; 
		if(type == 1)
    	{
    		file.open("Status_FCFS.txt", ios::out | ios::app);
		}
		else if(type == 2)
		{
			file.open("Status_SRTF.txt", ios::out | ios::app); 
		}
		else if(type == 3)
		{
			file.open("Status_RR.txt", ios::out | ios::app); 
		}
		string status;
		/*STATUS OF THE PROCESS*/
    	if(mode == 1)
    	{
    		status = "Arrived";
		}
		else if(mode == 2)
		{
			status = "Running";
		}
		else if(mode == 3)
		{
			status = "Exit";
		}
		file<<T<<"\t"<<P.getPID()<<"\t"<<status<<"\n";
		file.close();
	}
}

class Scheduler
{
	int tq;
	Process_Creator pc;
	public:
		Queue q;
		Queue FCFS(Process pro[], int type);
		Queue SRTF(Process pro[], int type);
		Queue RR(Process pro[], int tq, int type);
		friend void Status_txt(Process P, int T, int mode, int type);
		
		Scheduler(int t)		
		/*Constructor of class Scheduler: calls specific member functions according to parameter t*/
		{
			int i= t;
			if(i ==1)
			{
				q = FCFS(pc.getarr(), t);
			}
			else if(i==2)
			{
				q = SRTF(pc.getarr(), t);
			}
			else if(i==3)
			{
				cout<<"Enter The Time Quantam: ";
				cin>>tq;
				q = RR(pc.getarr(),tq, t);
			}
		}
};
	
	Queue Scheduler::FCFS(Process pro[], int type)	
	/*First Come First Serve Scheduling*/
	{
		Process pro1[20];
		Queue rq;								    	//Ready Queue
		Queue wq;								    	//Waiting Queue
		Queue q1;
		int t = pro[0].getAT();
		int count = 0,q_size = 0,index = 0;
		int t1;
		while(count < 20)
		{
			if(index < 20)
			{
				while(pro[index].getAT_temp()<= t)
				{
					if(q_size < 10)
					{
						rq.enqueue(pro[index]);
						Status_txt(pro[index],t,1,type);
						index++;
						q_size++;
					}
					else
					{
						wq.enqueue(pro[index]);
						index++;
					}
					
				}
			}
				Process p = rq.dequeue();
				p.run();
				
				if(p.getTEMP() == 1)
				{
					p.setRT(t);
					Status_txt(p,t,2,type);
				}
				if(p.getBT()- p.getTEMP() == 0)
				{
					p.setCT(t+1,1);
					pro1[count] = p;
					Status_txt(p,t+1,3,type);
					count++;
					q_size--;
					if(wq.head != NULL)
					{
						p = wq.dequeue();
						rq.enqueue(p);
						Status_txt(p,t+1,1,type);
						q_size++;
					}		
				}
				else
				{
					for(int k = 0; k < q_size-1; k++)
					{
						rq.enqueue(p);
						p = rq.dequeue();
					}
					rq.enqueue(p);
				}
			t++;
		}
		pro = pro1;
		PID_sort(pro,20);
		for(int i = 0; i < 20; i++)
			q1.enqueue(pro[i]);
		return q1;	
	}
	
	Queue Scheduler::SRTF(Process pro[], int type)	
	/*Shortest Remaining Time First Scheduling*/
	{
		Process pro1[20];
		Queue rq;								   	//Ready Queue
		Queue wq;							    	//Waiting Queue
		Queue q1;
		int t  = pro[0].getAT();
		int count = 0,q_size = 0,index = 0;
		int t1;
		int pid;
		while(count < 20)
		{
			if(index<20)
			{
				while(pro[index].getAT_temp()<= t)
				{
					if(q_size < 10)
					{
						rq.enqueue(pro[index]);
						Status_txt(pro[index], t, 1, type);
						index++;
						q_size++;
					}
					else
					{
						wq.enqueue(pro[index]);
						index++;
					}	
				}
			}
				int mn = 21,at;
				Queue current = rq;
				while(current.head != NULL)
				{
					Process p = current.dequeue();
					if(p.getBT() - p.getTEMP() < mn)
					{
						mn = p.getBT();
						pid = p.getPID();
						at = p.getAT();
					}
					else if(p.getBT() - p.getTEMP()== mn)
					{
						if(p.getAT() < at)
						{
							mn = p.getBT();
							pid = p.getPID();
							at = p.getAT();
						}
					}
				}
				Process p = rq.dequeue();
				while(p.getPID()!= pid)
				{
					rq.enqueue(p);
					p = rq.dequeue();
				}
				p.run();
				if(p.getTEMP() == 1)
				{
					p.setRT(t);
					Status_txt(p, t, 2, type);
				}
				if(p.getBT() == p.getTEMP())
				{
						p.setCT(t + 1,2);
						Status_txt(p, t + 1, 3, type);
					pro1[count]=p;
					count++;
					q_size--;
					if(wq.head != NULL)
					{
						p = wq.dequeue();
						rq.enqueue(p);
						Status_txt(p, t+1, 1, type);
						q_size++;
					}
				}
				else
				{
					rq.enqueue(p);
				}
			t++;	
		}
		pro = pro1;
		PID_sort(pro, 20);
		for(int i = 0; i < 20; i++)
			q1.enqueue(pro[i]);
		return q1;
	}
	
	Queue Scheduler::RR(Process pro[], int tq, int type)	
	/*Round Robin Scheduling*/
	{
		Process pro1[20];
		Queue rq;								    	//Ready Queue
		Queue wq;									   //Waiting Queue
		Queue q1;
		Process p;
		int t = pro[0].getAT();
		int count = 0,q_size = 0,index = 0;
		int t1;
		int check;
		int t2;
		int pid;
		bool lock = false;
		while(count < 20)
		{
			if(index < 20)
			{
				while(pro[index].getAT_temp() <= t)
				{
					if(q_size < 10)
					{
						rq.enqueue(pro[index]);
						Status_txt(pro[index],t,1,type);
						index++;
						q_size++;
					}
					else
					{
						wq.enqueue(pro[index]);
						index++;
					}
				}
			}
			if(lock == false)
			{	
				p = rq.dequeue();
				lock = true;
				if(p.getAT()+p.getBT()-p.getAT_temp() >= tq)
				{
					t1 = tq;
				}
				else
				{
					t1 = p.getAT()+p.getBT()-p.getAT_temp();
				}
				t2 = t1;
			}
			if(t2-t1 == 0)
			{
				Status_txt(p,t,2,type);
			}
			p.run_AT(1);
			if(p.getAT_temp()-p.getAT() == 1)
				{
					p.setRT(t);
				}
			t1--;
			if(t1 == 0)
			{
				lock = false;
				if(p.getAT()+p.getBT()-p.getAT_temp() > 0)
				{
					rq.enqueue(p);
				
				}
				else
				{
					p.setCT(t+1, 2);
					Status_txt(p, t+1, 3, type);	
					pro1[count]=p;
					count++;
					q_size--;
					if(wq.head != NULL)
					{
						p = wq.dequeue();
						rq.enqueue(p);
						Status_txt(p, t+1, 1, type);
						q_size++;
					}
				}
			}
			t++;
		}
		PID_sort(pro1, 20);
		pro = pro1;
		for(int i = 0; i < 20; i++)
			q1.enqueue(pro[i]);
		return q1;
	}

class Simulator
{
	public:
		
		Simulator(int type)
		/*Constructor of class Process_Creator: creates an objedt of class Scheduler and calls member function Processes_txt*/
		{
			Scheduler s(type);
			Processes_txt(s.q,type);
		}
		
		void Processes_txt(Queue, int);	
};

	void Simulator::Processes_txt(Queue q, int type) 
	/* this function creates a file "Process.txt" and saves the details of the process i.e. PID, AT, BT, TAT, WT and RT*/
	{
		fstream file;
		//Opens file according to the type of Scheduler run
		if(type == 1)
	    {
	    	file.open("Process_FCFS.txt", ios::out | ios::app);
		}
		else if(type == 2)
		{
			file.open("Process_SRTF.txt", ios::out | ios::app);
		}
		else if(type == 3)
		{
			file.open("Process_RR.txt", ios::out | ios::app);
		} 
	    file <<"PID\tAT\tBT\tCT\tTAT\tWT\tRT\n"; 
		/* Column Headers for Process.txt files*/
	    file <<"--\t--\t--\t--\t---\t--\t--\n";  
		for(int i=0;i<20;i++)
		{
			Process p = q.dequeue();
			file<<p.getPID()<<"\t"<<p.getAT()<<"\t"<<p.getBT()<<"\t"<<p.getCT()<<"\t"<<p.getTAT()<<"\t"<<p.getWT()<<"\t"<<p.getRT()<<"\n";
		}
		file.close();
	}

/*Main Funcion*/
int main()
{
	int type;
	cout<<".....CPU SCHEDULING.....\n";
	cout<<"Enter Simulation Time: ";
	cin>>sim_time;
	/* Takes the simulation time from the user.*/
	cout<<"Enter the Scheduling type\n";
	cout<<"1. First Come First Serve\n";
	cout<<"2. Shortest Job First\n";
	cout<<"3. Round Robin\n";
	cout<<"Input: ";
	/* Takes the type of Scheduling from the user*/
	cin>>type;
	fstream file; 
	if(type == 1)
    {
    	file.open("Status_FCFS.txt", ios::out | ios::app);
	}
	else if(type == 2)
	{
		file.open("Status_SRTF.txt", ios::out | ios::app); 
	}
	else if(type == 3)
	{
		file.open("Status_RR.txt", ios::out | ios::app); 
	}
    file<<"Time\tPID\tStatus\n"; 
	file.close();
	cout<<"Scheduler Start\n";
	/* Scheduler starts execution*/
	Simulator sim(type);
	cout<<"Scheduler Stop";
	/* Scheduler completes execution*/
	return 0;
}
