#include "GPIO.h"
#include "HardwareTimer.h"
#include "IOConfig.h"
#include "System.h"
#include "XPD.h"
#include "Thread.h"
using namespace sxc;

volatile int asd;



int detect(sxc::SystemClock& sysClock) {

  sxc::GPDPin myPin(6, sxc::Direction::Input, sxc::Polarity::ActiveLow);

  
  // start timer at 24576 ticks (this is 1 millisecond)
  auto timer = sysClock.GetTimer(24576);

  int milliseconds = 500;
  int counter = 0;
  int freq = 0;
  int p = 0;
  
  while (true) {
    // HasCapture tells checks if we saw a RisingOrFalling edge, then clears the result
	// if it saw a rising edge, add one to counter
	  if (myPin.IsLow()) {
		  if (p == 0) {
		  counter++;
		  p = 1;
		  }
	  }
	  if (myPin.IsHigh()) {
		  p = 0;
	  }
	  
    // If the timer elapsed, tell it to tick another 24576 times, but decrease milliseconds
    // If we run out of milliseconds, break this while loop
    if (timer.HasElapsed()) {
      if (--milliseconds == 0) break;

	  freq = 2*counter;
      timer.Tick(24576);
    }
  }

  sxc::xout << "Frequency is " << freq << " Hz!" << sxc::endl;
  sxc::xout << "Counted " << counter  << sxc::endl;

  return freq;
}

int motor(sxc::SystemClock& sysClock, int x) {

sxc::GPDPin myPin(1, Direction::Output);
myPin.SetInactive(); 


int n;
	
n = x*3;

if ( x > 50 || x < -50){
}

if (x < 0 && x > -50) {
	while (n != 0){
		n = n + 1;
		myPin.SetActive();
		for (int i = 0; i < 4; ++i){
			sxc::SystemClock::Wait(24576);}
		myPin.SetInactive();
		for (int i = 0; i < 20; ++i){
			sxc::SystemClock::Wait(24576);}
	}
}


if (x > 0 && x < 50) {
	while (n != 0){
		n = n - 1;
		myPin.SetActive();
		sysClock.GetTimer(49152).Wait();
		myPin.SetInactive();
		for (int i = 0; i < 20; ++i){
			sxc::SystemClock::Wait(24576);}
	}
}
}


int check (int a, int b, int c, int d, int e) {
	int upmargin = a + 4;			//upper margin of a
	int downmargin = a - 4;			//lower margin of a
	int n = 0;							//counter for whether inside margin

	while (true) {
	if (b == a) {n = n+2;}			//if equal to a, add two to count because it happened twice
	if (b < a) {
		//if greater than a, check if greater than down margin. If it is, add one to count. Otherwise, countine
		if (b >= downmargin) {n++;} }
	if (b > a) {
		if (b <= upmargin) {n++;}}

	if (c == a) {n = n+2;}			//if equal to a, add one to count
	if (c < a) {
		//if greater than a, check if greater than down margin. If it is, add one to count. Otherwise, countine
		if (c >= downmargin) {n++;} }
	if (c > a) {
		if (c <= upmargin) {n++;}}

	if (d == a) {n = n+2;}			//if equal to a, add one to count
	if (d < a) {
		//if greater than a, check if greater than down margin. If it is, add one to count. Otherwise, countine
		if (d >= downmargin) {n++;} }
	if (d > a) {
		if (d <= upmargin) {n++;}}

	if (e == a) {n = n+2;}			//if equal to a, add one to count
	if (e < a) {
		//if greater than a, check if greater than down margin. If it is, add one to count. Otherwise, countine
		if (e >= downmargin) {n++;} }
	if (e > a) {
		if (e <= upmargin) {n++;}}

	break;
}
	return n;
}

