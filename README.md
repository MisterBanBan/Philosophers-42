Philosophers Project
---------------------------------------
This is a project for the school 42. The project implements the problem of (Dining philosophers problem), It allows us to work with using threads and synchronization. For this the project asks us to recreate a philosophizing dinner. 
Wikipedia sources : https://en.wikipedia.org/wiki/Dining_philosophers_problem.

Installation
---------------------------------------
1. Clone the repository: git clone git@github.com:MtBanBann/Philosophers-42.git
2. Build the program: make

Usage
To run the program, simply execute the ./philo binary with the following arguments:

./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]

The explanations of each argument:

<number_of_philosophers>: the number of philosophers that will be seated 
                          at the table.

<time_to_die>: the maximum time (in milliseconds) a philosopher can go 
               without eating before dying.

<time_to_eat>: the time (in milliseconds) it takes for a philosopher to eat.

<time_to_sleep>: the time (in milliseconds) it takes for a philosopher to sleep.

[number_of_times_each_philosopher_must_eat]: (optional) the number of times 
                                             each philosopher must eat before the 
                                             simulation ends.

Example
-------------------------------------------

Here is an example of how to run the program with 4 philosophers who each have 410 milliseconds to live without food, 200 milliseconds to eat, and 200 milliseconds to sleep, and each must eat at least 5 times:
