//POP 2016-01-18 projekt 2 Socik Sebastian EIT 6 160307 Code::Blocks 13.12 GNU GCC Compiler

#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

void WczytanieElementu(ofstream &plikWy, char zawartosc[], char element[][700], int &i, int &licznikElementow)
{
    while(!(isspace(zawartosc[i]) || zawartosc[i] == NULL))
    {
        element[licznikElementow][i] = zawartosc[i];
        i++;
    }
    element[licznikElementow][i] = NULL;
    for(int i = 0; i < licznikElementow; i++)
    {
        plikWy << "\t";
    }
    plikWy << element[licznikElementow] << endl;
    licznikElementow++;
}

bool SprawdzanieWartosciAtrybutu(char wartosciAtrybutow[][700], char atrybuty[][700], int licznikAtrybutow, int &licznikZnacznikow)
{
    for(int i = 0; i < licznikAtrybutow; i++)
    {
        int iloscZnakow = 0;
        while(wartosciAtrybutow[i][iloscZnakow] != NULL)
        {
            iloscZnakow++;
        }
        if(wartosciAtrybutow[i][0] != '=' || wartosciAtrybutow[i][1] != '"' || wartosciAtrybutow[i][iloscZnakow - 1] != '"')
        {
            cout << "Zle zdefiniowany atrybut " << atrybuty[i] << " >>> Nr znacznika: " << licznikZnacznikow << endl;
            return false;
        }
    }
    return true;
}

bool WczytanieAtrybutu(char zawartosc[], char atrybuty[][700], char wartosciAtrybutow[][700], int &i, int licznikAtrybutow, int &licznikZnacznikow)
{
    int j = 0;
    i++;
    while(zawartosc[i] != '=')
    {
        atrybuty[licznikAtrybutow][j] = zawartosc[i];
        j++;
        i++;
        if(zawartosc[i] == NULL || isspace(zawartosc[i]))
        {
            atrybuty[licznikAtrybutow][j] = NULL;
            strcpy(wartosciAtrybutow[licznikAtrybutow],"=\"\"");
            cout << "Zle zdefiniowany atrybut: " << atrybuty[licznikAtrybutow] << " >>> Nr znacznika: " << licznikZnacznikow << endl;
            return false;
        }
    }
    atrybuty[licznikAtrybutow][j] = NULL;
    j = 0;
    while(!(isspace(zawartosc[i]) || zawartosc[i] == NULL || zawartosc[i] == '?'))
    {
        wartosciAtrybutow[licznikAtrybutow][j] = zawartosc[i];
        j++;
        i++;
    }
    wartosciAtrybutow[licznikAtrybutow][j] = NULL;
    return true;
}

void SprawdzanieAtrybutow(char atrybuty[][700], char wartosciAtrybutow[][700], int licznikAtrybutow, bool &poprawnosc, int &licznikZnacznikow)
{
    for(int i = 0; i < licznikAtrybutow - 1; i++)
    {
        for(int j = i + 1; j < licznikAtrybutow; j++)
        {
            if(!strcmp(atrybuty[i], atrybuty[j]))
            {
                cout << "Atrubut " << atrybuty[i] << " zostal wielokrotnie zdefiniowany" << " >>> Nr znacznika: " << licznikZnacznikow << endl;
                poprawnosc = false;
            }
        }
    }
    if(!SprawdzanieWartosciAtrybutu(wartosciAtrybutow, atrybuty, licznikAtrybutow, licznikZnacznikow))
    {
        poprawnosc = false;
    }
}

bool SprawdzanieInstrukcjiPrzetwarzania(char zawartosc[], int &i, int &licznikZnacznikow)
{
    int j = 0;
    while(!(isspace(zawartosc[i]) || zawartosc[i] == NULL))
    {
        i++;
    }
    while(zawartosc[j] != NULL)
    {
        j++;
    }
    if(zawartosc[j - 1] != '?')
    {
        cout << "Bledna instrukcja przetwarzania >>> Nr znacznika: " << licznikZnacznikow << endl;
        return false;
    }
    return true;
}

