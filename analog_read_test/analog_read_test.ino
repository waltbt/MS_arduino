//int analogPin = A3; // potentiometer wiper (middle terminal) connected to analog pin 3
                    // outside leads to ground and +5V
int val = 0;  // variable to store the value read

void setup() {
  Serial.begin(9600);           //  setup serial
}

void loop() {
  val = analogRead(A0);  // read the input pin
  Serial.println(val);          // debug value
//  val = analogRead(A1);  // read the input pin
//  Serial.println(val);          // debug value
//  val = analogRead(A2);  // read the input pin
//  Serial.println(val);          // debug value
  delay(500);
}
