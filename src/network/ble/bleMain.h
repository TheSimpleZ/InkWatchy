#pragma once

#include "defines.h"

#if BLE_ENABLED

extern BLEServer *pServer;
extern BLEService *bleService;
extern bool bleClientConnected;
extern bool bleIsStarted;
extern String blePasskey;

void initBle();
void initBle(String name);
void startBle();
void exitBle();

void enableBonding();
void removeBondedDevices();

#endif
