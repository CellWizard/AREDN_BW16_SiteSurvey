#include <wifi_conf.h>
uint32_t cidx=0;
bool scan_20M=true;
bool scan_10M=true;
bool scan_5M=true;
uint32_t channels[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122,123,124,125,126,127,128,129,130,131,132,133,134,135,136,137,138,139,140,141,142,143,144,149,150,151,152,153,154,155,156,157,158,159,160,161,162,163,164,165,166,167,168,169,170,171,172,173,174,175,176,177,182,183,184,185,186,187,188,189,190,191,192,193,194};
static void promisc_callback(unsigned char *buf, unsigned int len, void* userdata)
{
        const ieee80211_frame_info_t *frameInfo = (ieee80211_frame_info_t *)userdata;
        if (len >= 17) {
                printf("RSSI %d channel: %d frame_type: %02X BSSID: %02X:%02X:%02X:%02X:%02X:%02X\r\n",frameInfo->rssi,channels[cidx],buf[0],frameInfo->i_addr2[0],frameInfo->i_addr2[1],frameInfo->i_addr2[2],frameInfo->i_addr2[3],frameInfo->i_addr2[4],frameInfo->i_addr2[5]);
        }
}
extern "C" {
        extern uint32_t *rltk_wlan_info;
        extern void  set_channel_bwmode(uint32_t param_1,uint32_t param_2,char param_3,uint32_t param_4);
};
void setup() {
    wifi_on(RTW_MODE_PROMISC);
    wifi_enter_promisc_mode();
    wifi_set_promisc(RTW_PROMISC_ENABLE_2, promisc_callback, 0);
    printf("%08X\r\n",(uint32_t)rltk_wlan_info);
    delay(1000);
    uint32_t adapter=**(uint32_t**)(((uint32_t)rltk_wlan_info)+0x10);

    while (1) {
        for (cidx=0; cidx<sizeof(channels)/4; cidx++) {
                if (scan_20M || scan_5M || scan_10M) {
                        if (scan_20M) {
                                set_channel_bwmode(adapter,channels[cidx],0,0);
                                printf("scanning channel %d 20M\n",channels[cidx]);      
                                delay(100);  
                        }
                        if (scan_5M) {
                                set_channel_bwmode(adapter,channels[cidx],0,5);
                                printf("scanning channel %d 5M\n",channels[cidx]);              
                                delay(100);
                        }
                        if (scan_10M) {
                                set_channel_bwmode(adapter,channels[cidx],0,6);
                                printf("scanning channel %d 10M\n",channels[cidx]);              
                                delay(100);
                        }
                

                } else {
                        delay(100);
                }

        }
    }
}

void loop() {
}
