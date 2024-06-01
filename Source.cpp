#include <iostream>
#include <winbgim.h>
#include <stdlib.h>
#include <ctime>
#include <math.h>
#include <iomanip>
#define PI 3.1415
#define paginaMeniului 0
#define paginaCeasDigital 1
#define paginaCeasAnalogic 2
#define paginaSetari 3
#define paginaAlarma 5
#define seteazaStilTitlu  settextstyle(1,HORIZ_DIR,5)
#define seteazaStilText settextstyle(3,HORIZ_DIR,1)
#define ROMANIA 0
#define UK 1
using namespace std;

int regiune = ROMANIA; // initial regiunea este Romania

bool schimba_24h_to_12h = false; //initial , ceasul este de 24 de ore

struct punct
{
    int x, y;
};

struct dreptunghi
{
    punct SS, DJ;
};

struct Ceas
{
    int secunde;
    int minute;
    int ore;
    int zi;
    int luna;
};
Ceas ceas;
Ceas alarma;
struct buton
{
    bool hovered;
    dreptunghi D;
    dreptunghi D1;
    int culoare;
    char text[20];
};

bool apartine(punct P, dreptunghi D)
{
    return D.SS.x <= P.x && P.x <= D.DJ.x && D.SS.y <= P.y && P.y <= D.DJ.y;

}

buton B[6];
buton B1[4];
buton B2[4];
int nrButoane = 5;

void deseneazaMeniul()
{
    seteazaStilText;
    readimagefile("background-unfocused.jpg", 0, 0, 900, 600);
    setcolor(BLACK);
    setfillstyle(SOLID_FILL, LIGHTRED);

    int i;
    for (i = 1; i <= nrButoane; i++)
    {
        B[i].D.SS.x = 125 * i;
        B[i].D.DJ.x = 125 * (i + 1) - 5;
        B[i].D.SS.y = 270;
        B[i].D.DJ.y = 300;
        switch (i)
        {
        case 1:
            strcpy(B[i].text, "Setari");
            break;
        case 2:
            strcpy(B[i].text, "Alarma");
            break;
        case 3:
            strcpy(B[i].text, "Digital");
            break;
        case 4:
            strcpy(B[i].text, "Analogic");
            break;
        case 5:
            strcpy(B[i].text, "IESIRE");
            break;
        }
        rectangle(B[i].D.SS.x, B[i].D.SS.y, B[i].D.DJ.x, B[i].D.DJ.y);
        bar(B[i].D.SS.x, B[i].D.SS.y + 30, B[i].D.DJ.x, B[i].D.SS.y);
        setbkcolor(LIGHTRED);
        outtextxy(B[i].D.SS.x + 35, B[i].D.SS.y + 10, B[i].text);
    }
}



int butonAles()
{
    int i;
    punct p;
    if (ismouseclick(WM_LBUTTONDOWN))
    {
        clearmouseclick(WM_LBUTTONDOWN);
        p.x = mousex();
        p.y = mousey();
        for (i = 1; i <= nrButoane; i++)
            if (apartine(p, B[i].D))
            {
                return i;
            }
    }
    return 0;
}

void iaTimpulLocal()
{
    time_t t = time(NULL);
    tm* timePtr = localtime(&t); // ia timpul local al calculatorului
    if (regiune == ROMANIA)
    {
        ceas.secunde = (timePtr->tm_sec);
        ceas.minute = (timePtr->tm_min);
        ceas.ore = (timePtr->tm_hour);
    }
    if (regiune == UK)
    {
        ceas.secunde = (timePtr->tm_sec);
        ceas.minute = (timePtr->tm_min);
        ceas.ore = (timePtr->tm_hour) - 2;
        if (ceas.ore == -2)
            ceas.ore = 22;
        if (ceas.ore == -1)
            ceas.ore = 23;
    }
}


void deseneazaCasutaIesire()
{
    rectangle(10, 10, 40, 35);
    outtextxy(18, 13, "<-");
}

bool apartineCasutaIesire(punct P)
{
    return 10 <= P.x && P.x <= 40 && 10 <= P.y && P.y <= 35;
}

int intoarcereMeniuPrincipal()
{
    punct p;
    if (ismouseclick(WM_LBUTTONDOWN))
    {
        clearmouseclick(WM_LBUTTONDOWN);
        p.x = mousex();
        p.y = mousey();
        if (apartineCasutaIesire(p))
            return 1;
    }
    return 0;
}


