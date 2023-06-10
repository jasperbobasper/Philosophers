# Philosophers - The Deadly Quest for Sustenance
In this challenging assignment, I successfully tackled the task of simulating the behavior of philosophers sitting around a round table, alternately eating, thinking, and sleeping. Their goal? To avoid the deadly fate of starvation.

The simulation revolved around a round table with a large bowl of spaghetti placed at its center. To ensure a smooth dining experience, each philosopher needed to hold both the right and left forks to eat. And to avoid any mishaps, it was crucial to handle forks with care, preventing duplication or conflicts.

One of the most significant challenges of this project was to ensure thread safety and avoid data races. With the strict prohibition of global variables, I had to devise a robust synchronization mechanism using mutexes. This ensured that each philosopher had exclusive access to their forks, preventing conflicts. The program logs every action a philosopher takes, and announces their deaths within 10ms. 

Developing the Philosophers project expanded my understanding of concurrent programming, synchronization mechanisms, and the importance of avoiding data races. It pushed my problem-solving skills to the limit and enhanced my ability to handle complex threading scenarios.

##Usage
  - run make 
  - run the program with these arguments: number_of_philosophers time_to_die time_to_eat time_to_sleep
[number_of_times_each_philosopher_must_eat] (last argument is optional)
  - for example `./philo 5 800 200 200`
  - do not test with more than 200 philosophers!
  - Bon appétit, and may the philosophers avoid the perils of starvation!
 
