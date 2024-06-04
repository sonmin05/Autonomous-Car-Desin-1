#include <Wire.h>
#include <LSM303.h>

LSM303 compass; // LSM303 객체 생성

// Function prototypes
#define NO_MISSION 4
int read_line_sensor();
void read_sonar_sensor();
void line_following(int line_index);
void obstacle_avoidance();
void read_imu_sensor();
void motor_L_control(int speed);
void motor_R_control(int speed);
void imu_rotation(); 

// Global variables
int front_sonar = 0;
int right_sonar = 0;
int left_sonar = 0;
int heading_angle_error = 0;
int target_heading_angle = 0;
int heading_angle = 0;
bool mission_flag[NO_MISSION] = {-1, -1, -1, -1};

void setup() 
{
  Serial.begin(9600);
  Wire.begin();
  compass.init(); // LSM303 초기화
  
  compass.enableDefault();
  
  /*
  Calibration values; the default values of +/-32767 for each axis
  lead to an assumed magnetometer bias of 0. Use the Calibrate example
  program to determine appropriate values for your particular unit.
  */
  compass.m_min = (LSM303::vector<int16_t>){-32767, -32767, -32767};
  compass.m_max = (LSM303::vector<int16_t>){+32767, +32767, +32767};
}

void loop() 
{
  int line_index = -10;

  line_index = read_line_sensor();
  
  mission_flag[0] = 0;

  if (mission_flag[0] == 0) 
  {
    read_sonar_sensor();
    if (front_sonar < 200) 
    {
      mission_flag[0] = 1;
      mission_flag[1] = 0;
    }
    else if ((line_index == 0) && (right_sonar <= 100) && (left_sonar <= 100)) 
    {
      mission_flag[2] = 0;
    }
    else 
    {
      line_following(line_index);
    }
  }
  
  if (mission_flag[1] == 0) 
  {
    obstacle_avoidance(); 
    mission_flag[1] = 1;
  }
  
  imu_rotation();
}

void imu_rotation() 
{
  #define THRESHOLD_ANGLE1 15
  #define THRESHOLD_ANGLE2 7
  
  bool flag = 1; // bool 타입은 0,1
  int rotation_angle = 0; // 회전 각도 변수 추가
  while(flag) 
  {
    read_imu_sensor();
    
    // Calculate heading angle error
    heading_angle_error = target_heading_angle - heading_angle;
    
    if (heading_angle_error > 180) 
    {
      heading_angle_error -= 360;
    } 
    else if (heading_angle_error < -180) 
    {
      heading_angle_error += 360;
    }
    
    // Print heading angle error
    Serial.print("Heading Angle Error: ");
    Serial.print(heading_angle_error);
    Serial.print(" = ");
    Serial.print(target_heading_angle);
    Serial.print(" - ");
    Serial.println(heading_angle);
    
    // Motor control based on heading angle error
    if (heading_angle_error > THRESHOLD_ANGLE1) 
    { 
      motor_L_control(-70); 
      motor_R_control(60);
    } 
    else if ((heading_angle_error >= THRESHOLD_ANGLE2) && (heading_angle_error < THRESHOLD_ANGLE1)) {
      motor_L_control(-40); 
      motor_R_control(40);
    } 
    else if ((heading_angle_error >= -THRESHOLD_ANGLE2) && (heading_angle_error < THRESHOLD_ANGLE2)) { 
      motor_L_control(0); 
      motor_R_control(0);
      rotation_angle += abs(heading_angle_error); // 회전 각도를 누적
      if (rotation_angle >= 90) // 90도 이상 회전했을 경우
      {
        flag = 0; // 루프 종료
      }
    } 
    else if ((heading_angle_error >= -THRESHOLD_ANGLE1) && (heading_angle_error <= -THRESHOLD_ANGLE2)) { 
      motor_L_control(70); 
      motor_R_control(-70);
    } 
    else 
    { 
      motor_L_control(70); 
      motor_R_control(-70);
    }
  }
}

int read_line_sensor() 
{
  return 0;
}

void read_sonar_sensor() 
{

}

void line_following(int line_index) 
{

}

void obstacle_avoidance() 
{

}

void read_imu_sensor() 
{
  // LSM303 라이브러리를 사용하여 가속도 및 자기계 값을 읽어옴
  compass.read(); // 가속도 및 자기계 값 읽기
  float accel_x = compass.a.x; // X축 가속도 값
  float accel_y = compass.a.y; // Y축 가속도 값
  float accel_z = compass.a.z; // Z축 가속도 값
  
  // 가속도 값에 따라서 heading_angle을 업데이트
  // 예시로, X축 가속도 값을 사용하여 heading_angle 업데이트
  heading_angle = atan2(accel_y, accel_x) * (180 / PI); // atan2 함수를 사용하여 heading_angle 계산
}

void motor_L_control(int speed) 
{

}

void motor_R_control(int speed) 
{

}
