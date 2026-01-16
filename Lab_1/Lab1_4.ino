#define RED_LED   8
#define GREEN_LED 9
#define BLUE_LED  10

#define MAX_LEN 50

char arr[MAX_LEN + 1];   // user input array (string)
int rCount = 0;
int gCount = 0;
int bCount = 0;
//counts live here for now

void setup()
{
  Serial.begin(9600);//serial start

  pinMode(RED_LED, OUTPUT);
      pinMode(GREEN_LED, OUTPUT); //green output
  pinMode(BLUE_LED, OUTPUT);//blue out

  digitalWrite(RED_LED, LOW);
 digitalWrite(GREEN_LED, LOW);
      digitalWrite(BLUE_LED, LOW); //leds off init

  Serial.println("Enter an array of letters (R, G, B) then press Enter:");
 Serial.println("Example: RRGBGBR");//exampel input
}

void loop()
{
  if(Serial.available() > 0) //has input?
  {
    // read the whole input line from the user
    int len = Serial.readBytesUntil('\n', arr, MAX_LEN);
    arr[len] = '\0';   // make it a proper C string
//string ends here

    // reset counts
    rCount = 0;
 gCount = 0;
      bCount = 0; //reset all

    // count R, G, B
    for (int i = 0; i < len; i++)
    {
      if (arr[i] == 'R')
        rCount++;
      else if (arr[i] == 'G')
        gCount++;
      else if (arr[i] == 'B')
        bCount++;
    }

    // turn LEDs on if the letter was found
    digitalWrite(RED_LED,(rCount > 0) ? HIGH : LOW);
    digitalWrite(GREEN_LED, (gCount > 0) ? HIGH : LOW);
       digitalWrite(BLUE_LED,  (bCount > 0) ? HIGH : LOW);//led check

    // print results
    Serial.println("\nCounts:");
    Serial.print("R = ");
  Serial.println(rCount);//r output
    Serial.print("G = ");
       Serial.println(gCount);
    Serial.print("B = ");
    Serial.println(bCount);//done

    Serial.println("\nEnter another array (R, G, B) then press Enter:"); //again prompt
  }
}
