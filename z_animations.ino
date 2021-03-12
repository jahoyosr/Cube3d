/*------------ Private functions -----------------*/
static void send_frame(byte my_frame[])
{
    digitalWrite(Lpin, 0);
    for(int i=0;i<9;++i)
    {
     shiftOut(Dpin, CLKpin, MSBFIRST, my_frame[i]); //Cathode layer
    }
     digitalWrite(Lpin, 1);
}


static void send_frame_multiplex_equal(byte temp_array[][9],int number_of_rows, int delay_ms)
{
      int factor = (delay_ms/(number_of_rows+1))+1;
      for(int k = 0;k<number_of_rows*factor;++k){
        send_frame(temp_array[k%number_of_rows]);
      }      
}
/*------------ Public functions -----------------*/

void sandwich()
{
   byte temp_array[9];
   for (int i = 0; i <= 5; i++)
     { 
       temp_array[0]= sandwich_mx_z[i];
       memcpy(temp_array+1, sandwich_mx_x, sizeof(sandwich_mx_x));
       send_frame(temp_array);
       // Non-blocking delay to detect the button request 
       delay(70);
     }
}

void cross_updown()
{
   byte temp_array[9];
   int i;
   for (i = 0; i < 9; ++i)
   { 
       temp_array[0]= cross_updown_mx_z[i];
       memcpy(temp_array+1, cross_updown_mx_x[0], sizeof(cross_updown_mx_x[0]));
       send_frame(temp_array);
       delay(100);
   }

   temp_array[0]= cross_updown_mx_z[8];
   memcpy(temp_array+1, cross_updown_mx_x[1], sizeof(cross_updown_mx_x[1]));
   send_frame(temp_array);
   delay(100);

   for (i = 8; i >=0; --i)
   { 
       temp_array[0]= cross_updown_mx_z[i];
       memcpy(temp_array+1, cross_updown_mx_x[0], sizeof(cross_updown_mx_x[0]));
       send_frame(temp_array);
       delay(100);
   }

   temp_array[0]= cross_updown_mx_z[0];
   memcpy(temp_array+1, cross_updown_mx_x[1], sizeof(cross_updown_mx_x[1]));
   send_frame(temp_array);
   delay(100);
}

void monolite()
{
   byte temp_array[9];
   byte temp_array2d[2][9]; 
  temp_array2d[0][0]= 15;
  temp_array2d[1][0]= 240;
   for (int i =0; i<2; ++i)
   {
       memcpy(temp_array2d[i]+1, monolite_mx[1], sizeof(monolite_mx[1]));      
   }
      
   for (int i = 0; i <8; ++i)
   { 
       temp_array[0]= layer_ascending_mx[i];
       memcpy(temp_array+1, monolite_mx[0], sizeof(monolite_mx[0]));
       send_frame(temp_array);
       delay(70);
       send_frame(clear_array);
       delay(70);
   }
 

   for (int i = 0; i<10; ++i)
   {
      send_frame_multiplex_equal(temp_array2d,2,70);
      send_frame(clear_array);
      delay(70);
   }

   for (int i = 7; i>=0;--i)
   { 
       temp_array[0]= layer_ascending_mx[i];
       memcpy(temp_array+1, monolite_mx[0], sizeof(monolite_mx[0]));
       send_frame(temp_array);
       delay(70);
       send_frame(clear_array);
       delay(70);
   }  
   for (int i = 0; i<10; ++i)
   {
      send_frame_multiplex_equal(temp_array2d,2,70);
      send_frame(clear_array);
      delay(70);
   }
}

void phantom()
{
  byte temp_array[10][9];
  for(int j=0;j<10;++j)
  {
    memcpy(temp_array[j], phantom_mx[j], sizeof(temp_array[0]));
    send_frame(temp_array[j]);
    delay(100);
    send_frame(clear_array);
    delay(100);       
  }
}

