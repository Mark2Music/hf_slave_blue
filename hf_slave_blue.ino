/*
* MLT-BT05 4.0 蓝牙模块
* Support the IOS and ANDROID systems.
* 2017.04.24.
* XG-BM02X 5.0 蓝牙模块
*/

/*if the blueteeth is connected, this pin will exported a high level.
 * otherwise, it will have a low level.
*/
int connect_status = 7;
int relay_control = 4; // low level will trigger the relay control to work

void setup()
{
  //initialize the master uart
  Serial.begin(115200); 
  //initialize the connect_status pin level.
  pinMode(connect_status,INPUT);
  pinMode(relay_control, OUTPUT);
  digitalWrite(relay_control, HIGH);
}

void loop()
{
  if(Serial.available())
  {
      char cmd = Serial.read();    //从串口读取info
      switch(cmd)
      {
        case '1':
           digitalWrite(relay_control,LOW);  //open the door
           delay(300);
           digitalWrite(relay_control,HIGH);
           break;
        case '0':
           digitalWrite(relay_control,HIGH);   //close the door
           delay(300);
           break;           
        default:
           break;
      
      }
      
  }		
  delay(100);
}


