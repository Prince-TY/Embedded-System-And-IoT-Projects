int a = 2;
int b = 3;
int c = 4;
int d = 5;
int e = 6;
int f = 7;
int g = 8;

void setup() {
  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(d, OUTPUT);
  pinMode(e, OUTPUT);
  pinMode(f, OUTPUT);
  pinMode(g, OUTPUT);
}

void loop() {
  displayDigit(0); delay(1000);
  displayDigit(1); delay(1000);
  displayDigit(2); delay(1000);
  displayDigit(3); delay(1000);
  displayDigit(4); delay(1000);
  displayDigit(5); delay(1000);
  displayDigit(6); delay(1000);
  displayDigit(7); delay(1000);
  displayDigit(8); delay(1000);
  displayDigit(9); delay(1000);
}

void displayDigit(int digit) {
  switch (digit) {
    case 0: digitalWrite(a,1); digitalWrite(b,1); digitalWrite(c,1); digitalWrite(d,1); digitalWrite(e,1); digitalWrite(f,1); digitalWrite(g,0); break;
    case 1: digitalWrite(a,0); digitalWrite(b,1); digitalWrite(c,1); digitalWrite(d,0); digitalWrite(e,0); digitalWrite(f,0); digitalWrite(g,0); break;
    case 2: digitalWrite(a,1); digitalWrite(b,1); digitalWrite(c,0); digitalWrite(d,1); digitalWrite(e,1); digitalWrite(f,0); digitalWrite(g,1); break;
    case 3: digitalWrite(a,1); digitalWrite(b,1); digitalWrite(c,1); digitalWrite(d,1); digitalWrite(e,0); digitalWrite(f,0); digitalWrite(g,1); break;
    case 4: digitalWrite(a,0); digitalWrite(b,1); digitalWrite(c,1); digitalWrite(d,0); digitalWrite(e,0); digitalWrite(f,1); digitalWrite(g,1); break;
    case 5: digitalWrite(a,1); digitalWrite(b,0); digitalWrite(c,1); digitalWrite(d,1); digitalWrite(e,0); digitalWrite(f,1); digitalWrite(g,1); break;
    case 6: digitalWrite(a,1); digitalWrite(b,0); digitalWrite(c,1); digitalWrite(d,1); digitalWrite(e,1); digitalWrite(f,1); digitalWrite(g,1); break;
    case 7: digitalWrite(a,1); digitalWrite(b,1); digitalWrite(c,1); digitalWrite(d,0); digitalWrite(e,0); digitalWrite(f,0); digitalWrite(g,0); break;
    case 8: digitalWrite(a,1); digitalWrite(b,1); digitalWrite(c,1); digitalWrite(d,1); digitalWrite(e,1); digitalWrite(f,1); digitalWrite(g,1); break;
    case 9: digitalWrite(a,1); digitalWrite(b,1); digitalWrite(c,1); digitalWrite(d,1); digitalWrite(e,0); digitalWrite(f,1); digitalWrite(g,1); break;
  }
}