void rain_downup()
{
   byte temp_array[9];
   for (int j= 0; j<6;++j)
   {
     for (int i = 0; i < 7; ++i)
     { 
         temp_array[0]= layer_ascending_mx[i];
         memcpy(temp_array+1, rain_downup_mx[j], sizeof(rain_downup_mx[j]));
         send_frame(temp_array);
         delay(50);
     }
   }
}
void square_Turning()
{
   int counter = 0;
   int frame_nb=0;
    for (int i = 0; i < 112; ++i)
    {
      if(i%8==0)
      {
        counter++;
        i=8*frame_nb;
        if(counter>5)
        {
          counter = 0;
          frame_nb++;  
        }        
      }
      send_frame(square_mx[i]);
    }    
}

void cube_stripes()
{
   byte temp_array[8][9];
   byte temp_array_2[8][9];
   memcpy(temp_array , stripes_mx, sizeof(temp_array));
   memcpy(temp_array_2 , stripes_mx, sizeof(temp_array_2));
   
  for (int j=0;j<=8;++j)
  {   
      for (int i = 0; i < 8; ++i)
      {
        
        if(i%2==0)
        {
           temp_array[i][8]|= ( 1 << j );
        }
        else
        {
          temp_array[i][1]|= ( 1 << 7-j );
        }
        send_frame(temp_array[i]);
      } 
      delay(15);
  }  
  for(int k=1; k<7;++k)
  {
    for (int j=0;j<8;++j)
    {   
        for (int i = 0; i < 8; ++i)
        {
          if(i%2==0)
          {
             temp_array_2[i][k+1]|= ( 1 << j );
          }
          else
          {
             temp_array_2[i][7-k+1]|= ( 1 << j );
          }
          send_frame(temp_array_2[i]);
          
        } 
        delay(15);      
    }
  }
}

void cube_x()
{
    for (int i = 0; i <=8 ; ++i)
    {
      for(int k=0;k<50;++k)
      {
        if(i>=4)
        {
          for(int j=0;j<8-i;++j)
          {          
            send_frame(cubex_mx[j]);
          }
        }
        else
        {
          for(int j=0;j<i;++j)
          {          
            send_frame(cubex_mx[j]);
          }
        }        
      }
      
    }
    send_frame(clear_array); 
    delay(500); 
}
void outline_shrink()
{
  for(int k=0;k<4;++k)
  { 
   for(int j =0; j<30; ++j)
   {
    if(k==3)
    {
      for (int i = 0; i <3 ; ++i)
      {
        send_frame(ol_shrink_mx[9]);
      }
    }
    else
    {
      for (int i = k*3; i <k*3+3 ; ++i)
      {
        send_frame(ol_shrink_mx[i]);
      }
    }
   }
  }
  for(int k=3;k>0;--k)
  { 
   for(int j =0; j<30; ++j)
   {
    if(k==3)
    {
      for (int i = 0; i <3 ; ++i)
      {
        send_frame(ol_shrink_mx[9]);
      }
    }
    else
    {
      for (int i = (k+1)*3-1; i >(k+1)*3-4 ; --i)
      {
        send_frame(ol_shrink_mx[i]);
      }
    }
   }
  }
}

void cube_explosion()
{
  byte temp_array[9];
  memcpy(temp_array , explosion_mx[0], sizeof(temp_array));
  
  byte led_state = 24;
  for (int i = 0; i <= 4; ++i){
      for (int j = 3; j <= (i+3); ++j) {
        for (int k = 3; k <= (i+3); ++k){
            temp_array[0] = (1<<j)|(1<<7-j);
            temp_array[8-k]=led_state;
            temp_array[k+1]=led_state;
            send_frame(temp_array);
      }

    }
    delay(9*(3*i+1));
    led_state |= (1 << (3-i)) | (1 << (4+i));    
  }
  for (int i = 0; i <= 4; i++){
    led_state &= ~((1 << (3-i)) | (1 << (4+i)));
    for (int j = 3; j <= (i+3); j++) {
      for (int k = 3; k <= (i+3); k++){
            temp_array[0] = (1<<j)|(1<<7-j);
            temp_array[8-k]=led_state;
            temp_array[k+1]=led_state;
            send_frame(temp_array);
         
      }
    }
    delay(9*(3*i+1));
  }
delay(50);
 
}


