#include <reg51.h>
#include<stdio.h>
#define NUMBER 9844400424

// connected pins
// keypad rows
sbit keyrow1 = P2 ^ 0;
sbit keyrow2 = P2 ^ 1;
sbit keyrow3 = P2 ^ 2;
sbit keyrow4 = P2 ^ 3;
//keypad column
sbit keycolumn1 = P2 ^ 4;
sbit keycolumn2 = P2 ^ 5;
sbit keycolumn3 = P2 ^ 6;


// lcd pins
sbit rs = P3 ^ 5;
sbit rw = P3 ^ 6;
sbit en = P3 ^ 7;

//buzzer
sbit buzzer=P3 ^2;

//led
sbit led1=P3^3;
sbit led2=P3^4;

//functions
void lcdcmd(unsigned char);
void lcddat(unsigned char);
void lcddisplay(unsigned char *q);
char keypad();
void check();
void start();
void delay(unsigned int);
unsigned char pin[] = {"11111"};
unsigned char Epin[5];
//for counter
int k;
char ch[12];
void lcd(char a,int b);


//functions for GSM
void ser_init();
void tx(unsigned char send);
void tx_str(unsigned char *s);
unsigned char rx();
void sms(unsigned char *num1,unsigned char *msg);
// main function
void main()
{
	led1=0;
	led2=0;
	buzzer=0;
		lcdcmd(0x0F); //decimal value: 15
    lcdcmd(0x38); //decimal value: 56
    lcdcmd(0x01); //decimal value: 1
		TMOD=0x05;
		start();
}
void start(){
	while(1){
      unsigned int i = 0;
			buzzer=1;
			delay(1000);
			buzzer=0;9
			lcdcmd(0x80);
			lcddisplay(" WELCOME TO PBHS");
			
			delay(20000);
			lcdcmd(0x01);
			lcdcmd(0X80);
       //lcdcmd(0x80); //decimal value: 128
       lcddisplay("ENTER PIN NUMBER");
       delay(1000);
       lcdcmd(0xc0); //decimal value: 192
       while (pin[i] != '\0')
       {
         delay(20);  
				 Epin[i] = keypad();
           delay(1000);
           i++;
       }
			check();
    }
	}

//delay function
void delay(unsigned int j)
{
    int a, b;
    for (a = 0; a < j; a++)
    {
        for (b = 0; b < 10; b++)
            ;
    }
}

// lcd commands functions
void lcdcmd(unsigned char A)
{
    P1 = A;
    rs = 0;
    rw = 0;
    en = 1;
    delay(1000);
    en = 0;
}

//lcd data function

void lcddat(unsigned char i)
{
    P1 = i;
    rs = 1;
    rw = 0;
    en = 1;
    delay(1000);
    en = 0;
}

//lcd display charecters function

void lcddisplay(unsigned char *q)
{
    int k;
    for (k = 0; q[k] != '\0'; k++)
    {
        lcddat(q[k]);
    }
    delay(1000);
}

// assign keypad character value function

char keypad()
{
    int x = 0;
    while (x == 0)
    {
        // assign values for first row
        keyrow1 = 0;
        keyrow2 = 1;
        keyrow3 = 1;
        keyrow4 = 1;
				
        if (keycolumn1 == 0)
        {
            
					lcddat('X');
					delay(1000);
            x = 1;
            return '1';
        }
        if (keycolumn2 == 0)
        {
						lcddat('X');
            delay(1000);
            x = 1;
            return '2';
        }
        if (keycolumn3 == 0)
        {
          lcddat('X');					
					delay(1000);
          x = 1;
          return '3';
        }

        // assign values for second row
        keyrow1 = 1;
        keyrow2 = 0;
        keyrow3 = 1;
        keyrow4 = 1;

        if (keycolumn1 == 0)
        {
            //lcddat('*');
          lcddat('X');  
					delay(1000);
            x = 1;
				
            return '4';
        }
        if (keycolumn2 == 0)
        {
            //lcddat('*');
					lcddat('X');
            delay(1000);
            x = 1;
            return '5';
        }
        if (keycolumn3 == 0)
        {
            //lcddat('*');
						lcddat('X');
            delay(1000);
            x = 1;
            return '6';
        }
        // assign values for third row
        keyrow1 = 1;
        keyrow2 = 1;
        keyrow3 = 0;
        keyrow4 = 1;
        if (keycolumn1 == 0)
        {
            //lcddat('*');
						lcddat('X');
            delay(1000);
            x = 1;
            return '7';
        }
        if (keycolumn2 == 0)
        {
            //lcddat('*');
					lcddat('X');
            delay(1000);
            x = 1;
            return '8';
        }
        if (keycolumn3 == 0)
        {
            //lcddat('*');
					lcddat('X');
            delay(1000);
            x = 1;
            return '9';
        }
        // assign values for forth row
        keyrow1 = 1;
        keyrow2 = 1;
        keyrow3 = 1;
        keyrow4 = 0;

        if (keycolumn1 == 0)
        {
            lcddat('X');
            delay(1000);
            x = 1;
            return '*';
        }
        if (keycolumn2 == 0)
        {
            lcddat('X');
            delay(1000);
            x = 1;
            return '0';
        }
        if (keycolumn3 == 0)
        {
            lcddat('X');
            delay(1000);
            x = 1;
            return '#';
        }
    }
	
}

// password check function and run the door motor
void check()
{
    //  compare the input value with the assign password value
    if (pin[0] == Epin[0] && pin[1] == Epin[1] && pin[2] == Epin[2] && pin[3] == Epin[3] && pin[4] == Epin[4])
    {
        delay(1000);
        lcdcmd(0x01); //decimal value: 1
        lcdcmd(0x81); //decimal value: 129
        // show pin is correct
				led1=1;
				
        lcddisplay("PIN CORRECT");
        delay(1000);
				
        lcdcmd(0xc1); //decimal value: 193
        // show the door is unlocked
        lcddisplay("DOOR OPENED");
        delay(10000);
				buzzer=1;
        delay(100);
        lcdcmd(0x01); //decimal value: 1
			led1=0;
			buzzer=0;
    }
			
    else
    {		
			lcdcmd(0x01); //decimal value: 1
      lcdcmd(0x80); //decimal value: 128
			led2=1;
				buzzer=1;
        lcddisplay("WRONG PIN");
        delay(1000);
				//buzzer=1;
			delay(10000);
			ser_init();
			sms(NUMBER,"PIN INCORRECT");
      lcdcmd(0x01); //decimal value: 1
			led2=0;
			buzzer=0;
			counter();
    }
}
void lcd(char a,int b){
		P1=a;
     rs=b;
     rw=0;
     en=1;
     delay(100);
     en=0;
     delay(100);
}
//gsm
void ser_init()
{
  SCON=0x50;
  TMOD=0x21;
  TH1=0xFD;
  TL1=0xFD;
  TR1=1;
}

void tx(unsigned char send)
{
  SBUF=send;
  while(TI==0);
  TI=0;
}

void tx_str(unsigned char *s)
{
  while(*s)
    tx(*s++);
}

unsigned char rx()
{
  while(RI==0);
  RI=0;
  return SBUF;
}
void sms(unsigned char *num1,unsigned char *msg)
{
  tx_str("AT");
  tx(0x0d);
  delay(200);

  tx_str("AT+CMGF=1");
  tx(0x0d);
  delay(200);

  tx_str("AT+CMGS=");
  tx('"');
  while(*num1)
    tx(*num1++);
  tx('"');
  tx(0x0d);
  delay(200);

  while(*msg)
    tx(*msg++);
  tx(0x1a);
  delay(200);
}