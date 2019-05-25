 // include the display LCD library
#include <LiquidCrystal.h>  

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
int keyboardRead();
void selected_slot();
void screen0();
void screen1();
void screen2();
void screen3();
void screen4();
void screen5();
void screen6();

// declaration of variables
int adc_value = 0;
int optionsMenu = 0;  
int resp = 0;
int slot[4][2]; // slot [row][column]

/*
----------------------------------------------
|   SLOTS(0)    |   MEAT(1)   |  POINT(2)    |
----------------------------------------------
|   (0)SLOT 1   |             |              |
----------------------------------------------
|   (1)SLOT 2   |             |              |
----------------------------------------------
|   (2)SLOT 3   |             |              |
----------------------------------------------
|   (3)SLOT 4   |             |              |
----------------------------------------------
*/

void setup(){  
  Serial.begin(9600);
  disp.begin(16,2);
}  
  
void loop() {
  switch(optionsMenu) {
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
      optionsMenu++;
    }
  } while(optionsMenu == 0);
}

void screen1() {
  // int menu = matriz_esp[valor_esp][0]; // inicia valor do menu  
  int menu = 1, button = 0;  
  int control = 0;
  
  do {
    disp.setCursor(0,0);
    disp.print("SELECT SLOT:    ");

    switch(menu) {
      case 1:
        disp.setCursor(0,1);
        disp.print("> SLOT 1        ");
        resp = keyboardRead();
        if(resp == 1) {
          selected_slot();
        }
        break;
      case 2:
        disp.setCursor(0,1);
        disp.print("> SLOT 2        ");
        resp = keyboardRead();
        if(resp == 1) {
          selected_slot();
        }
        break;
      case 3:
        disp.setCursor(0,1);
        disp.print("> SLOT 3        ");
        resp = keyboardRead();
        if(resp == 1) {
          selected_slot();
        }
        break;
      case 4:
        disp.setCursor(0,1);
        disp.print("> SLOT 4        ");
        resp = keyboardRead();
        if(resp == 1) {
          selected_slot();
        }
        break;
    }
    
    resp = keyboardRead();

    if(resp == 3) {
      menu++;
      if(menu >= 5) menu = 4;  
    }
    else if(resp == 2) {
      menu--;
      if(menu <= 0) menu = 1;
    }
  } while(resp != 5);
  //matriz_esp[valor_esp][0]=menu;
  optionsMenu++;
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
  
    resp = keyboardRead();
    
    if(resp == 3) {
      menu++;
      if(menu >= 5) menu = 4;  
    }
    else if(resp == 2) {
      menu--;
      if(menu <= 0) menu = 1;
    } 
  } while(resp != 5);
  //matriz_esp[valor_esp][0]=menu;
  optionsMenu++;
}

void screen3() {
  int menu = 1;  
  
  do {
    disp.setCursor(0,0);
    disp.print("MEAT OPTIONS:   ");
    
    switch(menu) {
      case 1:
        disp.setCursor(0,1);
        disp.print("> BOVINA        ");
        resp = keyboardRead();
        if(resp == 1) {
          screen4();
        }
        break;
      case 2:
        disp.setCursor(0,1);
        disp.print("> SUINA         ");
        resp = keyboardRead();
        if(resp == 1) {
          screen4();
        }
        break;
      case 3:
        disp.setCursor(0,1);
        disp.print("> AVES          ");
        resp = keyboardRead();
        if(resp == 1) {
          screen4();
        }
        break;
      case 4:
        disp.setCursor(0,1);
        disp.print("> CORACAO       ");
        resp = keyboardRead();
        if(resp == 1) {
          screen4();
        }
        break;
      case 5: 
        disp.setCursor(0,1);
        disp.print("> QUEIJO        ");
        resp = keyboardRead();
        if(resp == 1) {
          screen4();
        }
        break;
    }

    resp = keyboardRead();
    
    if(resp == 3) {
      menu++;
      if(menu >= 6) menu = 5;  
    }
    else if(resp == 2) {
      menu--;
      if(menu <= 0) menu = 1;
    }
  } while(resp != 5);   

  optionsMenu++;
}

void screen4() {
  int menu = 1;  
  
  do {
    disp.setCursor(0,0);
    disp.print("POINT OPTIONS:  "); 

    switch(menu) {
      case 1:
        disp.setCursor(0,1);
        disp.print("> RARE          ");
        resp = keyboardRead();
        if(resp == 1) {
          screen1();
        }
        break;
      case 2:
        disp.setCursor(0,1);
        disp.print("> MEDIUM        ");
        resp = keyboardRead();
        if(resp == 1) {
          screen1();
        }
        break;
      case 3:
        disp.setCursor(0,1);
        disp.print("> WELL DONE     ");
        resp = keyboardRead();
        if(resp == 1) {
          screen1();
        }
        break;
    }

    resp = keyboardRead();
    
    if(resp == 3) {
      menu++;
      if(menu >= 4) menu = 3;  
    }
    else if(resp == 2) {
      menu--;
      if(menu <= 0) menu = 1;
    }
  } while(resp != 5);   

  optionsMenu++;
}

void screen5() {
  // equações para mostrar o tempo de preparo no display LCD
}

void screen6() {
  // inicia o preparo da carne
}

void selected_slot() {
  int resp = 0;
  resp = keyboardRead();
  
  if(resp == 1) {
    screen2();
  }
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





