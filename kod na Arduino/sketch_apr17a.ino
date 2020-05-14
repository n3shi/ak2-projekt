void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {

  if (Serial.available() > 0)
  {
    String info = Serial.readStringUntil('\n');
    int x = info.toInt();
    int tempX = pierwsza(x);
    Serial.println(tempX);
  }
}
int pierwsza(int x)
{
  for (int i = 2; i * i <= x; i++)
  {
    if (x % i == 0)
    {
      return 0;
    }
  }
  return 1;
}