bool SprawdzanieKomentarza(char zawartosc[], int &licznikZnacznikow)
{
    int iloscZnakow = 0;
    while(zawartosc[iloscZnakow] != NULL)
    {
        iloscZnakow++;
    }
    if(zawartosc[iloscZnakow - 1] != '-' || zawartosc[iloscZnakow - 2] != '-')
    {
        cout << "Bledny komentarz >>> Nr znacznika: " << licznikZnacznikow << endl;
        return false;
    }
    return true;
}

bool SprawdzanieCDATA(char zawartosc[], int &licznikZnacznikow)
{
    int iloscZnakow = 0;
    if(zawartosc[1] != '[' || zawartosc[2] != 'C' || zawartosc[3] != 'D' || zawartosc[4] != 'A' || zawartosc[5] != 'T' || zawartosc[6] != 'A' || zawartosc[7] != '[')
    {
        cout << "Blad w sekcji CDATA >>> Nr znacznika: " << licznikZnacznikow << endl;
        return false;
    }
    while(zawartosc[iloscZnakow] != NULL)
    {
        iloscZnakow++;
    }
    if(zawartosc[iloscZnakow - 1] != ']' || zawartosc[iloscZnakow - 2] != ']')
    {
        cout << "Blad w sekcji CDATA >>> Nr znacznika: " << licznikZnacznikow << endl;
        return false;
    }
    return true;
}

void WczytywanieZnacznika(ofstream &plikWy, char zawartosc[], char element[][700], char atrybuty[][700], int &licznikElementow, bool &poprawnosc, int &licznikZnacznikow)
{
    int i = 0;
    int licznikAtrybutow = 0;
    char wartosciAtrybutow[700][700];
    if(zawartosc[i] == '?')
    {
        if(!SprawdzanieInstrukcjiPrzetwarzania(zawartosc, i, licznikZnacznikow))
        {
            poprawnosc = false;
        }
    }
    else if(zawartosc[i] == '!')
    {
        if(zawartosc[i + 1] == '-')
        {
            if(zawartosc[i + 2] == '-')
            {
                if(!SprawdzanieKomentarza(zawartosc, licznikZnacznikow))
                {
                    poprawnosc = false;
                }
            }
            else
            {
                cout << "Bledny komentarz >>> Nr znacznika: " << licznikZnacznikow << endl;
                poprawnosc = false;
            }
        }
        else
        {
            if(!SprawdzanieCDATA(zawartosc, licznikZnacznikow))
            {
                poprawnosc = false;
            }
        }
        return;
    }
    else
    {
        WczytanieElementu(plikWy, zawartosc, element, i, licznikElementow);
    }
    while(zawartosc[i] != NULL)
    {
        if(zawartosc[i] == '?' || zawartosc[i + 1] == '?')
        {
            break;
        }
        if(!WczytanieAtrybutu(zawartosc, atrybuty, wartosciAtrybutow, i, licznikAtrybutow, licznikZnacznikow))
        {
            poprawnosc = false;
        }
        licznikAtrybutow++;
    }
    SprawdzanieAtrybutow(atrybuty, wartosciAtrybutow, licznikAtrybutow, poprawnosc, licznikZnacznikow);
}

void WczytywanieZnacznikaZamykajacego(char zawartosc[], char zamykajace[])
{
    int i = 1;                              //od 1 zeby pominac /
    while(zawartosc[i] != NULL)
    {
        zamykajace[i - 1] = zawartosc[i];
        i++;
    }
    zamykajace[i - 1] = NULL;
}

bool SprawdzenieCzyZamykajacy(char zawartosc[])
{
    if(zawartosc[0] == '/')
    {
        return true;
    }
    return false;
}

bool SprawdzanieZamykania(char element[][700], char zamykajace[], int licznikElementow)
{
    if(!strcmp(zamykajace, element[licznikElementow]))
    {
        return true;
    }
    return false;
}

bool SprawdzanieCzyPusty(ofstream &plikWy, char zawartosc[], int licznikElementow)
{
    int ostatniznak = 0;
    while(zawartosc[ostatniznak] != NULL)
    {
        ostatniznak++;
    }
    if(zawartosc[ostatniznak - 1] == '/')
    {
        zawartosc[ostatniznak - 1] = NULL;
        for(int i = 0; i < licznikElementow; i++)
        {
            plikWy << "\t";
        }
        plikWy << zawartosc << endl;
        return true;
    }
    return false;
}

