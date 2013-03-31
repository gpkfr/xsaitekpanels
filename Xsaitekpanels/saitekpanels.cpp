// ****** saitekpanels.cpp ***********
// ****  William R. Good   ***********
// ******** ver 2.14   ***************
// ****** Mar 30 2013   **************

#include "XPLMDisplay.h"
#include "XPLMGraphics.h"
#include "XPLMUtilities.h"
#include "XPLMDataAccess.h"
#include "XPLMProcessing.h"
#include "XPLMPlugin.h"
#include "XPLMPlanes.h"
#include "XPLMMenus.h"
#include "XPWidgets.h"
#include "XPStandardWidgets.h"

#define MSG_ADD_DATAREF 0x01000000

#include "hidapi.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
//#include <string>
#include <string.h>

#include <time.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

// ************* Radio Panel Command Ref ****************
XPLMCommandRef  Com1StbyFineDn = NULL, Com1StbyFineUp = NULL, Com1StbyCorseDn = NULL, Com1StbyCorseUp = NULL;
XPLMCommandRef  Com2StbyFineDn = NULL, Com2StbyFineUp = NULL, Com2StbyCorseDn = NULL, Com2StbyCorseUp = NULL;
XPLMCommandRef	Nav1StbyFineDn = NULL, Nav1StbyFineUp = NULL, Nav1StbyCorseDn = NULL, Nav1StbyCorseUp = NULL;
XPLMCommandRef	Nav2StbyFineDn = NULL, Nav2StbyFineUp = NULL, Nav2StbyCorseDn = NULL, Nav2StbyCorseUp = NULL;

XPLMCommandRef	Afd1StbyHunUp = NULL, Afd1StbyHunDn = NULL, Afd1StbyTensUp = NULL, Afd1StbyTensDn = NULL;
XPLMCommandRef	Afd1StbyOnesUp = NULL, Afd1StbyOnesDn = NULL;

XPLMCommandRef	Afd2StbyHunUp = NULL, Afd2StbyHunDn = NULL, Afd2StbyTensUp = NULL, Afd2StbyTensDn = NULL;
XPLMCommandRef	Afd2StbyOnesUp = NULL, Afd2StbyOnesDn = NULL;

XPLMCommandRef	XpdrThUp = NULL, XpdrThDn = NULL, XpdrHunUp = NULL, XpdrHunDn = NULL;
XPLMCommandRef	XpdrTensUp = NULL, XpdrTensDn = NULL, XpdrOnesUp = NULL, XpdrOnesDn = NULL;
XPLMCommandRef	BaroUp = NULL, BaroDn = NULL, BaroStd = NULL;


XPLMCommandRef Com1ActStby = NULL, Com2ActStby = NULL, Nav1ActStby = NULL, Nav2ActStby = NULL;
XPLMCommandRef Adf1ActStby = NULL, Adf2ActStby = NULL;

XPLMCommandRef Obs1Down = NULL, Obs1Up = NULL;
XPLMCommandRef Obs2Down = NULL, Obs2Up = NULL;

XPLMCommandRef Rad1UprCom1CrsUpRemapableCmd = NULL, Rad1UprCom1CrsDnRemapableCmd = NULL;
XPLMCommandRef Rad1UprCom1FnUpRemapableCmd = NULL, Rad1UprCom1FnDnRemapableCmd = NULL;
XPLMCommandRef Rad1UprCom1ActStbyRemapableCmd = NULL;
XPLMCommandRef Rad1UprCom2CrsUpRemapableCmd = NULL, Rad1UprCom2CrsDnRemapableCmd = NULL;
XPLMCommandRef Rad1UprCom2FnUpRemapableCmd = NULL, Rad1UprCom2FnDnRemapableCmd = NULL;
XPLMCommandRef Rad1UprCom2ActStbyRemapableCmd = NULL;
XPLMCommandRef Rad1UprNav1CrsUpRemapableCmd = NULL, Rad1UprNav1CrsDnRemapableCmd = NULL;
XPLMCommandRef Rad1UprNav1FnUpRemapableCmd = NULL, Rad1UprNav1FnDnRemapableCmd = NULL;
XPLMCommandRef Rad1UprNav1ActStbyRemapableCmd = NULL;
XPLMCommandRef Rad1UprNav2CrsUpRemapableCmd = NULL, Rad1UprNav2CrsDnRemapableCmd = NULL;
XPLMCommandRef Rad1UprNav2FnUpRemapableCmd = NULL, Rad1UprNav2FnDnRemapableCmd = NULL;
XPLMCommandRef Rad1UprNav2ActStbyRemapableCmd = NULL;


XPLMCommandRef Rad1LowrCom1CrsUpRemapableCmd = NULL, Rad1LowrCom1CrsDnRemapableCmd = NULL;
XPLMCommandRef Rad1LowrCom1FnUpRemapableCmd = NULL, Rad1LowrCom1FnDnRemapableCmd = NULL;
XPLMCommandRef Rad1LowrCom1ActStbyRemapableCmd = NULL;
XPLMCommandRef Rad1LowrCom2CrsUpRemapableCmd = NULL, Rad1LowrCom2CrsDnRemapableCmd = NULL;
XPLMCommandRef Rad1LowrCom2FnUpRemapableCmd = NULL, Rad1LowrCom2FnDnRemapableCmd = NULL;
XPLMCommandRef Rad1LowrCom2ActStbyRemapableCmd = NULL;
XPLMCommandRef Rad1LowrNav1CrsUpRemapableCmd = NULL, Rad1LowrNav1CrsDnRemapableCmd = NULL;
XPLMCommandRef Rad1LowrNav1FnUpRemapableCmd = NULL, Rad1LowrNav1FnDnRemapableCmd = NULL;
XPLMCommandRef Rad1LowrNav1ActStbyRemapableCmd = NULL;
XPLMCommandRef Rad1LowrNav2CrsUpRemapableCmd = NULL, Rad1LowrNav2CrsDnRemapableCmd = NULL;
XPLMCommandRef Rad1LowrNav2FnUpRemapableCmd = NULL, Rad1LowrNav2FnDnRemapableCmd = NULL;
XPLMCommandRef Rad1LowrNav2ActStbyRemapableCmd = NULL;


XPLMCommandRef Rad2UprCom1CrsUpRemapableCmd = NULL, Rad2UprCom1CrsDnRemapableCmd = NULL;
XPLMCommandRef Rad2UprCom1FnUpRemapableCmd = NULL, Rad2UprCom1FnDnRemapableCmd = NULL;
XPLMCommandRef Rad2UprCom1ActStbyRemapableCmd = NULL;
XPLMCommandRef Rad2UprCom2CrsUpRemapableCmd = NULL, Rad2UprCom2CrsDnRemapableCmd = NULL;
XPLMCommandRef Rad2UprCom2FnUpRemapableCmd = NULL, Rad2UprCom2FnDnRemapableCmd = NULL;
XPLMCommandRef Rad2UprCom2ActStbyRemapableCmd = NULL;
XPLMCommandRef Rad2UprNav1CrsUpRemapableCmd = NULL, Rad2UprNav1CrsDnRemapableCmd = NULL;
XPLMCommandRef Rad2UprNav1FnUpRemapableCmd = NULL, Rad2UprNav1FnDnRemapableCmd = NULL;
XPLMCommandRef Rad2UprNav1ActStbyRemapableCmd = NULL;
XPLMCommandRef Rad2UprNav2CrsUpRemapableCmd = NULL, Rad2UprNav2CrsDnRemapableCmd = NULL;
XPLMCommandRef Rad2UprNav2FnUpRemapableCmd = NULL, Rad2UprNav2FnDnRemapableCmd = NULL;
XPLMCommandRef Rad2UprNav2ActStbyRemapableCmd = NULL;


XPLMCommandRef Rad2LowrCom1CrsUpRemapableCmd = NULL, Rad2LowrCom1CrsDnRemapableCmd = NULL;
XPLMCommandRef Rad2LowrCom1FnUpRemapableCmd = NULL, Rad2LowrCom1FnDnRemapableCmd = NULL;
XPLMCommandRef Rad2LowrCom1ActStbyRemapableCmd = NULL;
XPLMCommandRef Rad2LowrCom2CrsUpRemapableCmd = NULL, Rad2LowrCom2CrsDnRemapableCmd = NULL;
XPLMCommandRef Rad2LowrCom2FnUpRemapableCmd = NULL, Rad2LowrCom2FnDnRemapableCmd = NULL;
XPLMCommandRef Rad2LowrCom2ActStbyRemapableCmd = NULL;
XPLMCommandRef Rad2LowrNav1CrsUpRemapableCmd = NULL, Rad2LowrNav1CrsDnRemapableCmd = NULL;
XPLMCommandRef Rad2LowrNav1FnUpRemapableCmd = NULL, Rad2LowrNav1FnDnRemapableCmd = NULL;
XPLMCommandRef Rad2LowrNav1ActStbyRemapableCmd = NULL;
XPLMCommandRef Rad2LowrNav2CrsUpRemapableCmd = NULL, Rad2LowrNav2CrsDnRemapableCmd = NULL;
XPLMCommandRef Rad2LowrNav2FnUpRemapableCmd = NULL, Rad2LowrNav2FnDnRemapableCmd = NULL;
XPLMCommandRef Rad2LowrNav2ActStbyRemapableCmd = NULL;


// ************* Radio Panel Data Ref ****************
XPLMDataRef Com1ActFreq = NULL, Com2ActFreq = NULL, Nav1ActFreq = NULL, Nav2ActFreq = NULL;
XPLMDataRef Com1StbyFreq = NULL, Com2StbyFreq = NULL, Nav1StbyFreq = NULL, Nav2StbyFreq = NULL;

XPLMDataRef Adf1StbyFreq = NULL, Adf2StbyFreq = NULL;
XPLMDataRef Adf1ActFreq = NULL, Adf2ActFreq = NULL;

XPLMDataRef XpdrCode = NULL, XpdrMode = NULL, BaroSetting = NULL;
XPLMDataRef MetricPress = NULL;

XPLMDataRef DmeMode = NULL, DmeSlvSource = NULL;
XPLMDataRef Nav1DmeNmDist = NULL, Nav1DmeSpeed = NULL;
XPLMDataRef Nav2DmeNmDist = NULL, Nav2DmeSpeed = NULL;
XPLMDataRef DmeFreq = NULL, DmeTime = NULL, DmeSpeed = NULL;

XPLMDataRef AvPwrOn = NULL, BatPwrOn = NULL;

XPLMDataRef Nav1PwrOn = NULL, Nav2PwrOn = NULL, Com1PwrOn = NULL, Com2PwrOn = NULL;
XPLMDataRef Afd1PwrOn = NULL, DmePwrOn = NULL;

XPLMDataRef Nav1ObsDegm = NULL, Nav2ObsDegm = NULL;
XPLMDataRef Adf1CardDirDegm = NULL,  Adf2CardDirDegm = NULL;

XPLMMenuID      RadioMenu;
XPLMMenuID      RadioMenuId;

XPWidgetID	RadioWidgetID = NULL;
XPWidgetID	RadioWindow = NULL;
XPWidgetID	RadioSpeed1CheckWidget[50] = {NULL};
XPWidgetID	RadioSpeed2CheckWidget[50] = {NULL};
XPWidgetID	RadioSpeed3CheckWidget[50] = {NULL};
XPWidgetID	RadioSpeed4CheckWidget[50] = {NULL};
XPWidgetID	RadioSpeed5CheckWidget[50] = {NULL};
XPWidgetID	RadioSpeedTextWidget[50] = {NULL};

XPWidgetID	RadioAdf1CheckWidget[50] = {NULL};
XPWidgetID	RadioAdf2CheckWidget[50] = {NULL};
XPWidgetID	RadioAdf1TextWidget[50] = {NULL};
XPWidgetID	RadioAdf2TextWidget[50] = {NULL};

XPWidgetID	RadioQnh0CheckWidget[50] = {NULL};
XPWidgetID	RadioQnh1CheckWidget[50] = {NULL};
XPWidgetID	RadioQnh0TextWidget[50] = {NULL};
XPWidgetID	RadioQnh1TextWidget[50] = {NULL};


// ****************** Multi Panel Command Ref **********************
XPLMCommandRef ApAltDn = NULL, ApAltUp = NULL, ApVsDn = NULL, ApVsUp = NULL;
XPLMCommandRef ApAsDn = NULL, ApAsUp = NULL, ApHdgDn = NULL, ApHdgUp = NULL;
XPLMCommandRef ApCrsDn = NULL, ApCrsUp = NULL, ApCrsDn2 = NULL, ApCrsUp2 = NULL;

XPLMCommandRef ApMstrBtnUp = NULL, ApMstrBtnDn = NULL, ApMstrBtnOff = NULL;
XPLMCommandRef ApHdgBtn = NULL, ApNavBtn = NULL, ApAltBtn = NULL, ApAltArmBtn = NULL;
XPLMCommandRef ApIasBtn = NULL;

XPLMCommandRef ApVsBtn = NULL, ApAprBtn = NULL, ApRevBtn = NULL;
XPLMCommandRef ApKnotsMachTgl = NULL;

XPLMCommandRef FlapsDn = NULL, FlapsUp = NULL;
XPLMCommandRef PitchTrimDn = NULL, PitchTrimUp = NULL, PitchTrimTkOff = NULL;

XPLMCommandRef XpanelsFnButtonCommand = NULL, XpanelsCrsToggleCommand = NULL;


XPLMCommandRef ApButtonRemapableCmd = NULL, HdgButtonRemapableCmd = NULL;
XPLMCommandRef NavButtonVorlocRemapableCmd = NULL, NavButtonLnavRemapableCmd = NULL;
XPLMCommandRef IasButtonRemapableCmd = NULL, IasChangeoverButtonRemapableCmd = NULL;
XPLMCommandRef AltButtonRemapableCmd = NULL, VsButtonRemapableCmd = NULL;
XPLMCommandRef AprButtonRemapableCmd = NULL, RevButtonRemapableCmd = NULL;

XPLMCommandRef AltSwitchUpRemapableCmd = NULL, AltSwitchDnRemapableCmd = NULL;
XPLMCommandRef VsSwitchUpRemapableCmd = NULL, VsSwitchDnRemapableCmd = NULL;
XPLMCommandRef IasSwitchUpRemapableCmd = NULL, IasSwitchDnRemapableCmd = NULL;
XPLMCommandRef HdgSwitchUpRemapableCmd = NULL, HdgSwitchDnRemapableCmd = NULL;
XPLMCommandRef CrsSwitchUpRemapableCmd = NULL, CrsSwitchDnRemapableCmd = NULL;

XPLMCommandRef ApVsUpRemapableCmd = NULL, ApVsDnRemapableCmd = NULL;
XPLMCommandRef TrimUpRemapableCmd = NULL, TrimDnRemapableCmd = NULL;

// ***************** Multi Panel Data Ref *********************
XPLMDataRef ApAlt = NULL, ApVs = NULL, ApAs = NULL, ApHdg = NULL, ApCrs = NULL, ApCrs2 = NULL;

XPLMDataRef ApMstrStat = NULL, ApHdgStat = NULL, ApNavStat = NULL, ApIasStat = NULL;
XPLMDataRef ApAltStat = NULL, ApVsStat = NULL, ApAprStat = NULL, ApRevStat = NULL;
XPLMDataRef ApState = NULL, ApAutThr;
XPLMDataRef Frp = NULL, MHdg = NULL;

XPLMDataRef ApButtonRemapableData = NULL, HdgButtonRemapableData = NULL;
XPLMDataRef NavButtonVorlocRemapableData = NULL, NavButtonLnavRemapableData = NULL;
XPLMDataRef IasButtonRemapableData = NULL, IasChangeoverButtonRemapableData = NULL;
XPLMDataRef AltButtonRemapableData = NULL, VsButtonRemapableData = NULL;
XPLMDataRef AprButtonRemapableData = NULL, RevButtonRemapableData = NULL;

XPLMDataRef AltSwitchRemapableData = NULL;
XPLMDataRef VsSwitchRemapableData = NULL;
XPLMDataRef IasSwitchRemapableData = NULL;
XPLMDataRef HdgSwitchRemapableData = NULL;
XPLMDataRef CrsSwitchRemapableData = NULL;

XPLMDataRef AttrSwitchRemapableData = NULL;

XPLMDataRef IasIsmachRemapableData = NULL;

XPLMDataRef ApLightRemapableData = NULL, HdgLightRemapableData = NULL;
XPLMDataRef NavLightVorlocRemapableData = NULL, NavLightLnavRemapableData = NULL;
XPLMDataRef IasLightRemapableData = NULL;
XPLMDataRef AltLightRemapableData = NULL, VsLightRemapableData = NULL;
XPLMDataRef AprLightRemapableData = NULL, RevLightRemapableData = NULL;

XPLMDataRef ApLightFlashRemapableData = NULL, HdgLightFlashRemapableData = NULL;
XPLMDataRef NavLightVorlocFlashRemapableData = NULL, NavLightLnavFlashRemapableData = NULL;
XPLMDataRef IasLightFlashRemapableData = NULL;
XPLMDataRef AltLightFlashRemapableData = NULL, VsLightFlashRemapableData = NULL;
XPLMDataRef AprLightFlashRemapableData = NULL, RevLightFlashRemapableData = NULL;


XPLMDataRef AirspeedIsMach = NULL, Airspeed = NULL;

XPLMDataRef HsiSelector = NULL;

XPLMMenuID      MultiMenu;
XPLMMenuID      MultiMenuId;

XPWidgetID	MultiWidgetID = NULL;
XPWidgetID	MultiWindow = NULL;
XPWidgetID	MultiSpeed1CheckWidget[50] = {NULL};
XPWidgetID	MultiSpeed2CheckWidget[50] = {NULL};
XPWidgetID	MultiSpeed3CheckWidget[50] = {NULL};
XPWidgetID	MultiSpeed4CheckWidget[50] = {NULL};
XPWidgetID	MultiSpeed5CheckWidget[50] = {NULL};
XPWidgetID	MultiSpeedTextWidget[50] = {NULL};

XPWidgetID	MultiTrimSpeed1CheckWidget[50] = {NULL};
XPWidgetID	MultiTrimSpeed2CheckWidget[50] = {NULL};
XPWidgetID	MultiTrimSpeed3CheckWidget[50] = {NULL};
XPWidgetID	MultiTrimSpeedTextWidget[50] = {NULL};

XPWidgetID	MultiAt0CheckWidget[50] = {NULL};
XPWidgetID	MultiAt1CheckWidget[50] = {NULL};
XPWidgetID	MultiAt0TextWidget[50] = {NULL};
XPWidgetID	MultiAt1TextWidget[50] = {NULL};

// *************** Switch Panel Command Ref *******************
XPLMCommandRef ClFlOpn = NULL, ClFlCls = NULL;
XPLMCommandRef PtHtOn = NULL, PtHtOff = NULL;
XPLMCommandRef PtHt0On = NULL, PtHt0Off = NULL, PtHt1On = NULL, PtHt1Off = NULL;

XPLMCommandRef AvLtOn = NULL, AvLtOff = NULL, BatOn = NULL, BatOff = NULL;
XPLMCommandRef LnLtOn = NULL, LnLtOff = NULL, TxLtOn = NULL, TxLtOff = NULL;
XPLMCommandRef StLtOn = NULL, StLtOff = NULL, NvLtOn = NULL, NvLtOff = NULL;
XPLMCommandRef BcLtOn = NULL, BcLtOff = NULL, GearUp = NULL, GearDn = NULL;

XPLMCommandRef MagOffSwitchOnCmd = NULL, MagOffSwitchOffCmd = NULL;
XPLMCommandRef MagRightSwitchOnCmd = NULL, MagRightSwitchOffCmd = NULL;
XPLMCommandRef MagLeftSwitchOnCmd = NULL, MagLeftSwitchOffCmd = NULL;
XPLMCommandRef MagBothSwitchOnCmd = NULL, MagBothSwitchOffCmd = NULL;
XPLMCommandRef MagStartSwitchOnCmd = NULL, MagStartSwitchOffCmd = NULL;

