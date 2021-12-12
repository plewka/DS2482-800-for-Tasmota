#include <Stream.h>
#include "owsensors.h"

void owsensors::setup(void)
{
  //DEBUG_P("Checking for I2C devices...:");
  if (oneWire.checkPresence())
  {
    //DEBUG_P("DS2482 present");

    oneWire.deviceReset();
    oneWire.wireResetSearch(); // ohne -> Probleme !!

    for (int8_t channel = 0; channel < 8; channel++)
    {
      oneWire.setChannel(channel);

      //DEBUG_P("\tChecking for 1-Wire devices...");
      if (oneWire.wireReset())
      {
        //DEBUG_P("\tDevices present on 1-Wire bus");

        //uint8_t currAddress[8];

        //DEBUG_P("\t\tSearching 1-Wire bus...");
        auto i = 0;
        while ((oneWire.wireSearch(id_sensors[channel][i])) && (i < 10)) // Limit to 10 per Channel
        {
          //         _PL("\t\t\tFound device: ");
          //printAddress(currAddress);
          printAddress(id_sensors[channel][i]);
          i++;
          //DEBUG_P();
        }
        num_sensors[channel] = i;
        oneWire.wireResetSearch(); // wichtig

      }
      else;
        //DEBUG_P("No devices on 1-Wire bus");
    }
  }
  else;
    //DEBUG_P("No DS2482 present");
  return;
}

void owsensors::update (uint8_t channel)
{
  if (channel >= 8) channel = 0;
  oneWire.setChannel(channel);
  sensors.requestTemperatures();
  for (auto j = 0; j < num_sensors[channel]; j++)
  {
    //   printData(id_sensors[channel][j]);
    temp_sensors[channel][j] = printTemperature(id_sensors[channel][j]);
  }
  //DEBUG_P();
}
void owsensors::loop()
{
  update(current_channel);
  current_channel++; if (current_channel >= 8) current_channel = 0;
}

void owsensors::printAddress(uint8_t deviceAddress[8])
{
  //DEBUG_P("{ ");
  for (uint8_t i = 0; i < 8; i++)
  {
    // zero pad the address if necessary
    //DEBUG_B("0x");
    //if (deviceAddress[i] < 16) //DEBUG_B("0");
    //DEBUG_F("%X", deviceAddress[i]);
    //if (i < 7) //DEBUG_B(", ");

  }
  //DEBUG_P(" }");
}

void owsensors::printData(DeviceAddress deviceAddress)
{
  //_PP("Device Address: ");
  printAddress(deviceAddress);
  //_PP(" ");
  printTemperature(deviceAddress);
  // _PL();
}

uint32_t owsensors::printTemperature(DeviceAddress deviceAddress)
{
  int32_t tempC = sensors.getTempC(deviceAddress) * 1000;
  if (tempC == DEVICE_DISCONNECTED_C)
  {
    //_PL("Error: Could not read temperature data");
    return (0);
  }
  //  _PP("Temp m°C: ");
  //  _PL(tempC);
  return (tempC);
}
