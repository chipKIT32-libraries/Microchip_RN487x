/* iBeacon
 * Based on work by M16946 (2017/01/13) for Microchip. 
 * Modified by Brian Schmalz of Schmalz Haus LLC (brian@schmalzhaus.com) also for Microchip, Dec 2017
 */

/*
    (c) 2016 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/

#include <Arduino.h>
#include <RN487x_BLE.h>
#include <iBeacon.h>

#define debugSerial Serial
#define bleSerial Serial1

#define SERIAL_TIMEOUT  10000

const char* myiBeaconUUID = "AD11CF40063F11E5BE3E0002A5D5C51B" ;  // 16bytes
const uint16_t myMajor = 0x0C ;
const uint16_t myMinor = 0x0D ;
const uint8_t myTxPower = 0xC5 ;

void setup()
{
  while ((!debugSerial) && (millis() < SERIAL_TIMEOUT)) ;

  debugSerial.begin(115200) ;

  // Set the optional debug stream
  rn487xBle.setDiag(debugSerial) ;
  // Initialize the BLE hardware
  rn487xBle.hwInit() ;
  // Open the communication pipe with the BLE module
  bleSerial.begin(rn487xBle.getDefaultBaudRate()) ;
  // Assign the BLE serial port to the BLE library
  rn487xBle.initBleStream(&bleSerial) ;
  // Finalize the init. process
  if (rn487xBle.swInit())
  {
    debugSerial.println("Init. procedure done!") ;
  }
  else
  {
    debugSerial.println("Init. procedure failed!") ;
    while(1) ;
  }

  // >> Configuring the BLE
  // First enter in command/configuration mode
  rn487xBle.enterCommandMode() ;
  rn487xBle.stopAdvertising() ;
  // Set the advertising output power (range: min = 5, max = 0)
  rn487xBle.setAdvPower(3) ;
  // Clear Beacon adv. packet
  rn487xBle.clearImmediateBeacon() ;

  // >> Start and generate iBeacon
  ibeacon.begin(myiBeaconUUID, myMajor, myMinor, myTxPower) ;

  debugSerial.println("Starter Kit as an iBeacon") ;
  debugSerial.println("=========================") ;
  debugSerial.print("iBeacon UUID: ") ; debugSerial.println(myiBeaconUUID) ;
  debugSerial.print("Major: ") ; debugSerial.println(myMajor, DEC) ;
  debugSerial.print("Minor: ") ; debugSerial.println(myMinor, DEC) ;
  debugSerial.print("Measured Tx Power: ") ; debugSerial.println(myTxPower, DEC) ;

}

void loop()
{ 

}