XPLMCommandRef BatMasterSwitchOnCmd = NULL, BatMasterSwitchOffCmd = NULL;
XPLMCommandRef AltMasterSwitchOnCmd = NULL, AltMasterSwitchOffCmd = NULL;
XPLMCommandRef AvMasterSwitchOnCmd = NULL, AvMasterSwitchOffCmd = NULL;

XPLMCommandRef FuelPumpOnCmd = NULL, FuelPumpOffCmd = NULL;
XPLMCommandRef FuelPump2OnCmd = NULL, FuelPump2OffCmd = NULL;
XPLMCommandRef FuelPump3OnCmd = NULL, FuelPump3OffCmd = NULL;
XPLMCommandRef FuelPump4OnCmd = NULL, FuelPump4OffCmd = NULL;

XPLMCommandRef DeiceOnCmd = NULL, DeiceOffCmd = NULL;
XPLMCommandRef DeiceOnCmd1 = NULL, DeiceOffCmd1 = NULL;
XPLMCommandRef DeiceOnCmd2 = NULL, DeiceOffCmd2 = NULL;
XPLMCommandRef DeiceOnCmd3 = NULL, DeiceOffCmd3 = NULL;
XPLMCommandRef DeiceOnCmd4 = NULL, DeiceOffCmd4 = NULL;
XPLMCommandRef DeiceOnCmd5 = NULL, DeiceOffCmd5 = NULL;
XPLMCommandRef DeiceOnCmd6 = NULL, DeiceOffCmd6 = NULL;
XPLMCommandRef DeiceOnCmd7 = NULL, DeiceOffCmd7 = NULL;
XPLMCommandRef DeiceOnCmd8 = NULL, DeiceOffCmd8 = NULL;

XPLMCommandRef PitotHeatOnCmd = NULL, PitotHeatOffCmd = NULL;
XPLMCommandRef Pitot2HeatOnCmd = NULL, Pitot2HeatOffCmd = NULL;
XPLMCommandRef GearUpOnCmd = NULL, GearOnOffCmd = NULL;
XPLMCommandRef GearDnOnCmd = NULL, GearDnOffCmd = NULL;

XPLMCommandRef CowlFlapsOpenCmd = NULL, CowlFlapsCloseCmd = NULL;
XPLMCommandRef Cowl2FlapsOpenCmd = NULL, Cowl2FlapsCloseCmd = NULL;
XPLMCommandRef PanelLightsOnCmd = NULL, PanelLightsOffCmd = NULL;
XPLMCommandRef BeaconLightsOnCmd = NULL, BeaconLightsOffCmd = NULL;
XPLMCommandRef NavLightsOnCmd = NULL, NavLightsOffCmd = NULL;
XPLMCommandRef StrobeLightsOnCmd = NULL, StrobeLightsOffCmd = NULL;
XPLMCommandRef TaxiLightsOnCmd = NULL, TaxiLightsOffCmd = NULL;
XPLMCommandRef LandingLightsOnCmd = NULL, LandingLightsOffCmd = NULL;

XPLMCommandRef MagOff1 = NULL, MagOff2 = NULL, MagOff3 = NULL, MagOff4 = NULL;
XPLMCommandRef MagOff5 = NULL, MagOff6 = NULL, MagOff7 = NULL, MagOff8 = NULL;

XPLMCommandRef MagLeft1 = NULL, MagLeft2 = NULL, MagLeft3 = NULL, MagLeft4 = NULL;
XPLMCommandRef MagLeft5 = NULL, MagLeft6 = NULL, MagLeft7 = NULL, MagLeft8 = NULL;

XPLMCommandRef MagRight1 = NULL, MagRight2 = NULL, MagRight3 = NULL, MagRight4 = NULL;
XPLMCommandRef MagRight5 = NULL, MagRight6 = NULL, MagRight7 = NULL, MagRight8 = NULL;

XPLMCommandRef MagBoth1 = NULL, MagBoth2 = NULL, MagBoth3 = NULL, MagBoth4 = NULL;
XPLMCommandRef MagBoth5 = NULL, MagBoth6 = NULL, MagBoth7 = NULL, MagBoth8 = NULL;

XPLMCommandRef EngStart1 = NULL, EngStart2 = NULL, EngStart3 = NULL, EngStart4 = NULL;
XPLMCommandRef EngStart5 = NULL, EngStart6 = NULL, EngStart7 = NULL, EngStart8 = NULL;

XPLMCommandRef BatOn1 = NULL, BatOn2 = NULL, BatOff1 = NULL, BatOff2 = NULL;

XPLMCommandRef GenOn1 = NULL, GenOn2 = NULL, GenOn3 = NULL, GenOn4 = NULL;
XPLMCommandRef GenOn5 = NULL, GenOn6 = NULL, GenOn7 = NULL, GenOn8 = NULL;

XPLMCommandRef GenOff1 = NULL, GenOff2 = NULL, GenOff3 = NULL, GenOff4 = NULL;
XPLMCommandRef GenOff5 = NULL, GenOff6 = NULL, GenOff7 = NULL, GenOff8 = NULL;

XPLMCommandRef FuelPumpOn1 = NULL, FuelPumpOn2 = NULL, FuelPumpOn3 = NULL, FuelPumpOn4 = NULL;
XPLMCommandRef FuelPumpOn5 = NULL, FuelPumpOn6 = NULL, FuelPumpOn7 = NULL, FuelPumpOn8 = NULL;

XPLMCommandRef FuelPumpOff1 = NULL, FuelPumpOff2 = NULL, FuelPumpOff3 = NULL, FuelPumpOff4 = NULL;
XPLMCommandRef FuelPumpOff5 = NULL, FuelPumpOff6 = NULL, FuelPumpOff7 = NULL, FuelPumpOff8 = NULL;

// ******************* Switch Panel Data Ref ********************
XPLMDataRef BatNum = NULL, GenNum = NULL, EngNum = NULL;
XPLMDataRef BatArrayOnDR = NULL, IgnSwitchArray = NULL;
XPLMDataRef EngnMixt = NULL, IgniterOn = NULL;
XPLMDataRef AcfEnType = NULL;

XPLMDataRef CowlFlaps = NULL, CockpitLights = NULL, AntiIce = NULL;
XPLMDataRef GearRetract = NULL, OnGround = NULL, LandingGearStatus = {NULL};
XPLMDataRef Gear1Fail = NULL, Gear2Fail = NULL, Gear3Fail = NULL;

XPLMDataRef MagOffSwitchData = NULL, MagOff2SwitchData = NULL;
XPLMDataRef MagOff3SwitchData = NULL, MagOff4SwitchData = NULL;

XPLMDataRef MagRightSwitchData = NULL, MagRight2SwitchData = NULL;
XPLMDataRef MagRight3SwitchData = NULL, MagRight4SwitchData = NULL;

XPLMDataRef MagLeftSwitchData = NULL, MagLeft2SwitchData = NULL;
XPLMDataRef MagLeft3SwitchData = NULL, MagLeft4SwitchData = NULL;

XPLMDataRef MagBothSwitchData = NULL, MagBoth2SwitchData = NULL;
XPLMDataRef MagBoth3SwitchData = NULL, MagBoth4SwitchData = NULL;

XPLMDataRef MagStartSwitchData = NULL, MagStart2SwitchData = NULL;
XPLMDataRef MagStart3SwitchData = NULL, MagStart4SwitchData = NULL;

XPLMDataRef BatMasterSwitchData = NULL, Bat2MasterSwitchData = NULL;
XPLMDataRef Bat3MasterSwitchData = NULL, Bat4MasterSwitchData = NULL;
XPLMDataRef Bat5MasterSwitchData = NULL, Bat6MasterSwitchData = NULL;
XPLMDataRef Bat7MasterSwitchData = NULL, Bat8MasterSwitchData = NULL;

XPLMDataRef AltMasterSwitchData = NULL, Alt2MasterSwitchData = NULL;
XPLMDataRef Alt3MasterSwitchData = NULL, Alt4MasterSwitchData = NULL;
XPLMDataRef Alt5MasterSwitchData = NULL, Alt6MasterSwitchData = NULL;
XPLMDataRef Alt7MasterSwitchData = NULL, Alt8MasterSwitchData = NULL;

XPLMDataRef AvMasterSwitchData = NULL, Av2MasterSwitchData = NULL;
XPLMDataRef Av3MasterSwitchData = NULL, Av4MasterSwitchData = NULL;
XPLMDataRef Av5MasterSwitchData = NULL, Av6MasterSwitchData = NULL;
XPLMDataRef Av7MasterSwitchData = NULL, Av8MasterSwitchData = NULL;

XPLMDataRef FuelPumpSwitchData = NULL;
XPLMDataRef FuelPump2SwitchData = NULL;
XPLMDataRef FuelPump3SwitchData = NULL;
XPLMDataRef FuelPump4SwitchData = NULL;

XPLMDataRef DeiceSwitchData = NULL;
XPLMDataRef Deice2SwitchData = NULL;
XPLMDataRef Deice3SwitchData = NULL;
XPLMDataRef Deice4SwitchData = NULL;
XPLMDataRef Deice5SwitchData = NULL;
XPLMDataRef Deice6SwitchData = NULL;
XPLMDataRef Deice7SwitchData = NULL;
XPLMDataRef Deice8SwitchData = NULL;

XPLMDataRef PitotHeatSwitchData = NULL, Pitot2HeatSwitchData = NULL;
XPLMDataRef Pitot3HeatSwitchData = NULL, Pitot4HeatSwitchData = NULL;
XPLMDataRef Pitot5HeatSwitchData = NULL, Pitot6HeatSwitchData = NULL;
XPLMDataRef Pitot7HeatSwitchData = NULL, Pitot8HeatSwitchData = NULL;


XPLMDataRef GearUpData = NULL;
XPLMDataRef GearDnData = NULL;

XPLMDataRef CowlFlapsData = NULL;
XPLMDataRef Cowl2FlapsData = NULL;
XPLMDataRef PanelLightsData = NULL;
XPLMDataRef BeaconLightsData = NULL;
XPLMDataRef NavLightsData = NULL;
XPLMDataRef StrobeLightsData = NULL;
XPLMDataRef TaxiLightsData = NULL;
XPLMDataRef LandingLightsData = NULL;


XPLMMenuID      SwitchMenu;
XPLMMenuID      SwitchMenuId;

XPWidgetID	SwitchWidgetID = NULL;
XPWidgetID	SwitchWindow = NULL;
XPWidgetID	SwitchEnableCheckWidget[50] = {NULL};
XPWidgetID	SwitchDisableCheckWidget[50] = {NULL};
XPWidgetID	SwitchRemapCheckWidget[50] = {NULL};
XPWidgetID	SwitchBatAltCheckWidget[50] = {NULL};
XPWidgetID	SwitchAltBatCheckWidget[50] = {NULL};
XPWidgetID	SwitchBatAltTextWidget[50] = {NULL};
XPWidgetID	SwitchAltBatTextWidget[50] = {NULL};

XPWidgetID	SwitchStartSwitchOldCheckWidget[50] = {NULL};
XPWidgetID	SwitchStartSwitchOldTextWidget[50] = {NULL};
XPWidgetID	SwitchStartSwitchNewCheckWidget[50] = {NULL};
XPWidgetID	SwitchStartSwitchNewTextWidget[50] = {NULL};

XPWidgetID	SwitchLabelTextWidget[50] = {NULL};
XPWidgetID	SwitchTextWidget[50] = {NULL};

typedef	std::vector<XPLMDataRef> aXPLMDataRefID;

static aXPLMDataRefID DataRefID;

// ****************** BIP Panel Command Ref **********************

//  ***************** BIP Panel Data Ref *********************
XPLMDataRef gTimeSimIsRunningXDataRef = NULL;

XPLMMenuID      XsaitekpanelsMenu;
XPLMMenuID      BipMenu;
XPLMMenuID      BipMenuId, Bip2MenuId, Bip3MenuId, Bip4MenuId;
XPLMMenuID      ConfigMenuId;

XPWidgetID      XsaitekpanelsWidgetID = NULL;
XPWidgetID      BipWidgetID = NULL;
XPWidgetID      Bip2WidgetID = NULL;
XPWidgetID      Bip3WidgetID = NULL;
XPWidgetID      Bip4WidgetID = NULL;

// ********************** Radio Panel variables ************************
int radcnt = 0, radiores, stopradcnt;
int radres, radnum = 0;
float interval = -1;
static unsigned char blankradiowbuf[4][23];
static unsigned char radiobuf[4][4], radiowbuf[4][23];

unsigned char radbuf[4], radwbuf[21];

int radspeed, numadf, metricpressenable;

int rad1uprcom1switchremap, rad1uprcom1actstbybtnremap;
int rad1uprcom2switchremap, rad1uprcom2actstbybtnremap;
int rad1uprnav1switchremap, rad1uprnav1actstbybtnremap;
int rad1uprnav2switchremap, rad1uprnav2actstbybtnremap;
int rad1lwrcom1switchremap, rad1lwrcom1actstbybtnremap;
int rad1lwrcom2switchremap, rad1lwrcom2actstbybtnremap;
int rad1lwrnav1switchremap, rad1lwrnav1actstbybtnremap;
int rad1lwrnav2switchremap, rad1lwrnav2actstbybtnremap;

int rad2uprcom1switchremap, rad2uprcom1actstbybtnremap;
int rad2uprcom2switchremap, rad2uprcom2actstbybtnremap;
int rad2uprnav1switchremap, rad2uprnav1actstbybtnremap;
int rad2uprnav2switchremap, rad2uprnav2actstbybtnremap;
int rad2lwrcom1switchremap, rad2lwrcom1actstbybtnremap;
int rad2lwrcom2switchremap, rad2lwrcom2actstbybtnremap;
int rad2lwrnav1switchremap, rad2lwrnav1actstbybtnremap;
int rad2lwrnav2switchremap, rad2lwrnav2actstbybtnremap;

void CreateRadioWidget(int x1, int y1, int w, int h);
int RadioHandler(XPWidgetMessage  RadioinMessage, XPWidgetID  RadioWidgetID, intptr_t  inParam1, intptr_t  inParam2);

int radioMenuItem;

string rad1_upper_com1_corse_up_remapable, rad1_upper_com1_corse_dn_remapable;
string rad1_upper_com1_fine_up_remapable, rad1_upper_com1_fine_dn_remapable;
string rad1_upper_com1_actstby_btn_remapable;
string rad1_upper_com2_corse_up_remapable, rad1_upper_com2_corse_dn_remapable;
string rad1_upper_com2_fine_up_remapable, rad1_upper_com2_fine_dn_remapable;
string rad1_upper_com2_actstby_btn_remapable;
string rad1_upper_nav1_corse_up_remapable, rad1_upper_nav1_corse_dn_remapable;
string rad1_upper_nav1_fine_up_remapable, rad1_upper_nav1_fine_dn_remapable;
string rad1_upper_nav1_actstby_btn_remapable;
string rad1_upper_nav2_corse_up_remapable, rad1_upper_nav2_corse_dn_remapable;
string rad1_upper_nav2_fine_up_remapable, rad1_upper_nav2_fine_dn_remapable;
string rad1_upper_nav2_actstby_btn_remapable;

string rad1_lower_com1_corse_up_remapable, rad1_lower_com1_corse_dn_remapable;
string rad1_lower_com1_fine_up_remapable, rad1_lower_com1_fine_dn_remapable;
string rad1_lower_com1_actstby_btn_remapable;
string rad1_lower_com2_corse_up_remapable, rad1_lower_com2_corse_dn_remapable;
string rad1_lower_com2_fine_up_remapable, rad1_lower_com2_fine_dn_remapable;
string rad1_lower_com2_actstby_btn_remapable;
string rad1_lower_nav1_corse_up_remapable, rad1_lower_nav1_corse_dn_remapable;
string rad1_lower_nav1_fine_up_remapable, rad1_lower_nav1_fine_dn_remapable;
string rad1_lower_nav1_actstby_btn_remapable;
string rad1_lower_nav2_corse_up_remapable, rad1_lower_nav2_corse_dn_remapable;
string rad1_lower_nav2_fine_up_remapable, rad1_lower_nav2_fine_dn_remapable;
string rad1_lower_nav2_actstby_btn_remapable;

string rad2_upper_com1_corse_up_remapable, rad2_upper_com1_corse_dn_remapable;
string rad2_upper_com1_fine_up_remapable, rad2_upper_com1_fine_dn_remapable;
string rad2_upper_com1_actstby_btn_remapable;
string rad2_upper_com2_corse_up_remapable, rad2_upper_com2_corse_dn_remapable;
string rad2_upper_com2_fine_up_remapable, rad2_upper_com2_fine_dn_remapable;
string rad2_upper_com2_actstby_btn_remapable;
string rad2_upper_nav1_corse_up_remapable, rad2_upper_nav1_corse_dn_remapable;
string rad2_upper_nav1_fine_up_remapable, rad2_upper_nav1_fine_dn_remapable;
string rad2_upper_nav1_actstby_btn_remapable;
string rad2_upper_nav2_corse_up_remapable, rad2_upper_nav2_corse_dn_remapable;
string rad2_upper_nav2_fine_up_remapable, rad2_upper_nav2_fine_dn_remapable;
string rad2_upper_nav2_actstby_btn_remapable;

string rad2_lower_com1_corse_up_remapable, rad2_lower_com1_corse_dn_remapable;
string rad2_lower_com1_fine_up_remapable, rad2_lower_com1_fine_dn_remapable;
string rad2_lower_com1_actstby_btn_remapable;
string rad2_lower_com2_corse_up_remapable, rad2_lower_com2_corse_dn_remapable;
string rad2_lower_com2_fine_up_remapable, rad2_lower_com2_fine_dn_remapable;
string rad2_lower_com2_actstby_btn_remapable;
string rad2_lower_nav1_corse_up_remapable, rad2_lower_nav1_corse_dn_remapable;
string rad2_lower_nav1_fine_up_remapable, rad2_lower_nav1_fine_dn_remapable;
string rad2_lower_nav1_actstby_btn_remapable;
string rad2_lower_nav2_corse_up_remapable, rad2_lower_nav2_corse_dn_remapable;
string rad2_lower_nav2_fine_up_remapable, rad2_lower_nav2_fine_dn_remapable;
string rad2_lower_nav2_actstby_btn_remapable;


char RadioSpeedText[50][200] = {
"FREQ KNOB  1 PULSE PER COMMAND",
"FREQ KNOB  2 PULSES PER COMMAND",
"FREQ KNOB  3 PULSES PER COMMAND",
"FREQ KNOB  4 PULSES PER COMMAND",
"FREQ KNOB  5 PULSES PER COMMAND",
"end"
};

hid_device *radiohandle[4];

// ********************** Multi Panel variables ***********************
int multicnt = 0, multires, stopmulticnt;
static unsigned char blankmultiwbuf[13];
unsigned char multibuf[4], multiwbuf[13];

int loaded737 = 0;

int trimspeed, multispeed, autothrottleswitchenable, autothrottleswitcharmedvalue;

int apbuttonremap, hdgbuttonremap, navbuttonremap, iasbuttonremap;
int altbuttonremap, vsbuttonremap, aprbuttonremap, revbuttonremap;
int lightdatareferencetype;

int aplightdata, hdglightdata, navlightvorlocdata, navlightlnavdata;
int iaslightdata,altlightdata, vslightdata, aprlightdata, revlightdata;

int aplightflashdata, hdglightflashdata, navlightflashvorlocdata, navlightflashlnavdata;
int iaslightflashdata,altlightflashdata, vslightflashdata, aprlightflashdata, revlightflashdata;

int altswitchremap, vsswitchremap, iasswitchremap;
int hdgswitchremap, crsswitchremap;
int trimupremap, trimdnremap;

int attrswitchremap;

int iasismachremap, iasismachvalue;


int xpanelsfnbutton = 0, xpanelscrstoggle = 0;

void CreateMultiWidget(int x1, int y1, int w, int h);
int MultiHandler(XPWidgetMessage  MultiinMessage, XPWidgetID  MultiWidgetID, intptr_t  inParam1, intptr_t  inParam2);

