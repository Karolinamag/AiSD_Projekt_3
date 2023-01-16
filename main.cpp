#include <iostream>
#include <fstream>

using namespace std;

 fstream zapisywanie; //Zapisywanie 

struct drzewo_binarne //Deklaracja struktury drzewa binarnego
{
    int dane; //Zmienna do wartosci danego wezla
    struct drzewo_binarne* lewe_dziecko; //Deklarowanie dla danego wezla lewego dziecka tego samego typu struktury
    struct drzewo_binarne* prawe_dziecko;//Deklarowanie dla danego wezla prawego dziecka tego samego typu struktury
    int wypisz() //Funkcja do wypisywania danych z wezla
    {
        return dane; //Zwraca dane
    }
};

struct drzewo_binarne* nowe_drzewo_binarne(int dane_wejsciowe) //Kostruktor dla drzewa, przyjmuje int
{
    struct drzewo_binarne* drzewo_binarne = new struct drzewo_binarne; //Inicjacja nowego drzewa
    drzewo_binarne->dane = dane_wejsciowe; //Dane przyjmuje wartosc podana podczas tworzenia instancji
    drzewo_binarne->lewe_dziecko = NULL; //Miejsca na dzieci zaczynaja puste, potem moga zostac wypelnione
    drzewo_binarne->prawe_dziecko = NULL;
    return drzewo_binarne; //Zwrot stworzonego drzewa
};

void dodawanie(drzewo_binarne* drzewo_do_ktorego_dodajemy, int dodwana_wartosc) //Funkcja dodawania, przyjmuje drzewo do ktorego mamy dodac wartosc i wartosc
{

   drzewo_binarne *rodzic = drzewo_do_ktorego_dodajemy; //Deklaracja zmiennej rodzic która bedzie wskazywala jakiego wezla dzieci badamy pod katem mienia wolnego miejsca na dane. 
  while(true){ //While dziala bez warunku tylko bedzie sie konczyl przy break'ach
    if (rodzic->lewe_dziecko != NULL){ //Jesli lewe dziecko jest zapelnione
        if (rodzic->prawe_dziecko != NULL){ //Jesli prawe dziecko jest zapelnione
            if (rodzic->lewe_dziecko->lewe_dziecko != NULL && rodzic->lewe_dziecko->prawe_dziecko != NULL){ //Sprawdzanie czy obojga dzieci danego wezla tez jest zajete
                if (rodzic->prawe_dziecko->lewe_dziecko != NULL && rodzic->prawe_dziecko->prawe_dziecko != NULL){ //Sprawdzanie czy obojga dzieci danego wezla tez jest zajete
                    rodzic = rodzic->lewe_dziecko; cout<<"idziemy w lewo"<<endl; //Jesli idac od rodzica oboje jego dzieci jest pelne, a takze ich dzieci, to przyjmujemy lewe dziecko jako rodzica
                }else{
                    rodzic = rodzic->prawe_dziecko; cout<<"idziemy w  prawo"<<endl; //Jesli idac od rodzica oboje jego dzieci a takze dzieci idace od lewego dziecka sa pelne, to przyjmujemy prawe dziecko jako rodzica
                }
            }else{
                rodzic = rodzic->lewe_dziecko; cout<<"idziemy w  lewo"<<endl; //Jesli idac od rodzica oboje jego dzieci jest pelne, ale dzieci lewego dziecka sa puste, to przyjmujemy lewe dziecko jako rodzica

            }
        }else{
        rodzic->prawe_dziecko = nowe_drzewo_binarne(dodwana_wartosc); cout<<"dodane po prawej"<<endl<<endl; break; //Jesli prawe dziecko tworzymy tam nowa strukture z dodawana wartoscia
        }
    }else{
    rodzic->lewe_dziecko = nowe_drzewo_binarne(dodwana_wartosc); cout<<"dodane po lewej"<<endl<<endl; break; //Jesli lewe dziecko tworzymy tam nowa strukture z dodawana wartoscia
    }
  }


}


