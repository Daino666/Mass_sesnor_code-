#include <Wire.h>              // Include Wire library for I2C
#include <LiquidCrystal_I2C.h> // Include LCD library for I2C

// LCD I2C address (commonly 0x27 or 0x3F) and dimensions (16x2)
LiquidCrystal_I2C lcd(0x3f, 16, 2);

const int ANALOG_PIN = A0;  // Analog pin connected to voltage divider
const float R = 10000.0;    // Fixed resistor value in ohms (10 kΩ)
const float VCC = 5.0;      // Supply voltage in volts
const float Gravity_acc = 9.8;

// LED pins for indicating different weight thresholds
const int LED1 = 8;   // Pin for LED1 (Low weight)
const int LED2 = 11;  // Pin for LED2 (Medium weight)
const int LED3 = 12;  // Pin for LED3 (Higher weight)
const int LED4 = 13;  // Pin for LED4 (Maximum weight)

void setup() {
  Serial.begin(9600); // Initialize Serial Monitor
  Serial.println("FSR Force Measurement");

  // Initialize the LCD
  lcd.init();
  lcd.backlight(); // Turn on the backlight
  lcd.setCursor(0, 0);
  lcd.print("Mass Measurement");
  delay(1000); // Wait to display the initial message
  lcd.clear();

  // Initialize LED pins as OUTPUT
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
}

void loop() {
  int adcValue = analogRead(ANALOG_PIN); // Read the ADC value
  float Vout = adcValue * VCC / 1023.0; // Convert ADC value to voltage

  // Calculate the FSR resistance using the formula
  float R_FSR = (R * VCC / Vout) - R;

  // Calculate force based on FSR resistance
  float force = 2272.3685 / pow(R_FSR, 1 / 0.69); // Force = 2272.3685 * (R_FSR)^(-0.69)

  // Regression coefficients
  float a2 = 95.31965234156165;
  float a1 = -624.6461673607346;
  float a0 = 1063.0032409832104;

  // Calculate mass
  float mass = ((a2 * (pow(Vout, 2))) + (Vout * a1) + a0);
  if (mass >= a0 - 300) {
    mass = 0; // Prevent negative mass or unrealistic values
  }

  // Print the results to Serial Monitor
  Serial.print("Voltage: ");
  Serial.print(Vout, 6); // Voltage with 6 decimal points
  Serial.println(" V");
  Serial.print(" | Mass: ");
  Serial.print(mass, 6); // Mass with 6 decimal points
  Serial.println(" g");

  // Display the mass and voltage on the LCD
  lcd.setCursor(0, 0);
  lcd.print("Voltage: ");
  lcd.print(Vout, 2); // Voltage with 2 decimal points
  lcd.print(" V  ");

  lcd.setCursor(0, 1); // Move to the second line
  lcd.print("Mass: ");
  lcd.print(mass, 2); // Mass with 2 decimal points
  lcd.print(" g   "); // Clear extra characters

  // Control LEDs based on weight thresholds
  if (mass < 100) {
    // Light up LED1 if the mass is less than 100 grams
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
    digitalWrite(LED4, LOW);
  } else if (mass >= 100 && mass < 200) {
    // Light up LED2 if the mass is between 100 and 200 grams
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, HIGH);
    digitalWrite(LED3, LOW);
    digitalWrite(LED4, LOW);
  } else if (mass >= 200 && mass < 300) {
    // Light up LED3 if the mass is between 200 and 300 grams
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, HIGH);
    digitalWrite(LED4, LOW);
  } else if (mass >= 300) {
    // Light up LED4 if the mass is greater than or equal to 300 grams
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
    digitalWrite(LED4, HIGH);
  }

  delay(500); // Wait for 500ms before next reading
}
