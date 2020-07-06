//Program to interface RFID(Radio Frequency Identification Device) and LCD with 8051 microcontroller (AT89S51) 
//**************DISASTER MANAGEMENT SYSTEM***************

#include<reg51.h> 
unsigned int data_out,command=0x80,temp; 
sfr lcd_data_pin=0xA0;     //P2 port 
sbit rs=P1^0;              //Register select  
sbit rw=P1^1;              //Read/Write  
sbit en=P1^2;              //Enable pin 
unsigned char card_id[12]; 
 
void delay(unsigned int count)    //Function to provide dela
{ 
    int i,j; 
     for(i=0;i<count;i++) 
     for(j=0;j<1275;j++); 
} 
 
void lcd_command(unsigned char comm)   //Lcd command funtion 
{ 
     lcd_data_pin=comm; 
     en=1; 
     rs=0; 
     rw=0; 
     delay(1); 
     en=0; 
} 
 
void lcd_data(unsigned char disp)  //Lcd data function 
{ 
     lcd_data_pin=disp; 
     en=1; 
     rs=1; 
     rw=0; 
     delay(1); 
     en=0; 
} 
 
lcd_string(unsigned char *disp)     //Function to send string  
{ 
     int x; 
     for(x=0;disp[x]!=0;x++) 
    { 
         lcd_data(disp[x]); 
    } 
} 
void lcd_ini()                  //Function to initialize the LCD 
{ 
    lcd_command(0x38);           
    delay(5); 
    lcd_command(0x0F);         
    delay(5); 
    lcd_command(0x80); 
    delay(5); 
}  
 
void recieve()     //Function to recieve data serialy from RS232  
{ 
    unsigned char k; 
     for(k=0;k<12;k++) 
     {  
         while(RI==0);  
          card_id[k]=SBUF; 
          RI=0; 
    } 
} 
 
void main() 
{ 
    int l; 
    TMOD=0x20;            //Enable Timer 1 mode 2
    TH1=0xFD; 
    SCON=0x50;             // serial port control (serial mode 1 select2)
    TR1=1;                // Triggering Timer 1 
    lcd_ini(); 
    lcd_command(0x81);        //Place cursor to second position of first line  
    lcd_string("RFID CARD ID:"); 
    delay(200); 
    while(1) 
    { 
         recieve(); 
         lcd_command(0xC1);        //Place cursor to second position of second line 
         for(l=0;l<12;l++) 
         {  
              lcd_data(card_id[l]);
		     } 
	}
}	
