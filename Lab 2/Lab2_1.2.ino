#define LED_RED 5
#define LED_GREEN 4
#define LED_BLUE 6


const int buttonPin = 2;      
const int buttonPin2 = 3;      
volatile bool buttonPressed = false;
volatile bool buttonPressed2 = false;


volatile int buttonOneCount = 0;
volatile int buttonTwoCount = 0;




void setup() {
  Serial.begin(9600);
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP); // button to GND


  // Attach interrupt on falling edge
  attachInterrupt(digitalPinToInterrupt(buttonPin), buttonISR, FALLING); /////the no interupts and interupts thing needs to be learned


    pinMode(buttonPin2, INPUT_PULLUP); // button to GND


  // Attach interrupt on falling edge
  attachInterrupt(digitalPinToInterrupt(buttonPin2), buttonISR2, FALLING);
}


void loop() {


          digitalWrite(LED_RED, LOW);
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_BLUE, LOW);


  if (buttonPressed) {
    buttonPressed = false; // clear flag


    Serial.println("Button interrupt triggered!");
    delay (200);
  }


  if (buttonPressed2) {
    buttonPressed2 = false; // clear flag


    Serial.println("Button interrupt triggered!");
    delay(200);
  }


    if (buttonOneCount > buttonTwoCount) {
    digitalWrite(LED_RED, HIGH);


  }
  if (buttonOneCount == buttonTwoCount) {
    digitalWrite(LED_BLUE, HIGH);


  }
  if (buttonOneCount < buttonTwoCount) {
    digitalWrite(LED_GREEN, HIGH);


  }


    Serial.println(buttonOneCount);
    Serial.println(buttonTwoCount);
    delay (5000);


}


// ISR
void buttonISR() {
  buttonPressed = true;
  buttonOneCount++;
 
 
}


// ISR
void buttonISR2() {
  buttonPressed2 = true;
  buttonTwoCount++;
 




}





