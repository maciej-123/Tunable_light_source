#include <LiquidCrystal.h>
#include <LiquidCrystal_I2C.h>
#include <Encoder.h>

LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display
Encoder encoder(20, 21);

byte level8[8] = {
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
};


byte level7[8] = {
  B00000,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
};

byte level6[8] = {
  B00000,
  B00000,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
};

byte level5[8] = {
  B00000,
  B00000,
  B00000,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
};

byte level4[8] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B11111,
  B11111,
  B11111,
  B11111,
};

byte level3[8] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B11111,
  B11111,
  B11111,
};

byte level2[8] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B11111,
  B11111,
};

byte level1[8] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B11111,
};

byte level0[8] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
};

byte sep[8] = {
  B00100,
  B00100,
  B00100,
  B00100,
  B00100,
  B00100,
  B00100,
  B00100,

};


int Up = 15;
int Down = 14;
int Left = 13;
int Right = 16;
int Enter = 17;
//int Choose = 41;
int Choose = 0;


void setup() {
  
  pinMode(Up, INPUT);    
  pinMode(Down, INPUT);    
  pinMode(Left, INPUT);    
  pinMode(Right, INPUT);    
  pinMode(Enter, INPUT);    
  pinMode(Choose, INPUT);  
  
  lcd.init();                      // initialize the lcd 
  lcd.init();
  // Print a message to the LCD.
  lcd.backlight();
  lcd.begin(16, 2);

  lcd.createChar(0, level1);
  lcd.createChar(1, level2);
  lcd.createChar(2, level3);
  lcd.createChar(3, level4);
  lcd.createChar(4, level5);
  lcd.createChar(5, level6);
  lcd.createChar(6, level7);
  lcd.createChar(7, level8);
}

int CS[12] = {0};

void DisplayColourSpectrum(){

  for(int x = 0; x < 12; x++){
  if(CS[x]<=8 && CS[x] >0){lcd.setCursor(x+2,1);lcd.write(CS[x]-1);lcd.setCursor(x+2,0);lcd.write(254);}
  else if(CS[x] > 8 && CS[x] <=16){lcd.setCursor(x+2,1);lcd.write(255);lcd.setCursor(x+2,0);lcd.write(CS[x]-1);}
   else{lcd.setCursor(x+2,1);lcd.write(254);lcd.setCursor(x+2,0);lcd.write(254);}
  }
}

void OutputColourSpectrum(){
  analogWrite(12,(CS[0]*255)/16);
  analogWrite(11,(CS[1]*255)/16);
  analogWrite(10,(CS[2]*255)/16);
  analogWrite(9 ,(CS[3]*255)/16);
  analogWrite(8 ,(CS[4]*255)/16);
  analogWrite(7 ,(CS[5]*255)/16);
  analogWrite(6 ,(CS[6]*255)/16);
  analogWrite(5 ,(CS[7]*255)/16);
  analogWrite(4 ,(CS[8]*255)/16);
  analogWrite(3 ,(CS[9]*255)/16);
  analogWrite(2 ,(CS[10]*255)/16);
  analogWrite(1 ,(CS[11]*255)/16);
}



void clear_output()
{
  for(int x = 0; x < 12; x++)
  {
    CS[x] = 0;
  }
}


void white_ref()
{
  analogWrite(12,0);
  analogWrite(11,0);
  analogWrite(10,255);
  analogWrite(9 ,0);
  analogWrite(8 ,0);
  analogWrite(7 ,0);
  analogWrite(6 ,255);
  analogWrite(5 ,0);
  analogWrite(4 ,255);
  analogWrite(3 ,0);
  analogWrite(2 ,0);
  analogWrite(1 ,0);
}