int odczytywanie_i_zliczanie(drzewo_binarne* drzewo_do_odczytania, int ilosc){ //Funkcja do odczytywania i zliczania ilosci wezlow


    if (drzewo_do_odczytania == NULL){return ilosc;}else{ilosc++;} //Jesli wezel ktory ma byc odczytany jest pusty, zwracamy obecna ilosc wezlow 

    ilosc = odczytywanie_i_zliczanie(drzewo_do_odczytania->lewe_dziecko, ilosc); //Wywolanie dla lewego dziecka, funkcja idzie coraz glebiej i zawsze gdy znajduje pelny wezel dodaje do ilosci wezlow, a jesli znajdzie pusty, to ta ilosc wroci sporotem do najwyzszego wywolania funkcji//

   
    cout << drzewo_do_odczytania->dane << " "; //Wypisanie wartosci obecnego wezla  

    ilosc = odczytywanie_i_zliczanie(drzewo_do_odczytania->prawe_dziecko, ilosc); //Wywolanie rekurencyjne dla prawego dziecka.

    return ilosc; //zwracamy ilosc 
}

void zapisywanie_do_pliku(drzewo_binarne* drzewo_do_odczytania){ //Funkcja praktycznie identyczna do odczytywania ale nie zlicza i ma plik zamiast cout


    if (drzewo_do_odczytania == NULL){return;} //Jesli wezel ktory ma byc odczytany jest pusty, koniec funkcji
    zapisywanie_do_pliku(drzewo_do_odczytania->lewe_dziecko); //Wywolanie rekurencyjne dla lewego dziecka.

    zapisywanie << drzewo_do_odczytania->dane << " "; //Wypisanie wartosci obecnego wezla do pliku

    zapisywanie_do_pliku(drzewo_do_odczytania->prawe_dziecko); //Wywolanie rekurencyjne dla prawego dziecka.

}


int ile_poziomow(drzewo_binarne* drzewo_do_odczytania){ //Funkcja sprawdzajaca ile poziomow ma drzewo, przyjmuje drzewo

    if (drzewo_do_odczytania == NULL){return 0;} //Sprawdzamy czy wezel jest pusty, jesli tak zwracamy 0 bo nie dodajemy kolejnego poziomu do zliczania

    int lewe_dziecko_wysokosc,prawe_dziecko_wysokosc; //Tworzymy zmienne pomocnicze by moc porownywac ktora galaz idzie glebiej

    lewe_dziecko_wysokosc=ile_poziomow(drzewo_do_odczytania->lewe_dziecko); //Wywolanie funkcji rekurencyjnie na lewej galezi. Wartosc wywolania czyli ilosc poziomow obliczona z tej galezi zapisana do zmiennej
    prawe_dziecko_wysokosc=ile_poziomow(drzewo_do_odczytania->prawe_dziecko); //Wywolanie funkcji rekurencyjnie na prawej galezi.

    return max(lewe_dziecko_wysokosc,prawe_dziecko_wysokosc) + 1; //Zwracamy wartosc z tej galezi ktora byla glebsza +1 bo jeszcze liczymy poziom korzenia
}


