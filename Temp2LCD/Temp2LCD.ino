/*-----( Import needed libraries )-----*/
#include <dht11.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

/*-----( Declare objects )-----*/
// set the LCD address to 0x27 for a 20 chars 4 line display
// Set the pins on the I2C chip used for LCD connections:
//                    addr, en,rw,rs,d4,d5,d6,d7,bl,blpol
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address
dht11 DHT11;
const int sensorPin= 0; //sensor pin connected to analog pin A0
int liquid_level;

/*-----( Declare Constants, Pin Numbers )-----*/
#define DHT11PIN 2

void setup()   /*----( SETUP: RUNS ONCE )----*/
{
  Serial.begin(9600); //(Remove all 'Serial' commands if not needed)
  lcd.begin(20,4);         // initialize the lcd for 20 chars 4 lines, turn on backlight
  lcd.backlight();
  // Print a message to the LCD.
  //lcd.setCursor(0, 1);
  lcd.print("MIGO Strautos");
  pinMode(sensorPin, INPUT);//the liquid level sensor will be an input to the arduino
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);

}/*--(end setup )---*/

void loop()   /*----( LOOP: RUNS CONSTANTLY )----*/
{


  int chk = DHT11.read(DHT11PIN);

  Serial.print("Read sensor: ");
  switch (chk)
  {
    case 0: Serial.println("OK"); break;
    case -1: Serial.println("Checksum error"); break;
    case -2: Serial.println("Time out error"); break;
    default: Serial.println("Unknown error"); break;
  }
  lcd.setCursor(0, 1);

  liquid_level= analogRead(sensorPin); //arduino reads the value from the liquid level sensor
  Serial.println(liquid_level); //prints out liquid level sensor reading
  // lcd.print("WL=");
  // lcd.print(liquid_level); 

  if (liquid_level<=480){ 
    Serial.println("Water level: 0mm - Empty!");
     lcd.print("WL= E");  
     digitalWrite(10, HIGH);
     digitalWrite(9, LOW);
     digitalWrite(8, LOW);   
     digitalWrite(11, HIGH);
  }
  else if (liquid_level>480 && liquid_level<=530){ 
    Serial.println("Water level: 0mm to 5mm"); 
    lcd.print("WL= !!!");
    digitalWrite(10, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1000);              // wait for a second
    digitalWrite(10, LOW);    // turn the LED off by making the voltage LOW
    delay(1000);              // wait for a second
    digitalWrite(11, LOW);
  }
  else if (liquid_level>530 && liquid_level<=615){ 
    Serial.println("Water level: 5mm to 10mm"); 
    lcd.print("WL= :(");
    digitalWrite(10, HIGH);
  }
  else if (liquid_level>615 && liquid_level<=660){ 
    Serial.println("Water level: 10mm to 15mm"); 
    lcd.print("WL= :(");
    digitalWrite(10, HIGH);
  } 
  else if (liquid_level>660 && liquid_level<=680){ 
    Serial.println("Water level: 15mm to 20mm"); 
    lcd.print("WL= :)");
    digitalWrite(10, HIGH);
    digitalWrite(9, HIGH);
  }
  else if (liquid_level>680 && liquid_level<=690){ 
    Serial.println("Water level: 20mm to 25mm"); 
    lcd.print("WL= :)");
    digitalWrite(10, HIGH);
    digitalWrite(9, HIGH);
    digitalWrite(8, HIGH);
  }
  else if (liquid_level>690 && liquid_level<=700){ 
    Serial.println("Water level: 25mm to 30mm"); 
    lcd.print("WL= :)");
    digitalWrite(10, HIGH);
    digitalWrite(9, HIGH);
    digitalWrite(8, HIGH);
  }
  else if (liquid_level>700 && liquid_level<=705){ 
    Serial.println("Water level: 30mm to 35mm"); 
    lcd.print("WL= :)");
    digitalWrite(10, HIGH);
    digitalWrite(9, HIGH);
    digitalWrite(8, HIGH);
  }
  else if (liquid_level>705){ 
    Serial.println("Water level: 35mm to 40mm");
    lcd.print("WL= F"); 
    digitalWrite(10, HIGH);
    digitalWrite(9, HIGH);
    digitalWrite(8, HIGH);
  }

 // lcd.print("C=");
 // lcd.print((float)DHT11.temperature, 0);
  Serial.print("Temperature (oC): ");
  Serial.println((float)DHT11.temperature, 2);

  lcd.print(" F=");
  lcd.print(Fahrenheit(DHT11.temperature), 0);
  Serial.print("Temperature (oF): ");
  Serial.println(Fahrenheit(DHT11.temperature), 2);
  
  lcd.print(" H=");
  lcd.print((float)DHT11.humidity, 0);
  lcd.print("%");
  Serial.print("Humidity (%): ");
  Serial.println((float)DHT11.humidity, 2);  

  Serial.print("Temperature (K): ");
  Serial.println(Kelvin(DHT11.temperature), 2);

  Serial.print("Dew Point (oC): ");
  Serial.println(dewPoint(DHT11.temperature, DHT11.humidity));

  Serial.print("Dew PointFast (oC): ");
  Serial.println(dewPointFast(DHT11.temperature, DHT11.humidity));

  delay(2000);

}/* --(end main loop )-- */

/*-----( Declare User-written Functions )-----*/
//
//Celsius to Fahrenheit conversion
double Fahrenheit(double celsius)
{
        return 1.8 * celsius + 32;
}

//Celsius to Kelvin conversion
double Kelvin(double celsius)
{
        return celsius + 273.15;
}

// dewPoint function NOAA 
double dewPoint(double celsius, double humidity)
{
        double A0= 373.15/(273.15 + celsius);
        double SUM = -7.90298 * (A0-1);
        SUM += 5.02808 * log10(A0);
        SUM += -1.3816e-7 * (pow(10, (11.344*(1-1/A0)))-1) ;
        SUM += 8.1328e-3 * (pow(10,(-3.49149*(A0-1)))-1) ;
        SUM += log10(1013.246);
        double VP = pow(10, SUM-3) * humidity;
        double T = log(VP/0.61078);   // temp var
        return (241.88 * T) / (17.558-T);
}

// delta max = 0.6544 wrt dewPoint()
// 5x faster than dewPoint()
double dewPointFast(double celsius, double humidity)
{
        double a = 17.271;
        double b = 237.7;
        double temp = (a * celsius) / (b + celsius) + log(humidity/100);
        double Td = (b * temp) / (a - temp);
        return Td;

} 

/* ( THE END ) */

