#include <WiFi.h>
#include <stdarg.h>
#include <WiFiManager.h>
#include <ArduinoOTA.h>
#include <WebServer.h>
#include <NimBLEDevice.h>
#include <NimBLEServer.h>
#include <Adafruit_NeoPixel.h>
#include <Preferences.h>
#include <PubSubClient.h>
#include <Update.h>
#include <WebSocketsServer.h>
#include "esp_mac.h"

#define FW_VERSION "v4.44-C6-MITM-indicate"

const uint8_t coffeeIconPng[] PROGMEM = {
137,80,78,71,13,10,26,10,0,0,0,13,73,72,68,82,0,0,0,96,
0,0,0,96,8,3,0,0,0,213,70,135,10,0,0,0,126,80,76,84,
69,141,117,92,220,210,196,159,136,112,195,180,161,124,96,70,173,154,132,83,
51,29,170,150,127,101,67,33,245,240,230,0,0,0,89,59,37,234,226,215,
242,237,227,119,89,58,184,167,149,155,133,110,198,184,167,131,104,76,163,141,
119,209,198,183,172,153,133,73,40,17,166,146,124,56,20,0,141,115,88,227,
219,207,117,90,66,185,168,148,213,202,186,50,14,0,141,115,88,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,12,245,3,139,0,0,0,32,116,82,78,83,227,
246,193,204,231,191,255,191,254,254,0,255,253,253,252,255,255,255,255,255,255,
255,255,255,255,255,246,255,193,211,255,203,76,252,236,34,0,0,3,63,73,
68,65,84,120,218,237,154,235,146,171,32,12,128,169,237,158,147,180,160,86,
123,223,94,222,255,45,23,81,65,45,96,220,70,127,45,211,153,58,78,146,
143,4,129,72,20,91,114,131,110,35,107,137,233,182,167,81,196,111,141,83,
33,226,51,243,227,8,241,161,245,81,134,96,48,31,69,8,22,243,17,132,
224,178,31,34,8,46,243,33,132,96,180,239,37,8,78,251,62,130,224,52,
239,67,136,152,125,172,90,220,222,187,200,8,96,168,27,71,120,69,162,128,
161,242,110,23,35,4,68,34,128,183,206,213,218,24,235,191,71,36,8,120,
119,190,209,198,72,124,124,34,1,128,39,184,173,54,134,227,239,21,25,3,
224,155,54,6,199,215,43,226,5,0,35,0,60,0,96,5,192,27,192,171,
220,209,198,128,253,160,200,210,0,96,7,64,15,0,51,0,96,73,0,204,
2,128,229,0,48,19,0,66,0,142,137,182,40,0,136,128,20,146,205,52,
0,132,0,190,181,248,117,67,165,47,212,227,254,18,196,21,189,1,0,105,
55,249,66,172,8,170,130,224,139,184,39,105,66,8,48,220,15,181,253,242,
116,168,60,168,126,15,19,43,194,174,26,1,12,118,244,53,162,120,110,220,
195,185,34,230,5,17,64,47,39,185,87,125,255,190,156,155,59,58,80,95,
180,204,70,3,72,89,213,163,10,205,225,116,218,59,31,94,180,220,76,208,
82,69,105,198,246,120,249,150,253,32,141,55,34,160,49,90,60,115,231,194,
157,17,176,49,83,64,247,122,119,202,134,65,98,1,36,13,0,179,11,220,
218,129,150,52,15,72,82,107,219,107,241,20,246,250,63,31,224,102,141,222,
224,114,116,52,54,128,235,53,238,79,187,67,59,25,248,60,232,196,8,243,
203,166,177,47,25,1,206,126,53,161,203,250,234,193,8,72,58,4,59,161,
191,24,1,221,24,53,19,90,145,198,152,12,72,101,135,96,38,180,194,148,
19,80,61,72,202,46,67,245,132,6,86,128,94,177,45,0,179,231,63,169,
18,102,0,220,31,104,189,200,51,162,3,83,0,122,209,54,91,141,50,187,
166,76,102,0,136,251,163,246,64,226,58,165,234,76,62,155,216,36,235,117,
154,208,59,245,233,225,199,31,128,1,48,47,97,251,7,160,0,198,8,24,
107,163,71,132,33,0,78,111,97,192,246,83,211,65,204,240,37,16,185,154,
23,208,23,145,144,50,48,220,155,190,189,151,102,113,64,37,83,28,21,141,
225,142,18,90,101,41,11,216,143,116,76,222,114,184,210,8,22,224,148,241,
12,165,73,216,50,237,65,157,185,21,41,20,178,126,79,46,149,145,81,169,
238,197,161,128,52,151,181,76,186,183,255,141,152,35,8,103,191,241,96,173,
101,247,74,214,128,67,6,176,58,130,201,119,213,25,50,3,192,28,206,43,
248,150,153,78,53,42,225,85,45,107,254,27,49,71,232,3,52,254,88,135,
191,6,164,120,128,2,247,80,162,202,171,61,242,220,2,142,153,190,214,201,
175,233,136,190,137,205,127,43,214,7,116,67,212,142,175,3,92,53,32,199,
12,114,149,105,80,27,162,76,123,229,1,180,98,253,16,117,6,57,6,208,
225,43,237,32,187,16,13,1,70,108,48,200,13,33,6,144,215,42,128,165,
123,76,237,32,247,0,173,152,181,223,57,152,69,222,230,61,187,230,91,42,
98,135,227,44,203,16,185,126,240,203,117,148,82,1,249,100,195,161,213,112,
152,42,93,98,203,78,152,80,71,227,168,212,45,95,9,156,191,150,185,64,
53,118,254,122,242,252,21,241,5,106,250,243,127,149,176,192,119,21,11,124,
25,178,196,183,45,31,127,157,243,3,189,150,65,68,74,107,212,186,0,0,
0,0,73,69,78,68,174,66,96,130,
};
const size_t coffeeIconPngLen = 1070;

const uint8_t qrCodePng[] PROGMEM = {
137,80,78,71,13,10,26,10,0,0,0,13,73,72,68,82,0,0,0,174,
0,0,0,174,1,0,0,0,0,135,119,11,67,0,0,1,64,73,68,65,
84,120,156,237,151,187,109,4,49,12,68,31,45,1,23,106,59,112,41,220,
14,92,147,59,211,150,114,29,80,225,1,90,140,131,189,179,13,127,35,155,
129,77,8,130,48,9,7,210,12,41,154,248,32,246,187,143,80,248,27,48,
10,128,18,72,93,225,0,248,204,97,226,146,202,171,165,72,97,114,7,152,
173,140,149,97,0,195,234,47,164,252,2,110,157,214,47,203,111,166,124,19,
245,229,56,86,157,215,92,38,130,58,30,230,112,90,175,77,140,172,215,217,
204,236,224,84,199,186,155,217,146,228,226,91,128,63,159,179,92,92,36,90,
7,104,154,77,37,203,197,237,113,14,155,48,97,178,157,98,187,44,89,53,
214,105,189,168,151,240,9,37,72,186,19,164,62,113,73,37,152,120,9,242,
116,2,56,77,10,20,100,86,251,214,21,232,188,130,239,247,2,246,37,173,
23,95,45,28,28,123,158,78,4,62,155,192,175,189,56,79,39,135,92,139,
122,9,14,86,73,58,17,215,98,194,190,184,130,211,121,205,233,59,195,204,
172,222,104,84,182,249,227,41,63,131,93,18,77,167,216,128,137,39,121,167,
2,134,3,23,99,46,216,207,167,252,14,222,78,225,71,193,175,173,103,50,
25,235,100,171,0,62,71,138,98,111,127,182,38,195,183,197,129,162,148,201,
235,101,222,41,234,224,69,61,169,239,216,255,52,250,46,158,0,74,234,219,
148,138,73,219,28,0,0,0,0,73,69,78,68,174,66,96,130,
};
const size_t qrCodePngLen = 377;


#define HOSTNAME "delonghi-c6"
#define SERVICE_UUID "00035b03-58e6-07dd-021a-08123a000300"
#define CHAR_UUID    "00035b03-58e6-07dd-021a-08123a000301"
#define CHAR2_UUID   "00035b03-58e6-07dd-021a-08123a0003ff"
#define FAKE_NAME    "D1900664"
#define REAL_SERIAL  "219006CP16031740064"
#define RGB_PIN 8
int rgbBrightness = 50;  // v4.18: persisted status-LED brightness (0-255), was hardcoded

// v4.41: fixed-size ring buffer for a web-viewable debug log — lets you
// capture the same func/exec/pct trace we already print to Serial, without
// needing USB access on a stationary install. Deliberately a plain char
// array, not String, to avoid the heap-fragmentation risk this file's own
// earlier comments warn about (frequent small String concatenation in a
// hot path). Fixed cost: 100 * 96 = ~9.4KB static RAM, well within budget.
#define DEBUG_LOG_LINES 300
#define DEBUG_LOG_LINE_LEN 96
char debugLogBuf[DEBUG_LOG_LINES][DEBUG_LOG_LINE_LEN];
int debugLogHead = 0;    // next slot to write
int debugLogCount = 0;   // how many slots are filled (caps at DEBUG_LOG_LINES)

void debugLog(const char* fmt, ...) {
  char line[DEBUG_LOG_LINE_LEN];
  int prefixLen = snprintf(line, sizeof(line), "[%lu] ", millis());
  va_list args;
  va_start(args, fmt);
  vsnprintf(line + prefixLen, sizeof(line) - prefixLen, fmt, args);
  va_end(args);
  // v4.42 FIX: this firmware builds with CDCOnBoot=cdc — with NO USB host
  // physically attached (the stationary-install case this whole /debug_log
  // feature exists for), Serial's internal TX buffer eventually fills up
  // since nothing ever drains it, and every FURTHER Serial.print/println/
  // printf call then BLOCKS indefinitely waiting for buffer space that
  // will never free. Confirmed live: the ring-buffer log went completely
  // silent (not just the % field) exactly once event frequency ramped up
  // at the start of a real brew — matches this exactly. `if (Serial)`
  // reflects whether a host is actually connected (DTR asserted) for
  // native USB CDC, so this safely skips the Serial write (the web ring
  // buffer below is unaffected either way — that's what /debug_log reads).
  if (Serial) Serial.println(line);
  strncpy(debugLogBuf[debugLogHead], line, DEBUG_LOG_LINE_LEN - 1);
  debugLogBuf[debugLogHead][DEBUG_LOG_LINE_LEN - 1] = '\0';
  debugLogHead = (debugLogHead + 1) % DEBUG_LOG_LINES;
  if (debugLogCount < DEBUG_LOG_LINES) debugLogCount++;
}

// Target machine MAC and the derived (offset) BLE advertising MAC are now
// configurable at runtime via the web UI /settings page instead of being
// hardcoded, so a new machine can be set up without touching the code.
String delonghiMac = "00:1e:c0:30:c0:45";  // loaded from NVS in setup()
uint8_t FAKE_MAC[6];  // computed from delonghiMac by computeFakeMac()

// ESP-IDF derives the Bluetooth MAC as (base MAC + 2) on the last octet.
// Confirmed empirically: esp_base_mac_addr_set(0x...45) actually advertises
// as 0x...47 over BLE. Subtract 2 here so the resulting BLE address matches
// the target MAC exactly, whatever it's set to.
void computeFakeMac(const String& macStr) {
  int vals[6];
  sscanf(macStr.c_str(), "%x:%x:%x:%x:%x:%x",
    &vals[0], &vals[1], &vals[2], &vals[3], &vals[4], &vals[5]);
  for (int i = 0; i < 6; i++) FAKE_MAC[i] = (uint8_t)vals[i];
  FAKE_MAC[5] -= 2;
}

Adafruit_NeoPixel rgb(1, RGB_PIN, NEO_GRB + NEO_KHZ800);
WebServer server(80);
WebSocketsServer webSocket(81);
Preferences prefs;

// User-customizable recipe settings, persisted to NVS. Defaults match the
// documented ranges from earlier CoffeeLink-slider testing (v3.66).
// These are now embedded directly into every START command sent through
// our bridge (v3.93+), instead of relying solely on the machine's own
// SAVE mechanism to persist changes reliably.
float savedEspressoMl = 83, savedEspressoStrength = 4;
float savedCoffeeMl = 204, savedCoffeeStrength = 3;
float savedCappuccinoMl = 90, savedCappuccinoStrength = 3, savedCappuccinoMilkSec = 19;
float savedLatteMl = 80, savedLatteStrength = 4, savedLatteMilkSec = 31;
bool advImmediate = false;  // false = start advertising only after machine connects; true = start immediately in setup()
String mqttHost = "192.168.0.157";
int mqttPort = 1883;
String mqttUser = "Home91";
String mqttPass = "admin260976";
String staticIP = "";      // empty = use DHCP
String staticGateway = "";
String staticSubnet = "255.255.255.0";
WiFiClient wifiClient;
PubSubClient mqtt(wifiClient);
String machineState = "unknown";  // offline / asleep / waking / ready
String waterMessage = "";  // shown on the LEFT of the machine image (water tank side)
String milkMessage = "";   // shown on the RIGHT of the machine image (milk carafe side)
String milkState = "";     // "" / "missing" / "clean" — drives which icon shows
String beansMessage = "";  // coffee beans hopper empty
String beansState = "";    // "" / "empty"
unsigned long beansStickyUntil = 0;      // sticky display: keep showing until this millis() time
unsigned long beansStickyPressSnapshot = 0;  // lastDrinkPressAt value when sticky window started
String groundsMessage = ""; // shown BELOW the machine image (coffee grounds container)
String waterState = "";    // "" / "missing" / "low" — drives which RIGHT icon shows
String groundsState = "";  // "" / "missing" / "full" — drives which RIGHT icon shows
unsigned long lastMqttReconnectAttempt = 0;
unsigned long lastSelfStatusPoll = 0;
#define MQTT_CMD_TOPIC   "delonghi/cmd"
#define MQTT_STATE_TOPIC "delonghi/state"
#define MQTT_PARAM_SOURCE_TOPIC "delonghi/param_source"  // v4.27: current profile/ESP32 indicator
#define MQTT_AVAIL_TOPIC "delonghi/availability"

NimBLEServer* bleServer = nullptr;
NimBLECharacteristic* fakeChar = nullptr;
NimBLECharacteristic* fakeChar2 = nullptr;
bool phoneConnected = false;

NimBLEClient* bleClient = nullptr;
NimBLERemoteCharacteristic* bleChar = nullptr;
bool machineConnected = false;
bool otaInProgress = false;  // set true during a web /update OTA upload, checked by the WiFi watchdog so it never restarts mid-flash

// MonitorV1 (byte[2]==0x70) — a separate, simpler status packet we never
// parsed before, decoded via APK decompilation. byte[4]+byte[5] (16-bit LE)
// is a 32-alarm bitmask. Of the 32 possible bits, only 18 are ever actually
// shown by the official app (14 are permanently ignored/suppressed there
// regardless of value) — see project docs for the full derivation.
uint32_t monitorV1Alarms = 0;  // raw 32-bit mask, updated whenever a MonitorV1 packet arrives
// MonitorV1 byte[8]/byte[9] — machine's own "Function OnGoing"/"Execution
// Program" state codes. Official CoffeeLink requires func==7 && exec==0
// before it will even attempt a recipe SAVE (see handleSettingProfile).
uint8_t monitorFuncCode = 0xFF;  // 0xFF = "never seen a MonitorV1 packet yet"
uint8_t monitorExecCode = 0xFF;
inline bool machineReadyForSave() { return monitorFuncCode == 7 && monitorExecCode == 0; }

// v4.13: shared parameter-source selector for ALL drinks — 0=ESP32(NVS,
// current default), 1-6=that machine profile number (read live via A6F0
// right before each brew instead of using NVS values). Chosen via the
// repurposed "Увімкнути" button (cycles while machine is awake) — resets
// to 0 automatically whenever the machine falls back asleep.
uint8_t paramSource = 0;
bool readFromActiveProfile(uint8_t recipeId, float* ml, float* sec, uint8_t* level);  // defined later, forward-declared for sendDrinkCommand's use
bool readQuantitiesOnly(uint8_t recipeId, float* ml, float* sec, uint8_t* level);  // defined later, forward-declared for handleParamPing's use

struct AlarmDef { uint8_t bit; const char* text; bool onMainPage; };
// bit, Ukrainian text, whether it also appears in the main-page single-icon-priority slot
// (bit 6 "Потрібен сервіс" is service-page-only per user's decision; bits 0/1/5/15
// are intentionally excluded entirely — already covered by the existing d0-packet icons)
const AlarmDef ALARM_TABLE[] = {
  {6,  "Потрібен сервіс", false},
  {2,  "Потрібне декальцинування", true},
  {3,  "Треба замінити фільтр води", true},
  {4,  "Занадто дрібний помел", true},
  {8,  "Забагато кави", true},
  {17, "Відсутній контейнер зерен", true},
  {9,  "Не працює мотор заварювального блоку", false},
  {18, "Наявність решітки", false},
  {19, "Датчик заварювального блоку", false},
  {22, "Проблема субмодулів розширення", false},
  {25, "Проблема вентилятора конденсату", false},
  {12, "Проблема гідравлічного контуру", false},
  {14, "Почистити регулятор", false},
  {7,  "Несправність датчика нагріву кави", false},
  {10, "Несправність датчика пари", false},
  {13, "Бак на місці", false},
  {16, "Бак переповнений", false},
  {20, "Замало кави", false},
  {21, "Проблема звязку модуля розширення", false},
  {23, "Проблема млинка 1", false},
  {24, "Проблема млинка 2", false},
  {26, "Проблема звязку годинника/BT", false},
  {27, "Проблема SPI-звязку", false},
};
const int ALARM_TABLE_LEN = sizeof(ALARM_TABLE) / sizeof(ALARM_TABLE[0]);
inline bool alarmActive(uint8_t bit) { return (monitorV1Alarms >> bit) & 1; }
unsigned long wakeDetectedAt = 0;
bool settingsSyncSent = false;
bool lastEncState = false;
bool connectingToMachine = false;

uint8_t lastFullPkt[128];
int lastFullPktLen = 0;

#define MAX_FRAGMENTS 40
uint8_t fragBufs[MAX_FRAGMENTS][64];
int fragLens[MAX_FRAGMENTS];
int fragCount = 0;
unsigned long lastFragmentTime = 0;

String allPackets = "";
int packetCount = 0;
unsigned long lastUpdate = 0;
unsigned long lastBlink = 0;
bool blinkState = false;

void setRGB(uint8_t r, uint8_t g, uint8_t b) {
  rgb.setPixelColor(0, rgb.Color(r, g, b));
  rgb.show();
}

unsigned long lastWifiBlink = 0;

void updateRGB() {
  if (machineConnected && phoneConnected) setRGB(0, 255, 0);
  else if (machineConnected) setRGB(0, 0, 255);
  else {
    if (millis() - lastBlink > 500) {
      lastBlink = millis(); blinkState = !blinkState;
      setRGB(blinkState ? 255 : 0, 0, 0);
    }
  }
  // Brief white blink overlay every ~4s to confirm Wi-Fi is OK, without
  // disrupting the base BLE-status color scheme above. If Wi-Fi is DOWN
  // (e.g. router rebooted), a yellow blink fires instead — same cadence,
  // opposite meaning: "everything else is fine, but Wi-Fi just dropped".
  if (millis() - lastWifiBlink > 4000) {
    lastWifiBlink = millis();
    uint8_t r, g, b;
    if (machineConnected && phoneConnected) { r = 0; g = 255; b = 0; }
    else if (machineConnected) { r = 0; g = 0; b = 255; }
    else { r = blinkState ? 255 : 0; g = 0; b = 0; }
    if (WiFi.status() == WL_CONNECTED) {
      setRGB(255, 255, 255);
    } else {
      setRGB(255, 255, 0);
    }
    delay(60);
    setRGB(r, g, b);
  }
}

