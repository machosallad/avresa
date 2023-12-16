# ESP32 Train Station Display

## Description

This project uses an ESP32 powered HUB75 matrix display to show arrival and departure times for trains from Swedish train stations. The information is taken from Trafikverket through their open API and is automatically synced with the last known departure and arrival times. The display, with a matrix size of 32x128, uses a font that mimics those found in Stockholm and their subway.

The display can be configured using a web interface, allowing for adjustments to brightness, on/off settings, and color. The project is divided into various modules for increased readability and uses an ESP32-Trinity PCB to connect to the HUB75 display. The final product is mounted in a wooden box.

The project uses PlatformIO to manage the settings and configuration for the ESP32 board.

## Development status

Project is currently under early development and therefore subject for large changes.

## Features

- **Real-time Train Information**: Displays the latest arrival and departure times from Swedish train stations, automatically synced with Trafikverket's open API.
- **Configurable Display**: Adjust the brightness, on/off settings, and color of the display using a web interface.
- **Modular Design**: The project is divided into various modules for increased readability.
- **Authentic Font**: Uses a font that mimics those found in Stockholm's subway.
- **Hardware**: Uses an ESP32-Trinity PCB to connect to the HUB75 display, all mounted in a wooden box.
- **PlatformIO Integration**: The project uses PlatformIO to manage the settings and configuration for the ESP32 board.

## Installation

1. Clone the repository: `git clone https://github.com/machosallad/avresa.git`
2. Make a copy of the `config.example.h` file named `config.h` and update it with your settings.
3. Install PlatformIO: Follow the [PlatformIO installation guide](https://docs.platformio.org/en/latest/core/installation.html).
4. Open the project in PlatformIO and upload the code to your ESP32.

## Usage

After setting up the hardware and uploading the code, connect the ESP32 to power. Use the web interface to configure the display to your liking.

## License

This project is licensed under the terms of the MIT license.
