# CPU Scheduling
This C++ program is designed to simulate the behavior of a CPU scheduler, i.e., choose a process from the ready queue based on a scheduling algorithm to execute it by the processor.

#### CLASSES:
The simulator consists of the following classes:

##### 1) Process: 
This class is used to store Process ID, Arrival Time, Burst Time, Completion Time , Turn Around Time, Waiting Time and the Response Time of a process.
  - ##### Data Members:
      - ***pid:*** Process ID
      - ***at:*** Arrival Time of process
      - ***bt:*** Burst Time of process
      - ***ct:*** Completion Time of process
      - ***tat:*** Turn Around Time of process
      - ***wt:*** Waiting Time of process
      - ***rt: Response Time of process***
      - ***at_temp:*** new arrival time(used in Round Robin)
      - ***bt_temp:*** time completed from the burst time
    
  - ##### Constructor is used to set the PID of the Process so that every Process gets a unquie PID.


  - ##### Member functions of this class are:
      - ***Display:*** used to display pid, at, bt, ct, tat, wt and rt of the process
      - ***setAT_BT:*** used to set the data members at and bt
      - ***setCT:*** used to set the data member ct and call the member function setTAT and setWT
      - ***setTAT:*** used to set the data member tat
      - ***setWT:*** used to set the data member wt
      - ***setRT:*** used to set the data member rt
      - ***getAT:*** returns at of the process
      - ***getBT:*** returns bt of the process
      - ***getCT:*** returns ct of the process
      - ***getRT:*** returns rt of the process
      - ***getTAT:*** returns tat of the process
      - ***getAT_temp:*** returns at_temp 
      - ***getTEMP:*** returns bt_temp
      - ***run:*** increments bt_temp
      - ***quata:*** increments at_temp


##### 2) Process_Creator: 
This class creates an array of processes and assigns random arrival time and burst time to each process. 

  - ##### Data Members:
      - ***process_array:*** an array of type process used to store processes
    
  - ##### Constructor is used to create an array of 20 processes with random arrival time and burst time.


  - ##### Member functions of this class are:
    - ***getarr:*** returns process_array

##### 3) Scheduler: 
This class implements the scheduling algorithms, viz., First Come First Serve (FCFS),Shortest Remaining Time First (SRTF), and Round Robin. The class maintain a ready queue of fixed capacity. 
  - ##### Data Members:
      - ***tq:*** Time quantam
      - ***pc:*** object of class Process_Creator
      - ***q:*** Queue
    
  - ##### Constructor is used to select the type of Scheduler to be used and to call the function to execute the scheduling algorithm.
  

  - ##### Member functions of this class are:
      - ***FCFS:*** This function is used to execute the process in the order they arrive and this scheduling algorithm is non-preemptive
    	> **Algorithm:**
    	> ->Loop is executed until 20 elements are inserted into the new process array pro1 and every in every iteration of the loop time is incremented by one second.
    	> ->If at current time new processes arrive then, the new processes are inserted into the ready queue if the number of processes in ready queue are less than the max limit of ready queue. If the max limit of ready queue arrives, then the processes are inserted into the waiting queue. (NOTE: When the process arrives to the ready queue at that moment "Arrived" is printed to the status.txt)
    	> ->The first element is popped from the ready queue and executed for time = burst time of that process.(NOTE: When the process executes for the first time "Running" is 	printed to 	the status.txt)
    	> ->As soon as the process completes execution, the completed process's completion time is noted and the process is appended to pro1 and if there is a process in waiting queue, then a process is transferred from the waiting queue to the ready queue.(NOTE: When the process completes execution "Exited" is printed to the status.txt)
    	> ->Step  2-4 are repeated until 20 process are appended to pro1.

      - ***SRTF:*** This function is used to execute the process with the shortest burst time first and this scheduling algorithm is preemptive
	    > **Algorithm:**
	    > ->Loop is executed until 20 elements are inserted into the new process array pro1 and every in every iteration of the loop time is incremented by one second.
	    > ->If at current time new processes arrive then, the new processes are inserted into the ready queue if the number of processes in ready queue are less than the max limit of ready queue. If the max limit of ready queue arrives, then the processes are inserted into the waiting queue. (NOTE: When the process arrives to the ready queue at that moment "Arrived" is printed to the status.txt)
	    > ->The process with the least remaing burst time is popped from the ready queue and executed for 1 sec.(NOTE: When the process executes for the first time "Running" is 	printed to 	the status.txt)
	    > -> If the remaining Burst Time of the process is not equal to zero the process is again added back to the ready queue. But if the remaining burst time is now equal to zero, then the completed process's completion time is noted and the process is appended to pro1 and if there is a process in waiting queue, then a process is transferred from the waiting queue to the ready queue.(NOTE: When the process completes execution "Exited" is printed to the status.txt)
	    > ->Step  2-4 are repeated until 20 process are appended to pro1.
	    
      - **RR:** This function is used to execute the process in the order they arrive, but every process is executed atmost a time quantam specified and this scheduling algorithm is preemptive.
	    > **Algorithm:**
	    > ->Loop is executed until 20 elements are inserted into the new process array pro1 and every in every iteration of the loop time is incremented by one second.
	    > ->If at current time new processes arrive then, the new processes are inserted into the ready queue if the number of processes in ready queue are less than the max limit of ready queue. If the max limit of ready queue arrives, then the processes are inserted into the waiting queue. (NOTE: When the process arrives to the ready queue at that moment "Arrived" is printed to the status.txt)
	    > ->The first element is popped from the ready queue and t1 is calculated.(Here t1 = equal to time quantam if remaining burst time is greater than time quantam else is equal to remaining burst time if remaining burst time is less than time quantam.
	    > ->Now lock is turned on so that only this process is executed for t1 sec.(because of this lock step 3 doesnt take place and this process is executed for t1 sec. NOTE: When the process executes for the first time "Running" is printed to the status.txt)
	    > ->When the process has executed for t1 seconds, the lock is turned off. If after execution for t1 seconds, the remaining burst time is not equal to zero the process is added back to the ready queue. But if the remaining burst time is now equal to zero, then the completed process's completion time is noted and the process is appended to pro1 and if there is a process in waiting queue, then a process is transferred from the waiting queue to the ready queue.(NOTE: When the process completes execution "Exited" is printed to the status.txt) 
	    > ->Step  2-5 are repeated until 20 process are appended to pro1.
	    
      - ***Status_txt(friend)***

##### 4) Simulator: 
This class starts the simulation and creates a file where all details of processes are stored.
  - ##### Data Members:
      - ***s:*** object of class Scheduler
    
  - ##### Constructor call the constructor of scheduler s and then call the member function Processes_txt


  - ##### Member functions of this class are:
      - ***Processes_txt:*** this function creates a file "Process.txt" and saves the details of the process i.e. PID, AT, BT, TAT, WT and RT.

#### OTHER FUNCTIONS:
   1) ***swap:*** function that swaps the location of the two processes
   2) ***sort:*** function that sorts the process array in order of their arrival time
   3) ***PID_sort:*** function that sorts the process array in order of their PID
   4) ***Status_txt:*** function that appends the status of the process at the given time period

#### ASSUMPTIONS:
   1) Total number of process: 20
   2) Size of ready queue: 10
   3) The random value of arrival time and burst time assigned are between 1 and 20***.
   4) When two process have the same arrival time and only one process can be pushed into the ready queue pid is taken into consideration.

#### ABOUT SIMULATION TXT FILES:
   1) ***Simulation Time:*** 100 ms
   2) ***Time Quantam of Round Robin:*** 5 ms
   