void scrieTimpulDigital_24h()
{
    int k = 1;
    while (k)
    {
        setbkcolor(BLACK);
        cleardevice(); //sterge consola
        setcolor(WHITE);
        seteazaStilText;
        deseneazaCasutaIesire();
        seteazaStilTitlu;
        ///tratarea fiecarui caz in parte pentru a se afisa acel '0' in fata orei in caz ca aceasta este mai mica decat 10
        if (ceas.ore < 10 && ceas.minute < 10 && ceas.secunde < 10)
            bgiout << setw(2) << setfill('0') << ceas.ore << " : " << setw(2) << setfill('0') << ceas.minute << " : " << setw(2) << setfill('0') << ceas.secunde << " " << endl;
        else if (ceas.minute < 10 && ceas.secunde < 10)
            bgiout << ceas.ore << " : " << setw(2) << setfill('0') << ceas.minute << " : " << setw(2) << setfill('0') << ceas.secunde << " " << endl;
        else if (ceas.ore < 10 && ceas.secunde < 10)
            bgiout << setw(2) << setfill('0') << ceas.ore << " : " << ceas.minute << " : " << setw(2) << setfill('0') << ceas.secunde << " " << endl;
        else if (ceas.ore < 10 && ceas.minute < 10)
            bgiout << setw(2) << setfill('0') << ceas.ore << " : " << setw(2) << setfill('0') << ceas.minute << " : " << ceas.secunde << " " << endl;
        else if (ceas.ore < 10)
            bgiout << setw(2) << setfill('0') << ceas.ore << " : " << ceas.minute << " : " << ceas.secunde << " " << endl;
        else if (ceas.minute < 10)
            bgiout << ceas.ore << " : " << setw(2) << setfill('0') << ceas.minute << " : " << ceas.secunde << " " << endl;
        else if (ceas.secunde < 10)
            bgiout << ceas.ore << " : " << ceas.minute << " : " << setw(2) << setfill('0') << ceas.secunde << " " << endl;
        else
            bgiout << ceas.ore << " : " << ceas.minute << " : " << ceas.secunde << " " << endl;

        outstreamxy(290, 270);
        //incrementeaza sec min si ore
        ceas.secunde++;
        if (ceas.secunde >= 60)
        {
            ceas.secunde = 1;
            ceas.minute++;
        }
        if (ceas.minute >= 60)
        {
            ceas.minute = 0;
            ceas.ore++;
        }
        if (ceas.ore > 24)
        {
            ceas.ore = 00;
        }

        seteazaStilText;
        if (regiune == 0)
            outtextxy(200, 200, "Ceas setat pentru Romania");
        else if (regiune == 1)
            outtextxy(200, 200, "Ceas setat pentru Anglia");
        delay(1000); // opreste codul timp de 1000 ms(o secunda)
        if (intoarcereMeniuPrincipal() != 0)
        {
            k = 0;
            cout << "[INFO]Intoarcere la meniu." << endl;
        }
    }
}

void scrieTimpulDigital_12h()
{
    int ok = 1;
    int sw = 0;
    char tip_ceas[3];

    if (ceas.ore >= 13)
    {
        ceas.ore = ceas.ore - 12;
        strcpy(tip_ceas, "PM");
    }
    else
    {
        strcpy(tip_ceas, "AM");
    }

    while (ok)
    {
        setbkcolor(BLACK);
        cleardevice(); //sterge consola
        setcolor(WHITE);
        seteazaStilText;
        deseneazaCasutaIesire();
        seteazaStilTitlu;


        ///tratarea fiecarui caz in parte pentru a se afisa acel '0' in fata orei in caz ca aceasta este mai mica decat 10
        if (ceas.ore < 10 && ceas.minute < 10 && ceas.secunde < 10)
            bgiout << setw(2) << setfill('0') << ceas.ore << " : " << setw(2) << setfill('0') << ceas.minute << " : " << setw(2) << setfill('0') << ceas.secunde << " " << tip_ceas << endl;
        else if (ceas.minute < 10 && ceas.secunde < 10)
            bgiout << ceas.ore << " : " << setw(2) << setfill('0') << ceas.minute << " : " << setw(2) << setfill('0') << ceas.secunde << " " << tip_ceas << endl;
        else if (ceas.ore < 10 && ceas.secunde < 10)
            bgiout << setw(2) << setfill('0') << ceas.ore << " : " << ceas.minute << " : " << setw(2) << setfill('0') << ceas.secunde << " " << tip_ceas << endl;
        else if (ceas.ore < 10 && ceas.minute < 10)
            bgiout << setw(2) << setfill('0') << ceas.ore << " : " << setw(2) << setfill('0') << ceas.minute << " : " << ceas.secunde << " " << tip_ceas << endl;
        else if (ceas.ore < 10)
            bgiout << setw(2) << setfill('0') << ceas.ore << " : " << ceas.minute << " : " << ceas.secunde << " " << tip_ceas << endl;
        else if (ceas.minute < 10)
            bgiout << ceas.ore << " : " << setw(2) << setfill('0') << ceas.minute << " : " << ceas.secunde << " " << tip_ceas << endl;
        else if (ceas.secunde < 10)
            bgiout << ceas.ore << " : " << ceas.minute << " : " << setw(2) << setfill('0') << ceas.secunde << " " << tip_ceas << endl;
        else
            bgiout << ceas.ore << " : " << ceas.minute << " : " << ceas.secunde << " " << tip_ceas << endl;

        outstreamxy(290, 270);
        //incrementeaza sec min si ore
        ceas.secunde++;
        if (ceas.secunde >= 60)
        {
            ceas.secunde = 1;
            ceas.minute++;
        }
        if (ceas.minute >= 60)
        {
            ceas.minute = 0;
            ceas.ore++;
        }
        if (ceas.ore > 24)
        {
            ceas.ore = 00;
        }
        seteazaStilText;
        if (regiune == 0)
            outtextxy(200, 200, "Ceas setat pentru Romania");
        else if (regiune == 1)
            outtextxy(200, 200, "Ceas setat pentru Anglia");
        delay(1000); // opreste codul timp de 1000 ms(o secunda)
        if (intoarcereMeniuPrincipal() != 0)
        {
            ok = 0;
            cout << "[INFO]Intoarcere la meniu." << endl;
        }
    }
}


