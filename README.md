# Philosophers - Multithreading Challenge 
In this  assignment, I had to simulate the behavior of philosophers sitting around a round table, alternately eating, thinking, and sleeping. Their goal? To avoid dying of starvation.

Each philosopher needed to hold both the right and left forks to eat. Each action takes a certain amount of time to complete, as defined by the user in the program arguments. If the philosoper does not eat with in the timeframe provided, he dies- thus ending the program.

Developing the Philosophers project expanded my understanding of concurrent programming, synchronization mechanisms, and the importance of avoiding data races. It pushed my problem-solving skills to the limit and taught me a lot about complex threading scenarios.

## Implementation 
Each Philosopher is represented by a thread, with a final thread that "Monitors" the philosopher actions and checks that they are staying within time limits. One of the most significant challenges of this project was to ensure thread safety and avoid data races. With a ban on global variables, I had to come up with a synchronization mechanism using mutexes. This ensured that each philosopher had exclusive access to their forks, preventing conflicts. The program logs every action a philosopher takes, and announces their deaths within 10ms. 

## Usage
  - run make 
  - run the program with these arguments: number_of_philosophers time_to_die time_to_eat time_to_sleep
[number_of_times_each_philosopher_must_eat] (last argument is optional)
  - for example `./philo 5 800 200 200`
  - do not test with more than 200 philosophers!
  - Bon appétit!
 
