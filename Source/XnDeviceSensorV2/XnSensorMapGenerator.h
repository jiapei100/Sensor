/*****************************************************************************
*                                                                            *
*  PrimeSense Sensor 5.x Alpha                                               *
*  Copyright (C) 2012 PrimeSense Ltd.                                        *
*                                                                            *
*  This file is part of PrimeSense Sensor                                    *
*                                                                            *
*  Licensed under the Apache License, Version 2.0 (the "License");           *
*  you may not use this file except in compliance with the License.          *
*  You may obtain a copy of the License at                                   *
*                                                                            *
*      http://www.apache.org/licenses/LICENSE-2.0                            *
*                                                                            *
*  Unless required by applicable law or agreed to in writing, software       *
*  distributed under the License is distributed on an "AS IS" BASIS,         *
*  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  *
*  See the License for the specific language governing permissions and       *
*  limitations under the License.                                            *
*                                                                            *
*****************************************************************************/
#ifndef __XN_SENSOR_MAP_GENERATOR_H__
#define __XN_SENSOR_MAP_GENERATOR_H__

//---------------------------------------------------------------------------
// Includes
//---------------------------------------------------------------------------
#include "XnSensorGenerator.h"

//---------------------------------------------------------------------------
// Types
//---------------------------------------------------------------------------
// disable the "inherits via dominance" warning. This is exactly what we want.
#pragma warning (push)
#pragma warning (disable: 4250)

class XnSensorMapGenerator : 
	public XnSensorGenerator, 
	virtual public xn::ModuleMapGenerator,
	virtual public xn::ModuleCroppingInterface
{
public:
	XnSensorMapGenerator(xn::Context& context, xn::Device& sensor, XnDeviceBase* pSensor, const XnChar* strStreamName);
	virtual ~XnSensorMapGenerator();

	XnStatus Init();

	XnBool IsCapabilitySupported(const XnChar* strCapabilityName);

	XnUInt32 GetSupportedMapOutputModesCount();
	XnStatus GetSupportedMapOutputModes(XnMapOutputMode aModes[], XnUInt32& nCount);

	XnStatus SetMapOutputMode(const XnMapOutputMode& Mode);
	XnStatus GetMapOutputMode(XnMapOutputMode& Mode);
	XnStatus RegisterToMapOutputModeChange(XnModuleStateChangedHandler handler, void* pCookie, XnCallbackHandle& hCallback);
	void UnregisterFromMapOutputModeChange(XnCallbackHandle hCallback);

	xn::ModuleCroppingInterface* GetCroppingInterface() { return this; }
	XnStatus SetCropping(const XnCropping &Cropping);
	XnStatus GetCropping(XnCropping &Cropping);
	XnStatus RegisterToCroppingChange(XnModuleStateChangedHandler handler, void* pCookie, XnCallbackHandle& hCallback);
	void UnregisterFromCroppingChange(XnCallbackHandle hCallback);

protected:
	virtual void FilterProperties(XnActualPropertiesHash* pHash);

	struct SupportedMode
	{
		XnMapOutputMode OutputMode;
		XnUInt32 nInputFormat;
	};

	SupportedMode* m_aSupportedModes;
	XnUInt32 m_nSupportedModesCount;
};

#pragma warning (pop)

#endif // __XN_SENSOR_MAP_GENERATOR_H__