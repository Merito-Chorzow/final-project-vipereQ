# Tests – Sygnalizacja świetlna ESP32

## Informacje ogólne

Testy zostały przeprowadzone manualnie w środowisku symulacyjnym Wokwi
z wykorzystaniem Serial Monitora jako interfejsu diagnostycznego.

Celem testów było sprawdzenie poprawności działania maszyny stanów (FSM),
obsługi przycisku oraz trybu SAFE.

---

## Test 1 – Start systemu

**Opis:**
Sprawdzenie zachowania systemu po uruchomieniu programu.

**Kroki:**
1. Uruchomić symulację w Wokwi
2. Obserwować diody LED oraz Serial Monitor

**Oczekiwany rezultat:**
- system startuje w stanie GREEN
- zapala się dioda zielona
- brak aktywacji trybu SAFE

**Wynik:**  
 OK

---

## Test 2 – Automatyczne przejścia czasowe

**Opis:**
Sprawdzenie automatycznych przejść FSM w trybie normalnym.

**Kroki:**
1. Nie naciskać przycisku
2. Obserwować diody LED

**Oczekiwany rezultat:**
- GREEN → YELLOW po ok. 5 s
- YELLOW → RED po ok. 2 s
- RED → GREEN po ok. 5 s
- cykl powtarza się

**Wynik:**  
OK

---

## Test 3 – Krótkie naciśnięcie przycisku

**Opis:**
Sprawdzenie reakcji systemu na krótkie naciśnięcie przycisku.

**Kroki:**
1. Krótko nacisnąć przycisk (poniżej 1 s)
2. Obserwować diody LED oraz logi w Serial Monitorze

**Oczekiwany rezultat:**
- natychmiastowe przejście do następnego stanu FSM
- w Serial Monitorze pojawia się komunikat:

Przycisk: szybkie przejscie

**Wynik:**  
✅ OK

---

## Test 4 – Wielokrotne krótkie naciśnięcia

**Opis:**
Sprawdzenie odporności systemu na drgania styków (debounce).

**Kroki:**
1. Kilkukrotnie szybko nacisnąć przycisk
2. Obserwować zachowanie systemu

**Oczekiwany rezultat:**
- każde naciśnięcie powoduje pojedyncze przejście FSM
- brak wielokrotnych przejść dla jednego kliknięcia

**Wynik:**  
 OK

---

## Test 5 – Długie przytrzymanie przycisku (SAFE)

**Opis:**
Sprawdzenie aktywacji trybu SAFE.

**Kroki:**
1. Przytrzymać przycisk przez co najmniej 3 sekundy
2. Obserwować diody LED oraz Serial Monitor

**Oczekiwany rezultat:**
- system przechodzi do trybu SAFE
- miga dioda żółta
- w Serial Monitorze pojawia się komunikat:

!!! SAFE AKTYWOWANY !!!

**Wynik:**  
OK

---

## Test 6 – Zachowanie systemu w trybie SAFE

**Opis:**
Sprawdzenie zachowania FSM w trybie SAFE.

**Kroki:**
1. Pozostawić system w trybie SAFE
2. Obserwować diody LED

**Oczekiwany rezultat:**
- brak automatycznych przejść FSM
- miganie wyłącznie diody żółtej
- diody zielona i czerwona wyłączone

**Wynik:**  
 OK

---

## Podsumowanie testów

Wszystkie testy zakończyły się wynikiem pozytywnym.
System działa zgodnie z założeniami projektowymi i spełnia
wymagania funkcjonalne projektu semestralnego.
