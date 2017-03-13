// theiotlife.com
// Charlie Nguyen

#include <Wire.h>
 
int maxI2cAddresses = 127; //Plus One more
int errorCode = 999;
int i2cAddress = 999;
int numberOfdevicesFound = 0;

void setup()
{
  Serial.begin(9600);
  Wire.begin();

  //Wait for Serial Monitor to connect
  while (!Serial);     
  Serial.println("Starting I2C Scanner...");
}
 
 
void loop()
{

  for(i2cAddress = 1; i2cAddress < maxI2cAddresses; i2cAddress++ )
  {
    Wire.beginTransmission(i2cAddress);

    //Check Error code for address status
    errorCode = Wire.endTransmission(); 

    if (errorCode == 0)
    {
      numberOfdevicesFound++;
      Serial.print("Address ");
      Serial.print(formatHexAddress(i2cAddress));
      Serial.println("  found.");
    }
    else if (errorCode == 4)
    {
      Serial.print("Address ");
      Serial.print(formatHexAddress(i2cAddress));
      Serial.println(" found but an errorCode (4) occurred.");
    }    
  }

  if (numberOfdevicesFound == 0)
    Serial.println("No I2C device detected. Did you plug anything in? Check Connections... ");
  else
    Serial.println("Program ran successfully!");

  Serial.println("Send any key to run program again..");
  while(Serial.available()==0);
  Serial.read();
 }

String formatHexAddress(int i2cAddressToBeConverted){
  String Address = "0x";
  if (i2cAddress <= 15){
    Address += "0";
  }
  Address += String(i2cAddressToBeConverted, HEX);
  return Address;
}
