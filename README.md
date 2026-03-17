# Hospital Emergency Management Simulation 🏥

A robust **C++ console-based application** that simulates the complex day-to-day operations of a hospital emergency ward. This project demonstrates the practical application of **Object-Oriented Programming (OOP)**, logic building, and efficient resource management.

## 🚀 Key Features

- **Patient Management:** Implemented real-time severity-based treatment logic (Critical, Serious, Normal).
- **Resource Tracking:** Dynamic management of Beds, ICU units, and Hospital Funds.
- **Doctor Fatigue System:** Doctors have a fatigue limit; they require rest/turns to remain active and available.
- **Queue Simulation:** Automated patient queuing system with health decay logic (patient health decreases if left untreated in the queue).
- **Data Persistence:** Automatically saves simulation logs and final reports to `hospital_log.txt` using **C++ File Handling (fstream)**.
- **Interactive Dashboard:** A turn-based UI that shows the current state of resources, admitted patients, and reputation.

## 🛠️ Technical Stack

- **Language:** C++11 or higher
- **Core Concepts:** Encapsulation, Composition, Classes & Objects, File I/O, STL (Queue, Vector).
- **Tools Used:** VS Code / Code::Blocks, Git, GitHub.

## 📂 Project Structure

- `Patient` Class: Handles individual patient ID, health status, and severity levels.
- `Doctor` Class: Manages doctor fatigue levels and work-turn availability.
- `Hospital` Class: Acts as a container for resources (Beds, ICU, Funds) and manages the lists of admitted/waiting patients.
- `Simulation` Class: The core engine that runs the turn-based logic and handles user input.

## 📝 How to Run

1. **Clone the repository:**
   ```bash
   git clone [https://github.com/Shruti121310/Hospital-Emergency-Simulation-CPP.git](https://github.com/Shruti121310/Hospital-Emergency-Simulation-CPP.git)