void sendPacketToPhone(uint8_t* pkt, int len) {
  // FIXED (v3.24): the old version only ever sent 3 fixed fragments
  // (1 byte + up to 20 bytes + THE ENTIRE REMAINDER in one indicate() call).
  // That remainder call silently truncated at the MTU limit (~20 bytes) for
  // any response longer than ~41 bytes total — e.g. a4f0's 68-byte response
  // always arrived at the phone as only 41 bytes, with the rest silently
  // lost. Confirmed via phone-side adb logcat (BtGatt.GattService onNotify
  // showed exactly 3 notifications, lengths 1/20/20, every single time).
  // Now loops properly, sending ALL remaining bytes in MTU-sized chunks.
  if (!phoneConnected || !fakeChar || len < 3) return;
  const int CHUNK = 20;
  uint8_t f1[1] = {pkt[0]};
  fakeChar->setValue(f1, 1); fakeChar->indicate(); delay(200);
  int offset = 1;
  while (offset < len) {
    int chunkLen = min(len - offset, CHUNK);
    fakeChar->setValue(pkt + offset, chunkLen); fakeChar->indicate(); delay(200);
    offset += chunkLen;
  }
}

void forwardFragmentsToPhone() {
  if (fragCount == 0) return;
  uint8_t fullPkt[128];
  int fullLen = 0;
  for (int i = 0; i < fragCount; i++) {
    if (fullLen + fragLens[i] > (int)sizeof(fullPkt)) {
      if (Serial) { Serial.printf("!!! fullPkt overflow avoided, truncating at %d bytes !!!\n", fullLen);
      Serial.printf("!!! fullPkt overflow avoided, truncating at %d bytes !!!\n", fullLen); }
      break;
    }
    memcpy(fullPkt + fullLen, fragBufs[i], fragLens[i]);
    fullLen += fragLens[i];
  }
  fragCount = 0;
  memcpy(lastFullPkt, fullPkt, fullLen);
  lastFullPktLen = fullLen;
  // v4.41: fires on every reassembled packet (not just status ones) — to
  // avoid the diagnostic itself adding load during exactly the high-
  // traffic brewing window we're trying to observe, always log a
  // suspiciously-short packet (<26 bytes, the length a full status packet
  // needs), but throttle normal-length ones to once per 500ms.
  static unsigned long lastAssembledLogAt = 0;
  if (fullLen < 26 || millis() - lastAssembledLogAt > 500) {
    lastAssembledLogAt = millis();
    debugLog("Assembled %d bytes (opcode 0x%02X)%s", fullLen, fullLen >= 3 ? fullPkt[2] : 0,
             fullLen < 26 ? " SHORT" : "");
  }

  maybeParseStatus(fullPkt, fullLen);
  sendPacketToPhone(fullPkt, fullLen);
  lastUpdate = millis();
}

void notifyFromMachine(NimBLERemoteCharacteristic* chr, uint8_t* data, size_t length, bool isNotify) {
  packetCount++;
  lastUpdate = millis();
  // Fragment buffering happens FIRST and fast, before any slow string work,
  // so NimBLE can send the ATT Confirmation back to the real machine with
  // minimal delay (a slow callback here was a suspected cause of the real
  // machine sometimes truncating multi-fragment responses early).
  if (fragCount < MAX_FRAGMENTS && length <= 64) {
    memcpy(fragBufs[fragCount], data, length);
    fragLens[fragCount] = length;
    fragCount++;
  } else if (fragCount >= MAX_FRAGMENTS) {
    if (Serial) { Serial.println("!!! FRAGMENT DROPPED: MAX_FRAGMENTS limit hit !!!");
    Serial.println("!!! FRAGMENT DROPPED: MAX_FRAGMENTS limit hit !!!"); }
  }
  lastFragmentTime = millis();

  // Logging (for Serial monitor) — cheap enough to keep, but no longer
  // rebuilds the 2000-char allPackets history string on every call.
  String packet = "";
  for (int i = 0; i < (int)length; i++) {
    if (i > 0) packet += " ";
    char buf[4]; sprintf(buf, "%02x", data[i]); packet += buf;
  }
  if (Serial) { Serial.printf("M→P [%d] len=%d: %s\n", packetCount, length, packet.c_str());
  Serial.printf("M→P [%d] len=%d: %s\n", packetCount, length, packet.c_str()); }
}

void sendSettingsSyncProbe() {
  // Self-initiated probe to the REAL machine (not the phone), using the
  // exact byte sequence CoffeeLink sends in a direct connection ~19s after
  // wake (delonnew1real.pcapng frames 6115-6307). Goal: test whether the
  // real machine only produces its richer status telemetry (which precedes
  // this sequence in the real capture) in response to these specific reads,
  // independent of whether CoffeeLink itself ever sends them through us.
  if (!machineConnected || !bleChar) return;
  if (Serial) { Serial.println("--- SETTINGS-SYNC PROBE: sending real sequence to machine ---");
  Serial.println("--- SETTINGS-SYNC PROBE: sending real sequence to machine ---"); }
  uint8_t c1[] = {0x0d,0x04,0xa3,0xf0,0x0f};
  uint8_t c2[] = {0x0d,0x06,0xa4,0xf0,0x01,0x03,0x08};
  uint8_t c3[] = {0x0d,0x06,0xa4,0xf0,0x04,0x06,0x08};
  uint8_t c4[] = {0x0d,0x06,0xaa,0xf0,0x04,0x06,0x06};
  uint8_t c5[] = {0x0d,0x07,0xa6,0xf0,0x01,0x01,0x18,0x11};
  uint8_t c6[] = {0x0d,0x05,0xa9,0xf0,0x01,0x05};
  bleChar->writeValue(c1, sizeof(c1), false); delay(400);
  bleChar->writeValue(c2, sizeof(c2), false); delay(400);
  bleChar->writeValue(c3, sizeof(c3), false); delay(400);
  bleChar->writeValue(c4, sizeof(c4), false); delay(400);
  bleChar->writeValue(c5, sizeof(c5), false); delay(400);
  bleChar->writeValue(c6, sizeof(c6), false); delay(400);
  if (Serial) { Serial.println("--- SETTINGS-SYNC PROBE done, any replies came via notifyFromMachine above ---");
  Serial.println("--- SETTINGS-SYNC PROBE done, any replies came via notifyFromMachine above ---"); }
}

void sendSerialResponse() {
  // Bytes captured from real machine responses (delonnew1real.pcapng
  // frames 6092+6096, delon65new21real.pcapng frames 6601+6606) rather
  // than recomputed. The second capture clearly shows a standalone 0xd0
  // marker indication immediately before the "1a a1 0f..." payload —
  // same framing as every other response type — so it's restored here.
  static const uint8_t resp[] = {
    0xd0,
    0x1a, 0xa1, 0x0f, 0x00, 0xcd,
    '2','1','9','0','0','6','C','P','1','6','0','3','1','7','4','0','0','6','4',
    0x00, 0xd7
  };
  if (!phoneConnected || !fakeChar) return;
  sendPacketToPhone((uint8_t*)resp, sizeof(resp));
  if (Serial) { Serial.printf("Sent serial (hardcoded real bytes): %s\n", REAL_SERIAL);
  Serial.printf("Sent serial (hardcoded real bytes): %s\n", REAL_SERIAL); }
}

class CharCallbacks : public NimBLECharacteristicCallbacks {
  void onWrite(NimBLECharacteristic* chr, NimBLEConnInfo& connInfo) {
    NimBLEAttValue val = chr->getValue();
    String packet = "";
    for (int i = 0; i < (int)val.length(); i++) {
      if (i > 0) packet += " ";
      char buf[4]; sprintf(buf, "%02x", val[i]); packet += buf;
    }
    allPackets = "P→M: " + packet + "\n" + allPackets;
    if (allPackets.length() > 2000) allPackets = allPackets.substring(0, 2000);
    if (Serial) { Serial.printf("P→M: %s\n", packet.c_str());
    Serial.printf("P→M: %s\n", packet.c_str()); }

    // Detect if encryption state changes mid-session (checked from our own
    // NimBLE stack — the actual crypto endpoint — not an external sniffer,
    // so this is authoritative regardless of what Wireshark can decode).
    bool nowEnc = connInfo.isEncrypted();
    if (nowEnc != lastEncState) {
      lastEncState = nowEnc;
      if (Serial) { Serial.printf("!!! ENCRYPTION STATE CHANGED: Encrypted=%d Bonded=%d Authenticated=%d !!!\n",
        connInfo.isEncrypted(), connInfo.isBonded(), connInfo.isAuthenticated()); }
    }

    // Serial number request: previously intercepted and answered locally
    // (hardcoded real bytes). Now forwarding to the real machine instead,
    // as a transparency test — even though our own settings-sync probe
    // already got rich data (a6f0) from the machine WITHOUT ever sending
    // it 0xa1/0x0f, which contradicts the theory that this is required to
    // unlock the machine's richer telemetry. Cheap to test either way.
    // Detect the wake command to time our self-initiated settings-sync probe
    if (val.length() >= 4 && val[2] == 0x82 && val[3] == 0x0f && wakeDetectedAt == 0) {
      wakeDetectedAt = millis();
      if (Serial) { Serial.println("Wake command detected, starting settings-sync timer");
      Serial.println("Wake command detected, starting settings-sync timer"); }
    }
    // Forward everything (including serial requests) to machine
    if (machineConnected && bleChar) {
      bleChar->writeValue((uint8_t*)val.data(), val.length(), false);
    }
  }

  void onSubscribe(NimBLECharacteristic* chr, NimBLEConnInfo& connInfo, uint16_t subValue) {
    if (Serial) { Serial.printf("Phone subscribed! subValue=%d\n", subValue);
    Serial.printf("Phone subscribed! subValue=%d\n", subValue); }
    if (subValue > 0 && lastFullPktLen > 0) {
      delay(200);
      sendPacketToPhone(lastFullPkt, lastFullPktLen);
      if (Serial) { Serial.println("Sent cached packet after subscription");
      Serial.println("Sent cached packet after subscription"); }
    }
  }

  void onRead(NimBLECharacteristic* chr, NimBLEConnInfo& connInfo) {
    if (Serial) { Serial.println("Phone READ char1");
    Serial.println("Phone READ char1"); }
  }
};

class Char2Callbacks : public NimBLECharacteristicCallbacks {
  void onRead(NimBLECharacteristic* chr, NimBLEConnInfo& connInfo) {
    if (Serial) { Serial.println("Phone READ char2");
    Serial.println("Phone READ char2"); }
    chr->setValue((uint8_t*)REAL_SERIAL, strlen(REAL_SERIAL));
  }
};

class ServerCallbacks : public NimBLEServerCallbacks {
  void onConnect(NimBLEServer* server, NimBLEConnInfo& connInfo) {
    if (Serial) { Serial.printf("Phone connected: %s\n", connInfo.getAddress().toString().c_str());
    Serial.printf("Phone connected: %s\n", connInfo.getAddress().toString().c_str()); }
    lastEncState = connInfo.isEncrypted();
    if (Serial) { Serial.printf("  Encrypted=%d Bonded=%d Authenticated=%d\n",
      connInfo.isEncrypted(), connInfo.isBonded(), connInfo.isAuthenticated()); }
    phoneConnected = true;
    fragCount = 0;
    if (!machineConnected) connectingToMachine = true;
  }
  void onDisconnect(NimBLEServer* server, NimBLEConnInfo& connInfo, int reason) {
    if (Serial) { Serial.printf("Phone disconnected, reason=%d\n", reason);
    Serial.printf("Phone disconnected, reason=%d\n", reason); }
    phoneConnected = false;
    // Only restart advertising here if it's safe to do so: in immediate
    // mode it should always be on, and in after-connect mode it should
    // only be on while we actually have a machine link.
    if (advImmediate || machineConnected) NimBLEDevice::getAdvertising()->start();
  }
};

// ===================== MQTT =====================

String lastSentCmdHex = "(ще нічого не надсилалось)";

void sendRawToMachine(const uint8_t* cmd, int len) {
  // Diagnostic: remember the bytes as hex, regardless of connection state,
  // so the user can see exactly what WOULD be / WAS sent, and copy it for
  // comparison against known-good captures.
  String hex = "";
  for (int i = 0; i < len; i++) {
    char buf[4];
    snprintf(buf, sizeof(buf), "%02x ", cmd[i]);
    hex += buf;
  }
  hex.trim();
  lastSentCmdHex = hex;
  if (!machineConnected || !bleChar) {
    if (Serial) { Serial.println("--- MQTT/web command ignored: machine not connected ---");
    Serial.println("--- MQTT/web command ignored: machine not connected ---"); }
    return;
  }
  bleChar->writeValue((uint8_t*)cmd, len, false);
}

// Sends a named drink/action command to the real machine. Bytes for
// espresso and latte_macchiato are confirmed from real captures; the rest
// are placeholders until captured — pressing those buttons just logs a
// message instead of sending anything (safer than guessing wrong bytes).
bool brewingActive = false;
// Today's drink counter — RAM only (never written to flash/NVS), resets
// on reboot. User explicitly wants this to avoid any flash wear from
// frequent writes — a simple in-memory counter for casual "how many
// today" curiosity, not a durable log.
uint16_t drinksToday = 0;
String brewingName = "";
unsigned long brewingStartedAt = 0;
unsigned long lastDrinkPressAt = 0;  // for the 20s auto-hiding wake prompt
uint8_t brewProgressRaw = 0;    // last real byte[17]-equivalent value seen
uint8_t brewProgressMax = 1;    // highest value seen so far this brew, for normalizing to ~0-100%
uint8_t warmupProgressRaw = 0;
uint8_t warmupProgressMax = 1;
// Last percentage actually published to delonghi/brew_progress — global
// (not function-local) so it can be explicitly reset to 0xFF whenever a
// NEW brew genuinely starts (both our own sendDrinkCommand() and the
// external-detection path). Without this reset, a fresh brew starting at
// 0% right after a PREVIOUS brew ended high would be wrongly caught by
// the v3.73 "suspicious drop to 0" guard below, silently blocking the
// real start (confirmed: Hot Water never showed on the matrix right
// after a Coffee brew — this was why).
uint8_t lastBrewProgressPct = 0xFF;
uint8_t lastPassivePct = 0;  // v4.22: renamed from lastWakingPct — no longer
                             // scoped to the "waking" state, tracks the trend
                             // across ALL passive brew-detection readings now.
                             // Was a local static inside maybeParseStatus —
                             // moved to global so connectToMachine() can reset
                             // it on every fresh connection (see long-idle-
                             // reconnect bug below)
uint8_t wakingAsleepStreak = 0;  // v4.26: counts consecutive asleep-looking
                                  // (0x00/0x01) readings seen while
                                  // machineState=="waking" — needs 2 in a row
                                  // before a real asleep transition is trusted,
                                  // see the classification block below
uint8_t notDispensingStreak = 0;  // v4.37: consecutive non-dispensing
                                   // readings seen while brewingActive —
                                   // see the clearing block below
bool brewingUsesRealSignal = false;  // v4.37: true once realDispensing (the
                                      // func/exec byte signal) has fired at
                                      // least once during the CURRENT brew —
                                      // only then do we trust its absence to
                                      // mean "dispensing stopped" for the
                                      // fast clear. A brew armed only via the
                                      // %-trend fallback (func code not yet
                                      // mapped for that recipe) never sets
                                      // this, so it safely falls back to the
                                      // old 5-minute cap instead of risking
                                      // a false "stopped" mid-brew.
unsigned long lastMqttPublishAt = 0;  // v4.29: updated at every one of our own
                                       // mqtt.publish() calls (state/attention/
                                       // param_source/brew_progress) — lets the
                                       // BLE self-poll below briefly stand back
                                       // instead of firing in the very same
                                       // instant as outgoing Wi-Fi traffic, so
                                       // the two radios take turns rather than
                                       // both being asked to work at once

// ⭐ CHECKSUM CRACKED: confirmed universal across the whole protocol
// (drink start/stop, recipe-save, wake, even status-poll) — simple XOR of
// every byte before the checksum, then XOR with the constant 0x55.
// Verified against 13+ diverse real captured commands, zero mismatches.
uint8_t computeChecksum(uint8_t* data, int len) {
  uint8_t x = 0;
  for (int i = 0; i < len; i++) x ^= data[i];
  return x ^ 0x55;
}

// ===================== Profile switching / read-back (v4.02) =====================
// Globals holding the most recent A6F0 (read-quantities) response, parsed
// in maybeParseStatus() below. "Fresh" is cleared before each new query and
// set once a genuine response for that query arrives — callers poll it
// with a short timeout rather than blocking on BLE directly.
bool lastA6F0Fresh = false;
uint8_t lastA6F0Echo4 = 0;  // byte[4] of the response, meaning uncertain post-v4.03 fix — see notes at the parser
float lastA6F0Ml = 0;
float lastA6F0Sec = 0;
uint8_t lastA6F0StrengthLevel = 0;  // decoded back to 1-5, not the raw nibble

// Confirmed via APK decompilation (AccountViewModel.c0()->p097j6.b.d0()):
// a dedicated 6-byte opcode that switches the machine's currently active
// profile. CoffeeLink sends this BEFORE any SAVE, so a save always lands
// in whichever profile was just activated.
void sendProfileSwitch(uint8_t profileId) {
  uint8_t cmd[6];
  cmd[0] = 0x0d; cmd[1] = 0x05; cmd[2] = 0xA9; cmd[3] = 0xF0;
  cmd[4] = profileId;
  cmd[5] = computeChecksum(cmd, 5);
  sendRawToMachine(cmd, sizeof(cmd));
}

// CORRECTED (v4.03) via APK decompilation deep-dive — the earlier byte
// layout was wrong. Real format (f.U(RecipeData) -> bVar.E(profileId,
// recipeId) -> X(profileId, recipeId, recipeId)): byte[4]=ACTIVE PROFILE
// NUMBER (not recipeId!), byte[5]=recipeId, byte[6]=recipeId (repeated).
// The earlier "01 18(24)" was a DIFFERENT command (bulk-read all 24
// recipe slots at once, from the connect-time sync path) — wrong for
// reading a single recipe's quantities.
void sendRecipeQuantitiesQuery(uint8_t profileId, uint8_t recipeId) {
  uint8_t cmd[8];
  cmd[0] = 0x0d; cmd[1] = 0x07; cmd[2] = 0xA6; cmd[3] = 0xF0;
  cmd[4] = profileId; cmd[5] = recipeId; cmd[6] = recipeId;
  cmd[7] = computeChecksum(cmd, 7);
  lastA6F0Fresh = false;  // caller should poll this after sending
  sendRawToMachine(cmd, sizeof(cmd));
}

// Confirmed recipe-customization formulas (from isolated CoffeeLink slider
// tests): coffee/water = ml*2 (16-bit), milk = seconds*10 (16-bit),
// strength = level*16+1 (1 byte, levels 1-5). Builds and sends a real
// "save recipe" command (action=0x00) for ANY value in range — no longer
// limited to pre-captured reference points now that the checksum is known.
// Builds a 12-byte 82-f0-family command (works for action=0x00 save,
// 0x01 start, 0x04 stop) from the given recipe values. Shared by the
// settings-save route AND sendDrinkCommand's START calls (v3.93+) — so
// a drink always starts with the user's saved water/milk/strength
// embedded directly, instead of relying on the machine's own SAVE
// persisting reliably (still sent too, as a secondary attempt, but no
// longer the only mechanism).
void buildRecipeCmd(uint8_t* cmd, uint8_t recipeId, uint8_t action, float coffeeMl, float milkSec, uint8_t strengthLevel) {
  uint16_t coffeeVal = (uint16_t)(coffeeMl * 2.0 + 0.5);
  uint16_t milkVal = (uint16_t)(milkSec * 10.0 + 0.5);
  if (strengthLevel < 1) strengthLevel = 1;
  if (strengthLevel > 5) strengthLevel = 5;
  // CONFIRMED (v4.02) via APK decompilation, cross-checked against the A6F0
  // read-back response format: raw strength enum (p127m6.c) is EXACTLY
  // level*16 (PREGROUND=0,EXTRA_MILD=16,MILD=32,NORMAL=48,STRONG=64,
  // EXTRA_STRONG=80) — the "+N" comes from XOR with the per-ACTION mode
  // enum, not a fixed constant: SAVE_BEVERAGE(mode=1)→+1 for genuine SAVE
  // (action=0x00); PREPARE_BEVERAGE(mode=2)→+2 for START/STOP (action=
  // 0x01/0x04) — the +2 v3.96 confirmed against real captures was only
  // ever tested against START commands, so it was action-specific all
  // along, not a universal constant as first assumed.
  uint8_t mode = (action == 0x00) ? 1 : 2;
  uint8_t strengthByte = (strengthLevel * 16) ^ mode;
  cmd[0] = 0x0d; cmd[1] = 0x0b; cmd[2] = 0x82; cmd[3] = 0xf0;
  cmd[4] = recipeId; cmd[5] = action;
  cmd[6] = (coffeeVal >> 8) & 0xFF; cmd[7] = coffeeVal & 0xFF;
  cmd[8] = (milkVal >> 8) & 0xFF;   cmd[9] = milkVal & 0xFF;
  cmd[10] = strengthByte;
  cmd[11] = computeChecksum(cmd, 11);
}

