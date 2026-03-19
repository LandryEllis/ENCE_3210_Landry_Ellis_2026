/*
   Q4 - Arduino Fan Controller
   ---------------------------
   This program reads an analog temperature sensor using the ADC,
   collects 100 samples over 5 seconds, calculates the average temperature,
   and uses PWM to control fan speed based on temperature.

   Since a real fan is not available, an LED connected to a PWM pin
   is used to simulate fan speed. Higher LED brightness = higher fan speed.

   Required features:
   - Analog temperature sensor monitored with ADC
   - 100 samples over 5 seconds, then average the reading
   - PWM output used to control speed
   - PWM frequency set close to 250 Hz
   - Button 1 turns fan ON/OFF
   - Button 2 cycles through 3 sensitivity levels
   - Lower sensitivity = lower fan speed response

   Pin assignments:
   - A0 : temperature sensor analog input
   - D2 : button 1 (fan ON/OFF)
   - D3 : button 2 (sensitivity select)
   - D9 : PWM output to LED

   Assumptions:
   - Sensor output range is 0V to 5V
   - Temperature mapping is simulated from voltage
   - Internal pull-up resistors are used for the buttons
*/

#define TEMP_SENSOR_PIN A0      // Analog input pin for temperature sensor
#define FAN_PWM_PIN 9           // PWM output pin for LED/fan simulation
#define BUTTON_ONOFF_PIN 2      // Button 1: fan ON/OFF
#define BUTTON_SENSE_PIN 3      // Button 2: change sensitivity level

#define TOTAL_SAMPLES 100       // Number of ADC samples
#define SAMPLE_PERIOD_MS 50     // 100 samples x 50 ms = 5000 ms = 5 seconds

// Fan state
bool fanEnabled = true;

// Sensitivity level:
// 0 = low sensitivity
// 1 = medium sensitivity
// 2 = high sensitivity
int sensitivityLevel = 1;

// Store previous button states for edge detection
int lastOnOffButtonState = HIGH;
int lastSenseButtonState = HIGH;

// Function prototypes
float readAverageTemperatureC(void);
float convertADCToTemperatureC(int adcValue);
int calculatePWMDuty(float temperatureC, int sensitivity);
void setPWMFrequency250Hz_D9(void);

void setup()
{
  // Start serial communication for monitoring
  Serial.begin(9600);

  // Configure pins
  pinMode(FAN_PWM_PIN, OUTPUT);
  pinMode(BUTTON_ONOFF_PIN, INPUT_PULLUP);   // Active low button
  pinMode(BUTTON_SENSE_PIN, INPUT_PULLUP);   // Active low button

  // Adjust Timer1 settings so PWM on pin D9 is approximately 250 Hz
  setPWMFrequency250Hz_D9();

  Serial.println("======================================");
  Serial.println("Q4 - Arduino Fan Controller");
  Serial.println("Temp sensor : A0");
  Serial.println("Button 1    : D2 (Fan ON/OFF)");
  Serial.println("Button 2    : D3 (Sensitivity)");
  Serial.println("PWM output  : D9 (LED brightness)");
  Serial.println("======================================");
  Serial.println();
}

void loop()
{
  // ---------------- Handle Button 1: Fan ON/OFF ----------------
  int currentOnOffButtonState = digitalRead(BUTTON_ONOFF_PIN);

  // Detect button press transition: HIGH -> LOW
  if (lastOnOffButtonState == HIGH && currentOnOffButtonState == LOW)
  {
    fanEnabled = !fanEnabled;   // Toggle fan state
    delay(200);                 // Simple debounce delay
  }

  lastOnOffButtonState = currentOnOffButtonState;

  // ---------------- Handle Button 2: Sensitivity Change ----------------
  int currentSenseButtonState = digitalRead(BUTTON_SENSE_PIN);

  // Detect button press transition: HIGH -> LOW
  if (lastSenseButtonState == HIGH && currentSenseButtonState == LOW)
  {
    sensitivityLevel++;
    if (sensitivityLevel > 2)
    {
      sensitivityLevel = 0;     // Cycle back to low sensitivity
    }
    delay(200);                 // Simple debounce delay
  }

  lastSenseButtonState = currentSenseButtonState;

  // ---------------- Measure Temperature ----------------
  // Take 100 samples over 5 seconds and compute average temperature
  float averageTemperatureC = readAverageTemperatureC();

  // ---------------- Calculate PWM Duty ----------------
  int pwmValue = 0;

  if (fanEnabled)
  {
    pwmValue = calculatePWMDuty(averageTemperatureC, sensitivityLevel);
  }
  else
  {
    pwmValue = 0;   // Fan OFF means LED OFF
  }

  // Output PWM to LED on pin D9
  analogWrite(FAN_PWM_PIN, pwmValue);

  // ---------------- Print Results ----------------
  Serial.println("--------------------------------------");
  Serial.print("Average Temperature: ");
  Serial.print(averageTemperatureC, 2);
  Serial.println(" C");

  Serial.print("Fan Enabled: ");
  if (fanEnabled)
  {
    Serial.println("YES");
  }
  else
  {
    Serial.println("NO");
  }

  Serial.print("Sensitivity Level: ");
  if (sensitivityLevel == 0)
  {
    Serial.println("LOW");
  }
  else if (sensitivityLevel == 1)
  {
    Serial.println("MEDIUM");
  }
  else
  {
    Serial.println("HIGH");
  }

  Serial.print("PWM Output (0-255): ");
  Serial.println(pwmValue);

  Serial.println("--------------------------------------");
  Serial.println();
}

