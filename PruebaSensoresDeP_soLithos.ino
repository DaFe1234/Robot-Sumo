int pisoIzq = A4;
int lecIzq = 0;
int pisoDer = A5;
int lecDer = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(pisoIzq, INPUT);
  pinMode(pisoDer, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  lecIzq = digitalRead(pisoIzq);
  lecDer = digitalRead(pisoDer);
  Serial.print(lecIzq);
  Serial.print("  ");
  Serial.println(lecDer);
}