void cube_belt_wipe()
{
  byte temp_array[9];
  memcpy(temp_array , belt_wipe_mx, sizeof(temp_array));
  for (int k = 7; k >= 0; --k){
    temp_array[0]|=(1<<k);
    send_frame(temp_array);
    for (int i = 1; i < 7; i++)
    { 
      temp_array[i+1] |= 129;
      send_frame(temp_array);
    }
    delay(50);
  }

  for (int k = 7; k >= 0; --k){
    for (int i = 0; i < 8; i++)
    { 
      temp_array[0]&=~(1<<k);
      send_frame(temp_array);
    }
    delay(50);
  }
  
}


void move_x_rev( int x1, int y1, int x2, int y2 , byte *current_frame)
{
  for (int layer = y1; layer <= 1; layer++) {
    for (int j = 0; j < 7; j++){
      for (int k = x1; k <= x2; k++) {
        if ((current_frame[j+2] & (1 << k)))
        {
          current_frame[j+1]|= (1 << k);
          send_frame(current_frame);
          //delay(50);
          current_frame[j+2] &= ~(1 << k);        
          send_frame(current_frame);
          //delay(50);
        } 
        else 
        {
          current_frame[j+1] &= ~(1 << k);
          send_frame(current_frame);
          //delay(50);
        }
      }

    }
  }
}

void cube_waves( void )
{
   byte temp_array[8][9];
   byte layer_array[]={16,32,64,128,128,64,32,16,8,4,2,1,1,2,4,8,16,32,64,128,128,64,32,16};
   byte raw_array[]={24,60,126,255,255,126,60,24,24,60,126,255,255,126,60,24,24,60,126,255,255,126,60,24};
   int head_layer = 1;
   int head_raw=1;
   memcpy(temp_array , sinus_mx2, sizeof(temp_array));
   for(int k=0;k<16;++k)
   {
      for(int j = 0 ; j<=5;++j)
      {
         for(int i = 0; i<8;++i)
         {
           send_frame(temp_array[i]);
           if(j==5)
           {
              temp_array[i][0]= layer_array[head_layer+i];
              temp_array[i][i+1]= raw_array[head_raw+i];              
           }
         }    
      }
      head_layer++;
      head_raw++;
   }
}
 
void cube_stars( void )
{
  byte temp_array[]={0,0,0,0,0,0,0,0,0};
  
  for (int j = 1; j < 2; j++){
    for (int loops = 0; loops < 18; loops++){
      send_frame(clear_array);
      memcpy(temp_array , clear_array, sizeof(temp_array));
      for (int i = 0; i< j; i++){
        int randx = random(8);
        int randy = random(8);
        int randz = random(8);
        
        temp_array[0]=(1<<randy);
        temp_array[randx] = (1<<randz);
        send_frame(temp_array);
      }
      delay(5);
    }
  }
}

void cube_rain( void )
{
  byte temp_array[8][9];
  int randx;
  int randz;
  for (int layer = 0; layer < 80; layer++){
      memcpy(temp_array[layer%8] , clear_array, sizeof(clear_array));
      randx = random(8)+1;
      randz = random(8);             
      temp_array[layer%8][randx] = (1<<randz);
     /* randx = random(8)+1;
      randz = random(8);        
      temp_array[layer%8][randx] = (1<<randz);*/
      temp_array[layer%8][0]= 128;

      for (int i = 0; i< 56; i++){       
        send_frame(temp_array[i%8]);
      }
      
      for(int k=0;k<8;++k)
      {
        temp_array[k][0]= (temp_array[k][0]>>1);
      }
      
    }
}


void cube_px_up_down()
{
    byte temp_array[4][9];
    memcpy(temp_array , cube_px_up_down_mx, sizeof(temp_array));
    pix_top_bottom(K_TOWARDS_DOWN,4,7,temp_array);
    pix_top_bottom(K_TOWARDS_UP,64,2,temp_array);
    pix_top_bottom(K_TOWARDS_DOWN,32,1,temp_array);
    pix_top_bottom(K_TOWARDS_UP,1,3,temp_array);
    pix_top_bottom(K_TOWARDS_DOWN,128,4,temp_array);
    pix_top_bottom(K_TOWARDS_UP,8,3,temp_array);
    pix_top_bottom(K_TOWARDS_DOWN,128,7,temp_array);
    pix_top_bottom(K_TOWARDS_UP,128,8,temp_array);
    

    pix_top_bottom(K_TOWARDS_DOWN,64,2,temp_array);
    pix_top_bottom(K_TOWARDS_UP,128,4,temp_array);
    pix_top_bottom(K_TOWARDS_DOWN,1,3,temp_array);
    pix_top_bottom(K_TOWARDS_UP,4,7,temp_array);
    pix_top_bottom(K_TOWARDS_DOWN,8,3,temp_array);
    pix_top_bottom(K_TOWARDS_UP,128,7,temp_array);
    pix_top_bottom(K_TOWARDS_DOWN,128,8,temp_array);
    pix_top_bottom(K_TOWARDS_UP,32,1,temp_array);

}

