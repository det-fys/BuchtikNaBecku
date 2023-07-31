#include "plugin.h"
#include "CHud.h"
#include "CTimer.h"
#include "CAudioEngine.h"

using namespace plugin;

class BuchtikExample {
public:
    BuchtikExample() {
        Events::gameProcessEvent += []
        {
            static bool autobuchtik = true;
            static unsigned int lastKeyPressedTime = 0;

            auto time = CTimer::m_snTimeInMilliseconds;

            CPlayerPed* pLocalPlayer = FindPlayerPed();
            if (pLocalPlayer) {
                if (KeyPressed('B') && (time - lastKeyPressedTime > 500)) {
                    lastKeyPressedTime = time;
                    autobuchtik = !autobuchtik;
                    CHud::SetHelpMessage(autobuchtik ? "BUCHTIK!" : "buchtik ne vice", true, false, false);
                }

                auto vehicle = pLocalPlayer->m_pVehicle;
                if (vehicle) {
                    bool radioDisabled = vehicle->m_vehicleAudio.m_settings.m_nRadioType == RADIO_DISABLED;

                    if (autobuchtik && !radioDisabled && !AudioEngine.IsRadioRetuneInProgress() && AudioEngine.GetCurrentRadioStationID() != RADIO_USER_TRACKS) {
                        AudioEngine.StartRadio(RADIO_USER_TRACKS, 0);
                    } 
                }
            }
        };
    }
};
BuchtikExample buchExample;