int standard(int a, int b) {
	int w;
while (true) {
	//case 1: string selected is 1 (E4)
	if (a==1) {
    w = 330 - b;	 //subtract freq from 329.63 and store in freqdiff
    sxc::xout << "You chose Stadard tuning and string 1. Verify the Freq diff" << sxc::endl;    // just for testing REMOVE AFTER
    break;}

	//case 2: string selected is 2 (B3)
	if (a==2) { 
	w = 247 - b;	 //subtract freq from 246.94 and store in freqdiff
    sxc::xout << "You chose Stadard tuning and string 2. Verify the Freq diff" << sxc::endl;    // just for testing REMOVE AFTER
    break;}

	//case 3: string selected is 3 (G3)
	if (a==3) {	 
    w = 196 - b;	 //subtract freq from 196 and store in freqdiff
    sxc::xout << "You chose Stadard tuning and string 3. Verify the Freq diff"<< sxc::endl;    // just for testing REMOVE AFTER
    break;}

	//case 4: string selected is 4 (D3)
	if (a==4) {
    w = 147 - b;	 //subtract freq from 146.83 and store in freqdiff
    sxc::xout << "You chose Stadard tuning and string 4. Verify the Freq diff"<< sxc::endl;    // just for testing REMOVE AFTER
    break;}

	//case 5: string selected is 5 (A2)
	if (a==5) {
    w = 110 - b;	 //subtract freq from 110 and store in freqdiff
    sxc::xout << "You chose Stadard tuning and string 5. Verify the Freq diff"<< sxc::endl;    // just for testing REMOVE AFTER
	break;}

	//case 6: string selected is 6 (E2)
	if (a==6) { 
    w = 82 - b;	 //subtract freq from 82.41 and store in freqdiff
    sxc::xout << "You chose Stadard tuning and string 6. Verify the Freq diff"<< sxc::endl;    // just for testing REMOVE AFTER
	break;}
	
	sxc::xout << "Error"<< sxc::endl;    // just for testing REMOVE AFTER
	}

return w;
}

int dropd(int a, int b) {
	int w;
while (true) {
	//case 1: string selected is 1 (E4)
	if (a==1) {	 
    w = 330 - b;	 //subtract freq from 329.63 and store in freqdiff
    sxc::xout << "You chose DropD tuning and string 1. Verify the Freq diff"<< sxc::endl;    // just for testing REMOVE AFTER
	break;}

	//case 2: string selected is 2 (B3)
	if (a==2) { 
    w = 247 - b;	 //subtract freq from 246.94 and store in freqdiff
    sxc::xout << "You chose DropD tuning and string 2. Verify the Freq diff"<< sxc::endl;    // just for testing REMOVE AFTER
    break;}

	//case 3: string selected is 3 (G3)
	if (a==3) { 
    w = 196 - b;	 //subtract freq from 196 and store in freqdiff
    sxc::xout << "You chose DropD tuning and string 3. Verify the Freq diff"<< sxc::endl;    // just for testing REMOVE AFTER
	break;}

	//case 4: string selected is 4 (D3)
	if (a==4) {
    w = 147 - b;	 //subtract freq from 146.83 and store in freqdiff
    sxc::xout << "You chose DropD tuning and string 4. Verify the Freq diff"<< sxc::endl;    // just for testing REMOVE AFTER
	break;}

	//case 5: string selected is 5 (A2)
	if (a==5) {	 
    w = 110 - b;	 //subtract freq from 110 and store in freqdiff
    sxc::xout << "You chose DropD tuning and string 5. Verify the Freq diff"<< sxc::endl;    // just for testing REMOVE AFTER
	break;}

	//case 6: string selected is 6 (D2)
	if (a==6) {	 
    w = 73 - b;	 //subtract freq from 73.42 and store in freqdiff
    sxc::xout << "You chose DropD tuning and string 6. Verify the Freq diff"<< sxc::endl;    // just for testing REMOVE AFTER
	break;}

  	sxc::xout << "Error"<< sxc::endl;    // just for testing REMOVE AFTER
	}

return w;
}

int dadgad(int a, int b){
	int w;
while (true) {
	//case 1: string selected is 1 (D4)
	if (a==1) { 
    w = 294 - b;	 //subtract freq from 293.66 and store in freqdiff
    sxc::xout << "You chose DADGAD tuning and string 6. Verify the Freq diff"<< sxc::endl;    // just for testing REMOVE AFTER
	break; }

	//case 2: string selected is 2 (A3)
	if (a==2) {	 
    w = 220 - b;	 //subtract freq from 220 and store in freqdiff
    sxc::xout << "You chose DADGAD tuning and string 6. Verify the Freq diff"<< sxc::endl;    // just for testing REMOVE AFTER
	break; }

	//case 3: string selected is 3 (G3)
	if (a==3) { 
    w = 196 - b;	 //subtract freq from 196 and store in freqdiff
    sxc::xout << "You chose DADGAD tuning and string 6. Verify the Freq diff"<< sxc::endl;    // just for testing REMOVE AFTER
	break; }

	//case 4: string selected is 4 (D3)
	if (a==4) {
    w = 147 - b;	 //subtract freq from 146.83 and store in freqdiff
    sxc::xout << "You chose DADGAD tuning and string 6. Verify the Freq diff"<< sxc::endl;    // just for testing REMOVE AFTER
	break; }

	//case 5: string selected is 5 (A2)
	if (a==5) { 
    w = 110 - b;	 //subtract freq from 110 and store in freqdiff
    sxc::xout << "You chose DADGAD tuning and string 6. Verify the Freq diff"<< sxc::endl;    // just for testing REMOVE AFTER
	break;}

	//case 6: string selected is 6 (D2)
	if (a==6) { 
    w = 73 - b;	 //subtract freq from 73.42 and store in freqdiff
    sxc::xout << "You chose DADGAD tuning and string 6. Verify the Freq diff"<< sxc::endl;    // just for testing REMOVE AFTER
	break;}

	  	sxc::xout << "Error"<< sxc::endl;    // just for testing REMOVE AFTER
}

return w;
}

