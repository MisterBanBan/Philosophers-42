Philosophers Project
---------------------------------------
This is a project for the school 42. The project implements the problem of (Dining philosophers problem), It allows us to work with using threads and synchronization. For this the project asks us to recreate a philosophizing dinner. 
Wikipedia sources : https://en.wikipedia.org/wiki/Dining_philosophers_problem.

Installation
---------------------------------------
1. Clone the Repository
Clone the project repository to your local machine using the following command:<br>
```bash
 git clone git@github.com:MtBanBann/Philosophers-42.git
```
2. Build the Program
Navigate to the project directory and build the executable using the ```make``` command:<br>
```bash
 cd Philosophers-42
 make
```



Uses
---------------------------------------
To run the program, simply execute the ./philo binary with the following arguments:
```bash
./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]
```
Argument Details:

1. ```<number_of_philosophers>```<br>
Specifies the number of philosophers seated at the table.<br><br>
2. ```<time_to_die>```<br>
The maximum time (in milliseconds) a philosopher can go without eating before they starve.<br><br>
3. ```<time_to_eat>```<br>
The time (in milliseconds) it takes for a philosopher to eat.<br><br>
4. ```<time_to_sleep>```<br>
The time (in milliseconds) a philosopher spends sleeping.<br><br>
5. ```[number_of_times_each_philosopher_must_eat] ```(optional)<br>
Specifies how many times each philosopher must eat before the simulation ends. If omitted, the simulation continues indefinitely.<br><br>
  
Example
-------------------------------------------

To simulate 4 philosophers where each has the following conditions:

• Maximum time without eating: 410 ms<br>
• Time to eat: 200 ms<br>
• Time to sleep: 200 ms<br>
• Each philosopher must eat at least 5 times<br>

Run the following command:

```bash
./philo 4 410 200 200 5
```

About the Problem
-------------------------------------------

The Dining Philosophers Problem explores issues of resource sharing and synchronization in concurrent systems. Philosophers alternate between thinking, eating, and sleeping, competing for shared resources (forks). The program ensures no philosopher starves, and proper synchronization prevents deadlocks or race conditions.
