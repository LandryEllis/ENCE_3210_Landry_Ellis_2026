/*
   Q3 - Improved Solar Charge Controller for Arduino
   -------------------------------------------------
   This version fixes the major issue from Q2 by allowing the battery to
   continue charging until it reaches a defined full-charge voltage before
   switching the solar panel back to powering the microcontroller.

   Pin assignments:
   - A0 : Solar panel voltage sense
   - A1 : Battery voltage sense
   - SDA/SCL : OLED display (I2C)

   Logic:
   1. If battery is not full and solar voltage is high enough, enter CHARGING mode.
   2. While charging, keep solar connected to battery until battery reaches full voltage.
   3. After battery is full:
      - If solar > 2.5 V, solar powers MCU
      - If solar <= 2.5 V, battery powers MCU
   4. OLED is used to indicate routing decisions since no real switch IC is available.

   IMPORTANT:
   - If input voltages exceed Arduino ADC range, use voltage dividers.
   - This program simulates routing decisions only.
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
#define SOLAR_PIN A0
#define BATTERY_PIN A1

// ---------------- ADC / Voltage Settings ----------------
#define ADC_REF_VOLTAGE 5.0
#define ADC_MAX_COUNT 1023.0

// ---------------- Control Thresholds ----------------
#define SOLAR_THRESHOLD 2.5       // Solar must exceed this to be considered available
#define BATTERY_FULL_VOLTAGE 4.20 // Example full-charge battery voltage

// ---------------- State Variable ----------------
bool chargingMode = false;        // True when battery is actively being charged

// ---------------- Function Prototypes ----------------
float readVoltage(int pin);
void updateOLED(float solarV, float batteryV, const char* systemMode, const char* mcuPath, const char* chargePath);

void setup()
{
  Serial.begin(9600);

  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS))
  {
    Serial.println("OLED initialization failed.");
    while (1);
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Solar Controller");
  display.println("Q3 Improved Logic");
  display.display();

  delay(1500);
}

void loop()
{
  // Read current voltages
  float solarVoltage = readVoltage(SOLAR_PIN);
  float batteryVoltage = readVoltage(BATTERY_PIN);

  // Text labels for display and serial output
  const char* systemMode;
  const char* mcuPowerPath;
  const char* chargePath;

  /*
     Improved charging logic:
     If solar is available and battery is not full, start or remain in charging mode.
     This prevents the system from switching solar back to MCU too early.
  */
  if ((solarVoltage > SOLAR_THRESHOLD) && (batteryVoltage < BATTERY_FULL_VOLTAGE))
  {
    chargingMode = true;
  }

  /*
     Stay in charging mode until battery reaches full voltage.
     Once full, exit charging mode.
  */
  if (chargingMode && (batteryVoltage >= BATTERY_FULL_VOLTAGE))
  {
    chargingMode = false;
  }

  /*
     Decide routing based on state:
     - In charging mode: solar charges battery, MCU is assumed powered from battery
       so solar can remain dedicated to charging.
     - Outside charging mode: follow normal source selection.
  */
  if (chargingMode)
  {
    systemMode = "CHARGING";
    mcuPowerPath = "BATTERY -> MCU";
    chargePath = "SOLAR -> BAT";
  }
  else
  {
    systemMode = "NORMAL";

    if (solarVoltage > SOLAR_THRESHOLD)
    {
      mcuPowerPath = "SOLAR -> MCU";
    }
    else
    {
      mcuPowerPath = "BATTERY -> MCU";
    }

    chargePath = "NO CHARGE";
  }

  // Print results to Serial Monitor
  Serial.println("==================================");
  Serial.print("Solar Voltage   : ");
  Serial.print(solarVoltage, 3);
  Serial.println(" V");

  Serial.print("Battery Voltage : ");
  Serial.print(batteryVoltage, 3);
  Serial.println(" V");

  Serial.print("System Mode     : ");
  Serial.println(systemMode);

  Serial.print("MCU Power Path  : ");
  Serial.println(mcuPowerPath);

  Serial.print("Charge Path     : ");
  Serial.println(chargePath);

  // Update OLED display
  updateOLED(solarVoltage, batteryVoltage, systemMode, mcuPowerPath, chargePath);

  delay(1000);
}

/*
   Function: readVoltage
   ---------------------
   Reads an analog input pin and converts the ADC value to voltage.
*/
float readVoltage(int pin)
{
  int rawADC = analogRead(pin);
  float voltage = (rawADC * ADC_REF_VOLTAGE) / ADC_MAX_COUNT;
  return voltage;
}

/*
   Function: updateOLED
   --------------------
   Displays measured voltages and routing status.
*/
void updateOLED(float solarV, float batteryV, const char* systemMode, const char* mcuPath, const char* chargePath)
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

  display.print("Mode: ");
  display.println(systemMode);

  display.print("MCU: ");
  display.println(mcuPath);

  display.print("Charge: ");
  display.println(chargePath);

  display.display();
}