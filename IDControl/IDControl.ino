#include <SPI.h>
#include <RFID.h>
 
#define SS_PIN 10
#define RST_PIN 9
 
RFID rfid(SS_PIN, RST_PIN); 
 
int serNum[5];

// Подключение к контактам rgb-светодиода
const byte rPin = 6;
const byte gPin = 5;
const byte bPin = 3;
 
void setup()
{ 
    Serial.begin(9600);
    SPI.begin(); 
    rfid.init();

    pinMode( rPin, OUTPUT );
    pinMode( gPin, OUTPUT );
    pinMode( bPin, OUTPUT );
}
 
void loop()
{
    // Если обнаружена метка
    if (rfid.isCard()) {
        // Считываем данные
        if (rfid.readCardSerial()) {
          // Проверка данных
          if ((rfid.serNum[0] == 0xE1)&&(rfid.serNum[1] == 0x54)&&(rfid.serNum[2] == 0x5A)&&(rfid.serNum[3] == 0x2D)&&(rfid.serNum[4] == 0xC2))
          {
            Serial.println("Access granted!");
            Serial.println("Card number:");
            Serial.print(rfid.serNum[0],HEX);
            Serial.print(" ");
            Serial.print(rfid.serNum[1],HEX);
            Serial.print(" ");
            Serial.print(rfid.serNum[2],HEX);
            Serial.print(" ");
            Serial.print(rfid.serNum[3],HEX);
            Serial.print(" ");
            Serial.print(rfid.serNum[4],HEX);
            Serial.println(" ");

            digitalWrite( rPin, LOW );
            digitalWrite( bPin, LOW );
            digitalWrite( gPin, HIGH );
          }
          else
          {
            Serial.println("Wrong ID!");
            Serial.println("Card number:");
            Serial.print(rfid.serNum[0],HEX);
            Serial.print(" ");
            Serial.print(rfid.serNum[1],HEX);
            Serial.print(" ");
            Serial.print(rfid.serNum[2],HEX);
            Serial.print(" ");
            Serial.print(rfid.serNum[3],HEX);
            Serial.print(" ");
            Serial.print(rfid.serNum[4],HEX);
            Serial.println(" "); 

            digitalWrite( bPin, LOW );
            digitalWrite( gPin, LOW );
            digitalWrite( rPin, HIGH );
          }

            delay(1000);
            digitalWrite( bPin, LOW );
            digitalWrite( gPin, LOW );
            digitalWrite( rPin, LOW );
        }       
    }
    rfid.halt();
}
