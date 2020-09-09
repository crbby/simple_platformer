
# Opis Projektu zaliczeniowego PSIO


### 1. Ogólny zarys projektu:
Moim projektem zaliczeniowym będzie prosty platformer inspirowany starszymi odsłonami kultowej gry Super Mario Bros, wspierający ładowanie dowolnej liczby, łatwo-edytowalnych poziomów z dysku.

Celem gry jest jak najszybsze ukończenie poziomu, nie tracąc przy tym wszystkich żyć bohatera.



### 2. Sterowanie postacią:

| Przycisk     | Akcja                      |
| ------------ | -------------------------- |
| A/D          | Sterowanie Lewo/Prawo      |
| A/D + LSHIFT | Sprint Lewo/Prawo          |
| Spacja       | Skok                       |
| Q            | Powrót na pozycję startową |



### 3. Format pliku poziomu:

#### Elementy składowe poziomu:

| Klucz | Wartość                 |
| ----- | ----------------------- |
| 0     | Powietrze               |
| 1     | Klocek z trawą          |
| 3     | Klocek bez trawy        |
| 2     | Kolce - zabijają gracza |
| g     | Punkt docelowy          |



#### Przeciwnicy:

| Klucz | Wartość                                            |
| ----- | -------------------------------------------------- |
| h     | Tworzy blok typu: `1` i umiejscawia na nim ślimaka |
| f     | Tworzy blok typu: `0` i umiejscawia na nim muchę   |



#### Przedmioty:

| Klucz | Wartość                                                      |
| ----- | ------------------------------------------------------------ |
| s     | Tworzy blok typu: `0` i umiejscawia na nim srebrny coin ( +100 pkt ) |
| d     | Tworzy blok typu: `0` i umiejscawia na nim złoty coin ( +300 pkt ) |



Szerokość poziomu pozyskiwana jest z *długości* pierwszej linijki w pliku


Lista poziomów jest edytowalna w pliku źródłowym, `404` linijka. 

Przykładowy poziom: pliki lvl1 do lvl3 ( .txt ).


### 4. Wykorzystane zasoby

Tiles from "Platformer Art Redux" - Creative Commons (CC0 1.0).
https://kenney.nl/assets/platformer-art-pixel-redux

Font from Pangolin - SIL Open Font License (OFL).
https://fonts.google.com/specimen/Pangolin



<sub><sup>
Ps. 
src nie zostało rozbite na klasy, wszystkie klasy zdefiniowane są w main.cpp
  </sub></sup>
