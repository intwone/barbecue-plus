 // include the display LCD library
#include <LiquidCrystal.h>  
#include <TimerOne.h>

boolean right   = 0, button01 = 0,
        up      = 0, button02 = 0,
        down    = 0, button03 = 0,
        left    = 0, button04 = 0,
        select  = 0, button05 = 0;

// select the pins used on the LCD panel
LiquidCrystal disp(8,  // RS digital 8
                   9,  // EN digital 9
                   4,  // D4 digital 4 
                   5,  // D5 digital 5
                   6,  // D6 digital 6
                   7); // D7 digital 7

// functions prototype                  
int  keyboardRead();
void controlAll();
void screen0();
void screen1();
void screen2();
void screen3();
void screen4();
void screen5();
void screen6();

// declaration of variables
int transistor_base = 0;
int slot_atual      = 0;
int adc_value       = 0;
int options_menu    = 0;  
int show_time       = 0;
int esp1_count      = 0;
int esp1_done       = 0;
int resp            = 0;
int slot[4][4]; // slot [row][column]

/*
------------------------------------------------------------------------
|     SLOTS     |   MEAT(0)   |  POINT(1)    |  TIME(2)   |   STATUS(3)
------------------------------------------------------------------------
|   (0)SLOT 1   |             |              |            |
------------------------------------------------------------------------
|   (1)SLOT 2   |             |              |            |
------------------------------------------------------------------------
|   (2)SLOT 3   |             |              |            |
------------------------------------------------------------------------
|   (3)SLOT 4   |             |              |            |
------------------------------------------------------------------------
*/

void setup(){  
  slot[0][2]=120;
  slot[1][2]=150;
  slot[2][2]=180;
  slot[3][2]=210;
  Timer1.initialize(1000000); 
  Timer1.attachInterrupt(controlAll);
  pinMode(transistor_base, OUTPUT);  
  disp.begin(16,2);
  
}  
  
void loop() {
  switch(options_menu) {
    case 0: 
      screen0();
      break;
    case 1: 
      screen1();
      break;
    case 2: 
      screen2();
      break;
    case 3: 
      screen3();
      break;
    case 4:
      screen4(); 
      break;
    case 5:
      screen5(); 
      break;
    case 6:
      screen6(); 
      break;
  }
}

void screen0() {
  do {
    disp.setCursor(0,0);
    disp.print("     WELCOME    ");
    disp.setCursor(0,1);
    disp.print("   BARBEBUE +   ");
    delay(2000);
    
    disp.clear();
    
    disp.setCursor(0,0);
    disp.print("  PRESS SELECT  ");
    disp.setCursor(0,1);
    disp.print("    TO READY    ");

    resp = keyboardRead();
    
    if(resp == 5) {
      options_menu++;
    }
  } while(options_menu == 0);
}

void screen1() {
  int menu = 1; 
  
  do {
    disp.setCursor(0,0);
    disp.print("SELECT SLOT:    ");

    switch(menu) {
      case 1:
        disp.setCursor(0,1);
        disp.print("> SLOT 1        ");
        slot_atual = 0;
        break;
      case 2:
        disp.setCursor(0,1);
        disp.print("> SLOT 2        ");
        slot_atual = 1;
        break;
      case 3:
        disp.setCursor(0,1);
        disp.print("> SLOT 3        ");
        slot_atual = 2;
        break;
      case 4:
        disp.setCursor(0,1);
        disp.print("> SLOT 4        ");
        slot_atual = 3;
        break;
    }

   resp = keyboardRead();
   
   if(resp == 1) {
    screen2();
   } 
   
   else if(resp == 3) {
    menu++;
    if(menu >= 5) menu = 4;  
   }
   
   else if(resp == 2) {
    menu--;
    if(menu <= 0) menu = 1;
   }
  } while(1);
}

void screen2() {
  int menu = 1;  
  
  do {
    disp.setCursor(0,0);
    disp.print("SELECT ACTION:  ");

    switch(menu) {
      case 1:
        disp.setCursor(0,1);
        disp.print("> CONFIG        ");
        resp = keyboardRead();
        if(resp == 1) {
          screen3();
        }
        break;
      case 2:
        disp.setCursor(0,1);
        disp.print("> TIME          ");
        resp = keyboardRead();
        if(resp == 1) {
          screen5();
        }
        break;
      case 3:
        disp.setCursor(0,1);
        disp.print("> START         ");
        resp = keyboardRead();
        if(resp == 1) {
          screen6();
        }
        break;
      case 4:
        disp.setCursor(0,1);
        disp.print("> CANCEL        ");
        resp = keyboardRead();
        if(resp == 1) {
          screen1();
        }
        break;
    }
    
    if(resp == 3) {
      menu++;
      if(menu >= 5) menu = 4;  
    }
    else if(resp == 2) {
      menu--;
      if(menu <= 0) menu = 1;
    } 
  } while(1);
  //options_menu++;
}