void deseneazaCeasAnalogic()
{
    int k = 1;
    while (k)
    {
        setbkcolor(BLACK);
        cleardevice();
        seteazaStilText;
        deseneazaCasutaIesire();
        setcolor(WHITE);
        circle(350, 350, 200);
        circle(350, 350, 5);
        outtextxy(350 + 180 * sin(PI / 6) - 5, 350 - 180 * cos(PI / 6), "1");
        outtextxy(350 + 180 * sin(2 * PI / 6) - 5, 350 - 180 * cos(2 * PI / 6), "2");
        outtextxy(350 + 180 * sin(3 * PI / 6) - 5, 350 - 180 * cos(3 * PI / 6), "3");
        outtextxy(350 + 180 * sin(4 * PI / 6) - 5, 350 - 180 * cos(4 * PI / 6), "4");
        outtextxy(350 + 180 * sin(5 * PI / 6) - 5, 350 - 180 * cos(5 * PI / 6), "5");
        outtextxy(350 + 180 * sin(6 * PI / 6) - 5, 350 - 180 * cos(6 * PI / 6), "6");
        outtextxy(350 + 180 * sin(7 * PI / 6) - 5, 350 - 180 * cos(7 * PI / 6), "7");
        outtextxy(350 + 180 * sin(8 * PI / 6) - 5, 350 - 180 * cos(8 * PI / 6), "8");
        outtextxy(350 + 180 * sin(9 * PI / 6) - 5, 350 - 180 * cos(9 * PI / 6), "9");
        outtextxy(350 + 180 * sin(10 * PI / 6) - 5, 350 - 180 * cos(10 * PI / 6), "10");
        outtextxy(350 + 180 * sin(11 * PI / 6) - 5, 350 - 180 * cos(11 * PI / 6), "11");
        outtextxy(350 + 180 * sin(12 * PI / 6) - 5, 350 - 180 * cos(12 * PI / 6), "12");

        iaTimpulLocal();

        //linia pentru ora

        setcolor(RED);
        line(350, 350, 350 + 150 * sin(ceas.ore * PI / 6), 350 - 150 * cos(ceas.ore * PI / 6));

        //linia pentru minute

        setcolor(GREEN);
        line(350, 350, 350 + 190 * sin(ceas.minute * PI / 30), 350 - 190 * cos(ceas.minute * PI / 30));

        //linia pentru secunde

        setcolor(WHITE);
        line(350, 350, 350 + 150 * sin(ceas.secunde * PI / 30), 350 - 150 * cos(ceas.secunde * PI / 30));
        delay(1000);
        if (intoarcereMeniuPrincipal() != 0)
        {
            k = 0;
            cout << "[INFO]Intoarcere la meniu." << endl;
        }
    }
}

void deseneazaSageata(int x1, int y1, int x2, int y2)
{
    line(x1, y1, x2, y2);
    line(x1, y1, x2 - 15, y2 - 5);
    line(x1, y1, x2 - 15, y2 + 5);
}

