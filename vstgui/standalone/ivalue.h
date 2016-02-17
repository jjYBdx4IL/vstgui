#pragma once

#include "fwd.h"
#include "interface.h"
#include "../lib/cstring.h"

//------------------------------------------------------------------------
namespace VSTGUI {
namespace Standalone {

//------------------------------------------------------------------------
/** value interface */
class IValue : public Interface
{
public:
	/** floating point value in the range of 0 to 1 */
	using Type = double;
	/** indicates an invalid value */
	static constexpr Type InvalidValue = std::numeric_limits<Type>::min ();

	virtual void beginEdit () = 0;
	virtual bool performEdit (Type newValue) = 0;
	virtual void endEdit () = 0;

	virtual void setActive (bool state) = 0;
	virtual bool isActive () const = 0;

	virtual Type getValue () const = 0;
	virtual bool isEditing () const = 0;

	virtual const UTF8String& getID () const = 0;

	virtual const IValueStringConverter& getStringConverter () const = 0;

	virtual void registerListener (IValueListener* listener) = 0;
	virtual void unregisterListener (IValueListener* listener) = 0;
};

//------------------------------------------------------------------------
/** extension to IValue for a non continous value with discrete steps */
class IStepValue : public Interface
{
public:
	using StepType = uint32_t;
	static constexpr StepType InvalidStep = std::numeric_limits<uint32_t>::max ();

	virtual StepType getSteps () const = 0;
	virtual IValue::Type stepToValue (StepType step) const = 0;
	virtual StepType valueToStep (IValue::Type) const = 0;
};

//------------------------------------------------------------------------
class IValueStringConverter : public Interface
{
public:
	virtual UTF8String valueAsString (IValue::Type value) const = 0;
	virtual IValue::Type stringAsValue (const UTF8String& string) const = 0;
};

//------------------------------------------------------------------------
} // Standalone
} // VSTGUI
