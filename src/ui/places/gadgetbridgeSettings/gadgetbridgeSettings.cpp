#include "gadgetbridgeSettings.h"
#include "rtcMem.h"

static int bleStatusLine;

static void onBtn()
{
    rM.gadgetbridge_is_on = true;
    gadgetbridgeInit();
    startBle();
    vibrateMotor(VIBRATION_ACTION_TIME);
}

static void offBtn()
{
    rM.gadgetbridge_is_on = false;
    exitBle();
    vibrateMotor(VIBRATION_ACTION_TIME);
}

void initGadgetbridgeDisplay()
{
    init_general_page(50);
    general_page_set_title("Gadgetbridge");
    genpage_set_center();

    GeneralPageButton button[] = {GeneralPageButton{DEBUG_WIFI_ON, onBtn}, GeneralPageButton{DEBUG_WIFI_OFF, offBtn}};
    general_page_set_buttons(button, 2);

    genpage_add("\n");

    bleStatusLine = genpage_add("");

    general_page_set_main();
}

void loopGadgetbridgeDisplay()
{
    if (!genpage_is_menu())
    {
        if (blePasskey != "")
        {
            genpage_change(("Passkey: " + blePasskey).c_str(), bleStatusLine);
        }
        else if (bleClientConnected)
        {
            genpage_change("Device connected", bleStatusLine);
        }

        else if (bleIsStarted)
        {
            genpage_change("Device is visible.", bleStatusLine);
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
