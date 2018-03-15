#define PSTART 2
#define PSTOP 3
#define PESO A5
#define EV1 4
#define EV2 5
#define MOT 6

unsigned int stato, bottiglie;
unsigned long tempo;

void setup() {
  pinMode(PSTART, INPUT);
  pinMode(PSTOP, INPUT);
  pinMode(PESO, INPUT);
  pinMode(EV1, OUTPUT);
  pinMode(EV2, OUTPUT);
  pinMode(MOT, OUTPUT);
  
  stato = tempo = bottiglie = 0;

  Serial.begin(9600);
}

void loop() {
  switch(stato){
    
    case 0:
      Serial.println("Attesa Start.");
      
      digitalWrite(EV1, LOW);
      digitalWrite(EV2, LOW);
      digitalWrite(MOT, LOW);
      
      if(digitalRead(PSTART) == HIGH)
        stato = 1;
        
      break;
      
     case 1:
      Serial.println("Verifica presenza bottiglia.");
      
      digitalWrite(EV1, LOW);
      digitalWrite(EV2, LOW);
      digitalWrite(MOT, LOW);
      
      if(map(analogRead(PESO),0,1023,0,1200) >= 200)
        stato = 2;
      
      if(digitalRead(PSTOP) == HIGH || millis()-tempo >= 3000)
        stato = 0;
        
      break;
      
     case 2:
      Serial.println("Aggiunta primo liquido.");
      
      digitalWrite(EV1, HIGH);
      digitalWrite(EV2, LOW);
      digitalWrite(MOT, LOW);

      if(map(analogRead(PESO),0,1023,0,1200) >= 400)
        stato = 3;
      
      if(digitalRead(PSTOP) == HIGH)
        stato = 0;
        
      break;
      
     case 3:
      Serial.println("Aggiunta secondo liquido.");
     
      digitalWrite(EV1, LOW);
      digitalWrite(EV2, HIGH);
      digitalWrite(MOT, LOW);

      if(map(analogRead(PESO),0,1023,0,1200) >= 900)
        stato = 4;
      
      if(digitalRead(PSTOP) == HIGH)
        stato = 0;
        
      break;
      
     case 4:
      Serial.println("Sposta la bottiglia.");
      
      digitalWrite(EV1, LOW);
      digitalWrite(EV2, LOW);
      digitalWrite(MOT, HIGH);

      if(millis()-tempo >= 3000)
        stato = 5;
      
      if(digitalRead(PSTOP) == HIGH)
        stato = 0;
        
      break;
      
     case 5:
      Serial.println("Verifica pacco bottiglie.");
     
      bottiglie++;
      
      if(bottiglie >= 6)
        stato = 0;
      else
        stato = 1;
        
      break;
  }
}
