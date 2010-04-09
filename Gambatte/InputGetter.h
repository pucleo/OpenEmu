/*
 Copyright (c) 2009, OpenEmu Team
 All rights reserved.
 
 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are met:
     * Redistributions of source code must retain the above copyright
       notice, this list of conditions and the following disclaimer.
     * Redistributions in binary form must reproduce the above copyright
       notice, this list of conditions and the following disclaimer in the
       documentation and/or other materials provided with the distribution.
     * Neither the name of the OpenEmu Team nor the
       names of its contributors may be used to endorse or promote products
       derived from this software without specific prior written permission.
 
 THIS SOFTWARE IS PROVIDED BY OpenEmu Team ''AS IS'' AND ANY
 EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 DISCLAIMED. IN NO EVENT SHALL OpenEmu Team BE LIABLE FOR ANY
 DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef INPUTGETTER_H
#define INPUTGETTER_H

#include "gambatte.h"
#include "inputstate.h"
#include "inputstategetter.h"

namespace Gambatte {
class InputGetter : public InputStateGetter {
public:
	InputState is;
	
	InputGetter() { memset(&is, 0, sizeof(is)); }
	
	const InputState& operator()() {
		return is;
	}
	
	void FillTabInput(bool** tab)
	{
		tab[0] = &(is.startButton);
		tab[1] = &(is.selectButton);
		tab[2] = &(is.bButton);
		tab[3] = &(is.aButton);
		tab[4] = &(is.dpadDown);
		tab[5] = &(is.dpadUp);
		tab[6] = &(is.dpadLeft);
		tab[7] = &(is.dpadRight);
	}
	
	void setStart(bool b) {is.startButton = b;}
	void setSelect(bool b) {is.selectButton = b;}
	void setUp(bool b) {is.dpadUp = b;}
	void setDown(bool b) {is.dpadDown = b;}
	void setLeft(bool b) {is.dpadLeft = b;}
	void setRight(bool b) {is.dpadRight = b;}
	void setButA(bool b) {is.aButton = b;}
	void setButB(bool b) {is.bButton = b;}
	
};
}

#endif