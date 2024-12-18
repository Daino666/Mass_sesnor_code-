# Mass Detection Circuit with Arduino and Machine Learning

## Overview
This repository contains the code and resources for a mass detection circuit built with the following components:

- **Breadboard**
- **LEDs**: Indicate whether the mass is too large or within range.
- **16x2 LCD Display with I2C**: Displays the measured mass.
- **Arduino Uno**: The main microcontroller for the circuit.
- **FSR Sensor**: Measures the force exerted by the object.
- **Resistors**

**Due to the poor accuracy of the FSR sensor in mass measurement, we trained a **Machine Learning regression model** to predict the mass from the voltage output. The model accounts for variations caused by the placement of the object on different corners of the FSR sensor.**

## Features
1. **LED Indicator**: Lights up to signal when the mass exceeds the maximum safe limit.
2. **LCD Display**: Shows the measured or corrected mass in real time.
3. **Machine Learning Model**:
   - Trains on true data to correct FSR sensor inaccuracies.
   - Accounts for object placement on different corners of the sensor.

## Circuit Components
| Component       | Quantity | Purpose                          |
|-----------------|----------|----------------------------------|
| Breadboard      | 1        | Circuit assembly                |
| LEDs            | Multiple | Mass range indication           |
| LCD 16x2 (I2C)  | 1        | Mass display                    |
| Arduino Uno     | 1        | Microcontroller                 |
| FSR Sensor      | 1        | Mass measurement                |
| Resistors       | Multiple | Voltage division and current control |

## Setup Instructions
1. **Hardware Setup**:
   - Assemble the circuit as per the design diagram.
   - Connect the FSR sensor to the analog pin of the Arduino Uno.
   - Attach the LCD display via I2C interface.
   - Wire the LEDs to digital pins for output control.
2. **Software Setup**:
   - Upload the Arduino code.
   - Train the machine learning model with the data exitsing in the repo or by makin your own data and putting it in the CSV.
   - Deploy the model for real-time corrections in mass measurement.

## Visualizations
- **Plots of the Trained Model**:
  View performance metrics and accuracy plots in the `plots/` folder.
- **Circuit Diagram**:
  Refer to the schematic in `circuit_design/` for building the circuit.

## How It Works
1. The FSR sensor measures the force applied by the object and outputs a voltage.
2. The Arduino reads the voltage and:
   - Activates LEDs based on predefined mass thresholds.
   - Displays the mass on the LCD using corrected values from the ML model.
3. The machine learning model improves accuracy by considering:
   - Voltage readings.
   - Corner-specific force variations.

## Future Improvements
- Enhance the dataset to include more mass and position combinations.
- Test alternative sensors for better baseline accuracy.
- Implement real-time model updates on new data.

