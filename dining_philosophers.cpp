#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include <mutex>
#include <condition_variable>

using namespace std;

const int THINKING = 0;
const int HUNGRY = 1;
const int EATING = 2;

class DiningPhilosophers {
private:
    int numPhilosophers;
    vector<thread> philosophers;
    vector<int> state;
    vector<mutex> forks; // Mutex for each fork
    mutex mtx; // Global mutex for synchronizing philosophers' state
    vector<condition_variable> cv; // Condition variables for philosophers

public:
    DiningPhilosophers(int n) : numPhilosophers(n), state(n, THINKING), forks(n), cv(n) {}

    void philosopher(int id) {
        for (int i = 0; i < 5; ++i) { // Each philosopher eats 5 times
            think(id);
            pickupForks(id);
            eat(id);
            putdownForks(id);
        }
    }

    void think(int id) {
        printState(id, "Thinking");
        this_thread::sleep_for(chrono::milliseconds(1000));
    }

    void pickupForks(int id) {
        unique_lock<mutex> lock(mtx); // Lock access to state modification
        state[id] = HUNGRY;
        printState(id, "Hungry");

        // Wait until the philosopher can pick up both forks
        cv[id].wait(lock, [&] {
            int left = id;
            int right = (id + 1) % numPhilosophers;
            return (state[left] != EATING && state[right] != EATING);
        });

        // The philosopher can start eating
        state[id] = EATING;
        printState(id, "Eating");
    }

    void eat(int id) {
        this_thread::sleep_for(chrono::milliseconds(2000));
    }

    void putdownForks(int id) {
        lock_guard<mutex> lock(mtx); // Secure fork release operation
        state[id] = THINKING;
        printState(id, "Thinking");

        // Notify neighbors that they may attempt to eat
        cv[(id + numPhilosophers - 1) % numPhilosophers].notify_one();
        cv[(id + 1) % numPhilosophers].notify_one();
    }

    void printState(int id, const string &state) {
        cout << "Philosopher " << id << " is " << state << endl;
    }

    void start() {
        for (int i = 0; i < numPhilosophers; ++i) {
            philosophers.emplace_back(&DiningPhilosophers::philosopher, this, i);
        }

        for (auto &p : philosophers) {
            p.join();
        }
    }
};

int main() {
    int numPhilosophers;

    cout << "=== Dining Philosophers Problem ===" << endl;
    cout << "Enter the number of philosophers: ";
    cin >> numPhilosophers;

    if (numPhilosophers < 2) {
        cout << "Number of philosophers must be at least 2!" << endl;
        return 1;
    }

    DiningPhilosophers dp(numPhilosophers);
    dp.start();

    cout << "Simulation finished." << endl;
    return 0;
}
