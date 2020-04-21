


//#define CONTROLLER_COUNT    5
/* Hardware Constructs */
//#include <ax12.h>
//#include <BioloidController.h>
//BioloidController controllers[CONTROLLER_COUNT];

//#include "ros.h"

///* Packet Decoding */
//int mode = 0;                   // where we are in the frame
//
//unsigned char id = 0;           // id of this frame
//unsigned char length = 0;       // length of this frame
//unsigned char ins = 0;          // instruction of this frame
//
//unsigned char params[143];      // parameters (match RX-64 buffer size)
//unsigned char index = 0;        // index in param buffer
//
//int checksum;                   // checksum

///* Register Storage */
//unsigned char baud = 7;         // ?
//unsigned char ret_level = 1;    // ?
//unsigned char alarm_led = 0;    // ?


///* 
// * Setup Functions
// */
//void scan(){
//#if defined(AX_RX_SWITCHED)
//  // do a search for devices on the RX bus, default to AX if not found
//  int i;
//  for(i=0;i<AX12_MAX_SERVOS;i++){
//    dynamixel_bus_config[i] = 1;
//    if(ax12GetRegister(i+1, AX_ID, 1) != (i+1)){
//      dynamixel_bus_config[i] = 0;
//    }
//  }
//#endif
//}

void setup(){
  Serial.begin(9600);
 // ax12Init(1000000);


//pinMode(0,OUTPUT);     // status LED

//  userSetup();

//digitalWrite(0, HIGH);

//ax12SetRegister(1,25, 0);


}





///*
// * Send status packet
// */
//void statusPacket(int id, int err){
//  Serial.write(0xff);
//  Serial.write(0xff);
//  Serial.write(id);
//  Serial.write(2);
//  Serial.write(err);
//  Serial.write(255-((id+2+err)%256));
//}

/* 
 * decode packets: ff ff id length ins params checksum
 *   same as ax-12 table, except, we define new instructions for Arbotix 
 */
void loop(){
 // digitalWrite(0,LOW);
  int i;
    //ax12SetRegister(1,25, 1);
  // process messages
  if(Serial.available() > 0){
  //  digitalWrite(0, HIGH);
  //ax12SetRegister(1,25, 1);
  byte data = Serial.read();
  Serial.print("AB");
  
  if (data == 0xff){
    Serial.print('HERE');
    while(true){
    
  }
  }
  while(true){
    
  }
    // We need to 0xFF at start of packet
//    if(mode == 0){         // start of new packet
//      if(Serial.read() == 0xff){
//        mode = 2;
//        //digitalWrite(0,HIGH-digitalRead(0));
//      }
//    }else if(mode == 1){   // another start byte
//        if(Serial.read() == 0xff)
//            mode = 2;
//        else
//            mode = 0;
//    }else if(mode == 2){   // next byte is index of servo
//      id = Serial.read();    
//      if(id != 0xff)
//        mode = 3;
//    }else if(mode == 3){   // next byte is length
//      length = Serial.read();
//      checksum = id + length;
//      mode = 4;
//    }else if(mode == 4){   // next byte is instruction
//      ins = Serial.read();
//      checksum += ins;
//      index = 0;
//      mode = 5;
//    }else if(mode == 5){   // read data in 
//    //digitalWrite(0, HIGH);  
//    
//      params[index] = Serial.read();
//      checksum += (int) params[index];
//      index++;
//      if(index + 1 == length){  // we've read params & checksum
//        mode = 0;
//        if((checksum%256) != 255){ 
//          // return an error packet: FF FF id Len Err=bad checksum, params=None check
//          statusPacket(id, ERR_CHECKSUM);
//        }else if(id == 0xFE){
//        
//        }else{ // ID != 253, pass thru 
//          digitalWrite(0, HIGH);
//          switch(ins){
//            // TODO: streamline this
//            case AX_READ_DATA:
//              //ax12GetRegister(id, params[0], params[1]);
//              // return a packet: FF FF id Len Err params check
//              if(ax_rx_buffer[3] > 0){
//                for(i=0;i<ax_rx_buffer[3]+4;i++)
//                  Serial.write(ax_rx_buffer[i]);
//              }
//              ax_rx_buffer[3] = 0;
//              break;
//             
//            case AX_WRITE_DATA:
//              if(length == 4){
//                
//              //digitalWrite(0, LOW);
//                //ax12SetRegister(id, params[0], params[1]);
//              }else{
//                int x = params[1] + (params[2]<<8);
//                //ax12SetRegister2(id, params[0], x);
//              }
//              statusPacket(id,0);
//              break;
//             
//          }
//        }
//      }
//    } // end mode == 5
  } // end while(available)

 


}