int multiMenuItem;

string ap_button_remapable, hdg_button_remapable, nav_button_vorloc_remapable, nav_button_lnav_remapable;
string ias_button_remapable, ias_changeover_button_remapable, alt_button_remapable, vs_button_remapable;
string apr_button_remapable, rev_button_remapable;

string ap_button_data_remapable, hdg_button_data_remapable, nav_button_data_vorloc_remapable, nav_button_data_lnav_remapable;
string ias_button_data_remapable, ias_changeover_button_data_remapable, alt_button_data_remapable, vs_button_data_remapable;
string apr_button_data_remapable, rev_button_data_remapable;

string ap_light_remapable, hdg_light_remapable, nav_light_vorloc_remapable, nav_light_lnav_remapable;
string ias_light_remapable, alt_light_remapable, vs_light_remapable, apr_light_remapable, rev_light_remapable;

string ap_light_flash_remapable, hdg_light_flash_remapable, nav_light_vorloc_flash_remapable, nav_light_lnav_flash_remapable;
string ias_light_flash_remapable, alt_light_flash_remapable, vs_light_flash_remapable, apr_light_flash_remapable, rev_light_flash_remapable;

string alt_switch_up_remapable, alt_switch_dn_remapable;
string vs_switch_up_remapable, vs_switch_dn_remapable;
string ias_switch_up_remapable, ias_switch_dn_remapable;
string hdg_switch_up_remapable, hdg_switch_dn_remapable;
string crs_switch_up_remapable, crs_switch_dn_remapable;

string attr_switch_remapable;

string ias_ismach_remapable;

string alt_switch_data_remapable;
string vs_switch_data_remapable;
string ias_switch_data_remapable;
string hdg_switch_data_remapable;
string crs_switch_data_remapable;

string attr_switch_data_remapable;

string ap_vs_up_remapable, ap_vs_dn_remapable;

string trim_up_remapable, trim_dn_remapable;

char MultiSpeedText[50][200] = {
"FREQ KNOB  1 PULSE PER COMMAND",
"FREQ KNOB  2 PULSES PER COMMAND",
"FREQ KNOB  3 PULSES PER COMMAND",
"FREQ KNOB  4 PULSES PER COMMAND",
"FREQ KNOB  5 PULSES PER COMMAND",
"end"
};

char MultiTrimSpeedText[50][200] = {
"TRIM X1",
"TRIM X2",
"TRIM X3",
"end"
};

hid_device *multihandle;

// ****************** Switch Panel variables *******************************
int switchcnt = 0, switchres, stopswitchcnt;

int magoffswitchenable, magrightswitchenable, magleftswitchenable;
int magbothswitchenable, magstartswitchenable;
int batmasterswitchenable, altmasterswitchenable;
int avionicsmasterswitchenable, fuelpumpswitchenable;
int deiceswitchenable, pitotheatswitchenable;
int landinggearknobupenable, landinggearknobdnenable;
int cowlflapsenable, panellightswitchenable;
int beaconlightswitchenable, navlightswitchenable;
int strobelightswitchenable, taxilightswitchenable;
int landinglightswitchenable, bataltinverse;
int panellightsenable, starterswitchenable;

int mag_off_switch_data_on_value, mag_off_switch_data_off_value;
int mag_off2_switch_data_on_value, mag_off2_switch_data_off_value;
int mag_off3_switch_data_on_value, mag_off3_switch_data_off_value;
int mag_off4_switch_data_on_value, mag_off4_switch_data_off_value;

int mag_right_switch_data_on_value, mag_right_switch_data_off_value;
int mag_right2_switch_data_on_value, mag_right2_switch_data_off_value;
int mag_right3_switch_data_on_value, mag_right3_switch_data_off_value;
int mag_right4_switch_data_on_value, mag_right4_switch_data_off_value;

int mag_left_switch_data_on_value, mag_left_switch_data_off_value;
int mag_left2_switch_data_on_value, mag_left2_switch_data_off_value;
int mag_left3_switch_data_on_value, mag_left3_switch_data_off_value;
int mag_left4_switch_data_on_value, mag_left4_switch_data_off_value;

int mag_both_switch_data_on_value, mag_both_switch_data_off_value;
int mag_both2_switch_data_on_value, mag_both2_switch_data_off_value;
int mag_both3_switch_data_on_value, mag_both3_switch_data_off_value;
int mag_both4_switch_data_on_value, mag_both4_switch_data_off_value;

int mag_start_switch_data_on_value, mag_start_switch_data_off_value;
int mag_start2_switch_data_on_value, mag_start2_switch_data_off_value;
int mag_start3_switch_data_on_value, mag_start3_switch_data_off_value;
int mag_start4_switch_data_on_value, mag_start4_switch_data_off_value;


int bat_master_switch_data_on_value, bat_master_switch_data_off_value;
int bat2_master_switch_data_on_value, bat2_master_switch_data_off_value;
int bat3_master_switch_data_on_value, bat3_master_switch_data_off_value;
int bat4_master_switch_data_on_value, bat4_master_switch_data_off_value;
int bat5_master_switch_data_on_value, bat5_master_switch_data_off_value;
int bat6_master_switch_data_on_value, bat6_master_switch_data_off_value;
int bat7_master_switch_data_on_value, bat7_master_switch_data_off_value;
int bat8_master_switch_data_on_value, bat8_master_switch_data_off_value;

int alt_master_switch_data_on_value, alt_master_switch_data_off_value;
int alt2_master_switch_data_on_value, alt2_master_switch_data_off_value;
int alt3_master_switch_data_on_value, alt3_master_switch_data_off_value;
int alt4_master_switch_data_on_value, alt4_master_switch_data_off_value;
int alt5_master_switch_data_on_value, alt5_master_switch_data_off_value;
int alt6_master_switch_data_on_value, alt6_master_switch_data_off_value;
int alt7_master_switch_data_on_value, alt7_master_switch_data_off_value;
int alt8_master_switch_data_on_value, alt8_master_switch_data_off_value;


int av_master_switch_data_on_value, av_master_switch_data_off_value;
int av2_master_switch_data_on_value, av2_master_switch_data_off_value;
int av3_master_switch_data_on_value, av3_master_switch_data_off_value;
int av4_master_switch_data_on_value, av4_master_switch_data_off_value;
int av5_master_switch_data_on_value, av5_master_switch_data_off_value;
int av6_master_switch_data_on_value, av6_master_switch_data_off_value;
int av7_master_switch_data_on_value, av7_master_switch_data_off_value;
int av8_master_switch_data_on_value, av8_master_switch_data_off_value;



int fuel_pump_switch_data_on_value, fuel_pump_switch_data_off_value;
int fuel_pump2_switch_data_on_value, fuel_pump2_switch_data_off_value;
int fuel_pump3_switch_data_on_value, fuel_pump3_switch_data_off_value;
int fuel_pump4_switch_data_on_value, fuel_pump4_switch_data_off_value;

int deice_switch_data_on_value, deice_switch_data_off_value;
int deice2_switch_data_on_value, deice2_switch_data_off_value;
int deice3_switch_data_on_value, deice3_switch_data_off_value;
int deice4_switch_data_on_value, deice4_switch_data_off_value;
int deice5_switch_data_on_value, deice5_switch_data_off_value;
int deice6_switch_data_on_value, deice6_switch_data_off_value;
int deice7_switch_data_on_value, deice7_switch_data_off_value;
int deice8_switch_data_on_value, deice8_switch_data_off_value;

int pitot_heat_switch_data_on_value, pitot_heat_switch_data_off_value;
int pitot2_heat_switch_data_on_value, pitot2_heat_switch_data_off_value;
int pitot3_heat_switch_data_on_value, pitot3_heat_switch_data_off_value;
int pitot4_heat_switch_data_on_value, pitot4_heat_switch_data_off_value;
int pitot5_heat_switch_data_on_value, pitot5_heat_switch_data_off_value;
int pitot6_heat_switch_data_on_value, pitot6_heat_switch_data_off_value;
int pitot7_heat_switch_data_on_value, pitot7_heat_switch_data_off_value;
int pitot8_heat_switch_data_on_value, pitot8_heat_switch_data_off_value;





int gear_switch_up_data_on_value, gear_switch_up_data_off_value;
int gear_switch_down_data_on_value, gear_switch_down_data_off_value;
int cowl_flaps_data_on_value, cowl_flaps_data_off_value;
int cowl2_flaps_data_on_value, cowl2_flaps_data_off_value;
int panel_lights_switch_data_on_value, panel_lights_switch_data_off_value;
int beacon_lights_switch_data_on_value, beacon_lights_switch_data_off_value;
int nav_lights_switch_data_on_value, nav_lights_switch_data_off_value;
int strobe_lights_switch_data_on_value, strobe_lights_switch_data_off_value;
int taxi_lights_switch_data_on_value, taxi_lights_switch_data_off_value;
int landing_lights_switch_data_on_value, landing_lights_switch_data_off_value;


string mag_off_switch_on, mag_off_switch_off, mag_off_switch_data;
string mag_off2_switch_on, mag_off2_switch_off, mag_off2_switch_data;
string mag_off3_switch_on, mag_off3_switch_off, mag_off3_switch_data;
string mag_off4_switch_on, mag_off4_switch_off, mag_off4_switch_data;

string mag_right_switch_on, mag_right_switch_off, mag_right_switch_data;
string mag_right2_switch_on, mag_right2_switch_off, mag_right2_switch_data;
string mag_right3_switch_on, mag_right3_switch_off, mag_right3_switch_data;
string mag_right4_switch_on, mag_right4_switch_off, mag_right4_switch_data;

string mag_left_switch_on, mag_left_switch_off, mag_left_switch_data;
string mag_left2_switch_on, mag_left2_switch_off, mag_left2_switch_data;
string mag_left3_switch_on, mag_left3_switch_off, mag_left3_switch_data;
string mag_left4_switch_on, mag_left4_switch_off, mag_left4_switch_data;

string mag_both_switch_on, mag_both_switch_off, mag_both_switch_data;
string mag_both2_switch_on, mag_both2_switch_off, mag_both2_switch_data;
string mag_both3_switch_on, mag_both3_switch_off, mag_both3_switch_data;
string mag_both4_switch_on, mag_both4_switch_off, mag_both4_switch_data;

string mag_start_switch_on, mag_start_switch_off, mag_start_switch_data;
string mag_start2_switch_on, mag_start2_switch_off, mag_start2_switch_data;
string mag_start3_switch_on, mag_start3_switch_off, mag_start3_switch_data;
string mag_start4_switch_on, mag_start4_switch_off, mag_start4_switch_data;

string bat_master_switch_on, bat_master_switch_off, bat_master_switch_data;
string bat2_master_switch_on, bat2_master_switch_off, bat2_master_switch_data;
string bat3_master_switch_on, bat3_master_switch_off, bat3_master_switch_data;
string bat4_master_switch_on, bat4_master_switch_off, bat4_master_switch_data;
string bat5_master_switch_on, bat5_master_switch_off, bat5_master_switch_data;
string bat6_master_switch_on, bat6_master_switch_off, bat6_master_switch_data;
string bat7_master_switch_on, bat7_master_switch_off, bat7_master_switch_data;
string bat8_master_switch_on, bat8_master_switch_off, bat8_master_switch_data;

string alt_master_switch_on, alt_master_switch_off, alt_master_switch_data;
string alt2_master_switch_on, alt2_master_switch_off, alt2_master_switch_data;
string alt3_master_switch_on, alt3_master_switch_off, alt3_master_switch_data;
string alt4_master_switch_on, alt4_master_switch_off, alt4_master_switch_data;
string alt5_master_switch_on, alt5_master_switch_off, alt5_master_switch_data;
string alt6_master_switch_on, alt6_master_switch_off, alt6_master_switch_data;
string alt7_master_switch_on, alt7_master_switch_off, alt7_master_switch_data;
string alt8_master_switch_on, alt8_master_switch_off, alt8_master_switch_data;

string av_master_switch_on, av_master_switch_off, av_master_switch_data;
string av2_master_switch_on, av2_master_switch_off, av2_master_switch_data;
string av3_master_switch_on, av3_master_switch_off, av3_master_switch_data;
string av4_master_switch_on, av4_master_switch_off, av4_master_switch_data;
string av5_master_switch_on, av5_master_switch_off, av5_master_switch_data;
string av6_master_switch_on, av6_master_switch_off, av6_master_switch_data;
string av7_master_switch_on, av7_master_switch_off, av7_master_switch_data;
string av8_master_switch_on, av8_master_switch_off, av8_master_switch_data;

string fuel_pump_switch_on, fuel_pump_switch_off, fuel_pump_switch_data;
string fuel_pump2_switch_on, fuel_pump2_switch_off, fuel_pump2_switch_data;
string fuel_pump3_switch_on, fuel_pump3_switch_off, fuel_pump3_switch_data;
string fuel_pump4_switch_on, fuel_pump4_switch_off, fuel_pump4_switch_data;

string deice_switch_on, deice_switch_off, deice_switch_data;
string deice2_switch_on, deice2_switch_off, deice2_switch_data;
string deice3_switch_on, deice3_switch_off, deice3_switch_data;
string deice4_switch_on, deice4_switch_off, deice4_switch_data;
string deice5_switch_on, deice5_switch_off, deice5_switch_data;
string deice6_switch_on, deice6_switch_off, deice6_switch_data;
string deice7_switch_on, deice7_switch_off, deice7_switch_data;
string deice8_switch_on, deice8_switch_off, deice8_switch_data;

string pitot_heat_switch_on, pitot_heat_switch_off, pitot_heat_switch_data;
string pitot2_heat_switch_on, pitot2_heat_switch_off, pitot2_heat_switch_data;
string pitot3_heat_switch_on, pitot3_heat_switch_off, pitot3_heat_switch_data;
string pitot4_heat_switch_on, pitot4_heat_switch_off, pitot4_heat_switch_data;
string pitot5_heat_switch_on, pitot5_heat_switch_off, pitot5_heat_switch_data;
string pitot6_heat_switch_on, pitot6_heat_switch_off, pitot6_heat_switch_data;
string pitot7_heat_switch_on, pitot7_heat_switch_off, pitot7_heat_switch_data;
string pitot8_heat_switch_on, pitot8_heat_switch_off, pitot8_heat_switch_data;

string gear_switch_up_on, gear_switch_up_off,gear_switch_up_data ;
string gear_switch_down_on, gear_switch_down_off, gear_switch_down_data;
string cowl_flaps_open, cowl_flaps_close, cowl_flaps_data ;
string cowl2_flaps_open, cowl2_flaps_close, cowl2_flaps_data;
string panel_lights_switch_on, panel_lights_switch_off, panel_lights_switch_data;
string beacon_lights_switch_on, beacon_lights_switch_off, beacon_lights_switch_data;
string nav_lights_switch_on, nav_lights_switch_off, nav_lights_switch_data;
string strobe_lights_switch_on, strobe_lights_switch_off, strobe_lights_switch_data;
string taxi_lights_switch_on, taxi_lights_switch_off, taxi_lights_switch_data;
string landing_lights_switch_on, landing_lights_switch_off, landing_lights_switch_data;

const char *GearTestStrUp;

static unsigned char blankswitchwbuf[2];
unsigned char switchbuf[4], switchwbuf[2];
float LandingGearDeployRatio[10];

void SwitchMenuHandler(void *, void *);
void CreateSwitchWidget(int x1, int y1, int w, int h);
int SwitchHandler(XPWidgetMessage  SwitchinMessage, XPWidgetID  SwitchWidgetID, intptr_t  inParam1, intptr_t  inParam2);

int switchMenuItem;
int max_items = 20;
int checkable = -1;

char SwitchText[50][200] = {
"MAGS OFF",
"MAGS RIGHT",
"MAGS LEFT",
"MAGS BOTH",
"START ENGINE",
"BATTERY MASTER",
"ALTERNATOR MASTER",
"AVIONICS MASTER",
"FUEL PUMP",
"DEICE SWITCH",
"PITOT HEAT",
"LANDING GEAR UP",
"LANDING GEAR DN",
"COWL FLAPS",
"PANEL LIGHTS",
"BEACON LIGHTS",
"NAV LIGHTS",
"STROBE LIGHTS",
"TAXI LIGHTS",
"LANDING LIGHTS",
"end"
};

hid_device *switchhandle;

// ****************** BIP Panel variables *******************************
int bipcnt = 0, biptmpcnt = 0, bipres, biploop[4], stopbipcnt;
int bipnum = 0;
int bipwcscmp0 = 0, bipwcscmp1 = 1;
unsigned char bipwbuf[4][10];

#define MAX_STR 255
wchar_t wstr[4][MAX_STR];

hid_device *biphandle[4];

// ****************** Saitek Panels variables *******************************
void XsaitekpanelsMenuHandler(void *, void *);
void WriteCSVTableToDisk(void);

int             XsaitekpanelsMenuItem;
int             BipMenuItem;

int Fps, multi_auto_mul;

int wrgXPlaneVersion = 0;
int wrgXPLMVersion = 0;
int wrgHostID = 0;

int readiniloop = 0;

void process_radio_panel();
void process_multi_panel();
void process_switch_panel();
void process_bip_panel();
void process_pref_file();
void process_read_ini_file();

// ********************* MyPanelsFlightLoopCallback **************************
float	MyPanelsFlightLoopCallback(
                                   float                inElapsedSinceLastCall,    
                                   float                inElapsedTimeSinceLastFlightLoop,    
                                   int                  inCounter,    
                                   void *               inRefcon);

int    XpanelsFnButtonCommandHandler(XPLMCommandRef       inCommand,          //  custom command handler
                               XPLMCommandPhase     inPhase,
                               void *               inRefcon);

void WriteCSVTableToDisk(void);

