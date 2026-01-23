#define N 10
#define BUTTON1_PIN 2

volatile int x[N] = { 10,11,12,13,14,15,16,17,18,19 }; // fill initially at top
volatile int y[N];
volatile int n= 0;                 // index for the array
volatile unsigned long lastIsr = 0;  // debounce timing

void button1ISR()
{
  unsigned long now = millis();
  if (now - lastIsr < 200) return;  // debounce
  lastIsr = now;

  y[n] = 2 * x[n] - x[n - 1];      

  n++;
  if (n >= N) n = 1;                // avoids n-1 < 0
}

void setup()
{
  Serial.begin(9600);

  pinMode(BUTTON1_PIN, INPUT_PULLUP);

  for (int i = 0; i < N; i++) y[i] = 0;
  n = 1;                           // start at 1 so x[n-1] is valid

  attachInterrupt(digitalPinToInterrupt(BUTTON1_PIN), button1ISR, FALLING);

  Serial.println("Ready. Press button to compute y[n] = 2*x[n] - x[n-1].");
}

void loop()
{
  static unsigned long lastPrint = 0;
  if (millis() - lastPrint > 500) {
    lastPrint = millis();

    noInterrupts();
    int xn = x[n];
     int yn = y[n];
    int idx = n;
    interrupts();

    Serial.print("n=");
  Serial.print(idx);
    Serial.print("  x[n]=");
    Serial.print(xn);
    Serial.print("  y[n]=");
    Serial.println(yn);
  }
}
