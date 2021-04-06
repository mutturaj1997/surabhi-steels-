const unsigned long delayinterval = 100000; // Common delay interval for LED ON LED OFF
const unsigned long delayintervalB = 150000; // B delay interval for LED ON LED OFF
const unsigned long delayintervalC = 90000; // C delay interval for LED ON LED OFF
const unsigned long delayintervalSpotLight = 180000; // C delay interval for LED ON LED OFF

#define LED_ON LOW
#define LED_OFF HIGH

//B area code starts
uint8_t ledAreaB = A1; //Right side area at the entrance

uint8_t sensorAAreaB=4; //9;
uint8_t sensorBAreaB=5; //10;
uint8_t sensorCAreaB=6; //11;
uint8_t sensorDAreaB=7; //12;

unsigned long LastTimeAreaB = 0;
byte stateLedAreaB = LOW;
byte LastsenseAreaB_st = LOW;
byte senseAreaB_st = LOW;

//B area code ends

//C area code starts
uint8_t ledAreaC = A2; //Inside area with PVC ceiling
//uint8_t sensorAAreaC=8; //4;
uint8_t sensorBAreaC=9; //5;
//uint8_t sensorCAreaC=10; //6;
uint8_t sensorDAreaC=11; //7;
//uint8_t sensorEAreaC=12; //8;

unsigned long LastTimeAreaC = 0;
byte stateLedAreaC = LOW;
byte LastsenseAreaC_st = LOW;
byte senseAreaC_st = LOW;

//C area code ends

//A area code starts
uint8_t ledAreaA = A0; //Left side area at the entrance  
uint8_t sensorAAreaA=A3;
uint8_t sensorBAreaA=A4;
uint8_t sensorCAreaA=A5;
uint8_t sensorDAreaA=2;
uint8_t sensorEAreaA=3;

unsigned long LastTimeAreaA = 0;
byte stateLedAreaA = LOW;
byte LastsenseAreaA_st = LOW; 
byte senseAreaA_st = LOW;

//A area code ends

uint8_t spotLight = 13;
unsigned long LastTimeSpotLight = 0;
byte stateSpotLight = LOW;

unsigned long RunCount = 0;

void setup() {
  // put your setup code here, to run once:
  delay(200);
  pinMode(ledAreaC, OUTPUT);
//  pinMode(sensorAAreaC, INPUT);
//  pinMode(sensorBAreaC, INPUT); //I/O 9
//  pinMode(sensorCAreaC, INPUT);
//  pinMode(sensorDAreaC, INPUT); //I/O 11
//  pinMode(sensorEAreaC, INPUT);

  pinMode(ledAreaB, OUTPUT);
  pinMode(sensorAAreaB, INPUT);
  pinMode(sensorBAreaB, INPUT);
  pinMode(sensorCAreaB, INPUT);
  pinMode(sensorDAreaB, INPUT);
  
  pinMode(ledAreaA, OUTPUT);
  pinMode(sensorAAreaA, INPUT);
  pinMode(sensorBAreaA, INPUT);
  pinMode(sensorCAreaA, INPUT);
  pinMode(sensorDAreaA, INPUT);
  pinMode(sensorEAreaA, INPUT);

  pinMode(spotLight, OUTPUT);
  
  Serial.begin(9600);         // initialize serial
  digitalWrite(ledAreaC, HIGH);
  digitalWrite(ledAreaB, HIGH);
  digitalWrite(ledAreaA, HIGH);
  digitalWrite(spotLight, HIGH);

  delay(200);
}

void(* resetFunc) (void) = 0; 

void loop() {
    RunCount++;
    
    AreaCRead();
    AreaBRead();
    AreaARead();

    SpotLightRead();
    
    if (RunCount >= 104000)
    {
      Serial.println(RunCount);
      resetFunc();
    }
    else
    {
      Serial.print("Run Count :");
      Serial.println(RunCount);
    }
}

/*
 * senseAreaB_st = sense state of area B
 * stateLedAreaB = LED State of area B
 * ledAreaB      = output of LEDs of area B
 */
void AreaBRead(){
    Serial.print ("B-1: ");
    Serial.println(digitalRead(sensorAAreaB));
    Serial.print("B-2: ");
    Serial.println(digitalRead(sensorBAreaB));
    Serial.print("B-3: ");
    Serial.println(digitalRead(sensorCAreaB));
    Serial.print("B-4: ");
    Serial.println(digitalRead(sensorDAreaB));
    
//    /////// Read sensors values of Area B
    senseAreaB_st = digitalRead(sensorAAreaB) || digitalRead(sensorBAreaB) || digitalRead(sensorCAreaB) || digitalRead(sensorDAreaB);
    
    //print the sense state of area B in serial monitor
    if (senseAreaB_st)
      Serial.println("Area B is sensing Motion");
    else
      Serial.println("Area B is not sensing any motion");

    if(stateLedAreaB == HIGH){                                //if LED's of area B has been ON for defined interval(delayinterval) then switch OFF the LED's of area B
      Serial.print("delayintervalB : ");
      Serial.println(delayintervalB);
      Serial.print("millis() - LastTimeAreaB : ");
      Serial.println(millis() - LastTimeAreaB);
      if((millis() - LastTimeAreaB) > delayintervalB){         // LastTimeAreaC is the last time interval when the LED is made ON
         digitalWrite(ledAreaB, LED_OFF);                     // Switch OFF LEDs of area B
         stateLedAreaB = LOW;                                 // Make LED state of area B LOW
      }
    }

      if((senseAreaB_st == HIGH)){                            // check current sense state of area B is HIGH and LED state of Area B is LOW
        digitalWrite(ledAreaB, LED_ON);                       // switch ON LEDs of area B
        digitalWrite(ledAreaC, LED_ON);                       // switch ON LEDs of area C
        digitalWrite(ledAreaA, LED_ON);                       // switch ON LEDs of area A
        digitalWrite(spotLight, LED_ON);
        stateLedAreaB = HIGH;                                 //make LED state of area B HIGH
        stateLedAreaC = HIGH;                                 //make LED state of area C HIGH
        stateLedAreaA = HIGH;                                 //make LED state of area A HIGH      
        stateSpotLight = HIGH;
        LastTimeAreaC = LastTimeAreaA = LastTimeAreaB = LastTimeSpotLight = millis();             //update the time when LED is made ON
        //LastTimeAreaA = LastTimeAreaB = LastTimeSpotLight = millis();
      }
}