void deseneazaPaginaSetari()
{
    setactivepage(paginaSetari);
    setbkcolor(BLACK);
    cleardevice();
    setcolor(WHITE);
    setfillstyle(SOLID_FILL, LIGHTRED);

    seteazaStilText;
    deseneazaCasutaIesire();

    seteazaStilTitlu;
    outtextxy(350, 50, "Setari");

    seteazaStilText;
    int i, j;
    for (i = 0, j = 0; i <= 300; i = i + 100, j++)
    {
        B1[j].D1.SS.x = 400;
        B1[j].D1.DJ.x = 500;
        B1[j].D1.SS.y = 150 + i;
        B1[j].D1.DJ.y = 200 + i;
        bar(B1[j].D1.SS.x, B1[j].D1.SS.y, B1[j].D1.DJ.x, B1[j].D1.DJ.y);
        rectangle(B1[j].D1.SS.x, B1[j].D1.SS.y, B1[j].D1.DJ.x, B1[j].D1.DJ.y);
        //bar draws a filled-in, rectangular, two-dimensional bar.
        //The bar is filled using the current fill pattern and fill color. bar does not outline the bar
        ///deci e ca un dreptunghi doar ca pot sa il stilizezi
        setbkcolor(LIGHTRED);
    }
    if (regiune == 0)
        deseneazaSageata(550, 275, 570, 275);
    if (regiune == 1)
        deseneazaSageata(550, 175, 570, 175);
    if (schimba_24h_to_12h == true)
        deseneazaSageata(550, 375, 570, 375);
    if (schimba_24h_to_12h == false)
        deseneazaSageata(550, 475, 570, 475);
    outtextxy(412, 170, "Anglia");
    outtextxy(412, 270, "Romania");
    outtextxy(412, 370, "Format 12h");
    outtextxy(412, 470, "Format 24h");
}

int butonAlesSetari()
{
    int j;
    punct p;
    if (ismouseclick(WM_LBUTTONDOWN))
    {
        clearmouseclick(WM_LBUTTONDOWN);
        p.x = mousex();
        p.y = mousey();
        for (j = 0; j <= 3; j++)
            if (apartine(p, B1[j].D1))
            {
                return j;
            }

    }
    return -1;
}

void deseneazaPaginaAlarma()
{
    alarma.ore = 0;
    alarma.minute = 0;
    int k = 1;
    while (k)
    {

        setbkcolor(BLACK);
        cleardevice();
        setcolor(WHITE);

        seteazaStilText;
        deseneazaCasutaIesire();

        seteazaStilText;
        outstreamxy(220, 280);
        bgiout << setw(2) << setfill('0') << alarma.ore << "                                                                                                    " << setw(2) << setfill('0') << alarma.minute;
        seteazaStilTitlu;
        outtextxy(350, 50, "Alarma");

        for (int i = 1; i <= 4; i++)
        {
            B2[i].D.SS.x = 200 * i - 100;
            B2[i].D.DJ.x = 200 * i;
            B2[i].D.SS.y = 250;
            B2[i].D.DJ.y = 350;
            rectangle(B2[i].D.SS.x, B2[i].D.SS.y, B2[i].D.DJ.x, B2[i].D.DJ.y);
            bar(B2[i].D.SS.x, B2[i].D.SS.y, B2[i].D.DJ.x, B2[i].D.SS.y);
            setbkcolor(LIGHTRED);

        }

        if (intoarcereMeniuPrincipal() != 0)
        {
            k = 0;
            cout << "[INFO]Intoarcere la meniu." << endl;
        }
        delay(1000);
    }

}

int butonAlesAlarma()
{
    int i;
    punct p;
    if (ismouseclick(WM_LBUTTONDOWN))
    {
        clearmouseclick(WM_LBUTTONDOWN);
        p.x = mousex();
        p.y = mousey();
        for (i = 1; i <= 4; i++)
            if (apartine(p, B2[i].D))
            {
                return i;
            }
    }
    return 0;
}

void hover()
{
    punct p;
    p.x = mousex();
    p.y = mousey();
    for (int i = 1; i <= nrButoane; i++)
        if (apartine(p, B[i].D))
        {
            B[i].hovered = 1;
        }
        else
            B[i].hovered = 0;
}

void animatieMeniuPrincipal(int x1, int y1, int x2, int y2)
{
    setcolor(WHITE);
    line(x1, y1, x1 - 10, y1 - 10);
    line(x1, y1, x1 + 10, y1 - 10);

    line(x2, y2, x2 - 10, y2 + 10);
    line(x2, y2, x2 + 10, y2 + 10);
}