int led_indicator(int freqdiff) {
	//sxc::SystemClock& sysClock
int b = 0;

 sxc::GPAPin LED_H(7, sxc::Direction::Output);
 sxc::GPAPin LED_L(6, sxc::Direction::Output);
 sxc::GPAPin LED_T(5, sxc::Direction::Output);


LED_H.SetInactive();
LED_L.SetInactive(); 
LED_T.SetInactive(); 

		if (freqdiff <= 4 && freqdiff >= -4) {
		b = 3; }		
 
		else if (freqdiff < 4 ) {
		b = 1;}

       else if (freqdiff > -4) {
		b = 2;}


		while (b==1) {
			LED_H.SetActive(); // set the Too High LED pin high
			LED_L.SetInactive();
			LED_T.SetInactive();     
			
			for (int i = 0; i < 5000; ++i){
				sxc::SystemClock::Wait(24576);}

			//turning off LEDs
			LED_H.SetInactive();
			LED_L.SetInactive(); 
			LED_T.SetInactive(); 

			sxc::xout << "Red ON " << sxc::endl;
			break;
		}

		while (b==2) {
			LED_H.SetInactive();
			LED_L.SetActive(); // set the Too Low LED pin high
			LED_T.SetInactive(); 
		
			for (int i = 0; i < 5000; ++i){
				sxc::SystemClock::Wait(24576);}

			//turning off LEDs
			LED_H.SetInactive();
			LED_L.SetInactive(); 
			LED_T.SetInactive(); 
		
			sxc::xout << "Blue ON " << sxc::endl;
			break;
		}

		while (b==3) {
			LED_H.SetInactive(); 
			LED_L.SetInactive();
			LED_T.SetActive(); // set the In Tune LED pin high

			for (int i = 0; i < 5000; ++i){
				sxc::SystemClock::Wait(24576);}

			//turning off LEDs
			LED_H.SetInactive();
			LED_L.SetInactive();
			LED_T.SetInactive(); 
		
			sxc::xout << "Green ON " << sxc::endl;
			break;
		}

		sxc::xout << "B is: " << b << sxc::endl;
return b;}

int strum_indicator(sxc::SystemClock& sysClock) {
	sxc::GPAPin strum(4, sxc::Direction::Output);

	while (true) {
		strum.SetActive();

		for (int i = 0; i < 5000; ++i){
				sxc::SystemClock::Wait(24576);}

		strum.SetInactive();
		break;}
	}

int tuneselect(int aaa){

sxc::GPEPin A_Tun(7, sxc::Direction::Output);
sxc::GPEPin B_Tun(6, sxc::Direction::Output);
sxc::GPHPin PB_Tun(0, sxc::Direction::Input, Polarity::ActiveLow);

//Set custom IOCTable to initialize pullup() for H class Pins
constexpr auto CustomIOCTable = sxc::stdcfg::GinsengIOCTable.SetPH(sxc::stdcfg::GinsengIOC.PullUp());
sxc::IOConfigTable ioc(CustomIOCTable);

A_Tun.SetInactive();
B_Tun.SetInactive();
int tuning;
int aa = 0;          //counter b

repeata:

while (aaa!=0){
	if (asd==1) {goto end_t;}
}


while(aaa==0){

if (asd==1) {goto end_t;}

for (int i = 0; i < 300; ++i){
sxc::SystemClock::Wait(24576);}
     if (PB_Tun.IsLow()) {
aa++;
break;}
}



switch(aa){

case 1: {
A_Tun.SetActive();
B_Tun.SetInactive();
tuning=1;
}

goto repeata;

case 2: {
A_Tun.SetInactive();
B_Tun.SetActive();
tuning=2;}

goto repeata;

case 3: {
A_Tun.SetActive();
B_Tun.SetActive();
tuning=3;
aa=0;	}

goto repeata;
}


switch(aaa){

case 1: {
A_Tun.SetActive();
B_Tun.SetInactive();
tuning=1;
}

goto repeata;

case 2: {
A_Tun.SetInactive();
B_Tun.SetActive();
tuning=2;}

goto repeata;

case 3: {
A_Tun.SetActive();
B_Tun.SetActive();
tuning=3;}

goto repeata;
}


end_t:
return tuning;}		

