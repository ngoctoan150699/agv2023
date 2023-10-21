// modeRFID = 0;// do nothing
// ModeRFID = 1;// CHẾ ĐỘ DỪNG , HMI 0x13 NHẤN LÀ ĐI TIẾP
// ModeRFID = 2;// CHẾ ĐỘ ĐI CHẬM 5S, CHUYỂN MODE RẺ TRÁI
// ModeRFID = 3;// CHẾ ĐỘ ĐI CHẬM 5S, CHUYỂN MODE RẺ PHẢI
// ModeRFID = 4;// CHẾ ĐỘ ĐI CHẬM 5S, ĐI BÌNH THƯỜNG(BỎ MODE TRÁI OR PHẢI)
//PID pid(&Input, &Output, &Setpoint, Kp, Ki, Kd, P_ON_M, DIRECT);
#define PID_
void BLDC(void *pvParameters)
{
  digitalWrite(motor_left_start, LOW);
  digitalWrite(motor_left_dir, LOW);
  digitalWrite(motor_right_start, LOW);
  digitalWrite(motor_right_dir, HIGH);
  digitalWrite(motor_brake, LOW); // setup io
  // DAC.Set(RightSpeed, LeftSpeed);
  while (1)
  {
    if (MODE == 2) // auto
    {
      MotorStraigh = 1;
      // Serial.println(last_poss);
      if (digitalRead(over_left) == 0)
      {
        RightSpeed = 100;
        LeftSpeed = ConstAutoMaxSpeed;
      }
      else if (digitalRead(over_right) == 0)
      {
        RightSpeed = ConstAutoMaxSpeed;
        LeftSpeed = 100;
      }
      else
      {
        if (last_poss == 0 or last_poss == 70)
        {
          RightSpeed = CurrentSpeed;
          LeftSpeed = CurrentSpeed;
          offset = 0;
          // if (last_poss == 0)
          // {
          //   Input = cons * (abs(last_poss) + 1) * abs(last_poss);
          //   pid.Compute();
          // }
        }
#ifdef PID_
        else
        {
          if (abs(last_poss) > 0 && abs(last_poss) < 2)
          {
            cons = cons1;
          }
          if (abs(last_poss) >= 2 && abs(last_poss) < 4)
          {
            cons = cons2;
          }
          if (abs(last_poss) >= 4 && abs(last_poss) < 7)
          {
            cons = cons3;
          }
          if (abs(last_poss) >= 7 && abs(last_poss) < 9)
          {
            cons = cons4;
          }
          if (abs(last_poss) >= 9 && abs(last_poss) < 12)
          {
            cons = cons5;
          }
           if (abs(last_poss) >= 12 && abs(last_poss) < 15)
          {
            cons = cons6;
          }
          AddValue = cons * (abs(last_poss) + 1);
          AddSpeed = CurrentSpeed + AddValue * abs(last_poss);
          MinusSpeed = CurrentSpeed - AddValue * abs(last_poss);
          offset = cons * (abs(last_poss) + 1) * abs(last_poss);
          if (AddSpeed > 3000)
          {
            AddSpeed = 3000;
          }
          if (MinusSpeed < 0)
          {
            MinusSpeed = 0;
          }
          if (last_poss < 0)
          {
            RightSpeed = AddSpeed;
            LeftSpeed = MinusSpeed;
          }
          else if (last_poss > 0)
          {
            RightSpeed = MinusSpeed;
            LeftSpeed = AddSpeed;
          }

          // Tính toán điều khiển
          // pid.Compute();
          // offset = map(Output, -15, 15, -500, 500);
          // int offset = cons * (last_poss + 1) * last_poss;
          // offset = cons *last_poss*last_poss+cons*abs(last_poss);
          // int temp1 = CurrentSpeed + (last_poss < 0 ? abs(offset) : -abs(offset));
          // int temp2 = CurrentSpeed + (last_poss < 0 ? -abs(offset) : abs(offset));
          // offset = 0;
          // RightSpeed = constrain(temp1, 0, ConstAutoMaxSpeed);
          // LeftSpeed = constrain(temp2, 0, ConstAutoMaxSpeed);
        }
#else
        else
        {
          // Input = abs(last_poss);
          // // Tính toán lỗi (độ chênh lệch giữa giá trị thực tế và giá trị mục tiêu)
          // int error = Input; // Giá trị mục tiêu là 0
          // double P = 0;
          // double I = 0;
          // double D = 0;
          // // Tính toán thành phần P
          // P = Kp * error;
          // // Tính toán thành phần I
          // integral += error;
          // I = Ki * integral;
          // // Tính toán thành phần D
          // int derivative = error - lastError;
          // D = Kd * derivative;
          // lastError = error;
          // Output = P + I + D;
          // Input = cons * (abs(last_poss) + 1) * abs(last_poss);

          int P = (last_poss);
          int I = I + last_poss;
          Input = cons * P + cons1 * I;
          pid.Compute();
          AddValue = abs(Output);
          AddSpeed = CurrentSpeed + AddValue;
          MinusSpeed = CurrentSpeed - AddValue;
          if (AddSpeed > ConstAutoMaxSpeed)
          {
            AddSpeed = ConstAutoMaxSpeed;
          }
          if (MinusSpeed < 0)
          {
            MinusSpeed = 0;
          }
          if (last_poss < 0)
          {
            RightSpeed = AddSpeed;
            LeftSpeed = MinusSpeed;
          }
          else if (last_poss > 0)
          {
            RightSpeed = MinusSpeed;
            LeftSpeed = AddSpeed;
          }
        }
#endif
      }
      // CurrentSpeed = constrain(CurrentSpeed, 0, ConstAutoMaxSpeed);
      // DAC.Set(RightSpeed, LeftSpeed);
    }
    else if (MODE == 1)
    {
      if (abs(angle_man) >= 90)
      {
        MotorStraigh = 0;
      }
      else
      {
        MotorStraigh = 1;
      }

      {
        if (angle_man == 0 or angle_man == 180)
        {
          RightSpeed = CurrentSpeed;
          LeftSpeed = CurrentSpeed;
        }
        else
        {
          int angle = abs(angle_man);
          int addValue = angle >= 90 ? angle * const_man : (180 - angle) * const_man;
          int AddSpeed = CurrentSpeed + addValue;
          int MinusSpeed = CurrentSpeed - addValue;
          if (angle_man < 0)
          {
            RightSpeed = AddSpeed;
            LeftSpeed = MinusSpeed;
          }
          else if (angle_man > 0)
          {
            RightSpeed = MinusSpeed;
            LeftSpeed = AddSpeed;
          }
        }
      }
    }
    CurrentSpeed = constrain(CurrentSpeed, 0, ConstAutoMaxSpeed);
    RightSpeed = constrain(RightSpeed, 0, 3000);
    LeftSpeed = constrain(LeftSpeed, 0, 3000);
    RightSpeed_DAC = map(RightSpeed, 0, 3000, 0, 2000);
    LeftSpeed_DAC = map(LeftSpeed, 0, 3000, 0, 2000);
    DAC.Set(RightSpeed_DAC, LeftSpeed_DAC);
    vTaskDelay(30 / portTICK_PERIOD_MS);
  }
}
void AccelDecel(void *pvParameters)
{
  while (1)
  {
    if (MODE == 2)
    {
      if (ModeRFID == 0)
      {
        if (last_poss != 70)
        {
          Maxspeed = ConstAutoMaxSpeed;
          if (Lidar_Mode == 2 or Lidar_Mode == 1)
          {
            Maxspeed = Maxspeed - Lidar_Mode * 600;
          }
          else if (Lidar_Mode == 3)
          {
            Maxspeed = 0;
          }
        }
        else
        {
          Maxspeed = 0;
        }
      }
    }
    else if (MODE == 1)
    {
      Maxspeed = (speed_man * ConstManualMaxSpeed) / 100;
    }

    Maxspeed = constrain(Maxspeed, 0, ConstAutoMaxSpeed);
    Decel = Accel = ConstAutoDecelTime;
    if (CurrentSpeed != Maxspeed)
    {
      int speedChange = (CurrentSpeed < Maxspeed) ? bu_tang_giam : -bu_tang_giam;
      vTaskDelay((speedChange > 0 ? Accel : Decel) / portTICK_PERIOD_MS);
      CurrentSpeed += speedChange;
    }
    CurrentSpeed = constrain(CurrentSpeed, 0, ConstAutoMaxSpeed);
    vTaskDelay(30 / portTICK_PERIOD_MS);
  }
}
void MotorController(void *pvParameters)
{
  while (1)
  {
    if (MotorStraigh == 1)
    {
      digitalWrite(motor_left_dir, LOW);
      digitalWrite(motor_right_dir, HIGH);
    }
    else
    {
      digitalWrite(motor_left_dir, HIGH);
      digitalWrite(motor_right_dir, LOW);
    }
    // DAC.Set(RightSpeed, LeftSpeed);
    vTaskDelay(100 / portTICK_PERIOD_MS);
  }
}
void MODERFID(void *pvParameters)
{
  while (1)
  {
    if (MODE == 2)
    {
      if (Tag_rfid != NULL)
      {
        // Serial.print("TAG_YEU CAU: ");
        // Serial.println(Tag_rfid);
      }
      if (CodeRFID != "0000")
      {
        // Serial.print("TAG_DOC DUOC: ");
        // Serial.println(CodeRFID);
      }

      if (CodeRFID == Tag_rfid)
      {
        ModeRFID = Action;
        // Serial.println(ModeRFID);
      }
      else
      {
        ModeRFID = 0;
      }

      if (MODE == 2 && ModeRFID != 0)
      {
        if (ModeRFID == 1)
        {
          Maxspeed = 0;
          if (NEXT == 1)
          {
            Maxspeed = ConstAutoMaxSpeed;
            CodeRFID = "0000";
            done_action = 1;
          }
        }
        else
        {
          Maxspeed = ConstAutoMaxSpeed / 2;
          // MagneticMode = ModeRFID - 1;
          // Select_Mode_Lidar = MagneticMode;
          vTaskDelay(3000 / portTICK_PERIOD_MS);
          MagneticMode = 0;
          Select_Mode_Lidar = 0;
          Maxspeed = ConstAutoMaxSpeed;
          CodeRFID = "0000";
          done_action = 1;
        }
      }
    }
    vTaskDelay(30 / portTICK_PERIOD_MS);
  }
}