bool ReadConfigFile(std::string PlaneICAO);
// ******************Plugin Calls ******************
PLUGIN_API int XPluginStart(char *		outName,
			    char *		outSig,
			    char *		outDesc)
{

  int ConfigSubMenuItem;
  int BipSubMenuItem, Bip2SubMenuItem;
  int MultiSubMenuItem, RadioSubMenuItem;
  int SwitchSubMenuItem;

  XPLMGetVersions(&wrgXPlaneVersion, &wrgXPLMVersion, &wrgHostID);

  printf("gXPlaneVersion = %d gXPLMVersion = %d gHostID = %d\n", wrgXPlaneVersion, wrgXPLMVersion, wrgHostID);

  XPLMDebugString("Xsaitekpanels: v2.14\n");

	/* First set up our plugin info. */
  strcpy(outName, "Xsaitekpanels v2.14");
  strcpy(outSig, "saitekpanels.hardware uses hidapi interface");
  strcpy(outDesc, "A plugin allows use of Saitek Pro Flight Panels on all platforms");

// ************ Find Radio Panel Commands Ref ******************
  Com1StbyFineDn = XPLMFindCommand("sim/radios/stby_com1_fine_down");
  Com1StbyFineUp = XPLMFindCommand("sim/radios/stby_com1_fine_up");
  Com1StbyCorseDn = XPLMFindCommand("sim/radios/stby_com1_coarse_down");
  Com1StbyCorseUp = XPLMFindCommand("sim/radios/stby_com1_coarse_up");

  Com2StbyFineDn = XPLMFindCommand("sim/radios/stby_com2_fine_down");
  Com2StbyFineUp = XPLMFindCommand("sim/radios/stby_com2_fine_up");
  Com2StbyCorseDn = XPLMFindCommand("sim/radios/stby_com2_coarse_down");
  Com2StbyCorseUp = XPLMFindCommand("sim/radios/stby_com2_coarse_up");

  Nav1StbyFineDn = XPLMFindCommand("sim/radios/stby_nav1_fine_down");
  Nav1StbyFineUp = XPLMFindCommand("sim/radios/stby_nav1_fine_up");
  Nav1StbyCorseDn = XPLMFindCommand("sim/radios/stby_nav1_coarse_down");
  Nav1StbyCorseUp = XPLMFindCommand("sim/radios/stby_nav1_coarse_up");

  Nav2StbyFineDn = XPLMFindCommand("sim/radios/stby_nav2_fine_down");
  Nav2StbyFineUp = XPLMFindCommand("sim/radios/stby_nav2_fine_up");
  Nav2StbyCorseDn = XPLMFindCommand("sim/radios/stby_nav2_coarse_down");
  Nav2StbyCorseUp = XPLMFindCommand("sim/radios/stby_nav2_coarse_up");

  Afd1StbyHunUp = XPLMFindCommand("sim/radios/stby_adf1_hundreds_up");
  Afd1StbyHunDn = XPLMFindCommand("sim/radios/stby_adf1_hundreds_down");
  Afd1StbyTensUp = XPLMFindCommand("sim/radios/stby_adf1_tens_up");
  Afd1StbyTensDn = XPLMFindCommand("sim/radios/stby_adf1_tens_down");
  Afd1StbyOnesUp = XPLMFindCommand("sim/radios/stby_adf1_ones_up");
  Afd1StbyOnesDn = XPLMFindCommand("sim/radios/stby_adf1_ones_down");

  Afd2StbyHunUp = XPLMFindCommand("sim/radios/stby_adf2_hundreds_up");
  Afd2StbyHunDn = XPLMFindCommand("sim/radios/stby_adf2_hundreds_down");
  Afd2StbyTensUp = XPLMFindCommand("sim/radios/stby_adf2_tens_up");
  Afd2StbyTensDn = XPLMFindCommand("sim/radios/stby_adf2_tens_down");
  Afd2StbyOnesUp = XPLMFindCommand("sim/radios/stby_adf2_ones_up");
  Afd2StbyOnesDn = XPLMFindCommand("sim/radios/stby_adf2_ones_down");

  XpdrThUp = XPLMFindCommand("sim/transponder/transponder_thousands_up");
  XpdrThDn = XPLMFindCommand("sim/transponder/transponder_thousands_down");
  XpdrHunUp	= XPLMFindCommand("sim/transponder/transponder_hundreds_up");
  XpdrHunDn	= XPLMFindCommand("sim/transponder/transponder_hundreds_down");
  XpdrTensUp = XPLMFindCommand("sim/transponder/transponder_tens_up");
  XpdrTensDn = XPLMFindCommand("sim/transponder/transponder_tens_down");
  XpdrOnesUp = XPLMFindCommand("sim/transponder/transponder_ones_up");
  XpdrOnesDn = XPLMFindCommand("sim/transponder/transponder_ones_down");

  BaroUp = XPLMFindCommand("sim/instruments/barometer_up");
  BaroDn = XPLMFindCommand("sim/instruments/barometer_down");
  BaroStd = XPLMFindCommand("sim/instruments/barometer_2992");

  Com1ActStby = XPLMFindCommand("sim/radios/com1_standy_flip");
  Com2ActStby = XPLMFindCommand("sim/radios/com2_standy_flip");
  Nav1ActStby = XPLMFindCommand("sim/radios/nav1_standy_flip");
  Nav2ActStby = XPLMFindCommand("sim/radios/nav2_standy_flip");
  Adf1ActStby = XPLMFindCommand("sim/radios/adf1_standy_flip");
  Adf2ActStby = XPLMFindCommand("sim/radios/adf2_standy_flip");

  Obs1Down = XPLMFindCommand("sim/radios/obs1_down");
  Obs1Up = XPLMFindCommand("sim/radios/obs1_up");
  Obs2Down = XPLMFindCommand("sim/radios/obs2_down");
  Obs2Up = XPLMFindCommand("sim/radios/obs2_up");


// ************ Find Radio Panel Data Ref ******************
  Com1ActFreq = XPLMFindDataRef("sim/cockpit/radios/com1_freq_hz");
  Com2ActFreq = XPLMFindDataRef("sim/cockpit/radios/com2_freq_hz");
  Nav1ActFreq = XPLMFindDataRef("sim/cockpit/radios/nav1_freq_hz");
  Nav2ActFreq = XPLMFindDataRef("sim/cockpit/radios/nav2_freq_hz");

  Com1StbyFreq = XPLMFindDataRef("sim/cockpit/radios/com1_stdby_freq_hz");
  Com2StbyFreq = XPLMFindDataRef("sim/cockpit/radios/com2_stdby_freq_hz");
  Nav1StbyFreq = XPLMFindDataRef("sim/cockpit/radios/nav1_stdby_freq_hz");
  Nav2StbyFreq = XPLMFindDataRef("sim/cockpit/radios/nav2_stdby_freq_hz");

  Adf1StbyFreq = XPLMFindDataRef("sim/cockpit/radios/adf1_stdby_freq_hz");
  Adf2StbyFreq = XPLMFindDataRef("sim/cockpit/radios/adf2_stdby_freq_hz");
  Adf1ActFreq = XPLMFindDataRef("sim/cockpit/radios/adf1_freq_hz");
  Adf2ActFreq = XPLMFindDataRef("sim/cockpit/radios/adf2_freq_hz");

  XpdrCode = XPLMFindDataRef("sim/cockpit/radios/transponder_code");
  XpdrMode = XPLMFindDataRef("sim/cockpit/radios/transponder_mode");
  BaroSetting = XPLMFindDataRef("sim/cockpit/misc/barometer_setting");
  MetricPress = XPLMFindDataRef("sim/physics/metric_press");

  DmeMode = XPLMFindDataRef("sim/cockpit2/radios/actuators/DME_mode");
  DmeSlvSource = XPLMFindDataRef("sim/cockpit2/radios/actuators/DME_slave_source");


  Nav1DmeNmDist	= XPLMFindDataRef("sim/cockpit2/radios/indicators/nav1_dme_distance_nm");
  Nav1DmeSpeed = XPLMFindDataRef("sim/cockpit2/radios/indicators/nav1_dme_speed_kts");
  Nav2DmeNmDist	= XPLMFindDataRef("sim/cockpit2/radios/indicators/nav2_dme_distance_nm");
  Nav2DmeSpeed = XPLMFindDataRef("sim/cockpit2/radios/indicators/nav2_dme_speed_kts");
  DmeSpeed = XPLMFindDataRef("sim/cockpit2/radios/indicators/dme_dme_speed_kts");

  DmeFreq = XPLMFindDataRef("sim/cockpit2/radios/actuators/dme_frequency_hz");
  DmeTime = XPLMFindDataRef("sim/cockpit2/radios/indicators/dme_dme_time_min");

  AvPwrOn = XPLMFindDataRef("sim/cockpit/electrical/avionics_on");
  BatPwrOn = XPLMFindDataRef("sim/cockpit/electrical/battery_on");

  Nav1PwrOn = XPLMFindDataRef("sim/cockpit2/radios/actuators/nav1_power");
  Nav2PwrOn = XPLMFindDataRef("sim/cockpit2/radios/actuators/nav2_power");
  Com1PwrOn = XPLMFindDataRef("sim/cockpit2/radios/actuators/com1_power");
  Com2PwrOn = XPLMFindDataRef("sim/cockpit2/radios/actuators/com2_power");
  Afd1PwrOn = XPLMFindDataRef("sim/cockpit2/radios/actuators/adf1_power");
  DmePwrOn = XPLMFindDataRef("sim/cockpit2/radios/actuators/dme_power");

  Nav1ObsDegm = XPLMFindDataRef("sim/cockpit/radios/nav1_obs_degm");
  Nav2ObsDegm = XPLMFindDataRef("sim/cockpit/radios/nav2_obs_degm");

  Adf1CardDirDegm = XPLMFindDataRef("sim/cockpit/radios/adf1_cardinal_dir");
  Adf2CardDirDegm = XPLMFindDataRef("sim/cockpit/radios/adf2_cardinal_dir");


// ************ Find Multi Panel Commands Ref ***************
  ApAltDn = XPLMFindCommand("sim/autopilot/altitude_down");
  ApAltUp = XPLMFindCommand("sim/autopilot/altitude_up");
  ApVsDn = XPLMFindCommand("sim/autopilot/vertical_speed_down");
  ApVsUp = XPLMFindCommand("sim/autopilot/vertical_speed_up");
  ApAsDn = XPLMFindCommand("sim/autopilot/airspeed_down");
  ApAsUp = XPLMFindCommand("sim/autopilot/airspeed_up");
  ApHdgDn = XPLMFindCommand("sim/autopilot/heading_down");
  ApHdgUp = XPLMFindCommand("sim/autopilot/heading_up");

  ApCrsDn = XPLMFindCommand("sim/radios/obs1_down");
  ApCrsUp = XPLMFindCommand("sim/radios/obs1_up");
  ApCrsDn2 = XPLMFindCommand("sim/radios/obs2_down");
  ApCrsUp2 = XPLMFindCommand("sim/radios/obs2_up");

  ApMstrBtnUp = XPLMFindCommand("sim/autopilot/fdir_servos_up_one");
  ApMstrBtnDn = XPLMFindCommand("sim/autopilot/fdir_servos_down_one");
  ApMstrBtnOff = XPLMFindCommand("sim/autopilot/servos_and_flight_dir_off");
  ApHdgBtn = XPLMFindCommand("sim/autopilot/heading");
  ApNavBtn = XPLMFindCommand("sim/autopilot/NAV");
  ApIasBtn = XPLMFindCommand("sim/autopilot/level_change");
  ApAltBtn = XPLMFindCommand("sim/autopilot/altitude_hold");
  ApAltArmBtn = XPLMFindCommand("sim/autopilot/altitude_arm");
  ApVsBtn = XPLMFindCommand("sim/autopilot/vertical_speed");
  ApAprBtn = XPLMFindCommand("sim/autopilot/approach");
  ApRevBtn = XPLMFindCommand("sim/autopilot/back_course");
  ApKnotsMachTgl = XPLMFindCommand("sim/autopilot/knots_mach_toggle");


  PitchTrimDn = XPLMFindCommand("sim/flight_controls/pitch_trim_down");
  PitchTrimUp = XPLMFindCommand("sim/flight_controls/pitch_trim_up");
  PitchTrimTkOff = XPLMFindCommand("sim/flight_controls/pitch_trim_takeoff");
  FlapsDn = XPLMFindCommand("sim/flight_controls/flaps_down");
  FlapsUp = XPLMFindCommand("sim/flight_controls/flaps_up");

  HsiSelector = XPLMFindDataRef("sim/cockpit/switches/HSI_selector");

  XpanelsFnButtonCommand = XPLMCreateCommand("bgood/xsaitekpanels/x_panels_fn_button","Xpanels Fn Button");


// **************** Find Multi Panel Data Ref ********************

  ApAlt = XPLMFindDataRef("sim/cockpit/autopilot/altitude");
  ApVs = XPLMFindDataRef("sim/cockpit/autopilot/vertical_velocity");
  ApAs = XPLMFindDataRef("sim/cockpit/autopilot/airspeed");
  ApHdg = XPLMFindDataRef("sim/cockpit/autopilot/heading_mag");

  ApCrs  = XPLMFindDataRef("sim/cockpit/radios/nav1_obs_degm");
  ApCrs2 = XPLMFindDataRef("sim/cockpit/radios/nav2_obs_degm");

  ApMstrStat = XPLMFindDataRef("sim/cockpit2/autopilot/flight_director_mode");
  ApState = XPLMFindDataRef("sim/cockpit/autopilot/autopilot_state");
  ApHdgStat = XPLMFindDataRef("sim/cockpit2/autopilot/heading_status");
  ApNavStat = XPLMFindDataRef("sim/cockpit2/autopilot/nav_status");
  ApIasStat = XPLMFindDataRef("sim/cockpit2/autopilot/speed_status");
  ApAltStat = XPLMFindDataRef("sim/cockpit2/autopilot/altitude_hold_status");
  ApVsStat = XPLMFindDataRef("sim/cockpit2/autopilot/vvi_status");
  ApAprStat = XPLMFindDataRef("sim/cockpit2/autopilot/approach_status");
  ApRevStat = XPLMFindDataRef("sim/cockpit2/autopilot/backcourse_status");
  AvPwrOn = XPLMFindDataRef("sim/cockpit/electrical/avionics_on");
  BatPwrOn = XPLMFindDataRef("sim/cockpit/electrical/battery_on");
  Frp = XPLMFindDataRef("sim/operation/misc/frame_rate_period");

  MHdg = XPLMFindDataRef("sim/flightmodel/position/magpsi");

  AirspeedIsMach = XPLMFindDataRef("sim/cockpit/autopilot/airspeed_is_mach");
  Airspeed = XPLMFindDataRef("sim/cockpit/autopilot/airspeed");

  ApAutThr = XPLMFindDataRef("sim/cockpit2/autopilot/autothrottle_enabled");


// **************** Find Switch Panel Commands Ref *******************
  ClFlOpn  = XPLMFindCommand("sim/flight_controls/cowl_flaps_open");
  ClFlCls  = XPLMFindCommand("sim/flight_controls/cowl_flaps_closed");
  PtHt0On   = XPLMFindCommand("sim/ice/pitot_heat0_on");
  PtHt0Off  = XPLMFindCommand("sim/ice/pitot_heat0_off");
  PtHt1On   = XPLMFindCommand("sim/ice/pitot_heat1_on");
  PtHt1Off  = XPLMFindCommand("sim/ice/pitot_heat1_off");

  PtHtOn   = XPLMFindCommand("sim/ice/pitot_heat_on");
  PtHtOff  = XPLMFindCommand("sim/ice/pitot_heat_off");

  AvLtOn   = XPLMFindCommand("sim/systems/avionics_on");
  AvLtOff  = XPLMFindCommand("sim/systems/avionics_off");
  BatOn   = XPLMFindCommand("sim/electrical/battery_1_on");
  BatOff  = XPLMFindCommand("sim/electrical/battery_1_off");

  LnLtOn   = XPLMFindCommand("sim/lights/landing_lights_on");
  LnLtOff  = XPLMFindCommand("sim/lights/landing_lights_off");
  TxLtOn   = XPLMFindCommand("sim/lights/taxi_lights_on");
  TxLtOff  = XPLMFindCommand("sim/lights/taxi_lights_off");
  StLtOn   = XPLMFindCommand("sim/lights/strobe_lights_on");
  StLtOff  = XPLMFindCommand("sim/lights/strobe_lights_off");
  NvLtOn   = XPLMFindCommand("sim/lights/nav_lights_on");
  NvLtOff  = XPLMFindCommand("sim/lights/nav_lights_off");
  BcLtOn   = XPLMFindCommand("sim/lights/beacon_lights_on");
  BcLtOff  = XPLMFindCommand("sim/lights/beacon_lights_off");
  GearUp   = XPLMFindCommand("sim/flight_controls/landing_gear_up");
  GearDn   = XPLMFindCommand("sim/flight_controls/landing_gear_down");

  MagOff1   = XPLMFindCommand("sim/magnetos/magnetos_off_1");
  MagOff2   = XPLMFindCommand("sim/magnetos/magnetos_off_2");
  MagOff3   = XPLMFindCommand("sim/magnetos/magnetos_off_3");
  MagOff4   = XPLMFindCommand("sim/magnetos/magnetos_off_4");
  MagOff5   = XPLMFindCommand("sim/magnetos/magnetos_off_5");
  MagOff6   = XPLMFindCommand("sim/magnetos/magnetos_off_6");
  MagOff7   = XPLMFindCommand("sim/magnetos/magnetos_off_7");
  MagOff8   = XPLMFindCommand("sim/magnetos/magnetos_off_8");

  MagLeft1  = XPLMFindCommand("sim/magnetos/magnetos_left_1");
  MagLeft2  = XPLMFindCommand("sim/magnetos/magnetos_left_2");
  MagLeft3  = XPLMFindCommand("sim/magnetos/magnetos_left_3");
  MagLeft4  = XPLMFindCommand("sim/magnetos/magnetos_left_4");
  MagLeft5  = XPLMFindCommand("sim/magnetos/magnetos_left_5");
  MagLeft6  = XPLMFindCommand("sim/magnetos/magnetos_left_6");
  MagLeft7  = XPLMFindCommand("sim/magnetos/magnetos_left_7");
  MagLeft8  = XPLMFindCommand("sim/magnetos/magnetos_left_8");

  MagRight1 = XPLMFindCommand("sim/magnetos/magnetos_right_1");
  MagRight2 = XPLMFindCommand("sim/magnetos/magnetos_right_2");
  MagRight3 = XPLMFindCommand("sim/magnetos/magnetos_right_3");
  MagRight4 = XPLMFindCommand("sim/magnetos/magnetos_right_4");
  MagRight5 = XPLMFindCommand("sim/magnetos/magnetos_right_5");
  MagRight6 = XPLMFindCommand("sim/magnetos/magnetos_right_6");
  MagRight7 = XPLMFindCommand("sim/magnetos/magnetos_right_7");
  MagRight8 = XPLMFindCommand("sim/magnetos/magnetos_right_8");

  MagBoth1  = XPLMFindCommand("sim/magnetos/magnetos_both_1");
  MagBoth2  = XPLMFindCommand("sim/magnetos/magnetos_both_2");
  MagBoth3  = XPLMFindCommand("sim/magnetos/magnetos_both_3");
  MagBoth4  = XPLMFindCommand("sim/magnetos/magnetos_both_4");
  MagBoth5  = XPLMFindCommand("sim/magnetos/magnetos_both_5");
  MagBoth6  = XPLMFindCommand("sim/magnetos/magnetos_both_6");
  MagBoth7  = XPLMFindCommand("sim/magnetos/magnetos_both_7");
  MagBoth8  = XPLMFindCommand("sim/magnetos/magnetos_both_8");

  EngStart1 = XPLMFindCommand("sim/starters/engage_starter_1");
  EngStart2 = XPLMFindCommand("sim/starters/engage_starter_2");
  EngStart3 = XPLMFindCommand("sim/starters/engage_starter_3");
  EngStart4 = XPLMFindCommand("sim/starters/engage_starter_4");
  EngStart5 = XPLMFindCommand("sim/starters/engage_starter_5");
  EngStart6 = XPLMFindCommand("sim/starters/engage_starter_6");
  EngStart7 = XPLMFindCommand("sim/starters/engage_starter_7");
  EngStart8 = XPLMFindCommand("sim/starters/engage_starter_8");

  BatOn1 = XPLMFindCommand("sim/electrical/battery_1_on");
  BatOn2 = XPLMFindCommand("sim/electrical/battery_2_on");

  BatOff1 = XPLMFindCommand("sim/electrical/battery_1_off");
  BatOff2 = XPLMFindCommand("sim/electrical/battery_2_off");

  GenOn1 = XPLMFindCommand("sim/electrical/generator_1_on");
  GenOn2 = XPLMFindCommand("sim/electrical/generator_2_on");
  GenOn3 = XPLMFindCommand("sim/electrical/generator_3_on");
  GenOn4 = XPLMFindCommand("sim/electrical/generator_4_on");
  GenOn5 = XPLMFindCommand("sim/electrical/generator_5_on");
  GenOn6 = XPLMFindCommand("sim/electrical/generator_6_on");
  GenOn7 = XPLMFindCommand("sim/electrical/generator_7_on");
  GenOn8 = XPLMFindCommand("sim/electrical/generator_8_on");

  GenOff1 = XPLMFindCommand("sim/electrical/generator_1_off");
  GenOff2 = XPLMFindCommand("sim/electrical/generator_2_off");
  GenOff3 = XPLMFindCommand("sim/electrical/generator_3_off");
  GenOff4 = XPLMFindCommand("sim/electrical/generator_4_off");
  GenOff5 = XPLMFindCommand("sim/electrical/generator_5_off");
  GenOff6 = XPLMFindCommand("sim/electrical/generator_6_off");
  GenOff7 = XPLMFindCommand("sim/electrical/generator_7_off");
  GenOff8 = XPLMFindCommand("sim/electrical/generator_8_off");

  FuelPumpOn1 = XPLMFindCommand("sim/fuel/fuel_pump_1_on");
  FuelPumpOn2 = XPLMFindCommand("sim/fuel/fuel_pump_2_on");
  FuelPumpOn3 = XPLMFindCommand("sim/fuel/fuel_pump_3_on");
  FuelPumpOn4 = XPLMFindCommand("sim/fuel/fuel_pump_4_on");
  FuelPumpOn5 = XPLMFindCommand("sim/fuel/fuel_pump_5_on");
  FuelPumpOn6 = XPLMFindCommand("sim/fuel/fuel_pump_6_on");
  FuelPumpOn7 = XPLMFindCommand("sim/fuel/fuel_pump_7_on");
  FuelPumpOn8 = XPLMFindCommand("sim/fuel/fuel_pump_8_on");

  FuelPumpOff1 = XPLMFindCommand("sim/fuel/fuel_pump_1_off");
  FuelPumpOff2 = XPLMFindCommand("sim/fuel/fuel_pump_2_off");
  FuelPumpOff3 = XPLMFindCommand("sim/fuel/fuel_pump_3_off");
  FuelPumpOff4 = XPLMFindCommand("sim/fuel/fuel_pump_4_off");
  FuelPumpOff5 = XPLMFindCommand("sim/fuel/fuel_pump_5_off");
  FuelPumpOff6 = XPLMFindCommand("sim/fuel/fuel_pump_6_off");
  FuelPumpOff7 = XPLMFindCommand("sim/fuel/fuel_pump_7_off");
  FuelPumpOff8 = XPLMFindCommand("sim/fuel/fuel_pump_8_off");

// **************** Find Switch Panel Data Ref *******************
  AntiIce           = XPLMFindDataRef("sim/cockpit/switches/anti_ice_on");
  CockpitLights     = XPLMFindDataRef("sim/cockpit/electrical/cockpit_lights");
  CowlFlaps         = XPLMFindDataRef("sim/flightmodel/engine/ENGN_cowl");
  GearRetract       = XPLMFindDataRef("sim/aircraft/gear/acf_gear_retract");
  LandingGearStatus = XPLMFindDataRef("sim/aircraft/parts/acf_gear_deploy");
  Gear1Fail         = XPLMFindDataRef("sim/operation/failures/rel_lagear1");
  Gear2Fail         = XPLMFindDataRef("sim/operation/failures/rel_lagear2");
  Gear3Fail         = XPLMFindDataRef("sim/operation/failures/rel_lagear3");

  OnGround          = XPLMFindDataRef("sim/flightmodel/failures/onground_any");

  BatNum            = XPLMFindDataRef("sim/aircraft/electrical/num_batteries");
  GenNum            = XPLMFindDataRef("sim/aircraft/electrical/num_generators");
  EngNum            = XPLMFindDataRef("sim/aircraft/engine/acf_num_engines");
  BatArrayOnDR      = XPLMFindDataRef("sim/cockpit/electrical/battery_array_on");

  IgnSwitchArray    = XPLMFindDataRef("sim/cockpit2/engine/actuators/ignition_key");
  EngnMixt          = XPLMFindDataRef("sim/flightmodel/engine/ENGN_mixt");
  IgniterOn         = XPLMFindDataRef("sim/cockpit2/engine/actuators/igniter_on");
  AcfEnType         = XPLMFindDataRef("sim/aircraft/prop/acf_en_type");

// ************* Open any Radio that is connected *****************

  struct hid_device_info *rad_devs, *rad_cur_dev;

  rad_devs = hid_enumerate(0x6a3, 0x0d05);
  rad_cur_dev = rad_devs;
  while (rad_cur_dev) {
        radiohandle[radcnt] = hid_open_path(rad_cur_dev->path);
        hid_set_nonblocking(radiohandle[radcnt], 1);
        radiores = hid_read(radiohandle[radcnt], radiobuf[radcnt], sizeof(radiobuf[radcnt]));
        hid_send_feature_report(radiohandle[radcnt], radiowbuf[radcnt], 23);
        radcnt++;
        rad_cur_dev = rad_cur_dev->next;
  }
  hid_free_enumeration(rad_devs);

// *** Find Connected Multi Panel *****

  struct hid_device_info *multi_devs, *multi_cur_dev;

  multi_devs = hid_enumerate(0x6a3, 0x0d06);
  multi_cur_dev = multi_devs;
  while (multi_cur_dev) {
        multihandle = hid_open_path(multi_cur_dev->path);
        hid_set_nonblocking(multihandle, 1);
        multires = hid_read(multihandle, multibuf, sizeof(multibuf));
        hid_send_feature_report(multihandle, multiwbuf, 13);
        multicnt++;
        multi_cur_dev = multi_cur_dev->next;
  }
  hid_free_enumeration(multi_devs);

// *** Find Connected Switch Panel *****

  struct hid_device_info *switch_devs, *switch_cur_dev;

  switch_devs = hid_enumerate(0x6a3, 0x0d67);
  switch_cur_dev = switch_devs;
  while (switch_cur_dev) {
        switchhandle = hid_open_path(switch_cur_dev->path);
        hid_set_nonblocking(switchhandle, 1);
        switchres = hid_read(switchhandle, switchbuf, sizeof(switchbuf));
        hid_send_feature_report(switchhandle, switchwbuf, 2);
        switchcnt++;
        switch_cur_dev = switch_cur_dev->next;
  }
  hid_free_enumeration(switch_devs);


  // *** Find Connected BIP Panel *****

  struct hid_device_info *bip_devs, *bip_cur_dev;

  bip_devs = hid_enumerate(0x6a3, 0xb4e);
  bip_cur_dev = bip_devs;
  char	buf[256];
  int result;
  // find serial numbers of all BIP's connected
  while (bip_cur_dev) {
      biphandle[biptmpcnt] = hid_open_path(bip_cur_dev->path);
      hid_get_serial_number_string(biphandle[biptmpcnt], wstr[biptmpcnt], MAX_STR);
      //sprintf(buf, "biptmpcnt = %d  Serial Number String: %ls\n", biptmpcnt, wstr[biptmpcnt]);
      //XPLMDebugString(buf);
      hid_close(biphandle[biptmpcnt]);
      biptmpcnt++;
      bip_cur_dev = bip_cur_dev->next;
  }

  hid_free_enumeration(bip_devs);

  if (biptmpcnt > 1) {

     result = wcscmp(wstr[0], wstr[1]);
     if(result > 0){
       //sprintf(buf, "(result > 0) %ls > %ls\n", wstr[0], wstr[1]);
       //XPLMDebugString(buf);
       biphandle[0] = hid_open(0x6a3, 0xb4e, wstr[0]);
       bipwbuf[0][0] = 0xb2; // 0xb2 Report ID for brightness
       bipwbuf[0][1] = 100;  // Set brightness to 100%
       bipres = hid_send_feature_report(biphandle[0], bipwbuf[0], 10);
       bipwcscmp0 = 0;

       biphandle[1] = hid_open(0x6a3, 0xb4e, wstr[1]);
       bipwbuf[1][0] = 0xb2; // 0xb2 Report ID for brightness
       bipwbuf[1][1] = 100;  // Set brightness to 100%
       bipres = hid_send_feature_report(biphandle[1], bipwbuf[1], 10);
       bipwcscmp1 = 1;

     }else if (result < 0){
       //sprintf(buf, "(result < 0) %ls < %ls\n", wstr[0], wstr[1]);
       //XPLMDebugString(buf);
       biphandle[1] = hid_open(0x6a3, 0xb4e, wstr[0]);
       bipwbuf[0][0] = 0xb2; // 0xb2 Report ID for brightness
       bipwbuf[0][1] = 100;  // Set brightness to 100%
       bipres = hid_send_feature_report(biphandle[1], bipwbuf[0], 10);
       bipwcscmp0 = 0;

       biphandle[0] = hid_open(0x6a3, 0xb4e, wstr[1]);
       bipwbuf[1][0] = 0xb2; // 0xb2 Report ID for brightness
       bipwbuf[1][1] = 100;  // Set brightness to 100%
       bipres = hid_send_feature_report(biphandle[0], bipwbuf[1], 10);
       bipwcscmp1 = 1;

     }

 }else if (biptmpcnt == 1){
      biphandle[0] = hid_open(0x6a3, 0xb4e, wstr[0]);
      bipwbuf[0][0] = 0xb2; // 0xb2 Report ID for brightness
      bipwbuf[0][1] = 100;  // Set brightness to 100%
      bipres = hid_send_feature_report(biphandle[0], bipwbuf[0], 10);
      bipwcscmp0 = 0;
  }

  bipcnt = biptmpcnt;

  sprintf(buf, "Xsaitekpanels: found %d Switch  %d Radio  %d Multi  %d BIP Panels\n", switchcnt, radcnt, multicnt, bipcnt);
  XPLMDebugString(buf);

  // * Register our callback for every loop. Positive intervals
  // * are in seconds, negative are the negative of sim frames.  Zero
  // * registers but does not schedule a callback for time.
  XPLMRegisterFlightLoopCallback(		
                        MyPanelsFlightLoopCallback,	// * Callback *
                        interval,			// * Interval -1 every loop*
                        NULL);				// * refcon not used. *

  // Register our custom commands
  XPLMRegisterCommandHandler(XpanelsFnButtonCommand,           // in Command name
                             XpanelsFnButtonCommandHandler,    // in Handler
                             1,                          // Receive input before plugin windows.
                             (void *) 0);                // inRefcon.

  // Create our menu

   XsaitekpanelsMenuItem = XPLMAppendMenuItem(
              XPLMFindPluginsMenu(),
              "Xsaitekpanels",
               NULL,
               1);

   XsaitekpanelsMenu = XPLMCreateMenu(
               "Xsaitekpanels",
               XPLMFindPluginsMenu(),
               XsaitekpanelsMenuItem,
               XsaitekpanelsMenuHandler,
               (void *)0);

   ConfigSubMenuItem = XPLMAppendMenuItem(
           XsaitekpanelsMenu,
           "xsaitekpanels.ini",
           NULL,
           1);

   ConfigMenuId = XPLMCreateMenu(
           "xsaitekpanels.ini",
           XsaitekpanelsMenu,
           ConfigSubMenuItem,
           XsaitekpanelsMenuHandler,
           (void *)1);

    XPLMClearAllMenuItems(ConfigMenuId);
    XPLMAppendMenuItem(ConfigMenuId, "Reload xsaitekpanels.ini", (void *) "TRUE", 1);


   if (bipcnt > 0) {

     if(bipcnt > 0){
       BipSubMenuItem = XPLMAppendMenuItem(
               XsaitekpanelsMenu,
               "Bip",
               NULL,
               2);


       BipMenuId = XPLMCreateMenu(
               "Bip",
               XsaitekpanelsMenu,
               BipSubMenuItem,
               XsaitekpanelsMenuHandler,
               (void *)2);



       BipWidgetID = XPCreateWidget(XPLMGetDatai(XPLMFindDataRef("sim/graphics/view/window_width"))-150,
                                    XPLMGetDatai(XPLMFindDataRef("sim/graphics/view/window_height")),
                                    XPLMGetDatai(XPLMFindDataRef("sim/graphics/view/window_width"))-10,
                                    XPLMGetDatai(XPLMFindDataRef("sim/graphics/view/window_height"))-10,         // screen coordinates
                                    1,                            // visible
                                    "BIP is working!", // description
                                    1, NULL,                      // we want it root
                                    xpWidgetClass_Caption);
       XPSetWidgetProperty(BipWidgetID, xpProperty_CaptionLit, 0);
     }

     if(bipcnt > 1) {
       Bip2SubMenuItem = XPLMAppendMenuItem(
           XsaitekpanelsMenu,
           "Bip2",
           NULL,
           3);

       Bip2MenuId = XPLMCreateMenu(
           "Bip2",
           XsaitekpanelsMenu,
           Bip2SubMenuItem,
           XsaitekpanelsMenuHandler,
           (void *)3);
     }

   }

   if (multicnt > 0) {

       MultiSubMenuItem = XPLMAppendMenuItem(
               XsaitekpanelsMenu,
               "Multi",
               NULL,
               4);


       MultiMenuId = XPLMCreateMenu(
               "Multi",
               XsaitekpanelsMenu,
               MultiSubMenuItem,
               XsaitekpanelsMenuHandler,
               (void *)4);
  }

   if (radcnt > 0) {

       RadioSubMenuItem = XPLMAppendMenuItem(
               XsaitekpanelsMenu,
               "Radio",
               NULL,
               5);


       RadioMenuId = XPLMCreateMenu(
               "Radio",
               XsaitekpanelsMenu,
               RadioSubMenuItem,
               XsaitekpanelsMenuHandler,
               (void *)5);
  }

   if (switchcnt > 0) {

       SwitchSubMenuItem = XPLMAppendMenuItem(
               XsaitekpanelsMenu,
               "Switch",
               NULL,
               6);


       SwitchMenuId = XPLMCreateMenu(
               "Switch",
               XsaitekpanelsMenu,
               SwitchSubMenuItem,
               XsaitekpanelsMenuHandler,
               (void *)6);
  }

  return 1;
}

