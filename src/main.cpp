/***********************************************************************
 * Project      :     tenergy32hub_template
 * Description  :     Template coding for tenergy32hub on vscode with platformIO
 * Hardware     :     tenergy32hub
 * Author       :     Tenergy Innovation Co., Ltd.
 * Date         :     27/04/2025
 * Revision     :     1.0
 * Rev1.0       :     Original
 * website      :     http://www.tenergyinnovation.co.th
 * Email        :     uten.boonliam@tenergyinnovation.co.th
 * TEL          :     +66 89-140-7205
 ***********************************************************************/
#include <Arduino.h>
#include <tenergy32hub.h>
#include <esp_task_wdt.h>

/**************************************/
/*          Firmware Version          */
/**************************************/
String version = "0.1";

/**************************************/
/*          Header project            */
/**************************************/
void header_print(void)
{
    Serial.printf("\r\n***********************************************************************\r\n");
    Serial.printf("* Project      :     tenergy32hub_template\r\n");
    Serial.printf("* Description  :     Template coding for tenergy32hub on vscode with platformIO\r\n");
    Serial.printf("* Hardware     :     tenergy32hub\r\n");
    Serial.printf("* Author       :     Tenergy Innovation Co., Ltd.\r\n");
    Serial.printf("* Date         :     04/07/2022\r\n");
    Serial.printf("* Revision     :     %s\r\n", version);
    Serial.printf("* Rev1.0       :     Origital\r\n");
    Serial.printf("* website      :     http://www.tenergyinnovation.co.th\r\n");
    Serial.printf("* Email        :     uten.boonliam@tenergyinnovation.co.th\r\n");
    Serial.printf("* TEL          :     +66 89-140-7205\r\n");
    Serial.printf("***********************************************************************/\r\n");
}

/**************************************/
/*        define object variable      */
/**************************************/
Tenergy32Hub mcu;

/**************************************/
/*            GPIO define             */
/**************************************/

/**************************************/
/*       Constand define value        */
/**************************************/
// 10 seconds WDT
#define WDT_TIMEOUT 10

/**************************************/
/*       eeprom address define        */
/**************************************/

/**************************************/
/*        define global variable      */
/**************************************/

/**************************************/
/*           define function          */
/**************************************/

/***********************************************************************
 * FUNCTION:    setup
 * DESCRIPTION: setup process
 * PARAMETERS:  nothing
 * RETURNED:    nothing
 ***********************************************************************/
void setup()
{
    // Initialize serial communication and print the header
    Serial.begin(115200);
    header_print();
    
    // Initialize and enable the watchdog with a 10-second timeout.
    esp_task_wdt_init(WDT_TIMEOUT, true);  // true resets the CPU on WDT timeout
    esp_task_wdt_add(NULL);                // Add current task to watchdog monitoring

    mcu.begin();
    mcu.displayOLEDInfo();
}

/***********************************************************************
 * FUNCTION:    loop
 * DESCRIPTION: loop process
 * PARAMETERS:  nothing
 * RETURNED:    nothing
 ***********************************************************************/
void loop()
{
    int16_t raw = mcu.readPotentiometer();
    float voltage = raw * (5.0 / 32767.0);
    
    Serial.printf("potentiometer = %d\r\n", raw);
    Serial.printf("Voltage = %.2f V\r\n", voltage);
    
    // Display four lines on the OLED
    mcu.displayOLEDLines(
        ("potentiometer = " + String(raw)).c_str(),
        ("Voltage = " + String(voltage) + " V").c_str(),
        ("AIN0 = " + String(mcu.readADCChannel(0))).c_str(),
        ("AIN3 = " + String(mcu.readADCChannel(3))).c_str()
    );
    
    if(mcu.readSW1())
    {
        Serial.println("SW1 pressed");
        mcu.displayOLEDLines("SW1 pressed", "SW2 not pressed");
        mcu.marioSound();
        mcu.setRedLED(true);
        mcu.setBlueLED(false);
        mcu.setbuildingLED(true);
        mcu.blinkBlueLED(1000);
        mcu.blinkbuildingLED(500);
        mcu.blinkRedLED(300);
    }
    else if(mcu.readSW2())
    {
        Serial.println("SW2 pressed");
        mcu.displayOLEDLines("SW2 pressed", "SW1 not pressed");
        mcu.angryBirdSound();
        mcu.setRedLED(false);
        mcu.setBlueLED(true);
        mcu.setbuildingLED(false);
        mcu.blinkBlueLED(0);
        mcu.blinkbuildingLED(0);
        mcu.blinkRedLED(0);
    }

    if(mcu.readSlideSwitch())
    {
       mcu.setRelay(true);
       Serial.println("Slide switch ON");
    }
    else
    {
       mcu.setRelay(false);
       Serial.println("Slide switch OFF");
    }
   

    esp_task_wdt_reset();
    vTaskDelay(1000);
}