// void MODERFID(void *pvParameters)
// {
//   while (1)
//   {
//     if (CodeRFID == Tag_rfid)
//     {
//       ModeRFID == Action;
//     }
//     if (AUTO == 1 && ModeRFID != 0)
//     {
//       if (ModeRFID == 1) // CHẾ ĐỘ DỪNG , HMI 0x13 NHẤN LÀ ĐI TIẾP
//       {
//         Maxspeed = 0;
//         MagneticMode = 0;
//         if (NEXT == 1)
//         {
//           Maxspeed = ConstAutoMaxSpeed;
//         }
//       }
//       if (ModeRFID == 2) // CHẾ ĐỘ ĐI CHẬM 5S, CHUYỂN MODE RẺ TRÁI
//       {
//         Maxspeed = ConstAutoMaxSpeed / 2;
//         MagneticMode = 1;
//         Select_Mode_Lidar = 1;
//         vTaskDelay(3000 / portTICK_PERIOD_MS);
//         MagneticMode = 0;
//         Select_Mode_Lidar = 0;
//         Maxspeed = ConstAutoMaxSpeed;
//       }
//       if (ModeRFID == 3) // CHẾ ĐỘ ĐI CHẬM 5S, CHUYỂN MODE RẺ PHẢI
//       {
//         Maxspeed = ConstAutoMaxSpeed / 2;
//         MagneticMode = 2;
//         Select_Mode_Lidar = 2;
//         vTaskDelay(3000 / portTICK_PERIOD_MS);
//         MagneticMode = 0;
//         Select_Mode_Lidar = 0;
//         Maxspeed = ConstAutoMaxSpeed;
//       }
//       if (ModeRFID == 4) // CHẾ ĐỘ ĐI CHẬM 5S, ĐI BÌNH THƯỜNG(BỎ MODE TRÁI OR PHẢI)
//       {
//         Maxspeed = ConstAutoMaxSpeed / 2;
//         MagneticMode = 0;
//         Select_Mode_Lidar = 0;
//         vTaskDelay(3000 / portTICK_PERIOD_MS);
//         Maxspeed = ConstAutoMaxSpeed;
//       }
//     }
//     vTaskDelay(30 / portTICK_PERIOD_MS);
//   }
// }