void pix_top_bottom(int towards,int cmd,int raw ,byte temp_array[][9])
{
  if(towards==K_TOWARDS_DOWN)
  {
    temp_array[1][raw]=cmd;
    for(int k = 0; k<8;++k)
    {
      for (int i = 0; i< 32; i++){       
          send_frame(temp_array[i%4]);
      }
      temp_array[0][raw]&= ~ temp_array[1][raw];    
      temp_array[1][0]= (1<<7-k);
    }
           
    temp_array[3][raw]|= temp_array[1][raw];
    temp_array[1][raw]=0;
  }
  else if(towards==K_TOWARDS_UP)
  { 
    temp_array[2][raw]=cmd;
    for(int k = 0; k<8;++k)
    {
      for (int i = 0; i< 32; i++){       
          send_frame(temp_array[i%4]);
      }
      temp_array[3][raw]&= ~ temp_array[2][raw];    
      temp_array[2][0]= (1<<k);
    }       
    temp_array[0][raw]|=  temp_array[2][raw];
    temp_array[2][raw]=0;
  }  
}

void wall_moving()
{
   byte temp_array[2][9];
   
   memcpy(temp_array[0] , cube_wall_moving_mx[0], sizeof(temp_array[0]));
   memcpy(temp_array[1] , cube_wall_moving_mx[1], sizeof(temp_array[0]));
   translation(K_TOWARDS_FRONT,temp_array,2,K_DELAY_TRANSLATION);

   memcpy(temp_array[0] , cube_wall_moving_mx[2], sizeof(temp_array[0]));
   memcpy(temp_array[1] , cube_wall_moving_mx[3], sizeof(temp_array[0]));
   translation(K_TOWARDS_BACK,temp_array,2,K_DELAY_TRANSLATION);

   memcpy(temp_array[0] , cube_wall_moving_mx[4], sizeof(temp_array[0]));
   translation(K_TOWARDS_DOWN,temp_array,1,K_DELAY_TRANSLATION*2);
   
   memcpy(temp_array[0] , cube_wall_moving_mx[5], sizeof(temp_array[0]));
   translation(K_TOWARDS_UP,temp_array,1,K_DELAY_TRANSLATION*2);

   memcpy(temp_array[0] , cube_wall_moving_mx[6], sizeof(temp_array[0]));
   memcpy(temp_array[1] , cube_wall_moving_mx[7], sizeof(temp_array[0]));
   translation(K_TOWARDS_RIGHT,temp_array,2,K_DELAY_TRANSLATION);
   
   memcpy(temp_array[0] , cube_wall_moving_mx[8], sizeof(temp_array[0]));
   memcpy(temp_array[1] , cube_wall_moving_mx[9], sizeof(temp_array[0]));
   translation(K_TOWARDS_LEFT,temp_array,2,K_DELAY_TRANSLATION);  
   

}

