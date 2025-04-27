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
Serial.printf("* Revision     :     %s\r\n",version);
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
    Serial.begin(115200);
    header_print();
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
    esp_task_wdt_reset();
    vTaskDelay(100);
}
