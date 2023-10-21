void RFID_sensor(void *pvParameters)
{
  while (1)
  {
    if (MODE == 2)
    {
      Serial2.println(SR);
      while (Serial2.available())
      {
        char receivedChar = Serial2.read();
        if (receivedChar == '5')
        {
          READ = "0000";
        }
        else if (receivedChar == '0')
        {
          if (CodeRFID == "0000") // đã thực hiện hành động phía trước theo tagrfid
          {
            READ = "";
            READ = READ + '0';
            for (int i = 0; i < count; i++)
            {
              READ += (char)Serial2.read();
            }
            CodeRFID = READ.substring(1, 4);
            if (CodeRFID!=Tag_rfid)
            {
              CodeRFID= "0000";
            }
            
          }
          // a = READ.charAt(1);
          // b = READ.charAt(2);
          // c = READ.charAt(3);
          // RFRead[0] = a;
          // RFRead[1] = b;
          // RFRead[2] = c;
          // READ = "";
          // RFLast[0] = RFRead[0];
          // RFLast[1] = RFRead[1];
          // RFLast[2] = RFRead[2];
          // CodeRFID= a+b+c;
        }
      }
    }
    vTaskDelay(150 / portTICK_PERIOD_MS);
  }
}
