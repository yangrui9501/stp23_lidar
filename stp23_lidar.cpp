#include "stp23_lidar.h"

void STP23LiDAR::begin(HardwareSerial& hw_serial)
{
    pHWSerial = &hw_serial;
    pHWSerial->begin(921600);
}

int STP23LiDAR::read()
{
    while (pHWSerial->available() >= 47)
    {
        start_bytes[0] = (uint8_t)pHWSerial->read();
        if (start_bytes[0] == START_BYTES[0])
        {
            start_bytes[1] = (uint8_t)pHWSerial->read();

            if (start_bytes[1] == START_BYTES[1])
            {
                pHWSerial->readBytes((uint8_t*)&temperature, 2U);
                pHWSerial->readBytes((uint8_t*)&begin_angle, 2U);
                for (int i = 0; i < 12; i++)
                {
                    pHWSerial->readBytes((uint8_t*)&lidar_measurement[i].distance, 2U);
                    pHWSerial->readBytes((uint8_t*)&lidar_measurement[i].confidence, 1U);
                }
                pHWSerial->readBytes((uint8_t*)&ending_angle, 2U);
                pHWSerial->readBytes((uint8_t*)&time_stamp, 2U);
                pHWSerial->readBytes((uint8_t*)&crc, 1U);

                return 1;
            }
        }
    }
    return 0;
}