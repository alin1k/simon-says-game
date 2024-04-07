int winLED = 12;
int loseLED = 2;

int LED1 = 4;
int LED2 = 6;
int LED3 = 8;

int buttonLED1 = 3;
int buttonLED2 = 5;
int buttonLED3 = 7;

int gameArray[100];
int gameArrayLength;

bool game;

void animation(){
  for (int j=0; j<7; j++) {
    for (int i = 4; i<=8; i+=2) {
      digitalWrite(i, HIGH);
      delay(100);
      digitalWrite(i, LOW);
    }
  }
}

void turnOffLEDs(){
  digitalWrite(4, LOW);
  digitalWrite(6, LOW);
  digitalWrite(8, LOW);
  digitalWrite(winLED, LOW);
  digitalWrite(loseLED, LOW);
}

double waitTime(){
  if(gameArrayLength >= 12) return 750;
  else if(gameArrayLength >= 7) return 1000;
  else if(gameArrayLength >= 3 ) return 1500;
  else return 2000;
}

void playGame(){
  game = true;

  while(game){
    turnOffLEDs();

    int randomLED = random(2,5) * 2;
    gameArray[gameArrayLength] = randomLED;
    gameArrayLength++;

    for(int i=0; i<gameArrayLength; i++){
      digitalWrite(gameArray[i], HIGH);
      delay(waitTime() / 2);
      digitalWrite(gameArray[i], LOW);
      delay(waitTime() / 2);
    }

    for(int i=0; i<gameArrayLength; i++){
      bool waitForInput = true;
      int userInput;

      while (waitForInput) {
        if(digitalRead(buttonLED1) == LOW){
          userInput = LED1;
          waitForInput = false;
        }else if(digitalRead(buttonLED2) == LOW){
          userInput = LED2;
          waitForInput = false;
        }else if(digitalRead(buttonLED3) == LOW){
          userInput = LED3;
          waitForInput = false;
        }
      }

      turnOffLEDs();
      digitalWrite(userInput, HIGH);
      delay(500);
      digitalWrite(userInput, LOW);

      if(userInput != gameArray[i]){
        game = false;
        digitalWrite(loseLED, HIGH);
        delay(2000);
        break;
      }
    }

    if(game){
      digitalWrite(winLED, HIGH);
      delay(2000);
    }
  }

  turnOffLEDs();
}

void restartGame(){
  gameArrayLength = 0;
}

void setup() {
  pinMode(loseLED, OUTPUT);
  pinMode(winLED, OUTPUT);

  pinMode(buttonLED1,INPUT_PULLUP);
  pinMode(LED1, OUTPUT);

  pinMode(buttonLED2, INPUT_PULLUP);
  pinMode(LED2, OUTPUT);

  pinMode(buttonLED3, INPUT_PULLUP);
  pinMode(LED3, OUTPUT);
}

void loop() {
  animation();
  
  playGame();

  restartGame();
}
