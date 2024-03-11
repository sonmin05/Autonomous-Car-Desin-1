char value;

void setup(){
  Serial.begin(9600);
  
}

void loop(){
  if(Serial.available()>0){
    value=Serial.read();
    Serial.print("value:");
    Serial.println(value);
  }
}
