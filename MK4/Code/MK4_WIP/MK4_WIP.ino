//include libraries
#include "Timer.h"
#include "Wire.h"
#include "I2C_eeprom.h"
#include <ADS1256.h>
#include <SPI.h>
#include <LiquidCrystal_I2C.h>
#include <ShiftRegister74HC595.h>

//Define some Variables
float HvRef = 7.05; 
float vRef = 2.35; // voltage reference for ADC if ADR1399 is used (expected value)



  //no touchy!
ShiftRegister74HC595<3> sr(47, 49, 48);// parameters: <number of shift registers> (data pin, clock pin, latch pin)
LiquidCrystal_I2C lcd(0x27,20,4); //initialize 2004 i2c lcd
I2C_eeprom ee(0x50, I2C_DEVICESIZE_24LC64); uint32_t start, dur1, dur2;//initalize EEPROM (64kb)
int pga; //pga gain (int val)
float Fpga; //pga gain (floating point val)
float VMUXA; //voltage MUX attenuation
float VMUXAT; // voltage MUX attenuation in x10 mode
float VoffCurr;// voltage offset in current state
float VoffIT;// voltage offset internal ten(x10 attenuation)
float VoffEO;// voltage offset external one(x1 attenuation)
float VoffET;// voltage offset external ten(x10 attenuation)
float FpgaA = 1; float FpgaB = 2; float FpgaC = 4; float FpgaD = 8; float FpgaE = 16; float FpgaF = 32; float FpgaG = 64; // default "actual" pga gains
//check if EEPROM has cal data on it
    //if yes, import cal data to variables from EEPROM
    //if no, display on screen that ECal is required, wait 5 sec, then set to defaults
ADS1256 adc(7.68,vRef,false); // Initialize ADS1256 object; RESETPIN is permanently tied to 3.3v




/*Arduino Mega2650 pinout
D0: DNC
D1: DNC
D2-D13: NC
TX1: NC
RX1: NC
TX2: NC
RX2: NC
TX3: NC
RX3: NC
SDA: LCD and EEPROM
SCL: LCD and EEPROM
D22-D29: NC
D30: Digital Ready (Input)
D31: Digital Sync (Output)
D32: Line Sync (Input)
D33: Line Present (Input)
D34: NC
D35: NC
D36: Excite Keypad Collumn 1 (Output)
D37: Excite Keypad Collumn 2 (Output)
D38: Excite Keypad Collumn 3 (Output)
D39: Excite Keypad Collumn 4 (Output)
D40: Keypad Row 1 (Input)
D41: Keypad Row 2 (Input)
D42: Keypad Row 3 (Input)
D43: Keypad Row 4 (Input)
D44: NC
D45: Power Monitor Reset (Output)
D46: Power Monitor Check (Input)
D47: Shift Register SI0 (Output)
D48: Shift Register RCK (Output; latch)
D49: Shift Register Clk (Output; shift)
D50: ADC MISO (Output)
D51: ADC MOSI (Output)
D52: ADC SCK (Output)

A0: Analog Rail Feedback
A1-A15: NC
*/

/*Shift register chain
 * SR0: Rail sense MUX S0
 * SR1: Rail sense MUX S1
 * SR2: Rail sense MUX S2
 * SR3-SR7: NC
 * 
 * SR8: Relay 1 SET
 * SR9: Relay 1 RESET
 * SR10: Relay 2 SET
 * SR11: Relay 2 RESET
 * SR12: Relay 3 SET
 * SR13: Relay 3 RESET
 * SR14: Relay 4 SET
 * SR15: Relay 4 RESET
 * 
 * SR16: Relay 5 SET (ICAL)
 * SR17: Relay 5 RESET (ICAL)
 * SR18-SR23:NC
 */



void setup() {
  Serial.begin(115200);// start usb at resonable baud rate
  


//check power monitor


  

}

void loop() {
  // put your main code here, to run repeatedly:

}


void ECalV(){ // external voltage calibration
  //have user confirm voltage ECal
  //reset all offsets and compensations to default
  VoffIT = 0; VoffEO = 0; VoffET = 0; HvRef = 7.05; vRef = 2.35;
  //have user connect external
  //have user connect voltage standard
  //conf when done
  //have user enter voltage standard value
    //confirm val is correct
    //otherwise, re-enter value
  //disp "please wait"
  delay(20000);//wait 20 sec
  //Autorange
  
}


void VARNG(){
  //voltage autorange

  //set 
  
}









void Error(int Err){
  if(Err == 1){
    //display "Fatal Error:"
    //display "PGA(int) undefined"
    
  }else if(Err == 2){
    //display "Fatal Error:"
    //display "SetRel(int, bool)"
    //display "undefined int"
  }else if(Err == 3){
    //display "Fatal Error:"
    //display "VMUX(int) undefined"
    //display "undefined int"
  }else if(Err == 4){
    //display "Fatal Error:"
    //display "
  }

  //wait until user clears
}







