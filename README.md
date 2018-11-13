# Zaawansowane Metody Programowania Obiektowego – zadanie 3
## Użycie obiektów, klasy wirtualne, metody wirtualne, przetwarzanie drzew, obsługa błędów, wczytywanie z pliku

**UWAGA:**
+ Pisząc własny program można użyć innego nazewnictwa niż to przedstawione w treści zadania. Należy jednak użyć spójnej konwencji kodowania, zgodnie z wymaganiami kursu.
+ Zadanie jest rozszerzeniem poprzedniego zadania. Żeby zaliczyć zadanie nr 3, należy posiadać program o pełnej funkcjonalności wymaganej w ramach zadania nr 2.

Należy rozwinąć program z zadania nr 2 o następujące funkcjonalności:
1. Po wpisaniu *help nazwa_komendy*, ma wyświetlić się opis komendy dla obiektu *CMenuCommand* z aktualnego menu, o ile komenda o takiej nazwie istnieje. Jeżeli komenda nie istnieje, należy wyprowadzić komunikat *brak komendy*.

Na przykład:
Jeśli dla menu głównego z przykładu do zadania nr 2 wpiszemy *help ala* to wyświetli się opis dla komendy *ala*

2. Po wpisaniu *search nazwa_komendy*, program ma przeszukać całe drzewo po kątem istnienia komend o zadanej nazwie. Należy wypisać wszystkie komendy wraz ze ścieżkami, w których występują.

Na przykład:
Jeśli dla drzewa menu z przykładu do zadania nr 2 wpiszemy następujące komendy:
*menu1*
*search ala*
to pomimo, że komenda menu1 spowodowała wejście w podmenu, komenda *search* i tak znajdzie i wypisze ścieżkę do komendy *ala*:
menu->*ala*

3. Należy wykonać zapis aktualnego drzewa menu do zmiennej typu *string* i ze zmiennej typu *string*. Zapis ma mieć następujący format. **Uwaga**: format nie musi uwzględniać konkretnych funkcji przechowywanych przez obiekty dziedziczące po klasie wirtualnej *CCommand*.

Format zapisu dla menu:
**(‘nazwa_menu’,‘polecenie_otwierające_menu>;dziecko1,dziecko2,...,dzieckon)**

Format zapisu dla komend:
**[‘nazwa_komendy’,‘polecenie_wywołujące_komendę',‘treść_help_dla_komendy’]**

4. W przypadku gdyby *string*, z którego następuje wczytywanie, był błędny program powinien poinformować o tym, gdzie w *stringu* wystąpił błąd i jakiego znaku program oczekiwał.


**Autor: Michał Przewoźniczek**