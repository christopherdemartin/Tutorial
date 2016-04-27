#include "Adafruit_DHT/Adafruit_DHT.h"

#define DHTPIN 7     // what pin we're connected to

#define DHTTYPE DHT11		// DHT 11 

SYSTEM_MODE(SEMI_AUTOMATIC);

DHT dht(DHTPIN, DHTTYPE);

void setup() {
    pinMode(4, OUTPUT);
    pinMode(6, OUTPUT);
	Serial.begin(9600); 
	//We will use serial monitor for testing and monitoring 
	dht.begin();
}

void loop() 
{
	float f = dht.getTempFarenheit();
	
//	for (int count = 0; f; count++)
//	{
//	    delay(30);
//		digitalWrite(D4,0);
//		delay(30);
//		digitalWrite(D4,1);
	    
//	}

// Check if any reads failed and exit early (to try again).
	if (isnan(f)) {
	    Serial.println("Read failed, not a number: ");
	    Serial.print(f);
		return;
	}
	else
	{
	Serial.println("The temperature is read as: ");
	Serial.print(f);
	}
	delay(20000);
	
	if (f < 135) //if its too cold
	{
	    digitalWrite(D6, 1); //Open the relay to the heater, relay normally closed
	}
    else
    {
        digitalWrite(D6, 0); //Otherwise shut off the relay to heater
    }
}

