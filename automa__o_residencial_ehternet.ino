#include <SPI.h>
#include <UIPEthernet.h>
#include <Thermistor.h>

String inString = "";
Thermistor temp(0);
double resistor = 10000;
double average =0;
int sample = 5000;
 int tttt= 0;
  float temperature = temp.getTemp();
/* #if defined(__AVR_ATmega328p__) || defined(__AVR_ATmega328p__)
#define ENC28J60_CONTROL_CS     48
#define SPI_MOSI        51
#define SPI_MISO        50
#define SPI_SCK         52
#else;
#define ENC28J60_CONTROL_CS     10
#define SPI_MOSI        11
#define SPI_MISO        12
#define SPI_SCK         13
#endif;


termistor s = A0  c= GND - = 5V
 
*/
int i, tem=0, freq, value = 0; // velocidae do motor ou intencidade da lampada
int d = 0;
String readString;  // string para leitura de datos pelo modulo ethernet
int dis = 0;



// parametros para comunicação via ethernet
byte mac[] = {0x74,0x69,0x69,0x2D,0x30,0x31}; // inderço unico 

IPAddress ip(192,168,0,105); // ip fixo 
EthernetServer server(80); // porta de comunicação 
//----------------------------------------------------
void setup()
{
 
  Ethernet.begin(mac, ip);
  server.begin();
  Serial.begin(57600);//
  pinMode(2, OUTPUT);  // presença
  pinMode(3, OUTPUT);  // pwm
  pinMode(4, OUTPUT);  // digital
  pinMode(5, OUTPUT);  // digital
  pinMode(6, OUTPUT);  // digital
  pinMode(7, OUTPUT);  // digital
  pinMode(8, OUTPUT);  // digital
  pinMode(9, OUTPUT); // temperatura

}

void loop() 
{
  
//Serial.println(temperature);


  //-------------------------------PRESENÇA------------------------------------ 
  dis = analogRead(1);
//Serial.println(dis);
if(dis < 970 )
         {
          
          digitalWrite(2, HIGH);
        // Serial.println("carga presenca ligada");
          }
          else
          {
            digitalWrite(2, LOW);
        //    Serial.println("carga presenca desligada");
            }


//-------------------------------PRESENÇA------------------------------------      



//-------------------------------TERMISTO----------------------------------- 
 /* temperature= temp.getTemp();

 // Serial.print("Temperatura no Sensor eh: ");
  //Serial.print(temperature);
  //Serial.println("*C");
  //delay(1000);
         if(tem>temperature )
         {
          
          digitalWrite(9, HIGH);
        //  Serial.println("arcondicionado desligado");
          }
          else if (tem < temperature - 2)
          {
            digitalWrite(9, LOW);
           // Serial.println("arcondicionado ligado");
            }*/

            temperature = temp.getTemp();
          
        
         if(temperature<tem )
         {
          
          digitalWrite(9, LOW);
        //  Serial.println("arcondicionado desligado");
          }
          else if (temperature>tem +2)
          {
            digitalWrite(9, HIGH);
           // Serial.println("arcondicionado ligado");
            }
//-------------------------------TERMISTO----------------------------------- 

 
  // criando conexao 
  EthernetClient client = server.available();
//------- fazendo leitura dos comandos   
 if (client) {
      

       
    while (client.connected()) {
   
        
     if (client.available()) {



        
        char c = client.read();
    //  d = client;
        if (readString.length() < 100) {

          //store characters to string
          readString += c;
       //   Serial.print(c);
        //  Serial.print(d);
        

       
         
        
 
       
         
//---------------------------------------------------------------------
       
     if (c == '\n') {
 
      // Serial.println(readString); //imprime dados recebidos para verificação
        



        
/////------------------------inicio digitais----------------------------------------------          
          // ligar 1
          if(readString.indexOf("?a") >0)
          {
            digitalWrite(4, HIGH);    
        //    Serial.println("1 On");
            
          }
          ///desligar 1
          if(readString.indexOf("?a1") >0)
          {
            digitalWrite(4, LOW);    
         //   Serial.println("1 off");
            
          }
          //ligar 2

           if(readString.indexOf("?b") >0)
          {
            digitalWrite(5, HIGH);    
        //    Serial.println("2 On");
           
          }
           //desligar 2

           if(readString.indexOf("?b1") >0)
          {
            digitalWrite(5, LOW);    
      //      Serial.println("2 off");
            
          }
           //ligar 3

           if(readString.indexOf("?c") >0)
          {
            digitalWrite(6, HIGH);    
         //   Serial.println("3 On");
          
          } //desligar 3

           if(readString.indexOf("?c1") >0)
          {
            digitalWrite(6, LOW);    
         //   Serial.println("3 off");
            
          }
           //ligar 4

           if(readString.indexOf("?d") >0)
          {
            digitalWrite(7, HIGH);    
         ///   Serial.println("4 On");
           
          }
           //desligar4

           if(readString.indexOf("?d1") >0)
          {
            digitalWrite(7, LOW);    
         //   Serial.println("4 Off");
           
          }
           //ligar 5

           if(readString.indexOf("?e") >0)
          {
            digitalWrite(8, HIGH);    
        //    Serial.println("5 On");
           
          }
           //desligar 5

           if(readString.indexOf("?e1") >0)
          {
            digitalWrite(8, LOW);    
         //   Serial.println("5 off");
            
          }
//------------------------------fim digitais-------------------------------------
//------------------------------inicio"analogicos"-------------------------------------
//-------------------controle de velocidade ou de intencidade------------------------------------   

 
           
  if(readString.indexOf("?vent=") >0)
          {
            
       if(readString.indexOf("+1") >0){
         freq = freq + 10;
            
            analogWrite(3, freq);  }
              
           if(readString.indexOf("-1") >0){
         freq = freq - 10;
            
            analogWrite(3, freq);  } 

         //  Serial.print("velocidade: ");
         //  Serial.println(freq);
          }
//-------------------controle de velocidade ou de intencidade------------------------------------


          
//---------------------------- TERMOSTATO------------------------------------       
       temperature = temp.getTemp();
           if(readString.indexOf("?temp=") >0) 
          { 
              
      if(readString.indexOf("+1") >0){
         tem ++;
            
              }
              
           if(readString.indexOf("-1") >0){
         tem --;
            
              } 
       // Serial.print("temperatura: ");
        //   Serial.println(tem);
          }

        
         if(temperature<tem )
         {
          
          digitalWrite(9, LOW);
        //  Serial.println("arcondicionado desligado");
          }
          else if (temperature>tem +2)
          {
            digitalWrite(9, HIGH);
           // Serial.println("arcondicionado ligado");
            }
//---------------------------- TERMOSTATO------------------------------------   



          readString="";/// apagar string

          client.println("HTTP/1.1 200 OK"); //send new page
          client.println("Content-Type: text/html");
          client.println();

          
          
           client.println(temperature);
           client.println(tem);
           client.println(freq);
       
          client.println("</body>");
          client.println("</head>");

          delay(1);
          
          client.stop();



        }
      }
    }
  }
}
  }

