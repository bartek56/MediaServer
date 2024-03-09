#ifndef ICONFIGFILE_H
#define ICONFIGFILE_H

#include "Utils/VectorData.h"

static constexpr char CONFIG_PATH[] = "/etc/mediaserver";
static constexpr char MPD_CONFIG_FILE[] = "/etc/mediaserver/mpd.conf";
static constexpr char MINIDLNA_CONFIG_FILE[] = "/etc/mediaserver/minidlna.conf";
static constexpr char NAPI_CONFIG_FILE[] = "/etc/mediaserver/qnapi.ini";
static constexpr char ALARM_CONFIG_FILE[] = "/etc/mediaserver/alarm.sh";
static constexpr char SCREENSAVER_CONFIG_FILE[] = "/etc/mediaserver/screensaver.conf";
static constexpr char WPA_CONFIG_FILE[] = "/etc/mediaserver/wpa_supplicant.conf";
static constexpr char ETHERNET_CONFIG_FILE[] = "/etc/mediaserver/10-wired.network";
static constexpr char WIFI_CONFIG_FILE[] = "/etc/mediaserver/20-wireless.network";
static constexpr char SAMBA_CONFIG_FILE[] = "/etc/mediaserver/smb.conf";
static constexpr char OPKG_CONFIG_FILE[] = "/etc/opkg/opkg.conf";

class IConfigFile
{
    virtual bool SaveConfiguration(const VectorData &mConfigsParameters) = 0;
    virtual bool LoadConfiguration(VectorData &configuration) = 0;
};

#endif
