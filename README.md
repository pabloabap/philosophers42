# [Dining Philosophers Problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem)
This problem is about some philosophers that have a repetitive routine of:

> eat->sleep->think.
 
They must complete the routine avoiding deadth when possible.
In the dinning table each one has his own fork at one side (ex: right)
but, to eat, they need the fork of his colleague at the other side (ex: left).

The program receive `./philo <number_of_philosophers> <time_to_die time_to_eat>
<time_to_sleep> [<number_of_times_each_philosopher_must_eat>]`:
- `./philo`: Is the name of the program.
- `number_of_philosophers`: Number of philosophers, also number of forks.
	Philo number range is from 1 to this number and last philo sits at 
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
	- <*timestamp_in_ms*> <*X*> has taken a fork.
	- <*timestamp_in_ms*> <*X*> is eating.
	- <*timestamp_in_ms*> <*X*> is sleeping.
	- <*timestamp_in_ms*> <*X*> is thinking.
	- <*timestamp_in_ms*> <*X*> died.
   
	Replacing <*timestamp_in_ms*> by time since the simulation start
	in miliseconds and <*X*> by philo number.
- Logs must not been breaken by other philosophers.
- The maximum delay between philo death and its log must be 10ms.
- Each philo must be a **thread**.
- To avoid fork duplication, each one must be protected by a **mutex**. 


> The program must not have **data races**.


The method used to solve this concurrent problem is paralelizing philos/tasks
using threads and locking shared resources using mutex. It could also be solved
using processes and semaphores.

## Concepts
### Threads
Subtasks that can be run at the same time of other task.
Threads that share resources, added to that resources, are known as process.
Share resources between threads allow that one thread change them and the 
changes will be available to the other threads.
Things that are specific for each thread are:
- **Counter**: Register that tell the instruction where the thread is.
- **Stack**: Tell where the thread should return once finish the execution,
but it is also used to: store local data, parameters, evaluation stack and
pointers inter alia.
- **CPU status**

One process run at least until one of its execution threads is active. When a
process finish, all its threads do it too, and all the resources are free.

Threads status are: executing, done or locked. 

Threads status changes are: creation, lock, unlock or end.


> One process could have **subprocesses** that run **tasks in paralel but**
the difference is that these subprocesses **don't have shared resources**. In 
their creation they generate a local copy of the resources of the main process.

