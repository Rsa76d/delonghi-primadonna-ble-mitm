# DeLonghi PrimaDonna ELITE — BLE MITM міст (ESP32-C6)

ESP32-C6 працює як dual-role MITM між кавомашиною та телефоном і дає повну інтеграцію з Home Assistant через MQTT.

- **central → кавомашина** (ECAM 656.75), **peripheral → телефон** (застосунок CoffeeLink)
- MQTT + discovery для Home Assistant
- Веб-інтерфейс: керування, налаштування, `/presence` (радар), `/debug_log`
- Радар LD2410C (присутність і рух) як окремі сенсори HA
- Керування WLED-матрицею 16×16: кавові анімації, погода, тривога (JAAM)

## Поточна версія

**v4.58-C6-MITM-gaps** — `firmware/current/`

## Структура

| Папка | Вміст |
|---|---|
| `firmware/current/` | Актуальна прошивка (`.ino` + `.bin`) |
| `firmware/history/` | Усі попередні версії v4.16 → v4.57 (`.ino` + `.bin`) |
| `docs/` | Мануал і документація (MD + PDF) |
| `home-assistant/` | Автоматизації, помічники, `rest_command` для WLED |

## Збірка

```bash
arduino-cli compile --fqbn "esp32:esp32:esp32c6:PartitionScheme=min_spiffs,CDCOnBoot=default" <папка_скетча> --export-binaries
```

Бібліотеки: NimBLE-Arduino (гілка 2.3.4), PubSubClient, WiFiManager, Adafruit_NeoPixel, WebSockets, ld2410 (ncmreynolds, v0.2.2).

> `CDCOnBoot=default` (вимкнено) обов'язково: USB Serial не працює, діагностика через `/debug_log`.

## Залізо

- ESP32-C6-WROOM-1
- LD2410C: VCC→5V, GND→GND, TX модуля→GPIO6, RX модуля→GPIO7 (256000 бод)
- WLED 16×16 (ESP32 Classic, WLED 16.0.1)

## MQTT-топіки

| Топік | Значення |
|---|---|
| `delonghi/state` (retained) | asleep / waking / ready / offline |
| `delonghi/availability` | online / offline (LWT) |
| `delonghi/attention_type` (retained) | water / grounds / beans / "" |
| `delonghi/brew_progress` (retained) | 0–100 |
| `delonghi/param_source` (retained) | "ESP32" / "Профіль N" |
| `delonghi/cmd` | coffee, espresso, cappuccino, latte_macchiato, hot_water, stop, profile_cycle, power_on |
| `delonghi/radar_motion` (retained) | on / off |
| `delonghi/radar_presence` (retained) | on / off |

## Протокол (підтверджено)

- Контрольна сума = XOR усіх байтів XOR 0x55
- `byte[25]` = прогрес приготування (0–100)
- `byte[19]` = func, `byte[20]` = exec: func==0 → сон; func==7, exec==0 → готова; func==7, exec≠0 → подача кави; func==11, exec==3 → гаряча вода
- Перемикання профілю: `0d 05 A9 F0 <profileId> <checksum>`
- Віддалене вимкнення живлення неможливе

## Home Assistant

У `home-assistant/`:

- `HA_автоматизації_і_помічники.yaml` — автоматизації та помічники
- `rest_command_wled_v2.yaml` — `rest_command` для WLED; `wled_weather` використовує сенсори JAAM `binary_sensor.jaam_546ec0c40a24_{red,yellow}_alert_level`
- `automation_trivoha_na_matrytsi.yaml` — автоматизація "Тривога на матриці"

ID сенсорів JAAM прив'язані до конкретного пристрою (`546ec0c40a24`). Для свого пристрою замініть їх на власні.

## Ключові виправлення (v4.33 → v4.58)

- `brewingActive` скидається за часом (15 с безперервного func==0), а не за кількістю читань
- Будь-який ненульовий func скидає лічильник простою
- `attention_type` публікується незалежно від веб-клієнтів
- `Serial.*` захищено `if(Serial)`, а `CDCOnBoot` вимкнено, бо без USB-хоста Serial блокував loop
- Межа BLE-фрагмента визначається заявленою довжиною (`byte[1]`), а не тишею 120 мс
- Неблокуючі RGB-патерни без `delay()`: єдиний 4-секундний цикл

## Відомі обмеження

- `drinksToday` не скидається опівночі (немає RTC), лічильник рахується до перезавантаження
- Підписка на NOTIFY, а не INDICATE: INDICATE давав більше сміттєвих пакетів
