#include <iostream>
#include <thread>
#include <vector>
#include <chrono>

using namespace std;

const int THINKING = 0;
const int HUNGRY = 1;
const int EATING = 2;

class DiningPhilosophers {
private:
    int numPhilosophers;
    vector<thread> philosophers;
    vector<int> state;  // Status: 0 = THINKING, 1 = HUNGRY, 2 = EATING
    vector<bool> forks; // true = wolne, false = zajęte

public:
    // Constructor - initializes philosophers' states and forks
    DiningPhilosophers(int n) : numPhilosophers(n), state(n, THINKING), forks(n, true) {}

    // Function executed by each philosopher thread
    void philosopher(int id) {
        for (int i = 0; i < 5; ++i) { // Each philosopher eats 5 times
            think(id);
            pickupForks(id);
            eat(id);
            putdownForks(id);
        }
    }

    // Simulates the thinking process
    void think(int id) {
        printState(id, "Thinking");
        this_thread::sleep_for(chrono::milliseconds(1000)); // Thinking for 1 second
    }

    // Philosopher tries to pick up forks
    void pickupForks(int id) {
        int left = id;
        int right = (id + 1) % numPhilosophers;

        state[id] = HUNGRY;
        printState(id, "Hungry");

        // Wait until both forks are available
        while (true) {
            if (forks[left] && forks[right]) {
                forks[left] = false;
                forks[right] = false;
                state[id] = EATING;
                break;
            }
            this_thread::sleep_for(chrono::milliseconds(100)); // Prevent excessive CPU usage
        }

        printState(id, "Eating");
    }

    // Simulates eating
    void eat(int id) {
        this_thread::sleep_for(chrono::milliseconds(2000)); // Eating for 2 seconds
    }

    // Philosopher puts down forks
    void putdownForks(int id) {
        int left = id;
        int right = (id + 1) % numPhilosophers;

        forks[left] = true;
        forks[right] = true;
        state[id] = THINKING;

        printState(id, "Thinking");
    }

    // Prints the philosopher's state
    void printState(int id, const string &state) {
        cout << "Philosopher " << id << " is " << state << endl;
    }

    // Starts the simulation
    void start() {
        for (int i = 0; i < numPhilosophers; ++i) {
            philosophers.emplace_back(&DiningPhilosophers::philosopher, this, i);
        }

        for (auto &p : philosophers) {
            p.join(); // Wait for all philosopher threads to finish
        }
    }
};

int main() {
    int numPhilosophers;

    // User input
    cout << "=== Dining Philosophers Problem ===" << endl;
    cout << "Enter the number of philosophers: ";
    cin >> numPhilosophers;

    // Validate input
    if (numPhilosophers < 2) {
        cout << "Number of philosophers must be at least 2!" << endl;
        return 1;
    }

    // Run simulation
    DiningPhilosophers dp(numPhilosophers);
    dp.start();

    cout << "Simulation finished." << endl;
    return 0;
}