void translation(int movement, byte temp_array[][9],int number_of_rows, int delay_ms)
{
   
   switch(movement){
    case K_TOWARDS_DOWN:
      for(int i = 1;i<9;++i)
       {
          for(int k = 0;k<number_of_rows*delay_ms;++k){
            send_frame(temp_array[k%number_of_rows]);
          }

          for(int n=0;n<number_of_rows;++n)
          {

            temp_array[n][0] = temp_array[n][0]>>1;

          }
       }
         
    break;
    case K_TOWARDS_UP:
        for(int i = 1;i<9;++i)
       {
          for(int k = 0;k<number_of_rows*delay_ms;++k){
            send_frame(temp_array[k%number_of_rows]);
          }

          for(int n=0;n<number_of_rows;++n)
          {

            temp_array[n][0] = temp_array[n][0]<<1;
            
          }
       }
    break;
    case K_TOWARDS_RIGHT:
       for(int i = 1;i<9;++i)
       {
          for(int k = 0;k<number_of_rows*delay_ms;++k){
            send_frame(temp_array[k%number_of_rows]);
          }

          for(int n=0;n<number_of_rows;++n)
          {
            for(int j=8;j>=1;--j)
            {
              if(j==1)
              {
                temp_array[n][1]=0;
              }
              else
              {
                temp_array[n][j] = temp_array[n][j-1];
              }
            }
          }
       }
       
    break;
    case K_TOWARDS_LEFT:
       for(int i = 1;i<9;++i)
       {
          for(int k = 0;k<number_of_rows*delay_ms;++k){
            send_frame(temp_array[k%number_of_rows]);
          }

          for(int n=0;n<number_of_rows;++n)
          {
            for(int j=1;j<9;++j)
            {
              if(j==8)
              {
                temp_array[n][j]=0;
              }
              else
              {
              temp_array[n][j] = temp_array[n][j+1];
              }
            }
          }
       }   
    break;
    case K_TOWARDS_FRONT:
       for(int i = 1;i<9;++i)
       {
          for(int k = 0;k<number_of_rows*delay_ms;++k){
            send_frame(temp_array[k%number_of_rows]);
          }

          for(int n=0;n<number_of_rows;++n)
          {
            for(int j=1;j<9;++j)
            {
              temp_array[n][j] = temp_array[n][j]>>1;
            }
          }
       }
    break;
    case K_TOWARDS_BACK:
        for(int i = 1;i<9;++i)
       {
          for(int k = 0;k<number_of_rows*delay_ms;++k){
            send_frame(temp_array[k%number_of_rows]);
          }

          for(int n=0;n<number_of_rows;++n)
          {
            for(int j=1;j<9;++j)
            {
              temp_array[n][j] = temp_array[n][j]<<1;
            }
          }
       }
   
    break;
    default:
      /*NOP*/
    break;
   }
}

void send_frame_multiplex(byte temp_array[][9],int number_of_rows, int delay_ms)
{
      for(int k = 0;k<number_of_rows*delay_ms;++k){
        send_frame(temp_array[k%number_of_rows]);
      }      
}


void cube_sizing()
{
  byte temp_array[2][9];

  for(int k = 0; k<8 ;++k)
  {
    for(int i = 0; i<=12;i=i+2)
    {
       memcpy(temp_array[0] , cube_sizing_mx[i+(14*k)], sizeof(temp_array[0]));
       memcpy(temp_array[1] , cube_sizing_mx[(i+1)+(14*k)], sizeof(temp_array[0]));
        
       send_frame_multiplex(temp_array,2,K_DELAY_CUBE_SIZING);
    }
  
    for(int i = 0; i<=12;i=i+2)
    {
       memcpy(temp_array[0] , cube_sizing_mx[13+(14*k)-i], sizeof(temp_array[0]));
       memcpy(temp_array[1] , cube_sizing_mx[12+(14*k)-i], sizeof(temp_array[0]));
        
       send_frame_multiplex(temp_array,2,K_DELAY_CUBE_SIZING);
    }
    
  }
}

void letters_test()
{
  byte temp_array[1][9];

  for(int i=0;i<26;++i)
  {
      memcpy(temp_array[0] , letters_mx[i], sizeof(temp_array[0]));
      send_frame(temp_array[0]);
      delay(1000);
  }

}


void print_string(char prompt[],byte size_string)
{
  byte temp_array[9];
  int char_position;
  for(int i=0;i<size_string-1;++i)
  {
      char_position = prompt[i]-65;
      memcpy(temp_array , letters_mx[char_position], sizeof(temp_array));
      for(int j =0;j<8;++j)
      {        
        send_frame(temp_array);
        temp_array[0] = temp_array[0]>>1;
        delay(50);      
      }

  }
}

