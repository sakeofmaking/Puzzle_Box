/*
 * Title: Puzzle Box
 * Author: Nicholas LaJeunesse
 * Date: 4/30/17
 * 
 * Description: http://sakeofmaking.com/puzzle_box.html
 */

#define delay_else(x) if (solved == HIGH) { solution(); } else { delay(x); }

// Morse code variables

char text[100] = "HAPPY BD";     // *********** EDIT *********** to change LED morse message
int i = 0;
int j = 0;
int k = 0;
char char_key[37] = { ' ', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
                    'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
                    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
char morse_key[37][10] = { "/", ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..", "--",
                      "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--..",
                      "-----", ".----", "..---", "...--", "....-", ".....", "-....", "--...", "---..", "----." };                    

// set pin numbers:
const int interruptPin0 = 0;     // the number of the pushbutton pin 0
const int interruptPin1 = 1;     // the number of the pushbutton pin 1
const int interruptPin2 = 2;     // the number of the pushbutton pin 2
const int interruptPin3 = 3;     // the number of the pushbutton pin 3
const int interruptPin4 = 5;     // the number of the pushbutton pin 5
const int interruptPin5 = 6;     // the number of the pushbutton pin 6
const int interruptPin6 = 7;     // the number of the pushbutton pin 7
const int interruptPin7 = 8;     // the number of the pushbutton pin 8
const int grnLedPin =  13;       // the number of the GRN LED pin
volatile int redLedPin = 12;     // the number of the RED LED pin

// variables will change:
int buttonState0 = HIGH;         // variable for reading the pushbutton0 status
int buttonState1 = HIGH;         // variable for reading the pushbutton1 status
int buttonState2 = HIGH;         // variable for reading the pushbutton2 status
int buttonState3 = HIGH;         // variable for reading the pushbutton3 status
int buttonState4 = HIGH;         // variable for reading the pushbutton5 status
int buttonState5 = HIGH;         // variable for reading the pushbutton6 status
int buttonState6 = HIGH;         // variable for reading the pushbutton7 status
int buttonState7 = HIGH;         // variable for reading the pushbutton8 status
int solved = LOW;                // variable for state puzzle

void setup() 
{
  // initialize the LED pins as output:
  pinMode(grnLedPin, OUTPUT);
  pinMode(redLedPin, OUTPUT);
  // initialize the pushbutton pins 0 - 8 except 4 as input:
  pinMode(interruptPin0, INPUT_PULLUP);
  pinMode(interruptPin1, INPUT_PULLUP);
  pinMode(interruptPin2, INPUT_PULLUP);
  pinMode(interruptPin3, INPUT_PULLUP);
  pinMode(interruptPin4, INPUT_PULLUP);
  pinMode(interruptPin5, INPUT_PULLUP);
  pinMode(interruptPin6, INPUT_PULLUP);
  pinMode(interruptPin7, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin0), blink, CHANGE);
  attachInterrupt(digitalPinToInterrupt(interruptPin1), blink, CHANGE);
  attachInterrupt(digitalPinToInterrupt(interruptPin2), blink, CHANGE);
  attachInterrupt(digitalPinToInterrupt(interruptPin3), blink, CHANGE);
  attachInterrupt(digitalPinToInterrupt(interruptPin4), blink, CHANGE);
  attachInterrupt(digitalPinToInterrupt(interruptPin5), blink, CHANGE);
  attachInterrupt(digitalPinToInterrupt(interruptPin6), blink, CHANGE);
  attachInterrupt(digitalPinToInterrupt(interruptPin7), blink, CHANGE);
}

void loop() 
{
  // Execute Morse Code loop forever
  for(i = 0; i < strlen(text); i++)
  {
    for(j = 0; j < 37; j++)
    {
      if(text[i] == char_key[j])
      {
        for(k = 0; k < strlen(morse_key[j]); k++)
        {
          if(morse_key[j][k] == '.')
          {                                          //blink for '.'
            digitalWrite(redLedPin, HIGH);   
            delay_else(200); 
            digitalWrite(redLedPin, LOW);
            delay_else(200);                              //delay after '.'
          } else if(morse_key[j][k] == '-'){         //longer blink for '-'
            digitalWrite(redLedPin, HIGH);   
            delay_else(1000); 
            digitalWrite(redLedPin, LOW);
            delay_else(200);                              //delay after '-'
          } else if(morse_key[j][k] == '/'){         //delay for space between words
            delay_else(400);
          }
        }
        delay_else(400);                                  //delay for between characters
      }
    }
  }
  delay_else(2000);                                       //delay after message
}

void solution()
{
  digitalWrite(redLedPin, LOW);
  digitalWrite(grnLedPin, HIGH);
  delay(10000);
  digitalWrite(grnLedPin, LOW);
  solved = LOW;
}

// Interrupt routine
void blink() 
{
  buttonState0 = digitalRead(interruptPin0);
  buttonState1 = digitalRead(interruptPin1);
  buttonState2 = digitalRead(interruptPin2);
  buttonState3 = digitalRead(interruptPin3);
  buttonState4 = digitalRead(interruptPin4);
  buttonState5 = digitalRead(interruptPin5);
  buttonState6 = digitalRead(interruptPin6);
  buttonState7 = digitalRead(interruptPin7);
  
  // Test switch combination
  // LOW = 1, HIGH = 0 (I know, right?)
  // *********** EDIT *********** LOW and HIGH to change acceptable switch combination
  if ((buttonState0 == LOW) && (buttonState1 == HIGH) && (buttonState2 == LOW) && (buttonState3 == LOW) && (buttonState4 == LOW) && (buttonState5 == LOW) && (buttonState6 == HIGH) && (buttonState7 == LOW))
  {
    digitalWrite(redLedPin, LOW);
    digitalWrite(grnLedPin, HIGH);
    solved = HIGH;
  }
}
