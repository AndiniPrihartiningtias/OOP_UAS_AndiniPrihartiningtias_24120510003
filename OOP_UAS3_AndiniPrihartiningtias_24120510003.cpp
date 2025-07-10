#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

//Person Base Class 
class Person {
protected:
    string personId, firstName, lastName, dateOfBirth, nationality;
public:
    Person(string id, string fName, string lName, string dob, string nat)
        : personId(id), firstName(fName), lastName(lName), dateOfBirth(dob), nationality(nat) {}
    virtual ~Person() = default;
    virtual string getFullName() const { return firstName + " " + lastName; }
};

//Player Class
class Player : public Person {
public:
    int jerseyNumber;
    double marketValue;
    string playerId, teamId, position, status;

    Player(string id, string fName, string lName, string dob, string nat,
           int number, double value, string pid, string tid,
           string pos, string stat)
        : Person(id, fName, lName, dob, nat),
          jerseyNumber(number), marketValue(value),
          playerId(pid), teamId(tid), position(pos), status(stat) {}

    void train() { cout << getFullName() << " is training.\n"; }
    void playMatch() { cout << getFullName() << " is playing a match.\n"; }
};

//Coach Class
class Coach : public Person {
public:
    string coachId, licenseLevel, teamId, role;

    Coach(string id, string fName, string lName, string dob, string nat,
          string cid, string license, string tid, string r)
        : Person(id, fName, lName, dob, nat),
          coachId(cid), licenseLevel(license), teamId(tid), role(r) {}

    void conductTraining() { cout << getFullName() << " is conducting training.\n"; }
    void selectSquad() { cout << getFullName() << " is selecting the squad.\n"; }
};

//Staff Class
class Staff : public Person {
public:
    string staffId, clubId, role, department;

    Staff(string id, string fName, string lName, string dob, string nat,
          string sid, string cid, string r, string dept)
        : Person(id, fName, lName, dob, nat),
          staffId(sid), clubId(cid), role(r), department(dept) {}

    void performDuties() { cout << getFullName() << " performing duties as " << role << "\n"; }
};

//Abstract Factory
class PersonFactory {
public:
    virtual Person* createPerson() = 0;
};

//Concrete Factories
class CoachFactory : public PersonFactory {
    string id, fName, lName, dob, nat, cid, license, tid, role;
public:
    CoachFactory(string id, string fName, string lName, string dob, string nat,
                 string cid, string license, string tid, string role)
        : id(id), fName(fName), lName(lName), dob(dob), nat(nat),
          cid(cid), license(license), tid(tid), role(role) {}

    Person* createPerson() override {
        return new Coach(id, fName, lName, dob, nat, cid, license, tid, role);
    }
};

class PlayerFactory : public PersonFactory {
    string id, fName, lName, dob, nat, pid, tid, pos, status;
    int jersey;
    double value;
public:
    PlayerFactory(string id, string fName, string lName, string dob, string nat,
                  int jersey, double value, string pid, string tid, string pos, string status)
        : id(id), fName(fName), lName(lName), dob(dob), nat(nat), jersey(jersey), value(value),
          pid(pid), tid(tid), pos(pos), status(status) {}

    Person* createPerson() override {
        return new Player(id, fName, lName, dob, nat, jersey, value, pid, tid, pos, status);
    }
};

//Club Class
class Club {
public:
    string clubId, name, foundationDate, league, stadiumId;
    double budget;

    Club(string cid, string n, string fdate, double bgt, string l, string sid)
        : clubId(cid), name(n), foundationDate(fdate), budget(bgt), league(l), stadiumId(sid) {}
};

//Team Class
class Team {
public:
    string teamId, name, division, clubId;
    vector<Player> players;
    vector<Coach> coaches;

    Team(string id, string n, string div, string cid)
        : teamId(id), name(n), division(div), clubId(cid) {}

    void addPlayer(Player p) { players.push_back(p); }
    void addCoach(Coach c) { coaches.push_back(c); }
};

//MAIN
int main() {
    Club fcCakrawala("C01", "FC Cakrawala", "2022-06-01", 1000000.0, "Liga Mahasiswa", "S01");
    Team cakrawalaMuda("T01", "FC Cakrawala Muda", "U-23", "C01");

    // Menambah Head Coach menggunakan Factory
    CoachFactory headCoachFactory("P01", "Andini", "Priha", "1980-01-01", "Indonesia",
                                  "C01", "A", "T01", "Head Coach");
    CoachFactory assistantCoachFactory("P02", "Andi", "Ramadan", "1985-02-01", "Indonesia",
                                       "C02", "B", "T01", "Assistant Coach");

    Coach* headCoach = dynamic_cast<Coach*>(headCoachFactory.createPerson());
    Coach* assistantCoach = dynamic_cast<Coach*>(assistantCoachFactory.createPerson());

    cakrawalaMuda.addCoach(*headCoach);
    cakrawalaMuda.addCoach(*assistantCoach);

    // Menambah 15 pemain menggunakan Factory
    for (int i = 1; i <= 15; ++i) {
        string pid = "PL" + to_string(i);
        string id = "P" + to_string(100 + i);
        string fName = "Player" + to_string(i);
        PlayerFactory pf(id, fName, "Justin", "2004-01-01", "Indonesia",
                         i, 100000 + i * 1000, pid, "T01", "Midfielder", "Active");
        Player* p = dynamic_cast<Player*>(pf.createPerson());
        cakrawalaMuda.addPlayer(*p);
        delete p;
    }

    cout << "FC Cakrawala Muda has " << cakrawalaMuda.players.size() << " players and "
         << cakrawalaMuda.coaches.size() << " coaches." << endl;

    // Clean up
    delete headCoach;
    delete assistantCoach;

    return 0;
}
