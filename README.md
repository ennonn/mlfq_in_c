# Multi-Level Feedback Queue (MLFQ) Scheduler in C

[Replit](#https://replit.com/@AljonFernando/MultiLevelFeedbackQueueAlgorithm)
This repository contains a C program implementing a Multi-Level Feedback Queue (MLFQ) scheduler. The MLFQ scheduler is designed to manage processes with different burst times across multiple priority levels. Processes move to lower priority queues if they exceed their time slice in the current queue, eventually being executed in a First-Come-First-Served (FCFS) manner.

## Program Overview

The program is structured as follows:

1. **Definitions and Data Structures:**
   - **Constants:**
     - `NUM_QUEUES`: The number of priority queues (3 in this case).
     - `TIME_SLICE`: The time slice each process gets to run in each queue before potentially being demoted.
     - `NUM_PROCESSES`: The total number of processes (5 in this case).
   - **Process Structure:**
     - `pid`: Process ID.
     - `burst_time`: Time required by the process for execution.
     - `remaining_time`: How many times the process needs to run in each queue before moving to the next one.
   - **Queue Structure:**
     - `processes`: An array to hold pointers to processes.
     - `front` and `rear`: Indices to manage the queue operations.

2. **Queue Operations:**
   - `create_queue()`: Initializes a new queue.
   - `enqueue()`: Adds a process to the end of the queue.
   - `dequeue()`: Removes a process from the front of the queue.
   - `is_empty()`: Checks if the queue is empty.

3. **Main Function:**
   - **Initialization:**
     - Define processes with different burst times and remaining times.
     - Create queues for different priority levels.
     - Initially enqueue all processes into the highest priority queue.
   - **MLFQ Scheduling:**
     - For each priority queue, processes are dequeued and executed for one time slice.
     - If a process has remaining time after the time slice, it is moved to the next lower priority queue.
   - **Final FCFS Queue:**
     - Once processes have been through all priority queues, they are executed in a First-Come-First-Served manner.

## Code
**Detailed Explanation**
***Let's go through the main function and understand each part:***


```c
int main() {
    // Define processes with different burst times and remaining times.
    Process processes[NUM_PROCESSES] = {
        {1, 1, 3},
        {2, 2, 3},
        {3, 3, 3},
        {4, 4, 3},
        {5, 5, 3}
    };
```
Here, we define five processes with different burst times but the same remaining time (3). The remaining time indicates how many time slices the process should be executed in each queue before being moved to a lower priority queue.


```c
    // Create queues for different priority levels.
    Queue* queues[NUM_QUEUES + 1]; // Last queue is FCFS
    for (int i = 0; i <= NUM_QUEUES; i++) {
        queues[i] = create_queue();
    }

    // Enqueue processes into the highest priority queue initially
    for (int i = 0; i < NUM_PROCESSES; i++) {
        enqueue(queues[0], &processes[i]);
    }
```
We create an array of queues. The NUM_QUEUES + 1 includes an additional queue for the FCFS scheduling at the end. Initially, all processes are enqueued into the highest priority queue (queues[0]).


```c
    int time = 0;
    for (int q = 0; q < NUM_QUEUES; q++) {
        int queue_size = queues[q]->rear;
        for (int i = 0; i < queue_size; i++) {
            Process* process = dequeue(queues[q]);
            printf("Time %d: Executing Process %d from Queue %d\n", time++, process->pid, q + 1);
            process->remaining_time--;
            if (process->remaining_time > 0) {
                enqueue(queues[q + 1], process);
            }
        }
    }
```
For each priority queue (q ranging from 0 to NUM_QUEUES - 1), we:

1. Get the current size of the queue.
2. Dequeue each process from the current queue and execute it for one time slice.
3. Print the current time and which process is being executed from which queue.
4. Decrement the remaining_time of the process.
5. If the process still has remaining time, enqueue it to the next lower priority queue.


```c
    // Move all processes to FCFS queue
    for (int i = 0; i < NUM_PROCESSES; i++) {
        enqueue(queues[NUM_QUEUES], &processes[i]);
    }
```
After all processes have been through the priority queues, they are moved to the FCFS queue (queues[NUM_QUEUES]).


```c
    while (!is_empty(queues[NUM_QUEUES])) {
        Process* process = dequeue(queues[NUM_QUEUES]);
        printf("Time %d: Executing Process %d from FCFS Queue\n", time, process->pid);
        time += process->burst_time;
        printf("Process %d finished at time %d\n", process->pid, time);
    }

    // Free memory
    for (int i = 0; i <= NUM_QUEUES; i++) {
        free(queues[i]);
    }

    return 0;
}
```
Finally, in the FCFS queue:

1. Dequeue each process and execute it.
2. Print the current time and which process is being executed from the FCFS queue.
3. Increment the time by the burst_time of the process.
4. Print the completion time of the process.
5. The memory for each queue is then freed, and the program ends.


***Example output***
```c
Time 0: Executing Process 1 from Queue 1
Time 1: Executing Process 2 from Queue 1
Time 2: Executing Process 3 from Queue 1
Time 3: Executing Process 4 from Queue 1
Time 4: Executing Process 5 from Queue 1
Time 5: Executing Process 1 from Queue 2
Time 6: Executing Process 2 from Queue 2
Time 7: Executing Process 3 from Queue 2
Time 8: Executing Process 4 from Queue 2
Time 9: Executing Process 5 from Queue 2
Time 10: Executing Process 1 from Queue 3
Time 11: Executing Process 2 from Queue 3
Time 12: Executing Process 3 from Queue 3
Time 13: Executing Process 4 from Queue 3
Time 14: Executing Process 5 from Queue 3
Time 15: Executing Process 1 from FCFS Queue
Process 1 finished at time 16
Time 16: Executing Process 2 from FCFS Queue
Process 2 finished at time 18
Time 18: Executing Process 3 from FCFS Queue
Process 3 finished at time 21
Time 21: Executing Process 4 from FCFS Queue
Process 4 finished at time 25
Time 25: Executing Process 5 from FCFS Queue
Process 5 finished at time 30
```


**Summary**

***MLFQ Scheduler: Manages processes in multiple priority levels, demoting processes to lower priorities if they exceed their time slice.***
***Queues: Implemented using arrays and managed with enqueue and dequeue operations.***
***Processes: Have different burst times and are moved through priority queues until they reach the FCFS queue.***
***Output: Prints the execution of each process at each time unit, including when they are moved to the FCFS queue and their completion times.***