void PGA(int SPGA){
  if(SPGA == 1){ // set PGA to 1
    pga = 1;
    Fpga = FpgaA; 
    adc.begin(ADS1256_DRATE_2_5SPS,ADS1256_GAIN_1,false); 
  } else if(SPGA == 2){// set PGA to 2
    pga = 2;
    Fpga = FpgaB;
    adc.begin(ADS1256_DRATE_2_5SPS,ADS1256_GAIN_2,false); 
  }else if(SPGA == 4){// set PGA to 4
    pga = 4;
    Fpga = FpgaC;
    adc.begin(ADS1256_DRATE_2_5SPS,ADS1256_GAIN_4,false);  
  }else if(SPGA == 8){// set PGA to 8
    pga = 8;
    Fpga = FpgaD;
    adc.begin(ADS1256_DRATE_2_5SPS,ADS1256_GAIN_8,false); 
  }else if(SPGA == 16){// set PGA to 16
    pga = 16;
    Fpga = FpgaE;
    adc.begin(ADS1256_DRATE_2_5SPS,ADS1256_GAIN_16,false); 
  }else if(SPGA == 32){// set PGA to 32
    pga = 32;
    Fpga = FpgaF;
    adc.begin(ADS1256_DRATE_2_5SPS,ADS1256_GAIN_32,false); 
  }else if(SPGA == 64){// set PGA to 64
    pga = 64;
    Fpga = FpgaG;
    adc.begin(ADS1256_DRATE_2_5SPS,ADS1256_GAIN_64,false); 
  } else{
    Error(1);
  }
}




void VMUX(int State){//done
  //only relays 1-4 are involved in the VMUX
  /*state settings (Relay1,Relay2,Relay3,Relay4)
   * 1: Set MUX to x1, connected to front term (1,1,0,0)
   * 2: Set MUX to x1 on internal short (0,1,0,0)
   * 10: Set MUX to x10 connected to front term (1,0,0,0) 
   * 11: Set MUX to x10 on internal short (0,0,0,0)
   * 12: Set MUX to x10 on vRef (0,0,0,1)
   * 13: Set MUX to x10 on HvRef (0,0,1,0) 
   */
   if(State == 1){
    SetRel(1,1);// set relay 1 to NO
    SetRel(2,1);// set relay 2 to NO
    SetRel(3,0);// set relay 3 to NC
    SetRel(4,0);// set relay 4 to NC
    VMUXA = 1; //voltage MUX attenuation
    VoffCurr = VoffEO;
   } else if(State == 2){
    SetRel(1,0);// set relay 1 to NC
    SetRel(2,1);// set relay 2 to NO
    SetRel(3,0);// set relay 3 to NC
    SetRel(4,0);// set relay 4 to NC
    VMUXA = 1; //voltage MUX attenuation
    VoffCurr = 0;// expect to down be in the nanovolts
   } else if(State == 10){
    SetRel(1,1);// set relay 1 to NO
    SetRel(2,0);// set relay 2 to NC
    SetRel(3,0);// set relay 3 to NC
    SetRel(4,0);// set relay 4 to NC
    VMUXA = VMUXAT; //voltage MUX attenuation
    VoffCurr = VoffET;
   } else if(State == 11){
    SetRel(1,0);// set relay 1 to NC
    SetRel(2,0);// set relay 2 to NC
    SetRel(3,0);// set relay 3 to NC
    SetRel(4,0);// set relay 4 to NC
    VMUXA = VMUXAT; //voltage MUX attenuation
    VoffCurr = 0;// expect to down be in the nanovolts
   } else if(State == 12){
    SetRel(1,0);// set relay 1 to NC
    SetRel(2,0);// set relay 2 to NC
    SetRel(3,0);// set relay 3 to NC
    SetRel(4,1);// set relay 4 to NO
    VMUXA = VMUXAT; //voltage MUX attenuation
    VoffCurr = 0;// expect to down be in the nanovolts
   } else if(State == 14){
    SetRel(1,0);// set relay 1 to NC
    SetRel(2,0);// set relay 2 to NC
    SetRel(3,1);// set relay 3 to NO
    SetRel(4,0);// set relay 4 to NC
    VMUXA = VMUXAT; //voltage MUX attenuation
    VoffCurr = 0;// expect to down be in the nanovolts
   } else{
    Error(3);// throw error
   }
    
}





void SetRel(int Numb, bool NumbState){ // done
  /*Shift register chain
 * SR0: Rail sense MUX S0
 * SR1: Rail sense MUX S1
 * SR2: Rail sense MUX S2
 * SR3-SR7: NC
 * 
 * SR8: Relay 1 SET
 * SR9: Relay 1 RESET
 * SR10: Relay 2 SET
 * SR11: Relay 2 RESET
 * SR12: Relay 3 SET
 * SR13: Relay 3 RESET
 * SR14: Relay 4 SET
 * SR15: Relay 4 RESET
 * 
 * SR16: Relay 5 SET (ICAL)
 * SR17: Relay 5 RESET (ICAL)
 * SR18-SR23:NC
 */
 int i = 18; //define i and set it to an output that won't fuck up something if shit happens and i doesn't change
  if(Numb == 1){
    if(NumbState == true){
      i = 8;// set 1
    }else{
      i = 9;// reset 1
    }
 }else if(Numb == 2){
  if(NumbState == true){
      i = 10;// set 2
    }else{
      i = 11;// reset 2
    }
 }else if(Numb == 3){
  if(NumbState == true){
      i = 12;// set 3
    }else{
      i = 13;// reset 3
    }
 }else if(Numb == 4){
  if(NumbState == true){
      i = 14;// set 4
    }else{
      i = 15;// reset 4
    }
 }else if(Numb == 5){
  if(NumbState == true){
      i = 16;// set 5
    }else{
      i = 17;// reset 5
    }
 }else{
  Error(2); // throw an error if something fucks up
 }
 sr.set(i, HIGH);
 delay(50);
 sr.set(i, LOW);
}