int stringselect(int bbb){

//Intialize String Push Buttons and outputs
sxc::GPEPin A_Str(3, sxc::Direction::Output);
sxc::GPEPin B_Str(2, sxc::Direction::Output);
sxc::GPEPin C_Str(1, sxc::Direction::Output);
sxc::GPHPin PB_Str(1, sxc::Direction::Input, Polarity::ActiveLow);

//Set custom IOCTable to initialize pullup() for H class Pins
constexpr auto CustomIOCTable = sxc::stdcfg::GinsengIOCTable.SetPH(sxc::stdcfg::GinsengIOC.PullUp());
sxc::IOConfigTable ioc(CustomIOCTable);

A_Str.SetInactive();
B_Str.SetInactive();
C_Str.SetInactive();

int string;
int bb = 0;          //counter b

repeatb:
while (bbb!=0){
	if (asd==1) {goto end_s;}
}

while (bbb=0) {   

if (asd==1) { goto end_s;}

for (int i = 0; i < 190; ++i){
sxc::SystemClock::Wait(24576);}   //Wait Here for 150*20ms
     if (PB_Str.IsLow()) {
bb++;
break;}
}

switch(bb){

case 1: {
A_Str.SetActive();
B_Str.SetInactive();
C_Str.SetInactive();
string=1;
}

goto repeatb;
case 2: {
A_Str.SetInactive();
B_Str.SetActive();
C_Str.SetInactive();
string=2;}

goto repeatb;
case 3: {
A_Str.SetActive();
B_Str.SetActive();
C_Str.SetInactive();
string=3;}

goto repeatb;
case 4: {

A_Str.SetInactive();
B_Str.SetInactive();
C_Str.SetActive();
string=4;}

goto repeatb;
case 5: {
A_Str.SetActive();
B_Str.SetInactive();
C_Str.SetActive();
string=5;}

goto repeatb;
case 6: {
A_Str.SetInactive();
B_Str.SetActive();
C_Str.SetActive();
string=6;
bb=0;}


goto repeatb;
}

switch(bbb){

case 1: {
A_Str.SetActive();
B_Str.SetInactive();
C_Str.SetInactive();
string=1;
}

goto repeatb;
case 2: {
A_Str.SetInactive();
B_Str.SetActive();
C_Str.SetInactive();
string=2;}

goto repeatb;
case 3: {
A_Str.SetActive();
B_Str.SetActive();
C_Str.SetInactive();
string=3;}

goto repeatb;
case 4: {

A_Str.SetInactive();
B_Str.SetInactive();
C_Str.SetActive();
string=4;}

goto repeatb;
case 5: {
A_Str.SetActive();
B_Str.SetInactive();
C_Str.SetActive();
string=5;}

goto repeatb;
case 6: {
A_Str.SetInactive();
B_Str.SetActive();
C_Str.SetActive();
string=6;
bb=0;}


goto repeatb;
}

end_s:
return string;}