void daylight()
{
  analogWrite(11,(10*255)/16);
  analogWrite(10,(12*255)/16);
  analogWrite(9 ,(13*255)/16);
  analogWrite(8 ,(14*255)/16);
  analogWrite(7 ,(15*255)/16);
  analogWrite(6 ,(14*255)/16);
  analogWrite(5 ,(13*255)/16);
  analogWrite(4 ,(12*255)/16);
  analogWrite(3 ,(11*255)/16);
  analogWrite(2 ,(10*255)/16);
  analogWrite(1 ,(8*255)/16);

//  analogWrite(11,(6*255)/16);
//  analogWrite(10,(8*255)/16);
//  analogWrite(9 ,(9*255)/16);
//  analogWrite(8 ,(10*255)/16);
//  analogWrite(7 ,(9*255)/16);
//  analogWrite(6 ,(9*255)/16);
//  analogWrite(5 ,(8*255)/16);
//  analogWrite(4 ,(7*255)/16);
//  analogWrite(3 ,(6*255)/16);
//  analogWrite(2 ,(6*255)/16);
//  analogWrite(1 ,(5*255)/16);
}

String functions[12] = {"Random","Control","Protan L-cone","Deutan M-cone","Tritan S-Cone","Colour Correct","Miscellaneous","MonoChrome","Fluctuating","Strobe","Anomalyscope","Pride"};

long Position  = -999;

//random option
int randomTime = 1500;
bool randomTimeOn = true;

//control option
int Value = 0;
int LampNum = 1;

int Amplitude[12] = {};

bool inMenu = true;
int i,currentOption = 0;

int severity = 9;
long New;
void adjust_severity(int Min, int Max)
{
  if(severity < 0){lcd.setCursor(0,0);lcd.print('-');}else{lcd.setCursor(0,0);lcd.print(' ');}
       lcd.setCursor(0,1);
       lcd.print(abs(severity));
       if(New > Position){severity--;Position = New;clear_output();}if(New < Position){severity++;Position = New;clear_output();}
       if(digitalRead(Up) == HIGH){severity++;delay(80);clear_output();}
       if(digitalRead(Down) == HIGH){severity--;delay(80);clear_output();}
       if(severity < Min){severity = Min;}
       if(severity > Max){severity = Max;}
       if(abs(severity) <10){lcd.setCursor(1,1);lcd.print(" ");}
}


void adjust_value(int Min, int Max)
{
  if(severity < 0){lcd.setCursor(0,0);lcd.print('-');}else{lcd.setCursor(0,0);lcd.print(' ');}
       lcd.setCursor(0,1);
       lcd.print(abs(Value));
       if(New > Position){Value--;Position = New;lcd.write("   ");}if(New < Position){Value++;Position = New;lcd.write("   ");}
       if(Value < Min){Value = Min;}
       if(Value > Max){Value = Max;}
       if(abs(Value) <10){lcd.setCursor(1,1);lcd.print(" ");}
}


