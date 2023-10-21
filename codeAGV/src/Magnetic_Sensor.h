
int last_poss;
// có 4 chế độ MODE0=THẲNG, MODE1=RẼ TRÁI , MODE2=RẼ PHẢI , MODE3= KHÔNG CHỌN
//#define AGV_MCP //
void Magnetic_Sensor(void *pvParameters)
{
  while (1)
  {

#ifdef AGV_MCP
    value_magnetic = adc.readChannel(0);
#else
    value_magnetic = analogRead(analog_magnetic);
#endif

    int n = sizeof(Magnetic_Board) / sizeof(Magnetic_Board[0]); // Số lượng phần tử trong mảng Magnetic_Board
    
    switch (MagneticMode)
    {
    case 0:
      digitalWrite(guide_sensor_sil1, LOW);
      digitalWrite(guide_sensor_sil2, LOW);
      break;
    case 1:
      digitalWrite(guide_sensor_sil1, LOW);
      digitalWrite(guide_sensor_sil2, HIGH);
      break;
    case 2:
      digitalWrite(guide_sensor_sil1, HIGH);
      digitalWrite(guide_sensor_sil2, LOW);
      break;
    default:
      digitalWrite(guide_sensor_sil1, HIGH);
      digitalWrite(guide_sensor_sil2, HIGH);
      break;
    }
    if (digitalRead(out_guide_sensor) == 0)
    {
      // Kiểm tra K có trong mảng arr hay không
      int K = value_magnetic;
      for (int i = 0; i < n; i++)
      {
        if (Magnetic_Board[i] >= K && K >= Magnetic_Board[i + 1])
        {
          Position = i + 1;
        }
      }
      last_poss = Position - 15;
    }
    else
    {
     last_poss = 70; // Không có line
    }
    vTaskDelay(20 / portTICK_PERIOD_MS);
  }
}
