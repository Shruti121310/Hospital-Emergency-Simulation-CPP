#include <bits/stdc++.h>
#include <fstream>

using namespace std;

class Patient {
public:
    int id, severity, health;
    int treatmentLeft;

    Patient(int id, int sev) : id(id), severity(sev), health(100) {
        if (severity == 3) treatmentLeft = 10;
        else if (severity == 2) treatmentLeft = 9;
        else treatmentLeft = 8;
    }

    void decayQueue() {
        if (severity == 3) health -= 20;
        else if (severity == 2) health -= 10;
        else health -= 5;
        if (health < 0) health = 0;
    }

    void treat() {
        treatmentLeft--;
    }

    bool cured() const {
        return treatmentLeft <= 0;
    }

    bool alive() const {
        return health > 0;
    }

    string sevStr() const {
        if (severity == 3) return "Critical";
        if (severity == 2) return "Serious";
        return "Normal";
    }
};

class Doctor {
public:
    int fatigue;
    int activeTurns;

    Doctor(int turns = -1) : fatigue(0), activeTurns(turns) {}

    bool available() const {
        return fatigue < 100;
    }

    void work() {
        fatigue += 15;
    }

    bool updateTurn() {
        if (activeTurns == -1) return true;
        activeTurns--;
        return activeTurns > 0;
    }
};

class Hospital {
public:
    int beds = 6, icuBeds = 2;
    int usedBeds = 0, usedICU = 0;
    int reputation = 60;
    int fund = 50000;

    vector<Doctor> doctors;
    vector<Patient*> admitted;
    queue<Patient*> waiting;

    Hospital() {
        for (int i = 0; i < 4; i++)
            doctors.emplace_back();
    }

    int activeDoctors() {
        int c = 0;
        for (auto &d : doctors)
            if (d.available()) c++;
        return c;
    }
};

void showDashboard(Hospital &h, int turn) {
    cout << "\n================ HOSPITAL STATUS =================\n";
    cout << "Turn: " << turn << "\n";

    cout << "\n--- Resources ---\n";
    cout << "Beds: " << h.usedBeds << "/" << h.beds
         << " | ICU: " << h.usedICU << "/" << h.icuBeds << "\n";
    cout << "Doctors Available: " << h.activeDoctors() << "\n";
    cout << "Fund: ৳" << h.fund << "\n";

    cout << "\n--- Reputation ---\n";
    cout << "Hospital Rating: " << h.reputation << " / 100\n";

    cout << "\n--- Admitted Patients ---\n";
    if (h.admitted.empty()) cout << "None\n";
    for (auto *p : h.admitted)
        cout << "P" << p->id << " | " << p->sevStr()
             << " | Recovery in: " << p->treatmentLeft << " turns\n";

    cout << "\n--- Waiting Queue ---\n";
    if (h.waiting.empty()) cout << "Empty\n";
    queue<Patient*> temp = h.waiting;
    while (!temp.empty()) {
        auto *p = temp.front(); temp.pop();
        cout << "P" << p->id << " | " << p->sevStr()
             << " | Health: " << p->health << "%\n";
    }
    cout << "==================================================\n";
}

class Simulation {
    Hospital hospital;
    int turn = 1, pid = 1;
    const int MAX_TURNS = 15;

public:
    void run() {
        srand(time(0));
        cout << "=== Hospital Emergency Management Simulation ===\n";

        while (turn <= MAX_TURNS && hospital.reputation > 0 && hospital.fund > 0) {
            showDashboard(hospital, turn);

            Patient* incoming = new Patient(pid++, rand() % 3 + 1);
            cout << "\nIncoming Patient: P" << incoming->id
                 << " (" << incoming->sevStr() << ")\n";

            bool turnDone = false;
            while (!turnDone) {
                cout << "\nChoose Action:\n";
                cout << "1. Admit Patient\n";
                cout << "2. Put in Waiting Queue\n";
                cout << "3. Refer Patient\n";
                cout << "4. Use Fund\n";
                cout << "Choice: ";

                int ch; cin >> ch;
                if (ch == 1) turnDone = admit(incoming);
                else if (ch == 2) turnDone = queuePatient(incoming);
                else if (ch == 3) turnDone = refer(incoming);
                else if (ch == 4) fundMenu();
                else cout << "Invalid choice!\n";
            }

            updateSystem();
            autoAdmitFromQueue();
            checkTermination();
            turn++;
        }
        showResult();
        saveToFile();
    }

private:
    bool admit(Patient* p) {
        if (hospital.activeDoctors() == 0) {
            cout << "⚠ No doctors available!\n";
            return false;
        }
        if (p->severity == 3 && hospital.usedICU >= hospital.icuBeds) {
            cout << "⚠ ICU full!\n";
            return false;
        }
        if (hospital.usedBeds >= hospital.beds) {
            cout << "⚠ Beds full!\n";
            return false;
        }

        hospital.usedBeds++;
        if (p->severity == 3) hospital.usedICU++;
        hospital.admitted.push_back(p);

        for (auto &d : hospital.doctors)
            if (d.available()) { d.work(); break; }

        hospital.reputation += (p->severity == 3 ? 5 : 3);
        hospital.fund += (p->severity == 3 ? 5000 : 3000);
        return true;
    }

