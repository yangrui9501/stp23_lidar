/**
 * @file stp23_lidar.h
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-02-23
 *
 * @copyright Copyright (c) 2023
 *
 */

#pragma once

#include <Arduino.h>

class STP23LiDAR
{
public:
    STP23LiDAR()
    {
        
    }
    struct LiDAR
    {
        uint16_t distance; // mm
        uint8_t confidence;
    };
    void begin(HardwareSerial& hw_serial);
    int read();

    /* Define Accesser */
    inline const uint16_t& get_lidar_distance() { return lidar_measurement[11].distance; }
    inline const uint8_t& get_lidar_confidence() { return lidar_measurement[11].confidence; }
    inline const LiDAR* get_lidar_measurement_array() {return lidar_measurement; }

protected:
    const uint8_t START_BYTES[2] = { 0x54, 0x2C };
    uint8_t start_bytes[2];
    uint16_t temperature;
    uint16_t begin_angle;
    LiDAR lidar_measurement[12];
    uint16_t ending_angle;
    uint16_t time_stamp;
    uint8_t crc;
    HardwareSerial* pHWSerial;
};