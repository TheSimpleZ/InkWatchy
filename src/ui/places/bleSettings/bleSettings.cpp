#include "bleSettings.h"
#include "rtcMem.h"

static int bleStatusLine;
static int blePasskeyLine;

void bleOnBtn()
{
    rM.ble_is_on = true;
    gadgetbridgeInit();
    vibrateMotor(VIBRATION_ACTION_TIME);
}

void bleOffBtn()
{
    rM.ble_is_on = false;
    exitBle();
    vibrateMotor(VIBRATION_ACTION_TIME);
}

void initBleDisplay()
{
    init_general_page(50);
    general_page_set_title("Bluetooth");
    genpage_set_center();

    GeneralPageButton button[] = {GeneralPageButton{DEBUG_WIFI_ON, bleOnBtn}, GeneralPageButton{DEBUG_WIFI_OFF, bleOffBtn}};
    general_page_set_buttons(button, 2);

    genpage_add("\n");

    bleStatusLine = genpage_add("\n");
    blePasskeyLine = genpage_add("\n");

    general_page_set_main();
}

void loopBleDisplay()
{
    if (!genpage_is_menu())
    {
        debugLog("passkey is " + blePasskey + " - passKeyLine: " + blePasskeyLine + " - statusLine: " + bleStatusLine);
        if (blePasskey == "")
        {
            genpage_change("", blePasskeyLine);
        }

        if (blePasskey != "")
        {
            genpage_change("Passkey:", bleStatusLine);
            genpage_change(blePasskey.c_str(), blePasskeyLine);
        }
        else if (bleClientConnected)
        {
            genpage_change("Connected to GadgetBridge", bleStatusLine);
        }

        else if (bleIsStarted)
        {
            genpage_change("Watchy is now visible. Scan using GadgetBridge", bleStatusLine);
        }
        else
        {
            genpage_change("Bluetooth is off", bleStatusLine);
        }
    }

    resetSleepDelay();
    general_page_set_main();
    slint_loop();
}