void sendRecipeSetting(uint8_t recipeId, float coffeeMl, float milkSec, uint8_t strengthLevel) {
  uint8_t cmd[12];
  buildRecipeCmd(cmd, recipeId, 0x00, coffeeMl, milkSec, strengthLevel);
  if (Serial) { Serial.printf("--- Recipe setting: recipe=%d coffee=%.1fml(%d) milk=%.1fs(%d) strength=%d ---\n",
                recipeId, coffeeMl, (cmd[6]<<8)|cmd[7], milkSec, (cmd[8]<<8)|cmd[9], strengthLevel); }
  sendRawToMachine(cmd, 12);
}

void sendDrinkCommand(const String& drink) {
  if (Serial) { Serial.println("--- Command requested: " + drink + " ---");
  Serial.println("--- Command requested: " + drink + " ---"); }
  if (drink != "power_on") lastDrinkPressAt = millis();
  if (drink == "power_on") {
    uint8_t cmd[] = {0x0d,0x0b,0x82,0x0f,0x28,0x01,0x00,0x00,0x00,0x00,0x00,0xf7};
    sendRawToMachine(cmd, sizeof(cmd));
  }
  if (drink == "espresso") {
    float ml = savedEspressoMl, sec = 0; uint8_t lvl = (uint8_t)savedEspressoStrength;
    if (paramSource != 0) { if (!readFromActiveProfile(0x01, &ml, &sec, &lvl)) { ml = savedEspressoMl; sec = 0; lvl = (uint8_t)savedEspressoStrength; } }
    uint8_t cmd[12];
    buildRecipeCmd(cmd, 0x01, 0x01, ml, sec, lvl);
    sendRawToMachine(cmd, sizeof(cmd));
    brewingActive = (machineState == "ready"); brewingName = "Еспресо"; brewingStartedAt = millis(); brewProgressRaw = 0; lastBrewProgressPct = 0xFF; notDispensingStreak = 0; brewingUsesRealSignal = false; if(brewingActive)drinksToday++;
  } else if (drink == "espresso_stop") {
    uint8_t cmd[] = {0x0d,0x0b,0x82,0xf0,0x01,0x04,0x00,0xa6,0x00,0x00,0x42,0xc0};
    sendRawToMachine(cmd, sizeof(cmd));
    brewingActive = false;
  } else if (drink == "latte_macchiato") {
    float ml = savedLatteMl, sec = savedLatteMilkSec; uint8_t lvl = (uint8_t)savedLatteStrength;
    if (paramSource != 0) { if (!readFromActiveProfile(0x08, &ml, &sec, &lvl)) { ml = savedLatteMl; sec = savedLatteMilkSec; lvl = (uint8_t)savedLatteStrength; } }
    uint8_t cmd[12];
    buildRecipeCmd(cmd, 0x08, 0x01, ml, sec, lvl);
    sendRawToMachine(cmd, sizeof(cmd));
    brewingActive = (machineState == "ready"); brewingName = "Латте Макіато"; brewingStartedAt = millis(); brewProgressRaw = 0; lastBrewProgressPct = 0xFF; notDispensingStreak = 0; brewingUsesRealSignal = false; if(brewingActive)drinksToday++;
  } else if (drink == "latte_macchiato_stop") {
    uint8_t cmd[] = {0x0d,0x0b,0x82,0xf0,0x08,0x04,0x00,0xa0,0x01,0x36,0x42,0xf8};
    sendRawToMachine(cmd, sizeof(cmd));
    brewingActive = false;
  } else if (drink == "coffee") {
    float ml = savedCoffeeMl, sec = 0; uint8_t lvl = (uint8_t)savedCoffeeStrength;
    if (paramSource != 0) { if (!readFromActiveProfile(0x02, &ml, &sec, &lvl)) { ml = savedCoffeeMl; sec = 0; lvl = (uint8_t)savedCoffeeStrength; } }
    uint8_t cmd[12];
    buildRecipeCmd(cmd, 0x02, 0x01, ml, sec, lvl);
    sendRawToMachine(cmd, sizeof(cmd));
    brewingActive = (machineState == "ready"); brewingName = "Кава"; brewingStartedAt = millis(); brewProgressRaw = 0; lastBrewProgressPct = 0xFF; notDispensingStreak = 0; brewingUsesRealSignal = false; if(brewingActive)drinksToday++;
  } else if (drink == "coffee_stop") {
    uint8_t cmd[] = {0x0d,0x0b,0x82,0xf0,0x02,0x04,0x01,0x98,0x00,0x00,0x32,0x8c};
    sendRawToMachine(cmd, sizeof(cmd));
    brewingActive = false;
  } else if (drink == "hot_water") {
    uint8_t cmd[] = {0x0d,0x0b,0x82,0xf0,0x10,0x01,0x02,0xbc,0x00,0x00,0x32,0xbc};
    sendRawToMachine(cmd, sizeof(cmd));
    brewingActive = (machineState == "ready"); brewingName = "Гаряча вода"; brewingStartedAt = millis(); brewProgressRaw = 0; lastBrewProgressPct = 0xFF; notDispensingStreak = 0; brewingUsesRealSignal = false; if(brewingActive)drinksToday++;
  } else if (drink == "hot_water_stop") {
    uint8_t cmd[] = {0x0d,0x0b,0x82,0xf0,0x10,0x04,0x02,0xbc,0x00,0x00,0x32,0xb9};
    sendRawToMachine(cmd, sizeof(cmd));
    brewingActive = false;
  } else if (drink == "cappuccino") {
    float ml = savedCappuccinoMl, sec = savedCappuccinoMilkSec; uint8_t lvl = (uint8_t)savedCappuccinoStrength;
    if (paramSource != 0) { if (!readFromActiveProfile(0x07, &ml, &sec, &lvl)) { ml = savedCappuccinoMl; sec = savedCappuccinoMilkSec; lvl = (uint8_t)savedCappuccinoStrength; } }
    uint8_t cmd[12];
    buildRecipeCmd(cmd, 0x07, 0x01, ml, sec, lvl);
    sendRawToMachine(cmd, sizeof(cmd));
    brewingActive = (machineState == "ready"); brewingName = "Капучино"; brewingStartedAt = millis(); brewProgressRaw = 0; lastBrewProgressPct = 0xFF; notDispensingStreak = 0; brewingUsesRealSignal = false; if(brewingActive)drinksToday++;
  } else if (drink == "cappuccino_stop") {
    uint8_t cmd[] = {0x0d,0x0b,0x82,0xf0,0x07,0x04,0x00,0xb4,0x00,0xbe,0x32,0x1a};
    sendRawToMachine(cmd, sizeof(cmd));
    brewingActive = false;
  } else if (drink == "profile_cycle") {
    // v4.27: mirrors the web dashboard's "🔌 Увімкнути"/"📍 Профіль N"
    // cycling button exactly — ESP32(0) -> Профіль 1 -> 2 -> ... -> 6 ->
    // back to ESP32. Only sends the A9F0 machine profile-switch when
    // landing on an actual profile (1-6); going back to ESP32(0) just
    // changes which values WE source from locally, nothing to tell the
    // machine. Published to MQTT so HA/voice can show or announce the
    // current source (see publishParamSource()).
    paramSource = (paramSource + 1) % 7;
    if (paramSource != 0) sendProfileSwitch(paramSource);
    publishParamSource();
  } else {
    if (Serial) { Serial.println("--- Unknown command: " + drink + " ---");
    Serial.println("--- Unknown command: " + drink + " ---"); }
  }
}

void mqttCallback(char* topic, byte* payload, unsigned int length) {
  String msg;
  for (unsigned int i = 0; i < length; i++) msg += (char)payload[i];
  if (Serial) { Serial.println("MQTT command received: " + msg);
  Serial.println("MQTT command received: " + msg); }
  sendDrinkCommand(msg);
}

// Home Assistant MQTT Discovery: one state sensor + one button per drink.
// Published (retained) each time we (re)connect to the broker, so HA
// picks up the entities automatically without manual YAML.
void mqttPublishDiscovery() {
  String devBlock = "\"device\":{\"identifiers\":[\"delonghi_c6_mitm\"],\"name\":\"DeLonghi PrimaDonna\",\"manufacturer\":\"De'Longhi\"}";

  String sensorCfg = "{\"name\":\"Стан кавомашини\",\"unique_id\":\"delonghi_state\",\"object_id\":\"delonghi_state\","
    "\"state_topic\":\"" MQTT_STATE_TOPIC "\",\"availability_topic\":\"" MQTT_AVAIL_TOPIC "\"," + devBlock + "}";
  bool ok1 = mqtt.publish("homeassistant/sensor/delonghi_c6/state/config", sensorCfg.c_str(), true);
  if (Serial) { Serial.printf("Sensor discovery publish: %s (len=%d)\n", ok1 ? "OK" : "FAILED", sensorCfg.length());
  Serial.printf("Sensor discovery publish: %s (len=%d)\n", ok1 ? "OK" : "FAILED", sensorCfg.length()); }

  // v4.27: profile/ESP32 indicator sensor — shows which source
  // sendDrinkCommand() currently reads brewing parameters from.
  String paramSrcCfg = "{\"name\":\"Джерело параметрів\",\"unique_id\":\"delonghi_param_source\",\"object_id\":\"delonghi_param_source\","
    "\"state_topic\":\"" MQTT_PARAM_SOURCE_TOPIC "\",\"availability_topic\":\"" MQTT_AVAIL_TOPIC "\"," + devBlock + "}";
  bool okPs = mqtt.publish("homeassistant/sensor/delonghi_c6/param_source/config", paramSrcCfg.c_str(), true);
  if (Serial) { Serial.printf("Param source discovery publish: %s (len=%d)\n", okPs ? "OK" : "FAILED", paramSrcCfg.length());
  Serial.printf("Param source discovery publish: %s (len=%d)\n", okPs ? "OK" : "FAILED", paramSrcCfg.length()); }
  publishParamSource();  // republish current value immediately so HA never shows stale/blank after a reconnect

  // Image entity (HA's MQTT Image integration): points at a static URL
  // rather than pushing image bytes ourselves. Same real machine photo
  // used on our own web dashboard.
  String imageCfg = "{\"name\":\"Фото машини\",\"unique_id\":\"delonghi_image\",\"object_id\":\"delonghi_image\","
    "\"url_topic\":\"delonghi/image_url\",\"availability_topic\":\"" MQTT_AVAIL_TOPIC "\"," + devBlock + "}";
  bool okImg = mqtt.publish("homeassistant/image/delonghi_c6/image/config", imageCfg.c_str(), true);
  if (Serial) { Serial.printf("Image discovery publish: %s (len=%d)\n", okImg ? "OK" : "FAILED", imageCfg.length());
  Serial.printf("Image discovery publish: %s (len=%d)\n", okImg ? "OK" : "FAILED", imageCfg.length()); }
  mqtt.publish("delonghi/image_url",
    "https://delonghibe.s3.eu-west-1.amazonaws.com/cms/prod/img/_opt_delonghi_uploads_elite_best_front.png", true);

  struct { const char* id; const char* name; } buttons[] = {
    {"power_on", "Увімкнути"},
    {"coffee", "Кава"},
    {"coffee_stop", "Стоп кави"},
    {"espresso", "Еспресо"},
    {"espresso_stop", "Стоп еспресо"},
    {"hot_water", "Гаряча вода"},
    {"hot_water_stop", "Стоп гарячої води"},
    {"latte_macchiato", "Латте Макіато"},
    {"latte_macchiato_stop", "Стоп латте макіато"},
    {"cappuccino", "Капучино"},
    {"cappuccino_stop", "Стоп капучино"},
    {"profile_cycle", "Профіль (по колу)"},
  };
  for (auto& b : buttons) {
    String cfg = "{\"name\":\"" + String(b.name) + "\",\"unique_id\":\"delonghi_" + String(b.id) + "\","
      "\"object_id\":\"delonghi_" + String(b.id) + "\","
      "\"command_topic\":\"" MQTT_CMD_TOPIC "\",\"payload_press\":\"" + String(b.id) + "\","
      "\"availability_topic\":\"" MQTT_AVAIL_TOPIC "\"," + devBlock + "}";
    String topic = "homeassistant/button/delonghi_c6_" + String(b.id) + "/config";
    bool ok2 = mqtt.publish(topic.c_str(), cfg.c_str(), true);
    if (Serial) { Serial.printf("Button discovery %s: %s (len=%d)\n", b.id, ok2 ? "OK" : "FAILED", cfg.length());
    Serial.printf("Button discovery %s: %s (len=%d)\n", b.id, ok2 ? "OK" : "FAILED", cfg.length()); }
  }
  if (Serial) { Serial.println("MQTT discovery published");
  Serial.println("MQTT discovery published"); }
}

void mqttReconnect() {
  if (mqttHost.length() == 0) return;  // not configured yet
  if (Serial) { Serial.println("Connecting to MQTT " + mqttHost + ":" + String(mqttPort) + "...");
  Serial.println("Connecting to MQTT " + mqttHost + ":" + String(mqttPort) + "..."); }
  mqtt.setServer(mqttHost.c_str(), mqttPort);
  mqtt.setCallback(mqttCallback);
  // Default PubSubClient buffer is only 256 bytes — our discovery JSON
  // (with Cyrillic names, 2 bytes/char in UTF-8) exceeds that, causing
  // publish() to silently fail with no error. Bump it up.
  mqtt.setBufferSize(768);
  bool ok;
  if (mqttUser.length() > 0) {
    ok = mqtt.connect(HOSTNAME, mqttUser.c_str(), mqttPass.c_str(), MQTT_AVAIL_TOPIC, 0, true, "offline");
  } else {
    ok = mqtt.connect(HOSTNAME, MQTT_AVAIL_TOPIC, 0, true, "offline");
  }
  if (ok) {
    if (Serial) { Serial.println("MQTT connected");
    Serial.println("MQTT connected"); }
    mqtt.subscribe(MQTT_CMD_TOPIC);
    mqtt.publish(MQTT_AVAIL_TOPIC, "online", true);
    mqttPublishDiscovery();
    // FIX: publishMachineState() only publishes on an actual change (vs
    // its own in-memory tracking), so after a disconnect/reconnect where
    // the real machine state didn't change at all, HA's sensor could be
    // left stuck on a stale/unavailable value indefinitely — confirmed
    // by user-observed history showing repeated ready/Недоступно/Невідомо
    // flickering. Force a fresh publish here, bypassing the change-check,
    // so HA always gets an accurate value immediately on every reconnect.
    if (machineState.length() > 0) {
      mqtt.publish(MQTT_STATE_TOPIC, machineState.c_str(), true);
      lastMqttPublishAt = millis();
    }
  } else {
    if (Serial) { Serial.printf("MQTT connect failed, rc=%d\n", mqtt.state());
    Serial.printf("MQTT connect failed, rc=%d\n", mqtt.state()); }
  }
}

void webSocketEvent(uint8_t num, WStype_t type, uint8_t* payload, size_t length) {
  // No client->server messages needed yet; connection tracking is enough.
}

void broadcastLiveState() {
  if (webSocket.connectedClients() == 0) return;
  unsigned long age = lastUpdate > 0 ? (millis() - lastUpdate) / 1000 : 0;
  int pct = brewingActive ? brewProgressRaw : 0;
  int warmupPct = 0;
  // FIXED: plain coffee brewing genuinely reports flag=01/03 through
  // byte[8] — the SAME values as idle asleep/waking — unlike milk drinks
  // which use 02/04. Without this guard, isWarming would incorrectly
  // interrupt the cup-fill animation with the warmup icon mid-brew
  // (confirmed via 2_кави_стоп.txt: cup showed 0%→100%→warmup→100%).
  // brewingActive (our own client-side tracking of "we just sent a real
  // brew command") takes priority — a genuine warmup only counts if we're
  // not already actively brewing.
  bool isWarming = (machineState == "waking") && !brewingActive;
  if (isWarming) warmupPct = warmupProgressRaw;
  // Wake-prompt should only appear as a REACTION to pressing a drink
  // button while not ready — not as a permanent "not ready" indicator
  // (that's what the state line already shows). Auto-hides 20s after the
  // press if the user never actually turns the machine on.
  bool showWakePrompt = (machineState != "ready") &&
                         (lastDrinkPressAt > 0) && (millis() - lastDrinkPressAt < 20000);
  String json = "{";
  json += "\"machineConnected\":" + String(machineConnected ? "true" : "false") + ",";
  json += "\"phoneConnected\":" + String(phoneConnected ? "true" : "false") + ",";
  json += "\"machineState\":\"" + machineState + "\",";
  json += "\"mqttConnected\":" + String(mqtt.connected() ? "true" : "false") + ",";
  json += "\"packetCount\":" + String(packetCount) + ",";
  json += "\"age\":" + String(age) + ",";
  json += "\"brewingActive\":" + String(brewingActive ? "true" : "false") + ",";
  json += "\"brewingName\":\"" + brewingName + "\",";
  json += "\"brewingPct\":" + String(pct) + ",";
  json += "\"isWarming\":" + String(isWarming ? "true" : "false") + ",";
  json += "\"warmupPct\":" + String(warmupPct) + ",";
  json += "\"showWakePrompt\":" + String(showWakePrompt ? "true" : "false") + ",";
  json += "\"waterMessage\":\"" + waterMessage + "\",";
  json += "\"milkMessage\":\"" + milkMessage + "\",";
  json += "\"groundsMessage\":\"" + groundsMessage + "\",";
  json += "\"waterState\":\"" + waterState + "\",";
  json += "\"groundsState\":\"" + groundsState + "\",";
  json += "\"milkState\":\"" + milkState + "\",";
  json += "\"beansMessage\":\"" + beansMessage + "\",";
  json += "\"beansState\":\"" + beansState + "\",";
  // Publish a combined "what needs attention" type to MQTT, for HA to
  // trigger the matching WLED preset (water/grounds/beans icons, 14/15/16).
  // Priority: water > grounds > beans (matches the existing on-page icon
  // priority chain).
  // v4.25 FIX: this function (broadcastLiveState) runs on a ~500ms timer
  // for the web dashboard, unrelated to how often real new BLE status data
  // actually arrives — so simply removing the "only on change" gate would
  // spam MQTT at ~2 msg/s continuously, which is not okay (MQTT broker,
  // HA history, retained-message writes). Confirmed live: the retained
  // delonghi/attention_type message got stuck non-empty because it's only
  // ever republished on an actual STRING change, and the underlying issue
  // that got fixed (grounds container really did clear) can happen without
  // attentionType's computed value changing in between — nothing to
  // trigger a fresh publish. Fix: keep the on-change publish (instant,
  // same as before) AND add a bounded heartbeat — republish the SAME
  // value at most once every 30s regardless of change. Worst case this
  // adds one extra tiny retained publish per 30s (negligible), but it
  // means the HA-side sensor's expire_after (see delivered YAML) never
  // times out while the firmware is genuinely alive and computing fresh
  // values each time — self-healing any future stuck-value scenario
  // within 30s instead of needing a manual MQTT publish to unstick it.
  {
    static String lastAttentionType = "(unset)";
    static unsigned long lastAttentionPublishAt = 0;
    String attentionType = "";
    if (waterState == "missing" || waterState == "low") attentionType = "water";
    else if (groundsState == "full" || groundsState == "missing") attentionType = "grounds";
    else if (beansState == "empty") attentionType = "beans";
    bool changed = (attentionType != lastAttentionType);
    bool heartbeatDue = (millis() - lastAttentionPublishAt > 30000);
    if (changed || heartbeatDue) {
      lastAttentionType = attentionType;
      lastAttentionPublishAt = millis();
      if (mqtt.connected()) mqtt.publish("delonghi/attention_type", attentionType.c_str(), true);
      lastMqttPublishAt = millis();
    }
  }
  // First active MonitorV1 alarm eligible for the main page, in priority
  // order (bits 2,3,4,8,17) — empty string if none active. This slot sits
  // below the existing water/grounds/beans icons and above milk in the
  // client-side priority chain (see the JS below).
  String monitorAlarmText = "";
  {
    const uint8_t mainPageBits[] = {2, 3, 4, 8, 17};
    for (int i = 0; i < 5 && monitorAlarmText == ""; i++) {
      if (alarmActive(mainPageBits[i])) {
        for (int j = 0; j < ALARM_TABLE_LEN; j++) {
          if (ALARM_TABLE[j].bit == mainPageBits[i]) { monitorAlarmText = ALARM_TABLE[j].text; break; }
        }
      }
    }
  }
  json += "\"monitorAlarmText\":\"" + monitorAlarmText + "\"";
  json += "}";
  webSocket.broadcastTXT(json);
}

