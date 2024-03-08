#include <OneWire.h> 
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 2 
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);


unsigned long systemTime;
int drawerCounter = 1;
float systemTemp;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  sensors.begin(); 
  pinMode(13,OUTPUT);  //floor 1 -L
  pinMode(12,OUTPUT);  //Floor 1 -M
  pinMode(11,OUTPUT);   //Floor 1 -R
  pinMode(10,OUTPUT);   //Floor 2 - R
  pinMode(9,OUTPUT);    //Floor 2 - L
  pinMode(8,OUTPUT);    //Floor 2 -M
  pinMode(7,OUTPUT);    //Floor 3 -L
  pinMode(6,OUTPUT);    //Floor 3 -M
  


  pinMode(22,OUTPUT);
  pinMode(23,OUTPUT);   //Floor 4 -L
  pinMode(24,OUTPUT);
  pinMode(25,OUTPUT);   //Floor 4 -M
  pinMode(26,OUTPUT);
  pinMode(27,OUTPUT);   //Floor 4 -R
  pinMode(28,OUTPUT);
  pinMode(29,OUTPUT);   //Floor 3 -R
  pinMode(30,OUTPUT);

  pinMode(31,OUTPUT);
  pinMode(32,OUTPUT);
  pinMode(33,OUTPUT);
  pinMode(34,OUTPUT);
  pinMode(35,OUTPUT);
  pinMode(36,OUTPUT);
  pinMode(37,OUTPUT);  //Saftey
  pinMode(38,OUTPUT);
  pinMode(39,OUTPUT);
  pinMode(40,OUTPUT);
  pinMode(41,OUTPUT);
  pinMode(42,OUTPUT);
  pinMode(43,OUTPUT);
  pinMode(44,OUTPUT);
  pinMode(45,OUTPUT);
  pinMode(46,OUTPUT);
  pinMode(47,OUTPUT);
  pinMode(48,OUTPUT);
  pinMode(49,OUTPUT);
  pinMode(50,OUTPUT);
  pinMode(51,OUTPUT);
  pinMode(52,OUTPUT);
  pinMode(53,OUTPUT);  

 
    digitalWrite(13,HIGH);
    digitalWrite(12,HIGH);
    digitalWrite(11,HIGH);
     digitalWrite(10,HIGH);
      digitalWrite(9,HIGH);
       digitalWrite(8,HIGH);
        digitalWrite(7,HIGH);
         digitalWrite(6,HIGH);
         digitalWrite(22,HIGH);  
          digitalWrite(23,HIGH);
          digitalWrite(24,HIGH);     //Floor 5 R
           digitalWrite(25,HIGH);
           digitalWrite(26,HIGH);   //Floor 5 L
            digitalWrite(27,HIGH);
            digitalWrite(28,HIGH);    //Floor 5 M
             digitalWrite(29,HIGH);
             digitalWrite(30,HIGH);    //Floor 6 R
             digitalWrite(31,HIGH);
             digitalWrite(32,HIGH);   //Floor 6 L
             digitalWrite(33,HIGH);
             digitalWrite(34,HIGH);   //Floor 6 M
             digitalWrite(35,HIGH);
             digitalWrite(36,HIGH);    //Floor 7 R
             digitalWrite(37,HIGH);     //Saftey
             digitalWrite(38,LOW);
             digitalWrite(39,HIGH);
             digitalWrite(40,HIGH);
             digitalWrite(41,HIGH);
             digitalWrite(42,HIGH);
             digitalWrite(43,HIGH);
             digitalWrite(44,HIGH);
             digitalWrite(45,HIGH);      //Floor 8M
             digitalWrite(46,HIGH);
             digitalWrite(47,HIGH);      //Floor 8L
             digitalWrite(48,HIGH);
             digitalWrite(49,HIGH);      //Flor 8R
             digitalWrite(50,HIGH);
             digitalWrite(51,HIGH);      //Floor 7M
             
              digitalWrite(52,HIGH);
              digitalWrite(53,HIGH);     //Floor 7L
              
              

}