PLUGIN_API void	XPluginStop(void)
{

  XPLMDebugString("XPluginStop has been called \n");


  if (switchMenuItem == 1)
  {
          XPDestroyWidget(SwitchWidgetID, 1);
          switchMenuItem = 0;
  }

  stopradcnt = radcnt - 1;

  // *** if open blank display and then close that radio panel ****

  if (stopradcnt == 3) {

      blankradiowbuf[3][0] = 0, blankradiowbuf[3][1] = 15, blankradiowbuf[3][2] = 15;
      blankradiowbuf[3][3] = 15, blankradiowbuf[3][4] = 15, blankradiowbuf[3][5] = 15;
      blankradiowbuf[3][6] = 15, blankradiowbuf[3][7] = 15, blankradiowbuf[3][8] = 15;
      blankradiowbuf[3][9] = 15, blankradiowbuf[3][10] = 15, blankradiowbuf[3][11] = 15;
      blankradiowbuf[3][12] = 15, blankradiowbuf[3][13] = 15, blankradiowbuf[3][14] = 15;
      blankradiowbuf[3][15] = 15, blankradiowbuf[3][16] = 15, blankradiowbuf[3][17] = 15;
      blankradiowbuf[3][18] = 15, blankradiowbuf[3][19] = 15, blankradiowbuf[3][20] = 15;

      radres = hid_send_feature_report(radiohandle[stopradcnt], blankradiowbuf[stopradcnt], 23);
      hid_close(radiohandle[stopradcnt]);
      stopradcnt--;
  }

  if (stopradcnt == 2) {

      blankradiowbuf[2][0] = 0, blankradiowbuf[2][1] = 15, blankradiowbuf[2][2] = 15;
      blankradiowbuf[2][3] = 15, blankradiowbuf[2][4] = 15, blankradiowbuf[2][5] = 15;
      blankradiowbuf[2][6] = 15, blankradiowbuf[2][7] = 15, blankradiowbuf[2][8] = 15;
      blankradiowbuf[2][9] = 15, blankradiowbuf[2][10] = 15, blankradiowbuf[2][11] = 15;
      blankradiowbuf[2][12] = 15, blankradiowbuf[2][13] = 15, blankradiowbuf[2][14] = 15;
      blankradiowbuf[2][15] = 15, blankradiowbuf[2][16] = 15, blankradiowbuf[2][17] = 15;
      blankradiowbuf[2][18] = 15, blankradiowbuf[2][19] = 15, blankradiowbuf[2][20] = 15;

      radres = hid_send_feature_report(radiohandle[stopradcnt], blankradiowbuf[stopradcnt], 23);
      hid_close(radiohandle[stopradcnt]);
      stopradcnt--;
  }

  if (stopradcnt == 1) {

      blankradiowbuf[1][0] = 0, blankradiowbuf[1][1] = 15, blankradiowbuf[1][2] = 15;
      blankradiowbuf[1][3] = 15, blankradiowbuf[1][4] = 15, blankradiowbuf[1][5] = 15;
      blankradiowbuf[1][6] = 15, blankradiowbuf[1][7] = 15, blankradiowbuf[1][8] = 15;
      blankradiowbuf[1][9] = 15, blankradiowbuf[1][10] = 15, blankradiowbuf[1][11] = 15;
      blankradiowbuf[1][12] = 15, blankradiowbuf[1][13] = 15, blankradiowbuf[1][14] = 15;
      blankradiowbuf[1][15] = 15, blankradiowbuf[1][16] = 15, blankradiowbuf[1][17] = 15;
      blankradiowbuf[1][18] = 15, blankradiowbuf[1][19] = 15, blankradiowbuf[1][20] = 15;

      radres = hid_send_feature_report(radiohandle[stopradcnt], blankradiowbuf[stopradcnt], 23);
      hid_close(radiohandle[stopradcnt]);
      stopradcnt--;
  }

  if (stopradcnt == 0) {

      blankradiowbuf[0][0] = 0, blankradiowbuf[0][1] = 15, blankradiowbuf[0][2] = 15;
      blankradiowbuf[0][3] = 15, blankradiowbuf[0][4] = 15, blankradiowbuf[0][5] = 15;
      blankradiowbuf[0][6] = 15, blankradiowbuf[0][7] = 15, blankradiowbuf[0][8] = 15;
      blankradiowbuf[0][9] = 15, blankradiowbuf[0][10] = 15, blankradiowbuf[0][11] = 15;
      blankradiowbuf[0][12] = 15, blankradiowbuf[0][13] = 15, blankradiowbuf[0][14] = 15;
      blankradiowbuf[0][15] = 15, blankradiowbuf[0][16] = 15, blankradiowbuf[0][17] = 15;
      blankradiowbuf[0][18] = 15, blankradiowbuf[0][19] = 15, blankradiowbuf[0][20] = 15;

      radres = hid_send_feature_report(radiohandle[stopradcnt], blankradiowbuf[stopradcnt], 23);
      hid_close(radiohandle[stopradcnt]);
  }



  // *** if open blank display and then close that multi panel ***
  if (multicnt > 0) {
        blankmultiwbuf[0] = 0, blankmultiwbuf[1] = 15, blankmultiwbuf[2] = 15;
        blankmultiwbuf[3] = 15, blankmultiwbuf[4] = 15, blankmultiwbuf[5] = 15;
        blankmultiwbuf[6] = 15, blankmultiwbuf[7] = 15, blankmultiwbuf[8] = 15;
        blankmultiwbuf[9] = 15, blankmultiwbuf[10] = 15, blankmultiwbuf[11] = 0;
        multires = hid_send_feature_report(multihandle, blankmultiwbuf, 13);
        hid_close(multihandle);

  }


// *** if open close that switch panel ***

  if (switchcnt > 0) {

      blankswitchwbuf[0] = 0;
      blankswitchwbuf[1] = 0;
      switchres = hid_send_feature_report(switchhandle, blankswitchwbuf, 2);
      hid_close(switchhandle);
  }

// *** if open close that bip panel ***

  stopbipcnt = bipcnt - 1;


  if (stopbipcnt == 3) {

       bipwbuf[3][0] = 0xb8;  //0xb8 Report ID to display
       bipwbuf[3][1] = 0, bipwbuf[3][2] = 0, bipwbuf[3][3] = 0;
       bipwbuf[3][4] = 0, bipwbuf[3][5] = 0, bipwbuf[3][6] = 0;

       bipres = hid_send_feature_report(biphandle[stopbipcnt], bipwbuf[stopbipcnt], 10);
       hid_close(biphandle[stopbipcnt]);
       stopbipcnt--;
  }

  if (stopbipcnt == 2) {

       bipwbuf[2][0] = 0xb8;  //0xb8 Report ID to display
       bipwbuf[2][1] = 0, bipwbuf[2][2] = 0, bipwbuf[2][3] = 0;
       bipwbuf[2][4] = 0, bipwbuf[2][5] = 0, bipwbuf[2][6] = 0;

       bipres = hid_send_feature_report(biphandle[stopbipcnt], bipwbuf[stopbipcnt], 10);
       hid_close(biphandle[stopbipcnt]);
       stopbipcnt--;
  }

  if (stopbipcnt == 1) {

       bipwbuf[1][0] = 0xb8;  //0xb8 Report ID to display
       bipwbuf[1][1] = 0, bipwbuf[1][2] = 0, bipwbuf[1][3] = 0;
       bipwbuf[1][4] = 0, bipwbuf[1][5] = 0, bipwbuf[1][6] = 0;

       bipres = hid_send_feature_report(biphandle[stopbipcnt], bipwbuf[stopbipcnt], 10);
       hid_close(biphandle[stopbipcnt]);
       stopbipcnt--;
  }

  if (stopbipcnt == 0) {

       bipwbuf[0][0] = 0xb8;  //0xb8 Report ID to display
       bipwbuf[0][1] = 0, bipwbuf[0][2] = 0, bipwbuf[0][3] = 0;
       bipwbuf[0][4] = 0, bipwbuf[0][5] = 0, bipwbuf[0][6] = 0;

       bipres = hid_send_feature_report(biphandle[stopbipcnt], bipwbuf[stopbipcnt], 10);
       hid_close(biphandle[stopbipcnt]);
       stopbipcnt--;
  }

  // ********** Unregitser the callback on quit. *************
  XPLMUnregisterFlightLoopCallback(MyPanelsFlightLoopCallback, NULL);
  XPLMUnregisterCommandHandler(XpanelsFnButtonCommand, XpanelsFnButtonCommandHandler, 1, NULL);
  XPDestroyWidget(BipWidgetID, 1);
  XPLMDestroyMenu(BipMenuId);
  XPLMDestroyMenu(Bip2MenuId);
  XPLMDestroyMenu(Bip3MenuId);
  XPLMDestroyMenu(MultiMenuId);
  XPLMDestroyMenu(RadioMenuId);
  XPLMDestroyMenu(SwitchMenuId);

  XPLMDestroyMenu(SwitchWidgetID);
  XPLMDestroyMenu(RadioWidgetID);
  XPLMDestroyMenu(MultiWidgetID);

}