int szukanie(drzewo_binarne* drzewo_do_odczytania, int szukana_wartosc){ //Funkcja szukanie pozwala znalezc czy jakas wartosc znajduje sie w drzewie, przyjmuje drzewo i szukana wartosc

    int zwrotlewy=0,zwrotprawy=0; //Definicja zmiennych pomocniczych potrzebnych do wiedzenia czy juz znaleziono liczbe

    if (drzewo_do_odczytania->dane == szukana_wartosc){ //Sprawdzamy czy wartosc danych w wezle jest rowna szukanej wartosci, jesli tak to zwracamy jedynke ktora wraca to pierwotnego wywolania funkcji
        return 1;
    }else{
        if (drzewo_do_odczytania->lewe_dziecko == NULL && drzewo_do_odczytania->prawe_dziecko == NULL){return 0;} //Jesli kolejne galezie sa puste to zwracamy 0 i konczymy poszukiwania w tym kierunku
    }

    if (drzewo_do_odczytania->lewe_dziecko != NULL){ //Jesli lewe dziecko nie jest puste to wywolujemy rekurencyjnie na nim szukanie
    zwrotlewy = szukanie(drzewo_do_odczytania->lewe_dziecko, szukana_wartosc);}

    if (drzewo_do_odczytania->prawe_dziecko != NULL){ //Jesli prawe dziecko nie jest puste to wywolujemy rekurencyjnie na nim szukanie
    zwrotprawy = szukanie(drzewo_do_odczytania->prawe_dziecko, szukana_wartosc);}


    return max(zwrotlewy,zwrotprawy); //Brany jest max z wartosci tak by jesli gdzies sie pojawila 1 bo znalezlismy liczbe zostala ona przekazana poza funkcje
}


string szukaj_czy_jest_element(drzewo_binarne* drzewo_do_odczytania, int szukana_wartosc){ //Funkcja pomocnicza dla szukania gdzie konwertujemy wyniki 1 albo 0 w tekst

if (szukanie(drzewo_do_odczytania,szukana_wartosc)==1){return "znaleziono";}else{return "nie znaleziono";} //Jesli wynik szukania to jeden to oznacza to ze znaleziono element o szukanej wartosci

}


int main()
{
    struct drzewo_binarne *przyklad = nowe_drzewo_binarne(10); //Inicjacja struktury, bierzemy wartosc 10 by root wyroznial sie od reszty wezlow

    cout<<"1. Dodawanie wezlow z wartosciami:"<<endl<<endl;

    fstream wczytywanie; //Otwieranie pliku
    wczytywanie.open("Galezie.txt", ios::in);
    while(!wczytywanie.eof()){ //A¿ do koñca pliku
        int p; //Deklaracja zmiennej pomocniczej do której bêd¹ zapiswyane po kolei wartoœci
       wczytywanie >> p;
       dodawanie(przyklad, p); //Wywo³anie funkcji dodawania z wartoscia wczytana z pliku
    }
    wczytywanie.close();

    cout<<endl<<"2. Wyswietlanie drzewa: ";
    int  ilosc=0; //Deklaracja zmiennej potrzebnej do zliczania
    ilosc = odczytywanie_i_zliczanie(przyklad,ilosc); //Funkcja wyswietla drzewo i za razem jej zwracana wartosc jest iloscia wezlow


    zapisywanie.open("Wyswietlone_drzewo.txt", ios::out); //Otwieranie nowego pliku tekstowego do ktorego zapisywane bedzie drzewo
    zapisywanie_do_pliku(przyklad); //Wywo³anie funkcji zapisywania
    zapisywanie.close(); //Zamkniecie pliku


    int poziomy = ile_poziomow(przyklad); //Deklaracja zmiennej do ktorej przypisujemy wynik funkcji sprawdzajacej ilosc poziomow
    cout<<endl<<endl<<"Ilosc poziomow: "<<poziomy<<endl<<"Ilosc wezlow: "<<ilosc<<endl<<endl; //Wyswietlanie uzyskanych wartosci

    przyklad->lewe_dziecko = NULL; //Usuwanie nie potrzebuje pisania nowej funkcji, przypisanie wezlowi wartosci NULL likwiduje wszystkie wychodzace z niego wezly

    cout<<"3. Drzewo po usunieciu wezla: ";

    odczytywanie_i_zliczanie(przyklad,ilosc); //Wyswietlanie drzewa po usunieciu

    cout<<endl<<endl<<"4. Szukanie czy element znajduje sie w drzewie: ";

    cout<<szukaj_czy_jest_element(przyklad, 7)<<endl<<endl;


    return 0;
}
