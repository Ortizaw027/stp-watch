## ESP32 Smartwatch Firmware

This project is a full-featured, open-source smartwatch firmware built from the ground up using the ESP-IDF framework. It runs on the ESP32-S3-Touch-LCD-1.28 development board and demonstrates real-time task scheduling, graphical UI rendering with LVGL, I2C peripheral communication, and low-power design strategies.

The firmware includes a digital clock display, compass functionality using the onboard IMU, a stopwatch, and swipe-based navigation between pages. All peripherals are configured and managed without relying on Arduino libraries, showcasing embedded C development and FreeRTOS fundamentals in a real-world wearable application.
## Features

- **Real-Time Clock**: Displays the current time using the internal RTC or synchronized source.
- **Graphical UI**: Built using LVGL with support for smooth screen transitions and swiping between pages.
- **Compass**: Reads and visualizes direction using the onboard IMU (6-axis sensor).
- **Stopwatch**: Start, pause, and reset functionality with visual feedback.
- **Touch Input**: Navigate the UI using the capacitive touch screen with swipe gesture recognition.
- **FreeRTOS Integration**: All tasks are handled through a real-time operating system for concurrency and responsiveness.
- **Low Power Modes**: Screen timeout and sleep logic implemented to preserve battery life.
- **Modular Codebase**: Peripherals and UI components are modularized for easier extension and maintenance.
