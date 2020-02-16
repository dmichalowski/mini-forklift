//LEFT motor
#define motorL1 6
#define motorL2 7
#define motorLpwm 5

//RIGHT motor
#define motorP1 8
#define motorP2 9
#define motorPpwm 10

//lift
#define lift1 13
#define lift2 12
#define liftPWM 11

bool motorControl = 0, liftControl = 0;

inline void motorLeftForward(){
  digitalWrite(motorL1, LOW);
  digitalWrite(motorL2, HIGH);
}

inline void motorRightForward(){
  digitalWrite(motorP1, LOW);
  digitalWrite(motorP2, HIGH);
}

inline void liftUp(){
  digitalWrite(lift1, HIGH);
  digitalWrite(lift2, LOW);
}

inline void motorLeftBackward(){
  digitalWrite(motorL1, HIGH);
  digitalWrite(motorL2, LOW);
}

inline void motorRightBackward(){
  digitalWrite(motorP1, HIGH);
  digitalWrite(motorP2, LOW);
}

inline void liftDown(){
  digitalWrite(lift1, LOW);
  digitalWrite(lift2, HIGH);
}

float radius(float x,float y)
{
  float result=0;
    result=sqrt(x*x+y*y);
    return result;
}

void setVelocity(float velocityX, float velocityY, bool control){
  if(control){ //1-prawo
    analogWrite(motorLpwm,radius(velocityX,velocityY));
    analogWrite(motorPpwm,velocityY*0.765);
  }
  else{
    analogWrite(motorLpwm,velocityY);
    analogWrite(motorPpwm,radius(velocityX,velocityY)*0.765);
  }
}



bool load(int * mode, float * x, float * y) {
  float a = 1,b = 2,c = 3;
  String recievedData[3];
  if(Serial.available() > 0) {
    recievedData[0] = Serial.readStringUntil(',');
    recievedData[1] = Serial.readStringUntil(',');
    recievedData[2] = Serial.readStringUntil('\n');
    if(recievedData[2].length()>8) {}
    else if(recievedData[0].length()==0) {}
    else
    {
      *mode = recievedData[0].toFloat();
      *x = recievedData[1].toFloat();
      *y = recievedData[2].toFloat();
      Serial.print(*mode);
      Serial.print(',');
      Serial.print(*x);
      Serial.print(',');
      Serial.print(*y);
      Serial.print('\n');
    }
  }
  return 1;
 }
 
void setup() {
  Serial.begin(9600);
  Serial.println("RUN!");
  
  pinMode(motorL1, OUTPUT);
  pinMode(motorL2, OUTPUT);
  pinMode(motorLpwm, OUTPUT);
  
  pinMode(motorP1, OUTPUT);
  pinMode(motorP2, OUTPUT);
  pinMode(motorPpwm, OUTPUT) ;

  pinMode(lift1, OUTPUT);
  pinMode(lift2, OUTPUT);
  pinMode(liftPWM, OUTPUT);
}



void loop() {
  float x,y, velocityX, velocityY,velocityZ;
  int mode;
  load(&mode, &x, &y);
  switch(mode){
    case 0:
      motorControl = 0;
      liftControl = 0;
      x = 0;
      y = 0;
      analogWrite(motorLpwm,0);
      analogWrite(motorPpwm,0);
      analogWrite(liftPWM,0);
      break;
    case 1:
      if(y>0){
        liftUp();
      }
      else{
        liftDown();
      }
      analogWrite(liftPWM,255);
      break;
      
    case 2:
    //DEAD ZONE
      if(radius(x,y)<0.3){
        analogWrite(motorLpwm,0);
        analogWrite(motorPpwm,0);
      }
      //STRAIGHT
      else if(x < 0.3 && x > -0.3){
        if(y>0){
          motorLeftForward();
          motorRightForward();
          velocityY = y * 255;
          setVelocity(0,velocityY,1);
        }
        else{
          motorLeftBackward();
          motorRightBackward();
          velocityY = y * (-255);
          setVelocity(0,velocityY,1);
        }
      }
      else{
        //Y
       if(y > 0){
         motorLeftForward();
         motorRightForward();
         velocityY = y * 255;
       }
       else {
         motorLeftBackward();
         motorRightBackward();
         velocityY = y * (-255);
      }
      //X
       if (x > 0){
        velocityX = x * 255;
        setVelocity(velocityX,velocityY,1);
       }
       else{
        velocityX = x * (-255);
        setVelocity(velocityX,velocityY,0);
       }
      }
      break;
    }
}
