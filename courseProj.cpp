#include "framework.h"
#include "courseProj.h"
#include <Commdlg.h>
#define MAX_LOADSTRING 100





class NunFunc
{
public:

    static   long long randNaturalNum()
    {
        long long n;

        do
        {
            n = rand() % 250;
        } while (!isSimple(n));

        return n;
    }

    static long long eylorFunc(const   long long a, const   long long b)
    {
        return (a - 1) * (b - 1);
    }

    static  unsigned long long openExhibitor(const   long long eylorNum)
    {
        long long n;

        for (long long i = 0; i < eylorNum; i++)
        {
            if (isSimple(i) && isMutSimple(i, eylorNum))
            {
                n = i;
                break;
            }
        }

        return n;
    }

private:

    static bool isSimple(const   long long num)
    {
        if (num < 2)
            return false;

        for (long long i = 2; i <= sqrt(num); i++)
            if (num % i == 0)
                return false;
        return true;
    }


    static bool isMutSimple(long long a, long long b)
    {

        for (long long gcd = a; ; gcd = b, b = a % b, a = gcd)
            if (!b) return gcd == 1;

    }

};


struct Key
{
    Key() {}

    Key(long long _num, long long _mod)
    {
        num = _num;
        mod = _mod;
    }

    long long num;
    long long mod;
};



class KeyGen
{
public:
    static std::vector<Key> genKeys()
    {
        std::vector<Key> keys;


        long long p;

        long long q;

        long long mod;


        do
        {
            p = NunFunc::randNaturalNum();
            q = NunFunc::randNaturalNum();
            mod = p * q;
        } while (mod < 300);




        long long fi = NunFunc::eylorFunc(p, q);

        long long e = NunFunc::openExhibitor(fi);


        /*      cout << "p\t" << p << endl;

              cout << "q\t" << q << endl;

              cout << "mod\t" << mod << endl;

              cout << "fi\t" << fi << endl;

              cout << "e\t" << e << endl << endl;
      */

        keys.push_back(Key(e, mod));


        for (long long d = 0; true; d++)
            if ((d * e) % fi == 1)
            {
                keys.push_back(Key(d, mod));
                break;
            }


        return keys;
    }

    static unsigned long long unlockData(unsigned long long lockVal, Key unlockKey)
    {
        std::vector<unsigned long long> unlockbuf;

        for (int i = 0; i < unlockKey.num; i++)
        {
            if (i % 2 == 0)
            {
                unlockbuf.push_back(lockVal);
            }
            else
            {

                unlockbuf[unlockbuf.size() - 1] *= lockVal;
            }

        }

        unsigned long long xunlock = unlockbuf[0] % unlockKey.mod;

        for (int i = 1; i < unlockbuf.size(); i++)
        {
            if (i <= unlockbuf.size() - 1)
            {
                xunlock *= unlockbuf[i];
                xunlock %= unlockKey.mod;
            }
        }

        return xunlock;
    }

    static unsigned long long lockData(unsigned long long lockVal, Key unlockKey)
    {
        std::vector<unsigned long long> unlockbuf;

        for (unsigned long long i = 0; i < unlockKey.num; i++)
        {
            if (i % 2 == 0)
            {
                unlockbuf.push_back(lockVal);
            }
            else
            {

                unlockbuf[unlockbuf.size() - 1] *= lockVal;
            }

        }

        unsigned long long xunlock = unlockbuf[0] % unlockKey.mod;

        for (unsigned long long i = 1; i < unlockbuf.size(); i++)
        {
            if (i <= unlockbuf.size() - 1)
            {
                xunlock *= unlockbuf[i];
                xunlock %= unlockKey.mod;
            }
        }

        return xunlock;
    }
};








HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_COURSEPROJ, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_COURSEPROJ));

    MSG msg;



    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_COURSEPROJ));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = 0;// MAKEINTRESOURCEW(IDC_COURSEPROJ);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

#define GENERATE_KEY 442
#define LOCK_FILE 443
#define UNLOCK_FILE 444


HWND staticPublMod;
HWND staticPublNum;
HWND staticPrivMod;
HWND staticPrivNum;


HWND PrivMod;
HWND PrivNum;



BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, 300 + 16, 450, nullptr, nullptr, hInstance, nullptr);

    CreateWindow(L"static", L"Ключ для шифрування(публічний)", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_CENTER, 0, 0, 300, 20, hWnd, NULL, NULL, NULL);
    staticPublMod = CreateWindow(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_CENTER | ES_NUMBER | ES_READONLY, 0, 25, 300, 20, hWnd, NULL, NULL, NULL);
    staticPublNum = CreateWindow(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_CENTER | ES_NUMBER | ES_READONLY, 0, 46, 300, 20, hWnd, NULL, NULL, NULL);
    CreateWindow(L"static", L"Ключ для розшифрування(особистий)", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_CENTER, 0, 85, 300, 20, hWnd, NULL, NULL, NULL);
    staticPrivMod = CreateWindow(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_CENTER | ES_NUMBER | ES_READONLY, 0, 110, 300, 20, hWnd, NULL, NULL, NULL);
    staticPrivNum = CreateWindow(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_CENTER | ES_NUMBER | ES_READONLY, 0, 131, 300, 20, hWnd, NULL, NULL, NULL);
    CreateWindow(L"button", L"Згенерувати ключі", WS_VISIBLE | WS_CHILD, 0, 155, 300, 50, hWnd, (HMENU)GENERATE_KEY, NULL, NULL);

    CreateWindow(L"button", L"Зашифрувати файл", WS_VISIBLE | WS_CHILD, 0, 205, 300, 50, hWnd, (HMENU)LOCK_FILE, NULL, NULL);

    CreateWindow(L"button", L"Розшифрувати файл", WS_VISIBLE | WS_CHILD, 0, 300, 300, 50, hWnd, (HMENU)UNLOCK_FILE, NULL, NULL);
    PrivMod = CreateWindow(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_CENTER | ES_NUMBER, 0, 356, 300, 20, hWnd, NULL, NULL, NULL);
    PrivNum = CreateWindow(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_CENTER | ES_NUMBER, 0, 377, 300, 20, hWnd, NULL, NULL, NULL);


    if (!hWnd)
    {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
}