void progessive_full()
{
  byte temp_array[8][9];
  int nb_random;
  int column_random;
  int rows_random_1;
  int rows_random_2;

  // Copying the null arrays
  for(int j=0; j<8;++j)
  {
    memcpy(temp_array[j], progressive_full[j], sizeof(temp_array[0]));
  }

  // Randomizing the LEDs to turn on
   for(int i=0;i<40;++i)
  {
      for(int k=0;k<4;++k)
      {
        for(int n=0;n<2;++n)
        {
          nb_random = random(8);
          rows_random_1 = random(8);
          rows_random_2 = random(8);
          column_random = random(8);

          temp_array[column_random][rows_random_1+1]|= 1<<nb_random;
          temp_array[column_random][rows_random_2+1]|= 1<<nb_random;
       
        }        
      }

 
      for(int l =0;l<8;++l)
      {        
        send_frame(temp_array[l]);
      }
  }

// Full cube
  for(int j=0; j<8;++j)
  {
    for(int n=0;n<8;++n)
    {
      temp_array[j][n+1]=255;
    }
  }
   for(int p=0; p<2; ++p)
   {   
      for(int l =0;l<8;++l)
      {        
        send_frame(temp_array[l]);
      }
   }
  // Randomizing the LEDs to turn off
   for(int i=0;i<40;++i)
  {
      for(int k=0;k<4;++k)
      {
        for(int n=0;n<4;++n)
        {
          nb_random = random(8);
          rows_random_1 = random(8);
          rows_random_2 = random(8);
          column_random = random(8);

          temp_array[column_random][rows_random_1+1]&=~(1<<nb_random);
          temp_array[column_random][rows_random_2+1]&=~(1<<nb_random);
       
        }        
      }
   
      for(int l =0;l<8;++l)
      {        
        send_frame(temp_array[l]);
      }
   
  }
// Void cube
  for(int j=0; j<8;++j)
  {
      temp_array[j][0]=0;
  }
   for(int p=0; p<5; ++p)
   {   
      for(int l =0;l<8;++l)
      {        
        send_frame(temp_array[l]);
      }
   }

}

void growing_diag()
{
  byte temp_array[16][9];

 // Copying the starting arrays
  for(int j=0; j<8;++j)
  {
    memcpy(temp_array[j], growing_diag_mx[j], sizeof(temp_array[0]));
  } 
  
  for(int h=8;h<16;++h)
  {
    memcpy(temp_array[h], growing_diag_mx[7], sizeof(temp_array[0]));
  }

  for(int i=0;i<16;++i)
  {
      send_frame_multiplex_equal(temp_array,i,30);
      for(int j=0;j<i;++j)
      {
        temp_array[j][0]= temp_array[j][0]<<1;
      }
      
  }

  
  for(int j=0; j<8;++j)
  {
    memcpy(temp_array[j], temp_array[j+8], sizeof(temp_array[0]));
  } 

  for(int h=8;h<16;++h)
  {
    memcpy(temp_array[h], growing_diag_mx[h], sizeof(temp_array[0]));
  }

  for(int i=8;i<16;++i)
  {
      send_frame_multiplex_equal(temp_array,i,25);
      for(int j=0;j<i;++j)
      {
        temp_array[j][0]= temp_array[j][0]<<1;
      }  
  }
  
  for(int i=0;i<8;++i)
  {
      send_frame_multiplex_equal(temp_array,16,25);
      for(int j=0;j<16;++j)
      {
        temp_array[j][0]= temp_array[j][0]<<1;
      }  
  }  


}

