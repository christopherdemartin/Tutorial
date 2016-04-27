//Notes: FOR THE RELAY, 0 = ON, 1 = OFF
class Valve {
    public: 
    int pin;
    bool isOpen;
    int wateringTime;
};

int valves = 4;
Valve valve1;
Valve valve2;
Valve valve3;
Valve valve4;
Valve valveArray[5]; //increase if add more valves
char publishString[64];

void setup()
{
  valve1.pin = D0;
  valve1.isOpen = false; //set the valve to be closed
  valve1.wateringTime = 2000; //set up first valve's watering time
  valve2.pin = D1;
  valve2.isOpen = false;
  valve2.wateringTime = 2000;
  valve3.pin = D2;
  valve3.isOpen = false;
  valve3.wateringTime = 2000;
  valve4.pin = D3;
  valve4.isOpen = false;
  valve4.wateringTime = 2000;
  
  Spark.function("sleep", sleep);
  Spark.function("water", water);
  Spark.function("update", update);
  Spark.function("togglevalve", togglevalve);
  //Spark.variable("getstatus", &valveStatus, INT);
  valveArray[0] = valve1;
  valveArray[1] = valve2;
  valveArray[2] = valve3;
  valveArray[3] = valve4;
  pinMode(valve1.pin, OUTPUT);
  pinMode(valve2.pin, OUTPUT);
  pinMode(valve3.pin, OUTPUT);
  pinMode(valve4.pin, OUTPUT);
  
int index = 0;
        for (index = 0; index < valves; index++ )
        {
            digitalWrite(valveArray[index].pin, 1);
        }
}

void loop() {
}

int water(String paramValue) //paramvalue not used, only here because of needed function structure, does a built in watering sequence
{
int index = 0;
        for (index = 0; index < valves; index++ )
        {
            digitalWrite(valveArray[index].pin, 0);
            delay(valveArray[index].wateringTime);
            digitalWrite(valveArray[index].pin, 1);
        }
    return 1;
}

int sleep(String paramValue)
{
    int sleeptime = paramValue.toInt();
    Spark.sleep(SLEEP_MODE_DEEP, sleeptime);
    return 1;
}

int update(String paramValue)
{
        unsigned long now = millis();
        unsigned nowSec = now/1000UL;
        unsigned sec = nowSec%60;
        unsigned min = (nowSec%3600)/60;
        unsigned hours = (nowSec%86400)/3600;
        sprintf(publishString,"{\"Hours\": %u, \"Minutes\": %u, \"Seconds\": %u}",hours,min,sec);
        Spark.publish("Uptime",publishString);
}

int togglevalve(String paramValue)
{
    int inputvalve = paramValue.toInt();
    if (inputvalve < 10)
    {
    digitalWrite(valveArray[inputvalve-1].pin, 0);
    }
    else
    {
    digitalWrite(valveArray[inputvalve-11].pin, 1);  
    }
    return 1;
}

//int setValve(String paramValue) { //0 calls an emergency shutoff, otherwise 0 is called eventually after watering
//    valveStatus = paramValue.toInt();
//    if (valveStatus == 1) //triggers a watering cycle. This includes powering the opening mechanism, waiting, powering the closing mechanism, and then going to sleep
//    {
//    digitalWrite(D4, 1);
//    delay(5000); //takes up to 5 seconds for the valve to actually open or close
//    digitalWrite(D4, 0);
//    delay(wateringTime);
//    setValve("0"); //calls the function to close the valve
//   Spark.sleep(SLEEP_MODE_DEEP,200);
//    }
//    if (valveStatus == 0)
//   {
//    digitalWrite(D5, 1);
//    delay(5000); //takes up to 5 seconds for the valve to actually open or close
//    digitalWrite(D5, 0);
//    }
//    return 0;
//}