void screen3() {
  int menu = 1;  
  
  if(slot[slot_atual][1] > 0) { // carrega valor se tiver algo escrito
    menu = slot[slot_atual][0];
  }
  
  do {
    disp.setCursor(0,0);
    disp.print("MEAT OPTIONS:   ");
    
    switch(menu) {
      case 1:
        disp.setCursor(0,1);
        disp.print("> BOVINA        ");
        break;
      case 2:
        disp.setCursor(0,1);
        disp.print("> SUINA         ");
        break;
      case 3:
        disp.setCursor(0,1);
        disp.print("> AVES          ");    
        break;
      case 4:
        disp.setCursor(0,1);
        disp.print("> CORACAO       ");
        break;
      case 5: 
        disp.setCursor(0,1);
        disp.print("> QUEIJO        ");
        break;
    }

    resp = keyboardRead();
    
    if(resp == 1) { // carrega opção escolhida
        slot[slot_atual][1] = menu;
        screen4();
    }
    
    if(resp == 3) {
      menu++;
      if(menu >= 6) menu = 5;  
    }
    else if(resp == 2) {
      menu--;
      if(menu <= 0) menu = 1;
    }
  } while(1);   
}

void screen4() {
  int menu = 1;  
  
  if(slot[slot_atual][2] > 0) { //carrega valor se tiver algo escrito
    menu = slot[slot_atual][1];
  }
  
  do {
    disp.setCursor(0,0);
    disp.print("POINT OPTIONS:  "); 

    switch(menu) {
      case 1:
        disp.setCursor(0,1);
        disp.print("> RARE          ");
        break;
      case 2:
        disp.setCursor(0,1);
        disp.print("> MEDIUM        ");
        break;
      case 3:
        disp.setCursor(0,1);
        disp.print("> WELL DONE     ");
        break;
    }

    resp = keyboardRead();
    
    if(resp == 1) { // carrega
      slot[slot_atual][1] = menu;
      screen1();
    }
    if(resp == 3) {
      menu++;
      if(menu >= 4) menu = 3;  
    }
    else if(resp == 2) {
      menu--;
      if(menu <= 0) menu = 1;
    }
  } while(resp != 5);   

  //options_menu++;
}

void screen5() {
  // equações para mostrar o tempo de preparo no display LCD
  do {
    show_time = 1;
    disp.setCursor(0,0);
    disp.print("TIME:           ");
    
    // TIMER
    disp.setCursor(0,1);
    disp.print("                ");
    
    resp = keyboardRead();
    
    if(resp == 5) { // carrega
      show_time = 0;
      screen2();
    }
  } while(1);
}

void screen6() {
  // inicia o preparo da carne
  if(slot[slot_atual][3] == 0) {
    esp1_count = 0;
    slot[slot_atual][3] = 1;
    disp.setCursor(0,0);
    disp.print("STARTING        ");
    disp.setCursor(0,1);
    disp.print(".               ");
    delay(300);
    disp.setCursor(0,1);
    disp.print("..              ");
    delay(300);
    disp.setCursor(0,1);
    disp.print("...             ");
    delay(300);
    disp.setCursor(0,1);
    disp.print("....            ");
    delay(300);
    disp.setCursor(0,1);
    disp.print(".....           ");
    delay(300);
    disp.setCursor(0,1);
    disp.print("......          ");
    delay(300);
    disp.setCursor(0,1);
    disp.print(".......         ");
    delay(300);
    digitalWrite(transistor_base, HIGH);
  } else {
    disp.setCursor(0,0);
    disp.print("SLOT            ");
    disp.setCursor(0,1);
    disp.print("WORKING         ");
    resp = keyboardRead();
  }
  screen2();
}

int keyboardRead() {
  int but = 0;
  
  while(!but) {
    adc_value = analogRead(A0);
    
    if(adc_value < 50) { 
      button01 = 0x01;
      but = 1; 
    }
    else if (adc_value > 103 && adc_value < 200) {
      button02 = 0x01;
      but = 1; 
    }
    else if (adc_value > 250 && adc_value < 380) {
      button03 = 0x01;
      but = 1; 
    }
    else if (adc_value > 420 && adc_value < 520) {
      button04 = 0x01;  
      but = 1; 
    }
    else if (adc_value > 550 && adc_value < 780) {
      button05 = 0x01;
      but = 1; 
    }
  }
  
  while(adc_value < 1000) { // solta botao
    adc_value = analogRead(A0);
  }
  if(adc_value > 50 && button01) {
    button01 = 0;
    return  (1);
  }
  if(adc_value > 200 && button02) {
    button02=0;
    return  (2);  
  }
  if(adc_value > 380 && button03) {
    button03=0;
    return  (3);  
  }
  if(adc_value > 550 && button04) {
    button04 = 0;
    return  (4);  
  }
  if(adc_value > 780 && button05) {
    button05 = 0;
    return  (5);  
  }
  return (0);
}

void controlAll() {
  if(slot[0][3] == 1) { // espetinho on
    esp1_count++;
    digitalWrite(9, LOW);
  }    
  
  if (esp1_count >= slot[0][2]) {
    slot[0][3] == 0;
    esp1_count = 0;
    esp1_done = 1;
    digitalWrite(9, HIGH);
  } 
  
  if(show_time == 1) {
    if(slot_atual == 0 && slot[slot_atual][3] == 1) {
      unsigned long t = slot[slot_atual][2] - esp1_count;
      unsigned long m = (t / 60);
      unsigned long s = t % 60;
      disp.setCursor(0,1);
      disp.print(m);
      disp.setCursor(1,1);
      disp.print(":");
      disp.setCursor(2,1);
      disp.print(s);
    } 
    else if (slot_atual == 1 && slot[slot_atual][3] == 1) {
      unsigned long t = slot[slot_atual][2] - esp1_count;
      unsigned long m (t / 60);
      unsigned long s = t % 60;
      disp.setCursor(0,1);
      disp.print(m);
      disp.setCursor(1,1);
      disp.print(":");
      disp.setCursor(2,1);
      disp.print(s);
    }
  }
}  