// Maxspeed = constrain(Maxspeed, 0, ConstAutoMaxSpeed);
// DAC.Set(RightSpeed, LeftSpeed);
// vTaskDelay(50 / portTICK_PERIOD_MS);
// v

// if (AUTO == 1 && ModeRFID != 0)
// {
//   if (ModeRFID == 1 or ModeRFID == 2 or ModeRFID == 3 or ModeRFID == 4 or ModeRFID == 5 or ModeRFID == 6) // CHẾ ĐỘ ĐI CHẬM 5S, ĐI BÌNH THƯỜNG(BỎ MODE TRÁI OR PHẢI)
//   {
//     Maxspeed = ConstAutoMaxSpeed / 2;
//     MagneticMode = 0;
//     vTaskDelay(3000 / portTICK_PERIOD_MS);
//   }
// }

// void DAC1(void *pvParameters)
// {
//   while (1)
//   {
//     if (ModeRFID != 0)
//     {
//       CurrentSpeed = constrain(CurrentSpeed, 0, ConstAutoMaxSpeed);
//       Maxspeed = constrain(Maxspeed, 0, ConstAutoMaxSpeed);
//       DAC.Set(RightSpeed, LeftSpeed);
//     }
//     vTaskDelay(60 / portTICK_PERIOD_MS);
//   }
// }