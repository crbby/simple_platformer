
# Opis Projektu zaliczeniowego PSIO

 1. Ogólny zarys projektu
 2. Główne cele
 3.  Przewidywane problemy
 4. Biblioteki
 5. Podsumowanie

## 1. Ogólny zarys projektu
Moim projektem zaliczeniowym będzie powierzchniowo prosty platformer inspirowany starszymi odsłonami kultowej gry Super Mario Bros.
 Kluczową wartością jest dla mnie skupienie się na "bebechach", zachowując przy tym, tradycyjną dla tego rodzaju gier, łatwość rozgrywki, sterowania. Jeżeli chodzi o zarys graficzny, nie jestem w stanie powiedzieć jeszcze w jaki sposób będzie się projekt prezentować. 

## 2. Główne cele
Zależy mi na zachowaniu w miarę najprostszego układu sterowania - ograniczenie się do d-pada + 4 przycisków funkcyjnych. Zostając przy prostych rozwiązaniach, w celach figuruje także zaimplementowanie autorskiego systemu siatkowego ułożenia obiektów. Takie rozwiązanie w znaczącym stopniu ułatwi implementacje edytora poziomów oraz umożliwi wprowadzenie systemu proceduralnej generacji plansz do trybu "endless".

## 3. Przewidywane problemy
Z uwagi na rozmiar projektu okropnie duży nacisk musi być położony na obiektowa implementacje wszelkich elementów gry. 

Kolejnym wyzwaniem może okazać się implementacja ww. systemu siatkowego dla obiektów, z tym problemem *nie mam pojęcia* jak sobie poradzić, jakoś to się wyjaśni samo.

Proceduralna generacją poziomów brzmi ciekawie, i pewnie *niesamowicie ciekawie* będzie wyglądała jej implementacja. 

Zadbać należy będzie również o wydajność kodu oraz garbage colection. Jeżeli ten aspekt będzie pominięty tryb `endless` zmieni się w `biegnij dopóki masz jeszcze RAM`.

Jeżeli wszystko pójdzie po myśli zapis postępu/niestandardowych poziomów będzie obsłużony prostym zapisem do pliku.

## 4. Biblioteki
Projekt będzie wykonany w języku C++, lista 3rd party bibliotek podlega zmianie, ale wstępny zarys prezentuje się następująco:
|Biblioteka|Zastosowanie|
|--|--|
|SFML| Główne elementy rozgrywki (gameplay) |
| QT | Level editor (nie jest to pewne) |
| Boost | Większa kultura pisania wiadomo

## 5. Podsumowanie
Prawdopodobnie rzuciłem się na za głęboka wodę, dlatego niektóre założenia mogą się drastycznie zmienić, albo nawet zostać pominięte(sic!). Jednak, mam nadzieję że nie napotkam się na za dużo problemów.