PLUGIN_API void XPluginDisable(void)
{
}

PLUGIN_API int XPluginEnable(void)
{
         return 1;
}

PLUGIN_API void XPluginReceiveMessage(XPLMPluginID	inFromWho,
                                      int		inMessage,
                                      void *		inParam)
{
    (void) inFromWho; // To get rid of warnings on unused variables
    std::string          PlaneICAO = "[]";
    char            ICAOString[40];

    XPLMGetDatab(XPLMFindDataRef("sim/aircraft/view/acf_ICAO"), ICAOString, 0, 40);

    PlaneICAO.insert(1,ICAOString);

    if ((inMessage == XPLM_MSG_PLANE_LOADED) & ((intptr_t) inParam == 0)) {
      process_read_ini_file();
    }

    if(bipcnt > 0){

        if ((inMessage == XPLM_MSG_PLANE_LOADED) & ((intptr_t) inParam == 0)) {
          process_bip_panel();
          ReadConfigFile(PlaneICAO);
          if(bipcnt > 1){
             process_bip_panel();
             ReadConfigFile(PlaneICAO);
          }
        }
        if (inMessage == XPLM_MSG_AIRPORT_LOADED) {
          ReadConfigFile(PlaneICAO);
          if(bipcnt > 1){
             process_bip_panel();
             ReadConfigFile(PlaneICAO);
          }

        }

    }

}

void XsaitekpanelsMenuHandler(void * inMenuRef, void * inItemRef)
{

    if((intptr_t)inMenuRef == 1){
         if (strcmp((char *) inItemRef, "TRUE") == 0) {
             process_read_ini_file();
         }

    }

    if((intptr_t)inMenuRef == 2){
        bipnum = 0;
        if (strcmp((char *) inItemRef, "[DEFAULT]") == 0) {
              ReadConfigFile((char *) inItemRef);
        }
         if (strcmp((char *) inItemRef, "<<CSV>>") == 0) {
             WriteCSVTableToDisk();
         }
         if (strcmp((char *) inItemRef, "[BIP_TEST]") == 0) {
               ReadConfigFile((char *) inItemRef);
         }

         else {
               ReadConfigFile((char *) inItemRef);

         }

    }

    if((intptr_t)inMenuRef == 3){
        bipnum = 1;
        if (strcmp((char *) inItemRef, "[DEFAULT]") == 0) {

             ReadConfigFile((char *) inItemRef);
        }

        if (strcmp((char *) inItemRef, "<<CSV>>") == 0) {
             WriteCSVTableToDisk();
        }

        if (strcmp((char *) inItemRef, "[BIP_TEST]") == 0) {
               ReadConfigFile((char *) inItemRef);
        }

        else {
               ReadConfigFile((char *) inItemRef);

         }

    }


    if((intptr_t)inMenuRef == 4){
       if (strcmp((char *) inItemRef, "MULTI_WIDGET") == 0) {
             CreateMultiWidget(05, 700, 300, 330);	//left, top, right, bottom.
             multiMenuItem = 1;
       }

    }

    if((intptr_t)inMenuRef == 5){

         if (strcmp((char *) inItemRef, "RADIO_WIDGET") == 0) {
             CreateRadioWidget(15, 700, 300, 300);	//left, top, right, bottom.
             radioMenuItem = 1;
         }

    }

    if((intptr_t)inMenuRef == 6){
         if (strcmp((char *) inItemRef, "SWITCH_WIDGET") == 0) {
             CreateSwitchWidget(05, 700, 300, 510);	//left, top, right, bottom.
             switchMenuItem = 1;

         }

    }



    return;
}


// This will create our switch widget dialog.
void CreateSwitchWidget(int x, int y, int w, int h)
{
        int x2 = x + w;
        int y2 = y - h;
        int Index = 0;
        int yOffset;

        DataRefID.clear();
        memset(SwitchEnableCheckWidget, 0, sizeof(SwitchEnableCheckWidget));
        memset(SwitchDisableCheckWidget, 0, sizeof(SwitchDisableCheckWidget));
        memset(SwitchRemapCheckWidget, 0, sizeof(SwitchRemapCheckWidget));
        memset(SwitchBatAltCheckWidget, 0, sizeof(SwitchBatAltCheckWidget));


// Create the Main Widget window.
        SwitchWidgetID = XPCreateWidget(x, y, x2, y2,
                                        1,		        	// Visible
                                        "Switch   Panel   Mappings",	// desc
                                        1,				// root
                                        NULL,				// no container
                                        xpWidgetClass_MainWindow);


// Add Close Box to the Main Widget.  Other options are available.  See the SDK Documentation.
        XPSetWidgetProperty(SwitchWidgetID, xpProperty_MainWindowHasCloseBoxes, 1);
        XPSetWidgetProperty(SwitchWidgetID, xpProperty_MainWindowType, xpMainWindowStyle_Translucent);

// Checkbox for Bat Alt Normal

        yOffset = (01+05+(1*15));
        SwitchBatAltCheckWidget[0] = XPCreateWidget(x+05, y-yOffset, x+05+22, y-yOffset-20,
                      1,	// Visible
                      "",       // desc
                      0,	// root
                      SwitchWidgetID,
                      xpWidgetClass_Button);

        XPSetWidgetProperty(SwitchBatAltCheckWidget[0], xpProperty_ButtonType, xpRadioButton);
        XPSetWidgetProperty(SwitchBatAltCheckWidget[0], xpProperty_ButtonBehavior, xpButtonBehaviorRadioButton);
        XPSetWidgetProperty(SwitchBatAltCheckWidget[0], xpProperty_ButtonState, 0);


// Labels for Bat Alt Normal

        yOffset = (01+05+(1*15));
        SwitchBatAltTextWidget[0] = XPCreateWidget(x+35, y-yOffset, x+35+100, y-yOffset-20,
                      1,	// Visible
                      "Bat Alt Normal",// desc
                      0,		// root
                      SwitchWidgetID,
                      xpWidgetClass_Caption);

        XPSetWidgetProperty(SwitchBatAltTextWidget[0], xpProperty_CaptionLit, 1);


// Checkbox for Alt Bat Cessna

        yOffset = (01+05+(1*15));
        SwitchAltBatCheckWidget[0] = XPCreateWidget(x+125, y-yOffset, x+125+22, y-yOffset-20,
                              1,	// Visible
                              "",       // desc
                              0,	// root
                              SwitchWidgetID,
                              xpWidgetClass_Button);

        XPSetWidgetProperty(SwitchAltBatCheckWidget[0], xpProperty_ButtonType, xpRadioButton);
        XPSetWidgetProperty(SwitchAltBatCheckWidget[0], xpProperty_ButtonBehavior, xpButtonBehaviorRadioButton);
        XPSetWidgetProperty(SwitchAltBatCheckWidget[0], xpProperty_ButtonState, 0);


 // Labels for Alt Bat Cessna

        yOffset = (01+05+(1*15));
        SwitchAltBatTextWidget[0] = XPCreateWidget(x+155, y-yOffset, x+155+100, y-yOffset-20,
                              1,	// Visible
                              "Alt Bat Cessna",// desc
                              0,		// root
                              SwitchWidgetID,
                              xpWidgetClass_Caption);

        XPSetWidgetProperty(SwitchAltBatTextWidget[0], xpProperty_CaptionLit, 1);

// Checkbox for Starter Switch Old Style

        yOffset = (25+05+(1*15));
        SwitchStartSwitchOldCheckWidget[0] = XPCreateWidget(x+05, y-yOffset, x+05+22, y-yOffset-20,
                      1,	// Visible
                      "",       // desc
                      0,	// root
                      SwitchWidgetID,
                      xpWidgetClass_Button);

        XPSetWidgetProperty(SwitchStartSwitchOldCheckWidget[0], xpProperty_ButtonType, xpRadioButton);
        XPSetWidgetProperty(SwitchStartSwitchOldCheckWidget[0], xpProperty_ButtonBehavior, xpButtonBehaviorRadioButton);
        XPSetWidgetProperty(SwitchStartSwitchOldCheckWidget[0], xpProperty_ButtonState, 0);

// Label for Starter Switch Old Style

        yOffset = (25+05+(1*15));
        SwitchStartSwitchOldTextWidget[0] = XPCreateWidget(x+35, y-yOffset, x+35+100, y-yOffset-20,
                      1,	// Visible
                      "Start Switch Old",// desc
                      0,		// root
                      SwitchWidgetID,
                      xpWidgetClass_Caption);

        XPSetWidgetProperty(SwitchStartSwitchOldTextWidget[0], xpProperty_CaptionLit, 1);

// Checkbox for Starter Switch New Style

        yOffset = (25+05+(1*15));
        SwitchStartSwitchNewCheckWidget[0] = XPCreateWidget(x+125, y-yOffset, x+125+22, y-yOffset-20,
                              1,	// Visible
                              "",       // desc
                              0,	// root
                              SwitchWidgetID,
                              xpWidgetClass_Button);

        XPSetWidgetProperty(SwitchStartSwitchNewCheckWidget[0], xpProperty_ButtonType, xpRadioButton);
        XPSetWidgetProperty(SwitchStartSwitchNewCheckWidget[0], xpProperty_ButtonBehavior, xpButtonBehaviorRadioButton);
        XPSetWidgetProperty(SwitchStartSwitchNewCheckWidget[0], xpProperty_ButtonState, 0);

// Label for Starter Switch New Style

        yOffset = (25+05+(1*15));
        SwitchStartSwitchNewTextWidget[0] = XPCreateWidget(x+155, y-yOffset, x+155+100, y-yOffset-20,
                              1,	// Visible
                              "Start Switch New",// desc
                              0,		// root
                              SwitchWidgetID,
                              xpWidgetClass_Caption);

        XPSetWidgetProperty(SwitchStartSwitchNewTextWidget[0], xpProperty_CaptionLit, 1);

// Labels for Enable Disable and Remapable

        yOffset = (25+28+(1*15));
        SwitchLabelTextWidget[Index] = XPCreateWidget(x+05, y-yOffset, x+05+170, y-yOffset-20,
              1,	// Visible
              "Disable        Enable        Remapable",// desc
              0,		// root
              SwitchWidgetID,
              xpWidgetClass_Caption);
        XPSetWidgetProperty(SwitchLabelTextWidget[Index], xpProperty_CaptionLit, 1);


// Create a check box for a disable item widget

       for (Index=0; Index < 50; Index++)
       {
            if(strcmp(SwitchText[Index],"end") == 0) {break;}

            yOffset = (65+28+(Index*20));
            SwitchDisableCheckWidget[Index] = XPCreateWidget(x+05, y-yOffset, x+05+22, y-yOffset-20,
                   1,	// Visible
                   "",    // desc
                   0,	// root
                   SwitchWidgetID,
                   xpWidgetClass_Button);

             XPSetWidgetProperty(SwitchDisableCheckWidget[Index], xpProperty_ButtonType, xpRadioButton);
             XPSetWidgetProperty(SwitchDisableCheckWidget[Index], xpProperty_ButtonBehavior, xpButtonBehaviorRadioButton);
             XPSetWidgetProperty(SwitchDisableCheckWidget[Index], xpProperty_ButtonState, 0);

       }

// Create a check box for a enable item widget

       for (Index=0; Index < 50; Index++)
       {
            if(strcmp(SwitchText[Index],"end") == 0) {break;}

            yOffset = (65+28+(Index*20));
            SwitchEnableCheckWidget[Index] = XPCreateWidget(x+65, y-yOffset, x+65+22, y-yOffset-20,
                   1,	// Visible
                   "",    // desc
                   0,	// root
                   SwitchWidgetID,
                   xpWidgetClass_Button);

           XPSetWidgetProperty(SwitchEnableCheckWidget[Index], xpProperty_ButtonType, xpRadioButton);
           XPSetWidgetProperty(SwitchEnableCheckWidget[Index], xpProperty_ButtonBehavior, xpButtonBehaviorRadioButton);
           XPSetWidgetProperty(SwitchEnableCheckWidget[Index], xpProperty_ButtonState, 0);

       }



// Create a check box for a remap item widget

       for (Index=0; Index < 50; Index++)
       {
            if(strcmp(SwitchText[Index],"end") == 0) {break;}

            yOffset = (65+28+(Index*20));
            SwitchRemapCheckWidget[Index] = XPCreateWidget(x+125, y-yOffset, x+125+22, y-yOffset-20,
                   1,	// Visible
                   "",    // desc
                   0,	// root
                   SwitchWidgetID,
                   xpWidgetClass_Button);

            XPSetWidgetProperty(SwitchRemapCheckWidget[Index], xpProperty_ButtonType, xpRadioButton);
            XPSetWidgetProperty(SwitchRemapCheckWidget[Index], xpProperty_ButtonBehavior, xpButtonBehaviorRadioButton);
            XPSetWidgetProperty(SwitchRemapCheckWidget[Index], xpProperty_ButtonState, 0);

       }


// Create a text widget

       for (Index=0; Index < 50; Index++)
       {
            if(strcmp(SwitchText[Index],"end") == 0) {break;}

            yOffset = (65+28+(Index*20));
            SwitchTextWidget[Index] = XPCreateWidget(x+170, y-yOffset, x+170+170, y-yOffset-20,
                  1,	// Visible
                  SwitchText[Index],// desc
                  0,		// root
                  SwitchWidgetID,
                  xpWidgetClass_Caption);
            XPSetWidgetProperty(SwitchTextWidget[Index], xpProperty_CaptionLit, 1);


        }



// Register our widget handler
        XPAddWidgetCallback(SwitchWidgetID, SwitchHandler);

        process_read_ini_file();
}