void loop() {

  static uint32_t oldtime=millis();
  sensors.requestTemperatures();
  systemTemp = sensors.getTempCByIndex(0);
  
  //Safety:
  Serial.println(systemTemp);
  if(systemTemp>12.5 && systemTemp!= -127.00)
    digitalWrite(37,HIGH);
  if(systemTemp<11 &&systemTemp!=-127.00)
    digitalWrite(37,LOW);

  
                 

  //time interval between drawers:
  if ( (millis()-oldtime) > 60000) {     //60000-1Minute interval
       oldtime = millis();
      Serial.println(systemTemp);
      drawerAirOn(drawerCounter);
      drawerCounter +=1;
      if(drawerCounter == 17)
        drawerCounter = 1;
  }
}


void drawerAirOn(int drawerNumber){

    switch(drawerNumber){
      
      case 1:
      if(systemTemp<12.5){
      digitalWrite(11,LOW); //Right
      delay(500);
      digitalWrite(11,HIGH);
      
      digitalWrite(13,LOW); //Left
      delay(500);
      digitalWrite(13,HIGH);

      delay(5000);

      for(int i=0;i<3;i++){  //Center
      digitalWrite(12,LOW);
      delay(500);
      digitalWrite(12,HIGH);
      delay(5000);
      }
      
      }
        break;

       case 2:
        if(systemTemp<12.5){
       digitalWrite(10,LOW); //Right
      delay(500);
      digitalWrite(10,HIGH);
      
      digitalWrite(9,LOW); //Left
      delay(500);
      digitalWrite(9,HIGH);

      delay(5000);

      for(int i=0;i<3;i++){  //Center
      digitalWrite(8,LOW);
      delay(500);
      digitalWrite(8,HIGH);
      delay(5000);
      }
        }
        break;

       case 3:
       if(systemTemp<12.5){
       digitalWrite(29,LOW); //Right
      delay(500);
      digitalWrite(29,HIGH);
      
      digitalWrite(7,LOW); //Left
      delay(500);
      digitalWrite(7,HIGH);

      delay(5000);

      for(int i=0;i<3;i++){  //Center
      digitalWrite(6,LOW);
      delay(500);
      digitalWrite(6,HIGH);
      delay(5000);
      }
       }
        break;

       case 4:
       if(systemTemp<12.5){
       digitalWrite(27,LOW); //Right
      delay(500);
      digitalWrite(27,HIGH);
      
      digitalWrite(23,LOW); //Left
      delay(500);
      digitalWrite(23,HIGH);

      delay(5000);

      for(int i=0;i<3;i++){  //Center
      digitalWrite(25,LOW);
      delay(500);
      digitalWrite(25,HIGH);
      delay(5000);
      }
       }
        break;

      case 5:
      if(systemTemp<12.5){
         digitalWrite(24,LOW); //Right
      delay(500);
      digitalWrite(24,HIGH);
      
      digitalWrite(26,LOW); //Left
      delay(500);
      digitalWrite(26,HIGH);

      delay(5000);

      for(int i=0;i<3;i++){  //Center
      digitalWrite(28,LOW);
      delay(500);
      digitalWrite(28,HIGH);
      delay(5000);
      }    
        }

        break;

      
      case 6:
      if(systemTemp<12.5){
         digitalWrite(30,LOW); //Right
      delay(500);
      digitalWrite(30,HIGH);
      
      digitalWrite(32,LOW); //Left
      delay(500);
      digitalWrite(32,HIGH);

      delay(5000);

      for(int i=0;i<3;i++){  //Center
      digitalWrite(34,LOW);
      delay(500);
      digitalWrite(34,HIGH);
      delay(5000);
      }    
        }

        break;

       
      case 7:
      if(systemTemp<12.5){
         digitalWrite(36,LOW); //Right
      delay(500);
      digitalWrite(36,HIGH);
      
      digitalWrite(53,LOW); //Left
      delay(500);
      digitalWrite(53,HIGH);

      delay(5000);

      for(int i=0;i<3;i++){  //Center
      digitalWrite(51,LOW);
      delay(500);
      digitalWrite(51,HIGH);
      delay(5000);
      }    
        }

        break;

       
      case 8:
      if(systemTemp<12.5){
         digitalWrite(49,LOW); //Right
      delay(500);
      digitalWrite(49,HIGH);
      
      digitalWrite(47,LOW); //Left
      delay(500);
      digitalWrite(47,HIGH);

      delay(5000);

      for(int i=0;i<3;i++){  //Center
      digitalWrite(45,LOW);
      delay(500);
      digitalWrite(45,HIGH);
      delay(5000);
      }    
        }

        break;

       
      case 9:
      if(systemTemp<12.5){
         digitalWrite(31,LOW); //Right
      delay(500);
      digitalWrite(31,HIGH);
      
      digitalWrite(33,LOW); //Left
      delay(500);
      digitalWrite(33,HIGH);

      delay(5000);

      for(int i=0;i<3;i++){  //Center
      digitalWrite(35,LOW);
      delay(500);
      digitalWrite(35,HIGH);
      delay(5000);
      }    
        }

        break;

       
      case 10:
      if(systemTemp<12.5){
         digitalWrite(31,LOW); //Right
      delay(500);
      digitalWrite(31,HIGH);
      
      digitalWrite(33,LOW); //Left
      delay(500);
      digitalWrite(33,HIGH);

      delay(5000);

      for(int i=0;i<3;i++){  //Center
      digitalWrite(35,LOW);
      delay(500);
      digitalWrite(35,HIGH);
      delay(5000);
      }    
        }

        break;

       
      case 11:
      if(systemTemp<12.5){
         digitalWrite(31,LOW); //Right
      delay(500);
      digitalWrite(31,HIGH);
      
      digitalWrite(33,LOW); //Left
      delay(500);
      digitalWrite(33,HIGH);

      delay(5000);

      for(int i=0;i<3;i++){  //Center
      digitalWrite(35,LOW);
      delay(500);
      digitalWrite(35,HIGH);
      delay(5000);
      }    
        }

        break;

       
      case 12:
      if(systemTemp<12.5){
         digitalWrite(31,LOW); //Right
      delay(500);
      digitalWrite(31,HIGH);
      
      digitalWrite(33,LOW); //Left
      delay(500);
      digitalWrite(33,HIGH);

      delay(5000);

      for(int i=0;i<3;i++){  //Center
      digitalWrite(35,LOW);
      delay(500);
      digitalWrite(35,HIGH);
      delay(5000);
      }    
        }

        break;

       
      case 13:
      if(systemTemp<12.5){
         digitalWrite(31,LOW); //Right
      delay(500);
      digitalWrite(31,HIGH);
      
      digitalWrite(33,LOW); //Left
      delay(500);
      digitalWrite(33,HIGH);

      delay(5000);

      for(int i=0;i<3;i++){  //Center
      digitalWrite(35,LOW);
      delay(500);
      digitalWrite(35,HIGH);
      delay(5000);
      }    
        }

        break;

       
      case 14:
      if(systemTemp<12.5){
         digitalWrite(31,LOW); //Right
      delay(500);
      digitalWrite(31,HIGH);
      
      digitalWrite(33,LOW); //Left
      delay(500);
      digitalWrite(33,HIGH);

      delay(5000);

      for(int i=0;i<3;i++){  //Center
      digitalWrite(35,LOW);
      delay(500);
      digitalWrite(35,HIGH);
      delay(5000);
      }    
        }

        break;

       
      case 15:
      if(systemTemp<12.5){
         digitalWrite(31,LOW); //Right
      delay(500);
      digitalWrite(31,HIGH);
      
      digitalWrite(33,LOW); //Left
      delay(500);
      digitalWrite(33,HIGH);

      delay(5000);

      for(int i=0;i<3;i++){  //Center
      digitalWrite(35,LOW);
      delay(500);
      digitalWrite(35,HIGH);
      delay(5000);
      }    
        }

        break;

       
      case 16:
      if(systemTemp<12.5){
         digitalWrite(31,LOW); //Right
      delay(500);
      digitalWrite(31,HIGH);
      
      digitalWrite(33,LOW); //Left
      delay(500);
      digitalWrite(33,HIGH);

      delay(5000);

      for(int i=0;i<3;i++){  //Center
      digitalWrite(35,LOW);
      delay(500);
      digitalWrite(35,HIGH);
      delay(5000);
      }    
        }

        break;
      
      
      }  
  
  
  
  
  
  }
