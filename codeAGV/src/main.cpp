//#define AGV_MCP // chuyển AGV thực tế và board test not define:board test//define is 
#include <Arduino.h>
#include <IO_define.h>
#include <Arduino_FreeRTOS.h>
#include <ModbusRtu.h>
#include <MCP4922.h>
#include <MCP3202.h>
#include <SPI.h>
MCP4922 DAC(51, 52, 53, 120);       // (MOSI, SCK, CS, LDAC) define Connections for MEGA_board
MCP3202 adc = MCP3202(PIN_LINE_TU); // Chân CS // 46
#include <const.h>
#include <PID_v1.h>
#include <Variable.h>
#include <semphr.h>
#include <Magnetic_Sensor.h>
#include <BLDC.h>
#include <Lidar.h>
#include <RFID_Sensor.h>
#include <Communication.h>
#include <Wire.h>
#include <data.h>
#define ID 1
//  *  Modbus object declaration
//  *  u8id : node id = 0 for master, = 1..247 for slave
//  *  port : serial port
//  *  u8txenpin : 0 for RS-232 and USB-FTDI
//  *               or any pin number > 1 for RS-485
Modbus slave(ID, Serial1, 1); // set Serial1 là cổng giao tiếp với HMI
int sharedData = 0;           // Biến toàn cục chia sẻ dữ liệu
String s;

void Communication(void *pvParameters)
{
  while (1)
  {
    slave.poll(Modbus_HMI, 20);
    HMI();
    vTaskDelay(30 / portTICK_PERIOD_MS);
  }
}
void DATA(void *pvParameters)
{
  while (1)
  {
    if (Serial.available() > 0)
    {
      String input = Serial.readString(); // Đọc dữ liệu từ Serial Monitor
      newValue = input.toInt();           // Chuyển đổi dữ liệu sang kiểu int
      Select_Mode_Lidar = newValue;
      // Serial.print("IN:");
      // Serial.print(Select_Mode_Lidar);
    }
  
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}
void CHECK(void *pvParameters)
{
  while (1)
  {
   // Serial.println("offset:" + String(offset));
    Serial.println("OUTPUT:" + String(Output));
    Serial.println("MODE:" + String(MODE));
    Serial.println("last_poss:" + String(last_poss));
    //Serial.println("MagneticMode:" + String(MagneticMode));
    Serial.println("Lidar_Mode:" + String(Lidar_Mode));
    //Serial.println("MotorStraigh:" + String(MotorStraigh));
    Serial.println("Select_Mode_Lidar:" + String(Select_Mode_Lidar));
    Serial.println("RightSpeed:" + String(RightSpeed));
    Serial.println("LeftSpeed:" + String(LeftSpeed));
    Serial.println("CurrentSpeed:" + String(CurrentSpeed));
    Serial.println("maxspeed:" + String(Maxspeed));
    //Serial.println("value_magnetic:" + String(value_magnetic));
    // if (MODE == 2)
    // {
    //   Serial.println("ID_AGV>Tag_rfid>Action:" + String(ID_AGV) + '>' + String(ID_AGV) + '>' + String(Action));
    // }
    // if (MODE == 1)
    // {
    //   Serial.println("speed>angle:" + String(speed_man) + '>' + String(angle_man));
    // }
     Serial.println("--------------------------------");

    
    vTaskDelay(300 / portTICK_PERIOD_MS);
  }
}
void setup()
{
  IO();
  Serial.begin(115200);  // COM MAY TINH
  Serial1.begin(115200); // HMI
  Serial2.begin(38400);  // GIAO TIEP VOI RFID
  slave.start();
  SPI.begin();
  adc.begin();
  Wire.begin(8);
  Wire.onReceive(receiveEvent); // lệnh nhận dữ liệu từ i2c esp32
  Wire.onRequest(sendData);     // Gắn hàm sendData vào sự kiện onRequest
  // Wire.onRequest(sendData_AUTO_MAN); // Gắn hàm sendData_AUTO_MAN vào sự kiện onRequest
  xTaskCreate(Magnetic_Sensor, "Magnetic_Sensor", 320, NULL, 15, NULL);
  xTaskCreate(BLDC, "BLDC", 320, NULL, 14, NULL);
  xTaskCreate(Communication, "Communication", 320, NULL, 12, NULL);
  xTaskCreate(RFID_sensor, "RFID_sensor", 320, NULL, 11, NULL);
  xTaskCreate(MODERFID, "MODERFID", 320, NULL, 8, NULL);
  xTaskCreate(processReceivedData, "processReceivedData", 320, NULL, 7, NULL);
  xTaskCreate(Lidar, "Lidar", 120, NULL, 6, NULL);
  xTaskCreate(AccelDecel, "AccelDecel", 320, NULL, 4, NULL);
  xTaskCreate(DATA, "DATA", 320, NULL, 10, NULL);
  xTaskCreate(MotorController, "MotorController", 320, NULL, 3, NULL);
  xTaskCreate(CHECK, "CHECK", 320, NULL, 2, NULL);
   // Khởi tạo PID
  // pid.SetMode(AUTOMATIC);  // Chế độ tự động
  // pid.SetSampleTime(0);  // Khoảng thời gian lấy mẫu (ms)
  // pid.SetOutputLimits(-ConstAutoMaxSpeed,ConstAutoMaxSpeed);  // Giới hạn từ 0 đến 255
  //Input=last_poss;
}
void loop()
{
}