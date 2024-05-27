#include<NewPing.h>

#define trigger_pin 13
#define echo_pin 12
#define MAX_DISTANCE 100

NewPing sonar_f(trigger_pin,echo_pin,MAX_DISTANCE);

int k,avg,avg_b;

int sonar_avg_filter(void)
{  
  k = 1;
  avg = avg_b*((k-1)/k)+(1/k)*sonar_f.ping_cm();
  avg_b = avg ;
  k++;
}

void setup() 
{
  Serial.begin(9600);
}

void loop() 
{
  sonar_avg_filter();
  Serial.print("Distance: ");
  Serial.print(sonar_f.ping_cm());
  Serial.print(" average: ");
  Serial.println(avg);
}
