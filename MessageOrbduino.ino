#define ORBPIN 13

void setup () {
  pinMode(ORBPIN,OUTPUT);
  Serial.begin(38400);
}
int next=0;
int curr=0;
int digits=0;

void loop () {
  Serial.print("Current state: ");
  Serial.println(curr);
  // Process serial data
  while (Serial.available()) {
    char ch = Serial.read();
    if (digits > 0 && (ch == '\r' || ch == '\n')) {
      // End of number! Use it.
      curr = next;
      next = 0;
      digits=0;
    } else {
      // It's a number to add to what we're working on.
      int n = (ch - '0');
      if (n < 0 || n > 9)
        return;
      next *= 10;
      next += n;
      digits++;
    }
  }
  
  // Act on the current state.
  if (curr) {
    digitalWrite(ORBPIN,HIGH);
  } else {
    digitalWrite(ORBPIN,LOW);
  }
  delay(100);
}

