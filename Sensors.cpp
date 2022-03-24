#include "Sensors.h"

DHT dht(DHTPIN, DHTTYPE);
BH1750 lightMeter(0x23);

SENSORS::SENSORS() {}
SENSORS::~SENSORS() {}

void SENSORS::DHT_init()
{
    Serial.println(F("DHTxx test!"));
    dht.begin();
}

void SENSORS::BH1750_init()
{
    lightMeter.begin(BH1750::CONTINUOUS_HIGH_RES_MODE);
    Serial.println(F("BH1750 Test"));
}

void SENSORS::readTempHum()
{
    float temperature, humidity;

    temperature = dht.readTemperature();
    humidity = dht.readHumidity();

    if (isnan(humidity) || isnan(temperature))
    {
        Serial.println("Failed to read from DHT sensor\t");
        return;
    }

    Serial.print(F("Temperature: "));
    Serial.print(temperature);
    Serial.println(F("°C"));

    Serial.print(F("Humidity: "));
    Serial.print(humidity);
    Serial.println(F("%"));
}

uint32_t SENSORS::readLight()
{
    uint32_t lux = lightMeter.readLightLevel();
    Serial.print("Light: ");
    Serial.print(lux);
    Serial.println(" lx");

    return lux;
}
