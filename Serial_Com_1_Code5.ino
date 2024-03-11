int value=77;


void setup(){
  Serial.begin(9600);
  Serial.print("DEC:");
  Serial.print("BIN:");
  Serial.println(value,BIN);
  Serial.print("OCT:");
  Serial.println(value,OCT);
  Serial.print("HEX;");
  Serial.println(value,HEX);
  
}

void loop(){
  
}