/*
   Function: readAverageTemperatureC
   ---------------------------------
   Reads 100 ADC samples over 5 seconds and returns
   the average temperature in degrees Celsius.
*/
float readAverageTemperatureC(void)
{
  long adcSum = 0;

  for (int i = 0; i < TOTAL_SAMPLES; i++)
  {
    int adcValue = analogRead(TEMP_SENSOR_PIN);
    adcSum += adcValue;

    // Wait 50 ms between samples
    delay(SAMPLE_PERIOD_MS);
  }

  // Compute average ADC count
  int averageADC = adcSum / TOTAL_SAMPLES;

  // Convert averaged ADC count to temperature
  return convertADCToTemperatureC(averageADC);
}

/*
   Function: convertADCToTemperatureC
   ----------------------------------
   Converts ADC reading to temperature in Celsius.

   This example assumes:
   - 0 V corresponds to 0 C
   - 5 V corresponds to 100 C

   Since Arduino Uno ADC is 10-bit:
   ADC = 0 to 1023

   Voltage = (ADC / 1023.0) * 5.0
   Temperature = (Voltage / 5.0) * 100.0
*/
float convertADCToTemperatureC(int adcValue)
{
  float voltage = (adcValue / 1023.0) * 5.0;
  float temperatureC = (voltage / 5.0) * 100.0;

  return temperatureC;
}

/*
   Function: calculatePWMDuty
   --------------------------
   Converts temperature into a PWM value (0 to 255)
   based on the selected sensitivity.

   Lower sensitivity -> lower fan speed for same temperature
   Higher sensitivity -> higher fan speed for same temperature

   Example scaling:
   - LOW sensitivity    = 40% of normal response
   - MEDIUM sensitivity = 70% of normal response
   - HIGH sensitivity   = 100% of normal response
*/
int calculatePWMDuty(float temperatureC, int sensitivity)
{
  float scaleFactor;

  if (sensitivity == 0)
  {
    scaleFactor = 0.40;   // Low sensitivity
  }
  else if (sensitivity == 1)
  {
    scaleFactor = 0.70;   // Medium sensitivity
  }
  else
  {
    scaleFactor = 1.00;   // High sensitivity
  }

  /*
     Convert temperature to a base PWM command.

     In this example:
     - 20 C and below -> fan off
     - 80 C and above -> maximum speed
     - Between 20 C and 80 C -> linear ramp
  */
  float basePWM;

  if (temperatureC <= 20.0)
  {
    basePWM = 0.0;
  }
  else if (temperatureC >= 80.0)
  {
    basePWM = 255.0;
  }
  else
  {
    basePWM = ((temperatureC - 20.0) / (80.0 - 20.0)) * 255.0;
  }

  // Apply sensitivity scaling
  int finalPWM = (int)(basePWM * scaleFactor);

  // Limit to valid PWM range
  if (finalPWM < 0)
  {
    finalPWM = 0;
  }
  if (finalPWM > 255)
  {
    finalPWM = 255;
  }

  return finalPWM;
}

/*
   Function: setPWMFrequency250Hz_D9
   ---------------------------------
   Sets Timer1 for phase-correct PWM on pin D9
   with a frequency close to 250 Hz.

   For Arduino Uno:
   PWM frequency = 16 MHz / (2 * prescaler * TOP)

   Using:
   prescaler = 64
   TOP = 500

   Frequency = 16,000,000 / (2 * 64 * 500) = 250 Hz

   Pin D9 uses Timer1 channel A.
*/
void setPWMFrequency250Hz_D9(void)
{
  // Clear Timer1 control registers
  TCCR1A = 0;
  TCCR1B = 0;

  // Set pin D9 behavior: non-inverting PWM on OC1A
  TCCR1A |= (1 << COM1A1);

  // Use phase-correct PWM with ICR1 as TOP
  TCCR1A |= (1 << WGM11);
  TCCR1B |= (1 << WGM13);

  // Set prescaler to 64
  TCCR1B |= (1 << CS11) | (1 << CS10);

  // Set TOP value for 250 Hz
  ICR1 = 500;

  // Start with duty cycle = 0
  OCR1A = 0;
}

/*
   Override analogWrite behavior for pin D9 by directly updating OCR1A.
   Since Timer1 is manually configured, write OCR1A instead of relying
   entirely on default analogWrite timing behavior.
*/
void analogWrite(uint8_t pin, int value)
{
  if (pin == 9)
  {
    // Convert 0-255 duty value into 0-ICR1 timer range
    OCR1A = map(value, 0, 255, 0, ICR1);
  }
}