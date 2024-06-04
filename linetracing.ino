#define ledPin 13 // LED는 디지털 핀 13에 연결됨

#define LINE_DETECT_WHITE 1

#define motor_speed_offset 25
int linesensor_data[5] = {0,0,0,0,0};
int linesensor_pin[5] = {21,20,19,18,17};

#define IN1 11
#define IN2 10
#define ENA 7

#define IN3 9
#define IN4 8
#define ENB 6
int read_digital_line_sensor(void)
{
  int i;
  int sum= 0;
  for(i=0;i<5;i++)
  {
    if(LINE_DETECT_WHITE == 0)
    {
      linesensor_data[i] = 1 - digitalRead(linesensor_pin[i]);
    }
    else
    {
      linesensor_data[i] = digitalRead(linesensor_pin[i]);
    }
    sum += linesensor_data[i];
  }
  if(sum == 5)
  {
      return sum;
  }
  else if (sum ==2)
  {
      if( (linesensor_data[3] == 1) && (linesensor_data[4] == 1) ) return 3;
      if( (linesensor_data[2] == 1) && (linesensor_data[3] == 1) ) return 1;
      if( (linesensor_data[1] == 1) && (linesensor_data[2] == 1) ) return -1;
      if( (linesensor_data[0] == 1) && (linesensor_data[1] == 1) ) return -3;
  }
  else if (sum == 1)
  {
      if(linesensor_data[0] == 1) return -4;
      if(linesensor_data[1] == 1) return -2;
      if(linesensor_data[2] == 1) return 0;
      if(linesensor_data[3] == 1) return 2;
      if(linesensor_data[4] == 1) return 4;
  }
  else if(sum == 3)
  {
      return -10;
  }
  else
  {
      return -5;
  }
}
void motor_L_control(int speed)
{
    if (speed >= 0)
    {
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, HIGH);
        analogWrite(ENA,speed ); // 0-255
    }
    else
    {
        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, LOW);
        analogWrite(ENA, -speed); 
    }
}

void motor_R_control(int speed)
{
    if (speed >= 0)
    {
        digitalWrite(IN3, HIGH);
        digitalWrite(IN4, LOW);
        analogWrite(ENB, speed); // 0-255
    }
    else
    {
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, HIGH);
        analogWrite(ENB, -speed);
    }
}

void robot_control(int left_motor_speed, int right_motor_speed)
{
    motor_L_control(left_motor_speed);
    motor_R_control(right_motor_speed);
}
void setup(){
  int i;
  pinMode(ledPin, OUTPUT);

  for(i=0;i<5;i++)
  {
      pinMode(linesensor_pin[i], INPUT);
  }
  Serial.begin(9600); 
}

void line_following(int line_type) 
{
  switch(line_type)
  {
    case -4:
      // 왼쪽으로 큰 각도로 회전
          motor_R_control(-200);
          motor_L_control(80);
          break;
    case -3:
      // 왼쪽으로 약간 각도로 회전
          motor_R_control(-180);
          motor_L_control(40);
          break;

    case -2:
      // 왼쪽으로 약간 각도로 회전
          motor_R_control(-160);
          motor_L_control(10);
          break;

    case -1:
      // 왼쪽으로 작은 각도로 회전
          motor_R_control(-140);
          motor_L_control(20);
          break;

    case 0:  
      // 직진
          motor_R_control(-80);
          motor_L_control(80);
          break;

    case 1:
      // 오른쪽으로 작은 각도로 회전
          motor_R_control(-20);
          motor_L_control(140);
          break;

    case 2:
      // 오른쪽으로 약간 각도로 회전
          motor_R_control(-10);
          motor_L_control(160);
          break;

    case 3:
      // 오른쪽으로 약간 각도로 회전
          motor_R_control(-40);
          motor_L_control(180);
          break;

    case 4:
      // 오른쪽으로 큰 각도로 회전
          motor_R_control(-80);
          motor_L_control(200);
          break;

    case 5:
      // 선을 발견하지 못한 경우, 정지
          motor_R_control(0);
          motor_L_control(0);
          break;
  }
}



void loop(){
  int i;
  int sum = 0;
  int line_type = 0;
  line_type = read_digital_line_sensor();  // 함수 실행
  sum = read_digital_line_sensor();
  
  Serial.print("Input data =");
  for(i=0;i<5;i++)
  {
      Serial.print(linesensor_data[i]);
      Serial.print(" ");
  }
  Serial.print(sum);
  Serial.println(" ");

  line_following(line_type);
}
