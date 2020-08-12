/* ########################################################################

   PICsimLab - PIC laboratory simulator

   ########################################################################

   Copyright (c) : 2010-2020  Luis Claudio Gambôa Lopes

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

   For e-mail suggestions :  lcgamboa@yahoo.com
   ######################################################################## */


#include "../../ucsim/picsimlab/ucsimlib.h"

#include "board_ucsim.h"
#include"../picsimlab1.h"

#define PID_C51      0
#define PID_STM8S103 1
#define PID_Z80      2


static const char pincount[3] = {40, 20, 40};


static const char pinnames[3][40][10] = {
 {"P1.0", "P1.1", "P1.2", "P1.3", "P1.4", "P1.5", "P1.6", "P1.7", "RST", "P3.0", "P3.1", "P3.2", "P3.3",
  "P3.4", "P3.5", "P3.6", "P3.7", "XTAL2", "XTAL1", "GND", "P2.0", "P2.1", "P2.2", "P2.3", "P2.4", "P2.5",
  "P2.6", "P2.7", "/PSEN", "ALE", "/EA", "P0.7", "P0.6", "P0.5", "P0.4", "P0.3", "P0.2", "P0.1", "P0.0", "VCC"},

 {"PD4", "PD5", "PD6", "NRST", "PA1", "PA2", "VSS", "VCAP", "VDD", "PA3", "PB5", "PB4", "PC3",
  "PC4", "PC5", "PC6", "PC7", "PD1", "PD2", "PD3", "", "", "", "", "", "",
  "", "", "", "", "", "", "", "", "", "", "", "", "", ""},

 {
  "P0.0", "P0.1", "P0.2", "P0.3", "P0.4", "P0.5", "P0.6", "P0.7",  
  "P1.0", "P1.1", "P1.2", "P1.3", "P1.4", "P1.5", "P1.6", "P1.7", 
  "P2.0", "P2.1", "P2.2", "P2.3", "P2.4", "P2.5", "P2.6", "P2.7",
  "P3.0", "P3.1", "P3.2", "P3.3", "P3.4", "P3.5", "P3.6", "P3.7",
  "RST","INT1","INT2", "INT3", "INT5","INT7", "GND", "VCC" }
};


const unsigned char UCSIM_PORTS[5] = {0, 1, 2, 3, 0xFF};

board_ucsim::board_ucsim(void)
{
 procid = -1;
}

void
board_ucsim::MSetSerial(const char * port) {
 /*
 set_serial (&pic,0, port, 0, 0, 0);
 set_serial (&pic,1, "", 0, 0, 0);
  */ }

int
board_ucsim::MInit(const char * processor, const char * fname, float freq)
{
 char fbuff[20];

 if (!strcmp ("C51", processor))
  {
   procid = PID_C51;
  }
 else if (!strcmp ("STM8S103", processor))
  {
   procid = PID_STM8S103;
  }
 else if (!strcmp ("Z80", processor))
  {
   procid = PID_Z80;
  }

 pins_reset ();

 sprintf (fbuff, "%i", (int) freq);

 int ret = ucsim_init (processor, fbuff, fname, SERIALDEVICE, Window1.Get_debug_port ());

 return ret;
}

void
board_ucsim::MEnd(void)
{
 ucsim_end (); //TODO
}

void
board_ucsim::MEraseFlash(void) {
 //erase_flash ();
}

void
board_ucsim::MSetFreq(float freq_)
{
 freq = freq_;
}

float
board_ucsim::MGetFreq(void)
{
 return freq;
}

float
board_ucsim::MGetInstClock(void)
{
 return freq;
}

int
board_ucsim::CpuInitialized(void)
{
 return 1;
}

void
board_ucsim::DebugLoop(void) { }

String
board_ucsim::MGetPinName(int pin)
{
 String pinname = "error";

 if ((pin)&&(pin <= MGetPinCount ()))
  pinname = pinnames[procid][pin - 1];

 return pinname;
}

void
board_ucsim::MDumpMemory(const char * fname)
{
 ucsim_dump (fname);
}

int
board_ucsim::DebugInit(int dtyppe) //argument not used in picm only mplabx
{
 return 0; //!mplabxd_init (this, Window1.Get_debug_port ()) - 1;
}

int
board_ucsim::MGetPinCount(void)
{
 return pincount[procid];
}

void
board_ucsim::pins_reset(void)
{

 if ((procid == PID_C51) || (procid == PID_Z80))
  {
   for (int p = 0; p < MGetPinCount (); p++)
    {
     String pname = MGetPinName (p + 1);
     if (pname[0] == 'P')
      {
       pins[p].port = (unsigned char *) &UCSIM_PORTS[pname[1] - '0'];
       pins[p].pord = pname[3] - '0';
      }
     else
      {
       pins[p].port = (unsigned char *) &UCSIM_PORTS[4];
       pins[p].pord = -1;
      }
     pins[p].avalue = 0;
     pins[p].lvalue = 0;
     pins[p].value = 0;
     pins[p].ptype = PT_CMOS;
     pins[p].dir = PD_IN;
     pins[p].ovalue = 0;
     pins[p].oavalue = 0;
    }

   //TODO
   //VCC pins
   //pins[6].value = 1;
   //pins[19].value = 1;
  }
 else if (procid == PID_STM8S103)
  {
   for (int p = 0; p < MGetPinCount (); p++)
    {
     String pname = MGetPinName (p + 1);
     if (pname[0] == 'P')
      {
       pins[p].port = (unsigned char *) &UCSIM_PORTS[pname[1] - 'A'];
       pins[p].pord = pname[2] - '0';
      }
     else
      {
       pins[p].port = (unsigned char *) &UCSIM_PORTS[4];
       pins[p].pord = -1;
      }
     pins[p].avalue = 0;
     pins[p].lvalue = 0;
     pins[p].value = 0;
     pins[p].ptype = PT_CMOS;
     pins[p].dir = PD_IN;
     pins[p].ovalue = 0;
     pins[p].oavalue = 0;
    }

   //TODO
   //VCC pins
   //pins[6].value = 1;
   //pins[19].value = 1;
  }

}

void
board_ucsim::MSetPin(int pin, unsigned char value)
{
 ucsim_set_pin (*pins[pin - 1].port, pins[pin - 1].pord, value);
}

void
board_ucsim::MSetPinDOV(int pin, unsigned char ovalue) {
 //set_pin_DOV (pin, ovalue);
}

void
board_ucsim::MSetAPin(int pin, float value) {
 //set_apin (pin, value);
}

unsigned char
board_ucsim::MGetPin(int pin)
{
 return ucsim_get_pin (*pins[pin - 1].port, pins[pin - 1].pord);
}

void
board_ucsim::MReset(int flags)
{
 ucsim_reset ();
}

const picpin *
board_ucsim::MGetPinsValues(void)
{
 return pins;
}

void
board_ucsim::MStep(void)
{
 unsigned char p[4];

 ucsim_step ();

 p[0] = ucsim_get_port (0);
 p[1] = ucsim_get_port (1);
 p[2] = ucsim_get_port (2);
 p[3] = ucsim_get_port (3);

 for (int i = 0; i < MGetPinCount (); i++)
  {
   if (*pins[i].port < 4)
    {
     pins[i].value = (p[*pins[i].port] & (1 << pins[i].pord)) > 0;
    }
  }

}

void
board_ucsim::MStepResume(void) {
 //if (pic.s2 == 1)step ();
}
