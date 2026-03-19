/*
   Q2 - Arduino Solar Charge Controller Logic
   ------------------------------------------
   This program monitors:
   - Solar panel voltage on A0
   - Battery voltage on A1

   System rules:
   1. If solar voltage > 2.5 V, the microcontroller is powered by solar.
   2. If solar voltage <= 2.5 V, the microcontroller is powered by battery.
   3. If battery voltage < solar voltage, connect battery to solar for charging.
   4. Since no real controllable switching element is available, the OLED display
      is used to show the power-routing decision.

   Pin assignments:
   - A0 : Solar panel voltage sense
   - A1 : Battery voltage sense
   - SDA/SCL : OLED display (I2C)

   IMPORTANT:
   If the solar panel or battery voltage can exceed the Arduino analog input limit,
   use a voltage divider before connecting to A0 or A1.
*/

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// ---------------- OLED Configuration ----------------
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// ---------------- Pin Definitions ----------------
#define SOLAR_PIN A0          // Analog input for solar panel voltage
#define BATTERY_PIN A1        // Analog input for battery voltage

// ---------------- System Constants ----------------
#define ADC_REF_VOLTAGE 5.0   // Arduino ADC reference voltage (Uno default = 5V)
#define ADC_MAX_COUNT 1023.0  // 10-bit ADC max value
#define SOLAR_THRESHOLD 2.5   // Threshold from assignment

// ---------------- Function Prototypes ----------------
float readVoltage(int pin);
void updateOLED(float solarV, float batteryV, const char* mcuSource, const char* chargePath);

void setup()
{
  // Start serial monitor for debugging and verification
  Serial.begin(9600);

  // Initialize OLED display
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS))
  {
    Serial.println("OLED initialization failed.");
    while (1); // Stop here if display cannot be initialized
  }

  // Clear the display at startup
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  // Startup message
  display.setCursor(0, 0);
  display.println("Solar Controller");
  display.println("Initializing...");
  display.display();

  delay(1500);
}

void loop()
{
  // Read solar panel voltage from A0
  float solarVoltage = readVoltage(SOLAR_PIN);

  // Read battery voltage from A1
  float batteryVoltage = readVoltage(BATTERY_PIN);

  // Variables to store routing decisions
  const char* mcuPowerSource;
  const char* chargingPath;

  /*
     Rule 1 and Rule 2:
     If solar panel voltage is greater than 2.5 V,
     the microcontroller is powered from solar.
     Otherwise, the battery powers the microcontroller.
  */
  if (solarVoltage > SOLAR_THRESHOLD)
  {
    mcuPowerSource = "SOLAR -> MCU";
  }
  else
  {
    mcuPowerSource = "BATTERY -> MCU";
  }

  /*
     Rule 3:
     If battery voltage drops below solar voltage,
     connect the battery to the solar panel for charging.
     Since we do not have a real switch IC, this is only indicated on the OLED.
  */
  if (batteryVoltage < solarVoltage)
  {
    chargingPath = "SOLAR -> BAT";
  }
  else
  {
    chargingPath = "NO CHARGE";
  }

  // Print readings and decisions to Serial Monitor
  Serial.println("==================================");
  Serial.print("Solar Voltage   : ");
  Serial.print(solarVoltage, 3);
  Serial.println(" V");

  Serial.print("Battery Voltage : ");
  Serial.print(batteryVoltage, 3);
  Serial.println(" V");

  Serial.print("MCU Power Path  : ");
  Serial.println(mcuPowerSource);

  Serial.print("Charge Path     : ");
  Serial.println(chargingPath);

  // Update OLED display with latest values and routing decisions
  updateOLED(solarVoltage, batteryVoltage, mcuPowerSource, chargingPath);

  // Delay to make the display readable
  delay(1000);
}

/*
   Function: readVoltage
   ---------------------
   Reads an analog pin and converts the ADC count to voltage.

   pin: analog input pin

   returns: measured voltage in volts
*/
float readVoltage(int pin)
{
  int rawADC = analogRead(pin);

  // Convert raw ADC count to voltage
  float voltage = (rawADC * ADC_REF_VOLTAGE) / ADC_MAX_COUNT;

  return voltage;
}

/*
   Function: updateOLED
   --------------------
   Displays the measured voltages and routing decisions on the OLED.

   solarV: measured solar voltage
   batteryV: measured battery voltage
   mcuSource: string describing MCU power source
   chargePath: string describing charging path
*/
void updateOLED(float solarV, float batteryV, const char* mcuSource, const char* chargePath)
{
  display.clearDisplay();

  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("Solar Charge Ctrl");

  display.print("Solar: ");
  display.print(solarV, 2);
  display.println(" V");

  display.print("Battery: ");
  display.print(batteryV, 2);
  display.println(" V");

  display.println();

  display.print("MCU: ");
  display.println(mcuSource);

  display.print("Charge: ");
  display.println(chargePath);

  display.display();
}