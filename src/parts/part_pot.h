	/* ########################################################################

	   PICsimLab - PIC laboratory simulator

	   ########################################################################

	   Copyright (c) : 2010-2015  Luis Claudio Gambôa Lopes

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

#ifndef PART_POT_H
#define	PART_POT_H

#include<lxrad.h>
#include"part.h"

class cpart_pot:public part
{
    public:
      lxString GetName(void){return lxT("Potentiometers");};
      lxString GetHelpURL(void){return lxT("Potentiometers.html");};
      lxString GetAboutInfo(void){return lxT("L.C. Gamboa \n <lcgamboa@yahoo.com>");};            
      cpart_pot(unsigned x, unsigned y);
      ~cpart_pot(void); 
      void Draw(void);
      void PreProcess(void);
      lxString GetPictureFileName(void){return lxT("pot/pot.png");};
      lxString GetInputMapFile(void){return lxT("pot/pot_i.map");};
      lxString GetOutputMapFile(void){return lxT("pot/pot_o.map");};
      lxString GetPropertiesWindowFile(void){return lxT("pot/pot.lxrad");};
      void EvMouseButtonPress(uint button, uint x, uint y,uint state);
      void EvMouseButtonRelease(uint button, uint x, uint y,uint state);
      void EvMouseMove(uint button, uint x, uint y,uint state);
      void ConfigurePropertiesWindow(CPWindow *  WProp);
      void ReadPropertiesWindow(CPWindow * WProp);
      lxString WritePreferences(void);
      void ReadPreferences(lxString value);
      unsigned short get_in_id(char * name);
      unsigned short get_out_id(char * name);
    private:
      void RegisterRemoteControl(void);          
      unsigned char output_pins[4]; 
      unsigned char values[4];
      unsigned char active[4];
};




#endif	/* POT */

