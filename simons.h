
static int score;
static bool pogresno=FALSE;
vector<int> cilj;
vector<int> pritisnuti;

static int brojac=100;
static int trenutni=0;
static bool ckv=false;
static bool zkv=false;
static bool zukv=false;
static bool pkv=false;
static bool prikaz=true;

static HBRUSH cetke[]={CreateSolidBrush(RGB(85,107,47)),CreateSolidBrush(RGB(205,92,92)),
                        CreateSolidBrush(RGB(240,230,140)),CreateSolidBrush(RGB(0,0,139))
};

static HBRUSH klikcetke[]={CreateSolidBrush(RGB(0,255,0)),CreateSolidBrush(RGB(255,0,0)),
                        CreateSolidBrush(RGB(255,255,0)),CreateSolidBrush(RGB(0,0,255))
};

struct Kvadrat{
    int xl;
    int yg;
    int xd;
    int yd;
    int rgb;
    Kvadrat();
    Kvadrat(int a,int b, int c,int d,int e){
        xl=a;yg=b;xd=c;yd=d;rgb=e;
    }
};

static vector<Kvadrat> kvadrati;

int pronadjiKvadrat(int x, int y){
    for(int i=0;i<kvadrati.size();++i){
        if(x>=kvadrati.at(i).xl && x<=kvadrati.at(i).xd
           && y>=kvadrati.at(i).yg && y<=kvadrati.at(i).yd)
            return i;
    }
    return -1;
}

void pokreniSS(){
    pritisnuti.clear();
    cilj.clear();
    for(int i=0;i<=score;++i){
        cilj.push_back(rand()%4);
    }
    trenutni=0;
    brojac=150;
    prikaz=true;
}

void provjeriSimon(){
    int temp=0;
    if(pritisnuti.size()==cilj.size()){
        for(int i=0;i<pritisnuti.size();++i){
            if(pritisnuti.at(i)==cilj.at(i)) continue;
            else temp++;
        }
        if(temp){
            MessageBox(NULL,"Simon kaze da ste pogrijesili!","Gotova igra",MB_OK);
        }
        else{
            score++;
            pokreniSS();
        }
    }else return;
}

void dodajKlik(int x,int y){
    if(pritisnuti.size()<cilj.size()){
        int i=pronadjiKvadrat(x,y);
        if(i>=0) pritisnuti.push_back(i);
    }
    provjeriSimon();
}

void initializeSimon(HWND hwnd){
    RECT crect;
    GetClientRect(hwnd,&crect);
    int xs=(crect.right-crect.left)/2;
    int ys=(crect.bottom-crect.top)/2;
    kvadrati.push_back(Kvadrat(xs-325,ys-205,xs-5,ys-5,0));
    kvadrati.push_back(Kvadrat(xs+5,ys-205,xs+325,ys-5,1));
    kvadrati.push_back(Kvadrat(xs-325,ys+5,xs-5,ys+205,2));
    kvadrati.push_back(Kvadrat(xs+5,ys+5,xs+325,ys+205,3));
    cilj.clear();
    pritisnuti.clear();
    score=0;
    pokreniSS();
    brojac=150;
    trenutni=0;
    prikaz=true;
}

void renderSimon(HWND hwnd){
    if(pogresno) return;
    RECT crect;
    GetClientRect(hwnd, &crect);
    HDC hdc = GetDC(hwnd);
    HDC hdcBuffer=CreateCompatibleDC(hdc);
    HBITMAP hbmBuffer=CreateCompatibleBitmap(hdc,crect.right,crect.bottom);
    HBITMAP hbmOldBuffer=(HBITMAP)SelectObject(hdcBuffer,hbmBuffer);
    HDC hdcMem=CreateCompatibleDC(hdc);
    HBITMAP hbmOld1;
    hbmOld1=(HBITMAP) SelectObject(hdcMem,hbmmempoz);
    BitBlt(hdcBuffer,0,0,bitmapmempoz.bmWidth,bitmapmempoz.bmHeight,hdcMem,0,0,SRCCOPY);

    for(int i=0;i<kvadrati.size();++i){
        SelectObject(hdcBuffer,cetke[kvadrati.at(i).rgb]);
        Rectangle(hdcBuffer,kvadrati.at(i).xl,kvadrati.at(i).yg,kvadrati.at(i).xd,kvadrati.at(i).yd);
    }
    if(prikaz){
        SelectObject(hdcBuffer,klikcetke[kvadrati.at(cilj.at(trenutni)).rgb]);
        Rectangle(hdcBuffer,kvadrati.at(cilj.at(trenutni)).xl,kvadrati.at(cilj.at(trenutni)).yg,
        kvadrati.at(cilj.at(trenutni)).xd,kvadrati.at(cilj.at(trenutni)).yd);
        brojac--;
    }
    if(brojac==0){
        SelectObject(hdcBuffer,cetke[kvadrati.at(cilj.at(trenutni)).rgb]);
        Rectangle(hdcBuffer,kvadrati.at(cilj.at(trenutni)).xl,kvadrati.at(cilj.at(trenutni)).yg,
                kvadrati.at(cilj.at(trenutni)).xd,kvadrati.at(cilj.at(trenutni)).yd);
        trenutni++;
        if(trenutni==cilj.size()){
            prikaz=false;
        }
        brojac=100;
    }

    if(pritisnuti.size()>0){
        SelectObject(hdcBuffer,klikcetke[kvadrati.at(pritisnuti.at(pritisnuti.size()-1)).rgb]);
        Rectangle(hdcBuffer,kvadrati.at(pritisnuti.at(pritisnuti.size()-1)).xl,kvadrati.at(pritisnuti.at(pritisnuti.size()-1)).yg,
                            kvadrati.at(pritisnuti.at(pritisnuti.size()-1)).xd,kvadrati.at(pritisnuti.at(pritisnuti.size()-1)).yd);
    }


    BitBlt(hdc,0,0,crect.right,crect.bottom,hdcBuffer,0,0,SRCCOPY);
    DeleteObject(hdcMem);
    DeleteObject(hbmBuffer);
    SelectObject(hdcBuffer, hbmOldBuffer);
    DeleteObject(hdcBuffer);
    DeleteObject(hbmOldBuffer);
}