int t = 0;//global time
void loop() {
  if(t > 1000000){t=0;}//resetting global time
  
  New = encoder.read();
  //main menu options
  if(inMenu == true){
  if(digitalRead(Up)==HIGH){i--;delay(150);lcd.clear();}
  if(digitalRead(Down)==HIGH){i++;delay(150);lcd.clear();}

  if(i < 0){i = 11;}
  if(i >= 12){i = 0;}
  lcd.setCursor(0,0);
  lcd.print("Choose Function");
  lcd.setCursor(0,1);
  lcd.print(functions[i]);

  if(digitalRead(Right) == HIGH){currentOption = i;inMenu = false;lcd.clear();}
  
  
  }
  else
  {
    //Random display
    if(i == 0){

       //toggle random time
       if(digitalRead(Up) == HIGH){randomTimeOn = false;}
       if(digitalRead(Down) == HIGH){randomTimeOn = true;}
       
       if(randomTimeOn == true)
       {
       lcd.clear();
       lcd.setCursor(15,0);
       lcd.print("R");
       lcd.setCursor(15,1);
       lcd.print("A");
       for(int x = 0; x <12; x++){CS[x] = random(0,16);}//choose random numbers
       OutputColourSpectrum();
       DisplayColourSpectrum();
       delay(randomTime);
       }
       
       if(randomTimeOn == false)
       {
       if(digitalRead(Right) == HIGH || digitalRead(Left) == HIGH){for(int x = 0; x <12; x++){CS[x] = random(0,16);lcd.clear();}}
       lcd.setCursor(15,0);
       lcd.print("R");
       lcd.setCursor(15,1);
       lcd.print("A");
       OutputColourSpectrum();
       DisplayColourSpectrum();
       }
       

       if(digitalRead(Enter) == HIGH){inMenu = true;clear_output();}//return to main menu

    }
    if(i == 1){//control 
      
       adjust_value(0, 16);

       if(digitalRead(Up) == true){Value++; delay(100);}
       if(digitalRead(Down) == true){Value--; delay(100);}
       if(Value > 16){Value = 16;}else if(Value < 0){Value = 0;}

       if(digitalRead(Right) == true){LampNum++; delay(100);}
       if(digitalRead(Left) == true){LampNum--; delay(100);}
       if(LampNum > 12){LampNum = 12;}else if(LampNum < 1){LampNum = 1;}

       if(digitalRead(Choose) == HIGH)
       {
       CS[LampNum-1] = Value;
       }

       if(Value<=8 && Value >0){lcd.setCursor(LampNum+1,1);lcd.write(Value-1);lcd.setCursor(LampNum+1,0);lcd.write(254);delay(80);}
       else if(Value > 8 && Value <=16){lcd.setCursor(LampNum+1,1);lcd.write(255);lcd.setCursor(LampNum+1,0);lcd.write(Value-1);delay(80);}
       else{lcd.setCursor(LampNum+1,1);lcd.write(254);lcd.setCursor(LampNum+1,0);lcd.write(254);delay(80);}
      
       
       OutputColourSpectrum();
       DisplayColourSpectrum();

     

       if(digitalRead(Enter) == HIGH){inMenu = true;clear_output();}//return to main menu
    }
    if(i == 2){//protan
        adjust_severity(0, 8);
       
       if(digitalRead(Choose) == HIGH){daylight();}
       else
       {
       
       if(severity == 0){//protan
       CS[2] = 12;
       CS[3] = 11;
       CS[4] = 10;
       CS[5] = 8;
       CS[6] = 12;
       CS[7] = 14;
       CS[8] = 16;
       CS[9] = 16;
       }
       if(severity == 1){//protan
       CS[2] = 7;
       CS[3] = 12;
       CS[4] = 8;
       CS[5] = 13;
       CS[6] = 14;
       CS[7] = 14;
       CS[8] = 16;
       CS[9] = 16;
       }
       if(severity == 2){//protan
       CS[2] = 5;
       CS[3] = 8;
       CS[4] = 8;
       CS[5] = 13;
       CS[6] = 14;
       CS[7] = 14;
       CS[8] = 16;
       CS[9] = 16;
       }
        if(severity == 3){//protan
       CS[2] = 3;
       CS[3] = 6;
       CS[4] = 8;
       CS[5] = 13;
       CS[6] = 14;
       CS[7] = 16;
       CS[8] = 16;
       CS[9] = 16;
       }
       if(severity == 4){//protan
       CS[2] = 1;
       CS[3] = 4;
       CS[4] = 8;
       CS[5] = 13;
       CS[6] = 14;
       CS[7] = 16;
       CS[8] = 16;
       CS[9] = 16;
       }
       if(severity == 5){//protan
       CS[3] = 2;
       CS[4] = 5;
       CS[5] = 13;
       CS[6] = 14;
       CS[7] = 16;
       CS[8] = 16;
       CS[9] = 16;
       }
       if(severity == 6){//protan
       CS[3] = 1;
       CS[4] = 3;
       CS[5] = 12;
       CS[6] = 14;
       CS[7] = 16;
       CS[8] = 16;
       CS[9] = 16;
       }
       if(severity == 7){//protan
       CS[4] = 1;
       CS[5] = 6;
       CS[6] = 14;
       CS[7] = 16;
       CS[8] = 16;
       CS[9] = 16;
       }
       if(severity == 8){//protan
       CS[6] = 16;
       CS[7] = 16;
       CS[8] = 16;
       CS[9] = 16;
       }
       
       OutputColourSpectrum();
       DisplayColourSpectrum();
       }
  
       if(digitalRead(Enter) == HIGH){inMenu = true;clear_output();}//return to main menu
    }
    if(i == 3){//deutan

       adjust_severity(0,8);

       if(digitalRead(Choose) == HIGH){daylight();}
       else
       {
     
       if(severity == 0){
       CS[2] = 14;
       CS[3] = 11;
       CS[4] = 14;
       CS[5] = 12;
       CS[6] = 14;
       CS[8] = 16;
       CS[9] = 13;
       }
       if(severity == 1){
       CS[2] = 12;
       CS[3] = 11;
       CS[4] = 13;
       CS[5] = 12;
       CS[6] = 13;
       CS[8] = 16;
       CS[9] = 13;
       }
       if(severity == 2){
       CS[2] = 9;
       CS[3] = 13;
       CS[4] = 14;
       CS[5] = 12;
       CS[6] = 12;
       CS[8] = 16;
       CS[9] = 13;
       }
       if(severity == 3){
       CS[2] = 4;
       CS[3] = 14;
       CS[4] = 14;
       CS[5] = 12;
       CS[6] = 12;
       CS[8] = 16;
       CS[9] = 13;
       }
       if(severity == 4){
       CS[2] = 1;
       CS[3] = 13;
       CS[4] = 15;
       CS[5] = 13;
       CS[6] = 12;
       CS[8] = 16;
       CS[9] = 13;
       }
       if(severity == 5){
       CS[3] = 11;
       CS[4] = 16;
       CS[5] = 12;
       CS[6] = 12;
       CS[8] = 16;
       CS[9] = 13;
       }
       if(severity == 6){
       CS[3] = 8;
       CS[4] = 16;
       CS[5] = 15;
       CS[6] = 8;
       CS[8] = 16;
       CS[9] = 15;
       }
       if(severity == 7){
       CS[3] = 4;
       CS[4] = 16;
       CS[5] = 15;
       CS[6] = 4;
       CS[8] = 16;
       CS[9] = 15;
       }
       if(severity == 8){
       CS[4] = 16;
       CS[5] = 16;
       CS[8] = 16;
       CS[9] = 16;
       }

       OutputColourSpectrum();
       DisplayColourSpectrum();
       }
       
       if(digitalRead(Enter) == HIGH){inMenu = true;clear_output();severity = 16;}//return to main menu
    }
    if(i == 4){//tritan

       adjust_severity(0,8);

       if(digitalRead(Choose) == HIGH){daylight();}
       else
       {

        
       CS[1] = 13;
       CS[2] = 16;
       CS[7] = 16;
       
       OutputColourSpectrum();
       DisplayColourSpectrum();
       }
       if(digitalRead(Enter) == HIGH){inMenu = true;clear_output();}//return to main menu
    }
    if(i == 5){//colour correct
       adjust_severity(0, 6);

       if(digitalRead(Choose) == HIGH){daylight();}
       else
       {
       if(severity == 0){daylight();}
       if(severity == 1){//correction spectrum
       CS[11] = 0;
       CS[10] = 12;
       CS[9] = 12;
       CS[8] = 12;
       CS[7] = 10;
       CS[6] = 16;
       CS[5] = 6;
       CS[4] = 8;
       CS[3] = 11;
       CS[2] = 16;
       CS[1] = 16;
       CS[0] = 0;
       }
       if(severity == 2){//correction spectrum
       CS[11] = 0;
       CS[10] = 15;
       CS[9] = 12;
       CS[8] = 0;
       CS[7] = 0;
       CS[6] = 14;
       CS[5] = 0;
       CS[4] = 2;
       CS[3] = 3;
       CS[2] = 14;
       CS[1] = 16;
       CS[0] = 0;
       }
        if(severity == 3){//correction spectrum
       CS[11] = 0;
       CS[10] = 0;
       CS[9] = 16;
       CS[8] = 16;
       CS[7] = 16;
       CS[6] = 16;
       CS[5] = 0;
       CS[4] = 0;
       CS[3] = 0;
       CS[2] = 16;
       CS[1] = 16;
       CS[0] = 0;
       }
        if(severity == 4){//correction spectrum
       CS[11] = 0;
       CS[10] = 0;
       CS[9] = 0;
       CS[8] = 16;
       CS[7] = 0;
       CS[6] = 16;
       CS[5] = 0;
       CS[4] = 0;
       CS[3] = 0;
       CS[2] = 16;
       CS[1] = 0;
       CS[0] = 0;
       }
     
       if(severity == 5){//correction spectrum
       CS[11] = 0;
       CS[10] = 15;
       CS[9] = 12;
       CS[8] = 0;
       CS[7] = 0;
       CS[6] = 5;
       CS[5] = 0;
       CS[4] = 2;
       CS[3] = 3;
       CS[2] = 14;
       CS[1] = 16;
       CS[0] = 0;
       }
       
       if(severity == 6){//enhance
       CS[2] = 12;
       CS[3] = 11;
       CS[4] = 10;
       CS[5] = 8;
       CS[6] = 12;
       CS[7] = 14;
       CS[8] = 16;
       CS[9] = 16;
       }
       
       OutputColourSpectrum();
       DisplayColourSpectrum();
       }
  
       if(digitalRead(Enter) == HIGH){inMenu = true;clear_output();}//return to main menu
    }

    
    if(i == 6){//Miscellaneous
       adjust_severity(-2, 8);

       if(digitalRead(Choose) == HIGH){daylight();}
       else
       {
       if(severity == -2){//colour equalised
       CS[11] = 3;
       CS[10] = 12;
       CS[9] = 16;
       CS[8] = 16;
       CS[7] = 13;
       CS[6] = 16;
       CS[5] = 9;
       CS[4] = 4;
       CS[3] = 10;
       CS[2] = 10;
       CS[1] = 12;
       CS[0] = 16;
       }
       if(severity == -1){//white led simulator
       CS[11] = 0;
       CS[10] = 1;
       CS[9] = 4;
       CS[8] = 16;
       CS[7] = 8;
       CS[6] = 14;
       CS[5] = 14;
       CS[4] = 12;
       CS[3] = 8;
       CS[2] = 5;
       CS[1] = 2;
       CS[0] = 0;
       }    
       
        if(severity == 0){
       CS[11] = 0;
       CS[10] = 0;
       CS[9] = 1;
       CS[8] = 2;
       CS[7] = 3;
       CS[6] = 4;
       CS[5] = 5;
       CS[4] = 7;
       CS[3] = 9;
       CS[2] = 11;
       CS[1] = 12;
       CS[0] = 13;
       }  
       if(severity == 1){
       CS[11] = 0;
       CS[10] = 2;
       CS[9] = 3;
       CS[8] = 4;
       CS[7] = 5;
       CS[6] = 6;
       CS[5] = 7;
       CS[4] = 8;
       CS[3] = 9;
       CS[2] = 10;
       CS[1] = 11;
       CS[0] = 11;
       }  
       if(severity == 2){
       CS[11] = 2;
       CS[10] = 3;
       CS[9] = 4;
       CS[8] = 5;
       CS[7] = 6;
       CS[6] = 7;
       CS[5] = 8;
       CS[4] = 9;
       CS[3] = 10;
       CS[2] = 11;
       CS[1] = 11;
       CS[0] = 10;
       } 
       if(severity == 3){
       CS[11] = 3;
       CS[10] = 4;
       CS[9] = 5;
       CS[8] = 6;
       CS[7] = 7;
       CS[6] = 8;
       CS[5] = 9;
       CS[4] = 11;
       CS[3] = 11;
       CS[2] = 10;
       CS[1] = 9;
       CS[0] = 8;
       }     
       if(severity == 4){
       CS[11] = 4;
       CS[10] = 5;
       CS[9] = 6;
       CS[8] = 7;
       CS[7] = 9;
       CS[6] = 10;
       CS[5] = 11;
       CS[4] = 12;
       CS[3] = 11;
       CS[2] = 9;
       CS[1] = 8;
       CS[0] = 7;
       }    
       if(severity == 5){
       CS[11] = 5;
       CS[10] = 6;
       CS[9] = 7;
       CS[8] = 8;
       CS[7] = 10;
       CS[6] = 12;
       CS[5] = 12;
       CS[4] = 11;
       CS[3] = 11;
       CS[2] = 10;
       CS[1] = 9;
       CS[0] = 8;
       }    
       if(severity == 6){
       CS[11] = 5;
       CS[10] = 8;
       CS[9] = 9;
       CS[8] = 10;
       CS[7] = 10;
       CS[6] = 12;
       CS[5] = 12;
       CS[4] = 10;
       CS[3] = 9;
       CS[2] = 8;
       CS[1] = 8;
       CS[0] = 7;
       }    
       if(severity == 7){
       CS[11] = 8;
       CS[10] = 9;
       CS[9] = 11;
       CS[8] = 12;
       CS[7] = 12;
       CS[6] = 11;
       CS[5] = 10;
       CS[4] = 9;
       CS[3] = 7;
       CS[2] = 5;
       CS[1] = 1;
       CS[0] = 0;
       } 
       if(severity == 8){
       CS[11] = 8;
       CS[10] = 12;
       CS[9] = 14;
       CS[8] = 12;
       CS[7] = 11;
       CS[6] = 10;
       CS[5] = 8;
       CS[4] = 6;
       CS[3] = 5;
       CS[2] = 3;
       CS[1] = 1;
       CS[0] = 0;
       }   
         
            
       
       OutputColourSpectrum();
       DisplayColourSpectrum();
       }
      
       if(digitalRead(Enter) == HIGH){inMenu = true;clear_output();}//return to main menu
    }

    
    if(i == 7){//monochrome
       adjust_severity(0,8);

       if(digitalRead(Right) == true){CS[LampNum-1] = 0; LampNum++; delay(100);}
       if(digitalRead(Left) == true){CS[LampNum-1] = 0; LampNum--; delay(100);}
       if(LampNum > 12){LampNum = 12;}else if(LampNum < 1){LampNum = 1;}

      if(digitalRead(Choose) == HIGH)
       {
       daylight();
       }
       else
       {
       for(int i = 0; i <= 12; i++){CS[i] = severity;}
       CS[LampNum-1] = 16;
       OutputColourSpectrum();
       DisplayColourSpectrum();
       }
       
       if(digitalRead(Enter) == HIGH){inMenu = true;clear_output();}//return to main menu
    }
    if(i == 8){//fluctuating
       t++;
       delay(20);
   
       Amplitude[1] = 127*(sin(0.0174533*t)+1);
       Amplitude[2] = 127*(sin(0.0174533*t+2.0944)+1);
       Amplitude[3] = 127*(sin(0.0174533*t+2.0944*2)+1);
       
       analogWrite(10,Amplitude[1]);
       analogWrite(6,Amplitude[2]);
       analogWrite(4,Amplitude[3]);
      
       lcd.setCursor(0,0);
       lcd.print(Amplitude[1]);
       lcd.setCursor(0,1);
       lcd.print(Amplitude[2]);

       
       if(digitalRead(Enter) == HIGH){inMenu = true;clear_output();}//return to main menu
    }
    if(i == 9){//strobe

       delay(10);
       CS[5] = 0;
       CS[8] = 16;
       OutputColourSpectrum();
       DisplayColourSpectrum();
       
       delay(10);
       CS[5] = 16;
       CS[8] = 0;
       OutputColourSpectrum();
       DisplayColourSpectrum();
       
       if(digitalRead(Enter) == HIGH){inMenu = true;clear_output();}//return to main menu
    }
    if(i == 10){//anomalyscope
       if(digitalRead(Up) == HIGH){Amplitude[11]+=2;}
       if(digitalRead(Down) == HIGH){Amplitude[11]-=2;}
       if(Amplitude[11] > 255){Amplitude[11] = 255;}
       if(Amplitude[11] < 0){Amplitude[11] = 0;}

       adjust_value(0,255);

       lcd.setCursor(4,1);
       lcd.print("Red-Green");
       lcd.setCursor(0,0);
       lcd.print(Amplitude[11]);
       lcd.setCursor(4,0);
       lcd.print("Yellow");
       
       if(digitalRead(Choose) == LOW)
       {
       analogWrite(6,Value);
       analogWrite(10,255-Value);
       analogWrite(7,0);
       }
       else
       {
       analogWrite(6,0);
       analogWrite(10,0);
       analogWrite(7,Amplitude[11]);
       }
       if(digitalRead(Enter) == HIGH){inMenu = true;clear_output();}//return to main menu
    }
    if(i == 11){//pride
       t++;
       delay(20);

       adjust_severity(-10,10);
       if(severity == 0){severity = 1;}
       double shift;
       if(severity < 1){shift = 0.628319*severity;}
       if(severity >= 1){shift = 0.628319/severity;}       
       
       double Speed = 0.0174533;
       Amplitude[1] = 127*(sin(Speed*t)+1);
       Amplitude[2] = 127*(sin(Speed*t+shift)+1);
       Amplitude[3] = 127*(sin(Speed*t+shift*2)+1);
       Amplitude[4] = 127*(sin(Speed*t+shift*3)+1);
       Amplitude[5] = 127*(sin(Speed*t+shift*4)+1);
       Amplitude[6] = 127*(sin(Speed*t+shift*5)+1);
       Amplitude[7] = 127*(sin(Speed*t+shift*6)+1);
       Amplitude[8] = 127*(sin(Speed*t+shift*7)+1);
       Amplitude[9] = 127*(sin(Speed*t+shift*8)+1);
       Amplitude[10]= 127*(sin(Speed*t+shift*9)+1);
      
       analogWrite(11,Amplitude[10]);
       analogWrite(10,Amplitude[9]);
       analogWrite(9,Amplitude[8]);
       analogWrite(8,Amplitude[7]);
       analogWrite(7,Amplitude[6]);
       analogWrite(6,Amplitude[5]);
       analogWrite(5,Amplitude[4]);
       analogWrite(4,Amplitude[3]);
       analogWrite(3,Amplitude[2]);
       analogWrite(2,Amplitude[1]);
      
       lcd.setCursor(0,0);
       lcd.print(severity);


       
       if(digitalRead(Enter) == HIGH){inMenu = true;clear_output();}//return to main menu
    }

//    return to main menu

  if(digitalRead(Enter) == HIGH){inMenu = true;lcd.clear();}
 
  }

  Serial.print("Encoder Position = ");
  Serial.println(New);
  Serial.println(digitalRead(Up));
  Serial.println(digitalRead(Down));
  Serial.println(digitalRead(Left));
  Serial.println(digitalRead(Right));
  Serial.println(digitalRead(Enter));
  Serial.println(digitalRead(Choose));
  Serial.println();


  
}
