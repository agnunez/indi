/*
    LX200 OnStep
    based on LX200 Classic azwing (alain@zwingelstein.org)
    Copyright (C) 2003 Jasem Mutlaq (mutlaqja@ikarustech.com)

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

*/

#pragma once

#include "lx200generic.h"
#include "lx200driver.h"
#include "indicom.h"

#include <cstring>
#include <unistd.h>
#include <termios.h>

#define setParkOnStep(fd)  write(fd, "#:hQ#", 5)
#define ReticPlus(fd)      write(fd, "#:B+#", 5)
#define ReticMoins(fd)     write(fd, "#:B-#", 5)
#define OnStepalign1(fd)   write(fd, "#:A1#", 5)
#define OnStepalign2(fd)   write(fd, "#:A2#", 5)
#define OnStepalign3(fd)   write(fd, "#:A3#", 5)

enum Errors {ERR_NONE, ERR_MOTOR_FAULT, ERR_ALT, ERR_LIMIT_SENSE, ERR_DEC, ERR_AZM, ERR_UNDER_POLE, ERR_MERIDIAN, ERR_SYNC};

class LX200_OnStep : public LX200Generic
{
  public:
    LX200_OnStep();
    ~LX200_OnStep() {}

    virtual const char *getDefaultName() override;
    virtual bool initProperties() override;
    virtual void ISGetProperties(const char *dev) override;
    virtual bool updateProperties() override;
    virtual bool ISNewNumber(const char *dev, const char *name, double values[], char *names[], int n) override;
    virtual bool ISNewSwitch(const char *dev, const char *name, ISState *states, char *names[], int n) override;

  protected:
    virtual void getBasicData() override;
    virtual bool Park() override;
    virtual bool UnPark() override;
    virtual bool SetCurrentPark() override;
    virtual bool SetDefaultPark() override;
    virtual bool SetTrackEnabled(bool enabled) override;
    virtual bool updateLocation(double latitude, double longitude, double elevation) override;
    virtual bool setLocalDate(uint8_t days, uint8_t months, uint16_t years) override;
    virtual bool ReadScopeStatus() override;

    bool sendOnStepCommand(const char *cmd);
    bool sendOnStepCommandBlind(const char *cmd);
    int  setMaxElevationLimit(int fd, int max);

    ITextVectorProperty ObjectInfoTP;
    IText ObjectInfoT[1];

    ISwitchVectorProperty StarCatalogSP;
    ISwitch StarCatalogS[3];

    ISwitchVectorProperty DeepSkyCatalogSP;
    ISwitch DeepSkyCatalogS[7];

    ISwitchVectorProperty SolarSP;
    ISwitch SolarS[10];

    INumberVectorProperty ObjectNoNP;
    INumber ObjectNoN[1];

    INumberVectorProperty MaxSlewRateNP;
    INumber MaxSlewRateN[2];

    INumberVectorProperty BacklashNP;    //test
    INumber BacklashN[2];    //Test

    INumberVectorProperty ElevationLimitNP;
    INumber ElevationLimitN[2];

    ITextVectorProperty VersionTP;
    IText VersionT[5];

    ITextVectorProperty OnstepStatTP;
    IText OnstepStat[10];

    int IsTracking = 0;

    // Reticle +/- Buttons
    ISwitchVectorProperty ReticSP;
    ISwitch ReticS[2];

    // Align Buttons
    ISwitchVectorProperty OSAlignSP;
    ISwitch OSAlignS[3];
    IText OSAlignT[20];
    ITextVectorProperty OSAlignTP;

    ISwitchVectorProperty TrackCompSP;
    ISwitch TrackCompS[3];

    ISwitchVectorProperty SetHomeSP;
    ISwitch SetHomeS[2];

    char OSStat[20];
    char OldOSStat[20];

    char OSPier[2];
    char OldOSPier[2];

  private:
    int currentCatalog;
    int currentSubCatalog;
};