![Single vs Multithread](https://github.com/pabloabap/philosophers42/blob/main/Threads.svg)

### Mutex (Mutual Exclussion Algorithm)
Used in concurrent programming to avoid that more than one thread or process 
access to a critical section at the same time. **Critical section** is a frame 
of the code where shared resources are modified or used. Something similar in
real life could be a bathroom locker that locks the space when it is bussy and
can be unlocked once finished.

Types:
- **Tokens based**: A token is share between nodes, the node that has the token
can access to the critical section and if others need access they wait in a
queue of requestors until the token is available. Web servers is an example.
**This is the type I used in my program**.
- **Not token based**: Access to critical section is managed by shifts and 
messages, using time hints to garantee equitative access. Shared queue algorithm
is an example.
- **Quorums based**: Each node belong to a net divided in node subgroups 
(quorums). On a critical section access quorum is locked. Maekawa algorithm is
an example.

### Data races
Issue that happen when several threads or processes change data that others are
using. To avoid it **mutex** and **semaphores** are used to organize the access
to shared resources.
One exaple could be a cash machine that store available cash in memory.

Imagine a couple have a shared account with 100€ and both try to withdraw 100€ at
the same time. If the processes aren't syncronized both transactions happen
independently and cash machine lose 100€. Locking the resource that modify
the balance allow to syncronize the processes and cash machine work as expexted.

### Deadlock
Issue that lock a set of processes or execution threads in a concurrent systems.
It happen when some threads lock resources and require the resources locked by
other thread/process that also need other locked resources that won't be
unlocked until other locked resources are available.
In this exercise it could happen if each philosopher take his forks at the 
same time, so no one can take the second fork and all dead.

### Inanition
A resource required to complete a thread task is always denied.
If a priority ranks is defined it can cause that high priority processes
always lock resource required by low priority processes.
It can also happen if high priority processes wait low priority process
end that never have access to required resources.

## Implementation with threads and mutex
### Resources
 [CodeVault video's list about threads and mutex](https://www.youtube.com/watch?v=d9s_d28yJq0&list=PLfqABt5AS4FmuQf70psXrsMLEDQXNkLq2)
### Explanation
To solve the problem it's important to understand the concepts explained
above to surpass deadlocks and lock shared resources when needed.

In my case I create two structs:
```
// Struct with shared resources and common details.
typedef struct s_data
{
	int				philos_n;
	long long		start_ts;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				mandatory_meals;
	int				end_flag;
	pthread_mutex_t	*array_forks;
	pthread_mutex_t	*write;
	pthread_mutex_t	*end_flag_update;
	t_philo			*array_philos;
}					t_data;

// Struct with specific info of each philo.
typedef struct s_philo
{
	int				philo_id;
	long long		start_eat;
	long long		start_sleep;
	int				initial_delay;
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;
	pthread_t		*thread_id;
	struct s_data	*rules;
}					t_philo;
```
In the global structure 3 mutex types are created:
- `array_forks` is an array of mutex, one per fork to lock/unlock
eachone when needed.
- `write` locks the resource of write logs. In this way we prevente a mess
of messages if two processes try to write at the same time.
- `end_flag_update`lock the process of update the flag that indicates when
the program should stop (when all philos eat mandatory meals or when someone
dead).
Dead cases are managed by a supervisor in the main process that check dead 
condition of all philosophers.


Each philo is a thread and have a `thread_id` used to initialize his routine
and point to the mutex asigned to the forks available for him. They also have
a pointer to the general struct `rules` to check and update shared info.


#### How to avoid issues.
- **Deadlock**: To prevent deadthlock is important the order in which each
philo take and leave forks. 

	In my case **take instructions** are:
	- **ODD philo IDs** take right fork first.
	- **EVEN philo IDs** wait some miliseconds (initial_delay) and take
	left fork first.
	
	
	In this way it's garanteed that ODD philos eat first. In case that
	total number of philos is ODD first and last philo will fight to take
	thier second fork but the order doesn't mater because whoever eat first
	don't lock the process (instead of have 2 eat shifts the program will
	have 3). 
	

	**Leave instructions** is that all philos leave right forks first, then
	left one with small delay. In this way a delay will be generated to 
	garantee the meals order is the same in all the shifts (also when total
	number of philosopher is an even number).


- **Avoid message mess**: Lock with a mutex the action of write to
syncronize write actions and generate a write queue in case of write request
at the same time.


- **Print messages when expected** Supervisor is checking death status
everytime and is the resposible to write the deadth message. 
Philos update `end_flag_update` int when they complete 
mandatory meals and supervisor when someone die. Until this flag take
the expected value each philo continue his routine (loop). 

> It is important to **check the status of the flag in each loop and also
before the start of each action** (take fork, leave fork, eat, sleep and
thinks) to break the routine when end has the expected value.
Doing this we garantee that deadth message is show with less than
10ms of dealy and the last write action is the one expected.


Imagine that you only check this flag at the begining of each routine
loop, if a deadth happen at the middle of the routine the philo continue
his routine until end all his tasks.


### Allowed functions
`memset`, `printf`, `malloc`, `free`, `write`, `usleep`, `gettimeofday`, 
`pthread_create`, `pthread_detach`, `pthread_join`, `pthread_mutex_init`,
`pthread_mutex_destroy`, `pthread_mutex_lock` y `pthread_mutex_unlock`.

### Tests
1. Check that your program has a thread per philo.
2. Check that there are a fork per philo and each fork has a mutex.
3. Check that there aren't mixed messages in log outputs.
4. Check what happen when you start the program with non unsigned
numerical parameters (ex. ./philo a 12 12 12).
5. Check what happen when you start the program with less or more
than required parameters.
6. Test `./philo 1 800 200 200`. Philo should take one fork but not eat
and should die at milisecon 800, not at the beginning of the program 
(that is a hardcoded solution).
7. Test `./philo 5 800 200 200`. Philos shouldn't die.
8. Test `./philo 5 800 200 200 7`. Philos shouldn't die and the simulation
	should stop when all philos eat at least 7 times. **IMPORTAN** philos should
	eat until all ate 7 times, it means that some of them could each more than 7
	times. You can check it using bash cmd 
	`./philo  5 800 200 200 7 | grep eating | cut -d ' ' -f 2- | sort | uniq -c`.
	This command return something like: 
	```
	/** Removes timestamp, count the number of times each sentence is repeated and
	* write in the terminal this counter push the distinct generated sentences 
	* without the timestamp.
	*/
		8 1 is eating
		7 2 is eating
		8 3 is eating
		8 4 is eating
		7 5 is eating
	```
8. Test `./philo 4 410 200 200`. Philos shouldn't die.
9. Test `./philo 4 310 200 100`. One philo should die.
10. Test with two philos to check the different times and
deadth message delay is not greather than 10ms. 

## Implementation with processes and semaphores
In this implementation each **philo** must be a `process` and the main 
process must has a philo. Forks are in the middle of the table, don't have 
memory status but the **number of available forks is represented by a
a `semaphore`.
### Allowed functions
`memset`, `printf`, `malloc`, `free`, `write`, `fork`, `kill`, `exit`, 
`pthread_create`, `pthread_detach`, `pthread_join`, `usleep`, `gettimeofday`, 
`waitpd`, `sem_open`, `sem_close`, `sem_post`, `sem_wait`, `sem_unlink`.