// Display-only decoration for machineState — the raw value (asleep/waking/
// ready/offline/unknown) is still what MQTT publishes and what all our own
// logic compares against; this is purely for the web dashboard's initial
// server-rendered HTML (the live WS updates use the equivalent JS map).
String prettyState(const String& s) {
  if (brewingActive) return s + "/готується 🥳";
  if (s == "asleep") return "asleep/спить 😴";
  if (s == "waking") return "waking/просипається 🤔";
  if (s == "ready") return "ready/готова 🙂";
  if (s == "offline") return "offline/офлайн ❌";
  return s + "/невідомо ❓";
}

void publishMachineState(const String& newState) {
  if (newState == machineState) return;
  machineState = newState;
  if (Serial) { Serial.println("Machine state -> " + machineState);
  Serial.println("Machine state -> " + machineState); }
  if (mqtt.connected()) { mqtt.publish(MQTT_STATE_TOPIC, machineState.c_str(), true); lastMqttPublishAt = millis(); }
  if (newState == "ready") brewingActive = false;
  if (newState == "waking") { warmupProgressRaw = 0; warmupProgressMax = 100; }
}

// v4.27: human-readable label for the current brewing-parameter source
// (mirrors the existing web UI's sourceLabels[] array), published to MQTT
// so HA/voice can show or announce which profile is currently active —
// same info the physical "🔌 Увімкнути"/"📍 Профіль N" button already
// shows on the web dashboard, just also exposed outside the browser now.
String paramSourceLabel() {
  if (paramSource == 0) return "ESP32";
  return "Профіль " + String(paramSource);
}

void publishParamSource() {
  if (mqtt.connected()) { mqtt.publish(MQTT_PARAM_SOURCE_TOPIC, paramSourceLabel().c_str(), true); lastMqttPublishAt = millis(); }
}

// Shared status-flag extraction: called whenever a fully-assembled packet
// turns out to be a status-poll response, regardless of who triggered the
// poll (CoffeeLink, through the bridge, or our own self-poll below).
char lastAnyPacketBuf[128] = "(ще нічого не отримано)";
unsigned long lastAnyPacketAt = 0;

void maybeParseStatus(uint8_t* fullPkt, int fullLen) {
  // Diagnostic (v4.04, perf-fixed v4.05): capture EVERY incoming packet as
  // hex, regardless of opcode — lets us see on /info whether the machine
  // responds AT ALL to a command we just sent, without USB. v4.04 built
  // this with Arduino String concatenation PER PACKET, which runs every
  // ~500ms via the normal status-poll cycle — String's repeated
  // reallocation is slow and fragments heap, causing the reported web
  // sluggishness. Fixed: write directly into a fixed char buffer instead,
  // no String involved, no reallocation.
  {
    int cap = fullLen; if (cap > 20) cap = 20;  // 128-byte buffer, 3 chars/byte + margin
    int pos = 0;
    for (int i = 0; i < cap && pos < 120; i++) {
      pos += snprintf(lastAnyPacketBuf + pos, sizeof(lastAnyPacketBuf) - pos, "%02x ", fullPkt[i]);
    }
    lastAnyPacketAt = millis();
  }
  // MonitorV1 (byte[2]==0x70) — separate, simpler packet. 32-bit LE alarm
  // bitmask starting at byte[4] (4 bytes). byte[8]/byte[9] ("Function
  // OnGoing"/"Execution Program" per APK decompilation) — INITIALLY
  // thought irrelevant, but confirmed critical: official CoffeeLink
  // refuses to send a recipe SAVE unless byte[8]==7 && byte[9]==0 at
  // that moment (`monitorData.o()` gate in BrewBeveragesViewModel.t()).
  // Tracked now so our own SAVE commands can respect the same gate.
  if (fullLen >= 10 && fullPkt[2] == 0x70) {
    monitorV1Alarms = (uint32_t)fullPkt[4] | ((uint32_t)fullPkt[5] << 8) |
                       ((uint32_t)fullPkt[6] << 16) | ((uint32_t)fullPkt[7] << 24);
    monitorFuncCode = fullPkt[8];
    monitorExecCode = fullPkt[9];
  }
  // A6F0 read-quantities response (v4.02) — confirmed 11-byte format:
  // d0 09 A6 F0 recipeId water_hi water_lo milk_hi milk_lo combined checksum
  if (fullLen >= 11 && fullPkt[2] == 0xA6 && fullPkt[3] == 0xF0) {
    lastA6F0Echo4 = fullPkt[4];  // v4.03: uncertain whether this echoes profileId or recipeId now that the request layout changed — see handleProfilePeek
    uint16_t waterRaw = ((uint16_t)fullPkt[5] << 8) | fullPkt[6];
    uint16_t milkRaw = ((uint16_t)fullPkt[7] << 8) | fullPkt[8];
    uint8_t combined = fullPkt[9];
    lastA6F0Ml = waterRaw / 2.0;
    lastA6F0Sec = milkRaw / 10.0;
    // upper nibble = raw strength (level*16); decode back to 1-5
    lastA6F0StrengthLevel = (combined & 0xF0) >> 4;
    lastA6F0Fresh = true;
  }
  if (fullLen >= 10 && fullPkt[1] == 0x1a && fullPkt[2] == 0x75 && fullPkt[3] == 0x0f) {
    // v4.11 CRITICAL FIX: func/exec (the SAVE-persistence gate) were being
    // read from byte[8]/byte[9], which are ONLY valid for MonitorData v1
    // (opcode 0x70) per MonitorData.java's e()/f() — `i10 = (version==1) ?
    // 9 : 20` / `i10 = (version==1) ? 8 : 19`. This machine apparently
    // never sends opcode 0x70 at all — it only sends v2 (this very 0x75
    // packet, the same one byte[25]=% has always come from), where func/
    // exec actually live at byte[19]/byte[20], not byte[8]/byte[9]. This
    // is why the gate NEVER opened no matter how long we waited — we were
    // reading the wrong offset of a packet type the machine doesn't send.
    if (fullLen >= 21) {
      static uint8_t lastLoggedFunc = 0xFF, lastLoggedExec = 0xFF;
      static unsigned long lastFuncExecLogAt = 0;
      // v4.31: pure diagnostic — logs func/exec on change, throttled.
      // v4.33: real captured data showed func/exec changing almost every
      // few seconds (much noisier than assumed), so on-every-change alone
      // could fire quite often during active periods — added a 1s minimum
      // gap on top of the change check, safe since we only need this for
      // eyeballing broad transitions, not sub-second precision.
      if ((fullPkt[19] != lastLoggedFunc || fullPkt[20] != lastLoggedExec) &&
          millis() - lastFuncExecLogAt > 1000) {
        lastLoggedFunc = fullPkt[19];
        lastLoggedExec = fullPkt[20];
        lastFuncExecLogAt = millis();
        debugLog("func/exec changed: func=%d exec=%d (pct=%d, state=%s)",
                 fullPkt[19], fullPkt[20],
                 (fullLen >= 26 ? fullPkt[25] : 0), machineState.c_str());
      }
      monitorFuncCode = fullPkt[19];
      monitorExecCode = fullPkt[20];
    }
    uint8_t flag = fullPkt[9];
    // v4.23 FIX: primary brew-detection signal is now func==7 && exec!=0
    // (monitorFuncCode/monitorExecCode, just populated above) — the SAME
    // fields the official CoffeeLink app itself checks (found via APK
    // decompilation of BrewBeveragesViewModel's S(MonitorData) method,
    // its dispensingStarted gate: `if (!monitorData.o())` where o() means
    // func==7 && exec==0). This is authoritative, not a heuristic: exec==0
    // specifically means "still grinding/preparing, don't trust the
    // percentage yet" per the official app's own logic — exec!=0 (while
    // func==7) means real dispensing has genuinely started. Two big wins
    // over the old pct-trend-only approach: (1) no longer fooled by any
    // percentage noise/movement during grinding, since exec==0 is excluded
    // outright regardless of what byte[25] shows; (2) fires on the FIRST
    // real dispensing packet instead of needing 2 consecutive polls to
    // confirm a trend, since it's a direct state read, not a noisy trend.
    // Completely unaffected by the base-byte (fullPkt[9]) asleep/waking/
    // ready ambiguity too, since func/exec live at a different offset.
    // Fallback: the original rising-%-trend check only kicks in on the
    // rare chance we haven't seen a single valid func/exec reading yet
    // this session (monitorFuncCode's 0xFF "never seen" sentinel — e.g.
    // right after a fresh BLE connect before the first full-length packet
    // has arrived). Kept exactly as tuned before (2 consecutive rises,
    // low range <50, avoiding the confirmed real end-of-warmup ~80->100
    // ramp false-positive) purely as a safety net for that narrow window.
    uint8_t pct = (fullLen >= 26) ? fullPkt[25] : 0;
    // v4.34: added func==11 && exec==3 — CONFIRMED live against a real hot
    // water brew (matched exactly, timestamp-correlated) and independently
    // confirmed via smali-level (not just Java) decompilation as the
    // dedicated "disp_hot_water_delivery" signal, separate from the
    // func==7 coffee/espresso/cappuccino/latte family. This also explains
    // a previously-mysterious bug: Hot Water never showed a percentage on
    // web/matrix when brewed passively, because detection only ever
    // checked func==7 and Hot Water simply never uses it.
    bool realDispensing = (monitorFuncCode == 7 && monitorExecCode != 0) ||
                           (monitorFuncCode == 11 && monitorExecCode == 3);
    bool brewTrendConfirmed = (pct > 0 && pct < 50 && lastPassivePct > 0 &&
                                lastPassivePct < 50 && pct > lastPassivePct);
    lastPassivePct = pct;
    // v4.24 FIX: v4.23's fallback was a one-time thing — "use trend ONLY
    // until we've seen a single valid func/exec reading this session" —
    // but monitorFuncCode goes non-0xFF almost immediately (first full
    // packet) and stays that way for the rest of the session REGARDLESS
    // of whether that particular func value ever applies to the CURRENT
    // drink. Confirmed live: Hot Water showed no percentage at all (on
    // web or matrix) when started from the machine's own button — most
    // likely because Hot Water routes through a different func code than
    // the func==7 the app uses for coffee/espresso/etc (recall the
    // decompiled icon-selector had a separate `exec == 11` branch called
    // out specifically for hot water). Once func/exec had already been
    // seen for a DIFFERENT (non-brewing) reason earlier in the session,
    // v4.23's fallback never got a chance to run for Hot Water at all.
    // Fix: trend is now a permanent, parallel OR — evaluated every packet
    // regardless of whether func/exec has been seen before, alongside
    // (not instead of) the func/exec check. For espresso/coffee/etc,
    // realDispensing still fires on the very first exec!=0 packet, well
    // before the trend could even accumulate its 2-poll confirmation, so
    // grinding stays protected exactly as in v4.23. Hot Water (or any
    // other recipe not covered by func==7) now falls back to the trend
    // check on every packet, not just a narrow one-time startup window.
    bool brewConfirmedNow = realDispensing || brewTrendConfirmed;
    if (fullLen >= 26 && !brewingActive && brewConfirmedNow) {
      brewingActive = true;
      brewingName = "Напій";  // unknown which drink — wasn't our own command
      brewingStartedAt = millis();
      lastBrewProgressPct = 0xFF;
      drinksToday++;
      notDispensingStreak = 0;
      brewingUsesRealSignal = realDispensing;  // armed via the trustworthy
                                                // byte signal, not just trend
    }
    // v4.37 FIX: found a foundational bug that predates this whole
    // detection rework — brewingActive was ONLY ever cleared inside
    // publishMachineState("ready"), specifically the `if (newState ==
    // "ready") brewingActive = false;` line. But that function early-
    // returns immediately (`if (newState == machineState) return;`)
    // whenever the state string isn't actually CHANGING — and the
    // priority branch that runs every single packet while brewing
    // (`if (brewingActive) publishMachineState("ready");`) always calls
    // it with "ready" while machineState is *already* "ready" (the
    // normal case: you always start brewing from "ready"). So that call
    // early-returns EVERY time, and the clear line is never reached —
    // brewingActive had no real path back to false on a normal brew
    // completion, only the blunt 5-minute safety cap further down ever
    // rescued it. This got far worse once v4.36 gated self-poll on
    // !brewingActive too: a stuck-true flag now also permanently
    // silenced self-poll, and since the machine itself goes quiet once
    // genuinely idle, the whole bridge would freeze solid until the
    // 5-minute cap fired — confirmed live with Hot Water (drinksToday
    // incremented correctly on start, then everything — func/exec,
    // state, % — froze until roughly the cap kicked in).
    // Fix: track dispensing stopping directly, independent of any state-
    // string transition. Only trusted once brewingUsesRealSignal is true
    // (the func/exec byte signal actually confirmed at least once for
    // THIS brew — e.g. Hot Water's func==11/exec==3) — for a brew armed
    // only via the %-trend fallback (some recipe not yet mapped to a
    // known func code), realDispensing is always false by definition and
    // "clearing after 5 non-dispensing reads" would trigger almost
    // immediately after arming, wrongly cutting off tracking seconds into
    // a real brew. Those cases still fall back to the 5-minute cap below.
    // Once trusted, requires 5 CONSECUTIVE non-dispensing readings (not
    // just one) so a brief protocol blip or a pause between multi-stage
    // recipe steps doesn't end tracking early — but once truly finished
    // this now clears within a handful of packets (seconds), not minutes.
    if (brewingActive && brewingUsesRealSignal) {
      if (realDispensing) {
        notDispensingStreak = 0;
      } else if (++notDispensingStreak >= 5) {
        brewingActive = false;
      }
    }
    // Mask off the attention-issue bits (0x08 grounds, 0x10 water, 0x40
    // seen during the post-wake transient) to get the underlying base
    // wake-state — otherwise composite flags (e.g. 0x15 = ready+water)
    // never match the old strict flag==0x05 check, and machineState gets
    // stuck on whatever it last was, leaving the "increase machine"
    // prompt hanging even once the machine is actually ready.
    uint8_t base = flag & 0x07;
    // Coffee's brewing quirk reports the SAME raw base value as
    // asleep/waking (0x00/0x01/0x03), which would otherwise make
    // machineState — and therefore the delonghi/state MQTT topic —
    // briefly claim the machine is asleep/waking mid-brew. Since we
    // already KNOW for certain a brew is active (brewingActive), that's
    // more reliable ground truth than the ambiguous raw flag — force
    // "ready" instead, so downstream consumers (e.g. the WLED weather
    // automation, which checks state=="asleep") don't get spuriously
    // triggered mid-brew.
    if (brewingActive) {
      publishMachineState("ready");
    } else if ((base == 0x00 || base == 0x01) && monitorFuncCode != 0xFF && monitorFuncCode != 0) {
      // v4.38 FIX: confirmed live that Hot Water (and likely other
      // recipes) has an earlier phase — heating the water — BEFORE
      // dispensing actually starts (before func==11/exec==3 arms
      // brewingActive above). During that window brewingActive is still
      // false, so the base-byte asleep/waking classification below ran
      // unprotected and picked up the same protocol ambiguity already
      // fixed for confirmed brewing — causing repeated real asleep<->
      // waking flips and voice-announcement spam (3x "asleep", 3x
      // "ready" for one Hot Water pour).
      // v4.39 FIX: v4.38's first attempt suppressed ALL classification
      // whenever func!=0 — but confirmed func is ALSO non-zero (func==1)
      // throughout completely normal warmup, which would have silently
      // broken warmup detection entirely (no more "waking" state, no
      // more warmup animation/announcement). Narrowed to ONLY suppress
      // the ASLEEP side (base==0x00/0x01) when func indicates activity —
      // waking (0x03) and ready (0x05) below are completely unaffected
      // and still fire exactly as before. Using the same fact confirmed
      // via decompilation (func==0 is the authoritative STANDBY/idle
      // signal) but applied narrowly: don't let the ambiguous base byte
      // claim "asleep" while func says busy — hold state instead (no
      // publish), which still lets a genuine "waking"/"ready" reading on
      // the very next packet through normally.
    } else if (base == 0x00 || base == 0x01) {
      // v4.20 FIX: DeLonghi's own status byte reports the SAME base
      // value for asleep/waking (0x00/0x01) as it briefly does right as
      // the machine finishes warming up — the same family of protocol
      // quirk as the brewing case handled just above. A machine that
      // was just "waking" going straight back to "asleep" on its own,
      // within the same warmup cycle, is effectively never real —
      // treat it as the same phantom transient and don't publish it,
      // letting the next (correct) "ready" reading through instead.
      // v4.26 FIX: v4.20's guard was WAY too broad — "if machineState !=
      // waking" means once state becomes "waking", a real asleep/off can
      // NEVER be published again, ever, for as long as state stays
      // "waking" — confirmed live: machine was genuinely asleep, matrix +
      // web stuck showing "waking/Прогрів" indefinitely, because every
      // single real asleep reading kept getting silently dropped by this
      // exact guard. A genuine phantom blip is a single isolated reading
      // (the very next real poll shows 0x03-still-waking or 0x05-ready);
      // real asleep/off keeps reading 0x00/0x01 on every subsequent poll
      // indefinitely. So: require the SAME asleep-looking reading on 2
      // consecutive polls while in "waking" before trusting it — a
      // one-shot phantom blip still gets filtered (next poll breaks the
      // streak via the 0x03/0x05 branches below), but a real, sustained
      // asleep-while-waking situation now correctly gets through instead
      // of being stuck forever.
      if (machineState != "waking") {
        publishMachineState("asleep");
        wakingAsleepStreak = 0;
      } else if (++wakingAsleepStreak >= 2) {
        publishMachineState("asleep");
      }
    }
    else if (base == 0x03) { wakingAsleepStreak = 0; publishMachineState("waking"); }
    else if (base == 0x05) { wakingAsleepStreak = 0; publishMachineState("ready"); }
    // Attention detection: LEFT-side text distinguishes the SPECIFIC
    // condition (missing vs low/full); RIGHT-side icon slot only cares
    // about the CATEGORY (water vs grounds), reusing the same icon shape
    // for both variants of each — see iconSlot JS logic below.
    waterMessage = ""; milkMessage = ""; groundsMessage = ""; waterState = ""; groundsState = ""; milkState = "";
    beansMessage = ""; beansState = "";
    // Confirmed via нет_кофе.txt: fullPkt[11]==0x20 held stable ~70s
    // (20 samples) INDEPENDENT of the base flag (seen with 03/01/05 all)
    // — genuinely distinct from the flag==0x04 "reason" sub-code which
    // uses fullPkt[10]. FIXED (v3.71): originally miswrote this as
    // fullPkt[10] (off-by-one from a Python-vs-firmware indexing mixup —
    // Python analysis excluded the leading d0 marker byte, firmware's
    // array includes it), which meant this never actually fired.
    if (fullLen >= 12 && fullPkt[11] == 0x20) {
      beansMessage = "☕ Немає кавових зерен!";
      beansState = "empty";
      beansStickyUntil = millis() + 60000;  // sticky window: up to 1 min
      beansStickyPressSnapshot = lastDrinkPressAt;
    } else if (millis() < beansStickyUntil && lastDrinkPressAt == beansStickyPressSnapshot) {
      // Real signal window is short (~20s, tied to the grinder's motor-load
      // test during an actual grind attempt) and easy to miss — keep
      // showing for up to 1 minute after last seen, UNLESS a NEW drink
      // button press happens first (that resets/clears it immediately).
      beansMessage = "☕ Немає кавових зерен!";
      beansState = "empty";
    }
    if (flag == 0x04 && fullLen >= 11) {
      uint8_t reason = fullPkt[10];
      if (reason == 0x00) { milkMessage = "🥛 Встав контейнер з молоком!"; milkState = "missing"; }
      else if (reason == 0x01) { waterMessage = "💧 Встав контейнер для води!"; waterState = "missing"; }
      else if (reason == 0x05) { milkMessage = "🥛 Промий молочник!"; milkState = "clean"; }
    }
    if (flag & 0x08) {
      // Confirmed via гуща.txt: perfectly clean 0x09 (0x01|0x08) while
      // asleep, toggling exactly with the grounds container in/out —
      // 6/6 matches against user-provided timestamps.
      groundsMessage = "🗑️ Встав контейнер для гущі!";
      groundsState = "missing";
    }
    // Confirmed via жмаки.txt (natural occurrence + adb cross-check against
    // CoffeeLink's own "COFFEE_WASTE_CONTAINER_FULL" log): while the
    // machine reports ready (flag=0x05), fullPkt[11]==0x02 means the
    // grounds container is full — held stable for many minutes, distinct
    // from the flag&0x08 "container missing" bit above.
    if (flag == 0x05 && fullLen >= 12 && fullPkt[11] == 0x02) {
      groundsMessage = "🗑️ Контейнер гущі повний!";
      groundsState = "full";
    }
    if ((flag & 0x10) && groundsMessage == "") {
      // Confirmed via water.txt: while asleep, water-missing shows as
      // 0x11 (0x01|0x10) rather than the awake-state 0x04. Also confirmed
      // via нет_воды.txt: this same 0x10 bit reappears on the READY
      // base-state too (0x15=0x10|0x05). User confirmed the machine's own
      // screen prioritizes grounds over water when both apply — mirrored
      // here (only show water if grounds message isn't already set).
      waterMessage = "💧 Встав контейнер для води!";
      waterState = "missing";
    } else if ((flag == 0x41 || flag == 0x43 || flag == 0x45) && groundsMessage == "") {
      // FIXED: was checking fullPkt[10]==0x01, which does NOT match the
      // now DEFINITIVELY confirmed EMPTY_WATER_TANK sample (flag=0x41,
      // fullPkt[10]=0x00) — cross-verified against CoffeeLink's own
      // "Found 1 errors: EMPTY_WATER_TANK" log at the exact same
      // timestamp, held stable 3.5+ minutes, in both adb log and our own
      // Serial log. This is NOT a brief post-wake transient as earlier
      // (less certain) data suggested — it persists as long as the real
      // condition does. Checking the flag value directly now instead.
      waterMessage = "💧 Закінчується вода!";
      waterState = "low";
    }
    // CONFIRMED via CoffeeLink's own adb logcat (BrewBeveragesViewModel
    // logs "Fun OnGoing / Exe Prog / Percent" alongside the raw bytes):
    // fullPkt[25] IS the real dispensing percentage, 0-100 directly, no
    // scaling needed. Verified against 3 real samples (50/94/100), exact
    // match every time. This replaces ALL the earlier guesswork (the old
    // fullPkt[18] "ramping counter" and the fixed-per-drink-max estimates)
    // — those were reading the wrong field entirely.
    if (fullLen >= 26) {
      // v4.21: pct already read and brewingActive already armed/checked
      // above, BEFORE the state classification — see the note there.
      // This block now only publishes the progress value and tracks
      // warmupProgressRaw.
      if (brewingActive) {
        brewProgressRaw = pct;
        // Heuristic guard: a physical STOP press on the machine itself is
        // invisible to us (nothing sent to our bridge), so brewingActive
        // can't be cleared in time — the machine's own byte[25] reverts to
        // noise/idle almost immediately once dispensing genuinely stops,
        // and a sudden drop to exactly 0 right after a meaningfully
        // non-zero reading is the most common symptom (matches user's
        // report: cup goes empty right when physically pressing Stop).
        // Skip publishing (and don't update lastBrewProgressPct) in that
        // specific case, so a real subsequent value still gets through
        // normally. lastBrewProgressPct is reset to 0xFF at every genuine
        // brew start (both here and in sendDrinkCommand), so this guard
        // never blocks a fresh brew's legitimate first 0% reading.
        bool suspiciousDropToZero = (pct == 0 && lastBrewProgressPct > 20 && lastBrewProgressPct != 0xFF);
        if (pct != lastBrewProgressPct && !suspiciousDropToZero) {
          lastBrewProgressPct = pct;
          debugLog("MQTT publish brew_progress=%d (brewingActive=%d, fullLen=%d)", pct, brewingActive, fullLen);
          if (mqtt.connected()) { mqtt.publish("delonghi/brew_progress", String(pct).c_str(), true); lastMqttPublishAt = millis(); }
        }
      }
      if (machineState == "waking") warmupProgressRaw = pct;
    }
  }
}

