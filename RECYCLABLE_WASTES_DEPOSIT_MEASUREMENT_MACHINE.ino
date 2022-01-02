/************************************************************************************************************************************************* 
 Project Name   : RECYCLABLE WASTES DEPOSIT MEASUREMENT MACHINE
 Revision Date  : 30.12.2021
 Author         : TUGBERK INANIR
 // **********************************************************************************************************************************************
 Purpose        : Implementing a deposit measurement machine that detect plastic bottles and metal cans, which  to separate different types of 
                  waste materials from each other.
 // **********************************************************************************************************************************************
 System Input   :
                  1) Baumer CH-8501 Diffuse Reflection Optical Sensor : To detect a waste material
                  2) Inductive Sensor                                 : To detect a waste material which made from metal
                  3) MZ-80 Optic Sensor 1                             : To measure the size of waste material
                  4) MZ-80 Optic Sensor 2                             : To measure the size of waste material
                  5) MZ-80 Optic Sensor 3                             : To measure the size of waste material
                  6) Push Button 1                                    : To activate 16x2 LCD Screen which prints waste material information which 
                                                                        are waste material type, the size of waste material and deposit refund fee
                                                                        of waste material
                  7) Push Button 2                                    : To activate servo motor which separates plastic bottles and metal cans from
                                                                        each other
 System Output  :                 
                  1) 16x2 LCD Screen                                  : To give information about waste material
                  2) Makeblock Digital Servo Motor                    : TO separate different materials from each other
 // ************************************************************************************************************************************************
 System Work    : The process of detecting two different waste materials, plastic and metal, from each other, will be carried out with inductive 
                  sensor and diffuse reflection optical sensor, the process of separating waste materials will be carried out with servo motor, the 
                  process of determining the size of waste materials will be carried out with MZ-80 optic sensors and the type of waste, the size of 
                  the waste volume and the deposit refund fee will be printed on the LCD screen                 
 // ************************************************************************************************************************************************                 
 */
 
// *************************************************************************************************************************************************
#include <LiquidCrystal_I2C_AvrI2C.h> // LCD library has been created.

LiquidCrystal_I2C_AvrI2C lcd(0x27, 16, 2); // I2C module and LCD initial parameters has been defined.

#include <Servo.h>  // Servo library has been created.

Servo myservo;      // Servo object to control a servo has been created.

// *************************************************************************************************************************************************

// DEFINITIONS
int pos = 0;          // Variable to store the servo position has been defined.
int optic = 0;        // Reflective sensor has been defined.
int inductive = 0;    // Inductive sensor has been defined.
int mz1 = 0;          // Mz 1 optic sensor has been defined.
int mz2 = 0;          // Mz 2 optic sensor has been defined.
int mz3 = 0;          // Mz 3 optic sensor has been defined.
int start = 0;        // Start button has been defined.
int confirmation = 0; // Confirmation button has been defined.
String size_;         // Variable for item size has been defined.
String type;          // Variable for item type has been defined.
int cost;             // Variable for item cost has been defined.

// *************************************************************************************************************************************************

// SETUP CODE AREA 
void setup() 
{
  myservo.attach(9);             // Servo motor is connected to Digital 9 pin.
  lcd.begin();                   // LCD has been activated.
  lcd.backlight();               // LCD is ON.
  lcd.setCursor(0, 0);
  lcd.print(" DEPOSIT MATIC  "); // First line has been printed.
  lcd.setCursor(0, 1);
  lcd.print(" TUGBERK INANIR "); // Second line has been printed.
  delay(3000);                   // Waited 3 seconds.
  pinMode(3, INPUT);             // Diffuse Reflection Optical Sensor is connected to Digital 3 pin.
  pinMode(4, INPUT);             // Inductive Sensor is connected to Digital 4 pin.
  pinMode(5, INPUT);             // MZ-80 1.sensor is connected to Digital 5 pin.
  pinMode(6, INPUT);             // MZ-80 2. sensor is connected to Digital 6 pin.
  pinMode(7, INPUT);             // MZ-80 3. sensor is connected to Digital 7 pin.
  pinMode(10, INPUT);            // Start button is connected to Digital 10 pin.
  pinMode(11, INPUT);            // Confirmation button is connected to Digital 11 pin.
   

}