void  displacement_spring()
{
  byte temp_array[8][9];
  // Copying the first row
  memcpy(temp_array[0], displacement_spring_mx[0], sizeof(temp_array[0]));
  
  for(int j=0;j<7;++j)
  {
    memcpy(temp_array[j+1], clear_array, sizeof(temp_array[0]));   
  }

  // Going up 1st step
  for(int i=0;i<8;++i)
  {
    send_frame_multiplex_equal(temp_array,8,6); 
    if(i<7)
    {
      memcpy(temp_array[i], displacement_spring_mx[(2*i)+1], sizeof(temp_array[0]));
      memcpy(temp_array[i+1], displacement_spring_mx[(2*i)+2], sizeof(temp_array[0]));
    }
    else
         send_frame_multiplex_equal(temp_array,8,1000); 
  }
  
  // Going up 2nd step
  for(int i=0;i<8;++i)
  { 
    if(i<7)
    {
      send_frame_multiplex_equal(temp_array,8,6);   

      for(int p=0;p<8;++p)
      {
       temp_array[i+1][p+1]+=temp_array[i][p+1];
      }  
      memcpy(temp_array[i], clear_array, sizeof(temp_array[0]));
    }
    else
      send_frame_multiplex_equal(temp_array,8,1000);     
  }      

  // Going down 1st step
  memcpy(temp_array[0], displacement_spring_mx2[0], sizeof(temp_array[0]));
  
  for(int j=0;j<7;++j)
  {
    memcpy(temp_array[j+1], clear_array, sizeof(temp_array[0]));   
  }

  // Going up 1st step
  for(int i=0;i<8;++i)
  {
    send_frame_multiplex_equal(temp_array,8,6); 
    if(i<7)
    {
      memcpy(temp_array[i], displacement_spring_mx2[(2*i)+1], sizeof(temp_array[0]));
      memcpy(temp_array[i+1], displacement_spring_mx2[(2*i)+2], sizeof(temp_array[0]));
    }
    else
         send_frame_multiplex_equal(temp_array,8,1000); 
  }
  
  // Going up 2nd step
  for(int i=0;i<8;++i)
  { 
    if(i<7)
    {
      send_frame_multiplex_equal(temp_array,8,6);   

      for(int p=0;p<8;++p)
      {
       temp_array[i+1][p+1]+=temp_array[i][p+1];
      }  
      memcpy(temp_array[i], clear_array, sizeof(temp_array[0]));
    }
    else
      send_frame_multiplex_equal(temp_array,8,1000);     
  }      

}

void  circle()
{
  byte temp_array[8][9];
  // Copying the mx
  for(int j=0;j<8;++j)
  {
    memcpy(temp_array[j], circle_mx[j], sizeof(temp_array[0]));   
  }

  send_frame_multiplex_equal(temp_array,8,1000);     

}

void  diamond()
{
  byte temp_array[8][9];
  // Copying the mx
  for(int j=0;j<8;++j)
  {
    memcpy(temp_array[j], diamond_mx[j], sizeof(temp_array[0]));   
  }

  send_frame_multiplex_equal(temp_array,8,1000);     

}


void  hourglass()
{
  byte temp_array[8][9];
  // Copying the mx
  for(int j=0;j<8;++j)
  {
    memcpy(temp_array[j], hourglass_mx[j], sizeof(temp_array[0]));   
  }

  send_frame_multiplex_equal(temp_array,8,1000);     

}

void rotatory_allien()
{
  byte temp_array[3][9];
  byte tmp1[9] = {24,0,0,0,8,16,0,0,0};
  byte tmp2[9] = {24,0,0,0,16,8,0,0,0};

  // First part
  for(int j=0;j<12;++j)
  {
    for(int i=0;i<2;++i)
    {

      memcpy(temp_array[i], rot_allien_mx[i+(3*j)], sizeof(temp_array[0]));
          
    }
    
    memcpy(temp_array[2], tmp1, sizeof(temp_array[0]));
    send_frame_multiplex_equal(temp_array,3,20);

    memcpy(temp_array[1], rot_allien_mx[2+(3*j)], sizeof(temp_array[0]));
    send_frame_multiplex_equal(temp_array,3,20);
    
  }
  
  // Second part
  for(int j=0;j<12;++j)
  {
    for(int i=0;i<2;++i)
    {

      memcpy(temp_array[i], rot_allien_mx_s[i+(3*j)], sizeof(temp_array[0]));
          
    }
    
    memcpy(temp_array[2], tmp2, sizeof(temp_array[0]));
    send_frame_multiplex_equal(temp_array,3,20);

    memcpy(temp_array[1], rot_allien_mx_s[2+(3*j)], sizeof(temp_array[0]));
    send_frame_multiplex_equal(temp_array,3,20);
    
  }
}

void  windmill()
{
  byte temp_array[8][9];
  // Copying the mx
  for(int j=0;j<8;++j)
  {
    memcpy(temp_array[j], windmill_mx[j], sizeof(temp_array[0]));   
  }

  send_frame_multiplex_equal(temp_array,8,1000);     

}