bool connectToMachine() {
  if (Serial) { Serial.println("Connecting to machine...");
  Serial.println("Connecting to machine..."); }
  setRGB(255, 165, 0);
  if (bleClient) { NimBLEDevice::deleteClient(bleClient); bleClient = nullptr; }
  NimBLEDevice::setMTU(512);
  NimBLEAddress addr(delonghiMac.c_str(), BLE_ADDR_PUBLIC);
  bleClient = NimBLEDevice::createClient();
  if (!bleClient->connect(addr)) {
    if (Serial) { Serial.println("Failed!");
    Serial.println("Failed!"); }
    NimBLEDevice::deleteClient(bleClient);
    bleClient = nullptr;
    return false;
  }
  if (!bleClient->exchangeMTU()) {
    if (Serial) { Serial.println("MTU exchange failed, staying at default!");
    Serial.println("MTU exchange failed, staying at default!"); }
  }
  if (Serial) { Serial.printf("Machine connected! MTU=%d\n", bleClient->getMTU());
  Serial.printf("Machine connected! MTU=%d\n", bleClient->getMTU()); }
  NimBLERemoteService* svc = bleClient->getService(SERVICE_UUID);
  if (!svc) { bleClient->disconnect(); return false; }
  bleChar = svc->getCharacteristic(CHAR_UUID);
  if (!bleChar) { bleClient->disconnect(); return false; }
  // v4.44 FIX: confirmed via APK decompilation — official CoffeeLink
  // subscribes to this exact characteristic via INDICATE (writes 0x02 to
  // the CCCD), not NOTIFY. Our subscribe(true, ...) was writing 0x01
  // (NOTIFY) instead. Confirmed live: during Hot Water specifically, our
  // bridge saw ZERO new packets for 14+ seconds of active dispensing
  // (fragCount stayed 0 the whole time, confirmed via a heartbeat log
  // independent of any packet event — loop() itself was fine, nothing
  // was arriving at all) — while CoffeeLink's own %-progress display
  // relies on this exact same characteristic delivering packets
  // continuously and reliably. INDICATE requires an ACK from the client
  // for each packet before the peripheral sends the next one — if the
  // machine's own firmware behaves differently depending on which
  // subscription type the client used (plausible, and would explain an
  // intermittent dropout that notify-callback code alone can't see),
  // matching the officially-used mode exactly is the safest fix. The
  // callback (notifyFromMachine) doesn't use its `isNotify` parameter
  // anywhere, so this needs no other code changes.
  bleChar->subscribe(false, notifyFromMachine, true);
  if (Serial) { Serial.println("MITM ready!");
  Serial.println("MITM ready!"); }
  machineConnected = true;
  wakeDetectedAt = 0;
  settingsSyncSent = false;
  // Reset all brew-detection tracking state on every fresh connection —
  // previously only wakeDetectedAt/settingsSyncSent were reset here, so a
  // BLE reconnect after a long idle period (24h+, plausible over real-world
  // RF hiccups) could leave machineState/brewingActive/lastPassivePct/
  // lastBrewProgressPct stale from the PREVIOUS session, confusing
  // detection on the next real brew until a full device restart cleared
  // everything. This should fix that without needing a restart.
  machineState = "unknown";
  brewingActive = false;
  lastBrewProgressPct = 0xFF;
  lastPassivePct = 0;
  wakingAsleepStreak = 0;
  notDispensingStreak = 0;
  brewingUsesRealSignal = false;
  brewProgressRaw = 0;
  setRGB(0, 0, 255);

  if (!advImmediate) {
    NimBLEDevice::getAdvertising()->start();
    if (Serial) { Serial.println("Advertising as " FAKE_NAME " (after-connect mode)");
    Serial.println("Advertising as " FAKE_NAME " (after-connect mode)"); }
  }

  return true;
}

void handleWifiPortal() {
  server.send(200, "text/html; charset=utf-8",
    "<html><body style='font-family:monospace'>Скидаю Wi-Fi і перезавантажуюсь. "
    "Через ~5с підключись до точки доступу ESP32 (вона з'явиться в списку Wi-Fi "
    "на телефоні/комп'ютері) і обери нову мережу зі списку знайдених. "
    "<a href='/'>Назад</a></body></html>");
  delay(500);
  WiFiManager wm;
  wm.resetSettings();
  delay(300);
  ESP.restart();
}

void handleSettings() {
  if (server.method() == HTTP_POST) {
    if (server.hasArg("machineMac") && server.arg("machineMac").length() > 0) {
      prefs.putString("machineMac", server.arg("machineMac"));
    }
    prefs.putString("mqttHost", server.arg("mqttHost"));
    prefs.putInt("mqttPort", server.arg("mqttPort").toInt() > 0 ? server.arg("mqttPort").toInt() : 1883);
    prefs.putString("mqttUser", server.arg("mqttUser"));
    if (server.arg("mqttPass").length() > 0) {
      prefs.putString("mqttPass", server.arg("mqttPass"));
    }
    prefs.putString("staticIP", server.arg("staticIP"));
    prefs.putString("staticGateway", server.arg("staticGateway"));
    prefs.putString("staticSubnet", server.arg("staticSubnet").length() > 0 ? server.arg("staticSubnet") : "255.255.255.0");
    server.send(200, "text/html; charset=utf-8",
      "<html><body style='font-family:monospace'>Збережено. Для застосування нового MAC потрібне "
      "перезавантаження ESP32 (MQTT-дані застосуються без перезавантаження). "
      "<a href='/settings'>Назад до налаштувань</a> · <a href='/'>На дашборд</a></body></html>");
    return;
  }
  String html = "<html><head><meta charset='utf-8'><meta name='viewport' content='width=device-width,initial-scale=1'>";
  html += "<style>body{font-family:monospace;background:#1a1a2e;color:#eee;padding:20px}";
  html += "input{width:90%;max-width:300px;padding:8px;margin:4px 0;background:#222;color:#eee;border:1px solid #555}";
  html += ".card{background:#16213e;border-radius:10px;padding:16px;margin-bottom:16px}";
  html += "button{padding:10px 20px;background:#e94560;color:#fff;border:none;border-radius:6px;font-family:monospace}</style>";
  html += "</head><body>";
  html += "<h2>⚙️ Налаштування</h2>";
  html += "<div class='card'>📶 Wi-Fi: <b>" + WiFi.SSID() + "</b><br>";
  html += "IP: " + WiFi.localIP().toString() + " · RSSI: " + String(WiFi.RSSI()) + "дБм<br><br>";
  html += "<button type='button' onclick=\"if(confirm('Скинути Wi-Fi і перезавантажитись?'))location.href='/wifi'\">🔄 Змінити Wi-Fi мережу</button></div>";
  html += "<div class='card'>📡 Реклама BLE: <b>" + String(advImmediate ? "одразу" : "після конекту") + "</b><br><br>";
  html += "<a href='/adv?mode=after' style='color:#eee'>[ після конекту ]</a> &nbsp; ";
  html += "<a href='/adv?mode=immediate' style='color:#eee'>[ одразу ]</a>";
  html += "<br><small>Зміна перезавантажує ESP32</small></div>";
  html += "<form method='POST' action='/settings'><div class='card'>";
  html += "🎯 MAC цільової машини<br>";
  html += "<input name='machineMac' value='" + delonghiMac + "' placeholder='00:1e:c0:30:c0:45'><br>";
  html += "<small>Формат XX:XX:XX:XX:XX:XX. Підміна MAC-адреси відбудеться автоматично після перезавантаження.</small>";
  html += "</div><div class='card'>📡 MQTT-брокер (для Home Assistant)<br>";
  html += "Адреса: <input name='mqttHost' value='" + mqttHost + "' placeholder='192.168.0.XXX'><br>";
  html += "Порт: <input name='mqttPort' value='" + String(mqttPort) + "' placeholder='1883'><br>";
  html += "Логін: <input name='mqttUser' value='" + mqttUser + "' placeholder='mqtt_user'><br>";
  html += "Пароль: <input name='mqttPass' type='password' placeholder='" + String(mqttPass.length() > 0 ? "(збережено, лишити порожнім щоб не міняти)" : "") + "'>";
  html += "</div><div class='card'>🌐 Статична IP-адреса (лишити порожнім для DHCP)<br>";
  html += "IP: <input name='staticIP' value='" + staticIP + "' placeholder='192.168.0.150'><br>";
  html += "Шлюз: <input name='staticGateway' value='" + staticGateway + "' placeholder='192.168.0.1'><br>";
  html += "Маска: <input name='staticSubnet' value='" + staticSubnet + "' placeholder='255.255.255.0'><br>";
  html += "<small>Застосується після перезавантаження ESP32.</small>";
  html += "</div><button type='submit'>💾 Зберегти</button></form>";
  html += "<br><a href='/' style='color:#aaa'>← Назад на дашборд</a>";
  html += "</body></html>";
  server.send(200, "text/html; charset=utf-8", html);
}

void handleAdv() {
  if (server.hasArg("mode")) {
    bool val = server.arg("mode") == "immediate";
    prefs.putBool("advImmediate", val);
    server.send(200, "text/html; charset=utf-8",
      "<html><body style='font-family:monospace'>Збережено: " +
      String(val ? "одразу" : "після конекту") +
      ". Перезавантаження...</body></html>");
    delay(300);
    ESP.restart();
  } else {
    server.send(400, "text/plain", "missing mode param");
  }
}

void handleUpdatePage() {
  String html = "<html><head><meta charset='utf-8'><meta name='viewport' content='width=device-width,initial-scale=1'>";
  html += "<style>body{font-family:monospace;background:#1a1a2e;color:#eee;padding:20px}";
  html += ".card{background:#16213e;border-radius:10px;padding:16px;margin-bottom:16px}";
  html += "input[type=file]{margin:10px 0}";
  html += "#bar-bg{width:100%;background:#333;border-radius:6px;overflow:hidden;margin-top:12px;display:none}";
  html += "#bar{height:24px;width:0%;background:#27ae60;color:#fff;text-align:center;line-height:24px;font-size:0.85em;transition:width 0.2s}";
  html += "button{padding:10px 20px;background:#e94560;color:#fff;border:none;border-radius:6px;font-family:monospace}</style>";
  html += "</head><body>";
  html += "<h2>🔄 Оновлення прошивки</h2>";
  html += "<div class='card'>Поточна версія: <b>" + String(FW_VERSION) + "</b><br><br>";
  html += "Обери зкомпільований <code>.bin</code>-файл (Sketch → Export Compiled Binary в Arduino IDE):<br>";
  html += "<input type='file' id='fw' accept='.bin'><br>";
  html += "<button onclick='doUpload()'>⬆️ Залити</button>";
  html += "<div id='bar-bg'><div id='bar'>0%</div></div>";
  html += "<div id='status' style='margin-top:8px'></div>";
  html += "</div>";
  html += "<a href='/' style='color:#aaa'>← Назад на дашборд</a>";
  html += "<script>";
  html += "function doUpload(){";
  html += "var f=document.getElementById('fw').files[0];";
  html += "if(!f){alert('Обери файл');return;}";
  html += "var fd=new FormData(); fd.append('firmware',f);";
  html += "var xhr=new XMLHttpRequest();";
  html += "document.getElementById('bar-bg').style.display='block';";
  html += "xhr.upload.onprogress=function(e){";
  html += "if(e.lengthComputable){var p=Math.round(e.loaded/e.total*100);";
  html += "document.getElementById('bar').style.width=p+'%';";
  html += "document.getElementById('bar').innerText=p+'%';}};";
  html += "xhr.onload=function(){";
  html += "document.getElementById('status').innerHTML=xhr.responseText;";
  html += "document.getElementById('bar').style.width='100%';";
  html += "document.getElementById('bar').innerText='Прошивається...';};";
  html += "xhr.onerror=function(){document.getElementById('status').innerText='Помилка мережі';};";
  html += "xhr.open('POST','/doupdate',true);";
  html += "xhr.send(fd);}";
  html += "</script>";
  html += "</body></html>";
  server.send(200, "text/html; charset=utf-8", html);
}

void handleDoUpdate() {
  server.sendHeader("Connection", "close");
  server.send(200, "text/html; charset=utf-8",
    String("<html><body style='font-family:monospace'>") +
    (Update.hasError() ? "❌ Помилка оновлення!" : "✅ Успішно! Перезавантажуюсь...") +
    "</body></html>");
  delay(500);
  if (!Update.hasError()) ESP.restart();
}

void handleUpdateUpload() {
  HTTPUpload& upload = server.upload();
  if (upload.status == UPLOAD_FILE_START) {
    if (Serial) { Serial.printf("OTA update starting: %s\n", upload.filename.c_str());
    Serial.printf("OTA update starting: %s\n", upload.filename.c_str()); }
    otaInProgress = true;
    if (!Update.begin(UPDATE_SIZE_UNKNOWN)) {
      Update.printError(Serial);
    }
  } else if (upload.status == UPLOAD_FILE_WRITE) {
    if (Update.write(upload.buf, upload.currentSize) != upload.currentSize) {
      Update.printError(Serial);
    }
  } else if (upload.status == UPLOAD_FILE_END) {
    if (Update.end(true)) {
      if (Serial) { Serial.printf("OTA update success: %u bytes\n", upload.totalSize);
      Serial.printf("OTA update success: %u bytes\n", upload.totalSize); }
    } else {
      Update.printError(Serial);
    }
    otaInProgress = false;
  }
}

void handleBrew() {
  if (server.hasArg("drink")) {
    sendDrinkCommand(server.arg("drink"));
    server.sendHeader("Location", "/");
    server.send(303);
  } else {
    server.send(400, "text/plain", "missing drink param");
  }
}

void handleSetting() {
  String drink = server.arg("drink");
  float ml = server.arg("ml").toFloat();
  float sec = server.hasArg("sec") ? server.arg("sec").toFloat() : 0;
  int level = server.arg("level").toInt();
  uint8_t recipeId; float mlMin, mlMax, secMin, secMax; bool hasMilk;
  if (drink == "coffee")           { recipeId = 2; mlMin=110; mlMax=280; hasMilk=false; }
  else if (drink == "espresso")    { recipeId = 1; mlMin=20;  mlMax=195; hasMilk=false; }
  else if (drink == "cappuccino")  { recipeId = 7; mlMin=20;  mlMax=195; hasMilk=true; secMin=5;  secMax=90; }
  else if (drink == "latte_macchiato") { recipeId = 8; mlMin=20; mlMax=195; hasMilk=true; secMin=7; secMax=90; }
  else { server.send(400, "text/plain", "unknown drink"); return; }
  if (ml < mlMin) ml = mlMin; if (ml > mlMax) ml = mlMax;
  if (level < 1) level = 1; if (level > 5) level = 5;
  if (hasMilk) { if (sec < secMin) sec = secMin; if (sec > secMax) sec = secMax; } else sec = 0;
  // Save to NVS + update in-memory globals ONLY — this button ("Зберегти")
  // is now purely local/ESP32-side, per user's clarified design: fast way
  // to brew your own custom values through OUR bridge without touching the
  // machine's own profile at all. The SEPARATE "В профіль" button
  // (handleSettingProfile below) is what actually sends anything to the
  // machine.
  if (drink == "espresso") {
    savedEspressoMl = ml; savedEspressoStrength = level;
    prefs.putFloat("esprMl", ml); prefs.putFloat("esprStr", level);
  } else if (drink == "coffee") {
    savedCoffeeMl = ml; savedCoffeeStrength = level;
    prefs.putFloat("coffMl", ml); prefs.putFloat("coffStr", level);
  } else if (drink == "cappuccino") {
    savedCappuccinoMl = ml; savedCappuccinoStrength = level; savedCappuccinoMilkSec = sec;
    prefs.putFloat("cappMl", ml); prefs.putFloat("cappStr", level); prefs.putFloat("cappMilk", sec);
  } else if (drink == "latte_macchiato") {
    savedLatteMl = ml; savedLatteStrength = level; savedLatteMilkSec = sec;
    prefs.putFloat("latteMl", ml); prefs.putFloat("latteStr", level); prefs.putFloat("latteMilk", sec);
  }
  server.send(200, "text/plain", "ok");
}

