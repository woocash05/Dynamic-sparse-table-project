# Dynamic-sparse-table-project
Projekt zaawansowanej struktury danych typu Dynamic Sparse Table,  opartej na specyficznej odmianie drzewa Trie (cyfrowego). Zrealizowany  w ramach kursu Algorytmy i Struktury Danych jako wydajniejsza  alternatywa dla tablic haszowanych w scenariuszach pesymistycznych.

Funkcje i mechanika
-------------------
- Architektura Trie (n, k): Wielostopniowa struktura drzewiasta, w ktorej 
  korzen posiada n potomkow, a kazdy kolejny poziom posiada k potomkow.
- Hybrydowe przechowywanie: Kazdy wezel (zarowno wewnetrzny, jak 
  i lisc) moze przechowywac klucz, co optymalizuje wykorzystanie pamieci.
- Adresowanie modulo: Wstawianie i wyszukiwanie oparte na sekwencji 
  operacji modulo (x % n na pierwszym poziomie, nastepnie div % k), 
  co zapewnia deterministyczna sciezke dostepu do danych.
- Algorytm usuwania (Leaf-Replacement): Implementacja specyficznej 
  logiki zastepowania usuwanego klucza wewnetrznego wartoscia z 
  najbardziej lewego wezla zewnetrznego (liscia).



Technologie i biblioteki
------------------------
- Jezyk: C++
- Zarzadzanie pamiecia: Manualna alokacja i dealokacja pamieci przy 
  uzyciu wskaznikow do wskaznikow (rootChild**, childChild**).
- Algorytmy:
    * Rekurencyjna czystka pamieci (cleanup) zapobiegajaca wyciekom.
    * Przeglad drzewa w porzadku Preorder.
    * Algorytm szukania kandydata do usuniecia (searchCandidateToDelete).

Instrukcja obslugi
------------------
1.  Obslugiwane komendy:
   - I x: Wstaw klucz x (unikalnosc sprawdzana automatycznie).
   - L x: Wyszukaj klucz x (wynik: exist/not exist).
   - D x: Usun klucz x z procedura reorganizacji wezlow (leaf search).
   - P  : Wyswietl strukture drzewa w formacie Preorder.

2. Konfiguracja:
   Program wczytuje liczbe przypadkow, zakres uniwersum oraz parametry 
   n i k przed wykonaniem instrukcji.

Autor: Łukasz Steciuk
========================================================================
