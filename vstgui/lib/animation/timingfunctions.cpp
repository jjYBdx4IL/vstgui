//-----------------------------------------------------------------------------
// VST Plug-Ins SDK
// VSTGUI: Graphical User Interface Framework for VST plugins : 
//
// Version 4.0
//
//-----------------------------------------------------------------------------
// VSTGUI LICENSE
// (c) 2010, Steinberg Media Technologies, All Rights Reserved
//-----------------------------------------------------------------------------
// Redistribution and use in source and binary forms, with or without modification,
// are permitted provided that the following conditions are met:
// 
//   * Redistributions of source code must retain the above copyright notice, 
//     this list of conditions and the following disclaimer.
//   * Redistributions in binary form must reproduce the above copyright notice,
//     this list of conditions and the following disclaimer in the documentation 
//     and/or other materials provided with the distribution.
//   * Neither the name of the Steinberg Media Technologies nor the names of its
//     contributors may be used to endorse or promote products derived from this 
//     software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A  PARTICULAR PURPOSE ARE DISCLAIMED. 
// IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, 
// INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, 
// BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, 
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
// LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE 
// OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE  OF THIS SOFTWARE, EVEN IF ADVISED
// OF THE POSSIBILITY OF SUCH DAMAGE.
//-----------------------------------------------------------------------------

#include "timingfunctions.h"
#include "../vstguibase.h"

namespace VSTGUI {
namespace Animation {

//-----------------------------------------------------------------------------
LinearTimingFunction::LinearTimingFunction (unsigned long length)
: TimingFunctionBase (length)
{
}

//-----------------------------------------------------------------------------
float LinearTimingFunction::getPosition (unsigned long milliseconds) 
{
	float pos = ((float)milliseconds) / ((float)length);
	if (pos > 1.f)
		pos = 1.f;
	else if (pos < 0.f)
		pos = 0.f;
	return pos;
}

//-----------------------------------------------------------------------------
bool LinearTimingFunction::isDone (unsigned long milliseconds)
{
	return milliseconds >= length;
}

//-----------------------------------------------------------------------------
RepeatTimingFunction::RepeatTimingFunction (TimingFunctionBase* tf, long repeatCount, bool autoReverse)
: tf (tf)
, repeatCount (repeatCount)
, autoReverse (autoReverse)
, isReverse (false)
, runCounter (0)
{
}

//-----------------------------------------------------------------------------
RepeatTimingFunction::~RepeatTimingFunction ()
{
	CBaseObject* obj = dynamic_cast<CBaseObject*> (tf);
	if (obj)
		obj->forget ();
	else
		delete tf;
}

//-----------------------------------------------------------------------------
float RepeatTimingFunction::getPosition (unsigned long milliseconds)
{
	if (runCounter > 0)
		milliseconds -= tf->getLength () * runCounter;
	float pos = tf->getPosition (milliseconds);
	return isReverse ? 1.f - pos : pos;
}

//-----------------------------------------------------------------------------
bool RepeatTimingFunction::isDone (unsigned long milliseconds)
{
	if (runCounter > 0)
		milliseconds -= tf->getLength () * runCounter;
	if (tf->isDone (milliseconds))
	{
		runCounter++;
		if (autoReverse)
			isReverse = !isReverse;
		if (runCounter >= repeatCount)
			return true;
	}
	return false;
}

}} // namespaces