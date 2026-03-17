# Hospital-Emergency-Simulation-CPP
A logic-driven C++ simulation of a Hospital Emergency Management System focusing on OOP principles, resource allocation, and file handling
# Hospital Emergency Management Simulation 🏥

A robust **C++ console application** that simulates the complex operations of a hospital emergency ward. This project demonstrates the practical application of **Object-Oriented Programming (OOP)** and efficient resource management.

## 🚀 Key Features
- **Patient Management:** Real-time severity-based treatment logic (Critical, Serious, Normal).
- **Resource Tracking:** Dynamic management of Beds, ICU units, and Hospital Funds.
- **Doctor Fatigue System:** Doctors have a fatigue limit; they need rest/turns to remain active.
- **Queue Simulation:** Automated patient queuing and decay logic (health decreases if not treated).
- **Data Persistence:** Automatically saves simulation logs to `hospital_log.txt` using **fstream**.

## 🛠️ Technical Stack
- **Language:** C++11 or higher
- **Concepts:** Encapsulation, Composition, File I/O, STL (Queue, Vector)
- **Tool:** VS Code / Code::Blocks

## 📂 Project Structure
- `Patient` Class: Handles health and treatment turns.
- `Doctor` Class: Manages fatigue and availability.
- `Hospital` Class: Manages resources and admitted patients.
- `Simulation` Class: The core engine that runs the turn-based logic.

## 📝 How to Run
1. Clone the repository: `git clone https://github.com/Shruti121310/Repository-Name.git`
2. Compile: `g++ main.cpp -o hospital_sim`
3. Run: `./hospital_sim`
