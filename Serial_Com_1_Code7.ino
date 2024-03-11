char value='a';
float value_dot=1.2345;

void setup(){
  Serial.begin(9600);
  Serial.print("value:");
  Serial.println(value);
  Serial.print("value_dot:");
  Serial.println(value_dot,4);
}

void loop(){
  
}
