int Hall_Effect_In = A1;

void setup() {
Serial.begin(9600);
}

void loop() {
  Serial.println(analogRead(Hall_Effect_In));


}
