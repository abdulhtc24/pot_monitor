#include <Adafruit_MAX31865.h>

// Define pin numbers for SPI communication
#define MAX31865_MOSI 13
#define MAX31865_MISO 12
#define MAX31865_SCLK 14
#define MAX31865_CS   15  // Chip Select (CS)

// Create the MAX31865 object
Adafruit_MAX31865 max31865 = Adafruit_MAX31865(MAX31865_CS, MAX31865_MOSI,MAX31865_MISO, MAX31865_SCLK);

// RTD Parameters
#define RREF      430.0  // Reference resistance
#define RNOMINAL  100.0  // Nominal resistance for PT100 RTD

void setup() {
  Serial.begin(115200);
  // Initialize the MAX31865 sensor
  if (!max31865.begin(MAX31865_3WIRE)) {
    Serial.println("Failed to initialize MAX31865 sensor.");
    while (1);
  }
  
  Serial.println("MAX31865 sensor initialized.");
}

void loop() {
  // Read the RTD resistance value
  float resistance = max31865.readRTD();
  
  // Calculate the temperature
  float temperature = max31865.temperature(RNOMINAL, RREF);
  
  // Output the resistance and temperature
  Serial.print("Resistance: ");
  Serial.print(resistance);
  Serial.print(" ohms | Temperature: ");
  Serial.print(temperature);
  Serial.println(" C");
  
  delay(1000);  // Poll every second
}