unsigned int m = 0;
int verifHover()            //animatie selectare buton meniu
{
    m = 0;
    for (int i = 1; i <= nrButoane; i++)
        if (B[i].hovered == 1)
        {
            animatieMeniuPrincipal(B[i].D.SS.x + 60, B[i].D.SS.y - 5, B[i].D.DJ.x - 60, B[i].D.DJ.y + 5);
            m = 1;
        }
    delay(250);
    if (m == 0)    //caz in care niciun buton nu e hovered
        return 0;
    if (m == 1) //caz in care un buton e hovered si trebuie sa redesenez meniul pt a crea efectul
    {
        deseneazaMeniul();
    }

}

int main()
{

    int comanda, butonul_apasat, buton_apasat_setari, buton_apasat_alarma;
    initwindow(900, 600);
    setlinestyle(0, 1, 2);
    deseneazaMeniul();
    deseneazaPaginaSetari();
    setactivepage(paginaMeniului);

    do
    {

        hover();
        verifHover();

        butonul_apasat = butonAles();
        if (butonul_apasat != 0)
        {
            comanda = butonul_apasat;
            /////////////////////////////////////////////////////MENIU SETARI/////////////////////////////////////////////////////
            if (comanda == 1)
            {
                cout << "[INFO]Afisare setari." << endl;
                setvisualpage(paginaSetari);
                deseneazaPaginaSetari();
            }
            while (comanda == 1)
            {
                buton_apasat_setari = butonAlesSetari();
                if (buton_apasat_setari != -1)
                {
                    if (buton_apasat_setari == 0)
                    {
                        regiune = 1;
                        cout << "[INFO]Timpul setat pentru Anglia" << endl;
                        deseneazaPaginaSetari();
                    }
                    if (buton_apasat_setari == 1)
                    {
                        regiune = 0;
                        cout << "[INFO]Timpul setat pentru Romania" << endl;
                        deseneazaPaginaSetari();
                    }

                    if (buton_apasat_setari == 2)
                    {
                        cout << "[INFO]Format ceas:12h." << endl;
                        schimba_24h_to_12h = true;
                        deseneazaPaginaSetari();
                    }

                    if (buton_apasat_setari == 3)
                    {
                        cout << "[INFO]Format ceas:24h." << endl;
                        schimba_24h_to_12h = false;
                        deseneazaPaginaSetari();
                    }
                }

                if (intoarcereMeniuPrincipal() != 0)
                {
                    comanda = 10; //numar random doar ca sa iasa din while
                    setvisualpage(paginaMeniului);
                    setactivepage(paginaMeniului);
                    cout << "[INFO]Intoarcere la meniu." << endl;
                }
            }
            ///////////////////////////////////////////////////////////////////^MENIU SETARI^///////////////////////////////////////////////////////////////

            if (comanda == 2)
            {
                cout << "[INFO]Meniu Alarma." << endl;


                setvisualpage(paginaAlarma);
                deseneazaPaginaAlarma();
                setactivepage(paginaMeniului);
                setvisualpage(paginaMeniului);
                deseneazaMeniul();
            }

            if (comanda == 3)
            {
                if (schimba_24h_to_12h == false)
                {
                    cout << "[INFO]Afisare ceas digital(24h)." << endl;
                    setactivepage(paginaCeasDigital);
                    setvisualpage(paginaCeasDigital);
                    iaTimpulLocal();
                    scrieTimpulDigital_24h();
                    setvisualpage(paginaMeniului);
                    setactivepage(paginaMeniului);
                }
                else if (schimba_24h_to_12h == true)
                {
                    cout << "[INFO]Afisare ceas digital(12h)." << endl;
                    setactivepage(paginaCeasDigital);
                    setvisualpage(paginaCeasDigital);
                    iaTimpulLocal();
                    scrieTimpulDigital_12h();
                    setvisualpage(paginaMeniului);
                    setactivepage(paginaMeniului);
                }
            }

            if (comanda == 4)
            {
                cout << "[INFO]Afisare ceas analogic." << endl;
                setactivepage(paginaCeasAnalogic);
                setvisualpage(paginaCeasAnalogic);
                deseneazaCeasAnalogic();
                setvisualpage(paginaMeniului);
                setactivepage(paginaMeniului);
            }

            if (comanda == 5)
                cout << "[INFO]IESIRE.";
        }
    } while (comanda != 5);
    closegraph();
    return 0;
}