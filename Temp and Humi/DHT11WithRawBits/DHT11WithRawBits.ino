#include <LiquidCrystal.h>
#include <SimpleDHT.h>


// for DHT11, 
//      VCC: 5V or 3V
//      GND: GND
//      DATA: 2
int pinDHT11 = 2;
SimpleDHT11 dht11;
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  // Print a message to the LCD.
}

void loop() {
  // start working...
  
  // read with raw sample data.
  int tempReading = analogRead(pinDHT11);
  float tempVolts = tempReading * 5.0 / 1024.0;
  float tempC = (tempVolts - 0.5) * 100.0;
  float tempF = tempC * 9.0 / 5.0 + 32.0;
  byte temperature = 0;
  byte humidity = 0;
  byte data[40] = {0};
  if (dht11.read(pinDHT11, &temperature, &humidity, data)) {
    lcd.print("Read DHT11 failed");
    return;
  }
  
  
  ///Serial.print("Sample RAW Bits: ");
  //for (int i = 0; i < 40; i++) {
    //Serial.print((int)data[i]);
    //if (i > 0 && ((i + 1) % 4) == 0) {
      ///Serial.print(' ');
   /// }
  ///}
  ///Serial.println("");
  
  Serial.print("Sample OK: ");
 Serial.print((int)temperature); Serial.print(" *C, ");
  Serial.print((int)humidity); Serial.println(" %");
  lcd.print("Temp         F  ");
  lcd.setCursor(6, 0);
  
  // Display Light on second row
  lcd.print((int)temperature); lcd.print(" *C, ");
  lcd.print((int)humidity); lcd.println(" %");
  lcd.setCursor(0, 1);
  //         ----------------
  
  
  // DHT11 sampling rate is 1HZ.
  delay(1000);
}

