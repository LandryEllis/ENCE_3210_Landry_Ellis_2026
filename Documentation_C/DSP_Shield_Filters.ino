#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

/* ================= OLED CONFIG ================= */
#define SCREEN_WIDTH    128   // OLED display width, in pixels
#define SCREEN_HEIGHT   32    // OLED display height, in pixels
#define OLED_RESET      -1    // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS  0x3C  ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

/* ================= GPIOs ================= */
#define BUTTON_1 2
#define BUTTON_2 3

// DAC uses:
// PORTD bits 4–7  -> DAC bits 0–3
// PORTB bits 0–5  -> DAC bits 4–9
const int gDAC_PIN[10] = {4, 5, 6, 7, 8, 9, 10, 11, 12, 13};

/* ================= SIGNAL ================= */
#define DAC_MAX       1023
#define SINE_SAMPLES  256
#define ADC_MIN_DELAY 100   // us
#define ADC_MAX_DELAY 1000  // us

uint16_t gSineTable[SINE_SAMPLES];
uint16_t gSampleDelayUs = 1;

/* ================= MENU ================= */
enum MenuItem {
  MENU_LPF,
  MENU_HPF,
  MENU_BPF,
  MENU_BYP
};

#define MENU_COUNT 4

const char* menuText[MENU_COUNT] = {
  "LOW-PASS FILTER",
  "HIGH-PASS FILTER",
  "BAND-PASS FILTER",
  "BYPASS"
};

int8_t gMenuIndex = 1;

volatile uint8_t gISR_Flag_1 = 0;
volatile uint8_t gISR_Flag_2 = 0;

/* ================= FIR FILTER ================= */
#define FIR_TAPS 8

int16_t firBuffer[FIR_TAPS] = {0};
uint8_t firIndex = 0;

// Low-Pass (moving average)
const int8_t firLPF[FIR_TAPS] = {
  1, 1, 1, 1, 1, 1, 1, 1
};

// High-Pass (DC blocking)
const int8_t firHPF[FIR_TAPS] = {
  -1, -1, -1, 7, -1, -1, -1, -1
};

// Band-Pass (mid emphasis)
const int8_t firBPF[FIR_TAPS] = {
  -1, 0, 2, 3, 3, 2, 0, -1
};

void setup() {
  Serial.begin(115200);

  // Init Buttons
  pinMode(BUTTON_1, INPUT);
  pinMode(BUTTON_2, INPUT);

  attachInterrupt(digitalPinToInterrupt(BUTTON_1), isr_button_1, FALLING);
  attachInterrupt(digitalPinToInterrupt(BUTTON_2), isr_button_2, FALLING);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  display.setTextColor(SSD1306_WHITE); // Set OLED Text Color
  display.clearDisplay(); // Clear the buffer
  display.setRotation(0);  // Set screen rotation

  // Init DAC
  // Init GPIO
  for(int i=0; i<10; i++){
    pinMode(gDAC_PIN[i], OUTPUT);
  }

  // Generate sine lookup table (0–1023)
  for (int i = 0; i < SINE_SAMPLES; i++) {
    float angle = 2.0f * PI * i / SINE_SAMPLES;
    gSineTable[i] = (uint16_t)(512 + 511 * sin(angle));
  }

  outputDAC(0);
}

/* ================= LOOP ================= */
void loop() {
  if( (gISR_Flag_1 == 1) ||(gISR_Flag_2 == 1) )
    updateDisplay();

  applyFilter();
}

/* ================= FUNCTIONS ================= */
void isr_button_1(){
  gISR_Flag_1 = 1;
}

void isr_button_2(){
  gISR_Flag_2 = 1;
}

void updateDisplay() {

  if(gISR_Flag_1) {
    gISR_Flag_1 = 0;
    gMenuIndex = (gMenuIndex - 1 + MENU_COUNT) % MENU_COUNT;
  }

  if(gISR_Flag_2) {
    gISR_Flag_2 = 0;
    gMenuIndex = (gMenuIndex + 1) % MENU_COUNT;
  }

  display.clearDisplay();
  display.setTextSize(1);

  for (int8_t i = -1; i <= 1; i++) {
    int8_t item = (gMenuIndex + i + MENU_COUNT) % MENU_COUNT;
    int y = (i + 1) * 10;

    display.setCursor(0, y);
    display.print(i == 0 ? "> " : "  ");
    display.print(menuText[item]);
  }

  display.display();
}

void applyFilter() {
  int16_t sample = analogRead(A2) - 512;  // center signal

  firBuffer[firIndex] = sample;
  firIndex = (firIndex + 1) % FIR_TAPS;

  uint16_t output = 0;

  switch (gMenuIndex) {
    case MENU_LPF:
      // Low-Pass Filter
      output = applyFIR(firLPF, 3);   // ÷8
      break;
    
    case MENU_HPF:
      // High-Pass Filter
      output = applyFIR(firHPF, 3);
      break;

    case MENU_BPF:
      // Band-Pass Filter
      output = applyFIR(firBPF, 3);
      break;

    case MENU_BYP:
      // Bypass
      output = sample + 512;
      break;
  }
  outputDAC(output);
}

void outputDAC(uint16_t value) {
  value &= 0x03FF; // 10-bit safety mask
  // PORTD: bits 4–7 = DAC bits 0–3
  PORTD = (PORTD & 0x0F) | ((value & 0x000F) << 4);
  // PORTB: bits 0–5 = DAC bits 4–9
  PORTB = (PORTB & 0xC0) | (value >> 4);
}

uint16_t applyFIR(const int8_t* coeffs, uint8_t gainShift) {
  int32_t acc = 0;

  for (uint8_t i = 0; i < FIR_TAPS; i++) {
    uint8_t idx = (firIndex + FIR_TAPS - i) % FIR_TAPS;
    acc += firBuffer[idx] * coeffs[i];
  }

  acc >>= gainShift;   // normalize
  acc += 512;          // recenter (signed → unsigned)

  if (acc < 0) acc = 0;
  if (acc > DAC_MAX) acc = DAC_MAX;

  return (uint16_t)acc;
}

