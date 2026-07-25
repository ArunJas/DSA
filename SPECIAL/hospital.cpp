/*
    HOSPITAL MANAGEMENT SYSTEM
    ---------------------------
    A console-based C++ project demonstrating:
      - Classes & Objects, Inheritance, Polymorphism
      - File handling (data persists between runs in .txt files)
      - STL (vector, algorithm)
      - Menu-driven modular design

    Modules:
      1. Patient Management   (add / view / search / discharge)
      2. Doctor Management    (add / view / search)
      3. Appointment Booking  (book / view / cancel)
      4. Billing              (generate bill for a patient)

    Compile:  g++ -std=c++17 hospital_management.cpp -o hospital
    Run:      ./hospital
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <limits>

using namespace std;

// ------------------------- Utility helpers -------------------------

void pause() {
    cout << "\nPress Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

int readInt(const string& prompt) {
    int val;
    while (true) {
        cout << prompt;
        if (cin >> val) return val;
        if (cin.eof()) { cout << "\nInput closed. Exiting.\n"; exit(0); }
        cout << "Invalid input. Please enter a number.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

double readDouble(const string& prompt) {
    double val;
    while (true) {
        cout << prompt;
        if (cin >> val) return val;
        if (cin.eof()) { cout << "\nInput closed. Exiting.\n"; exit(0); }
        cout << "Invalid input. Please enter a number.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

string readLine(const string& prompt) {
    string val;
    cout << prompt;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, val);
    return val;
}

// ------------------------- Base class: Person -------------------------

class Person {
protected:
    int id;
    string name;
    int age;
    string gender;
    string phone;

public:
    Person() : id(0), age(0) {}
    Person(int id, string name, int age, string gender, string phone)
        : id(id), name(move(name)), age(age), gender(move(gender)), phone(move(phone)) {}

    virtual ~Person() = default;

    int getId() const { return id; }
    string getName() const { return name; }

    virtual void display() const {
        cout << left << setw(6) << id << setw(20) << name << setw(6) << age
             << setw(10) << gender << setw(15) << phone;
    }

    virtual string serialize() const {
        stringstream ss;
        ss << id << "|" << name << "|" << age << "|" << gender << "|" << phone;
        return ss.str();
    }
};

// ------------------------- Patient -------------------------

class Patient : public Person {
    string disease;
    double billAmount;
    bool admitted;

public:
    Patient() : billAmount(0), admitted(true) {}
    Patient(int id, string name, int age, string gender, string phone,
            string disease, double billAmount = 0, bool admitted = true)
        : Person(id, move(name), age, move(gender), move(phone)),
          disease(move(disease)), billAmount(billAmount), admitted(admitted) {}

    string getDisease() const { return disease; }
    double getBill() const { return billAmount; }
    bool isAdmitted() const { return admitted; }
    void setAdmitted(bool v) { admitted = v; }
    void addCharge(double amt) { billAmount += amt; }

    void display() const override {
        Person::display();
        cout << setw(18) << disease << setw(10) << fixed << setprecision(2) << billAmount
             << setw(10) << (admitted ? "Admitted" : "Discharged") << "\n";
    }

    string serialize() const override {
        stringstream ss;
        ss << Person::serialize() << "|" << disease << "|" << billAmount << "|" << admitted;
        return ss.str();
    }

    static Patient deserialize(const string& line) {
        stringstream ss(line);
        string idS, name, ageS, gender, phone, disease, billS, admS;
        getline(ss, idS, '|'); getline(ss, name, '|'); getline(ss, ageS, '|');
        getline(ss, gender, '|'); getline(ss, phone, '|'); getline(ss, disease, '|');
        getline(ss, billS, '|'); getline(ss, admS, '|');
        return Patient(stoi(idS), name, stoi(ageS), gender, phone, disease,
                        stod(billS), admS == "1");
    }
};

// ------------------------- Doctor -------------------------

class Doctor : public Person {
    string specialization;
    string schedule; // e.g. "Mon-Fri 9AM-2PM"

public:
    Doctor() {}
    Doctor(int id, string name, int age, string gender, string phone,
           string specialization, string schedule)
        : Person(id, move(name), age, move(gender), move(phone)),
          specialization(move(specialization)), schedule(move(schedule)) {}

    string getSpecialization() const { return specialization; }

    void display() const override {
        Person::display();
        cout << setw(18) << specialization << setw(20) << schedule << "\n";
    }

    string serialize() const override {
        stringstream ss;
        ss << Person::serialize() << "|" << specialization << "|" << schedule;
        return ss.str();
    }

    static Doctor deserialize(const string& line) {
        stringstream ss(line);
        string idS, name, ageS, gender, phone, spec, sched;
        getline(ss, idS, '|'); getline(ss, name, '|'); getline(ss, ageS, '|');
        getline(ss, gender, '|'); getline(ss, phone, '|'); getline(ss, spec, '|');
        getline(ss, sched, '|');
        return Doctor(stoi(idS), name, stoi(ageS), gender, phone, spec, sched);
    }
};

// ------------------------- Appointment -------------------------

struct Appointment {
    int apptId;
    int patientId;
    int doctorId;
    string date;
    string time;
    string status; // Booked / Cancelled / Completed

    string serialize() const {
        stringstream ss;
        ss << apptId << "|" << patientId << "|" << doctorId << "|" << date << "|" << time << "|" << status;
        return ss.str();
    }

    static Appointment deserialize(const string& line) {
        stringstream ss(line);
        string a, p, d, dt, tm, st;
        getline(ss, a, '|'); getline(ss, p, '|'); getline(ss, d, '|');
        getline(ss, dt, '|'); getline(ss, tm, '|'); getline(ss, st, '|');
        return Appointment{stoi(a), stoi(p), stoi(d), dt, tm, st};
    }
};

// ------------------------- Hospital System (manages everything) -------------------------

class HospitalSystem {
    vector<Patient> patients;
    vector<Doctor> doctors;
    vector<Appointment> appointments;

    const string patientFile = "patients.txt";
    const string doctorFile = "doctors.txt";
    const string apptFile = "appointments.txt";

    int nextPatientId, nextDoctorId, nextApptId;

public:
    HospitalSystem() {
        loadAll();
        nextPatientId = patients.empty() ? 1 : (*max_element(patients.begin(), patients.end(),
                            [](auto&a, auto&b){return a.getId()<b.getId();})).getId() + 1;
        nextDoctorId = doctors.empty() ? 1 : (*max_element(doctors.begin(), doctors.end(),
                            [](auto&a, auto&b){return a.getId()<b.getId();})).getId() + 1;
        nextApptId = appointments.empty() ? 1 : (*max_element(appointments.begin(), appointments.end(),
                            [](auto&a, auto&b){return a.apptId<b.apptId;})).apptId + 1;
    }

    ~HospitalSystem() { saveAll(); }

    // ---------- Persistence ----------
    void loadAll() {
        ifstream pf(patientFile);
        string line;
        while (getline(pf, line)) if (!line.empty()) patients.push_back(Patient::deserialize(line));

        ifstream df(doctorFile);
        while (getline(df, line)) if (!line.empty()) doctors.push_back(Doctor::deserialize(line));

        ifstream af(apptFile);
        while (getline(af, line)) if (!line.empty()) appointments.push_back(Appointment::deserialize(line));
    }

    void saveAll() {
        ofstream pf(patientFile);
        for (auto& p : patients) pf << p.serialize() << "\n";

        ofstream df(doctorFile);
        for (auto& d : doctors) df << d.serialize() << "\n";

        ofstream af(apptFile);
        for (auto& a : appointments) af << a.serialize() << "\n";
    }

    // ---------- Patient module ----------
    void addPatient() {
        string name = readLine("Enter patient name: ");
        int age = readInt("Enter age: ");
        string gender = readLine("Enter gender: ");
        string phone = readLine("Enter phone: ");
        string disease = readLine("Enter disease/reason for admission: ");

        Patient p(nextPatientId++, name, age, gender, phone, disease);
        patients.push_back(p);
        saveAll();
        cout << "\nPatient added successfully. Patient ID: " << p.getId() << "\n";
    }

    void viewPatients() {
        if (patients.empty()) { cout << "\nNo patients found.\n"; return; }
        cout << "\n" << left << setw(6) << "ID" << setw(20) << "Name" << setw(6) << "Age"
             << setw(10) << "Gender" << setw(15) << "Phone" << setw(18) << "Disease"
             << setw(10) << "Bill" << setw(10) << "Status" << "\n";
        cout << string(95, '-') << "\n";
        for (auto& p : patients) p.display();
    }

    Patient* findPatient(int id) {
        for (auto& p : patients) if (p.getId() == id) return &p;
        return nullptr;
    }

    void searchPatient() {
        int id = readInt("Enter Patient ID to search: ");
        Patient* p = findPatient(id);
        if (!p) { cout << "\nPatient not found.\n"; return; }
        cout << "\n";
        p->display();
    }

    void dischargePatient() {
        int id = readInt("Enter Patient ID to discharge: ");
        Patient* p = findPatient(id);
        if (!p) { cout << "\nPatient not found.\n"; return; }
        p->setAdmitted(false);
        saveAll();
        cout << "\nPatient " << p->getName() << " discharged.\n";
    }

    // ---------- Doctor module ----------
    void addDoctor() {
        string name = readLine("Enter doctor name: ");
        int age = readInt("Enter age: ");
        string gender = readLine("Enter gender: ");
        string phone = readLine("Enter phone: ");
        string spec = readLine("Enter specialization: ");
        string sched = readLine("Enter schedule (e.g. Mon-Fri 9AM-2PM): ");

        Doctor d(nextDoctorId++, name, age, gender, phone, spec, sched);
        doctors.push_back(d);
        saveAll();
        cout << "\nDoctor added successfully. Doctor ID: " << d.getId() << "\n";
    }

    void viewDoctors() {
        if (doctors.empty()) { cout << "\nNo doctors found.\n"; return; }
        cout << "\n" << left << setw(6) << "ID" << setw(20) << "Name" << setw(6) << "Age"
             << setw(10) << "Gender" << setw(15) << "Phone" << setw(18) << "Specialization"
             << setw(20) << "Schedule" << "\n";
        cout << string(95, '-') << "\n";
        for (auto& d : doctors) d.display();
    }

    Doctor* findDoctor(int id) {
        for (auto& d : doctors) if (d.getId() == id) return &d;
        return nullptr;
    }

    void searchDoctorBySpecialization() {
        string spec = readLine("Enter specialization to search: ");
        bool found = false;
        cout << "\n";
        for (auto& d : doctors) {
            if (d.getSpecialization() == spec) {
                d.display();
                found = true;
            }
        }
        if (!found) cout << "No doctors found with that specialization.\n";
    }

    // ---------- Appointment module ----------
    void bookAppointment() {
        int pid = readInt("Enter Patient ID: ");
        if (!findPatient(pid)) { cout << "\nInvalid Patient ID.\n"; return; }
        int did = readInt("Enter Doctor ID: ");
        if (!findDoctor(did)) { cout << "\nInvalid Doctor ID.\n"; return; }
        string date = readLine("Enter appointment date (DD-MM-YYYY): ");
        string time = readLine("Enter appointment time (e.g. 10:30AM): ");

        Appointment a{nextApptId++, pid, did, date, time, "Booked"};
        appointments.push_back(a);
        saveAll();
        cout << "\nAppointment booked. Appointment ID: " << a.apptId << "\n";
    }

    void viewAppointments() {
        if (appointments.empty()) { cout << "\nNo appointments found.\n"; return; }
        cout << "\n" << left << setw(8) << "ApptID" << setw(10) << "PatientID" << setw(10) << "DoctorID"
             << setw(14) << "Date" << setw(12) << "Time" << setw(10) << "Status" << "\n";
        cout << string(70, '-') << "\n";
        for (auto& a : appointments) {
            cout << left << setw(8) << a.apptId << setw(10) << a.patientId << setw(10) << a.doctorId
                 << setw(14) << a.date << setw(12) << a.time << setw(10) << a.status << "\n";
        }
    }

    void cancelAppointment() {
        int id = readInt("Enter Appointment ID to cancel: ");
        for (auto& a : appointments) {
            if (a.apptId == id) {
                a.status = "Cancelled";
                saveAll();
                cout << "\nAppointment cancelled.\n";
                return;
            }
        }
        cout << "\nAppointment not found.\n";
    }

    // ---------- Billing module ----------
    void generateBill() {
        int pid = readInt("Enter Patient ID: ");
        Patient* p = findPatient(pid);
        if (!p) { cout << "\nPatient not found.\n"; return; }

        double extra = readDouble("Enter additional charges to add (0 if none): ");
        if (extra > 0) {
            p->addCharge(extra);
            saveAll();
        }

        cout << "\n========= HOSPITAL BILL =========\n";
        cout << "Patient ID   : " << p->getId() << "\n";
        cout << "Name         : " << p->getName() << "\n";
        cout << "Disease      : " << p->getDisease() << "\n";
        cout << fixed << setprecision(2);
        cout << "Total Amount : Rs. " << p->getBill() << "\n";
        cout << "Status       : " << (p->isAdmitted() ? "Admitted" : "Discharged") << "\n";
        cout << "==================================\n";
    }
};

// ------------------------- Menus -------------------------

void patientMenu(HospitalSystem& hs) {
    int choice;
    do {
        cout << "\n----- PATIENT MANAGEMENT -----\n";
        cout << "1. Add Patient\n2. View All Patients\n3. Search Patient by ID\n";
        cout << "4. Discharge Patient\n5. Back to Main Menu\n";
        choice = readInt("Enter choice: ");
        switch (choice) {
            case 1: hs.addPatient(); break;
            case 2: hs.viewPatients(); break;
            case 3: hs.searchPatient(); break;
            case 4: hs.dischargePatient(); break;
            case 5: break;
            default: cout << "Invalid choice.\n";
        }
        if (choice != 5) pause();
    } while (choice != 5);
}

void doctorMenu(HospitalSystem& hs) {
    int choice;
    do {
        cout << "\n----- DOCTOR MANAGEMENT -----\n";
        cout << "1. Add Doctor\n2. View All Doctors\n3. Search by Specialization\n";
        cout << "4. Back to Main Menu\n";
        choice = readInt("Enter choice: ");
        switch (choice) {
            case 1: hs.addDoctor(); break;
            case 2: hs.viewDoctors(); break;
            case 3: hs.searchDoctorBySpecialization(); break;
            case 4: break;
            default: cout << "Invalid choice.\n";
        }
        if (choice != 4) pause();
    } while (choice != 4);
}

void appointmentMenu(HospitalSystem& hs) {
    int choice;
    do {
        cout << "\n----- APPOINTMENT MANAGEMENT -----\n";
        cout << "1. Book Appointment\n2. View All Appointments\n3. Cancel Appointment\n";
        cout << "4. Back to Main Menu\n";
        choice = readInt("Enter choice: ");
        switch (choice) {
            case 1: hs.bookAppointment(); break;
            case 2: hs.viewAppointments(); break;
            case 3: hs.cancelAppointment(); break;
            case 4: break;
            default: cout << "Invalid choice.\n";
        }
        if (choice != 4) pause();
    } while (choice != 4);
}

int main() {
    HospitalSystem hs;
    int choice;

    cout << "=====================================\n";
    cout << "   WELCOME TO HOSPITAL MANAGEMENT SYSTEM\n";
    cout << "=====================================\n";

    do {
        cout << "\n============ MAIN MENU ============\n";
        cout << "1. Patient Management\n";
        cout << "2. Doctor Management\n";
        cout << "3. Appointment Management\n";
        cout << "4. Billing\n";
        cout << "5. Exit\n";
        choice = readInt("Enter choice: ");

        switch (choice) {
            case 1: patientMenu(hs); break;
            case 2: doctorMenu(hs); break;
            case 3: appointmentMenu(hs); break;
            case 4: hs.generateBill(); pause(); break;
            case 5: cout << "\nData saved. Goodbye!\n"; break;
            default: cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 5);

    return 0;
}
