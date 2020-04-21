//int led = 0;
//
//void setup() {
//  //Serial.setTimeout(4000);
//  Serial.begin(115200); // use the same baud-rate as the python side
//  pinMode(LED_BUILTIN, OUTPUT); 
//}
//void loop() {
//  while(Serial.available()==0){
//    digitalWrite(LED_BUILTIN, HIGH);
//  }
//
//  while(true){
//      digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
//  delay(1000);               // wait for a second
//  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
//  delay(1000);               // wait for a second
//  }
//  
//
//
//
////  digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
////  delay(100);               // wait for a second
////  digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
////  delay(100);
//}



void setup() {
 // pinMode(LED_BUILTIN, OUTPUT);
//  Serial.begin(115200,SERIAL_8N1);
  Serial.begin(9600);
//  while(!Serial){
//  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
//  delay(1000);               // wait for a second
//  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
//  delay(1000);  
//  }
}
void loop() {
  while(Serial.available() > 0) {
    byte data = Serial.read();
//    char str[2];
//    str[0] = data;
//    str[1] = '\0';
    Serial.print('A');
  }
}