void handleSettingProfile() {
  // "В профіль" — sends the SAVE command (82 f0, action 0x00) directly to
  // the machine. If a "profile" arg is given (v4.02+), switches the
  // machine's active profile first (A9F0) so the save lands exactly
  // there; if omitted, applies to whichever profile is currently active
  // (backward-compatible with v4.00/4.01 behavior). Does NOT touch our
  // own NVS storage — that's the separate "Зберегти" button's job.
  String drink = server.arg("drink");
  float ml = server.arg("ml").toFloat();
  float sec = server.hasArg("sec") ? server.arg("sec").toFloat() : 0;
  int level = server.arg("level").toInt();
  uint8_t recipeId; float mlMin, mlMax, secMin, secMax; bool hasMilk;
  if (drink == "coffee")           { recipeId = 2; mlMin=110; mlMax=280; hasMilk=false; }
  else if (drink == "espresso")    { recipeId = 1; mlMin=20;  mlMax=195; hasMilk=false; }
  else if (drink == "cappuccino")  { recipeId = 7; mlMin=20;  mlMax=195; hasMilk=true; secMin=5;  secMax=90; }
  else if (drink == "latte_macchiato") { recipeId = 8; mlMin=20; mlMax=195; hasMilk=true; secMin=7; secMax=90; }
  else { server.send(400, "text/plain", "unknown drink"); return; }
  if (ml < mlMin) ml = mlMin; if (ml > mlMax) ml = mlMax;
  if (level < 1) level = 1; if (level > 5) level = 5;
  if (hasMilk) { if (sec < secMin) sec = secMin; if (sec > secMax) sec = secMax; } else sec = 0;
  if (server.hasArg("profile")) {
    int profileId = server.arg("profile").toInt();
    if (profileId >= 1 && profileId <= 6) {
      sendProfileSwitch((uint8_t)profileId);
      delay(300);  // give the machine a moment to apply the switch
    }
  }
  // Official CoffeeLink refuses to send SAVE unless the machine's MonitorV1
  // function/execution state is exactly func==7,exec==0 at that moment —
  // confirmed via APK decompilation (BrewBeveragesViewModel.t()'s
  // monitorData.o() gate). Give it a window to reach that state.
  // v4.07: also pump fragment-processing here — same starvation bug as
  // handleProfilePeek() (see its comment for the full explanation).
  // v4.10: extended window from 3s(30x100ms) to 8s(80x100ms) — this gate
  // apparently doesn't open often enough for 3s to reliably catch it,
  // matching the same category of issue A6F0 reading had (v4.06/v4.08).
  bool gateOk = false;
  for (int i = 0; i < 80; i++) {
    if (fragCount > 0 && (millis() - lastFragmentTime > 120)) {
      forwardFragmentsToPhone();
    }
    if (machineReadyForSave()) { gateOk = true; break; }
    delay(100);
  }
  if (!gateOk) {
    server.send(200, "text/plain", "not_ready");
    return;
  }
  sendRecipeSetting(recipeId, ml, sec, level);
  server.send(200, "text/plain", "ok");
}

void handleParamSource() {
  int v = server.arg("value").toInt();
  if (v >= 0 && v <= 6) paramSource = (uint8_t)v;
  server.send(200, "text/plain", "ok");
}

void handleParamPing() {
  // Fired the moment the user clicks to select a profile as the brewing
  // source (main-page power button, once machine is awake) — switches the
  // machine's active profile (A9F0) immediately, then does a coffee A6F0
  // read purely as a connectivity/switch confirmation "ping" (per user:
  // fine to ignore the actual values — always re-read fresh for whatever
  // drink is ultimately brewed). Doing the switch HERE (not at brew time)
  // means readFromActiveProfile() below no longer needs to re-switch,
  // shortening the wait right before an actual brew.
  int v = server.arg("profile").toInt();
  if (v < 1 || v > 6) { server.send(400, "text/plain", "bad profile"); return; }
  paramSource = (uint8_t)v;
  sendProfileSwitch(paramSource);
  delay(300);
  float ml, sec; uint8_t lvl;
  readQuantitiesOnly(2 /*coffee*/, &ml, &sec, &lvl);  // result intentionally discarded — ping only
  server.send(200, "text/plain", "ok");
}

// Reads live quantities for the given recipeId from WHATEVER profile is
// currently active on the machine (does NOT switch profile itself — that
// already happened via handleParamPing() when the user selected this
// profile as the brewing source). Returns true and fills ml/sec/level on
// success; false (leaving them untouched) on failure.
bool readQuantitiesOnly(uint8_t recipeId, float* ml, float* sec, uint8_t* level) {
  bool gotResponse = false;
  for (int attempt = 0; attempt < 5 && !gotResponse; attempt++) {
    lastA6F0Fresh = false;
    sendRecipeQuantitiesQuery(paramSource, recipeId);
    for (int i = 0; i < 15; i++) {
      delay(100);
      if (fragCount > 0 && (millis() - lastFragmentTime > 120)) {
        forwardFragmentsToPhone();
      }
      if (lastA6F0Fresh) { gotResponse = true; break; }
    }
  }
  if (!gotResponse) return false;
  *ml = lastA6F0Ml;
  *sec = lastA6F0Sec;
  *level = lastA6F0StrengthLevel;
  return true;
}

// Kept as a thin wrapper (same name sendDrinkCommand already calls) —
// v4.15 moved the profile-switch to click-time (handleParamPing), so this
// now only reads, it doesn't re-switch.
bool readFromActiveProfile(uint8_t recipeId, float* ml, float* sec, uint8_t* level) {
  return readQuantitiesOnly(recipeId, ml, sec, level);
}

void handleProfilePeek() {
  // "В профіль" cycling button — switches to the given profile, reads
  // back its CURRENT quantities for the given drink, returns them as
  // JSON so the page can draw red-dot markers for comparison.
  String drink = server.arg("drink");
  int profileId = server.arg("profile").toInt();
  uint8_t recipeId;
  if (drink == "coffee") recipeId = 2;
  else if (drink == "espresso") recipeId = 1;
  else if (drink == "cappuccino") recipeId = 7;
  else if (drink == "latte_macchiato") recipeId = 8;
  else { server.send(400, "text/plain", "unknown drink"); return; }
  if (profileId < 1 || profileId > 6) { server.send(400, "text/plain", "bad profile"); return; }
  sendProfileSwitch((uint8_t)profileId);
  delay(300);
  // v4.08: retry the query up to 5 times — even with v4.07's starvation
  // fix, success rate was still only ~1/12. Likely cause: the machine
  // sends its own regular status broadcasts independently of our request,
  // and if one happens to interleave with our A6F0 fragments in the
  // shared reassembly buffer, both get corrupted. Retrying with a fresh
  // request each time greatly improves the odds that at least one
  // attempt doesn't collide with a background broadcast.
  bool gotResponse = false;
  for (int attempt = 0; attempt < 5 && !gotResponse; attempt++) {
    lastA6F0Fresh = false;
    sendRecipeQuantitiesQuery((uint8_t)profileId, recipeId);
    for (int i = 0; i < 15; i++) {
      delay(100);
      // v4.07 CRITICAL FIX: forwardFragmentsToPhone() (which assembles BLE
      // fragments and calls maybeParseStatus() to actually parse an A6F0
      // response) is normally only invoked from loop() — but we're stuck in
      // a blocking wait INSIDE this HTTP handler, which itself only runs
      // via loop()->server.handleClient(). Our own delay()-based wait was
      // starving loop() from ever reaching the fragment-processing check,
      // so the response could never be parsed WHILE we were waiting for it
      // — it only got processed AFTER we gave up and returned (explaining
      // why the v4.05 diagnostic capture showed correct data, just too
      // late). Fix: pump the same fragment-processing check ourselves here.
      if (fragCount > 0 && (millis() - lastFragmentTime > 120)) {
        forwardFragmentsToPhone();
      }
      if (lastA6F0Fresh) { gotResponse = true; break; }
    }
  }
  if (!gotResponse) {
    server.send(200, "application/json", "{\"error\":\"no_response\"}");
    return;
  }
  String json = "{\"ml\":" + String(lastA6F0Ml, 1) +
                ",\"sec\":" + String(lastA6F0Sec, 1) +
                ",\"level\":" + String(lastA6F0StrengthLevel) + "}";
  server.send(200, "application/json", json);
}

void handleRgbBrightness() {
  // v4.18: live-adjust and persist the status LED (NeoPixel) brightness
  // from the /info page slider. rgb.setBrightness() alone doesn't repaint
  // the LED — it only takes effect on the next show() call, so we call
  // rgb.show() ourselves right after to re-apply whatever color is
  // already in the pixel buffer at the new brightness immediately
  // (visible feedback), and save to NVS so it survives a reboot.
  if (server.hasArg("v")) {
    int v = server.arg("v").toInt();
    if (v < 2) v = 2;
    if (v > 255) v = 255;
    rgbBrightness = v;
    rgb.setBrightness(rgbBrightness);
    rgb.show();
    prefs.putInt("rgbBri", rgbBrightness);
  }
  server.send(200, "text/plain", "ok");
}

void handleDebugLog() {
  // v4.41: plain-text dump of the ring buffer, oldest to newest — easy to
  // select-all/copy from a phone browser, no USB needed. Read-only, no
  // side effects; safe to leave in permanently.
  String html = "<html><head><meta charset='UTF-8'><meta name='viewport' content='width=device-width,initial-scale=1'>";
  html += "<style>body{font-family:monospace;background:#111;color:#0f0;font-size:13px;white-space:pre-wrap;word-break:break-all;padding:8px}";
  html += "a{color:#6cf}</style></head><body>";
  html += "<a href='/info'>&larr; Система</a> | <a href='/debug_log'>&#8635; Оновити</a><br><br>";
  html += "Рядків у буфері: " + String(debugLogCount) + " / " + String(DEBUG_LOG_LINES) + "\n\n";
  int start = (debugLogCount < DEBUG_LOG_LINES) ? 0 : debugLogHead;
  for (int i = 0; i < debugLogCount; i++) {
    int idx = (start + i) % DEBUG_LOG_LINES;
    html += String(debugLogBuf[idx]) + "\n";
  }
  html += "</body></html>";
  server.send(200, "text/html", html);
}

void handleInfo() {
  String html = "<!DOCTYPE html><html><head><meta charset='utf-8'>";
  html += "<meta name='viewport' content='width=device-width,initial-scale=1'>";
  html += "<title>PrimaDonna — Система</title>";
  html += "<link rel='icon' href='/icon.png'>";
  html += "<style>body{background:#1a1a2e;color:#fff;font-family:sans-serif;padding:10px;font-size:0.92em}";
  html += "a{color:#f39c12}.card{background:#16213e;border-radius:10px;padding:10px 14px;margin-bottom:10px}";
  html += "p{margin:4px 0}img{display:block;margin:4px auto}</style></head><body>";
  html += "<a href='/'>&larr; Назад</a><h3 style='margin:6px 0'>📊 Система</h3>";

  html += "<div class='card' style='text-align:center'>";
  html += "<img src='/qr.png' width='160' height='160'>";
  html += "<p>🌐 " + WiFi.localIP().toString() + "</p></div>";

  unsigned long upSec = millis() / 1000;
  unsigned long upH = upSec / 3600, upM = (upSec % 3600) / 60, upS = upSec % 60;
  html += "<div class='card'>";
  html += "<p>☕ Сьогодні: <b style='font-size:1.6em'>" + String(drinksToday) + "</b> напоїв</p>";
  html += "<p>🕐 Час роботи: " + String(upH) + "г " + String(upM) + "хв " + String(upS) + "с</p>";
  html += "<p>💾 Пам'ять: " + String(ESP.getFreeHeap() / 1024) + " КБ (шматок: " + String(ESP.getMaxAllocHeap() / 1024) + " КБ)</p>";
  html += "<p>📶 Wi-Fi: " + String(WiFi.RSSI()) + " dBm</p>";
  html += "<p>🔵 BLE: ";
  if (machineConnected && bleClient != nullptr && bleClient->isConnected()) {
    html += String(bleClient->getRssi()) + " dBm";
  } else {
    html += "не підключено";
  }
  html += "</p>";
  html += "<p>🔧 " + String(FW_VERSION) + "</p>";
  html += "<p>🔍 func/exec: <b>" + (monitorFuncCode == 0xFF ? String("ще не бачили") : String(monitorFuncCode) + "/" + String(monitorExecCode)) + "</b> (для перевірки детекції варіння)</p>";
  html += "<p>📜 <a href='/debug_log' style='color:#6cf'>Детальний лог (для діагностики)</a></p>";
  html += "<p style='margin-top:8px'>💡 Яскравість індикатора: <b id='rgbVal'>" + String(rgbBrightness) + "</b></p>";
  html += "<input type='range' min='2' max='255' value='" + String(rgbBrightness) + "' id='rgbSlider' style='width:100%'";
  html += " oninput=\"document.getElementById('rgbVal').innerText=this.value\"";
  html += " onchange=\"fetch('/rgb_brightness?v='+this.value)\">";
  html += "</div>";

  html += "<div class='card'><h3 style='margin:2px 0 8px'>🔧 Сервісне меню</h3>";
  for (int i = 0; i < ALARM_TABLE_LEN; i++) {
    bool active = alarmActive(ALARM_TABLE[i].bit);
    html += "<p style='margin:3px 0";
    if (active) html += ";color:#e74c3c;font-weight:bold";
    html += "'>" + String(active ? "✓ " : "&nbsp;&nbsp; ") + ALARM_TABLE[i].text + "</p>";
  }
  html += "</div>";

  html += "<div class='card'>";
  html += "<h3 style='margin:2px 0 8px'>🧪 Останній надісланий код</h3>";
  html += "<textarea id='lastCmdBox' readonly style='width:100%;background:#0f0f23;color:#0f0;border:1px solid #444;border-radius:6px;padding:8px;font-family:monospace;font-size:0.95em' rows='2'>" + lastSentCmdHex + "</textarea>";
  html += "<button onclick=\"navigator.clipboard.writeText(document.getElementById('lastCmdBox').value);this.innerText='Скопійовано!'\" style='margin-top:6px;background:#f39c12;color:#000;border:none;border-radius:6px;padding:8px 14px'>📋 Копіювати</button>";
  html += "</div>";

  html += "<div class='card'>";
  html += "<h3 style='margin:2px 0 8px'>📥 Останній отриманий пакет</h3>";
  html += "<textarea id='lastRecvBox' readonly style='width:100%;background:#0f0f23;color:#0af;border:1px solid #444;border-radius:6px;padding:8px;font-family:monospace;font-size:0.95em' rows='2'>" + String(lastAnyPacketBuf) + "</textarea>";
  unsigned long sinceRecv = (millis() - lastAnyPacketAt) / 1000;
  html += "<p style='margin:4px 0;color:#888;font-size:0.85em'>" + String(sinceRecv) + " сек тому</p>";
  html += "<button onclick=\"navigator.clipboard.writeText(document.getElementById('lastRecvBox').value);this.innerText='Скопійовано!'\" style='margin-top:2px;background:#f39c12;color:#000;border:none;border-radius:6px;padding:8px 14px'>📋 Копіювати</button>";
  html += "</div>";

  html += "<div class='card' style='text-align:center'>";
  html += "<a href='/reboot' style='color:#e74c3c' onclick=\"return confirm('Перезавантажити пристрій?')\">🔁 Перезавантажити пристрій</a></div>";

  html += "</body></html>";
  server.send(200, "text/html", html);
}