void DzialaniazElementami(ifstream &plikWe, ofstream &plikWy, char znak, int &licznikElementow, char element[][700], char zawartosc[], char atrybuty[][700], char zamykajace[], char niezamkniete[][700], int nrNiezamknietego[],  int &licznikNiezamknietych, bool &poprawnosc, int &licznikZnacznikow)
{
    while(plikWe){
        plikWe >> znak;
        while(znak != '<')
        {
            plikWe >> znak;
            if(!plikWe)
            {
                if(licznikElementow != 0)
                {
                    for(int i = licznikElementow - 1; i >= 0; i--)
                    {
                        strcpy(niezamkniete[licznikNiezamknietych], element[i]);
                        nrNiezamknietego[licznikNiezamknietych] = licznikZnacznikow + 1;
                        licznikNiezamknietych++;
                    }
                }
                return;
            }
        }
        plikWe.get(zawartosc,700,'>');
        licznikZnacznikow++;

        if(!SprawdzenieCzyZamykajacy(zawartosc))
        {
            if(!SprawdzanieCzyPusty(plikWy, zawartosc, licznikElementow))
            {
                WczytywanieZnacznika(plikWy, zawartosc, element, atrybuty, licznikElementow, poprawnosc, licznikZnacznikow);
            }
        }
        else if(licznikElementow > 0)
        {
            licznikElementow--;
            WczytywanieZnacznikaZamykajacego(zawartosc, zamykajace);
            if(!SprawdzanieZamykania(element, zamykajace, licznikElementow))
            {
                strcpy(niezamkniete[licznikNiezamknietych], element[licznikElementow]);
                nrNiezamknietego[licznikNiezamknietych] = licznikZnacznikow;
                licznikNiezamknietych++;
            }
        }
        else
        {
            WczytywanieZnacznikaZamykajacego(zawartosc, zamykajace);
            cout << "Brak znacznika otwierajacego do znacznika: " << zamykajace << " >>> Nr znacznika: " << licznikZnacznikow << endl;
            poprawnosc = false;
        }
    }
}

int main()
{
    char nazwa[700];
    cin >> nazwa;
    ifstream plikWe(nazwa);
    if(!plikWe)
    {
        cout << "Nieudane otwarcie pliku " << nazwa;
        return 1;
    }
    cin >> nazwa;
    ofstream plikWy(nazwa);
    if(!plikWy)
    {
        cout << "Nieudane otwarcie pliku " << nazwa;
        return 1;
    }
    char znak;
    char zawartosc[700];
    char element[700][700];
    char atrybuty[700][700];
    int licznikElementow = 0;
    char zamykajace[700];
    char niezamkniete[700][700];
    int nrNiezamknietego[700];
    int licznikNiezamknietych = 0;
    bool poprawnosc = true;
    int licznikZnacznikow = 0;

    plikWe >> znak;
    if(znak == '<')
    {
        plikWe.get(zawartosc,700,'>');
        licznikZnacznikow++;
    }
    else
    {
        cout << "Wczytano bledny plik lub rozpoczyna on sie od znaku innego niz '<'.";
        return 0;
    }

    WczytywanieZnacznika(plikWy, zawartosc, element, atrybuty, licznikElementow, poprawnosc, licznikZnacznikow);
    DzialaniazElementami(plikWe, plikWy, znak, licznikElementow, element, zawartosc, atrybuty, zamykajace, niezamkniete, nrNiezamknietego, licznikNiezamknietych, poprawnosc, licznikZnacznikow);

    if(licznikNiezamknietych != 0)
    {
        for(int i = 0; i < licznikNiezamknietych; i++)
        {
            cout << "Zle zamkniety znacznik: " << niezamkniete[i] << " >>> Nr znacznika: " << nrNiezamknietego[i] << endl;
            poprawnosc = false;
        }
    }
    if(poprawnosc)
    {
        cout << "Poprawny plik xml";
    }
    plikWe.close();
    plikWy.close();
    return 0;
}
