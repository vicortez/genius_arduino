#include <stdlib.h>// necessário p/ as funções rand() e srand()
#include <time.h>//necessário p/ função time()

#define bot_vm_press !digitalRead(botvm)
#define bot_am_press !digitalRead(botam)
#define bot_vd_press !digitalRead(botvd)
#define N 10

bool game_ended = false;
int numLeds = 1;

int botvd = 8;
int botam = 9;
int botvm = 10;
int ledvd = 5;
int ledam = 6;
int ledvm = 7;

int color_vec[20]={0};

///////////////////////////////////////////
void start_game(){
  set_color_vec();
  //um pra cada etapa do jogo
  for(int i = 0; i<N; i++){
    light_leds();
    push_buttons();
    if(game_ended){
      break;
    }
    numLeds++;
    Serial.println("TERMINOU RODADA");
  }

  game_ended = true;
  Serial.println("GAME ENDED");
}

///////////////////////////////////////////
void push_buttons(){

    for(int i = 0; i< numLeds; i++){
      int button_press = catch_single_button_press();
      if(button_press != color_vec[i]){
        game_ended = true;
        break;
      }
    }
    

}

//////////////////////////////////////////
int catch_single_button_press(){
    bool flag1 = 0;
    bool flag2 = 0;
    bool flag3 = 0;
        while(1){
        Serial.println("esperar_botao");
        Serial.println(digitalRead(botvm));
        
        if(bot_vm_press){
          while(1){
            Serial.println("botvm pressionado");
            if(!bot_vm_press){
              Serial.println("botvm solto");
              flag1=1;
              break;
            }
          }     
        }
      
      if(bot_am_press){
        while(1){
          Serial.println("bot2 pressionado");
          if(!bot_am_press){
            Serial.println("bot2 solto");
            flag2=1;
            break;
          }
        }
      }
      if(bot_vd_press){
        while(1){
          Serial.println("botvd pressionado");
          if(!bot_vd_press){
            Serial.println("botvd solto");
            flag3=1;
            break;
          }
        }
      }
        if(flag1  || flag2 || flag3){
          break;
        }
    }
    if(flag1){
       return 0;
    }else if(flag2){
      return 1;
    }else if(flag3){
      return 2;
    }
    else{
      Serial.println("nenhum");
    }
}

///////////////////////////////////////////
void set_color_vec(){
  float color;
  for(int i=0; i<N; i++){
    color = random(0, 3);
    color_vec[i]=color;
    Serial.println(color_vec[i]);
  } 
}

/////////////////////////////////////////////////////
void light_leds(){
    for(int i = 0; i < numLeds; i++){
      if(color_vec[i] == 2){
        digitalWrite(ledvd, HIGH);
        digitalWrite(ledam, LOW);
        digitalWrite(ledvm, LOW);
        delay(1000);
        digitalWrite(ledvd, LOW);
      }
      if(color_vec[i] == 1){
        digitalWrite(ledam, HIGH);
        digitalWrite(ledvd, LOW);
        digitalWrite(ledvm, LOW);
        delay(1000);
        digitalWrite(ledam, LOW);
      }
      if(color_vec[i] == 0){
        digitalWrite(ledvm, HIGH);
        digitalWrite(ledam, LOW);
        digitalWrite(ledvd, LOW);
        delay(1000);
        digitalWrite(ledvm, LOW);
      }
      delay(500);
  }
      Serial.print("numleds: ");
    Serial.println(numLeds);
}

void setup() {
  pinMode(botvd, INPUT_PULLUP);
  pinMode(botam, INPUT_PULLUP);
  pinMode(botvm, INPUT_PULLUP);
  pinMode(ledvd, OUTPUT);
  pinMode(ledam, OUTPUT);
  pinMode(ledvm, OUTPUT);

  Serial.begin(9600);

}

void loop() {
  if(!game_ended){
    start_game();  
  }

  digitalWrite(ledvd, HIGH);
  digitalWrite(ledam, HIGH);
  digitalWrite(ledvm, HIGH);
  Serial.print("POINTS: ");
  Serial.println(numLeds);
  
  
}
