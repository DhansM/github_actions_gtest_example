class Vehicle{
public:
string model;
string color;
string name;
int regno;
};

//parent child relation shop
class car:public Vehicle{
 Engine engObj;
public:
void Start() {
  engObj.crankEngine();
}
};

class Engine{
private:
FuelPump fuelpumpObj;
StartupMotor motorObj;
public:
void crankEngine(){} //delegate-interact
};

class StartupMotor{};
class FuelPump{};


