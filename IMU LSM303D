///////////////////////////IMU/////////////////////////
#include <Wire.h>
#include <LSM303.h>


#define ENA 12
#define IN1 8
#define IN2 9
#define IN3 10
#define IN4 11
#define ENB 13

#define THRESHOLD_ANGLE 10

LSM303 compass;

float heading_angle = 0.0;
float init_heading_angle = 17.0; //초기 방향
float target_heading_angle = 90;
float heading_angle_error = 0.0; //error 값

void setup()
{
  //put your setup code here, to run once:

  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);

  Serial.begin(115200);

  Wire.begin();   //IMU initiallize
  compass.init();
  compass.enableDefault();

  /*
   * Calibratoin values; the default values of +/-32767 for each axis
   * lead to an assumed magnetometer blas of 0. Use the Calibrate example
   * program to determine appropriate values for your particular unit.
   */
  compass.m_min = (LSM303::vector<int16_t>){-32767, -32767, -32767};
  compass.m_max = (LSM303::vector<int16_t>){+32767, +32767, +32767};
}

void motor_L_control(int speed)
{
  if (speed >=0)
  {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    analogWrite (ENA, speed); // 0-255
  }
  else
  {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    analogWrite (ENA, -speed);
  }
}

void motor_R_control(int speed)
{
  if (speed >=0)
  {
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    analogWrite (ENB, speed); // 0-255
  }
  else
  {
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    analogWrite (ENB, -speed);
  }
}

void imu_rotation(void)
{
  compass.read();
  float heading1 = compass.heading();
  compass.read();
  float heading2 = compass.heading();
  float heading = (heading1+heading2)/2;

  heading = 360 - heading;    // 회전 좌표계를 반시계 방향으로 할 것

  Serial.println(heading);

  heading_angle_error = target_heading_angle - heading;

  if(heading_angle_error > 180)
  {
    heading_angle_error = heading_angle_error - 360;
  }
  else if(heading_angle_error < -180)
  {
    heading_angle_error = heading_angle_error + 360;
  }
  else
  {
    
  }

  Serial.print("Heading Angle Error : ");
  Serial.print(heading_angle_error);  //heading angle error 표시
  Serial.print(" = ");
  Serial.print(target_heading_angle);
  Serial.print(" = ");
  Serial.println(heading);  //heading angle 표시

  if(heading_angle_error > THRESHOLD_ANGLE) //반시계방향으로 회전
  {
    motor_R_control(50);  motor_L_control(-50);
  }
  else if( (heading_angle_error >= -THRESHOLD_ANGLE) && (heading_angle_error <= THRESHOLD_ANGLE)) //정지
  {
    motor_R_control(0); // 왼쪽 바퀴가 앞으로 도는 지 확인
    motor_L_control(0);
  }
  else  // heading_angle_error < -2 //시계방향으로 회전
  {
    motor_R_control(-50);   motor_L_control(50);
  }
}

void loop(){

  imu_rotation();
}
