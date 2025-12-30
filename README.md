# PPN_ESP32_Projekt_Siczek_68386

## Opis projektu

Projekt przedstawia implementację prostej sygnalizacji świetlnej
zrealizowanej na mikrokontrolerze ESP32 z wykorzystaniem maszyny stanów (FSM).

System posiada:
- trzy diody LED (zielona, żółta, czerwona),
- przycisk sterujący,
- tryb awaryjny SAFE,
- logi diagnostyczne przez UART.

Projekt został wykonany w języku C++ z użyciem frameworka Arduino
i uruchamiany w symulatorze Wokwi.

---

## Wymagania

- Windows 10
- Visual Studio Code
- PlatformIO Extension
- Dostęp do platformy Wokwi (symulacja ESP32)

---

## Struktura projektu

PPN_ESP32_Projekt_Siczek_68386/
├─ src/
│ └─ main.cpp
├─ include/
├─ lib/
├─ test/
├─ .pio/
├─ platformio.ini
├─ wokwi.toml
├─ diagram.json
├─ README.md
├─ design.md
└─ tests.md


---

## Uruchomienie projektu (krok po kroku)

### 1. Otwarcie projektu

1. Uruchom Visual Studio Code
2. Otwórz folder: PPN_ESP32_Projekt_Siczek_68386

---

### 2. Budowanie projektu

1. W VS Code kliknij ikonę **PlatformIO**
2. Wybierz: PlatformIO: Build
lub kliknij ikonę ✔ na dolnym pasku

Po poprawnym buildzie zostanie wygenerowany plik:
.pio/build/esp32dev/firmware.elf

---

### 3. Uruchomienie symulacji w Wokwi

1. Otwórz Command Palette: Ctrl + Shift + P
2. Wybierz: Wokwi: Start Simulation
3. Otwórz **Serial Monitor**, aby zobaczyć logi systemowe

---

## Zasada działania

- System startuje w trybie normalnym (RUN)
- Diody zmieniają się automatycznie:
- zielona → żółta → czerwona
- **Krótkie naciśnięcie przycisku**
- natychmiastowe przejście do następnego stanu
- **Długie przytrzymanie przycisku (>3 s)**
- aktywacja trybu SAFE (migająca dioda żółta)

---

## Tryb SAFE

Tryb SAFE sygnalizuje stan awaryjny systemu:
- migająca dioda żółta,
- brak przejść czasowych,
- wyłączone pozostałe diody LED.

Tryb SAFE może zostać aktywowany wyłącznie przez długie
przytrzymanie przycisku.

---

## Autor

- Imię i nazwisko: **Andrzej Siczek**
- Numer albumu: **68386**
