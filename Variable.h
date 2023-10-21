// Khai báo cho Modbus
uint16_t Modbus_HMI[20];
// biến của magnetic
int MagneticMode = 0; // Chế độ của cảm biến dò line: có 4 chế độ MODE0=THẲNG, MODE1=RẼ TRÁI , MODE2=RẼ PHẢI , MODE3= KHÔNG CHỌN
float channel1 = 0;
int Position;
// Line từ
int possition_magnetic = 0; // vị trí của line từ
// Chế độ
int MANUAL1, EMG;
int MODE = 2;
// RFID
int8_t state = 0;
int count = 10;
int ReadWrite;                // 1 la read, 2 la write
bool ReadBuffer, WriteBuffer; // luu gia tri doc lan truoc
String SR = "SR000002#";      // lệnh dùng để đọc RFID
String READ = "";
String a, b, c;
char RFRead[4];
char RFLast[4];
String CodeRFID = "0000";
int ModeRFID;
// Lidar
int Lidar_Mode; // cảnh báo của lidar , =0 không có vật cản, =1 phát hiện vật cản(đi chậm lại),=2 đi chậm hơn, =3 nguy hiểm dừng gấp
int Select_Mode_Lidar;
// Motor BLDC
int RightSpeed = 0;
int LeftSpeed = 0;
int RightSpeed_DAC = 0;
int LeftSpeed_DAC = 0;
int Maxspeed = 0;
int Decel = 0;
int Accel = 0;
int CurrentSpeed = 0;
int Acceleration = 50; // Đặt lượng tăng/giảm tốc độ ban đầu ở đây
int Increment = 10;    // Tốc độ tăng dần sau mỗi lần vào chương trình
// HMI
bool NEXT = 0;
//
int bu = 40;
int bu_tang_giam = 65;
int bu_lidar = 250;
//
// int modeMPC =0;   // chuyển đổi giữa MCP và Analog

int cons;
int cons1 = 2.4;
int cons2 = 4.1;
int cons3 = 9.7;
int cons4 = 9.9;
int cons5 = 10.3;
int cons6 = 11.5;
int cc = 50;
int const_man = 3;
bool MotorStraigh = 1;
//
int done_action = 0; // Biến kiểu int để gửi cho Master
int ID_AGV = 0;
int Step = 0;
String Tag_rfid; // tag rfid cần tìm
int Action = 0;  // action cần thực hiện khi tìm thấy tag_rfid

// ble
int speed_man, angle_man;

char requestType;
int n;
int newValue;
String Str_ATtoESP32; // Chuỗi bạn muốn gửi
int value_magnetic;

//
// Khai báo các hệ số PID
int lastError = 0;
double integral = 0;

double Kp = 0.9;  // Hệ số tỷ lệ (Proportional)
double Ki = 0.05; // Hệ số tích phân (Integral)
double Kd = 0;    // Hệ số đạo hàm (Derivative)

double Kp1 = 0.5;  // Hệ số tỷ lệ (Proportional)
double Ki1 = 0.01; // Hệ số tích phân (Integral)
double Kd1 = 0.0;  // Hệ số đạo hàm (Derivative)

double Kp2 = 0.5;  // Hệ số tỷ lệ (Proportional)
double Ki2 = 0.01; // Hệ số tích phân (Integral)
double Kd2 = 0.0;  // Hệ số đạo hàm (Derivative)
// Khai báo biến PID và setpoint
double Setpoint = 0; // Thay đổi giá trị này
double Input, Output;
int offset;

int AddValue, AddSpeed, MinusSpeed;