void loop() 
{
  
  lcd.begin();                    // LCD has been activated.
  lcd.backlight();                // LCD is ON.
  lcd.setCursor(0, 0);
  lcd.print("   PLEASE PUT   ");  // First line has been printed.
  lcd.setCursor(0, 1);
  lcd.print("   THE WASTE    ");  // Second line has been printed.
  delay(100);                     // Waited 0.1 seconds.
  lcd.begin();                    // LCD has been activated.
  lcd.backlight();                // LCD is ON.
  lcd.setCursor(0, 0);
  lcd.print("  PRESS START   ");  // First line has been printed.
  lcd.setCursor(0, 1);
  lcd.print("     BUTTON     ");  // Second line has been printed.
  delay(100);                     // Waited 0.1 seconds. 

  optic = digitalRead(3);         // Diffuse Reflection Optical Sensor is connected to Digital 3 pin.
  inductive = digitalRead(4);     // Inductive Sensor is connected to Digital 4 pin.
  mz1 = digitalRead(5);           // MZ-80 1.sensor is connected to Digital 5 pin.
  mz2 = digitalRead(6);           // MZ-80 2. sensor is connected to Digital 6 pin.
  mz3 = digitalRead(7);           // MZ-80 3. sensor is connected to Digital 7 pin.
  start = digitalRead(10);        // Start button is connected to Digital 10 pin.
  confirmation = digitalRead(11); // Confirmation button is connected to Digital 11 pin.
  
  if ((start == HIGH) && (optic == HIGH)) // If the waste exists and start button has been pressed.
  { 
    lcd.begin();                    // LCD has been activated.
    lcd.backlight();                // LCD is ON.
    lcd.setCursor(0, 0);
    lcd.print(" READING WASTE  ");  // First line has been printed.
    lcd.setCursor(0, 1);
    lcd.print("  PLEASE WAIT   ");  // Second line has been printed.
    delay(3000);                    // Waited 3 seconds.
  
   read_();    // Read function has been called.
   dispose();  // Dispose function has been called.
   }
}
void read_()
{  
 if ((optic == HIGH) && (inductive == HIGH) && (mz1 == LOW) && (mz2 == LOW) && (mz3 == LOW)) // Variables for big size plastic bottle has been assigned.  
{     type = String("PET");
      size_ = String("BIG");
      cost = 50;
}
 
 if ((optic == HIGH) && (inductive == HIGH) && (mz1 == HIGH) && (mz2 == LOW) && (mz3 == LOW)) // Variables for medium size plastic bottle has been assigned.
{     type = String("PET");  
      size_ = String("MEDIUM");
      cost = 40;
}
 
 if ((optic == HIGH) && (inductive == HIGH) && (mz1 == HIGH) && (mz2 == HIGH) && (mz3 == LOW)) // Variables for small size plastic bottle has been assigned.
{     type = String("PET");
      size_ = String("SMALL");
      cost = 25;
}
  if ((optic == HIGH) && (inductive == LOW) && (mz1 == LOW) && (mz2 == LOW) && (mz3 == LOW)) // Variables for big size metal can has been assigned. 
{      type = String("METAL");
       size_ = String("BIG");
       cost = 75;
}
 
 if ((optic == HIGH) && (inductive == LOW) && (mz1 == HIGH) && (mz2 == HIGH) && (mz3 == LOW)) // Variables for medium size metal can has been assigned. 
{     type = String("METAL");  
      size_ = String("MEDIUM");
      cost = 50;
}
 
 if ((optic == HIGH) && (inductive == LOW) && (mz1 == HIGH) && (mz2 == HIGH) && (mz3 == HIGH)) // Variables for small size metal can has been assigned. 
 {    type = String("METAL");
      size_ = String("SMALL");
      cost = 35;
 }
  
  // Waste information has been printed to LCD screen.
   
  lcd.begin();                    // LCD has been activated.
  lcd.backlight();                // LCD is ON.
  lcd.setCursor(0, 0);
  lcd.print(type);                // First line has been printed.
  lcd.setCursor(7, 0);
  lcd.print(size_); 
  lcd.setCursor(13, 0);
  lcd.print("SIZE"); 
  lcd.setCursor(0, 1);
  lcd.print("COST =");            // Second line has been printed.
  lcd.setCursor(8, 1);
  lcd.print(cost); 
  lcd.setCursor(11, 1);
  lcd.print("KURUS");
  delay(5000);                    // Waited 5 seconds.
  
 do { 
  lcd.begin();                    // LCD has been activated.
  lcd.backlight();                // LCD is ON.
  lcd.setCursor(0, 0);
  lcd.print("   PRESS THE    ");  // First line has been printed.
  lcd.setCursor(0, 1);
  lcd.print(" CONFIRM BUTTON ");  // Second line has been printed.
  optic = digitalRead(3);         // Diffuse Reflection Optical Sensor is connected to Digital 3 pin.
  confirmation = digitalRead(11); // Confirmation button is connected to Digital 11 pin.
  
 } while((optic == HIGH) && (confirmation == LOW)); // While the waste exists and confirmation button hasn't been pressed.

}
void dispose()
{    
  if ((optic == HIGH) && (inductive == HIGH))       // If the plastic bottle waste exists.
         {
             for (pos = 90; pos <= 150; pos += 1)
                {
                   myservo.write(pos);              // Going to position in variable 'pos' has been told to servo.
                   delay(10);                       // Waited 10ms for the servo to reach the position.
                }

          delay(5000);                              // Waited 5 seconds.

            for (pos = 150; pos >= 90; pos -= 1)
               {
                  myservo.write(pos);              // Going to position in variable 'pos' has been told to servo.
                  delay(10);                       // Waited 10ms for the servo to reach the position.
               }
          delay(1000);                             // Waited 1 second.
         }
         
  if ((optic == HIGH) && (inductive == LOW))       // If the metal can waste exists.
        {
              for (pos = 90; pos >= 15; pos -= 1)
                {
                  myservo.write(pos);              // Going to position in variable 'pos' has been told to servo.
                  delay(10);                       // Waited 10ms for the servo to reach the position.
                }
         delay(5000);                              // Waited 5 seconds.

              for (pos = 15; pos <= 90; pos += 1)
                {
                  myservo.write(pos);              // Going to position in variable 'pos' has been told to servo.
                  delay(10);                       // Waited 10ms for the servo to reach the position.
                }
         delay(1000);                              // Waited 1 second.
       }

  }
