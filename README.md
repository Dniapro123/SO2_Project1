# SO2_Project1


Autor: Uladzislau Budziankou
Przedmiot: Systemy Operacyjne
Temat:Problem jedzących filozofów
Data:25.03.2025


**Opis projektu:**
Problem jedzących filozofów stanowi model rzeczywistych problemów współdzielenia zasobów w systemach operacyjnych, takich jak:

Deadlock (Zakleszczenie)
Może wystąpić, jeśli wszyscy filozofowie jednocześnie podniosą jeden widelec, ale żaden z nich nie zdobędzie drugiego.
Każdy filozof będzie czekał na sąsiada, który nigdy nie odłoży swojego widelca.

Starvation (Głodzenie)
Może się zdarzyć, jeśli filozof nigdy nie dostanie obu widelców, ponieważ inni częściej przejmują zasoby.

Race Condition (Warunki wyścigu)
Gdy kilku filozofów próbuje podnieść te same widelce w tym samym czasie, może dojść do niespójnego stanu.

**Rodzaje akcji:**
Wyobraźmy sobie okrągły stół, przy którym siedzi N filozofów. Każdy filozof cyklicznie przechodzi przez trzy stany:

Myślenie (Thinking) – Filozof zastanawia się nad problemami filozoficznymi i nie potrzebuje zasobów.

Głód (Hungry) – Filozof chce jeść i próbuje podnieść dwa widelce.

Jedzenie (Eating) – Filozof trzyma dwa widelce i spożywa posiłek.

Przy stole znajduje się dokładnie N widelców (jeden między każdym dwoma filozofami). Aby filozof mógł jeść,
musi jednocześnie zdobyć dwa sąsiadujące widelce – ten po lewej i ten po prawej stronie.
Po skończonym posiłku filozof odkłada widelce, dzięki czemu inni filozofowie mogą je podnieść i zacząć jeść.

**Zasady działania:**
1. Każdy filozof myśli, a następnie próbuje podnieść dwa widelce (po lewej i prawej stronie).
2. Filozof czeka, aż oba widelce będą wolne.
3. Jeśli oba widelce są dostępne, filozof rozpoczyna jedzenie.
4. Po jedzeniu odkłada widelce i wraca do myślenia.
5. Proces powtarza się 5 razy dla każdego filozofa.

**Implementacja**
1. Każdy filozof działa jako osobny wątek (std::thread).

2. Stany filozofów (THINKING, HUNGRY, EATING) są przechowywane w tablicy state[].

3. Dostęp do widelców jest synchronizowany za pomocą std::mutex.

4. Filozofowie czekają na dostęp do widelców przy użyciu std::condition_variable, co pozwala uniknąć aktywnego oczekiwania (busy waiting).


**Struktura klasy DiningPhilosophers**
- `int numPhilosophers` – Liczba filozofów
- `vector<thread> philosophers` – Wątki filozofów
- `vector<int> state` – Stan filozofów (THINKING, HUNGRY, EATING)
- `vector<bool> forks` – Status widelców (true = dostępne, false = zajęte)
- `void think(int id)` – Symuluje myślenie filozofa
- `void pickupForks(int id)` – Filozof próbuje podnieść widelce
- `void eat(int id)` – Symuluje jedzenie
- `void putdownForks(int id)` – Filozof odkłada widelce
- `void printState(int id, const string &state)` – Wypisuje stan filozofa
- `void start()` – Rozpoczyna symulację
- `~DiningPhilosophers()` – Destruktor (opcjonalnie)



**Uwzględnione wymagania projektowe:**

1. Raportowanie stanu w konsoli
1. Brak trwałego zablokowania (deadlock)
2. Podanie liczby filozofów jako argument programu
3. Brak mutex, semaphore, gotowych mechanizmów synchronizacji
4. Kod w języku angielskim
5. Czytelny wydruk w konsoli