# STP23 LiDAR Serial Data Decoder

- Feb 23, 2023
- This is an Arduino library for decoding the serial data of the STP-23 LiDAR distance sensor

## How to use?

Here is an example for how to use `<stp23_lidar.h>`.

```cpp
#include <Arduino.h>
#include <stp23_lidar.h>

#define HW_SERIAL_INTERFACE Serial3

STP23LiDAR lidar;

void setup()
{
    Serial.begin(115200);

    lidar.begin(HW_SERIAL_INTERFACE);
}

void loop()
{
    static unsigned long t_enter, t_duration;
    if (lidar.read() == 1)
    {
        t_duration = micros() - t_enter;
        t_enter = micros();

        for (int i = 0; i < 12; i++)
        {
            Serial.printf("%d ", lidar.get_lidar_measurement_array()[i].distance);
        }
        // Serial.print(lidar.get_lidar_distance()); // Or use this to get data
        // Serial.print(" ");
        Serial.print(t_duration);
        Serial.println();
        Serial.flush();
    }
}
```
