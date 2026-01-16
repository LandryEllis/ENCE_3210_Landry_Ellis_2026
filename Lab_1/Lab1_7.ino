#define N 10

#define RED_LED 8
#define GREEN_LED    9
#define BLUE_LED  10

#define OP_BTN 2
#define EXE_BTN   3

int A[N] = { 0,1,2,3,4,5,6,7,8,9 }; //array A values
int B[N] = { 9,8,7,6,5,4,3,2,1,0 };
int C[N]; // output array

int opCount = 0;            // 1 add, 2 sub, 3 mul
int lastOpBtn  = HIGH;      // pullup idle state
int lastExeBtn = HIGH;//last EXE button

void setOpLeds()
{
 digitalWrite(RED_LED,   (opCount == 1) ? HIGH : LOW); // sets red led  
  digitalWrite(GREEN_LED,(opCount == 2) ? HIGH : LOW);//sets green LED
  
  digitalWrite(BLUE_LED,  (opCount == 3) ? HIGH : LOW);
}

void allOff()
{
  digitalWrite(RED_LED, LOW);//turn everything off
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(BLUE_LED, LOW);
}

void allOn()
{
  digitalWrite(RED_LED, HIGH);
  digitalWrite(GREEN_LED, HIGH);
    digitalWrite(BLUE_LED, HIGH);//turn leds on 
}

void printArrays()
{

 Serial.print("opCount = ");
 Serial.println(opCount);

 Serial.print("A: ");//printting A
  for (int i = 0; i < N; i++) { Serial.print(A[i]); Serial.print(' '); }
     Serial.println();

  Serial.print("B: ");
  for(int i = 0; i < N; i++) { Serial.print(B[i]); Serial.print(' '); }
  Serial.println();

  Serial.print("C: ");
  for (int i = 0;i < N; i++) { Serial.print(C[i]); Serial.print(' '); } //reslts
 Serial.println();
  Serial.println();
}

void setup()
{
  Serial.begin(9600);

  pinMode(RED_LED, OUTPUT);
   pinMode(GREEN_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);

  pinMode(OP_BTN, INPUT_PULLUP);
  pinMode(EXE_BTN, INPUT_PULLUP);

  allOff();
  Serial.println("Ready. Press OP button to choose (+,-,*) then press EXE to run."); //start msg
}

void loop()
{
  int opBtnState  = digitalRead(OP_BTN);
 int exeBtnState = digitalRead(EXE_BTN);

  // OP button press (HIGH -> LOW)
  if (opBtnState == LOW && lastOpBtn == HIGH)
  {
    opCount++;
    if (opCount > 3) opCount = 1;

      setOpLeds();

    if (opCount == 1) Serial.println("Selected: ADD (RED)");
    if (opCount == 2) Serial.println("Selected: SUB (GREEN)");
    if (opCount == 3) Serial.println("Selected: MUL (BLUE)");

    //delay(200);  
  }

  //EXE button press (HIGH -> LOW)
  if (exeBtnState == LOW && lastExeBtn == HIGH)
  {
    allOff();     // LEDs off while running

    for (int i = 0; i < N; i++)
    {
      if (opCount == 1)      C[i] = A[i] + B[i];
      else if (opCount == 2) C[i] = A[i] - B[i];
      else if (opCount == 3) C[i] = A[i] * B[i];
      else                   C[i] = 0;   // no op chosen yet
    }

    allOn();      // done
    Serial.println("Done. Results:");
   printArrays();

    //delay(200);  
  }

  lastOpBtn  = opBtnState;
 lastExeBtn = exeBtnState;
}
