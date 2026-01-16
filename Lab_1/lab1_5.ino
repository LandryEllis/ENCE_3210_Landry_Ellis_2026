#define RED_LED   8
#define GREEN_LED  9

#define N 20

int data[N] = {1, 2,3,4, 2,3,4, 2,3,9, 2,3,4, 7, 2,3,4, 2,3,2};
int pat[3]  = {2,3,4};

int mainCount = 0;

void setup()
{
  Serial.begin(9600);

  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);

  digitalWrite(RED_LED, LOW);
  digitalWrite(GREEN_LED, LOW);

  // count pattern matches
  mainCount = 0;
  for (int i = 0; i <= N - 3; i++)
  {
    if (data[i] == pat[0] && data[i + 1] == pat[1] && data[i + 2] == pat[2])
    {
      mainCount++;
    }
  }

  // LED result at end
  if (mainCount > 0)
  {
    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(RED_LED, LOW);
  }
  else
  {
    digitalWrite(RED_LED, HIGH);
    digitalWrite(GREEN_LED, LOW);
  }

  
  Serial.print("Pattern count = ");
  Serial.println(mainCount);
}

void loop()
{
}