int main() {
// Setup system Frequency to 24.576MHz from a crystal with 12.288MHz
auto sysFreq = sxc::SystemFrequency::_24_576_MHz;
auto crystalFreq = sxc::CrystalFrequency::_12_288_MHz;
sxc::SystemClock sysClock(crystalFreq, sysFreq);
// Configure the standard IOConfiguration
sxc::IOConfigTable iocTable(sxc::stdcfg::GinsengIOCTable);
// Configure Varactor to stabilize crystal (probably don't actually need to do this)
sxc::Varactor varactor(sysFreq);

// Setup TimerA with a Divider of 256, this means TimerA will tick at 24.576MHz / 256 = 96kHz
sxc::TimerA timerA(sxc::HardwareTimerDivider::_256);

sxc::xout << "Starting:" << sxc::endl;


int aaa = 0;
int bbb = 0;


repeat:

sxc::Thread parallelTune(tuneselect,aaa);
sxc::Thread parallelString(stringselect,bbb);

sxc::xout << "Repeat again "<< sxc::endl;

	int z = 0;
	//variables for detecting frequency
	int x1 = 0;
	int x2 = 0;
	int x3 = 0;
	int x4 = 0;
	int x5 = 0;
	int n1 = 0;
	int n2 = 0;
	int n3 = 0;
	int n4 = 0;
	int n5 = 0;
	int freqT = 0;
	int freqmode = 60;

	//variables for comparing frequency
	int tuningg;
	int stringg;
	int freqdiff;
	
	
	
// Initialize Push Button Start
sxc::GPHPin PB_Start(2, sxc::Direction::Input, Polarity::ActiveLow);
//Set custom IOCTable to initialize pullup() for H class Pins
constexpr auto CustomIOCTable = sxc::stdcfg::GinsengIOCTable.SetPH(sxc::stdcfg::GinsengIOC.PullUp());
sxc::IOConfigTable ioc(CustomIOCTable);

while(true){
for (int i = 0; i < 500; ++i){
sxc::SystemClock::Wait(24576);}

if (PB_Start.IsLow()){
	asd=1;

	parallelTune.Join();
	parallelString.Join();

	stringg = parallelString.ExitCode();
	tuningg = parallelTune.ExitCode();

	asd = 0;
break;}
}

sxc::xout << "y is: "<< asd << sxc::endl;	
sxc::xout << "String selected: "<< stringg << sxc::endl;	
sxc::xout << "Tuning mode is: "<< tuningg << sxc::endl;	
  


	  
	//detecting the frequency
/*	while (true) {

		if (z==0) {
			i++; 
			sxc::xout << "Iteration: " << i << sxc::endl;
			x1 = detect(sysClock);

			i++; 
			sxc::xout << "Iteration: " << i << sxc::endl;
			x2 = detect(sysClock);

			i++; 
			sxc::xout << "Iteration: " << i << sxc::endl;
			x3 = detect(sysClock);

			i++; 
			sxc::xout << "Iteration: " << i << sxc::endl;
			x4 = detect(sysClock);

			i++; 
			sxc::xout << "Iteration: " << i << sxc::endl;
			x5 = detect(sysClock);
			
			freqT = x1+x2+x3+x4+x5 ;
			sxc::xout << "Frequency Total" << freqT << sxc::endl;
			
			z = 1;			
		}
		
		if (z==1) break;
	}

	//checking which frequency to use
	while (true) {
		n1 = check(x1, x2, x3, x4, x5);
		n2 = check(x2, x1, x3, x4, x5);
		n3 = check(x3, x1, x2, x4, x5);
		n4 = check(x4, x1, x2, x3, x5);
		n5 = check(x5, x1, x2, x3, x4);
		
		freqmode = x1;		//stores frequency that occurs the most
		int max;			//stores max number of times a freq occurs
		max = n1;			//initializes max with n1

		while (true) {
		if (n2 >= max) {max = n2; freqmode = x2;}
		if (n3 >= max) {max = n3; freqmode = x3;}
		if (n4 >= max) {max = n4; freqmode = x4;}
		if (n5 >= max) {max = n5; freqmode = x5;}

		break;}

		sxc::xout << "Frequency mode:" << freqmode << sxc::endl;
		break;
	}*/

	//comparing the frequency to reference

  while (true) {
	//standard tuning
	if (tuningg == 1){
		freqdiff = standard(stringg, freqmode); 
	break;}         

	//dropd tuning
    if (tuningg == 2){
		freqdiff = dropd(stringg, freqmode);
	break;}

	//dadgad tuning
    if (tuningg == 3){
        freqdiff = dadgad(stringg, freqmode); 
	break;}

	}

	sxc::xout << "The Frequency difference is: " << freqdiff << "Hz" << sxc::endl;	

//start thread to turn on LEDs on while motor is turning
sxc::Thread ledindicate(led_indicator, freqdiff);

sxc::xout << "LED thread started " << sxc::endl;	


//turning motor
motor(sysClock, freqdiff);
sxc::xout << "Motor started " << sxc::endl;	

//turning on LED indicators
//int b = 0;
//b = led_indicator(sysClock, freqdiff);


//goes back to thread and checks if it is done running
ledindicate.Join();

//stores result of thread into b
int b = ledindicate.ExitCode();
sxc::xout << "LED thread ended " << sxc::endl;	

sxc::xout << "B is "<< b << sxc::endl;	

//wait awhile before asking users to strum again
for (int ii = 0; ii < 5000; ++ii){
	sxc::SystemClock::Wait(24576);}

//turning on strum indicators
if (b!=3) {
	sxc::xout << "Strum again "<< sxc::endl;	
	strum_indicator(sysClock);
	aaa = tuningg;
	bbb = stringg;
	goto repeat;
}



  return 0;
} 