// This is our widget handler.  In this example we are only interested when the close box is pressed.
int	SwitchHandler(XPWidgetMessage  SwitchinMessage, XPWidgetID  SwitchWidgetID, intptr_t  inParam1, intptr_t  inParam2)
{
        (void) inParam2;
        int State;
        int Index1;
        if (SwitchinMessage == xpMessage_CloseButtonPushed)
        {
                if (switchMenuItem == 1)
                {
                        XPHideWidget(SwitchWidgetID);
                }
                return 1;
        }


        if(SwitchinMessage == xpMsg_ButtonStateChanged)
        {

            if(inParam1 == (intptr_t)SwitchBatAltCheckWidget[0] ||
               inParam1 == (intptr_t)SwitchAltBatCheckWidget[0]) {

                     XPSetWidgetProperty(SwitchBatAltCheckWidget[0], xpProperty_ButtonState, 0);
                     XPSetWidgetProperty(SwitchAltBatCheckWidget[0], xpProperty_ButtonState, 0);

                     XPSetWidgetProperty((XPWidgetID)inParam1, xpProperty_ButtonState, 1);
            }

            if(inParam1 == (intptr_t)SwitchStartSwitchOldCheckWidget[0] ||
               inParam1 == (intptr_t)SwitchStartSwitchNewCheckWidget[0]) {

                     XPSetWidgetProperty(SwitchStartSwitchOldCheckWidget[0], xpProperty_ButtonState, 0);
                     XPSetWidgetProperty(SwitchStartSwitchNewCheckWidget[0], xpProperty_ButtonState, 0);

                     XPSetWidgetProperty((XPWidgetID)inParam1, xpProperty_ButtonState, 1);
            }


            for (Index1=0; Index1 < 50; Index1++)
            {
                 if(strcmp(SwitchText[Index1],"end") == 0) {break;}



            if(inParam1 == (intptr_t)SwitchDisableCheckWidget[Index1] ||
               inParam1 == (intptr_t)SwitchEnableCheckWidget[Index1] ||
               inParam1 == (intptr_t)SwitchRemapCheckWidget[Index1]) {

                     XPSetWidgetProperty(SwitchDisableCheckWidget[Index1], xpProperty_ButtonState, 0);
                     XPSetWidgetProperty(SwitchEnableCheckWidget[Index1], xpProperty_ButtonState, 0);
                     XPSetWidgetProperty(SwitchRemapCheckWidget[Index1], xpProperty_ButtonState, 0);

                     XPSetWidgetProperty((XPWidgetID)inParam1, xpProperty_ButtonState, 1);

            }

           }


            State = XPGetWidgetProperty(SwitchBatAltCheckWidget[0], xpProperty_ButtonState, 0);
            if (State){
                bataltinverse = 0;
            }
            State = XPGetWidgetProperty(SwitchAltBatCheckWidget[0], xpProperty_ButtonState, 0);
            if (State){
                bataltinverse = 1;
           }

            State = XPGetWidgetProperty(SwitchStartSwitchOldCheckWidget[0], xpProperty_ButtonState, 0);
            if (State){
                starterswitchenable = 0;
            }
            State = XPGetWidgetProperty(SwitchStartSwitchNewCheckWidget[0], xpProperty_ButtonState, 0);
            if (State){
                starterswitchenable = 1;
           }

            printf("starterswitchenable %d\n", starterswitchenable);


            State = XPGetWidgetProperty(SwitchDisableCheckWidget[0], xpProperty_ButtonState, 0);
            if (State){
                magoffswitchenable = 0;
            }
            State = XPGetWidgetProperty(SwitchEnableCheckWidget[0], xpProperty_ButtonState, 0);
            if (State){
                magoffswitchenable = 1;
           }
           State = XPGetWidgetProperty(SwitchRemapCheckWidget[0], xpProperty_ButtonState, 0);
           if (State){
               magoffswitchenable = 2;
           }


           State = XPGetWidgetProperty(SwitchDisableCheckWidget[1], xpProperty_ButtonState, 0);
           if (State){
                magrightswitchenable = 0;
           }
           State = XPGetWidgetProperty(SwitchEnableCheckWidget[1], xpProperty_ButtonState, 0);
           if (State){
                magrightswitchenable = 1;
           }
           State = XPGetWidgetProperty(SwitchRemapCheckWidget[1], xpProperty_ButtonState, 0);
           if (State){
               magrightswitchenable = 2;
           }

           State = XPGetWidgetProperty(SwitchDisableCheckWidget[2], xpProperty_ButtonState, 0);
           if (State){
               magleftswitchenable = 0;
           }
           State = XPGetWidgetProperty(SwitchEnableCheckWidget[2], xpProperty_ButtonState, 0);
           if (State){
                magleftswitchenable = 1;
           }
           State = XPGetWidgetProperty(SwitchRemapCheckWidget[2], xpProperty_ButtonState, 0);
           if (State){
               magleftswitchenable = 2;
           }
           State = XPGetWidgetProperty(SwitchDisableCheckWidget[3], xpProperty_ButtonState, 0);
           if (State){
                magbothswitchenable = 0;
           }
           State = XPGetWidgetProperty(SwitchEnableCheckWidget[3], xpProperty_ButtonState, 0);
           if (State){
                magbothswitchenable = 1;
           }
           State = XPGetWidgetProperty(SwitchRemapCheckWidget[3], xpProperty_ButtonState, 0);
           if (State){
               magbothswitchenable = 2;
           }

           State = XPGetWidgetProperty(SwitchDisableCheckWidget[4], xpProperty_ButtonState, 0);
           if (State){
                magstartswitchenable = 0;
           }
           State = XPGetWidgetProperty(SwitchEnableCheckWidget[4], xpProperty_ButtonState, 0);
           if (State){
                magstartswitchenable = 1;
           }
           State = XPGetWidgetProperty(SwitchRemapCheckWidget[4], xpProperty_ButtonState, 0);
           if (State){
               magstartswitchenable = 2;
           }

           State = XPGetWidgetProperty(SwitchDisableCheckWidget[5], xpProperty_ButtonState, 0);
           if (State){
                batmasterswitchenable = 0;
           }
           State = XPGetWidgetProperty(SwitchEnableCheckWidget[5], xpProperty_ButtonState, 0);
           if (State){
                batmasterswitchenable = 1;
           }
           State = XPGetWidgetProperty(SwitchRemapCheckWidget[5], xpProperty_ButtonState, 0);
           if (State){
               batmasterswitchenable = 2;
           }


           State = XPGetWidgetProperty(SwitchDisableCheckWidget[6], xpProperty_ButtonState, 0);
           if (State){
                altmasterswitchenable = 0;
           }
           State = XPGetWidgetProperty(SwitchEnableCheckWidget[6], xpProperty_ButtonState, 0);
           if (State){
                altmasterswitchenable = 1;
           }
           State = XPGetWidgetProperty(SwitchRemapCheckWidget[6], xpProperty_ButtonState, 0);
           if (State){
               altmasterswitchenable = 2;
           }

           State = XPGetWidgetProperty(SwitchDisableCheckWidget[7], xpProperty_ButtonState, 0);
           if (State){
                avionicsmasterswitchenable = 0;
           }
           State = XPGetWidgetProperty(SwitchEnableCheckWidget[7], xpProperty_ButtonState, 0);
           if (State){
                avionicsmasterswitchenable = 1;
           }
           State = XPGetWidgetProperty(SwitchRemapCheckWidget[7], xpProperty_ButtonState, 0);
           if (State){
               avionicsmasterswitchenable = 2;
           }


           State = XPGetWidgetProperty(SwitchDisableCheckWidget[8], xpProperty_ButtonState, 0);
           if (State){
                fuelpumpswitchenable = 0;
           }
           State = XPGetWidgetProperty(SwitchEnableCheckWidget[8], xpProperty_ButtonState, 0);
           if (State){
                fuelpumpswitchenable = 1;
           }
           State = XPGetWidgetProperty(SwitchRemapCheckWidget[8], xpProperty_ButtonState, 0);
           if (State){
               fuelpumpswitchenable = 2;
           }


           State = XPGetWidgetProperty(SwitchDisableCheckWidget[9], xpProperty_ButtonState, 0);
           if (State){
               deiceswitchenable = 0;
           }
           State = XPGetWidgetProperty(SwitchEnableCheckWidget[9], xpProperty_ButtonState, 0);
           if (State){
               deiceswitchenable = 1;
           }
           State = XPGetWidgetProperty(SwitchRemapCheckWidget[9], xpProperty_ButtonState, 0);
           if (State){
              deiceswitchenable = 2;
           }

           State = XPGetWidgetProperty(SwitchDisableCheckWidget[10], xpProperty_ButtonState, 0);
           if (State){
              pitotheatswitchenable = 0;
           }
           State = XPGetWidgetProperty(SwitchEnableCheckWidget[10], xpProperty_ButtonState, 0);
           if (State){
              pitotheatswitchenable = 1;
           }
           State = XPGetWidgetProperty(SwitchRemapCheckWidget[10], xpProperty_ButtonState, 0);
           if (State){
             pitotheatswitchenable = 2;
           }

           State = XPGetWidgetProperty(SwitchDisableCheckWidget[11], xpProperty_ButtonState, 0);
           if (State){
             landinggearknobupenable = 0;
           }
           State = XPGetWidgetProperty(SwitchEnableCheckWidget[11], xpProperty_ButtonState, 0);
           if (State){
             landinggearknobupenable = 1;
           }
           State = XPGetWidgetProperty(SwitchRemapCheckWidget[11], xpProperty_ButtonState, 0);
           if (State){
            landinggearknobupenable = 2;
           }

           State = XPGetWidgetProperty(SwitchDisableCheckWidget[12], xpProperty_ButtonState, 0);
           if (State){
            landinggearknobdnenable = 0;
           }
           State = XPGetWidgetProperty(SwitchEnableCheckWidget[12], xpProperty_ButtonState, 0);
           if (State){
            landinggearknobdnenable = 1;
           }
           State = XPGetWidgetProperty(SwitchRemapCheckWidget[12], xpProperty_ButtonState, 0);
           if (State){
           landinggearknobdnenable = 2;
           }


           State = XPGetWidgetProperty(SwitchDisableCheckWidget[13], xpProperty_ButtonState, 0);
           if (State){
             cowlflapsenable = 0;
           }
           State = XPGetWidgetProperty(SwitchEnableCheckWidget[13], xpProperty_ButtonState, 0);
           if (State){
             cowlflapsenable = 1;
           }
           State = XPGetWidgetProperty(SwitchRemapCheckWidget[13], xpProperty_ButtonState, 0);
           if (State){
            cowlflapsenable = 2;
           }

           State = XPGetWidgetProperty(SwitchDisableCheckWidget[14], xpProperty_ButtonState, 0);
           if (State){
            panellightswitchenable = 0;
           }
           State = XPGetWidgetProperty(SwitchEnableCheckWidget[14], xpProperty_ButtonState, 0);
           if (State){
            panellightswitchenable = 1;
           }
           State = XPGetWidgetProperty(SwitchRemapCheckWidget[14], xpProperty_ButtonState, 0);
           if (State){
             panellightswitchenable = 2;
           }


           State = XPGetWidgetProperty(SwitchDisableCheckWidget[15], xpProperty_ButtonState, 0);
           if (State){
             beaconlightswitchenable = 0;
           }
           State = XPGetWidgetProperty(SwitchEnableCheckWidget[15], xpProperty_ButtonState, 0);
           if (State){
              beaconlightswitchenable = 1;
           }
           State = XPGetWidgetProperty(SwitchRemapCheckWidget[15], xpProperty_ButtonState, 0);
           if (State){
             beaconlightswitchenable = 2;
           }

           State = XPGetWidgetProperty(SwitchDisableCheckWidget[16], xpProperty_ButtonState, 0);
           if (State){
               navlightswitchenable = 0;
           }
           State = XPGetWidgetProperty(SwitchEnableCheckWidget[16], xpProperty_ButtonState, 0);
           if (State){
              navlightswitchenable = 1;
           }
           State = XPGetWidgetProperty(SwitchRemapCheckWidget[16], xpProperty_ButtonState, 0);
           if (State){
               navlightswitchenable = 2;
           }

           State = XPGetWidgetProperty(SwitchDisableCheckWidget[17], xpProperty_ButtonState, 0);
           if (State){
               strobelightswitchenable = 0;
           }
           State = XPGetWidgetProperty(SwitchEnableCheckWidget[17], xpProperty_ButtonState, 0);
           if (State){
              strobelightswitchenable = 1;
           }
           State = XPGetWidgetProperty(SwitchRemapCheckWidget[17], xpProperty_ButtonState, 0);
           if (State){
               strobelightswitchenable = 2;
           }

           State = XPGetWidgetProperty(SwitchDisableCheckWidget[18], xpProperty_ButtonState, 0);
           if (State){
               taxilightswitchenable = 0;
           }
           State = XPGetWidgetProperty(SwitchEnableCheckWidget[18], xpProperty_ButtonState, 0);
           if (State){
                taxilightswitchenable = 1;
           }
           State = XPGetWidgetProperty(SwitchRemapCheckWidget[18], xpProperty_ButtonState, 0);
           if (State){
               taxilightswitchenable = 2;
           }

           State = XPGetWidgetProperty(SwitchDisableCheckWidget[19], xpProperty_ButtonState, 0);
           if (State){
               landinglightswitchenable = 0;
           }
           State = XPGetWidgetProperty(SwitchEnableCheckWidget[19], xpProperty_ButtonState, 0);
           if (State){
               landinglightswitchenable = 1;
           }
           State = XPGetWidgetProperty(SwitchRemapCheckWidget[19], xpProperty_ButtonState, 0);
           if (State){
               landinglightswitchenable = 2;
           }

        return 1;

        }



return 0;
}

// This will create our radio widget dialog.
void CreateRadioWidget(int x, int y, int w, int h)
{
        int x2 = x + w;
        int y2 = y - h;
        int Index;
        int yOffset;

        DataRefID.clear();
        memset(RadioSpeed1CheckWidget, 0, sizeof(RadioSpeed1CheckWidget));
        memset(RadioSpeed2CheckWidget, 0, sizeof(RadioSpeed2CheckWidget));
        memset(RadioSpeed3CheckWidget, 0, sizeof(RadioSpeed3CheckWidget));
        memset(RadioSpeed4CheckWidget, 0, sizeof(RadioSpeed4CheckWidget));
        memset(RadioSpeed5CheckWidget, 0, sizeof(RadioSpeed5CheckWidget));

// Create the Main Widget window.
        RadioWidgetID = XPCreateWidget(x, y, x2, y2,
                                        1,		        	// Visible
                                        "Radio   Panel   Mappings",	// desc
                                        1,				// root
                                        NULL,				// no container
                                        xpWidgetClass_MainWindow);

// Add Close Box to the Main Widget.  Other options are available.  See the SDK Documentation.
        XPSetWidgetProperty(RadioWidgetID, xpProperty_MainWindowHasCloseBoxes, 1);
        XPSetWidgetProperty(RadioWidgetID, xpProperty_MainWindowType, xpMainWindowStyle_Translucent);


// Checkbox for silver knob speed



         yOffset = (05+28+(0*20));
         RadioSpeed1CheckWidget[0] = XPCreateWidget(x+05, y-yOffset, x+05+22, y-yOffset-20,
                                      1,	// Visible
                                      "",       // desc
                                      0,	// root
                                      RadioWidgetID,
                                      xpWidgetClass_Button);

          XPSetWidgetProperty(RadioSpeed1CheckWidget[0], xpProperty_ButtonType, xpRadioButton);
          XPSetWidgetProperty(RadioSpeed1CheckWidget[0], xpProperty_ButtonBehavior, xpButtonBehaviorRadioButton);
          XPSetWidgetProperty(RadioSpeed1CheckWidget[0], xpProperty_ButtonState, 0);

          yOffset = (05+28+(1*20));
          RadioSpeed2CheckWidget[0] = XPCreateWidget(x+05, y-yOffset, x+05+22, y-yOffset-20,
                                       1,	// Visible
                                       "",       // desc
                                       0,	// root
                                       RadioWidgetID,
                                       xpWidgetClass_Button);

           XPSetWidgetProperty(RadioSpeed2CheckWidget[0], xpProperty_ButtonType, xpRadioButton);
           XPSetWidgetProperty(RadioSpeed2CheckWidget[0], xpProperty_ButtonBehavior, xpButtonBehaviorRadioButton);
           XPSetWidgetProperty(RadioSpeed2CheckWidget[0], xpProperty_ButtonState, 0);


           yOffset = (05+28+(2*20));
           RadioSpeed3CheckWidget[0] = XPCreateWidget(x+05, y-yOffset, x+05+22, y-yOffset-20,
                                        1,	// Visible
                                        "",       // desc
                                        0,	// root
                                        RadioWidgetID,
                                        xpWidgetClass_Button);

            XPSetWidgetProperty(RadioSpeed3CheckWidget[0], xpProperty_ButtonType, xpRadioButton);
            XPSetWidgetProperty(RadioSpeed3CheckWidget[0], xpProperty_ButtonBehavior, xpButtonBehaviorRadioButton);
            XPSetWidgetProperty(RadioSpeed3CheckWidget[0], xpProperty_ButtonState, 0);

            yOffset = (05+28+(3*20));
            RadioSpeed4CheckWidget[0] = XPCreateWidget(x+05, y-yOffset, x+05+22, y-yOffset-20,
                                         1,	// Visible
                                         "",       // desc
                                         0,	// root
                                         RadioWidgetID,
                                         xpWidgetClass_Button);

             XPSetWidgetProperty(RadioSpeed4CheckWidget[0], xpProperty_ButtonType, xpRadioButton);
             XPSetWidgetProperty(RadioSpeed4CheckWidget[0], xpProperty_ButtonBehavior, xpButtonBehaviorRadioButton);
             XPSetWidgetProperty(RadioSpeed4CheckWidget[0], xpProperty_ButtonState, 0);

             yOffset = (05+28+(4*20));
             RadioSpeed5CheckWidget[0] = XPCreateWidget(x+05, y-yOffset, x+05+22, y-yOffset-20,
                                          1,	// Visible
                                          "",       // desc
                                          0,	// root
                                          RadioWidgetID,
                                          xpWidgetClass_Button);

              XPSetWidgetProperty(RadioSpeed5CheckWidget[0], xpProperty_ButtonType, xpRadioButton);
              XPSetWidgetProperty(RadioSpeed5CheckWidget[0], xpProperty_ButtonBehavior, xpButtonBehaviorRadioButton);
              XPSetWidgetProperty(RadioSpeed5CheckWidget[0], xpProperty_ButtonState, 0);


// Create a text widget

        for (Index=0; Index < 50; Index++)
        {
             if(strcmp(RadioSpeedText[Index],"end") == 0) {break;}

         yOffset = (05+28+(Index*20));
         RadioSpeedTextWidget[Index] = XPCreateWidget(x+50, y-yOffset, x+50+170, y-yOffset-20,
                          1,	// Visible
                          RadioSpeedText[Index],// desc
                          0,		// root
                          RadioWidgetID,
                          xpWidgetClass_Caption);
         XPSetWidgetProperty(RadioSpeedTextWidget[Index], xpProperty_CaptionLit, 1);


         }


// Checkbox for adf tuner



          yOffset = (05+28+(6*20));
          RadioAdf1CheckWidget[0] = XPCreateWidget(x+05, y-yOffset, x+05+22, y-yOffset-20,
                          1,	// Visible
                          "",       // desc
                          0,	// root
                          RadioWidgetID,
                          xpWidgetClass_Button);

          XPSetWidgetProperty(RadioAdf1CheckWidget[0], xpProperty_ButtonType, xpRadioButton);
          XPSetWidgetProperty(RadioAdf1CheckWidget[0], xpProperty_ButtonBehavior, xpButtonBehaviorRadioButton);
          XPSetWidgetProperty(RadioAdf1CheckWidget[0], xpProperty_ButtonState, 0);

          yOffset = (05+28+(7*20));
          RadioAdf2CheckWidget[0] = XPCreateWidget(x+05, y-yOffset, x+05+22, y-yOffset-20,
                            1,	// Visible
                            "",       // desc
                            0,	// root
                            RadioWidgetID,
                            xpWidgetClass_Button);

          XPSetWidgetProperty(RadioAdf2CheckWidget[0], xpProperty_ButtonType, xpRadioButton);
          XPSetWidgetProperty(RadioAdf2CheckWidget[0], xpProperty_ButtonBehavior, xpButtonBehaviorRadioButton);
          XPSetWidgetProperty(RadioAdf2CheckWidget[0], xpProperty_ButtonState, 0);


          yOffset = (05+28+(6*20));
          RadioAdf1TextWidget[0] = XPCreateWidget(x+50, y-yOffset, x+50+22, y-yOffset-20,
                          1,	// Visible
                          "ONE ADF TUNER",       // desc
                           0,	// root
                           RadioWidgetID,
                           xpWidgetClass_Caption);

          XPSetWidgetProperty(RadioAdf1TextWidget[0], xpProperty_CaptionLit, 1);

          yOffset = (05+28+(7*20));
          RadioAdf2TextWidget[0] = XPCreateWidget(x+50, y-yOffset, x+50+22, y-yOffset-20,
                          1,	// Visible
                          "TWO ADF TUNERS",       // desc
                          0,	// root
                          RadioWidgetID,
                          xpWidgetClass_Caption);

          XPSetWidgetProperty(RadioAdf2TextWidget[0], xpProperty_CaptionLit, 1);




// Checkbox for QNH



          yOffset = (05+28+(9*20));
          RadioQnh0CheckWidget[0] = XPCreateWidget(x+05, y-yOffset, x+05+22, y-yOffset-20,
                           1,	// Visible
                           "",       // desc
                           0,	// root
                           RadioWidgetID,
                           xpWidgetClass_Button);

          XPSetWidgetProperty(RadioQnh0CheckWidget[0], xpProperty_ButtonType, xpRadioButton);
          XPSetWidgetProperty(RadioQnh0CheckWidget[0], xpProperty_ButtonBehavior, xpButtonBehaviorRadioButton);
          XPSetWidgetProperty(RadioQnh0CheckWidget[0], xpProperty_ButtonState, 0);

          yOffset = (05+28+(10*20));
          RadioQnh1CheckWidget[0] = XPCreateWidget(x+05, y-yOffset, x+05+22, y-yOffset-20,
                           1,	// Visible
                           "",       // desc
                           0,	// root
                           RadioWidgetID,
                           xpWidgetClass_Button);

          XPSetWidgetProperty(RadioQnh1CheckWidget[0], xpProperty_ButtonType, xpRadioButton);
          XPSetWidgetProperty(RadioQnh1CheckWidget[0], xpProperty_ButtonBehavior, xpButtonBehaviorRadioButton);
          XPSetWidgetProperty(RadioQnh1CheckWidget[0], xpProperty_ButtonState, 0);


          yOffset = (05+28+(9*20));
          RadioQnh0TextWidget[0] = XPCreateWidget(x+50, y-yOffset, x+50+22, y-yOffset-20,
                          1,	// Visible
                          "QNH display inHg",       // desc
                          0,	// root
                          RadioWidgetID,
                          xpWidgetClass_Caption);

          XPSetWidgetProperty(RadioQnh0TextWidget[0], xpProperty_CaptionLit, 1);

          yOffset = (05+28+(10*20));
          RadioQnh1TextWidget[0] = XPCreateWidget(x+50, y-yOffset, x+50+22, y-yOffset-20,
                          1,	// Visible
                          "QNH display hPa",       // desc
                          0,	// root
                          RadioWidgetID,
                          xpWidgetClass_Caption);

         XPSetWidgetProperty(RadioQnh1TextWidget[0], xpProperty_CaptionLit, 1);


// Register our widget handler
        XPAddWidgetCallback(RadioWidgetID, RadioHandler);
        process_read_ini_file();


}

