#include <bits/stdc++.h>
#include <ctype.h>
using namespace std;

class Car {
public:
  string regNo;
  int age;

  Car(string regNo , int age) {
    this->regNo = regNo;
    this->age = age;
  }

};

class ParkSystem {
int MAX_SIZE = 0;
public:
  fstream outputFile;
  //list of avalible slots
  vector<int> availableSlots;

  // map of slot and car 
  map<int, Car> mp1;

  //map of age and list of registration number and slot of driver 
  map<int,vector<pair<string,int>>> mp3;

  bool createParkSytem(int n) {
    MAX_SIZE = n;
    cout << "Created parking of " << n << " slots" << endl;
    string output = "Created parking of " + to_string(n) + " slots\n";
    outputFile.open("output.txt", ios::out);
    writeInFile(output);
    for(int i = 1 ; i <= MAX_SIZE ; i++) {
      availableSlots.push_back(i);
    }
    return true;
  }

  void parkCar(string regNo , int age) {
    if(MAX_SIZE == 0) cout << "Parking Lot not created" << endl;
    if(mp1.size() == MAX_SIZE) {
      writeInFile("Sorry, Parking is full\n");
      return ;
    }

    sort(availableSlots.begin() , availableSlots.end());

    int slot = availableSlots[0];

    Car car(regNo , age);
    mp1.insert({slot, car});

    mp3[age].push_back({regNo,slot});
    auto it = availableSlots.begin();
    availableSlots.erase(it);
    cout << "Car with vehicle registration number \""<< regNo <<"\" has been parked at slot number " << slot << endl;
    string output = "Car with vehicle registration number \"" + regNo + "\" has been parked at slot number " + to_string(slot) + "\n";
    writeInFile(output);
  }

  void leaveSlot(int slot) {
    if(MAX_SIZE == 0) cout << "Parking Lot not created" << endl;
    else if(mp1.size() > 0) {
      if(mp1.find(slot) == mp1.end()) {
        writeInFile("Slot already vacant\n");
        return ;
      }

      auto carToLeave = mp1.at(slot);
      mp1.erase(slot);

      if(mp3.find(carToLeave.age) != mp3.end()) {
        vector<pair<string,int>> listOfCar = mp3[carToLeave.age];
        for(auto it = listOfCar.begin() ; it != listOfCar.end() ; it++) {
          if(it->first == carToLeave.regNo && it->second == carToLeave.age) {
            listOfCar.erase(it);
            break;
          }
        }

        cout << "Slot number "<< slot << " vacated, the car with vehicle registration number \""<< carToLeave.regNo <<"\" left the space, the driver of the car was of age " << carToLeave.age << endl;
        
        string output = "Slot number " + to_string(slot) + " vacated, the car with vehicle registration number \"" + carToLeave.regNo + "\" left the space, the driver of the car was of age " + to_string(carToLeave.age) + "\n";
        writeInFile(output);
      }
    }
    availableSlots.push_back(slot);
  }

  void getSlotNumber(string regNo) {
    for(auto it: mp1) {
      if(it.second.regNo == regNo) {
        writeInFile(to_string(it.first) + "\n");
        return ;
      }
    }

    writeInFile("No car with Reg No. " + regNo + " found\n");
  }

  void getSlotsWithRespectToAge(int age) {
    if(mp3.find(age) == mp3.end()) {
      writeInFile("No car driver of age " + to_string(age) +" found\n");
      return ;
    }
    vector<pair<string,int>> listOfSlot = mp3[age];
    int n = listOfSlot.size();
    for(int i = 0 ; i < n ; i++) {
      if(i == n -  1) writeInFile(to_string(listOfSlot[i].second));
      else writeInFile(to_string(listOfSlot[i].second) + ","); 
    }

    writeInFile("\n");
  }

  void getRegNoWithRespectToAge (int age) {
    if(mp3.find(age) == mp3.end()) {
      writeInFile("No car driver of age " + to_string(age) +" found\n");
      return ;
    }
    vector<pair<string,int>> listOfRegNo = mp3[age];
    int n = listOfRegNo.size();
    for(int i = 0 ; i < n ; i++) {
      if(i == n -  1) writeInFile(listOfRegNo[i].first);
      else writeInFile(listOfRegNo[i].first + ",");
    }

    writeInFile("\n");
  }

  void writeInFile(string s) {
    if(outputFile) {
      outputFile << s;
    }
  }
  
};

vector<string> split(const string &s , char delim) {
  vector<string> result;
  stringstream ss(s);
  string item;

  while(getline(ss , item, delim)) {
    result.push_back(item);
  }

  return result;
}



int main() {
  ParkSystem myParkSystem;
  string myText;
  ifstream MyReadFile("input.txt");
  
  while (getline (MyReadFile, myText)) {
    
    vector<string> words = split(myText , ' ');

    string command = words[0];

    if(command == "Create_parking_lot") {
      if(words.size() != 2) cout << "Create_parking_lot needs slot";
      int slots = stoi(words[1]);
      
      if(isdigit(slots)) {
        cout << "Please enter a digit";
        return 0;
      }

      myParkSystem.createParkSytem(slots);
      
    }

    else if(command == "Park") {
      if(words.size() != 4) {
        cout << "Park needs registration number and age as well" << endl;
        return 0;
      }

      myParkSystem.parkCar(words[1] , stoi(words[3]));
    }

    else if(command == "Leave") {
      if(words.size() != 2) cout << "Please enter slot number as well\n";
      myParkSystem.leaveSlot(stoi(words[1]));
      
    }

    else if(command == "Slot_number_for_car_with_number") {
      if(words.size() != 2) {
        cout << "Please enter car number\n";
        return 0;
      }

      myParkSystem.getSlotNumber(words[1]);
      
    }

    else if(command == "Slot_numbers_for_driver_of_age") {
      if(words.size() != 2) cout << "Please enter a age\n";
      myParkSystem.getSlotsWithRespectToAge(stoi(words[1]));
    }

    else if(command=="Vehicle_registration_number_for_driver_of_age") {
      if(words.size() != 2) cout << "Please enter age\n";
      myParkSystem.getRegNoWithRespectToAge(stoi(words[1]));
    }
    
  }
  MyReadFile.close();
  return 0;
}