void handleRoot() {
  unsigned long age = lastUpdate > 0 ? (millis() - lastUpdate) / 1000 : 0;
  String html;
  // v4.14 perf fix: this page has grown substantially across many feature
  // additions (settings panels, profile picker, dots, etc.) — Arduino
  // String's default small initial capacity means MANY reallocations as
  // it grows via += across this whole function, each one copying
  // everything built so far. Reserving generously upfront avoids that
  // entirely. Same root-cause category as the v4.04/v4.05 perf bug, just
  // in the page-generation path this time instead of packet parsing.
  html.reserve(24000);
  html = "<!DOCTYPE html><html><head>";
  html += "<meta charset='utf-8'><meta name='viewport' content='width=device-width,initial-scale=1'>";
  html += "<title>PrimaDonna</title>";
  html += "<link rel='icon' href='/icon.png'>";
  html += "<link rel='apple-touch-icon' href='/icon.png'>";
  html += "<link rel='manifest' href='/manifest.json'>";
  html += "<style>body{font-family:monospace;padding:10px;background:#1a1a2e;color:#eee;}";
  html += "h1{color:#f39c12;text-align:center;}";
  html += ".card{background:#16213e;border-radius:10px;padding:12px;margin:8px;}";
  html += "@keyframes blinkPower{0%,100%{background:#ff3860}50%{background:#3498db}}";
  html += ".blinking{animation:blinkPower 0.6s infinite}</style></head><body>";
  html += "<h1>☕ MITM " + String(FW_VERSION) + "</h1>";
  html += "<div style='display:flex;align-items:center;justify-content:center;gap:10px'>";
  html += "<div style='flex:1;text-align:right'>";
  html += "<div id='waterMsg' style='color:#f39c12;font-size:0.9em'>" + waterMessage + "</div>";
  html += "<div id='groundsMsg' style='color:#f39c12;font-size:0.9em'>" + groundsMessage + "</div>";
  html += "<div id='beansMsg' style='color:#f39c12;font-size:0.9em'>" + beansMessage + "</div>";
  html += "</div>";
  html += "<img src='https://delonghibe.s3.eu-west-1.amazonaws.com/cms/prod/img/_opt_delonghi_uploads_elite_best_front.png' style='max-width:180px;max-height:180px;flex-shrink:0' onerror=\"this.style.display='none'\">";
  html += "<div style='flex:1;text-align:left'>";
  html += "<div id='milkMsg' style='color:#f39c12;font-size:0.9em'>" + milkMessage + "</div>";
  html += "<div id='iconSlot' style='display:none;text-align:center;margin-top:6px'>";
  // Water-drop icon, solid (water container physically missing)
  html += "<svg id='iconWaterMissing' style='display:none' width='40' height='50' viewBox='0 0 40 50'>"
          "<path d='M20 2 C20 2 4 24 4 34 C4 43 11 48 20 48 C29 48 36 43 36 34 C36 24 20 2 20 2 Z' "
          "fill='#3498db' stroke='#f39c12' stroke-width='1.5'/></svg>";
  // Water-drop icon, outline + down-arrow (running low, container still present)
  html += "<svg id='iconWaterLow' style='display:none' width='40' height='50' viewBox='0 0 40 50'>"
          "<path d='M20 2 C20 2 4 24 4 34 C4 43 11 48 20 48 C29 48 36 43 36 34 C36 24 20 2 20 2 Z' "
          "fill='none' stroke='#3498db' stroke-width='2'/>"
          "<line x1='20' y1='18' x2='20' y2='34' stroke='#f39c12' stroke-width='2.5'/>"
          "<path d='M14 28 L20 36 L26 28' fill='none' stroke='#f39c12' stroke-width='2.5' stroke-linecap='round' stroke-linejoin='round'/></svg>";
  // Coffee-grounds bin icon, normal (grounds container physically missing)
  html += "<svg id='iconGroundsMissing' style='display:none' width='40' height='50' viewBox='0 0 40 50'>"
          "<rect x='8' y='14' width='24' height='30' rx='2' fill='#5C3A1E' stroke='#f39c12' stroke-width='1.5'/>"
          "<rect x='4' y='8' width='32' height='6' rx='1' fill='#8B5A2B' stroke='#f39c12' stroke-width='1.5'/>"
          "<line x1='16' y1='6' x2='16' y2='2' stroke='#f39c12' stroke-width='2'/>"
          "<line x1='24' y1='6' x2='24' y2='2' stroke='#f39c12' stroke-width='2'/></svg>";
  // Coffee-grounds bin icon, overflowing (container full, needs emptying)
  html += "<svg id='iconGroundsFull' style='display:none' width='40' height='50' viewBox='0 0 40 50'>"
          "<rect x='8' y='14' width='24' height='30' rx='2' fill='#5C3A1E' stroke='#e94560' stroke-width='1.5'/>"
          "<rect x='4' y='8' width='32' height='6' rx='1' fill='#8B5A2B' stroke='#e94560' stroke-width='1.5'/>"
          "<circle cx='14' cy='6' r='3' fill='#5C3A1E'/><circle cx='20' cy='4' r='3.5' fill='#5C3A1E'/><circle cx='26' cy='6' r='3' fill='#5C3A1E'/>"
          "<text x='20' y='26' font-size='16' fill='#e94560' text-anchor='middle'>!</text></svg>";
  // Milk carton icon, outline (milk container missing)
  html += "<svg id='iconMilkMissing' style='display:none' width='40' height='50' viewBox='0 0 40 50'>"
          "<path d='M10 10 L10 4 L20 0 L30 4 L30 10 L30 46 L10 46 Z' fill='none' stroke='#f39c12' stroke-width='2'/>"
          "<line x1='10' y1='18' x2='30' y2='18' stroke='#f39c12' stroke-width='1.5' stroke-dasharray='2,2'/></svg>";
  // Milk jug icon with warning (jug needs cleaning)
  html += "<svg id='iconMilkClean' style='display:none' width='40' height='50' viewBox='0 0 40 50'>"
          "<path d='M10 10 L10 4 L20 0 L30 4 L30 10 L30 46 L10 46 Z' fill='#fefefe' fill-opacity='0.15' stroke='#e94560' stroke-width='2'/>"
          "<line x1='10' y1='18' x2='30' y2='18' stroke='#e94560' stroke-width='1.5'/>"
          "<text x='20' y='34' font-size='14' fill='#e94560' text-anchor='middle'>!</text></svg>";
  // Coffee bean icon, outline (beans hopper empty)
  html += "<svg id='iconBeansEmpty' style='display:none' width='40' height='50' viewBox='0 0 40 50'>"
          "<ellipse cx='20' cy='25' rx='14' ry='20' fill='none' stroke='#f39c12' stroke-width='2'/>"
          "<path d='M20 6 Q26 16 20 25 Q14 34 20 44' fill='none' stroke='#f39c12' stroke-width='2'/></svg>";
  html += "<div id='monitorAlarmSlot' style='display:none;color:#e74c3c;font-weight:bold;padding:8px'></div>";
  html += "<svg id='iconWarmup' style='display:none' width='40' height='50' viewBox='0 0 40 50'>"
          "<circle cx='14' cy='16' r='3' fill='#3498db'><animate attributeName='cy' values='10;30' dur='1s' repeatCount='indefinite'/>"
          "<animate attributeName='opacity' values='1;0' dur='1s' repeatCount='indefinite'/></circle>"
          "<circle cx='26' cy='22' r='3' fill='#3498db'><animate attributeName='cy' values='10;30' dur='1s' begin='0.5s' repeatCount='indefinite'/>"
          "<animate attributeName='opacity' values='1;0' dur='1s' begin='0.5s' repeatCount='indefinite'/></circle>"
          "<rect x='6' y='34' width='28' height='8' rx='2' fill='none' stroke='#f39c12' stroke-width='2'/></svg>";
  html += "<div id='brewCup' style='width:40px;height:52px;margin:0 auto;border:3px solid #f39c12;";
  html += "border-radius:0 0 8px 8px;position:relative;overflow:hidden;background:#0a0a1a'>";
  html += "<div id='brewFill' style='position:absolute;bottom:0;left:0;right:0;height:0%;";
  html += "background:linear-gradient(#8B5A2B,#5C3A1E);transition:height 0.5s'></div>";
  html += "</div>";
  html += "<div id='iconBar' style='display:none;width:50px;height:8px;margin:4px auto;background:#0a0a1a;border:1px solid #f39c12;border-radius:4px;overflow:hidden'>";
  html += "<div id='iconBarFill' style='height:100%;width:0%;background:#3498db;transition:width 0.5s'></div></div>";
  html += "<div id='brewName' style='font-size:0.75em;color:#f39c12'></div>";
  html += "<div id='brewPct' style='font-size:0.75em'></div>";
  html += "</div></div>";
  html += "</div>";
  html += "<div class='card'>";
  html += "🎛️ Стан машини: <b id='machineState'>" + prettyState(machineState) + "</b><br>";
  html += "📶 Wi-Fi: ✅ " + WiFi.SSID() + " (" + WiFi.localIP().toString() + ")<br>";
  html += "☕ Машина: <span id='machineConn'>" + String(machineConnected ? "✅" : "❌") + "</span> ";
  html += "📡 MQTT: <span id='mqttConn'>" + String(mqtt.connected() ? "✅" : (mqttHost.length() ? "❌" : "не налаштовано")) + "</span> ";
  html += "📱 Телефон: <span id='phoneConn'>" + String(phoneConnected ? "✅" : "❌") + "</span><br>";
  html += "📦 Пакетів: <span id='pktCount'>" + String(packetCount) + "</span> &nbsp; ";
  html += "🕐 <span id='age'>" + String(age) + "</span>с тому";
  html += "<br><br><a href='/info' style='color:#f39c12'>📊 Система (QR, діагностика, лічильник)</a>";
  html += "<br><a href='/settings' style='color:#f39c12'>⚙️ Налаштування (MAC, MQTT, Wi-Fi)</a>";
  html += "<br><a href='/update' style='color:#f39c12'>🔄 Оновити прошивку</a>";
  html += "</div>";
  html += "<div class='card'><h3 style='margin-top:0;display:flex;justify-content:space-between;align-items:center'>";
  html += "<span>☕ Приготувати</span>";
  html += "<span style='display:flex;gap:6px'>";
  html += "<button id='gearBtn' onclick=\"settingsMode=!settingsMode;this.style.background=settingsMode?'#f39c12':'#3a3a5c';if(!settingsMode)showGrid();\" "
          "style='padding:6px 10px;background:#3a3a5c;color:#fff;border:none;border-radius:6px;font-family:monospace;font-size:0.85em;cursor:pointer'>⚙️</button>";
  html += "<button id='powerBtn' onclick=\"handlePowerBtnClick()\" "
          "style='padding:6px 14px;background:#3498db;color:#fff;border:none;border-radius:6px;font-family:monospace;font-size:0.85em;cursor:pointer'>🔌 Увімкнути</button>";
  html += "</span></h3>";
  const char* drinkRows[][3] = {
    {"coffee", "coffee_stop", "☕ Кава"},
    {"espresso", "espresso_stop", "☕ Еспресо"},
    {"latte_macchiato", "latte_macchiato_stop", "🥛 Латте Макіато"},
    {"cappuccino", "cappuccino_stop", "🥛 Капучино"},
    {"hot_water", "hot_water_stop", "💧 Гаряча вода"},
  };
  html += "<div id='drinkGrid' style='display:grid;grid-template-columns:1fr 1fr;gap:8px'>";
  for (auto& d : drinkRows) {
    html += "<button onclick=\"location.href='/brew?drink=" + String(d[0]) + "'\" "
            "style='padding:14px;background:#e94560;color:#fff;border:none;border-radius:8px;font-family:monospace'>"
            + String(d[2]) + "</button>";
    if (strlen(d[1]) > 0) {
      html += "<button onclick=\"handleStopClick('" + String(d[0]) + "','" + String(d[1]) + "')\" "
              "style='padding:14px;background:#5c3a5c;color:#fff;border:none;border-radius:8px;font-family:monospace'>🛑 Стоп</button>";
    } else {
      html += "<button disabled style='padding:14px;background:#2a2a3a;color:#666;border:none;border-radius:8px;font-family:monospace'>—</button>";
    }
  }
  html += "</div>";
  // Real settings panels — one per customizable drink, swapped in place of
  // the whole button grid (same screen space). Each uses TRUE range
  // sliders now that the checksum is cracked — any value in the real
  // min/max range works, computed live in firmware via sendRecipeSetting().
  struct { const char* id; const char* name; float mlMin, mlMax, mlDef; bool milk; float secMin, secMax, secDef; int lvlDef; } panels[] = {
    {"coffee", "☕ Кава", 110, 280, savedCoffeeMl, false, 0, 0, 0, (int)savedCoffeeStrength},
    {"espresso", "☕ Еспресо", 20, 195, savedEspressoMl, false, 0, 0, 0, (int)savedEspressoStrength},
    {"cappuccino", "🥛 Капучино", 20, 195, savedCappuccinoMl, true, 5, 90, savedCappuccinoMilkSec, (int)savedCappuccinoStrength},
    {"latte_macchiato", "🥛 Латте Макіато", 20, 195, savedLatteMl, true, 7, 90, savedLatteMilkSec, (int)savedLatteStrength},
  };
  for (auto& p : panels) {
    html += "<div id='panel_" + String(p.id) + "' style='display:none'>";
    html += "<div style='color:#f39c12;margin-bottom:8px;font-size:1.1em'>" + String(p.name) + " — налаштування</div>";
    html += "<div style='margin-bottom:4px'>Вода: <span id='" + String(p.id) + "_mlval'>" + String(p.mlDef,1) + "</span> мл</div>";
    html += "<div style='position:relative'>";
    html += "<input type='range' id='" + String(p.id) + "_ml' min='" + String(p.mlMin,0) + "' max='" + String(p.mlMax,0) + "' step='0.5' value='" + String(p.mlDef,1) +
            "' style='width:100%' oninput=\"document.getElementById('" + String(p.id) + "_mlval').innerText=this.value\">";
    html += "<div id='" + String(p.id) + "_ml_dot' style='display:none;position:absolute;top:3px;width:18px;height:18px;border-radius:50%;background:#ff2020;pointer-events:none'></div>";
    html += "</div>";
    html += "<div style='margin:10px 0 4px'>Міцність: <span id='" + String(p.id) + "_lvlval'>" + String(p.lvlDef) + "</span></div>";
    html += "<div style='position:relative'>";
    html += "<input type='range' id='" + String(p.id) + "_lvl' min='1' max='5' step='1' value='" + String(p.lvlDef) +
            "' style='width:100%' oninput=\"document.getElementById('" + String(p.id) + "_lvlval').innerText=this.value\">";
    html += "<div id='" + String(p.id) + "_lvl_dot' style='display:none;position:absolute;top:3px;width:18px;height:18px;border-radius:50%;background:#ff2020;pointer-events:none'></div>";
    html += "</div>";
    if (p.milk) {
      html += "<div style='margin:10px 0 4px'>Молоко: <span id='" + String(p.id) + "_secval'>" + String(p.secDef,1) + "</span> с</div>";
      html += "<div style='position:relative'>";
      html += "<input type='range' id='" + String(p.id) + "_sec' min='" + String(p.secMin,0) + "' max='" + String(p.secMax,0) + "' step='0.5' value='" + String(p.secDef,1) +
              "' style='width:100%' oninput=\"document.getElementById('" + String(p.id) + "_secval').innerText=this.value\">";
      html += "<div id='" + String(p.id) + "_sec_dot' style='display:none;position:absolute;top:3px;width:18px;height:18px;border-radius:50%;background:#ff2020;pointer-events:none'></div>";
      html += "</div>";
    }
    html += "<div style='display:flex;gap:8px;margin-top:14px'>";
    html += "<button id='" + String(p.id) + "_savebtn' onclick=\"saveOrProfile('" + String(p.id) + "'," + String(p.milk ? "true" : "false") + ")\" "
            "style='flex:1;padding:12px;background:#27ae60;color:#fff;border:none;border-radius:8px;font-family:monospace'>💾 Зберегти</button>";
    html += "<button id='" + String(p.id) + "_profbtn' onclick=\"toggleProfileMode('" + String(p.id) + "'," + String(p.milk ? "true" : "false") + ")\" "
            "style='flex:1;padding:12px;background:#1f6e8e;color:#fff;border:none;border-radius:8px;font-family:monospace'>📍 В профіль</button>";
    html += "<button onclick=\"resetDefault('" + String(p.id) + "')\" "
            "style='flex:1;padding:12px;background:#8e6e1f;color:#fff;border:none;border-radius:8px;font-family:monospace'>↺ Дефолт</button>";
    html += "<button onclick=\"showGrid()\" "
            "style='flex:1;padding:12px;background:#5c3a5c;color:#fff;border:none;border-radius:8px;font-family:monospace'>Відміна</button>";
    html += "</div></div>";
  }
  // True factory-confirmed defaults (verified byte-for-byte against real
  // captured commands, v3.96) — kept separate from the panels[] mlDef/
  // lvlDef/secDef above, which reflect the CURRENTLY SAVED (possibly
  // user-modified) values, not necessarily these originals.
  html += "<script>var FACTORY_DEFAULTS={";
  html += "coffee:{ml:204,lvl:3,sec:0},";
  html += "espresso:{ml:83,lvl:4,sec:0},";
  html += "cappuccino:{ml:90,lvl:3,sec:19},";
  html += "latte_macchiato:{ml:80,lvl:4,sec:31}";
  html += "};";
  html += "function resetDefault(id){";
  html += "var d=FACTORY_DEFAULTS[id];";
  html += "document.getElementById(id+'_ml').value=d.ml;document.getElementById(id+'_mlval').innerText=d.ml;";
  html += "document.getElementById(id+'_lvl').value=d.lvl;document.getElementById(id+'_lvlval').innerText=d.lvl;";
  html += "var secEl=document.getElementById(id+'_sec');if(secEl){secEl.value=d.sec;document.getElementById(id+'_secval').innerText=d.sec;}";
  html += "}</script>";
  html += "<script>var settingsMode=false;";
  html += "function showGrid(){document.getElementById('drinkGrid').style.display='grid';";
  html += "if(profileDrink){hideDots(profileDrink,true);exitProfileMode(profileDrink);}";
  html += "['coffee','espresso','cappuccino','latte_macchiato'].forEach(function(id){document.getElementById('panel_'+id).style.display='none';});}";
  html += "function handleStopClick(drinkId,stopId){";
  html += "if(settingsMode){";
  html += "var panel=document.getElementById('panel_'+drinkId);";
  html += "if(panel){document.getElementById('drinkGrid').style.display='none';panel.style.display='block';}";
  html += "else{alert('Для цього напою немає налаштувань (гаряча вода)');}";
  html += "}else{location.href='/brew?drink='+stopId;}}";
  html += "function saveSetting(id,hasMilk){";
  html += "var ml=document.getElementById(id+'_ml').value;";
  html += "var lvl=document.getElementById(id+'_lvl').value;";
  html += "var url='/setting?drink='+id+'&ml='+ml+'&level='+lvl;";
  html += "if(hasMilk){url+='&sec='+document.getElementById(id+'_sec').value;}";
  html += "fetch(url).then(function(){showGrid();});}";
  html += "var profileCycle=0,profileDrink=null;";
  html += "function showDot(sliderId,dotId,value){";
  html += "var s=document.getElementById(sliderId),d=document.getElementById(dotId);";
  html += "var min=parseFloat(s.min),max=parseFloat(s.max);";
  html += "var pct=(value-min)/(max-min)*100;if(pct<0)pct=0;if(pct>100)pct=100;";
  html += "d.style.left='calc('+pct+'% - 9px)';d.style.display='block';}";
  html += "function hideDots(id,hasMilk){";
  html += "document.getElementById(id+'_ml_dot').style.display='none';";
  html += "document.getElementById(id+'_lvl_dot').style.display='none';";
  html += "var secDot=document.getElementById(id+'_sec_dot');if(secDot)secDot.style.display='none';}";
  html += "function exitProfileMode(id){";
  html += "profileCycle=0;profileDrink=null;";
  html += "document.getElementById(id+'_profbtn').innerText='📍 В профіль';";
  html += "document.getElementById(id+'_savebtn').innerText='💾 Зберегти';}";
  html += "function toggleProfileMode(id,hasMilk){";
  html += "if(currentMachineState!=='ready'){";
  html += "var pbtn=document.getElementById('powerBtn');";
  html += "pbtn.classList.add('blinking');";
  html += "setTimeout(function(){pbtn.classList.remove('blinking');},20000);";
  html += "return;}";
  html += "if(profileDrink!==id){profileCycle=0;profileDrink=id;}";
  html += "profileCycle=profileCycle%6+1;";
  html += "document.getElementById(id+'_profbtn').innerText='📍 Профіль '+profileCycle;";
  html += "document.getElementById(id+'_savebtn').innerText='💾 Зберегти в профіль';";
  html += "var pdbtn=document.getElementById(id+'_profbtn');pdbtn.classList.add('blinking');";
  html += "fetch('/profile_peek?drink='+id+'&profile='+profileCycle).then(function(r){return r.json();}).then(function(d){";
  html += "pdbtn.classList.remove('blinking');";
  html += "if(d.error){alert('Не вдалося прочитати профіль '+profileCycle+'. Спробуй ще раз.');return;}";
  html += "showDot(id+'_ml',id+'_ml_dot',d.ml);showDot(id+'_lvl',id+'_lvl_dot',d.level);";
  html += "if(hasMilk)showDot(id+'_sec',id+'_sec_dot',d.sec);});}";
  html += "function saveOrProfile(id,hasMilk){";
  html += "if(profileCycle>0&&profileDrink===id){";
  html += "var ml=document.getElementById(id+'_ml').value;";
  html += "var lvl=document.getElementById(id+'_lvl').value;";
  html += "var url='/setting_profile?drink='+id+'&ml='+ml+'&level='+lvl+'&profile='+profileCycle;";
  html += "if(hasMilk){url+='&sec='+document.getElementById(id+'_sec').value;}";
  html += "fetch(url).then(function(r){return r.text();}).then(function(t){";
  html += "if(t=='not_ready'){alert('Машина зараз не в потрібному стані для збереження. Спробуй ще раз за кілька секунд.');return;}";
  html += "hideDots(id,hasMilk);exitProfileMode(id);showGrid();});";
  html += "}else{saveSetting(id,hasMilk);}}";
  html += "var ws=new WebSocket('ws://'+location.hostname+':81/');";
  html += "var currentMachineState='unknown';";
  html += "var paramSource=0;";  // 0=ESP32, 1-6=profile number
  html += "var sourceColors=['#3498db','#e74c3c','#e67e22','#f1c40f','#27ae60','#9b59b6','#e84393'];";
  html += "var sourceLabels=['🔌 ESP32','🔌 Профіль 1','🔌 Профіль 2','🔌 Профіль 3','🔌 Профіль 4','🔌 Профіль 5','🔌 Профіль 6'];";
  html += "function handlePowerBtnClick(){";
  html += "if(currentMachineState!=='ready'){fetch('/brew?drink=power_on');return;}";
  html += "paramSource=(paramSource+1)%7;";
  html += "var btn=document.getElementById('powerBtn');";
  html += "btn.innerText=sourceLabels[paramSource];";
  html += "btn.style.background=sourceColors[paramSource];";
  html += "if(paramSource===0){fetch('/param_source?value=0');return;}";
  html += "btn.classList.add('blinking');";
  html += "fetch('/param_ping?profile='+paramSource).then(function(){btn.classList.remove('blinking');});}";
  html += "ws.onmessage=function(e){var d=JSON.parse(e.data);";
  html += "document.getElementById('machineConn').innerText=d.machineConnected?'✅':'❌';";
  html += "document.getElementById('phoneConn').innerText=d.phoneConnected?'✅':'❌';";
  html += "var stateMap={asleep:'asleep/спить 😴',waking:'waking/просипається 🤔',ready:'ready/готова 🙂',offline:'offline/офлайн ❌'};";
  html += "document.getElementById('machineState').innerText=d.brewingActive?(d.machineState+'/готується 🥳'):(stateMap[d.machineState]||(d.machineState+'/невідомо ❓'));";
  html += "document.getElementById('powerBtn').classList.toggle('blinking', d.showWakePrompt);";
  html += "var pbtn=document.getElementById('powerBtn');";
  html += "if(d.machineState==='ready'){";
  html += "if(pbtn.innerText==='🔌 Увімкнути'){pbtn.innerText=sourceLabels[paramSource];pbtn.style.background=sourceColors[paramSource];}";
  html += "}else{";
  html += "paramSource=0;pbtn.innerText='🔌 Увімкнути';pbtn.style.background='#3498db';}";
  html += "currentMachineState=d.machineState;";
  html += "document.getElementById('mqttConn').innerText=d.mqttConnected?'✅':'❌';";
  html += "document.getElementById('pktCount').innerText=d.packetCount;";
  html += "document.getElementById('age').innerText=d.age;";
  html += "document.getElementById('waterMsg').innerText=d.waterMessage;";
  html += "document.getElementById('milkMsg').innerText=d.milkMessage;";
  html += "document.getElementById('groundsMsg').innerText=d.groundsMessage;";
  html += "document.getElementById('beansMsg').innerText=d.beansMessage;";
  html += "var ic=['iconWaterMissing','iconWaterLow','iconGroundsMissing','iconGroundsFull','iconMilkMissing','iconMilkClean','iconBeansEmpty','iconWarmup'];ic.forEach(function(i){document.getElementById(i).style.display='none';});";
  html += "document.getElementById('monitorAlarmSlot').style.display='none';";
  html += "document.getElementById('brewCup').style.display='none';";
  html += "document.getElementById('iconBar').style.display='none';";
  html += "document.getElementById('brewName').innerText='';document.getElementById('brewPct').innerText='';";
  html += "if(d.waterState=='missing'){document.getElementById('iconSlot').style.display='block';document.getElementById('iconWaterMissing').style.display='inline';}";
  html += "else if(d.waterState=='low'){document.getElementById('iconSlot').style.display='block';document.getElementById('iconWaterLow').style.display='inline';}";
  html += "else if(d.groundsState=='missing'){document.getElementById('iconSlot').style.display='block';document.getElementById('iconGroundsMissing').style.display='inline';}";
  html += "else if(d.groundsState=='full'){document.getElementById('iconSlot').style.display='block';document.getElementById('iconGroundsFull').style.display='inline';}";
  html += "else if(d.beansState=='empty'){document.getElementById('iconSlot').style.display='block';document.getElementById('iconBeansEmpty').style.display='inline';}";
  html += "else if(d.monitorAlarmText){document.getElementById('iconSlot').style.display='block';document.getElementById('monitorAlarmSlot').style.display='inline';document.getElementById('monitorAlarmSlot').innerText='❗ '+d.monitorAlarmText;}";
  html += "else if(d.milkState=='missing'){document.getElementById('iconSlot').style.display='block';document.getElementById('iconMilkMissing').style.display='inline';}";
  html += "else if(d.milkState=='clean'){document.getElementById('iconSlot').style.display='block';document.getElementById('iconMilkClean').style.display='inline';}";
  html += "else if(d.isWarming){document.getElementById('iconSlot').style.display='block';document.getElementById('iconWarmup').style.display='inline';";
  html += "document.getElementById('iconBar').style.display='block';document.getElementById('iconBarFill').style.width=d.warmupPct+'%';";
  html += "document.getElementById('brewName').innerText='Прогрів';}";
  html += "else if(d.brewingActive){document.getElementById('iconSlot').style.display='block';document.getElementById('brewCup').style.display='block';";
  html += "document.getElementById('brewFill').style.height=d.brewingPct+'%';";
  html += "document.getElementById('brewName').innerText=d.brewingName;document.getElementById('brewPct').innerText=d.brewingPct+'%';}";
  html += "else{document.getElementById('iconSlot').style.display='none';}};";
  html += "ws.onclose=function(){setTimeout(function(){location.reload();},3000);};";
  html += "</script>";
  html += "</body></html>";
  server.send(200, "text/html; charset=utf-8", html);
}

