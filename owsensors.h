#include <Wire.h>
#include "OneWire.h"
#include "DallasTemperature.h"
#include "heizregler.h"
#include <array>

#ifndef owsensors_h
#define owsensors_h

class owsensors
{
  public:
    owsensors (OneWire& ow): oneWire(ow)
      //    owsensors (OneWire& ow, DallasTemperature& sen, Stream& s): sensors(sen), oneWire(ow), dbgserial(s)
    {
      current_channel = 0;
      sensors.setOneWire(&oneWire);
      sensors.begin();
    };

    int32_t get_temp (uint8_t channel, uint8_t index) {
      return (temp_sensors[channel][index]);
    }
    //int32_t get_id   (uint8_t channel, uint8_t index);
    uint8_t number (uint8_t channel) {
      return (num_sensors[channel]);
    }

    void setup(void);
    void loop(void);

    //int32_t& get_refsensors(void);

  protected:

  private:

    uint8_t current_channel;
    DallasTemperature sensors;
    OneWire& oneWire;    
    
    int32_t temp_sensors[8][10];     // temperature of sensor
    uint8_t num_sensors [8];          // number of sensors in channel


//    Stream& dbgserial;
    DeviceAddress id_sensors[8][10];  // id of sensor

    void update (uint8_t channel);
    void printAddress(uint8_t deviceAddress[8]);
    uint32_t printTemperature(DeviceAddress deviceAddress);
    void printData(DeviceAddress deviceAddress);
};

/*
    int32_t& owsensors::get_refsensors(void)
    {
      return temp_sensors;
    }
    */

#endif // owsensors_h
