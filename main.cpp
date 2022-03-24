#include "Sensors.h"
typedef enum
{
  READ_SERIAL,
  BLINK_LED,
  READ_SENSORS,
  NUM_STATES
} StateType;

StateType state = READ_SERIAL;

SENSORS sensor;
int led = 13;

void setup()
{
  pinMode(led, OUTPUT);
  Serial.begin(9600);
  sensor.DHT_init();
  sensor.BH1750_init();
  delay(100); // give some time to send data over Serial before going to sleep
}
void loop()
{

  switch (state)
  {
  case READ_SERIAL:
    //Run state machine code
    //za sada mozete ostaviti prazno

    //Move to the next state
    state = READ_SENSORS;
    break;
  case BLINK_LED:
    //Run state machine code
    digitalWrite(led, HIGH);
    delay(1000);
    digitalWrite(led, LOW);
    delay(1000);
    digitalWrite(led, HIGH);
    delay(1000);
    digitalWrite(led, LOW);

    //Move to the next state
    state = READ_SENSORS;
    break;
  case READ_SENSORS:
    //Run state machine code

    sensor.readTempHum();
    uint32_t lux = sensor.readLight();

    if (lux >= 200)
    {
      state = BLINK_LED;
      break;
    }
    else
    {
      delay(1000);
      state = READ_SERIAL;
    }

    //Move to the next state
    state = READ_SERIAL;
    break;
  }
}