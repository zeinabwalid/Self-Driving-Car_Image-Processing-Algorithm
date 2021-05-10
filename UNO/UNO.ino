#include <SoftwareSerial.h>
#include "millisDelay.h" 
SoftwareSerial ArduinoUno(3,2);

int flag =1 ;
String Direction;
millisDelay ledDelay;


uint8_t Pwm1 = 6; //Nodemcu PWM pin 
uint8_t Pwm2 = 9; //Nodemcu PWM pin
  
int a0 = 10;   
int a1 = 11;      
int a2 = 5;     
int a3 = 4; 

void setup(){
	Serial.begin(9600);
	ArduinoUno.begin(4800);
  pinMode(10, OUTPUT);     
  pinMode(11, OUTPUT);     
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT); 
}

void loop(){
	float Direction = ArduinoUno.parseFloat();
	Serial.println(Direction);
 if (Direction == 3.0 )  {  
  // Right
  digitalWrite(a0, LOW); 
  digitalWrite(a1, LOW);

  digitalWrite(a2, LOW); 
  digitalWrite(a3, HIGH);
}

if (Direction == 5.0)  {  
  // stop
  digitalWrite(a0, LOW); 
  digitalWrite(a1, LOW);

  digitalWrite(a2, LOW); 
  digitalWrite(a3, LOW);
}

if (Direction == 1.0)  {
  // Forward
  digitalWrite(a0, LOW);   
  digitalWrite(a1, HIGH);
  
  digitalWrite(a2, LOW); 
  digitalWrite(a3, HIGH);

  }

if (Direction == 2.0)  {
  // BACK
  digitalWrite(a0, HIGH);   
  digitalWrite(a1, LOW);
  
  digitalWrite(a2,HIGH); 
  digitalWrite(a3, LOW);

  
}

if (Direction == 4.0)  {
  // left
  digitalWrite(a0, LOW);   
  digitalWrite(a1, HIGH);
  
  digitalWrite(a2, LOW); 
  digitalWrite(a3, LOW);

 
}

if (flag == 1)  {  
analogWrite(Pwm1, 665);  
analogWrite(Pwm2, 700);  
}
}


