#define K_DELAY_STEP 10
#define WAVES_DELAY 10
#define WAVES_DEPTH 255

#define K_TOWARDS_DOWN 0
#define K_TOWARDS_UP 1
#define K_TOWARDS_RIGHT 2
#define K_TOWARDS_LEFT 3
#define K_TOWARDS_FRONT 4
#define K_TOWARDS_BACK 5

#define K_DELAY_TRANSLATION 10
#define K_DELAY_CUBE_SIZING 30

int Lpin = 10;
int CLKpin = 13;
int Dpin = 11;
int CLRpin = 8;

int Button1State;
int Button2State;
int mode=14;
int Button1 = 7;
int Button2 = 2;

int LED1 = 5;
int LED2 = 4;

char str[] ="HOLA";
int size_str= sizeof(str);
void setup() {
Serial.begin(9600); // open the serial port at 9600 bps:
  // put your setup code here, to run once:
  pinMode (Lpin, OUTPUT);
  pinMode (CLKpin, OUTPUT);
  pinMode (Dpin, OUTPUT);
  pinMode (CLRpin, OUTPUT);
  
  pinMode (Button1, INPUT_PULLUP); // Top button
  attachInterrupt(digitalPinToInterrupt(Button1), interrupt_top_button, RISING);
  pinMode (Button2, INPUT); // Bottom button 
  
  pinMode (LED1, OUTPUT); // Yellow one
  pinMode (LED2, OUTPUT); // Green one
  
  digitalWrite(CLRpin, 1);
  digitalWrite(LED2, 1);

}

void loop() {
switch (mode) {
  case 0:
    sandwich();    
  break;
  case 1:
    cross_updown();
  break;
  case 2:
    monolite();
  break;
  case 3:
    phantom();
  break;
  case 4:
    rain_downup();
  break;
  case 5:
      cube_x();
  break;
  case 6:
      square_Turning();
  break;
  case 7:
      cube_stripes();
  break;
  case 8:
      outline_shrink();
  break; 
  case 9:
      cube_explosion();
  break; 
  case 10:
      cube_explosion();
  break;  
  case 11:
      cube_belt_wipe();
  break;
  case 12:
      cube_waves();
  break;
  case 13:
      cube_stars();
  break;
  case 14:
      cube_rain();
  break;
  case 15:
      cube_px_up_down();
  break;
  case 16:
      wall_moving();
  break;
  case 17:
      cube_sizing();
  break;
  case 18:
      print_string(str,size_str);
  break;
  case 19: 
      progessive_full();
  break;
  case 20: 
      growing_diag();
  break;
  case 21: 
      displacement_spring();
  break;
  case 22: 
      circle();
  break;
  case 23: 
      diamond();
  break;
  case 24: 
      hourglass();
  break;
  case 25: 
      windmill();
  break;
  case 26: 
      rotatory_allien();
  break;     
  default:
    // statements
  break;
}
mode ++;
if(mode >=26)
  mode =0;
}

void interrupt_top_button()
{
  static unsigned long last_interrupt_time = 0;
  unsigned long interrupt_time = millis();
  // If interrupts come faster than 200ms, assume it's a bounce and ignore
  if (interrupt_time - last_interrupt_time > 600)
  {
     mode++;
     if(mode>=22)
       mode=0;
  }
 last_interrupt_time = interrupt_time;

  
}
