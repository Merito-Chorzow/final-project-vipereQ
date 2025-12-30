# Design – Sygnalizacja świetlna ESP32

## 1. Cel projektu

Celem projektu jest implementacja prostej sygnalizacji świetlnej
na mikrokontrolerze ESP32 z wykorzystaniem maszyny stanów (FSM),
przycisku sterującego oraz trybu awaryjnego SAFE.

Projekt został wykonany w środowisku PlatformIO (framework Arduino)
i uruchamiany w symulatorze Wokwi.

---

## 2. Architektura systemu

System składa się z następujących elementów:

- **Wejście**
  - przycisk (GPIO19, INPUT_PULLUP)
- **Wyjście**
  - diody LED:
    - zielona (GPIO21)
    - żółta (GPIO22)
    - czerwona (GPIO23)
- **Logika sterująca**
  - maszyna stanów FSM
- **Interfejs diagnostyczny**
  - UART (Serial Monitor)

Architektura ma charakter jednowątkowy i opiera się na pętli `loop()`
oraz funkcji czasu `millis()` (bez użycia opóźnień blokujących).

---

## 3. Maszyna stanów (FSM)

System pracuje w oparciu o cztery stany:

- **GREEN** – światło zielone
- **YELLOW** – światło żółte
- **RED** – światło czerwone
- **SAFE** – tryb awaryjny (migające światło żółte)

### 3.1 Diagram FSM (opisowy)

GREEN --(czas / klik)--> YELLOW
YELLOW --(czas / klik)--> RED
RED --(czas / klik)--> GREEN

GREEN/YELLOW/RED --(przycisk > 3s)--> SAFE


---

## 4. Logika sterowania

### 4.1 Praca automatyczna

W trybie normalnym stany zmieniają się automatycznie po upływie
zadanego czasu:

- GREEN – 5 s
- YELLOW – 2 s
- RED – 5 s

### 4.2 Sterowanie przyciskiem

- **Krótkie naciśnięcie przycisku**
  - wymusza natychmiastowe przejście do następnego stanu
- **Długie przytrzymanie (> 3 s)**
  - przełącza system w tryb SAFE

Zastosowano programowy debounce przycisku.

---

## 5. Tryb SAFE

Tryb SAFE sygnalizuje stan awaryjny systemu:

- migająca dioda żółta
- wyłączone pozostałe diody
- brak automatycznych przejść między stanami

Tryb SAFE może zostać aktywowany wyłącznie przez długie
przytrzymanie przycisku.

---

## 6. Logi i diagnostyka

System wysyła komunikaty diagnostyczne przez UART, m.in.:

- zmiany stanów FSM
- aktywację trybu SAFE
- zdarzenia przycisku

Logi są widoczne w Serial Monitorze środowiska Wokwi.
