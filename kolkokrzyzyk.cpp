#include <iostream>
#include <cstdlib>

using namespace std;

int x, y;
int _w;

char** xo;  // przechowuje plansze gry


void czysc_xo()
{
    for (int i = 0; i < x; i++)
        for (int j = 0; j < y; j++) xo[i][j] = ' ';
}


void plansza()
{
    cout<<"   ";
    for (int j = 0; j < y; j++)
            cout <<" "<<j<<"  ";
        cout << endl;
    for (int i = 0; i < x; i++)
    {
        cout<<i<<"  ";
        for (int j = 0; j < y; j++)
            cout <<" " << xo[i][j] << " |";
        cout << endl;
        cout<<"   ";
        for (int j = 0; j < y; j++)
            cout << "----";
        cout << endl;

    }

    cout << endl;


}


void ruch_cz()
{
    char klawisz;
    bool ruch_zly;
    int w, k;

    do
    {
        ruch_zly = true;
        cout << "Podaj numer wiersza i kolumny:" << endl;
        cin >> w >> k;

        if (xo[w][k] == ' ')
        {
            xo[w][k] = 'o';
            ruch_zly = false;
        }

    } while (ruch_zly);
}


bool wygrana(char gracz)
{

    int  licznik = 0;

    for (int i = 0; i < x; i++)
    {
        licznik = 0;
        for (int j = 0; j < y; j++)
        {
            if (xo[i][j] == gracz)
                licznik++;
            else
                licznik = 0;
            if (licznik == _w)
            {
                return true;
            }
        }


        licznik = 0;
        for (int j = 0; j < y; j++)
        {
            if (xo[j][i] == gracz)
                licznik++;
            else
                licznik = 0;
            if (licznik == _w)
            {
                return true;
            }
        }
    }

    licznik = 0;
    for (int j = 0; j < y; j++)
    {
        if (xo[j][j] == gracz)
            licznik++;
        else
            licznik = 0;
        if (licznik == _w)
        {
            return true;
        }
    }

    licznik = 0;
    for (int j = 0; j < y; j++)
    {
        if (xo[j][y - j - 1] == gracz)
            licznik++;
        else
            licznik = 0;
        if (licznik == _w)
        {
            return true;
        }
    }
    return false;
}


bool wolne()
{
    for (int w = 0; w < x; w++)
        for (int k = 0; k < y; k++)
            if (xo[w][k] == ' ') return true;
    return false;
}


int minimax(char gracz, int poziom, int glebokosc)
{

    int licznik = 0;
    int w, k;


    for (int i = 0; i < x; i++)
        for (int j = 0; j < y; j++)
            if (xo[i][j] == ' ')
            {
                xo[i][j] = gracz;
                w = i; k = j;  // jesli remis
                licznik++;     // zlicza wolne pola

                bool test = wygrana(gracz);

                xo[i][j] = ' ';
                if (test)
                {
                    if (!poziom) xo[i][j] = gracz;
                    return gracz == 'x' ? -1 : 1;
                }
            }

    // czy remis

    if (licznik == 1)
    {
        if (!poziom) xo[w][k] = gracz;
        return 0;
    }

    // jaki najlepszy ruch

    int v;
    int vmax;

    vmax = gracz == 'x' ? x - 1 : -x + 1;

    for (int i = 0; i < x; i++)
        for (int j = 0; j < y; j++)
            if (xo[i][j] == ' ')
            {
                xo[i][j] = gracz;
                if (3* y - _w >= glebokosc)
                    v = minimax(gracz == 'x' ? 'o' : 'x', poziom + 1, glebokosc + 1);
                else
                {
                    xo[i][j] = ' ';
                    return gracz == 'x' ? -1 : 1;
                }
                xo[i][j] = ' ';

                if (((gracz == 'x') && (v < vmax)) || ((gracz == 'o') && (v > vmax)))
                {
                    vmax = v; w = i; k = j;
                }
            }

    if (!poziom) xo[w][k] = gracz;

    return vmax;
}


int main()
{
    cout << "Podaj wymiar planszy:"<< " ";
    cin >> x;
    y = x;
    while (1)
    {
        cout << "Podaj ile znakow musi byc w rzedzie, by wygrac: ";
        cin >> _w;
        if (_w > 2 && _w <= x)
        {
            break;
        }
        cout<<"Podales zla wartosc";
    }
    xo = new char* [x];
    for (int i = 0; i < x; i++)
        xo[i] = new char[y];


    czysc_xo();
    plansza();
    do
    {
        ruch_cz();


        if (wygrana('o')) break;  

        if (wolne())
        {
            minimax('x', 0, 0);

            if (wygrana('x')) {
                plansza(); cout << "Niestety przegrales. :(" << endl;  break;
            };
        }
        else { plansza(); cout << "Remis!" << endl; break; };
        plansza();
    } while (true);

}
