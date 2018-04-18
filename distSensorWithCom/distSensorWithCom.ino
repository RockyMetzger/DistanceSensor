#define echoPin  2
#define trigPin  6

String inputString = "";
boolean stringComplete = false;

void setup() {
  // put your setup code here, to run once:
  //attachInterrupt(digitalPinToInterrupt(2), RISING, PulseIn); 
  Serial.begin(9600);
  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);
  inputString.reserve(200);
}



void loop() {
  // put your main code here, to run repeatedly:
  if (stringComplete){    
    float rawDist, trueDist;  
    digitalWrite(trigPin, HIGH); //sets trigger high for 10 microseconds
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
  
    rawDist = pulseIn(echoPin, HIGH); //pulsein returns total time echo pin is held high
    trueDist = (rawDist/2) / 29.1;    //converts to cm
   
    Serial.println(String(trueDist)); //writes distance to serial output
    
  
    inputString = "";
    stringComplete = false;
  } 
  

}

void serialEvent(){ //raises on input of serial data from pi
  while(Serial.available()){
    char inChar = (char)Serial.read();
    inputString += inChar;
    
    if(inChar == '\n'){
      stringComplete = true; 
    }
  }
}