    bool queuePatient(Patient* p) {
        if (hospital.waiting.size() >= 3) {
            cout << "⚠ Queue full!\n";
            return false;
        }
        hospital.waiting.push(p);
        return true;
    }

    bool refer(Patient* p) {
        if (rand() % 100 < 70) {
            cout << "Referral successful.\n";
            hospital.reputation -= 5;
            hospital.fund += 1000;
        } else {
            cout << "Referral failed. Patient died.\n";
            hospital.reputation -= 15;
        }
        return true;
    }

    void fundMenu() {
        cout << "\n1. Hire Temp Doctor (৳15000)\n";
        cout << "2. Build ICU Bed (৳25000)\n";
        cout << "3. Build Normal Bed (৳15000)\n";
        cout << "Choice: ";

        int c; cin >> c;
        if (c == 1 && hospital.fund >= 15000) {
            hospital.fund -= 15000;
            hospital.doctors.emplace_back(5);
        } else if (c == 2 && hospital.fund >= 25000) {
            hospital.fund -= 25000;
            hospital.icuBeds++;
        } else if (c == 3 && hospital.fund >= 15000) {
            hospital.fund -= 15000;
            hospital.beds++;
        } else cout << "Insufficient fund.\n";
    }

    void updateSystem() {
        for (auto it = hospital.admitted.begin(); it != hospital.admitted.end();) {
            (*it)->treat();
            if ((*it)->cured()) {
                cout << "✅ Patient P" << (*it)->id << " cured & released.\n";
                hospital.usedBeds--;
                if ((*it)->severity == 3) hospital.usedICU--;
                it = hospital.admitted.erase(it);
            } else it++;
        }

        int sz = hospital.waiting.size();
        queue<Patient*> tmp;
        while (sz--) {
            Patient* p = hospital.waiting.front();
            hospital.waiting.pop();
            p->decayQueue();
            if (!p->alive()) {
                cout << "❌ Patient P" << p->id << " died in queue.\n";
                hospital.reputation -= 10;
            } else tmp.push(p);
        }
        hospital.waiting = tmp;

        for (auto it = hospital.doctors.begin(); it != hospital.doctors.end();) {
            if (!it->updateTurn()) it = hospital.doctors.erase(it);
            else it++;
        }

        if (hospital.reputation > 70)
            hospital.fund += 2000;
    }

    void autoAdmitFromQueue() {
        if (!hospital.waiting.empty()) {
            Patient* p = hospital.waiting.front();
            if (hospital.activeDoctors() > 0 &&
                hospital.usedBeds < hospital.beds &&
                !(p->severity == 3 && hospital.usedICU >= hospital.icuBeds)) {
                hospital.waiting.pop();
                admit(p);
            }
        }
    }

    void checkTermination() {
        if (hospital.reputation <= 0 || hospital.fund <= 0) {
            if (hospital.fund <= 0) hospital.fund = 0;
            if (hospital.reputation <= 0) hospital.reputation = 0;
        }
    }

    void showResult() {
        cout << "\n=========== SIMULATION ENDED ===========\n";
        cout << "Final Reputation: " << hospital.reputation << "\n";
        cout << "Final Fund: ৳" << hospital.fund << "\n";

        if (hospital.fund <= 0) {
            cout << "❌ Hospital Bankruptcy! Fund Empty. Hospital Closed.\n";
        } else if (hospital.reputation <= 0) {
            cout << "❌ Hospital Shut Down! Reputation hit Zero.\n";
        } else if (hospital.reputation >= 75) {
            cout << "⭐ Excellent Hospital\n";
        } else if (hospital.reputation >= 50) {
            cout << "✔ Stable Hospital\n";
        } else {
            cout << "⚠ Struggling Hospital\n";
        }
    }

    void saveToFile() {
        ofstream outFile("hospital_log.txt", ios::app);
        if (outFile.is_open()) {
            outFile << "--- Simulation Record ---\n";
            outFile << "Final Turn: " << turn - 1 << "\n";
            outFile << "Final Fund: " << hospital.fund << "\n";
            outFile << "Final Reputation: " << hospital.reputation << "\n";

            string status;
            if (hospital.fund <= 0) status = "Bankrupt/Closed";
            else if (hospital.reputation <= 0) status = "Shut Down/No Reputation";
            else status = (hospital.reputation >= 50 ? "Stable/Excellent" : "Struggling");

            outFile << "Status: " << status << "\n";
            outFile << "--------------------------\n\n";
            outFile.close();
            cout << "\n[System] Simulation results saved to 'hospital_log.txt'.\n";
        } else {
            cout << "\n[Error] Could not save to file.\n";
        }
    }
};

int main() {
    Simulation sim;
    sim.run();
    return 0;
}
