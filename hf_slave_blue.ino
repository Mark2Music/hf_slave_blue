/*
* MLT-BT05 4.0 蓝牙模块
* Support the IOS and ANDROID systems.
* 2017.04.24.
* XG-BM02X 5.0 蓝牙模块
* 此蓝牙从机程序可以完美支持 XG-BM02X 5.0 模块
* 如果 MLT-BT05 4.0，只支持当它是从机的状态(若是主机，需要手动发指令让其变为从机) 
*/

/*if the blueteeth is connected, this pin will exported a high level.
 * otherwise, it will have a low level.
*/
int connect_status = 7;
int relay_control = 4; // low level will trigger the relay control to work
char receive_buffer[2];
int ret = 0;
boolean already_slave = false;
int count = 0;

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
  //query and change the role to 'S'
  if (already_slave == false)
  {
     //change the status to slave 
     LABEL_CMD:
     Serial.flush(); 
     ret = Serial.write("AT+ROLE=S\r");
     if (ret == 10)
     {
          count++;
          if(count < 5)
          {  
    			  if(Serial.available())
    			  {
      				  ret = Serial.readBytes(receive_buffer, 2);
      				  if(ret == 2)
      				  {
          				  if (receive_buffer[0] != 'O' && receive_buffer[1] != 'K')
          				  {
          					  goto LABEL_CMD;
          				  }
          				  else if (receive_buffer[0] == 'O' && receive_buffer[1] == 'K')
          				  {
          					  already_slave = true;
          				  }
      			    }
    			  }
		      } 	  
          else if(count >= 5)
          {//if five times is not ok, default is ok...if that happened, most probably reason is the slave bluetooth is bad!
              count = 0;
              already_slave = true;
          }	
     }
     Serial.flush();
             
  }
    
  if(Serial.available())
  {
      char cmd = Serial.read();    //从串口读取info
      switch(cmd)
      {
        case '1':
		   ret = Serial.write("8");
		   if (ret == 1)
		   {
			  digitalWrite(relay_control,LOW);  //open the door
			  delay(300);
              digitalWrite(relay_control,HIGH);	
		   }
		   else if(1 == Serial.write("8"))
		   {
			  digitalWrite(relay_control,LOW);  //open the door
			  delay(300);
              digitalWrite(relay_control,HIGH); 	
		   }
		   else
		   {
			  digitalWrite(relay_control,LOW);  //open the door
			  delay(300);
              digitalWrite(relay_control,HIGH); 	
		   }	
           break;
           
        case '0':
		   ret = Serial.write("8");
		   if (ret == 1)
		   {
			  digitalWrite(relay_control,HIGH);   //close the door	
		   }
		   else if(1 == Serial.write("8"))
		   {
			  digitalWrite(relay_control,HIGH);   //close the door	
		   }
		   else
		   {
			  digitalWrite(relay_control,HIGH);   //close the door	
		   }
           break;
                      
        default:
           break;
      }
      Serial.flush();
      
  }		
  delay(100);
}


