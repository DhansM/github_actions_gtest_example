#include <string>
using namespace std;
class H3OHardware{};
class RTOS{};

class TimerService{
private:
RTOS rtosObj;
public:
string getTime(){return "";}
};

class LightController{
private:
H3OHardware hardwareObj;
public:
void on(){}
void off(){}
};

class LightScheduler{
private:
TimerService timerObj;
LightController controllerObj;
public:
void removeSchedule(){}
void wakeup(){}
void turnONschedule(){}
};
