# 3D Printer Auto-Leveling with Load Cell

This project aims to implement an auto-leveling system for 3D printers using a load cell, replacing traditional methods such as the BLTouch. This shall ease offset calibrations. The system utilizes an Arduino Nano to interpret load cell readings, offering a cost-effective and highly sensitive solution for auto-leveling. By detecting minute changes in pressure when the printer's nozzle touches the bed, the system can accurately level the bed in real-time, enhancing print quality and reliability for the first layer.

## Features

- **High Sensitivity**: Utilizes a load cell for precise detection of the nozzle touching the print bed.
- **Noise Filtering**: Implements software filtering to mitigate the effects of vibration and electrical noise, ensuring reliable touch detection.
- **Easy Integration**: Designed to be easily integrated with existing 3D printers, requiring minimal modifications.
- **Open Source**: Encourages community collaboration and improvement.

## Getting Started

### Prerequisites

- Arduino Nano
- HX711 Load Cell Amplifier
- A compatible load cell
- Basic soldering tools and wiring
- Access to the 3D printer's firmware for configuration

### Hardware Setup

1. Connect the load cell to the HX711 module.
2. Interface the HX711 with the Arduino Nano.
3. Mount the load cell to the printer's hotend assembly.
4. Wire the Arduino Nano to receive control signals from the printer and to send touch detection signals back.

### Software Installation

1. Install the Arduino IDE on your computer.
2. Clone this repository and open the project in the Arduino IDE.
3. Adjust the pin definitions in the code to match your wiring.
4. Upload the sketch to your Arduino Nano.

## Usage

Once installed, the system automatically calibrates at the start of each print or when the deploy command is sent from the printer's firmware. The load cell detects the slightest touch of the nozzle on the bed, signaling the printer to adjust according to the detected bed level.

## Contributing

Contributions to this project are welcome. Here are some ways you can contribute:

- Reporting bugs
- Suggesting enhancements
- Submitting pull requests for bug fixes or feature additions

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details.

## Acknowledgments

- Thanks to Gianni (G5) for the idea and the use of his wonderful lab facilities for testing and development
- Thanks to the HX711 library contributors for providing the backbone of the load cell data reading.
- Gratitude to the open-source 3D printing community for continuous inspiration and support.

## Contact

For any inquiries or contributions, please open an issue in this repository, and I'll get back to you.
