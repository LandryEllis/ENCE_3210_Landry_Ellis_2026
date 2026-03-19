/*
   14-bit SAR ADC Simulation on Arduino
   ------------------------------------
   This sketch reads a real analog voltage on pin A0 using the Arduino's ADC,
   converts that reading into a voltage using an external 3.0 V reference,
   and then runs a 14-bit SAR ADC simulation in software.

   Hardware connections:
   - Apply the test voltage to A0
   - Connect a stable 3.0 V reference to AREF
   - Make sure the signal source and Arduino share a common GND

   Test voltages for the assignment:
   - 0.42 V
   - 0.83 V
   - 1.65 V
   - 2.752 V

   IMPORTANT:
   - If using analogReference(EXTERNAL), do NOT apply more than 3.0 V to AREF.
   - Do NOT exceed 3.0 V on A0 when using a 3.0 V reference.
   - On Arduino Uno/Nano, analogRead() is 10-bit hardware resolution.
     The 14-bit SAR conversion below is a software simulation based on the
     measured voltage.
*/

#define BITS 14                 // Desired simulated ADC resolution
#define VREF 3.0                // External reference voltage applied to AREF
#define ANALOG_PIN A0           // Real analog input pin
#define SERIAL_BAUD 9600        // Serial monitor baud rate

/*
   Function: printBinary14
   -----------------------
   Prints a 14-bit binary representation of the ADC code.
*/
void printBinary14(uint16_t code)
{
  for (int i = BITS - 1; i >= 0; i--)
  {
    Serial.print((code >> i) & 0x01);
  }
}

/*
   Function: sar_adc_convert
   -------------------------
   Simulates a 14-bit SAR ADC in software.

   vin: measured analog voltage in volts

   returns: 14-bit digital code
*/
uint16_t sar_adc_convert(double vin)
{
  uint16_t code = 0;        // Final 14-bit output code
  uint16_t trial_code = 0;  // Temporary code used to test each bit
  double dac_voltage = 0.0; // Trial DAC voltage for comparison

  // Keep vin within the valid input range of the ADC
  if (vin < 0.0)
  {
    vin = 0.0;
  }
  if (vin > VREF)
  {
    vin = VREF;
  }

  /*
     SAR process:
     Start with the MSB and move toward the LSB.
     For each bit:
     1. Set the current bit to 1 temporarily
     2. Convert that trial code to an equivalent DAC voltage
     3. Compare Vin to the DAC voltage
     4. Keep the bit if Vin >= DAC voltage
  */
  for (int bit = BITS - 1; bit >= 0; bit--)
  {
    // Temporarily set the current bit
    trial_code = code | (1U << bit);

    // Convert the trial code to its analog equivalent
    dac_voltage = ((double)trial_code / (1 << BITS)) * VREF;

    // Comparator decision
    if (vin >= dac_voltage)
    {
      code = trial_code;
    }
  }

  return code;
}

void setup()
{
  // Start serial communication so results can be viewed in the Serial Monitor
  Serial.begin(SERIAL_BAUD);

  // Use an external reference connected to the AREF pin
  // This should be a stable 3.0 V source
  analogReference(EXTERNAL);

  // Small delay for startup stability
  delay(1000);

  Serial.println("==============================================");
  Serial.println("14-bit SAR ADC Simulation on Arduino");
  Serial.println("Real analog input pin : A0");
  Serial.println("Reference pin         : AREF = 3.0 V");
  Serial.println("Ground reference      : GND must be shared");
  Serial.println("==============================================");
  Serial.println();
}

void loop()
{
  // Read the real analog voltage on A0 using Arduino's built-in ADC
  // On Uno/Nano, this is a 10-bit value from 0 to 1023
  int raw_adc = analogRead(ANALOG_PIN);

  // Convert the raw ADC count into a measured voltage
  // Since analogRead() returns 0..1023, divide by 1023.0
  double measured_voltage = ((double)raw_adc / 1023.0) * VREF;

  // Run the 14-bit SAR simulation using the measured voltage
  uint16_t digital_code = sar_adc_convert(measured_voltage);

  // Reconstruct the quantized voltage from the 14-bit output code
  double quantized_voltage = ((double)digital_code / (1 << BITS)) * VREF;

  // Compute the 14-bit LSB size
  double lsb_size = VREF / (1 << BITS);

  // Compute quantization error between measured voltage and 14-bit quantized value
  double quant_error = measured_voltage - quantized_voltage;

  // Print all results to the Serial Monitor
  Serial.println("--------------- New Conversion ---------------");
  Serial.print("Analog input pin       : A0");
  Serial.println();

  Serial.print("Raw Arduino ADC count  : ");
  Serial.println(raw_adc);

  Serial.print("Measured voltage       : ");
  Serial.print(measured_voltage, 6);
  Serial.println(" V");

  Serial.print("Simulated 14-bit code  : ");
  Serial.println(digital_code);

  Serial.print("14-bit binary output   : ");
  printBinary14(digital_code);
  Serial.println();

  Serial.print("Quantized voltage      : ");
  Serial.print(quantized_voltage, 6);
  Serial.println(" V");

  Serial.print("14-bit LSB size        : ");
  Serial.print(lsb_size, 9);
  Serial.println(" V");

  Serial.print("Quantization error     : ");
  Serial.print(quant_error, 9);
  Serial.println(" V");

  Serial.println("----------------------------------------------");
  Serial.println();

  // Take one reading every 2 seconds so the output is easy to observe
  delay(2000);
}