void AreaCRead(){

//    senseAreaC_st = digitalRead(sensorBAreaC) || digitalRead(sensorDAreaC);
//
//    Serial.print("C-2: ");
//    Serial.println(digitalRead(sensorBAreaC));
//
//    Serial.print("C-4: ");
//    Serial.println(digitalRead(sensorDAreaC));

    //print the sense state of area C in serial monitor
//    if (senseAreaC_st)
//      Serial.println("Area C is sensing Motion");
//    else
//      Serial.println("Area C is not sensing any motion");

    if(stateLedAreaC == HIGH)
    {                                                         //if LED's of area C has been ON for defined interval(delayinterval) then switch OFF the LED's of area C
      if((millis() - LastTimeAreaC) > delayintervalC)
      {                                                       // LastTimeAreaC is the last time interval when the LED is made ON
         digitalWrite(ledAreaC, LED_OFF);                     // Switch OFF LEDs of area C
         stateLedAreaC = LOW;                                 // Make LED state of area C LOW
      }
    }
 
//    if((senseAreaC_st == HIGH))
//    {                                                       // check current sense state of area C is HIGH and LED state of Area C is LOW
//      digitalWrite(ledAreaC, LED_ON);                       // switch ON LEDs of area C
//      digitalWrite(ledAreaA, LED_ON);                       // switch ON LEDs of area A
//      digitalWrite(spotLight, LED_ON);
//      stateLedAreaC = HIGH;                                 //make LED state of area C HIGH
//      stateSpotLight = HIGH;
//      stateLedAreaA = HIGH;
//      LastTimeAreaA = LastTimeAreaC = LastTimeSpotLight = millis();                             //update the time when LED is made ON
//    }
}

/*
 * senseAreaA_st = sense state of area A
 * stateLedAreaA = LED State of area A
 * ledAreaA      = output of LEDs of area A
 */
void AreaARead(){

    Serial.print ("A-1: ");
    Serial.println(digitalRead(sensorAAreaA));
    Serial.print("A-2: ");
    Serial.println(digitalRead(sensorBAreaA));
    Serial.print("A-3: ");
    Serial.println(digitalRead(sensorCAreaA));
    Serial.print("A-4: ");
    Serial.println(digitalRead(sensorDAreaA));
    Serial.print("A-5: ");
    Serial.println(digitalRead(sensorEAreaA));
    
//  ////// Read sensors values of Area A
  senseAreaA_st = digitalRead(sensorAAreaA) || digitalRead(sensorBAreaA) || digitalRead(sensorCAreaA) || digitalRead(sensorDAreaA) || digitalRead(sensorEAreaA) || senseAreaB_st;
    
    //print the sense state of area B in serial monitor
    if (senseAreaA_st)
      Serial.println("Area A is sensing Motion");
    else
      Serial.println("Area A is not sensing any motion");

    if(stateLedAreaA == HIGH || stateLedAreaB == HIGH || stateLedAreaC == HIGH){ //if LED's of area A has been ON for defined interval(delayinterval) then switch OFF the LED's of area A
      if((millis() - LastTimeAreaA) > delayinterval){           // LastTimeAreaA is the last time interval when the LED is made ON
         digitalWrite(ledAreaA, LED_OFF);                       // Switch OFF LEDs of area A
         stateLedAreaA = LOW;                                   // Make LED state of area A LOW
      }
      Serial.print("A-Millis ");
      Serial.println(millis());
      Serial.print("A-Last Time AreaA ");
      Serial.println(LastTimeAreaA);
      Serial.print("A-delayInterval ");
      Serial.println(delayinterval);
    }

    if(senseAreaA_st == HIGH){  // check current sense state of area A is HIGH and LED state of Area A is LOW
      digitalWrite(ledAreaA, LED_ON);                         // switch ON LEDs of area A
      digitalWrite(ledAreaC, LED_ON);                         // switch ON LEDs of area C
      digitalWrite(spotLight, LED_ON);
      stateLedAreaA = HIGH;                                   //make LED state of area A HIGH
      stateLedAreaC = HIGH;                                   //make LED state of area C HIGH
      stateSpotLight = HIGH;
      LastTimeAreaC = LastTimeAreaA = LastTimeSpotLight = millis();               //update the time when LED is made ON
    }
}

void SpotLightRead(){

    if(stateSpotLight == HIGH)
    {                                                         //if LED's of area C has been ON for defined interval(delayinterval) then switch OFF the LED's of area C
      if((millis() - LastTimeSpotLight) > (delayintervalSpotLight))
      {                                                       // LastTimeAreaC is the last time interval when the LED is made ON
         digitalWrite(spotLight, LED_OFF);                     // Switch OFF LEDs of area C
         stateSpotLight = LOW;                                 // Make LED state of area C LOW
      }
    }
}
