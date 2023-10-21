
void HMI()
{
    // 0x7 RUN
    // 0X8 STOP
    // 0X5 ERROR
    // 0X4 LINE
    // 0X14 READY
    // 0X10 AUTO/MAN
    // 4X10 SPEED
    // 4X11 4X12 4X13 RF READ

    vTaskDelay(100 / portTICK_PERIOD_MS);
    if (bitRead(Modbus_HMI[0], 9) == 1) // AUTO/MAN
    {
        MODE = 2; 
        //MANUAL1 = 0;
    }
    else //(bitRead(Modbus_HMI[0], 9) == 0) // AUTO/MAN
    {
        MODE = 1;
       // MANUAL1 = 1;
    }
    Modbus_HMI[9] = CurrentSpeed; // SPEED
    if (CurrentSpeed == 0)        // RUNNING/STOP
    {
        bitWrite(Modbus_HMI[0], 7, 1); // STOP
        bitWrite(Modbus_HMI[0], 6, 0); // RUNNING
    }
    else
    {
        bitWrite(Modbus_HMI[0], 7, 0); // STOP
        bitWrite(Modbus_HMI[0], 6, 1); // RUNNING
    }
    if (Lidar_Mode == 3)
    {
        bitWrite(Modbus_HMI[0], 4, 1); // ERROR LIDAR
    }
    else
    {
        bitWrite(Modbus_HMI[0], 4, 0); // ERROR LIDAR
    }
    if (last_poss != 70)
    {
        bitWrite(Modbus_HMI[0], 3, 1); // CÓ LINE
    }
    else
    {
        bitWrite(Modbus_HMI[0], 3, 0); // KHÔNG CÓ LINE
    }
    if (bitRead(Modbus_HMI[0], 12) == 1) // Next
    {
        NEXT = 1;
    }
    else
    {
        NEXT = 0;
    }

    if (READ == "")
    {
        Modbus_HMI[10] = '0';
        Modbus_HMI[11] = '0';
        Modbus_HMI[12] = '0';
    }
    else
    {
        Modbus_HMI[10] = READ.charAt(1);
        Modbus_HMI[11] = READ.charAt(2);
        Modbus_HMI[12] = READ.charAt(3);
    }
}
