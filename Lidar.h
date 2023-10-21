void Lidar(void *pvParameters)
{
    while (1)
    {
        bool out1 = digitalRead(out1_safe_sensor); // Cảm biến lidar gần nhất
        bool out2 = digitalRead(out2_safe_sensor); // Cảm biến lidar trung bình
        bool out3 = digitalRead(out3_safe_sensor); // Cảm biến lidar xa nhất
        int i = 0;                                 // Không có vật cản mặc định

        if (Select_Mode_Lidar == 0) {
            digitalWrite(lidar_select_1, HIGH);
            digitalWrite(lidar_select_2, HIGH);
        } else if (Select_Mode_Lidar == 1) {
            digitalWrite(lidar_select_1, LOW);
            digitalWrite(lidar_select_2, HIGH);
        } else if (Select_Mode_Lidar == 2) {
            digitalWrite(lidar_select_1, HIGH);
            digitalWrite(lidar_select_2, LOW);
        } else if (Select_Mode_Lidar == 3) {
            digitalWrite(lidar_select_1, LOW);
            digitalWrite(lidar_select_2, LOW);
        }
        if (out1 == 0 && out2 == 0 && out3 == 0)
        {
            i = 0; // Không có vật cản
        }
        if (out1 == 0 && out2 == 0 && out3 == 1)
        {
            i = 1; // Có vật cản xa nhất, đi chậm lại
        }
        else if (out1 == 0 && out2 == 1 && out3 == 1)
        {
            i = 2; // Có vật cản trung bình, đi chậm hơn
        }
        else if (out1 == 1 && out2 == 1 && out3 == 1)
        {
            i = 3; // Nguy hiểm, dừng gấp
        }
         Lidar_Mode = i;
        vTaskDelay(60 / portTICK_PERIOD_MS);
    }
}