// This is our widget handler.  In this example we are only interested when the close box is pressed.
int	RadioHandler(XPWidgetMessage  RadioinMessage, XPWidgetID  RadioWidgetID, intptr_t  inParam1, intptr_t  inParam2)
{
        (void) inParam2;
        int State; //, State1, State2;
        //int Index1;
        if (RadioinMessage == xpMessage_CloseButtonPushed)
        {
                if (radioMenuItem == 1)
                {
                        XPHideWidget(RadioWidgetID);
                }
                return 1;
        }

        if(RadioinMessage == xpMsg_ButtonStateChanged)
        {



            if(inParam1 == (intptr_t)RadioSpeed1CheckWidget[0] ||
               inParam1 == (intptr_t)RadioSpeed2CheckWidget[0] ||
               inParam1 == (intptr_t)RadioSpeed3CheckWidget[0] ||
               inParam1 == (intptr_t)RadioSpeed4CheckWidget[0] ||
               inParam1 == (intptr_t)RadioSpeed5CheckWidget[0]) {



                     XPSetWidgetProperty(RadioSpeed1CheckWidget[0], xpProperty_ButtonState, 0);
                     XPSetWidgetProperty(RadioSpeed2CheckWidget[0], xpProperty_ButtonState, 0);
                     XPSetWidgetProperty(RadioSpeed3CheckWidget[0], xpProperty_ButtonState, 0);
                     XPSetWidgetProperty(RadioSpeed4CheckWidget[0], xpProperty_ButtonState, 0);
                     XPSetWidgetProperty(RadioSpeed5CheckWidget[0], xpProperty_ButtonState, 0);


                     XPSetWidgetProperty((XPWidgetID)inParam1, xpProperty_ButtonState, 1);

            }

            State = XPGetWidgetProperty(RadioSpeed1CheckWidget[0], xpProperty_ButtonState, 0);
            if (State){
                radspeed = 1;
            }
            State = XPGetWidgetProperty(RadioSpeed2CheckWidget[0], xpProperty_ButtonState, 0);
            if (State){
                radspeed = 2;
            }
            State = XPGetWidgetProperty(RadioSpeed3CheckWidget[0], xpProperty_ButtonState, 0);
            if (State){
                radspeed = 3;
            }
            State = XPGetWidgetProperty(RadioSpeed4CheckWidget[0], xpProperty_ButtonState, 0);
            if (State){
                radspeed = 4;
            }
            State = XPGetWidgetProperty(RadioSpeed5CheckWidget[0], xpProperty_ButtonState, 0);
            if (State){
                radspeed = 5;
            }


            if(inParam1 == (intptr_t)RadioAdf1CheckWidget[0] ||
               inParam1 == (intptr_t)RadioAdf2CheckWidget[0] ) {

                     XPSetWidgetProperty(RadioAdf1CheckWidget[0], xpProperty_ButtonState, 0);
                     XPSetWidgetProperty(RadioAdf2CheckWidget[0], xpProperty_ButtonState, 0);

                     XPSetWidgetProperty((XPWidgetID)inParam1, xpProperty_ButtonState, 1);

            State = XPGetWidgetProperty(RadioAdf1CheckWidget[0], xpProperty_ButtonState, 0);
            if (State){
                numadf = 1;
            }

            State = XPGetWidgetProperty(RadioAdf2CheckWidget[0], xpProperty_ButtonState, 0);
            if (State){
                numadf = 2;
            }
         }



            if(inParam1 == (intptr_t)RadioQnh0CheckWidget[0] ||
               inParam1 == (intptr_t)RadioQnh1CheckWidget[0] ) {

                     XPSetWidgetProperty(RadioQnh0CheckWidget[0], xpProperty_ButtonState, 0);
                     XPSetWidgetProperty(RadioQnh1CheckWidget[0], xpProperty_ButtonState, 0);

                     XPSetWidgetProperty((XPWidgetID)inParam1, xpProperty_ButtonState, 1);

            State = XPGetWidgetProperty(RadioQnh0CheckWidget[0], xpProperty_ButtonState, 0);
            if (State){
                metricpressenable = 0;
            }

            State = XPGetWidgetProperty(RadioQnh1CheckWidget[0], xpProperty_ButtonState, 0);
            if (State){
                metricpressenable = 1;
            }
         }


         return 1;
    }


  return 0 ;
}


// This will create our multi widget dialog.
void CreateMultiWidget(int x, int y, int w, int h)
{
        int x2 = x + w;
        int y2 = y - h;
        int Index;
        int yOffset;

        DataRefID.clear();
        memset(MultiSpeed1CheckWidget, 0, sizeof(MultiSpeed1CheckWidget));
        memset(MultiSpeed2CheckWidget, 0, sizeof(MultiSpeed2CheckWidget));
        memset(MultiSpeed3CheckWidget, 0, sizeof(MultiSpeed3CheckWidget));
        memset(MultiSpeed4CheckWidget, 0, sizeof(MultiSpeed4CheckWidget));
        memset(MultiSpeed5CheckWidget, 0, sizeof(MultiSpeed5CheckWidget));

// Create the Main Widget window.
        MultiWidgetID = XPCreateWidget(x, y, x2, y2,
                                        1,		        	// Visible
                                        "Multi   Panel   Mappings",	// desc
                                        1,				// root
                                        NULL,				// no container
                                        xpWidgetClass_MainWindow);

// Add Close Box to the Main Widget.  Other options are available.  See the SDK Documentation.
        XPSetWidgetProperty(MultiWidgetID, xpProperty_MainWindowHasCloseBoxes, 1);
        XPSetWidgetProperty(MultiWidgetID, xpProperty_MainWindowType, xpMainWindowStyle_Translucent);


 // Checkbox for silver knob speed



        yOffset = (05+28+(0*20));
        MultiSpeed1CheckWidget[0] = XPCreateWidget(x+05, y-yOffset, x+05+22, y-yOffset-20,
                           1,	// Visible
                           "",       // desc
                           0,	// root
                           MultiWidgetID,
                           xpWidgetClass_Button);

        XPSetWidgetProperty(MultiSpeed1CheckWidget[0], xpProperty_ButtonType, xpRadioButton);
        XPSetWidgetProperty(MultiSpeed1CheckWidget[0], xpProperty_ButtonBehavior, xpButtonBehaviorRadioButton);
        XPSetWidgetProperty(MultiSpeed1CheckWidget[0], xpProperty_ButtonState, 0);

        yOffset = (05+28+(1*20));
        MultiSpeed2CheckWidget[0] = XPCreateWidget(x+05, y-yOffset, x+05+22, y-yOffset-20,
                           1,	// Visible
                           "",       // desc
                           0,	// root
                           MultiWidgetID,
                           xpWidgetClass_Button);

        XPSetWidgetProperty(MultiSpeed2CheckWidget[0], xpProperty_ButtonType, xpRadioButton);
        XPSetWidgetProperty(MultiSpeed2CheckWidget[0], xpProperty_ButtonBehavior, xpButtonBehaviorRadioButton);
        XPSetWidgetProperty(MultiSpeed2CheckWidget[0], xpProperty_ButtonState, 0);


        yOffset = (05+28+(2*20));
        MultiSpeed3CheckWidget[0] = XPCreateWidget(x+05, y-yOffset, x+05+22, y-yOffset-20,
                           1,	// Visible
                           "",       // desc
                           0,	// root
                           MultiWidgetID,
                           xpWidgetClass_Button);

        XPSetWidgetProperty(MultiSpeed3CheckWidget[0], xpProperty_ButtonType, xpRadioButton);
        XPSetWidgetProperty(MultiSpeed3CheckWidget[0], xpProperty_ButtonBehavior, xpButtonBehaviorRadioButton);
        XPSetWidgetProperty(MultiSpeed3CheckWidget[0], xpProperty_ButtonState, 0);

        yOffset = (05+28+(3*20));
        MultiSpeed4CheckWidget[0] = XPCreateWidget(x+05, y-yOffset, x+05+22, y-yOffset-20,
                           1,	// Visible
                           "",       // desc
                           0,	// root
                           MultiWidgetID,
                           xpWidgetClass_Button);

        XPSetWidgetProperty(MultiSpeed4CheckWidget[0], xpProperty_ButtonType, xpRadioButton);
        XPSetWidgetProperty(MultiSpeed4CheckWidget[0], xpProperty_ButtonBehavior, xpButtonBehaviorRadioButton);
        XPSetWidgetProperty(MultiSpeed4CheckWidget[0], xpProperty_ButtonState, 0);

        yOffset = (05+28+(4*20));
        MultiSpeed5CheckWidget[0] = XPCreateWidget(x+05, y-yOffset, x+05+22, y-yOffset-20,
                           1,	// Visible
                           "",       // desc
                           0,	// root
                           MultiWidgetID,
                           xpWidgetClass_Button);

        XPSetWidgetProperty(MultiSpeed5CheckWidget[0], xpProperty_ButtonType, xpRadioButton);
        XPSetWidgetProperty(MultiSpeed5CheckWidget[0], xpProperty_ButtonBehavior, xpButtonBehaviorRadioButton);
        XPSetWidgetProperty(MultiSpeed5CheckWidget[0], xpProperty_ButtonState, 0);


// Create a text widget

        for (Index=0; Index < 50; Index++)
        {
             if(strcmp(MultiSpeedText[Index],"end") == 0) {break;}

                 yOffset = (05+28+(Index*20));
                 MultiSpeedTextWidget[Index] = XPCreateWidget(x+50, y-yOffset, x+50+170, y-yOffset-20,
                                  1,	// Visible
                                  MultiSpeedText[Index],// desc
                                  0,		// root
                                  MultiWidgetID,
                                  xpWidgetClass_Caption);
                 XPSetWidgetProperty(MultiSpeedTextWidget[Index], xpProperty_CaptionLit, 1);
        }

//  // Checkbox for trim speed

        yOffset = (05+28+(6*20));
        MultiTrimSpeed1CheckWidget[0] = XPCreateWidget(x+05, y-yOffset, x+05+22, y-yOffset-20,
                           1,	// Visible
                           "",       // desc
                           0,	// root
                           MultiWidgetID,
                           xpWidgetClass_Button);

        XPSetWidgetProperty(MultiTrimSpeed1CheckWidget[0], xpProperty_ButtonType, xpRadioButton);
        XPSetWidgetProperty(MultiTrimSpeed1CheckWidget[0], xpProperty_ButtonBehavior, xpButtonBehaviorRadioButton);
        XPSetWidgetProperty(MultiTrimSpeed1CheckWidget[0], xpProperty_ButtonState, 0);


        yOffset = (05+28+(7*20));
        MultiTrimSpeed2CheckWidget[0] = XPCreateWidget(x+05, y-yOffset, x+05+22, y-yOffset-20,
                           1,	// Visible
                           "",       // desc
                           0,	// root
                           MultiWidgetID,
                           xpWidgetClass_Button);

        XPSetWidgetProperty(MultiTrimSpeed2CheckWidget[0], xpProperty_ButtonType, xpRadioButton);
        XPSetWidgetProperty(MultiTrimSpeed2CheckWidget[0], xpProperty_ButtonBehavior, xpButtonBehaviorRadioButton);
        XPSetWidgetProperty(MultiTrimSpeed2CheckWidget[0], xpProperty_ButtonState, 0);

        yOffset = (05+28+(8*20));
        MultiTrimSpeed3CheckWidget[0] = XPCreateWidget(x+05, y-yOffset, x+05+22, y-yOffset-20,
                           1,	// Visible
                           "",       // desc
                           0,	// root
                           MultiWidgetID,
                           xpWidgetClass_Button);

        XPSetWidgetProperty(MultiTrimSpeed3CheckWidget[0], xpProperty_ButtonType, xpRadioButton);
        XPSetWidgetProperty(MultiTrimSpeed3CheckWidget[0], xpProperty_ButtonBehavior, xpButtonBehaviorRadioButton);
        XPSetWidgetProperty(MultiTrimSpeed3CheckWidget[0], xpProperty_ButtonState, 0);


 // Create a text widget

        for (Index=0; Index < 50; Index++)
        {
             if(strcmp(MultiTrimSpeedText[Index],"end") == 0) {break;}

                 yOffset = (05+28+((Index+6)*20));
                 MultiTrimSpeedTextWidget[Index] = XPCreateWidget(x+50, y-yOffset, x+50+170, y-yOffset-20,
                                  1,	// Visible
                                  MultiTrimSpeedText[Index],// desc
                                  0,		// root
                                  MultiWidgetID,
                                  xpWidgetClass_Caption);
                 XPSetWidgetProperty(MultiTrimSpeedTextWidget[Index], xpProperty_CaptionLit, 1);
        }

// Auto Throttle Widget

        yOffset = (05+28+(10*20));
        MultiAt0CheckWidget[0] = XPCreateWidget(x+05, y-yOffset, x+05+22, y-yOffset-20,
                         1,	// Visible
                         "",       // desc
                         0,	// root
                         MultiWidgetID,
                         xpWidgetClass_Button);

        XPSetWidgetProperty(MultiAt0CheckWidget[0], xpProperty_ButtonType, xpRadioButton);
        XPSetWidgetProperty(MultiAt0CheckWidget[0], xpProperty_ButtonBehavior, xpButtonBehaviorRadioButton);
        XPSetWidgetProperty(MultiAt0CheckWidget[0], xpProperty_ButtonState, 0);


        yOffset = (05+28+(11*20));
        MultiAt1CheckWidget[0] = XPCreateWidget(x+05, y-yOffset, x+05+22, y-yOffset-20,
                         1,	// Visible
                         "",       // desc
                         0,	// root
                         MultiWidgetID,
                         xpWidgetClass_Button);

        XPSetWidgetProperty(MultiAt1CheckWidget[0], xpProperty_ButtonType, xpRadioButton);
        XPSetWidgetProperty(MultiAt1CheckWidget[0], xpProperty_ButtonBehavior, xpButtonBehaviorRadioButton);
        XPSetWidgetProperty(MultiAt1CheckWidget[0], xpProperty_ButtonState, 0);

        yOffset = (05+28+(10*20));
        MultiAt0TextWidget[0] = XPCreateWidget(x+50, y-yOffset, x+50+22, y-yOffset-20,
                        1,	// Visible
                        "DISABLE_AUTO_THROTTLE SWITCH",       // desc
                         0,	// root
                         MultiWidgetID,
                         xpWidgetClass_Caption);

        XPSetWidgetProperty(MultiAt0TextWidget[0], xpProperty_CaptionLit, 1);

        yOffset = (05+28+(11*20));
        MultiAt1TextWidget[0] = XPCreateWidget(x+50, y-yOffset, x+50+22, y-yOffset-20,
                        1,	// Visible
                        "ENABLE_AUTO_THROTTLE SWITCH",       // desc
                         0,	// root
                         MultiWidgetID,
                         xpWidgetClass_Caption);

        XPSetWidgetProperty(MultiAt1TextWidget[0], xpProperty_CaptionLit, 1);


// Register our widget handler
             XPAddWidgetCallback(MultiWidgetID, MultiHandler);
             process_read_ini_file();




}


// This is our widget handler.  In this example we are only interested when the close box is pressed.
int	MultiHandler(XPWidgetMessage  MultiinMessage, XPWidgetID  MultiWidgetID, intptr_t  inParam1, intptr_t  inParam2)
{
        (void) inParam2;
        int State;
        if (MultiinMessage == xpMessage_CloseButtonPushed)
        {
                if (multiMenuItem == 1)
                {
                        XPHideWidget(MultiWidgetID);
                }
                return 1;
        }

        if(MultiinMessage == xpMsg_ButtonStateChanged)
        {



            if(inParam1 == (intptr_t)MultiSpeed1CheckWidget[0] ||
               inParam1 == (intptr_t)MultiSpeed2CheckWidget[0] ||
               inParam1 == (intptr_t)MultiSpeed3CheckWidget[0] ||
               inParam1 == (intptr_t)MultiSpeed4CheckWidget[0] ||
               inParam1 == (intptr_t)MultiSpeed5CheckWidget[0]) {



                     XPSetWidgetProperty(MultiSpeed1CheckWidget[0], xpProperty_ButtonState, 0);
                     XPSetWidgetProperty(MultiSpeed2CheckWidget[0], xpProperty_ButtonState, 0);
                     XPSetWidgetProperty(MultiSpeed3CheckWidget[0], xpProperty_ButtonState, 0);
                     XPSetWidgetProperty(MultiSpeed4CheckWidget[0], xpProperty_ButtonState, 0);
                     XPSetWidgetProperty(MultiSpeed5CheckWidget[0], xpProperty_ButtonState, 0);


                     XPSetWidgetProperty((XPWidgetID)inParam1, xpProperty_ButtonState, 1);

            }

            State = XPGetWidgetProperty(MultiSpeed1CheckWidget[0], xpProperty_ButtonState, 0);
            if (State){
                multispeed = 1;
            }
            State = XPGetWidgetProperty(MultiSpeed2CheckWidget[0], xpProperty_ButtonState, 0);
            if (State){
                multispeed = 2;
            }
            State = XPGetWidgetProperty(MultiSpeed3CheckWidget[0], xpProperty_ButtonState, 0);
            if (State){
                multispeed = 3;
            }
            State = XPGetWidgetProperty(MultiSpeed4CheckWidget[0], xpProperty_ButtonState, 0);
            if (State){
                multispeed = 4;
            }
            State = XPGetWidgetProperty(MultiSpeed5CheckWidget[0], xpProperty_ButtonState, 0);
            if (State){
                multispeed = 5;
            }


            if(inParam1 == (intptr_t)MultiTrimSpeed1CheckWidget[0] ||
               inParam1 == (intptr_t)MultiTrimSpeed2CheckWidget[0] ||
               inParam1 == (intptr_t)MultiTrimSpeed3CheckWidget[0] ) {

                     XPSetWidgetProperty(MultiTrimSpeed1CheckWidget[0], xpProperty_ButtonState, 0);
                     XPSetWidgetProperty(MultiTrimSpeed2CheckWidget[0], xpProperty_ButtonState, 0);
                     XPSetWidgetProperty(MultiTrimSpeed3CheckWidget[0], xpProperty_ButtonState, 0);

                     XPSetWidgetProperty((XPWidgetID)inParam1, xpProperty_ButtonState, 1);

            State = XPGetWidgetProperty(MultiTrimSpeed1CheckWidget[0], xpProperty_ButtonState, 0);
            if (State){
                trimspeed = 1;
            }

            State = XPGetWidgetProperty(MultiTrimSpeed2CheckWidget[0], xpProperty_ButtonState, 0);
            if (State){
                trimspeed = 2;
            }
            State = XPGetWidgetProperty(MultiTrimSpeed3CheckWidget[0], xpProperty_ButtonState, 0);
            if (State){
                trimspeed = 3;
            }

         }





            if(inParam1 == (intptr_t)MultiAt0CheckWidget[0] ||
               inParam1 == (intptr_t)MultiAt1CheckWidget[0] ) {

                     XPSetWidgetProperty(MultiAt0CheckWidget[0], xpProperty_ButtonState, 0);
                     XPSetWidgetProperty(MultiAt1CheckWidget[0], xpProperty_ButtonState, 0);

                     XPSetWidgetProperty((XPWidgetID)inParam1, xpProperty_ButtonState, 1);

            State = XPGetWidgetProperty(MultiAt0CheckWidget[0], xpProperty_ButtonState, 0);
            if (State){
                autothrottleswitchenable = 0;
            }

            State = XPGetWidgetProperty(MultiAt1CheckWidget[0], xpProperty_ButtonState, 0);
            if (State){
                autothrottleswitchenable = 1;
            }
         }


         return 1;
    }


  return 0 ;
}



int    XpanelsFnButtonCommandHandler(XPLMCommandRef       inCommand,
                        XPLMCommandPhase     inPhase,
                        void *               inRefcon)
{
    (void) inCommand;
    (void) inRefcon;
//  If inPhase == 1 the command is executed continuously.
     if (inPhase == 1)
   {
          xpanelsfnbutton = 1;
    }
     if (inPhase == 2)
   {
          xpanelsfnbutton = 0;
    }

return 0;
}

// ************************* Panels Callback  *************************
float	MyPanelsFlightLoopCallback(
                                   float                inElapsedSinceLastCall,    
                                   float                inElapsedTimeSinceLastFlightLoop,    
                                   int                  inCounter,    
                                   void *               inRefcon)

{
    (void) inElapsedSinceLastCall; // To get rid of warnings on unused variables
    (void) inElapsedTimeSinceLastFlightLoop; // To get rid of warnings on unused variables
    (void) inCounter; // To get rid of warnings on unused variables
    (void) inRefcon; // To get rid of warnings on unused variables

  if(radcnt > 0){
    process_radio_panel();
  }

  if (multicnt > 0) {
        process_multi_panel();
  }


  if(switchcnt > 0){
    process_switch_panel();
  }

  if(bipcnt > 0){
    process_bip_panel();

  }

  if (readiniloop < 50) {
      readiniloop++;
  } else if (readiniloop == 50) {
      process_read_ini_file();
      readiniloop = 51;
  }



  return interval;
}
