#define RED_LED   8
#define GREEN_LED 9
#define BLUE_LED  10

#define BUTTON_PIN 2

int running = 0;          // sequence state
int lastButton = LOW;     // previous button state
//button stuff lives up here

void setup()
{
 pinMode(RED_LED, OUTPUT); //set red as output
    pinMode(GREEN_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);//blue output too

  pinMode(BUTTON_PIN, INPUT); //button input

  digitalWrite(RED_LED, LOW);
 digitalWrite(GREEN_LED, LOW); //turn off green
  digitalWrite(BLUE_LED, LOW); //off for start
}

void loop()
{
  int buttonState = digitalRead(BUTTON_PIN);//read btn

  // detect button press (edge)
  if (buttonState == HIGH && lastButton == LOW)
  {
    running = !running;   // toggle run state
    
  }

  lastButton = buttonState;//save last state

  if (running)
  {
    // R
    digitalWrite(RED_LED, HIGH);
    digitalWrite(GREEN_LED, LOW);
 digitalWrite(BLUE_LED, LOW);//only red
    delay(400);

    // RG
    digitalWrite(GREEN_LED, HIGH); // now red+green
    delay(400);

    // RGB
    digitalWrite(BLUE_LED, HIGH);
    delay(400);//all on now

    // GB
    digitalWrite(RED_LED, LOW);
    delay(400);

    // B
    digitalWrite(GREEN_LED, LOW);
    delay(400);

    // RB
    digitalWrite(RED_LED, HIGH);//red comes back
    delay(400);
  }
  else
  {
    // all off when stopped
 digitalWrite(RED_LED, LOW);
digitalWrite(GREEN_LED, LOW);
digitalWrite(BLUE_LED, LOW);//stop mode
  }
}
