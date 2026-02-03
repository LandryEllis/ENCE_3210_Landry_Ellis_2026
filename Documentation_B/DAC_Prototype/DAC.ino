const int analogPin = A0;
const float referenceVoltage = 5.0;  // Change to 3.3 if needed


int LSB = 13;
int SB2 = 12;
int SB3 = 11;
int MSB = 10;
void setup() {
  Serial.begin(9600);
  pinMode(LSB, OUTPUT);
pinMode(SB2,OUTPUT);
pinMode(SB3,OUTPUT);
pinMode(MSB,OUTPUT);
}

void loop() {

  digitalWrite(LSB, LOW);
  digitalWrite(SB2, LOW);
  digitalWrite(SB3, LOW);
  digitalWrite(MSB, LOW);
  
  delay (1000);

  int rawValue = analogRead(analogPin);
  float voltage = rawValue * (referenceVoltage / 1023.0);
float a = ((abs(5-voltage)-0.89)*5); 

  Serial.print("Raw ADC: ");
  Serial.print(rawValue);
  Serial.print(" | Voltage: ");
  Serial.print(voltage, 3); // 3 decimal places
Serial.print(" V ");
Serial.println(a); 

  digitalWrite(LSB, HIGH);
  digitalWrite(SB2, LOW);
  digitalWrite(SB3, LOW);
  digitalWrite(MSB, LOW);
  
  delay (1000);
  
  rawValue = analogRead(analogPin);
  voltage = rawValue * (referenceVoltage / 1023.0);
a = ((abs(5-voltage)-0.89)*5); 

  Serial.print("Raw ADC: ");
  Serial.print(rawValue);
  Serial.print(" | Voltage: ");
  Serial.print(voltage, 3); // 3 decimal places
Serial.print(" V ");
Serial.println(a); 

  digitalWrite(LSB, LOW);
  digitalWrite(SB2, HIGH);
  digitalWrite(SB3, LOW);
  digitalWrite(MSB, LOW);
  
  delay (1000);

  rawValue = analogRead(analogPin);
  voltage = rawValue * (referenceVoltage / 1023.0);
a = ((abs(5-voltage)-0.89)*5); 

  Serial.print("Raw ADC: ");
  Serial.print(rawValue);
  Serial.print(" | Voltage: ");
  Serial.print(voltage, 3); // 3 decimal places
Serial.print(" V ");
Serial.println(a); 

  digitalWrite(LSB, HIGH);
  digitalWrite(SB2, HIGH);
  digitalWrite(SB3, LOW);
  digitalWrite(MSB, LOW);
  
  delay (1000);
  
   rawValue = analogRead(analogPin);
   voltage = rawValue * (referenceVoltage / 1023.0);
a = ((abs(5-voltage)-0.89)*5); 

  Serial.print("Raw ADC: ");
  Serial.print(rawValue);
  Serial.print(" | Voltage: ");
  Serial.print(voltage, 3); // 3 decimal places
Serial.print(" V ");
Serial.println(a); 

  digitalWrite(LSB, LOW);
  digitalWrite(SB2, LOW);
  digitalWrite(SB3, HIGH);
  digitalWrite(MSB, LOW);
  
  delay (1000);
  
   rawValue = analogRead(analogPin);
   voltage = rawValue * (referenceVoltage / 1023.0);
a = ((abs(5-voltage)-0.89)*5); 

  Serial.print("Raw ADC: ");
  Serial.print(rawValue);
  Serial.print(" | Voltage: ");
  Serial.print(voltage, 3); // 3 decimal places
Serial.print(" V ");
Serial.println(a); 

  digitalWrite(LSB, HIGH);
  digitalWrite(SB2, LOW);
  digitalWrite(SB3, HIGH);
  digitalWrite(MSB, LOW);
  
  delay (1000);

   rawValue = analogRead(analogPin);
   voltage = rawValue * (referenceVoltage / 1023.0);
a = ((abs(5-voltage)-0.89)*5); 

  Serial.print("Raw ADC: ");
  Serial.print(rawValue);
  Serial.print(" | Voltage: ");
  Serial.print(voltage, 3); // 3 decimal places
Serial.print(" V ");
Serial.println(a); 

  digitalWrite(LSB, LOW);
  digitalWrite(SB2, HIGH);
  digitalWrite(SB3, HIGH);
  digitalWrite(MSB, LOW);
  
  delay (1000);

   rawValue = analogRead(analogPin);
   voltage = rawValue * (referenceVoltage / 1023.0);
a = ((abs(5-voltage)-0.89)*5); 

  Serial.print("Raw ADC: ");
  Serial.print(rawValue);
  Serial.print(" | Voltage: ");
  Serial.print(voltage, 3); // 3 decimal places
Serial.print(" V ");
Serial.println(a); 

  digitalWrite(LSB, HIGH);
  digitalWrite(SB2, HIGH);
  digitalWrite(SB3, HIGH);
  digitalWrite(MSB, LOW);
  
  delay (1000);

   rawValue = analogRead(analogPin);
   voltage = rawValue * (referenceVoltage / 1023.0);
a = ((abs(5-voltage)-0.89)*5); 

  Serial.print("Raw ADC: ");
  Serial.print(rawValue);
  Serial.print(" | Voltage: ");
  Serial.print(voltage, 3); // 3 decimal places
Serial.print(" V ");
Serial.println(a); 

  digitalWrite(LSB, LOW);
  digitalWrite(SB2, LOW);
  digitalWrite(SB3, LOW);
  digitalWrite(MSB, HIGH);
  
  delay (1000);

  rawValue = analogRead(analogPin);
  voltage = rawValue * (referenceVoltage / 1023.0);
a = ((abs(5-voltage)-0.89)*5); 

  Serial.print("Raw ADC: ");
  Serial.print(rawValue);
  Serial.print(" | Voltage: ");
  Serial.print(voltage, 3); // 3 decimal places
Serial.print(" V ");
Serial.println(a); 

  digitalWrite(LSB, HIGH);
  digitalWrite(SB2, LOW);
  digitalWrite(SB3, LOW);
  digitalWrite(MSB, HIGH);
  
  delay (1000);
  
  rawValue = analogRead(analogPin);
  voltage = rawValue * (referenceVoltage / 1023.0);
a = ((abs(5-voltage)-0.89)*5); 

  Serial.print("Raw ADC: ");
  Serial.print(rawValue);
  Serial.print(" | Voltage: ");
  Serial.print(voltage, 3); // 3 decimal places
Serial.print(" V ");
Serial.println(a); 

  digitalWrite(LSB, LOW);
  digitalWrite(SB2, HIGH);
  digitalWrite(SB3, LOW);
  digitalWrite(MSB, HIGH);
  
  delay (1000);

  rawValue = analogRead(analogPin);
  voltage = rawValue * (referenceVoltage / 1023.0);
a = ((abs(5-voltage)-0.89)*5); 

  Serial.print("Raw ADC: ");
  Serial.print(rawValue);
  Serial.print(" | Voltage: ");
  Serial.print(voltage, 3); // 3 decimal places
Serial.print(" V ");
Serial.println(a); 

  digitalWrite(LSB, HIGH);
  digitalWrite(SB2, HIGH);
  digitalWrite(SB3, LOW);
  digitalWrite(MSB, HIGH);
  
  delay (1000);
  
  rawValue = analogRead(analogPin);
  voltage = rawValue * (referenceVoltage / 1023.0);
a = ((abs(5-voltage)-0.89)*5); 

  Serial.print("Raw ADC: ");
  Serial.print(rawValue);
  Serial.print(" | Voltage: ");
  Serial.print(voltage, 3); // 3 decimal places
Serial.print(" V ");
Serial.println(a); 

  digitalWrite(LSB, LOW);
  digitalWrite(SB2, LOW);
  digitalWrite(SB3, HIGH);
  digitalWrite(MSB, HIGH);
  
  delay (1000);
  
  rawValue = analogRead(analogPin);
  voltage = rawValue * (referenceVoltage / 1023.0);
a = ((abs(5-voltage)-0.89)*5); 

  Serial.print("Raw ADC: ");
  Serial.print(rawValue);
  Serial.print(" | Voltage: ");
  Serial.print(voltage, 3); // 3 decimal places
Serial.print(" V ");
Serial.println(a); 

  digitalWrite(LSB, HIGH);
  digitalWrite(SB2, LOW);
  digitalWrite(SB3, HIGH);
  digitalWrite(MSB, HIGH);
  
  delay (1000);

  rawValue = analogRead(analogPin);
  voltage = rawValue * (referenceVoltage / 1023.0);
a = ((abs(5-voltage)-0.89)*5); 

  Serial.print("Raw ADC: ");
  Serial.print(rawValue);
  Serial.print(" | Voltage: ");
  Serial.print(voltage, 3); // 3 decimal places
Serial.print(" V ");
Serial.println(a); 

  digitalWrite(LSB, LOW);
  digitalWrite(SB2, HIGH);
  digitalWrite(SB3, HIGH);
  digitalWrite(MSB, HIGH);
  
  delay (1000);

  rawValue = analogRead(analogPin);
  voltage = rawValue * (referenceVoltage / 1023.0);
a = ((abs(5-voltage)-0.89)*5); 

  Serial.print("Raw ADC: ");
  Serial.print(rawValue);
  Serial.print(" | Voltage: ");
  Serial.print(voltage, 3); // 3 decimal places
Serial.print(" V ");
Serial.println(a); 

  digitalWrite(LSB, HIGH);
  digitalWrite(SB2, HIGH);
  digitalWrite(SB3, HIGH);
  digitalWrite(MSB, HIGH);
  
  delay (1000);


  rawValue = analogRead(analogPin);
  voltage = rawValue * (referenceVoltage / 1023.0);
a = ((abs(5-voltage)-0.89)*5);

  Serial.print("Raw ADC: ");
  Serial.print(rawValue);
  Serial.print(" | Voltage: ");
  Serial.print(voltage, 3); // 3 decimal places
Serial.print(" V ");
Serial.println(a); 
}
