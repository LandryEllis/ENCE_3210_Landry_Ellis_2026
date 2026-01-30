const uint8_t GREEN_LED_PIN = 8;
const uint8_t RED_LED_PIN   = 9;
const uint8_t BUTTON_PIN    = 2;


const unsigned long TASK1_PERIOD_MS = 1000; // 1 Hz
const unsigned long TASK2_PERIOD_MS = 100;  // 10 Hz


volatile uint32_t g_seconds = 0;


unsigned long t1_last = 0;
unsigned long t2_last = 0;


uint32_t lastPrintedAt = 0;

void setup() {
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(RED_LED_PIN, OUTPUT);

                                        //button to ground --> pull up 
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  Serial.begin(9600);
}

void loop() {
  unsigned long nowMs = millis();

  // 1 Hz counter do task 1
  if (nowMs - t1_last >= TASK1_PERIOD_MS) {
    t1_last += TASK1_PERIOD_MS;        
    task1_1Hz();
  }

  //10 Hz counter do task 2
  if (nowMs - t2_last >= TASK2_PERIOD_MS) {
    t2_last += TASK2_PERIOD_MS;
    task2_10Hz();
  }
  foregroundTask();
}

// Task 1 green led
void task1_1Hz() {
  digitalWrite(GREEN_LED_PIN, !digitalRead(GREEN_LED_PIN));
  g_seconds++; //timer
}

// Task 2 --> button pull up, button to gnd then red led
void task2_10Hz() {

  if (digitalRead(BUTTON_PIN) == LOW)
    digitalWrite(RED_LED_PIN, HIGH);
  else
    digitalWrite(RED_LED_PIN, LOW);
}

// prints every 3 seconds using the Task 1 counter
void foregroundTask() {
  uint32_t sec = g_seconds; //prevents getting new g_seconds value

  if ((sec - lastPrintedAt) >= 3) {
    lastPrintedAt = sec;
    Serial.println(sec);
  }
}
