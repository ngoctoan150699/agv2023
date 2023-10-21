
String receivedData = "";
String receivedData_Man = "";
bool newDataAvailable = false;
bool newDataAvailable_Man = false;

void splitString(String input, String *part1, String *part2, String *part3, String *part4)
{
    int n = input.length();
    int separatorIndex1 = -1;
    // Tìm vị trí của > đầu tiên
    for (int i = 0; i < n; i++)
    {
        if (input.charAt(i) == '>')
        {
            separatorIndex1 = i;
            break;
        }
    }
    // Nếu tìm thấy khoảng trắng đầu tiên
    if (separatorIndex1 != -1)
    {
        // Gán giá trị cho part1
        *part1 = input.substring(0, separatorIndex1);
        int separatorIndex2 = -1;
        // Tìm vị trí của > thứ hai sau > đầu tiên
        for (int i = separatorIndex1 + 1; i < n; i++)
        {
            if (input.charAt(i) == '>')
            {
                separatorIndex2 = i;
                break;
            }
        }
        // Nếu tìm thấy > thứ hai
        if (separatorIndex2 != -1)
        {
            // Gán giá trị cho part2
            *part2 = input.substring(separatorIndex1 + 1, separatorIndex2);
            int separatorIndex3 = -1;
            // Tìm vị trí của > thứ ba sau khoảng trắng thứ hai
            for (int i = separatorIndex2 + 1; i < n; i++)
            {
                if (input.charAt(i) == '>')
                {
                    separatorIndex3 = i;
                    break;
                }
            }
            // Nếu tìm thấy > thứ ba
            if (separatorIndex3 != -1)
            {
                // Gán giá trị cho part2 và part3
                *part3 = input.substring(separatorIndex2 + 1, separatorIndex3);
                *part4 = input.substring(separatorIndex3 + 1);
            }
            // Nếu không tìm thấy > thứ ba
            else
            {
                // Gán giá trị cho part2
                *part3 = input.substring(separatorIndex2 + 1);
                *part4 = "";
            }
        }
        // Nếu không tìm thấy > thứ hai
        else
        {
            // Gán giá trị mặc định cho part1, part2 và part3
            *part2 = input.substring(separatorIndex1 + 1);
            *part3 = "";
            *part4 = "";
        }
    }
    else
    {
        // Gán giá trị mặc định cho part1, part2 và part3
        *part1 = input;
        *part2 = "";
        *part3 = "";
        *part4 = "";
    }
}
void splitString_man(String input, String *part1, String *part2)
{
    int separatorIndex_man = input.indexOf('>');
    if (separatorIndex_man != -1)
    {
        *part1 = input.substring(0, separatorIndex_man);
        *part2 = input.substring(separatorIndex_man + 1);
    }
    else
    {
        *part1 = input;
        *part2 = "";
    }
}
void receiveEvent(int byteCount)
{
    if (MODE == 2)
    {
        if (Wire.available() > 0)
        {
            while (Wire.available())
            {
                char c = Wire.read();
                receivedData += c;
            }
            newDataAvailable_Man = false;
            newDataAvailable = true; // Đánh dấu rằng có dữ liệu mới
        }
    }
    else if (MODE == 1)
    {
        if (Wire.available() > 0)
        {
            while (Wire.available())
            {
                char c = Wire.read();
                receivedData_Man += c;
            }
            newDataAvailable = false;
            newDataAvailable_Man = true; // Đánh dấu rằng có dữ liệu mới từ manual
        }
    }
}
void sendData()
{
    if (done_action == 0)
    {
        Str_ATtoESP32 = (String)MODE + ">" + "0";
        for (int i = 0; i < static_cast<int>(Str_ATtoESP32.length()); i++)
        {
            Wire.write(Str_ATtoESP32[i]);
        }
        Str_ATtoESP32 = "";
        //vTaskDelay(pdMS_TO_TICKS(50));
    }
    else
    {
        done_action = 0;
        Str_ATtoESP32 = (String)MODE + ">" + "1";
        for (int i = 0; i < static_cast<int>(Str_ATtoESP32.length()); i++)
        {
            Wire.write(Str_ATtoESP32[i]);
        }
        Str_ATtoESP32 = "";
        //vTaskDelay(pdMS_TO_TICKS(50));
    }
}
void processReceivedData(void *pvParameters)
{
    (void)pvParameters;
    while (1)
    {
        // Kiểm tra xem có dữ liệu mới không
        if (newDataAvailable)
        {
            String id, part1, part2, step_esp;
            splitString(receivedData, &id, &part1, &part2, &step_esp);
            Serial.println("Received data in task: ");
            int ID_ = atoi(id.c_str());
            Tag_rfid = part1;
            int Action_ = atoi(part2.c_str());
            int Step_ = atoi(step_esp.c_str());
            ID_AGV = ID_;
            Action = Action_;
            Step = Step_;

            // done_action = 0;
            receivedData = "";        // Đặt lại biến receivedData sau khi xử lý xong
            newDataAvailable = false; // Đặt lại biến cờ
        }
        if (newDataAvailable_Man)
        {
            String part1_man, part2_man;
            splitString_man(receivedData_Man, &part1_man, &part2_man);
           // Serial.println("Received data in task: ");
            int angle_manual = atoi(part1_man.c_str());
            int speed_manual = atoi(part2_man.c_str());
            speed_man = speed_manual;
            angle_man = angle_manual;
            // Serial.println("receivedData_Man:");
            // Serial.println(receivedData_Man);
            // Serial.println("speed_man:");
            // Serial.println(speed_man);
            // Serial.println("angle_man:");
            // Serial.println(angle_man);
            receivedData_Man = "";        // Đặt lại biến receivedData sau khi xử lý xong
            newDataAvailable_Man = false; // Đặt lại biến cờ
        }
        vTaskDelay(pdMS_TO_TICKS(50)); // Ngủ 50ms trước khi kiểm tra lại dữ liệu
    }
}