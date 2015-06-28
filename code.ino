int ax_pin = A4;
int ax_read;
int ax_sum;
float ax_avg;
int ax_curr;
int ax_prev;
float vx_curr;

int ay_pin = A2;
int ay_read;
int ay_sum;
float ay_avg;
int ay_curr;
int ay_prev;
float vy_curr;

float ay_prev1=0;
float ay_prev2=0;
float ay_prev3=0;
float ax_prev1=0;
float ax_prev2=0;
float ax_prev3=0;
float ax_fltr=0;
float ay_fltr=0;

int onb = 13;
int arb;

int ir_pin = A0;
int ir_read;

int i, k, m, n, x, y, z, p, q;

int ck = 3;
int ckr = 2;


void setup() {
  ax_sum = 0;
  i = 0;  k = 0;
  ax_avg = 0; ax_prev = 0;

  ay_sum = 0;
  m = 0; n = 0;
  ay_avg = 0; ay_prev = 0;
  
  arb=1;

  Mouse.begin();
  digitalWrite(onb, HIGH);


x = 0;
y = 0;
z = 0;
p = 0;
q = 0;

}

void loop() {

  
  if (digitalRead(onb)==LOW){
     if(arb==0){
      arb=1;
    }
    else{
      arb=0;
    }
    delay(500);
  }
  
if(arb==0){
    
//rightclickstarts
digitalWrite(ckr, HIGH);   
    if(digitalRead(ckr) == LOW){
              p = 1;
    }
    
    else{
      if(p==1){ 
          p = 0;
          q = 1;
      }
    }
    
    if(q==1){
      Mouse.click(MOUSE_RIGHT);
      q = 0;
    }
//rightclickends

  
  //leftclickstarts
  digitalWrite(ck, HIGH);
  if(digitalRead(ck) == LOW){
      y++;
      x = 1;
  }
  
  else{
      if(x==1 && y<50){
          z=1;
          x=0;
          y=0;
      }
      
      if(x==1 && y>49){
          Mouse.release(MOUSE_LEFT);
          x=0;
          y=0;
      }
  }

  if(z==1){
      Mouse.click(MOUSE_LEFT);
      z=0;
  }
  
  if(x==1 && y==50){
      Mouse.press(MOUSE_LEFT);
  }
    //leftclickends
    
    
    
    
    ax_read = analogRead(ax_pin);
    ay_read = analogRead(ay_pin);
    ir_read = analogRead(ir_pin);

    if ( i < 20 ) {
      i = i + 1;
    }
    else if ( i > 19 && i < 100) {
      ax_sum = ax_sum - ax_read;
      i = i + 1;
    }
    else {
      if (i == 100) {
        ax_avg = ax_sum / 80;
        i++;
      }

    if(ax_avg>0){
      ax_curr = ax_read - ax_avg;}//signmatters
      else{
        ax_curr = ax_read + ax_avg;}//signmatters


      if ((ax_curr < (ax_prev + 8)) && (ax_curr > (ax_prev - 8))) {
        k++;
      }
      else {
        k = 0;
      }

      if (k < 5) {
        vx_curr = vx_curr + ax_curr * 0.01 ;
        ax_avg = ax_sum / 80;
      }
      else {
        vx_curr = 0;
        if(ax_avg>0){
        ax_avg = ax_avg + ax_curr;}//signmatters
        else{
          ax_avg = ax_avg - ax_curr;}//signmatters
      }
      ax_prev = ax_curr;
      ax_fltr = (ax_prev1 + ax_prev2 + ax_prev3 + ax_curr)/4;
        ax_prev3 = ax_prev2;
        ax_prev2 = ax_prev1;
        ax_prev1 = ax_curr;
    }
  


Serial.print(ax_read);
Serial.print("  ");
Serial.print(ax_curr);
Serial.print("  ");
Serial.print(ax_avg);
Serial.print("  ");
Serial.print(vx_curr);
Serial.print("  ");
Serial.print(k);
Serial.print("       "); 


    if ( m < 20 ) {
      m = m + 1;
    }
    else if ( m > 19 && m < 100 ) {
      ay_sum = ay_sum + ay_read;
      m = m + 1;
    }
    else {
      if (m == 100) {
        ay_avg = ay_sum / 80;
        m++;
      }

      if(ay_avg>0){
      ay_curr = ay_read - ay_avg;}//signmatters
      else{
        ay_curr = ay_read + ay_avg;}//signmatters


      if ((ay_curr < (ay_prev + 8)) && (ay_curr > (ay_prev - 8))) {
        n++;
      }
      else {
        n = 0;
      }

      if (n < 5) {
        vy_curr = vy_curr + 0.01 * ay_curr ;
        ay_avg = ay_sum / 80;
      }
      else {
        vy_curr = 0;
        if(ay_avg>0){
        ay_avg = ay_avg + ay_curr;}//signmatters
        else{
          ay_avg = ay_avg - ay_curr;}//signmatters
      }
      ay_prev = ay_curr;
      ay_fltr = (ay_prev1 + ay_prev2 + ay_prev3 + ay_curr)/4;
        ay_prev3 = ay_prev2;
        ay_prev2 = ay_prev1;
        ay_prev1 = ay_curr;
    }
if(ir_read>500){
    Mouse.move(0.5*vx_curr,-(0.5*vy_curr),0);}
    else{
      Mouse.move(0,0,0.3*vy_curr);}
  
Serial.print(ay_read);
Serial.print("  ");
Serial.print(ay_curr);
Serial.print("  ");
Serial.print(ay_avg);
Serial.print("  ");
Serial.print(vy_curr);
Serial.print("  ");
Serial.print(n);
Serial.print("  ");
Serial.print(ir_read);
Serial.println("       ");

 
