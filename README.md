# [Dining Philosophers Problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem)
This problem is about some philosophers that have a repetitive routine of:

> eat->sleep->think.
 
They must complete the routine avoiding deadth when possible.
In the dinning table each one has his own fork at one side (p.ex: right)
but, to eat, they need the fork of his colleague at the other dise (left).

The program receive `./philo number_of_philosophers time_to_die time_to_eat
time_to_sleep [number_of_times_each_philosopher_must_eat]`:
- `./philo`: Is the name of the program.
- `number_of_philosophers`: Number of philosophers, and also number of forks.
	philo number start at 1 to this number. Also the last philo sits at 
	the right of first one. If one philo only one fork exist.
- `time_to_die` (miliseconds): If a philosopher doesn't start eating in this
   frame of time since the program start or since his last meal, die.
- `time_to_eat` (miliseconds): Required time to eat, in this time forks are
	locked.
- `time_to_sleep` (miliseconds): Required time to sleep.
- `number_of_times_each_philosopher_must_eat` (optional): If all philos
	eat at least this number of times, the simulation stop. If not specified,
	simulation will stop on philo deadth.

Other considerations:
- The don't talks inbetween.
- They don't know if other philo will die.
- The program must show the logs:
	- *timestamp_in_ms* *X* has taken a fork.
	- *timestamp_in_ms* *X* is eating.
	- *timestamp_in_ms* *X* is sleeping.
	- *timestamp_in_ms* *X* is thinking.
	- *timestamp_in_ms* *X* died.
   
	Replacing *timestamp_in_ms* by time passed since the simulation start
	in miliseconds and *X* by philo number.
- Logs must not been breaken by other philosophers.
- The maximum delay between philo death and its log must be 10ms.
- Each philo mut be a **thread**.
- To avoid fork duplication, each one must be protected by a **mutex**. 
> The program must not have **data races**.

The way used to solve this concurrent problem is paralelizing philos/tasks
using threads and locking shared resources updates using mutex.

## Concepts
### Threads
TBD
### Mutex
TBD
### Data races
TBD
### Deadlock
TBD
### Inanition
TBD

## Implementation with threads and mutex
### Explanation
TBD
### Allowed functions
`memset`, `printf`, `malloc`, `free`, `write`, `usleep`, `gettimeofday`, 
`pthread_create`, `pthread_detach`, `pthread_join`, `pthread_mutex_init`,
`pthread_mutex_destroy`, `pthread_mutex_lock` y `pthread_mutex_unlock`.

## Implementation with processes and semaphores
In this implementation each **philo** must be a **process** and the main 
process must has a philo. Forks are in the middle of the table, don't have 
memory status but the **number of available forks is represented by a
a semaphore**.
### Allowed functions
`memset`, `printf`, `malloc`, `free`, `write`, `fork`, `kill`, `exit`, 
`pthread_create`, `pthread_detach`, `pthread_join`, `usleep`, `gettimeofday`, 
`waitpd`, `sem_open`, `sem_close`, `sem_post`, `sem_wait`, `sem_unlink`.


