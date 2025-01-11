//this is the first version of the code used in making the Mass sensor
//although it was discarded later


#include <LiquidCrystal.h>

// LCD setup: RS, EN, D4, D5, D6, D7
LiquidCrystal lcd(5, 4, 3, 2, A4, A5);

// Constants
const int SENSOR_PIN = A0; // Force sensor pin
const float Vcc = 5.0;     // Supply voltage
const float R_DIV = 1000.0; // Voltage divider resistor value (1k ohms)
const int maxCount = 30;   // Number of samples for calculations

// Variables
float inputs[maxCount] = {0};
int count = 0;
float mean, variance, standardDeviation, averagePrecision;
bool readyToCalculate = false;

// Function prototypes
void greeting();
float getInput();
void calculateMean();
void calculateVariance();
void calculatePrecision();
void printResults();
void my_print();
void displayMass();

void setup() {
  // Pin modes and initializations
  pinMode(SENSOR_PIN, INPUT);
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.clear();

  // Display greeting
  greeting();
}

void loop() {

  // Collect input data
  float input = getInput();
  inputs[count] = input;
  count++;
  
  if(!readyToCalculate){
  	displayMass(input);
  	delay(1000);
  }

  // If enough data collected, calculate and display results
  if (count == maxCount) {
    count = 0;
    readyToCalculate = true;
  }

  if (readyToCalculate) {
    calculateMean();
    calculateVariance();
    calculatePrecision();
    standardDeviation = sqrt(variance);

    // Display results
    printResults();
    lcd.clear();
    delay(4000); // Wait before next measurement

    readyToCalculate = false; // Reset flag
  }
}

void my_print(bool b, bool b2, int cur, int line, char* arr)
{
    if (b)
    {
        lcd.clear();
    }
    lcd.setCursor(cur, line);
    int len = strlen(arr);
    for (int i = 0; i < len; i++)
    {
      lcd.print(arr[i]);
      if(b2) delay(100);
    }
}

// Function to display a welcome message
void greeting()
{
    lcd.clear();
    delay(100);
    lcd.clear();
    my_print(true, true, 2, 0, "Measurements");
    my_print(false, true, 4, 1, "Project.");
    delay(2000);

    my_print(true, true, 4, 0, "Welcome!");
    delay(2000);
}

// Function to read input from force sensor
float getInput() {
  int sensorValue = analogRead(SENSOR_PIN);
  float voltage = sensorValue * (Vcc / 1023.0);

  // Avoid divide-by-zero errors
  if (voltage <= 0) {
    return 0;
  }

  // Calculate resistance and force
  float Rfsr = R_DIV * (Vcc / voltage - 1.0);
  if (Rfsr <= 0) {
    return 0; // Invalid resistance
  }

  float force = (232722.021 / pow(Rfsr, 1.419));
  return force / 9.8 * 1000; // Convert to mass (gm)
}

// Function to display the mass on the LCD
void displayMass(float mass) {
  lcd.clear();
  lcd.setCursor(0, 0);

  if (mass < 1000) {
    lcd.print("Mass: ");
    lcd.print(mass, 2); // Display with two decimal places
    lcd.print(" gm");
  } else {
    lcd.print("Mass: ");
    lcd.print(mass / 1000, 2); // Convert to kilograms
    lcd.print(" kg");
  }
}


// Function to calculate mean
void calculateMean() {
  float sum = 0;
  for (int i = 0; i < maxCount; i++) {
    sum += inputs[i];
  }
  mean = sum / maxCount;
}

// Function to calculate variance
void calculateVariance() {
  float sum = 0;
  for (int i = 0; i < maxCount; i++) {
    float deviation = inputs[i] - mean;
    sum += deviation * deviation;
  }
  variance = sum / maxCount;
}

// Function to calculate average precision
void calculatePrecision() {
  float sum = 0;
  for (int i = 0; i < maxCount; i++) {
    sum += (1 - abs((inputs[i] - mean) / mean));
  }
  averagePrecision = sum / maxCount;
}

// Function to display results on LCD
void printResults() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("M=");
  lcd.print(mean, 2);
  lcd.setCursor(8, 0);
  lcd.print("P=");
  lcd.print(averagePrecision, 2);
  
  lcd.setCursor(0, 1);
  lcd.print("S=");
  lcd.print(standardDeviation, 2);
  lcd.setCursor(8, 1);
  lcd.print("V=");
  lcd.print(variance, 2);
}
