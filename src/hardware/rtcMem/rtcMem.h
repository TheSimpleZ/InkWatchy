#pragma once

#include "defines.h"

struct rtcMem
{
    // Battery
    batteryInfo bat;
    bool isBatterySaving : 1;
#if ATCHY_VER == YATCHY
    bool previousStatInStateBefore : 1;
    bool previousStatInStateAfter : 1;
    bool previousFiveVolt : 1;
#endif
    // Accelerometer
#if ACC_ENABLED
    StableBMA SBMA; // Class
    bool initedAcc : 1;
    uint8_t initAccTries : 4; // Max 15
    bool stepsInited : 1;
    uint8_t stepDay; // For steps to reset each days
#endif
    // Display
    GxEPD2_BW<GxEPD2_154_D67, GxEPD2_154_D67::HEIGHT> display;
    uint8_t updateCounter;
// Mcp23018
#if ATCHY_VER == YATCHY
    mcp23018 gpioExpander;
#endif
    // RTC
    SmallRTC SRTC;
    char posixTimeZone[POSIX_TIMEZONE_MAX_LENGTH];
    // Temp
#if TEMP_CHECKS_ENABLED
    uint8_t fixCounts;
    float initialTemp;
    float previousTemp;
#endif
    // Wifi logic
    uint64_t lastSyncUnix;
    uint64_t lastTryUnix;
// Ntp
// Time drift correction
#if TIME_DRIFT_CORRECTION
    uint64_t driftStartUnix;
#endif
// Watchdog
#if WATCHDOG_TASK
    bool everythingIsFine : 1;
#endif
    // Power settings
    bool disableAllVibration : 1;
    bool disableWakeUp : 1;
    bool userDisableAllVibration : 1;
    bool userDisableWakeUp : 1;
    // Manager
    UiPlace placeTree[PLACE_TREE_MAX_DEPTH];
    UiPlace currentPlace;
    // wManageOne
    tmElements_t wFTime;
    bool disableSomeDrawing : 1;
    uint8_t batteryPercantageWF : 7;
    // wManageAll
    uint8_t watchfaceSelected;
// Inkfield watchface
#if WATCHFACE_INKFIELD_SZYBET
    struct
    {
        uint8_t dayBar;
        uint8_t percentOfDay;
#if ACC_ENABLED
        uint8_t percentSteps;
#else
        uint8_t showedTemp;
#endif
        uint16_t weatherMinutes;
        // inkput
        int watchfacePos; // It needs to be int because it's used in checkMinMax
        bool positionEngaged : 1;
    } inkfield;
#endif
// Shades watchface
#if WATCHFACE_SHADES_SZYBET
    struct
    {
        uint16_t stepsSaved;
    } shades;
#endif
// slate watchface
#if WATCHFACE_SLATE
    struct
    {
        bool weatherAvailable : 1;
        uint8_t lastHourWeatherCheck;
        uint8_t lastBatteryLevel;
        uint8_t lastDay;
        uint8_t lastMonth;
        char lastTemp[12];          // For temperature string like "-15°C" (max ~11 chars + null)
        char lastCondition[32];     // For weather condition strings (max ~31 chars + null)
    } slate;
#endif
// taychron watchface
#if WATCHFACE_TAYCHRON
    struct
    {
        uint8_t dayBar;
        uint16_t weatherMinutes;
        uint8_t Hours;
    } taychron;
#endif
    // Watchface modules
    uint64_t latestModuleUpdate;
    int currentModule; // Int because checkMinMax again
    int8_t previousModuleCount;
    int8_t previousCurrentModule;
// wFApi
#if API_MODULE
    wfModule wfApi;
#endif
    // wFBit
    wfModule wfBit;
    bool isBtcDataAvail : 1;
    bool isBtcDataNew : 1;
    bool smallBtcData : 1;
    uint btcLastUpdate;
// wFBook
#if BOOK_MODULE_ENABLED
    wfModule wfBook;
#endif
// wFConway
#if CONWAY_MODULE_ENABLED
    wfModule wfConway;
    uint8_t timeChangeCheck;
    uint8_t conwayModuleGrid[CONWAY_MODULE_WIDTH / 8 * CONWAY_MODULE_HEIGHT];
#endif
// wFEvent
#if EVENT_MODULE
    wfModule wfEvent;
    int64_t currentEventTime;
    int8_t currentDay;
#endif
// wFImg
#if IMAGE_MODULE
    wfModule wfImage;
#if IMG_MODULE_CHANGE_EVERY_HOUR
    int8_t imageCurrentHour;
#endif
    uint32_t imageNameCrc32;
#endif
// wFNet
#if WIFI_MODULE
    wfModule wfNet;
#endif
// wFAlarm
#if ALARM_MODULE && INK_ALARMS
    wfModule wfAlarm;
    int8_t wfAlarmMinutes;
    int8_t wfAlarmHours;
#endif
// Alarms
#if INK_ALARMS
    inkAlarm alarms[MAX_ALARMS];
    uint64_t nextAlarm;
    int8_t nextAlarmIndex;
#if POMODORO_ALARM
    uint8_t pomodoroIter : 4;
    bool pomodoroWorkNow : 1;
#endif
#endif
};

extern rtcMem rM;

#if RTC_MEMORY_BACKUP
extern unsigned char rtcMd5[16];
bool didRtcChange(rtcMem* source, rtcMem* destination);
void rtcMemBackupManage();
#endif