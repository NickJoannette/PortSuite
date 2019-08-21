int led = 9;
void setup() {
  
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(led, OUTPUT);
}

void loop() {
  if (Serial.available())
  {
     int data = Serial.read();
      if (data == 'A')digitalWrite(led,HIGH);
      else if (data == 'B') digitalWrite(led,LOW);

    
  }
 
}
