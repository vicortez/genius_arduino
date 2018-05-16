/*
 * code by Victor Cortez
 * https://github.com/vicortez
 * Contributors:
 *  Matheus blabla
 *  https://github.com/blabla
 */
//#include <stdlib.h>// necessário p/ as funções rand() e srand()
//#include <time.h>//necessário p/ função time()

#define bot_rd_press !digitalRead(botrd)
#define bot_yl_press !digitalRead(botyl)
#define bot_vd_press !digitalRead(botgr)
#define N 10

bool game_ended = false;
int level = 1;

//buttons and leds
int botgr = 8;
int botyl = 9;
int botrd = 10;
int ledgr = 5;
int ledyl = 6;
int ledrd = 7;

int color_vec[20]={0};

///////////////////////////////////////////
void start_game(){
  set_color_vec();
  //one for each level
  for(int i = 0; i<N; i++){
    play_level();
    if(game_ended){
      break;
    }
  }

  game_ended = true;
  Serial.println("GAME ENDED");
}

void play_level(){
    light_leds();
    receive_button_pushes();
    if(!game_ended){
      level++;  
    }
    Serial.println("LEVEL FINISHED");
}


///////////////////////////////////////////
void receive_button_pushes(){
    for(int i = 0; i< level; i++){
      int button_pressed = catch_single_button_pressed();
      if(button_pressed != color_vec[i]){
        game_ended = true;
        break;
      }
    }
}

/*
 * Waits for a button to be pressed, then returns the number
 * that represents that button. (0, 1, 2 = rd, gr, yl <- TODO fix)
 */
//////////////////////////////////////////
int catch_single_button_pressed(){
    bool flag1 = 0;
    bool flag2 = 0;
    bool flag3 = 0;
        while(1){
        //Serial.println("waiting button");
        //Serial.println(digitalRead(botrd));
        
          if(bot_rd_press ){
            while(1){
              Serial.println("botrd pressed");
              if(!bot_rd_press){
                Serial.println("botrd released");
                flag1=1;
                break;
              }
            }     
          }
        
        if(bot_yl_press){
          while(1){
            Serial.println("botyl pressed");
            if(!bot_yl_press){
              Serial.println("botyl released");
              flag2=1;
              break;
            }
          }
        }
        if(bot_vd_press){
          while(1){
            Serial.println("botgr pressionado");
            if(!bot_vd_press){
              Serial.println("botgr solto");
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
      Serial.println("none");
    }
}

/*
 *initialize the vector responsible for the color of the up to N 
 *leds that will light up 
 *///////////////////////////////
void set_color_vec(){
  float color;
  for(int i=0; i<N; i++){
    color = random(0, 3);
    color_vec[i]=color;
    Serial.println(color_vec[i]);
  } 
}

//////////////////////////////////////////
void light_leds(){
    for(int i = 0; i < level; i++){
      if(color_vec[i] == 2){
        digitalWrite(ledgr, HIGH);
        digitalWrite(ledyl, LOW);
        digitalWrite(ledrd, LOW);
        delay(1000);
        digitalWrite(ledgr, LOW);
      }
      if(color_vec[i] == 1){
        digitalWrite(ledyl, HIGH);
        digitalWrite(ledgr, LOW);
        digitalWrite(ledrd, LOW);
        delay(1000);
        digitalWrite(ledyl, LOW);
      }
      if(color_vec[i] == 0){
        digitalWrite(ledrd, HIGH);
        digitalWrite(ledyl, LOW);
        digitalWrite(ledgr, LOW);
        delay(1000);
        digitalWrite(ledrd, LOW);
      }
      delay(500);
  }
      Serial.print("level: ");
    Serial.println(level);
}

void setup() {
  pinMode(botgr, INPUT_PULLUP);
  pinMode(botyl, INPUT_PULLUP);
  pinMode(botrd, INPUT_PULLUP);
  pinMode(ledgr, OUTPUT);
  pinMode(ledyl, OUTPUT);
  pinMode(ledrd, OUTPUT);

  Serial.begin(9600);

}

void loop() {
  if(!game_ended){
    start_game();
  }

  digitalWrite(ledgr, HIGH);
  digitalWrite(ledyl, HIGH);
  digitalWrite(ledrd, HIGH);
  Serial.print("LEVEL: ");
  Serial.println(level-1);
  
  
}
