# 3D Printer Auto-Leveling with Load Cell

This project aims to implement an auto-leveling system for 3D printers using a load cell, replacing traditional methods such as the BLTouch. This shall ease offset calibrations. The system utilizes an Arduino Nano to interpret load cell readings, offering a cost-effective and highly sensitive solution for auto-leveling. By detecting minute changes in pressure when the printer's nozzle touches the bed, the system can accurately level the bed in real-time, enhancing print quality and reliability for the first layer.
Maintaining compatibility with the BLTouch protocol means we shall handle signals in a way that aligns with how a BLTouch operates, typically using a single control signal for deploy/stow commands and another for signaling the touch detection back to the printer.

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
2. Search for “HX711 Arduino Library” and install the library by Bogdan Necula
3. Clone this repository and open the project in the Arduino IDE.
4. Adjust the pin definitions in the code to match your wiring.
5. Upload the sketch to your Arduino Nano.

## Usage

Once installed, the system automatically calibrates at the start of each print or when the deploy command is sent from the printer's firmware. The load cell detects the slightest touch of the nozzle on the bed, signaling the printer to adjust according to the detected bed level.

## BL Touch interface
For a BLTouch, the control signal (deploy/stow) typically comes through a PWM (Pulse Width Modulation) signal, where different pulse widths correspond to different commands:

    Deploy Command: A short pulse (e.g., 10ms) to deploy the probe.
    Stow Command: A longer pulse (e.g., 90ms) to retract the probe.
    Test/Alarm Release: Other specific pulse widths might be used for self-test or to clear alarms.
For a BLTouch, the control signal (deploy/stow) typically comes through a PWM (Pulse Width Modulation) signal, where different pulse widths correspond to different commands:

   - Deploy Command: A short pulse (10ms) to deploy the probe.
   - Stow Command: A longer pulse (90ms) to retract the probe.
   - Test/Alarm Release: Other specific pulse widths might be used for self-test or to clear alarms.

When the probe touches the bed, the BLTouch signals this by pulling up the Z-min pin (or whichever pin it's connected to for touch detection) to HIGH for a brief moment.

## Adapting the Code for Firmware Compatibility

Given the nuances in how firmware controls a BLTouch, we can adapt the Arduino code to interpret PWM signals for deploy and stow commands based on pulse width. This requires using an interrupt to measure the length of the incoming pulse on the control pin accurately. However, accurately decoding PWM signals on an Arduino to match specific pulse lengths can be complex and might require precise timing that interrupts can offer.

Since implementing a full PWM decoder might be overly complex, we've focused on a conceptual outline that adapts the previous approach to be more aligned with how firmware might interface with a BLTouch:

    - Use an interrupt to measure pulse width on the control pin. This involves setting up an interrupt service routine (ISR) to detect rising and falling edges and measure the time between them to determine the pulse width.
    - Interpret the pulse width to determine if it's a deploy or stow command (or other commands) based on predefined thresholds that match the firmware's signaling method.
    - Act accordingly, either by starting/stopping the monitoring of the load cell or by performing other required actions like a self-test or clearing alarms, mimicking the BLTouch behavior.

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