std::vector<Key> keys;


long value;



LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
   
    switch (message)
    {

    case WM_CREATE:
        srand(time(0));
        break;

    case WM_COMMAND:
    {
        switch (LOWORD(wParam))
        {
        case GENERATE_KEY:
        {
            keys = KeyGen::genKeys();

            SetWindowText(staticPublMod, std::to_wstring(keys[0].mod).c_str());
            SetWindowText(staticPublNum, std::to_wstring(keys[0].num).c_str());
            SetWindowText(staticPrivMod, std::to_wstring(keys[1].mod).c_str());
            SetWindowText(staticPrivNum, std::to_wstring(keys[1].num).c_str());
        }
            break;


        case LOCK_FILE:
        {
            if (!keys.empty() && keys[0].mod != 0 && keys[0].num != 0)
            {

                OPENFILENAME ofn;
                wchar_t szFile[260];
                ZeroMemory(&ofn, sizeof(ofn));

                ofn.lStructSize = sizeof(ofn);
                ofn.hwndOwner = NULL;
                ofn.lpstrFile = szFile;
                ofn.lpstrFile[0] = '\0';
                ofn.nMaxFile = sizeof(szFile);
                ofn.lpstrFilter = L"*.txt\0";
                ofn.nFilterIndex = 1;
                ofn.lpstrFileTitle = NULL;
                ofn.nMaxFileTitle = 0;
                ofn.lpstrInitialDir = NULL;
                ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

                if (GetOpenFileName(&ofn) == TRUE)
                {
                    std::string buffer;
                    std::ifstream fin;
                    std::ofstream fout;


                    fin.open(ofn.lpstrFile);

                    char ch;

                    while (fin.get(ch))
                    {
                        buffer += std::to_string(KeyGen::lockData(ch, keys[0]));
                        buffer += ' ';
                    }

                    fin.close();

                    fout.open(ofn.lpstrFile);

                    fout << buffer;

                    fout.close();

                    MessageBox(hWnd, L"Файл успешно зашифрован!", L"Успех!", MB_OK | MB_ICONINFORMATION);
                }
                else
                {
                    MessageBox(hWnd, L"Не удалось открыть файл!", L"Ошибка!", MB_OK | MB_ICONERROR);
                }
            }
            else
            {
                MessageBox(hWnd, L"Сначала сгенерируйте ключ!", L"Ошибка!", MB_OK | MB_ICONERROR);
            }
        }
            break;


        case UNLOCK_FILE:
        {

            wchar_t str[10];
            wchar_t str1[10];
            GetWindowText(PrivMod, str, 10);
            GetWindowText(PrivNum, str1, 10);

            Key otherKey(wcstol(str1, 0, 10), wcstol(str, 0, 10));
       
            if (otherKey.mod != 0 && otherKey.num != 0)
            {
                OPENFILENAME ofn;
                wchar_t szFile[260];
                ZeroMemory(&ofn, sizeof(ofn));

                ofn.lStructSize = sizeof(ofn);
                ofn.hwndOwner = NULL;
                ofn.lpstrFile = szFile;
                ofn.lpstrFile[0] = '\0';
                ofn.nMaxFile = sizeof(szFile);
                ofn.lpstrFilter = L"*.txt\0";
                ofn.nFilterIndex = 1;
                ofn.lpstrFileTitle = NULL;
                ofn.nMaxFileTitle = 0;
                ofn.lpstrInitialDir = NULL;
                ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

                if (GetOpenFileName(&ofn) == TRUE)
                {
                    std::string buffer;
                    std::string tempbuffer;
                    std::ifstream fin;
                    std::ofstream fout;


                    fin.open(ofn.lpstrFile);


                    while (!fin.eof())
                    {

                        fin >> tempbuffer;

                        buffer += (char)KeyGen::unlockData(atoi(tempbuffer.c_str()), otherKey);
                    }

                    fin.close();

                    fout.open(ofn.lpstrFile);

                    fout << buffer;

                    fout.close();
                    MessageBox(hWnd, L"Файл успешно расшифрован!", L"Успех!", MB_OK | MB_ICONINFORMATION);
                }
                else
                {
                    MessageBox(hWnd, L"Не удалось открыть файл!", L"Ошибка!", MB_OK | MB_ICONERROR);
                }
            }
            else
            {
                MessageBox(hWnd, L"Введите ключ для расшифровки", L"Ошибка!", MB_OK | MB_ICONERROR);
            }
        }
        break;


        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }

    }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