void setup() {
  Serial.begin(115200);
  delay(500);

  prefs.begin("mitm", false);
  advImmediate = prefs.getBool("advImmediate", false);
  delonghiMac = prefs.getString("machineMac", delonghiMac);
  mqttHost = prefs.getString("mqttHost", mqttHost);
  mqttPort = prefs.getInt("mqttPort", mqttPort);
  mqttUser = prefs.getString("mqttUser", mqttUser);
  mqttPass = prefs.getString("mqttPass", mqttPass);
  staticIP = prefs.getString("staticIP", staticIP);
  staticGateway = prefs.getString("staticGateway", staticGateway);
  staticSubnet = prefs.getString("staticSubnet", staticSubnet);
  savedEspressoMl = prefs.getFloat("esprMl", savedEspressoMl);
  savedEspressoStrength = prefs.getFloat("esprStr", savedEspressoStrength);
  savedCoffeeMl = prefs.getFloat("coffMl", savedCoffeeMl);
  savedCoffeeStrength = prefs.getFloat("coffStr", savedCoffeeStrength);
  savedCappuccinoMl = prefs.getFloat("cappMl", savedCappuccinoMl);
  savedCappuccinoStrength = prefs.getFloat("cappStr", savedCappuccinoStrength);
  savedCappuccinoMilkSec = prefs.getFloat("cappMilk", savedCappuccinoMilkSec);
  savedLatteMl = prefs.getFloat("latteMl", savedLatteMl);
  savedLatteStrength = prefs.getFloat("latteStr", savedLatteStrength);
  savedLatteMilkSec = prefs.getFloat("latteMilk", savedLatteMilkSec);
  rgbBrightness = prefs.getInt("rgbBri", rgbBrightness);
  computeFakeMac(delonghiMac);

  esp_base_mac_addr_set(FAKE_MAC);
  rgb.begin(); rgb.setBrightness(rgbBrightness); setRGB(255, 0, 0);
  if (Serial) { Serial.println("DeLonghi MITM C6 " + String(FW_VERSION));
  Serial.println("DeLonghi MITM C6 " + String(FW_VERSION)); }
  if (Serial) { Serial.println("Adv mode: " + String(advImmediate ? "immediate" : "after-connect"));
  Serial.println("Adv mode: " + String(advImmediate ? "immediate" : "after-connect")); }
  if (Serial) { Serial.println("Machine MAC: " + delonghiMac);
  Serial.println("Machine MAC: " + delonghiMac); }

  WiFiManager wm;
  wm.setHostname(HOSTNAME);
  wm.setConfigPortalTimeout(180);
  if (staticIP.length() > 0 && staticGateway.length() > 0) {
    IPAddress ip, gw, sn;
    ip.fromString(staticIP);
    gw.fromString(staticGateway);
    sn.fromString(staticSubnet);
    wm.setSTAStaticIPConfig(ip, gw, sn);
    if (Serial) { Serial.println("Using static IP: " + staticIP);
    Serial.println("Using static IP: " + staticIP); }
  }
  setRGB(128, 0, 128);  // purple while connecting to Wi-Fi / in setup portal
  if (!wm.autoConnect("DeLonghi-C6-Setup")) ESP.restart();
  if (Serial) { Serial.println("WiFi: " + WiFi.localIP().toString());
  Serial.println("WiFi: " + WiFi.localIP().toString()); }

  ArduinoOTA.setHostname(HOSTNAME);
  ArduinoOTA.begin();
  server.on("/", handleRoot);
  server.on("/icon.png", HTTP_GET, []() {
    server.send_P(200, "image/png", (const char*)coffeeIconPng, coffeeIconPngLen);
  });
  server.on("/manifest.json", HTTP_GET, []() {
    String m = "{\"name\":\"PrimaDonna\",\"short_name\":\"PrimaDonna\",";
    m += "\"start_url\":\"/\",\"display\":\"standalone\",";
    m += "\"background_color\":\"#1a1a2e\",\"theme_color\":\"#1a1a2e\",";
    m += "\"icons\":[{\"src\":\"/icon.png\",\"sizes\":\"96x96\",\"type\":\"image/png\"}]}";
    server.send(200, "application/json", m);
  });
  server.on("/qr.png", HTTP_GET, []() {
    server.send_P(200, "image/png", (const char*)qrCodePng, qrCodePngLen);
  });
  server.on("/info", HTTP_GET, handleInfo);
  server.on("/debug_log", HTTP_GET, handleDebugLog);
  server.on("/rgb_brightness", HTTP_GET, handleRgbBrightness);
  server.on("/reboot", HTTP_GET, []() {
    server.send(200, "text/html", "<html><body style='background:#1a1a2e;color:#fff;font-family:sans-serif;padding:20px'>Перезавантаження...</body></html>");
    delay(500);
    ESP.restart();
  });
  server.on("/adv", handleAdv);
  server.on("/settings", handleSettings);
  server.on("/wifi", handleWifiPortal);
  server.on("/brew", handleBrew);
  server.on("/setting", handleSetting);
  server.on("/setting_profile", handleSettingProfile);
  server.on("/profile_peek", handleProfilePeek);
  server.on("/param_source", handleParamSource);
  server.on("/param_ping", handleParamPing);
  server.on("/update", HTTP_GET, handleUpdatePage);
  server.on("/doupdate", HTTP_POST, handleDoUpdate, handleUpdateUpload);
  server.begin();
  webSocket.begin();
  webSocket.onEvent(webSocketEvent);

  NimBLEDevice::init(FAKE_NAME);
  // Previously (false,false,false) explicitly disabled bonding/pairing —
  // that was fine while we assumed encryption was irrelevant, but real
  // direct-connection captures show the phone attempting LL_ENC_REQ mid-
  // session (and sniffers on real connections usually go "Anonymous"),
  // which our peripheral could never gracefully accept before. Enable
  // bonding + Just Works (no IO capability) so if the phone tries, we can
  // actually complete it instead of silently failing.
  NimBLEDevice::setSecurityAuth(/*bonding*/ true, /*mitm*/ false, /*sc*/ true);
  NimBLEDevice::setSecurityIOCap(BLE_HS_IO_NO_INPUT_OUTPUT);

  bleServer = NimBLEDevice::createServer();
  bleServer->setCallbacks(new ServerCallbacks());

  NimBLEService* fakeSvc = bleServer->createService(SERVICE_UUID);
  fakeChar = fakeSvc->createCharacteristic(
    CHAR_UUID,
    NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::WRITE |
    NIMBLE_PROPERTY::WRITE_NR | NIMBLE_PROPERTY::NOTIFY | NIMBLE_PROPERTY::INDICATE
  );
  fakeChar->setCallbacks(new CharCallbacks());

  fakeChar2 = fakeSvc->createCharacteristic(
    CHAR2_UUID,
    NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::WRITE | NIMBLE_PROPERTY::WRITE_NR
  );
  fakeChar2->setCallbacks(new Char2Callbacks());
  fakeChar2->setValue((uint8_t*)REAL_SERIAL, strlen(REAL_SERIAL));
  fakeSvc->start();

  NimBLEAdvertising* adv = NimBLEDevice::getAdvertising();
  adv->addServiceUUID(SERVICE_UUID);
  adv->setName(FAKE_NAME);
  if (advImmediate) {
    adv->start();
    if (Serial) { Serial.println("Advertising as " FAKE_NAME " (immediate mode)");
    Serial.println("Advertising as " FAKE_NAME " (immediate mode)"); }
  }
  // else: left to connectToMachine(), which starts it only once the real
  // machine link is confirmed, to avoid a MAC collision with our own
  // central-side connect attempt below.

  connectToMachine();
  if (Serial) { Serial.println("Ready!");
  Serial.println("Ready!"); }
}

unsigned long lastMachineRetry = 0;

void loop() {
  ArduinoOTA.handle();
  server.handleClient();
  webSocket.loop();
  // v4.43: periodic heartbeat, completely independent of any BLE/packet
  // event — the only thing that tells us whether loop() itself is still
  // alive during a freeze, vs. BLE notifications simply having stopped
  // arriving (two very different problems that looked identical in the
  // debug log so far, since ALL our previous log lines were event-
  // triggered and stayed silent either way). If this line keeps appearing
  // every ~2s even while packet-related lines go quiet, loop() is fine —
  // the machine/BLE stack stopped delivering data. If THIS also stops,
  // loop() itself is genuinely hung somewhere.
  static unsigned long lastHeartbeat = 0;
  if (millis() - lastHeartbeat > 2000) {
    lastHeartbeat = millis();
    debugLog("heartbeat: heap=%d machineConnected=%d fragCount=%d brewingActive=%d wifi=%d mqtt=%d",
             ESP.getFreeHeap(), machineConnected, fragCount, brewingActive,
             WiFi.status() == WL_CONNECTED, mqtt.connected());
  }
  static unsigned long lastBroadcast = 0;
  if (millis() - lastBroadcast > 500) {
    lastBroadcast = millis();
    broadcastLiveState();
  }
  updateRGB();

  // MQTT: keep connection alive, reconnect every 5s if dropped
  if (mqttHost.length() > 0) {
    if (!mqtt.connected()) {
      if (millis() - lastMqttReconnectAttempt > 5000) {
        lastMqttReconnectAttempt = millis();
        mqttReconnect();
      }
    } else {
      mqtt.loop();
    }
  }

  // Self-poll machine status every 5s, but ONLY when the phone isn't
  // connected — so MQTT/HA still knows the state when CoffeeLink is
  // closed, without ever interleaving with a live CoffeeLink session.
  // v4.16 tried to also self-poll when the phone stays BLE-connected but
  // goes idle (background app, no real requests) — that part was right,
  // but it judged "idle" using lastAnyPacketAt, which is only touched
  // inside maybeParseStatus() for a fully-reassembled 0x75 packet, not
  // on every raw BLE notification. During brewing the machine can go
  // quiet on 0x75 specifically for well over 30s while still mid-
  // conversation on other traffic, so v4.16 sometimes injected a
  // self-poll query DURING an active brew/CoffeeLink exchange —
  // corrupting the shared fragment reassembly buffer (see the collision
  // note in handleProfilePeek() above) and producing exactly what was
  // seen live: state misread as asleep + missing brew_progress.
  // v4.17 fixes this with three independent guards instead of one:
  //  - lastUpdate instead of lastAnyPacketAt — set on EVERY raw BLE
  //    notification in notifyFromMachine(), not just parsed 0x75
  //    packets, so a live session can't be misjudged as idle just
  //    because the last packet happened to be a different type
  //  - fragCount == 0 — never inject while a multi-fragment response is
  //    actively being reassembled
  //  - !brewingActive — never self-poll during a brew cycle at all,
  //    regardless of idle time, since that's the highest-risk window
  //  - idle threshold raised 30s -> 45s for extra margin
  //
  // v4.28 FIX: user confirmed v4.15 (before ANY self-poll-while-phone-
  // connected logic existed) ran rock-stable for hours, while intermittent
  // BLE hangs (peripheral advertising stopped responding to CoffeeLink
  // entirely) started showing up sometime after this self-poll widening.
  // No smoking gun found in the actual code — no leak, no blocking call —
  // but the widening DOES mean substantially more real BLE central traffic
  // (actual radio writes/reads, not just cheap comparisons) sustained over
  // long uptimes on a stack that already juggles central+peripheral roles
  // simultaneously, which is documented elsewhere in this file as
  // inherently fragile. Softening rather than reverting outright, since
  // the underlying bug this was fixing (attention_type freezing for hours
  // when CoffeeLink sits idle-but-connected in the background) is real:
  //  - the phone-truly-disconnected path (the ORIGINAL, proven-stable
  //    v4.15 behavior) is untouched — still polls every 5s, exactly as
  //    before this whole feature existed
  //  - the phone-idle fallback (the NEW part) requires 45s of silence
  //    (v4.29 briefly tried 5 minutes to cut BLE traffic further, but
  //    confirmed live: that made physically waking the machine while
  //    CoffeeLink sat idle-connected take up to minutes to even be
  //    noticed, since NO self-poll happens at all before the threshold
  //    trips — reverted the wait back to the original 45s, keeping only
  //    the gentler 30s cadence once active, which still meaningfully
  //    cuts sustained traffic vs the old 5s without hurting responsiveness)
  //
  // v4.33: skip self-poll entirely whenever the machine is already
  // actively self-broadcasting on its own (brewing or warming up) —
  // confirmed live that the machine sends unsolicited 0x75 status packets
  // continuously during both, so a self-poll query in that window is pure
  // waste (and, per the just-observed web-dashboard slowdown to ~4s
  // updates during exactly a warmup/brew test, possibly contended BLE
  // radio time).
  // v4.35 FIX: v4.33 decided "already broadcasting" from the machineState
  // LABEL ("waking") rather than from actual data flow — confirmed live
  // this was a serious regression: if the state ever gets stuck on
  // "waking" (a real scenario, e.g. the phantom-transition edge cases
  // fixed elsewhere in this file), self-poll now ALSO stops firing
  // because the label says "it's broadcasting anyway" — even when it
  // genuinely isn't. Result: total data freeze, confirmed live (func/exec
  // frozen unchanged for 2+ minutes spanning a real brew attempt, 0
  // drinks detected). Fixed by checking actual packet freshness
  // (lastUpdate, already tracked from every raw BLE notification) instead
  // of the label — self-poll now only backs off while data is GENUINELY
  // still arriving recently, and automatically resumes the moment real
  // packets stop, regardless of what machineState/brewingActive currently
  // claim. This is strictly more self-healing than the label check.
  //
  // v4.36: recentPacketFlow alone should rarely let self-poll fire mid-
  // brew (packets arrive frequently while brewing), but "rarely" isn't
  // "never" — restoring the explicit !brewingActive && fragCount==0 guard
  // (originally added in v4.17 to stop self-poll from colliding with a
  // live fragment reassembly and corrupting brew%) on the MAIN path too,
  // not just the phone-idle sub-path. Belt-and-suspenders: never inject a
  // query during an active brew or mid-fragment, regardless of how fresh
  // the last packet was.
  bool phoneSessionIdle = phoneConnected && !brewingActive && fragCount == 0 &&
      (millis() - lastUpdate > 45000);
  unsigned long selfPollInterval = phoneConnected ? 30000 : 5000;
  bool recentPacketFlow = (millis() - lastUpdate < 3000);
  if (machineConnected && !recentPacketFlow && !brewingActive && fragCount == 0 &&
      (!phoneConnected || phoneSessionIdle) && bleChar &&
      millis() - lastSelfStatusPoll > selfPollInterval &&
      millis() - lastMqttPublishAt > 200) {
    lastSelfStatusPoll = millis();
    uint8_t cmd[] = {0x0d,0x04,0x75,0x0f,0x26};
    bleChar->writeValue(cmd, sizeof(cmd), false);
  }
  if (!machineConnected) publishMachineState("offline");
  // v4.37: shortened 5min -> 90s. This is now only the fallback for a brew
  // armed purely via %-trend (brewingUsesRealSignal never went true) —
  // the common case self-heals within seconds via the fast clear above.
  // 90s is generous for any real drink (longest is roughly a milk-heavy
  // latte/cappuccino) plus margin, without leaving the bridge frozen for
  // minutes on end if this fallback path is the one that got used.
  if (brewingActive && millis() - brewingStartedAt > 90000) brewingActive = false;  // 90s safety cap (fallback only)

  // Wi-Fi watchdog: MQTT already retries every 5s, but Wi-Fi itself
  // never had any self-healing — it connects once via WiFiManager in
  // setup() and if it ever drops, previously just sat there forever
  // requiring a manual power cycle. Now: if disconnected for >30s, try
  // a soft reconnect; if that hasn't worked after 2 minutes total,
  // do a full restart as a last resort (safer than staying stuck offline
  // indefinitely — a reboot is quick and this device has no state that
  // needs to survive a restart, brewingActive's own 5min cap already
  // accepts a restart mid-brew as tolerable).
  static unsigned long wifiDownSince = 0;
  static bool wifiReconnectTried = false;
  if (!otaInProgress && WiFi.status() != WL_CONNECTED) {
    if (wifiDownSince == 0) wifiDownSince = millis();
    if (!wifiReconnectTried && millis() - wifiDownSince > 30000) {
      wifiReconnectTried = true;
      WiFi.reconnect();
    }
    if (millis() - wifiDownSince > 120000) {
      ESP.restart();
    }
  } else {
    wifiDownSince = 0;
    wifiReconnectTried = false;
  }

  // Self-probe disabled: now that the serial-request interception is
  // removed, CoffeeLink asks a3f0/a4f0 etc. on its own — firing our own
  // probe in parallel just adds redundant traffic to the machine. Keeping
  // sendSettingsSyncProbe() defined in case it's useful again later.
  // if (machineConnected && wakeDetectedAt > 0 && !settingsSyncSent &&
  //     millis() - wakeDetectedAt > 19000) {
  //   settingsSyncSent = true;
  //   sendSettingsSyncProbe();
  // }

  if (connectingToMachine && !machineConnected) {
    connectingToMachine = false;
    delay(500);
    connectToMachine();
  }

  if (fragCount > 0 && (millis() - lastFragmentTime > 120)) {
    forwardFragmentsToPhone();
  }

  if (machineConnected && bleClient && !bleClient->isConnected()) {
    if (Serial) { Serial.println("Machine lost!");
    Serial.println("Machine lost!"); }
    machineConnected = false;
    bleChar = nullptr;
    if (!advImmediate) NimBLEDevice::getAdvertising()->stop();
    connectToMachine();
  }

  // Safety net: if we're not connected to the machine and nothing else is
  // driving a retry (e.g. the very first connect attempt in setup() failed,
  // so no phone can ever connect to trigger connectingToMachine), keep
  // retrying periodically instead of getting stuck until a manual reboot.
  if (!machineConnected && !connectingToMachine) {
    if (millis() - lastMachineRetry > 10000) {
      lastMachineRetry = millis();
      if (Serial) { Serial.println("Periodic retry: not connected to machine, retrying...");
      Serial.println("Periodic retry: not connected to machine, retrying..."); }
      connectToMachine();
    }
  }
}
