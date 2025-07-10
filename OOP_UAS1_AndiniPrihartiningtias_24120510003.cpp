#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

//Person Class 
class Person {
protected:
    string personId, firstName, lastName, dateOfBirth, nationality;
public:
    Person(string id, string fName, string lName, string dob, string nat)
        : personId(id), firstName(fName), lastName(lName), dateOfBirth(dob), nationality(nat) {}

    string getFullName() const { return firstName + " " + lastName; }
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

//Contract Class
class Contract {
public:
    string contractId, startDate, endDate, clauses, clubId, personId;
    double salary;

    Contract(string cid, string start, string end, double sal, string cl, string pid, string cls)
        : contractId(cid), startDate(start), endDate(end), salary(sal), clauses(cls),
          clubId(cl), personId(pid) {}

    void renew() { cout << "Contract renewed.\n"; }
    void terminate() { cout << "Contract terminated.\n"; }
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

//Sponsor Class
class Sponsor {
public:
    string sponsorId, name, contactPerson, phone, email;
    double contractValue;
    string contractStartDate, contractEndDate;

    Sponsor(string id, string n, string contact, string ph, string mail,
            double value, string start, string end)
        : sponsorId(id), name(n), contactPerson(contact), phone(ph), email(mail),
          contractValue(value), contractStartDate(start), contractEndDate(end) {}
};

//TrainingSession Class
class TrainingSession {
public:
    string sessionId, sessionDate, sessionTime, location, focusArea, teamId;
    map<string, bool> attendance; // playerId -> presence

    TrainingSession(string sid, string date, string time, string loc, string area, string tid)
        : sessionId(sid), sessionDate(date), sessionTime(time),
          location(loc), focusArea(area), teamId(tid) {}
};

//Match Class
class Match {
public:
    string matchId, matchDate, matchTime, competition;
    int homeScore, awayScore;
    string homeTeamId, awayTeamId, stadiumId, seasonId;

    Match(string id, string date, string time, string comp,
          int hScore, int aScore, string home, string away, string sid, string seid)
        : matchId(id), matchDate(date), matchTime(time), competition(comp),
          homeScore(hScore), awayScore(aScore), homeTeamId(home), awayTeamId(away),
          stadiumId(sid), seasonId(seid) {}
};

//Stadium Class
class Stadium {
public:
    string stadiumId, name, address;
    int capacity;

    Stadium(string id, string n, int cap, string addr)
        : stadiumId(id), name(n), capacity(cap), address(addr) {}
};

//Season Class
class Season {
public:
    string seasonId, league;
    int year;
    string startDate, endDate;

    Season(string id, int y, string l, string start, string end)
        : seasonId(id), year(y), league(l), startDate(start), endDate(end) {}
};

//MAIN (Instansiasi FC Cakrawala)
int main() {
    Club fcCakrawala("C01", "FC Cakrawala", "2022-06-01", 1000000.0, "Liga Mahasiswa", "S01");
    Team cakrawalaMuda("T01", "FC Cakrawala Muda", "U-23", "C01");

    Coach headCoach("P01", "Andini", "Priha", "1980-01-01", "Indonesia",
                    "C01", "A", "T01", "Head Coach");
    Coach assistantCoach("P02", "Andi", "Ramadan", "1985-02-01", "Indonesia",
                         "C02", "B", "T01", "Assistant Coach");

    cakrawalaMuda.addCoach(headCoach);
    cakrawalaMuda.addCoach(assistantCoach);

    for (int i = 1; i <= 15; ++i) {
        Player p("P" + to_string(100+i), "Player" + to_string(i), "Justin", "2004-01-01", "Indonesia",
                 i, 100000 + i*1000, "PL" + to_string(i), "T01", "Midfielder", "Active");
        cakrawalaMuda.addPlayer(p);
    }

    cout << "FC Cakrawala Muda has " << cakrawalaMuda.players.size() << " players and "
         << cakrawalaMuda.coaches.size() << " coaches." << endl;
    return 0;
}
