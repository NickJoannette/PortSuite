int pwm = 9;

void setup() {
 
  pinMode(pwm, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
      analogWrite(pwm,255) ;      //setting pwm to 25 
      
}
