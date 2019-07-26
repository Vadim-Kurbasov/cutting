#include <windows.h>
#include "Cod.h"
#include "resource.h"
#include "winres.h"
#include "string.h"
#include<fstream>
#include <iostream>
#include "TCHAR.H" 

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
OPENFILENAME ofn;       // структура станд. блока диалога
char szFile[260];       // буфер для имени файла
char szFileTitle[260];
HWND hwnd;              // окно-владелец

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

ENHMETAHEADER emh{};
HDC hDC{};
std::ofstream fout;
std::ifstream fin;

int openq{ 77 };
int open{0};
#define FILE_NAME "Pict1.emf"
double MetalengthIshodnic{};
double MetawidthIshodnic{};

HENHMETAFILE hemf; // Метафайл
RECT rect11;
int xMeta1, yMeta1, xMeta2, yMeta2;

LPTSTR lpString= new TCHAR[100]; // Cторока для имени файла
LPTSTR lpStringCopy = new TCHAR[100];//Cторока для имени открываемого файла файла


HDC hdcEMF; // Метафайл
HWND hEdtMeta;  //Дескриптор роля диалогового окна "Создать"
HWND hEdtEmf;  //Дескриптор роля диалогового окна "Создать"
RECT r;// исходный прямоугольник	
HWND hWnd;

TCHAR charF[4] ;
void DrawSomething(HDC);
int flajok{ 0 }; //для замены элементов местами
const int widthpen{ 5 };          // ширина пера
const double propil{ 3 };
double lengthIshodnic{}; // длина исходника
double widthIshodnic{}; // ширина исходника
double squar{};         // площадь листа
double squarPiece{};     // площадь куска
int countPiece{ 0 };
double length{0};
double weight{0};
double lengthb{ 0 };
double weightb{ 0 };
double lengthd{ 0 };
double weightd{ 0 };
double lengthc{ 0 };
double weightc{ 0 };
double lengthe{ 0 };
double weighte{ 0 };
double lengthf{ 0 };
double weightf{ 0 };
double lengthg{ 0 };
double weightg{ 0 };
double lengthh{ 0 };
double weighth{ 0 };
double lengthi{ 0 };
double weighti{ 0 };
double lengthj{ 0 };
double weightj{ 0 };
double lengthk{ 0 };
double weightk{ 0 };
double lengthl{ 0 };
double weightl{ 0 };
double lengthm{ 0 };
double weightm{ 0 };
double lengthn{ 0 };
double weightn{ 0 };
double lengtho{ 0 };
double weighto{ 0 };
double lengthp{ 0 };
double weightp{ 0 };
double lengthq{ 0 };
double weightq{ 0 };
double lengthrr{ 0 };
double weightrr{ 0 };
double lengths{ 0 };
double weights{ 0 };
double lengtht{ 0 };
double weightt{ 0 };
double lengthu{ 0 };
double weightu{ 0 };
double lengthv{ 0 };
double weightv{ 0 };
double lengthw{ 0 };
double weightw{ 0 };
double lengthx{ 0 };
double weightx{ 0 };
double lengthy{ 0 };
double weighty{ 0 };
double lengthz{ 0 };
double weightz{ 0 };
double lengthxx{ 0 };
double weightxx{ 0 };
double lengthww{ 0 };
double weightww{ 0 };
double lengthee{ 0 };
double weightee{ 0 };
double lengthyy{ 0 };
double weightyy{ 0 };

int mas{ 1730 };
int flagMeta{ 1 };
 	
double len1{};
double len2{};

DLGPROC CALLBACK PovorotProc(HWND, UINT, WPARAM, LPARAM);//оконная процедура для поворота элемента
DLGPROC CALLBACK DELETEProc(HWND, UINT, WPARAM, LPARAM);//оконная процедура для удаления элемента
DLGPROC CALLBACK SWAPProc(HWND , UINT , WPARAM , LPARAM );//оконная процедура для замены элементов местами
DLGPROC CALLBACK WndAddToOneProc(HWND, UINT, WPARAM, LPARAM);//оконная процедура для прибавления кусков по одному
DLGPROC CALLBACK WndNewListProc(HWND, UINT, WPARAM, LPARAM);//оконная процедура для исходника
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);// основная оконная процедура
//====================================================================

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int
	nCmdShow)
{
	HWND hWnd;
	MSG msg;
	WNDCLASSEX wc;
	char szClassName[] = "KWndClass";
	wc.cbSize = sizeof(wc);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInst;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = szClassName;
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	// Регистрируем класс окна
	if (!RegisterClassEx(&wc)) {
		char msg[100] = "Cannot register class: ";
		strcpy_s(msg, szClassName);
		MessageBox(NULL, msg, "Error", MB_OK);
		return 0;
	}
	// получаем дескриптор окна. Создаем окно
	hWnd = CreateWindow(szClassName, "Раскрой листа", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, (HMENU)NULL, hInst, NULL);


	if (!hWnd) {
		char text[100] = "Cannot create window: ";
		strcpy_s(text, "Application");
		MessageBox(NULL, text, "Error", MB_OK);
		return 0;
	}

	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// Инициализация структуры OPENFILENAME
	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = hwnd;
	ofn.lpstrFile = szFile;
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = 0/*"All\0*.*\0Text\0*.TXT\0"*/;
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = szFileTitle;
	ofn.nMaxFileTitle = 260;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@2

	 MENUINFO mi;
	mi.cbSize = sizeof(mi);
	mi.hbrBack = CreateSolidBrush(RGB(237, 237, 237));
	mi.fMask = MIM_BACKGROUND;
	mi.dwStyle = MNS_DRAGDROP;

	HMENU hMainMenu = CreateMenu();
	
	HMENU hPopMenuFile = CreatePopupMenu();
    HMENU hPopMenuPravka = CreatePopupMenu();
	AppendMenu(hMainMenu, MF_OWNERDRAW, NULL, NULL);
	AppendMenu(hMainMenu, MF_STRING | MF_POPUP, (UINT)hPopMenuFile, "Файл");
	AppendMenu(hMainMenu, MF_STRING | MF_POPUP, (UINT)hPopMenuPravka, "Работа с листом");
	AppendMenu(hMainMenu, MF_STRING | MF_POPUP, (UINT)hPopMenuPravka, ofn.lpstrFileTitle);

    //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	AppendMenu(hPopMenuFile, MF_STRING, IDMyOpenMetaFileNew, "Открыть");
	AppendMenu(hPopMenuFile, MF_STRING, IDMyCreatMetaFileNew, "Создать");
	AppendMenu(hPopMenuFile, MF_STRING, IDMySaveMetaFileNew, "Сохранить");
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

	AppendMenu(hPopMenuFile, MF_STRING, IDMyVIHOD, "Выход");
	AppendMenu(hPopMenuPravka, MF_STRING, AddToOne, "Добавить элемент");
	AppendMenu(hPopMenuPravka, MF_STRING, Swap, "Заменить местами элементы");
	AppendMenu(hPopMenuPravka, MF_STRING, Povorot, "Повернуть элемент");
	AppendMenu(hPopMenuPravka, MF_STRING, Delete, "Удалить элемент");

	SetMenuInfo(hMainMenu, &mi);
	SetMenu(hWnd, hMainMenu);
	SetMenu(hWnd, hPopMenuFile);

	// Показываем окно
	ShowWindow(hWnd, SW_SHOWMAXIMIZED);
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}
//====================================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{	
	int userReply;
	int userReplyNewList;
	int userReply2piece;	
	static double nPos{};
	static double cyClient = HIWORD(lParam);
	static double cxClient = LOWORD(lParam);

	PAINTSTRUCT ps;
	RECT ramka;
	RECT rect;//прямоугольник клиентской области
	RECT r;// исходный прямоугольник	
	RECT a;// первый кусок
	RECT b;
	RECT bCopy;
	RECT c;
	RECT d;
	RECT e;
	RECT f;
	RECT g;
	RECT h;
	RECT i;
	RECT j;
	RECT k;
	RECT l;
	RECT m;
	RECT n;
	RECT o;
	RECT p;
	RECT q;
	RECT rr;
	RECT s;
	RECT t;
	RECT u;
	RECT v;
	RECT w;
	RECT x;
	RECT y;
	RECT z;
	RECT xx;
	RECT ww;
	RECT ee;
	RECT yy;

	RECT ram1;
	RECT ram2;
	RECT ram3;
	RECT ram4;

	HRGN hRgnRam1{};
	HRGN hRgnRam2{};
	HRGN hRgnRam3{};
	HRGN hRgnRam4{};
	HRGN hRgna{};
	HRGN hRgnb{};
	HRGN hRgnc{};
	HRGN hRgnd{};
	HRGN hRgne{};
	HRGN hRgnf{};
	HRGN hRgng{};
	HRGN hRgnh{};
	HRGN hRgni{};
	HRGN hRgnj{};
	HRGN hRgnk{};
	HRGN hRgnl{};
	HRGN hRgnm{};
	HRGN hRgnn{};
	HRGN hRgno{};
	HRGN hRgnp{};
	HRGN hRgnq{};
	HRGN hRgnrr{};
	HRGN hRgns{};
	HRGN hRgnt{};
	HRGN hRgnu{};
	HRGN hRgnv{};
	HRGN hRgnw{};
	HRGN hRgnx{};
	HRGN hRgny{};
	HRGN hRgnz{};
	HRGN hRgnxx{};
	HRGN hRgnww{};
	HRGN hRgnee{};
	HRGN hRgnyy{};

	HINSTANCE hInst{};
	HBRUSH hBrush{};
	HPEN hPen{};
	HPEN hPen22{};

	HFONT  hFont{};
	HBRUSH hBrushIshod{};
	HBRUSH hBrushKusok{};
	HBRUSH hBrushFrame{};

	HWND  hwndNewList{};
	HWND  hwndAddToOne{};
	HWND hwndSwap{};
	HWND hwndDelete{};
	HWND hwndPovorot{};
	HWND hwndCreatMetaFile{};
	HWND hwndOpenMetaFile{};

	static int flag1{ 0 };
	static int flag2{ 0 };

	int left{ 50 }; //отступ по оси X 
	static double top{ -200 };   //отступ по оси Y
	static double top1{ -200 };// отступ по оси Y для отображения 1-го куска вне исходника
	static int countThumbtrack{};
	static double right{};
	static double bottom{};
	TCHAR StrA[20];
	static double len;
	static double CenaI;
	static double CenaII;

	static HWND hBtn0; // Дескриптор  кнопки "!"
	static HWND hBtn1; // Дескриптор  кнопки "Добавить"
	static HWND hBtn2; // Дескриптор кнопки  "Рассчитать"
	static HWND hBtn3; // Дескриптор кнопки  "Создать исходник"
	static HWND hBtn5; // Дескриптор кнопки  "Создать исходник"
	static HWND hEdt1, hEdt2, hEdt3, hEdt4; // дескрипторы полей редактирования
	static HWND hStat; // дескриптор статического текста
	static HWND hStatCena;
	POINT pos;
	POINT ishod;

	switch (uMsg)
	{

	case WM_SIZE:

		cyClient = HIWORD(lParam);
		cxClient = LOWORD(lParam);
		return 0;
		case WM_PAINT:
		
		hDC = BeginPaint(hWnd, &ps);
		hPen = CreatePen(
		PS_SOLID,   // стиль пера
		widthpen,       // ширина пера
		RGB(255, 255, 255)); // цвет пера
		SelectObject(hDC, hPen);
		hBrushIshod = CreateSolidBrush(RGB(0, 170, 0));
		hBrushKusok = CreateSolidBrush(RGB(50, 250, 0));
		hBrushFrame = CreateSolidBrush(RGB(255, 255, 255));
			
		SetMapMode(hDC, MM_ISOTROPIC); // Переход на логические координаты
		SetBkMode(hDC, TRANSPARENT); //заливка текста
		
		TextOut(hDC, 2200, -10, "Введите цену м2:", 16); // вывод текстовых сообщений
		TextOut(hDC, 40, -10, "Длина листа мм:", 15); // вывод текстовых сообщений
		TextOut(hDC, 400, -10, "Высота листа мм:", 16); // вывод текстовых сообщений
		TextOut(hDC, 1580, -10, "Площадь м2:", 11); // вывод текстовых сообщений
		TextOut(hDC, 1950, -10, "Цена руб:", 9); // вывод текстовых сообщений

		SetWindowExtEx(hDC, 1000, mas, 0);
		SetViewportExtEx(hDC, cxClient, -cyClient, 0);

		hFont = CreateFont(40, 15, 0, 0, 5, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, ("Consolas"));  // шрифт размеров элемента
		SelectObject(hDC, hFont);
		
		// исходник
		r.left = left; //отступ левого верхнего угла по оси X
		r.top = top;  //отступ левого верхнего угла по оси Y ;  +nPos это перерисовки прямоугольника дляполосы прокрутки	
		r.right = r.left + lengthIshodnic; // длина по оси X с учетом r.left
		r.bottom = r.top - widthIshodnic;// длина по оси Y с учетом r.top

		FillRect(hDC, &r, hBrushIshod);

		DrawText(hDC, "исходный лист", -1, &r,
			DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		SetWindowText(hStat, DoubleToStr(squar, 2));//Выводим площадь исходника в статическое поле

		/////////////////////////////////////////////////////////////////////////////////////////////
		// Создаем рамку регионов
		ram1.left = 40;
		ram1.top = -160;
		ram1.right = ram1.left + lengthIshodnic + 20;
		ram1.bottom = ram1.top - 10;
		hRgnRam1 = CreateRectRgnIndirect(&ram1);
	
		ram2.left = left + lengthIshodnic;
		ram2.top = top;
		ram2.right = ram2.left + 10;
		ram2.bottom = ram2.top - widthIshodnic;
		hRgnRam2 = CreateRectRgnIndirect(&ram2);
		CombineRgn(hRgnRam1, hRgnRam1, hRgnRam2, RGN_OR);
		
		ram3.left = 40;
		ram3.top = top - widthIshodnic;
		ram3.right = ram3.left + lengthIshodnic + 20;
		ram3.bottom = ram3.top - 10;
		hRgnRam3 = CreateRectRgnIndirect(&ram3);
		CombineRgn(hRgnRam1, hRgnRam1, hRgnRam3, RGN_OR);
	
		ram4.left = 40;
		ram4.top = top;
		ram4.right = ram4.left + 10;
		ram4.bottom = ram4.top - widthIshodnic;
		hRgnRam4 = CreateRectRgnIndirect(&ram4);
		CombineRgn(hRgnRam1, hRgnRam1, hRgnRam4, RGN_OR);

		// Первый кусок
		if (countPiece > 0)  // в следующем куске 2

		{
			//Этот код нужен для того, чтобы значение lenght и weight присваивалось только один раз 
			if (length == 0 & weight == 0)
			{
				length = len1 + propil; // len1 и len2 взяты из полей диалогового окна
				weight = len2 + propil;
				squar -= squarPiece; // Вычитаем площадь куска из исходника
			}

			if (length > lengthIshodnic | weight > widthIshodnic)
			{
				MessageBox(hWnd, "Недопустимые размеры",
					"", 0);
				length = 0;
				weight = 0;
				countPiece=0;
				squar = 0;

				DeleteObject(hRgnRam1);
				DeleteObject(hRgnRam2);
				DeleteObject(hRgnRam3);
				DeleteObject(hRgnRam4);
				DeleteObject(hRgna);
				DeleteObject(hRgnb);
				DeleteObject(hRgnc);
				DeleteObject(hRgnd);
				DeleteObject(hRgne);
				DeleteObject(hRgnf);
				DeleteObject(hRgng);
				DeleteObject(hRgnh);
				DeleteObject(hRgni);
				DeleteObject(hRgnj);
				DeleteObject(hRgnk);
				DeleteObject(hRgnl);
				DeleteObject(hRgnm);
				DeleteObject(hRgnn);
				DeleteObject(hRgno);
				DeleteObject(hRgnp);
				DeleteObject(hRgnq);
				DeleteObject(hRgnrr);
				DeleteObject(hRgns);
				DeleteObject(hRgnt);
				DeleteObject(hRgnu);
				DeleteObject(hRgnv);
				DeleteObject(hRgnw);
				DeleteObject(hRgnx);
				DeleteObject(hRgny);
				DeleteObject(hRgnz);
				DeleteObject(hRgnxx);
				DeleteObject(hRgnww);
				DeleteObject(hRgnee);
				DeleteObject(hRgnyy);

				
				 lengthb= 0 ;
				 weightb= 0 ;
				 lengthd= 0 ;
			     weightd= 0 ;
				 lengthc= 0 ;
				 weightc= 0 ;
				 lengthe= 0 ;
				 weighte= 0 ;
				 lengthf= 0 ;
				 weightf= 0 ;
				 lengthg= 0 ;
				 weightg= 0 ;
				lengthh= 0 ;
				 weighth= 0 ;
				lengthi= 0 ;
				weighti= 0 ;
				lengthj= 0 ;
				weightj= 0 ;
				lengthk= 0 ;
				weightk=0 ;
			   lengthl= 0 ;
				weightl= 0 ;
			    lengthm =0 ;
				weightm=0 ;
				 lengthn= 0 ;
				 weightn= 0 ;
				 lengtho= 0 ;
			   weighto= 0 ;
				 lengthp= 0 ;
				 weightp= 0 ;
				 lengthq= 0 ;
				 weightq =0 ;
				 lengthrr= 0 ;
			    weightrr= 0 ;
				 lengths= 0 ;
				 weights= 0 ;
				 lengtht= 0 ;
				 weightt= 0;
				 lengthu= 0 ;
			    weightu= 0 ;
				lengthv=0 ;
				 weightv= 0 ;
				 lengthw= 0 ;
				 weightw= 0 ;
				 lengthx= 0 ;
				 weightx= 0 ;
				 lengthy= 0 ;
				 weighty= 0 ;
			   lengthz= 0 ;
				 weightz= 0 ;
				 lengthxx= 0;
				 weightxx= 0 ;
				 lengthww= 0 ;
				 weightww= 0 ;
				 lengthee= 0 ;
				 weightee= 0 ;
				 lengthyy= 0 ;
				 weightyy= 0 ;

				 DeleteObject(hBrush);
				 DeleteObject(hBrushIshod);
				 DeleteObject(hBrushKusok);
				 DeleteObject(hBrushFrame);
				 DeleteObject(hPen);
				 DeleteObject(hFont);

				 DeleteObject(hDC);
				 EndPaint(hWnd, &ps);

				return 0;
			
			}

			a.left = left;	//отступ левого верхнего угла по оси X
			a.top = top1;  //отступ левого верхнего угла по оси Y: +pos.x это для перерисовки прямоугольника для полосы прокрутки
			a.right = a.left + length; // длина по оси X с учетом a.left
			a.bottom = a.top - weight; // длина по оси Y с учетом a.top
			hRgna = CreateRectRgnIndirect(&a);
			CombineRgn(hRgnRam1, hRgnRam1, hRgna, RGN_OR);
			FillRect(hDC, &a, hBrushKusok);

			FrameRgn(hDC, hRgna, hBrushFrame, 3, 3);
			DrawText(hDC, "1", -1, &a, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
			DrawText(hDC, IntToStr(length - propil), -1, &a, DT_SINGLELINE | DT_LEFT | DT_CENTER);
			DrawText(hDC, IntToStr(weight - propil), -1, &a, DT_SINGLELINE | DT_LEFT | DT_VCENTER);
			
			SetWindowText(hStat, DoubleToStr(squar, 2));//Выводим площадь исходника в статическое поле

		}
		
		// Второй кусок

		if (countPiece > 1)  // в следующем куске 2
		{
			//Этот код нужен для того, чтобы значение lenghtb и weightb присваивалось только один раз 
			if (lengthb == 0 & weightb == 0)
			{
				lengthb = len1 + propil; // len1 и len2 взяты из полей диалогового окна
				weightb = len2 + propil;
				squar -= squarPiece; // Вычитаем площадь куска из исходника
			}

			int	countBX = 0;
			int countBY = 0;
			int coX{};
			int flagg = 0;
			int fflagg = 0;
			int userReplyPiece;
			int countwarring{0};
			int countwarring2{ 0 };
			for (int coY = 0; coY < (widthIshodnic)& flag1 == 0; coY+=3, countBY-=3)
			{
				if (countwarring2 > 10000000)
				{
					SendMessage(hWnd, WM_DESTROY, 0, 0);
						
				}
				++countwarring2;

				for (int coX = 0; coX < (lengthIshodnic - lengthb) & flag1 == 0; coX+=3, countBX+=3)
				{
				if (countwarring > 10000000)
				{
						SendMessage(hWnd, WM_DESTROY, 0, 0);

					}
					++countwarring;
					b.left = left + countBX;	//отступ левого верхнего угла по оси X
					b.top = top1 + countBY;  //отступ левого верхнего угла по оси Y: +pos.x это для перерисовки прямоугольника для полосы прокрутки
					b.right = b.left + lengthb; // длина по оси X с учетом a.left
					b.bottom = b.top - weightb; // длина по оси Y с учетом a.top
					

					if (!(RectInRegion(hRgnRam1, &b)))
					{
						flag1 = 1;
						fflagg = 1;
					}
				}
				countBX = 0;
				coX = 0;
			}
			flag1 = 0;

			if (fflagg)
			{
	

				hRgnb = CreateRectRgnIndirect(&b);
				CombineRgn(hRgnRam1, hRgnRam1, hRgnb, RGN_OR);
				FillRect(hDC, &b, hBrushKusok);
				
				FrameRgn(hDC, hRgnb, hBrushFrame, 3, 3);
				DrawText(hDC, "2", -1, &b, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
				DrawText(hDC, IntToStr(lengthb - propil), -1, &b, DT_SINGLELINE | DT_LEFT | DT_CENTER);
				DrawText(hDC, IntToStr(weightb - propil), -1, &b, DT_SINGLELINE | DT_LEFT | DT_VCENTER);
				
				SetWindowText(hStat, DoubleToStr(squar, 2));//Выводим площадь исходника в статическое поле

			}
			else
			{
				{
					MessageBox(hWnd, "Недопустимые размеры",
						"", 0);
					lengthb = 0;
					weightb = 0;
					countPiece=1;
					//squar += squarPiece; // Возвращаем площадь исходника так как элемент не нарисовался
					squar = 0;
				DeleteObject(hRgnRam1);
				DeleteObject(hRgnRam2);
				DeleteObject(hRgnRam3);
				DeleteObject(hRgnRam4);
				DeleteObject(hRgna);
				DeleteObject(hRgnb);
				DeleteObject(hRgnc);
				DeleteObject(hRgnd);
				DeleteObject(hRgne);
				DeleteObject(hRgnf);
				DeleteObject(hRgng);
				DeleteObject(hRgnh);
				DeleteObject(hRgni);
				DeleteObject(hRgnj);
				DeleteObject(hRgnk);
				DeleteObject(hRgnl);
				DeleteObject(hRgnm);
				DeleteObject(hRgnn);
				DeleteObject(hRgno);
				DeleteObject(hRgnp);
				DeleteObject(hRgnq);
				DeleteObject(hRgnrr);
				DeleteObject(hRgns);
				DeleteObject(hRgnt);
				DeleteObject(hRgnu);
				DeleteObject(hRgnv);
				DeleteObject(hRgnw);
				DeleteObject(hRgnx);
				DeleteObject(hRgny);
				DeleteObject(hRgnz);
				DeleteObject(hRgnxx);
				DeleteObject(hRgnww);
				DeleteObject(hRgnee);
				DeleteObject(hRgnyy);

				
				
				 lengthd= 0 ;
			     weightd= 0 ;
				 lengthc= 0 ;
				 weightc= 0 ;
				 lengthe= 0 ;
				 weighte= 0 ;
				 lengthf= 0 ;
				 weightf= 0 ;
				 lengthg= 0 ;
				 weightg= 0 ;
				lengthh= 0 ;
				 weighth= 0 ;
				lengthi= 0 ;
				weighti= 0 ;
				lengthj= 0 ;
				weightj= 0 ;
				lengthk= 0 ;
				weightk=0 ;
			   lengthl= 0 ;
				weightl= 0 ;
			    lengthm =0 ;
				weightm=0 ;
				 lengthn= 0 ;
				 weightn= 0 ;
				 lengtho= 0 ;
			   weighto= 0 ;
				 lengthp= 0 ;
				 weightp= 0 ;
				 lengthq= 0 ;
				 weightq =0 ;
				 lengthrr= 0 ;
			    weightrr= 0 ;
				 lengths= 0 ;
				 weights= 0 ;
				 lengtht= 0 ;
				 weightt= 0;
				 lengthu= 0 ;
			    weightu= 0 ;
				lengthv=0 ;
				 weightv= 0 ;
				 lengthw= 0 ;
				 weightw= 0 ;
				 lengthx= 0 ;
				 weightx= 0 ;
				 lengthy= 0 ;
				 weighty= 0 ;
			   lengthz= 0 ;
				 weightz= 0 ;
				 lengthxx= 0;
				 weightxx= 0 ;
				 lengthww= 0 ;
				 weightww= 0 ;
				 lengthee= 0 ;
				 weightee= 0 ;
				 lengthyy= 0 ;
				 weightyy= 0 ;

				 DeleteObject(hBrush);
				 DeleteObject(hBrushIshod);
				 DeleteObject(hBrushKusok);
				 DeleteObject(hBrushFrame);
				 DeleteObject(hPen);
				 DeleteObject(hFont);

				 DeleteObject(hDC);
				 EndPaint(hWnd, &ps);

				return 0;
			
				}
			}
		}


		
		// Третий кусок

		if (countPiece > 2)  // в следующем куске 3
		{
			//	f2 = 1; // Обязательно поменять!!
				//Этот код нужен для того, чтобы значение lenghtb и weightb присваивалось только один раз 
			if (lengthc == 0 & weightc == 0)
			{
				lengthc = len1 + propil; // len1 и len2 взяты из полей диалогового окна
				weightc = len2 + propil;
				squar -= squarPiece; // Вычитаем площадь куска из исходника
			}

			int	countBX = 0;
			int countBY = 0;
			int coX{};
			int flagg = 0;
			int fflagg = 0;
			int userReplyPiece;
			int countwarring{ 0 };
			int countwarring2{ 0 };
			for (int coY = 0; coY < (widthIshodnic)& flag1 == 0; coY+=3, countBY-=3)
			{
				if (countwarring2 > 10000000)
				{
					SendMessage(hWnd, WM_DESTROY, 0, 0);
		//			return 0;
				}
				++countwarring2;
				for (int coX = 0; coX < (lengthIshodnic - lengthc) & flag1 == 0; coX+=3, countBX+=3)
				{
					
					if (countwarring > 10000000)
					{
						SendMessage(hWnd, WM_DESTROY, 0, 0);
		//				return 0;
					}
					++countwarring;
					c.left = left + countBX;	//отступ левого верхнего угла по оси X
					c.top = top1 + countBY;  //отступ левого верхнего угла по оси Y: +pos.x это для перерисовки прямоугольника для полосы прокрутки
					c.right = c.left + lengthc; // длина по оси X с учетом a.left
					c.bottom = c.top - weightc; // длина по оси Y с учетом a.top

					if (!(RectInRegion(hRgnRam1, &c)))
					{
						flag1 = 1;
						fflagg = 1;
					}
				}

				countBX = 0;
				coX = 0;
			}
			flag1 = 0;

			if (fflagg)
			{
	
				hRgnc = CreateRectRgnIndirect(&c);
				CombineRgn(hRgnRam1, hRgnRam1, hRgnc, RGN_OR);
			
				FillRect(hDC, &c, hBrushKusok);
				FrameRgn(hDC, hRgnc, hBrushFrame , 3, 3);
		
				DrawText(hDC, "3", -1, &c, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
				DrawText(hDC, IntToStr(lengthc - propil), -1, &c, DT_SINGLELINE | DT_LEFT | DT_CENTER);
				DrawText(hDC, IntToStr(weightc - propil), -1, &c, DT_SINGLELINE | DT_LEFT | DT_VCENTER);
				
				SetWindowText(hStat, DoubleToStr(squar, 2));//Выводим площадь исходника в статическое поле

				//SelectClipRgn(hDC, hRgnRam1);
			}
			else
			{
				{
					MessageBox(hWnd, "Недопустимые размеры",
						"", 0);
					lengthc = 0;
					weightc = 0;
				countPiece=2;
					//squar += squarPiece; // Возвращаем площадь исходника так как элемент не нарисовался
				squar = 0;
					
					DeleteObject(hRgnRam1);
					DeleteObject(hRgnRam2);
					DeleteObject(hRgnRam3);
					DeleteObject(hRgnRam4);
					DeleteObject(hRgna);
					DeleteObject(hRgnb);
					DeleteObject(hRgnc);
					DeleteObject(hRgnd);
					DeleteObject(hRgne);
					DeleteObject(hRgnf);
					DeleteObject(hRgng);
					DeleteObject(hRgnh);
					DeleteObject(hRgni);
					DeleteObject(hRgnj);
					DeleteObject(hRgnk);
					DeleteObject(hRgnl);
					DeleteObject(hRgnm);
					DeleteObject(hRgnn);
					DeleteObject(hRgno);
					DeleteObject(hRgnp);
					DeleteObject(hRgnq);
					DeleteObject(hRgnrr);
					DeleteObject(hRgns);
					DeleteObject(hRgnt);
					DeleteObject(hRgnu);
					DeleteObject(hRgnv);
					DeleteObject(hRgnw);
					DeleteObject(hRgnx);
					DeleteObject(hRgny);
					DeleteObject(hRgnz);
					DeleteObject(hRgnxx);
					DeleteObject(hRgnww);
					DeleteObject(hRgnee);
					DeleteObject(hRgnyy);


					lengthd = 0;
					weightd = 0;
					
					lengthe = 0;
					weighte = 0;
					lengthf = 0;
					weightf = 0;
					lengthg = 0;
					weightg = 0;
					lengthh = 0;
					weighth = 0;
					lengthi = 0;
					weighti = 0;
					lengthj = 0;
					weightj = 0;
					lengthk = 0;
					weightk = 0;
					lengthl = 0;
					weightl = 0;
					lengthm = 0;
					weightm = 0;
					lengthn = 0;
					weightn = 0;
					lengtho = 0;
					weighto = 0;
					lengthp = 0;
					weightp = 0;
					lengthq = 0;
					weightq = 0;
					lengthrr = 0;
					weightrr = 0;
					lengths = 0;
					weights = 0;
					lengtht = 0;
					weightt = 0;
					lengthu = 0;
					weightu = 0;
					lengthv = 0;
					weightv = 0;
					lengthw = 0;
					weightw = 0;
					lengthx = 0;
					weightx = 0;
					lengthy = 0;
					weighty = 0;
					lengthz = 0;
					weightz = 0;
					lengthxx = 0;
					weightxx = 0;
					lengthww = 0;
					weightww = 0;
					lengthee = 0;
					weightee = 0;
					lengthyy = 0;
					weightyy = 0;

					DeleteObject(hBrush);
					DeleteObject(hBrushIshod);
					DeleteObject(hBrushKusok);
					DeleteObject(hBrushFrame);
					DeleteObject(hPen);
					DeleteObject(hFont);

					DeleteObject(hDC);
					EndPaint(hWnd, &ps);

					return 0;
		
				}
			}
		}

		// Четвертый кусок

		if (countPiece > 3)  // в следующем куске 4
		{
			//	f2 = 1; // Обязательно поменять!!
				//Этот код нужен для того, чтобы значение lenghtb и weightb присваивалось только один раз 
			if (lengthd == 0 & weightd == 0)
			{
				lengthd = len1 + propil; // len1 и len2 взяты из полей диалогового окна
				weightd = len2 + propil;
				squar -= squarPiece; // Вычитаем площадь куска из исходника
			}

			int	countBX = 0;
			int countBY = 0;
			int coX{};
			int flagg = 0;
			int fflagg = 0;
			int userReplyPiece;
			int countwarring{ 0 };
			int countwarring2{ 0 };

			for (int coY = 0; coY < (widthIshodnic)& flag1 == 0; coY+=3, countBY-=3)
			{
				if (countwarring2 > 10000000)
				{
					SendMessage(hWnd, WM_DESTROY, 0, 0);
					return 0;
				}
				++countwarring2;

				for (int coX = 0; coX < (lengthIshodnic - lengthd) & flag1 == 0; coX+=3, countBX+=3)
				{
					if (countwarring > 10000000)
					{
						SendMessage(hWnd, WM_DESTROY, 0, 0);
						return 0;
					}
					++countwarring;

					d.left = left + countBX;	//отступ левого верхнего угла по оси X
					d.top = top1 + countBY;  //отступ левого верхнего угла по оси Y: +pos.x это для перерисовки прямоугольника для полосы прокрутки
					d.right = d.left + lengthd; // длина по оси X с учетом a.left
					d.bottom = d.top - weightd; // длина по оси Y с учетом a.top

					if (!(RectInRegion(hRgnRam1, &d)))
					{
						flag1 = 1;
						fflagg = 1;
					}
				}

				countBX = 0;
				coX = 0;
			}
			flag1 = 0;

			if (fflagg)
			{

				hRgnd = CreateRectRgnIndirect(&d);
				CombineRgn(hRgnRam1, hRgnRam1, hRgnd, RGN_OR);
				FillRect(hDC, &d, hBrushKusok);
				
				FrameRgn(hDC, hRgnd, hBrushFrame , 3, 3);
			
				DrawText(hDC, "4", -1, &d, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
				DrawText(hDC, IntToStr(lengthd - propil), -1, &d, DT_SINGLELINE | DT_LEFT | DT_CENTER);
				DrawText(hDC, IntToStr(weightd - propil), -1, &d, DT_SINGLELINE | DT_LEFT | DT_VCENTER);
				SetWindowText(hStat, DoubleToStr(squar, 2));//Выводим площадь исходника в статическое поле

			}
			else
			{
				{
					MessageBox(hWnd, "Недопустимые размеры",
						"", 0);
					lengthd = 0;
					weightd = 0;
				countPiece=3;
				squar = 0;
					
					
					DeleteObject(hRgnRam1);
					DeleteObject(hRgnRam2);
					DeleteObject(hRgnRam3);
					DeleteObject(hRgnRam4);
					DeleteObject(hRgna);
					DeleteObject(hRgnb);
					DeleteObject(hRgnc);
					DeleteObject(hRgnd);
					DeleteObject(hRgne);
					DeleteObject(hRgnf);
					DeleteObject(hRgng);
					DeleteObject(hRgnh);
					DeleteObject(hRgni);
					DeleteObject(hRgnj);
					DeleteObject(hRgnk);
					DeleteObject(hRgnl);
					DeleteObject(hRgnm);
					DeleteObject(hRgnn);
					DeleteObject(hRgno);
					DeleteObject(hRgnp);
					DeleteObject(hRgnq);
					DeleteObject(hRgnrr);
					DeleteObject(hRgns);
					DeleteObject(hRgnt);
					DeleteObject(hRgnu);
					DeleteObject(hRgnv);
					DeleteObject(hRgnw);
					DeleteObject(hRgnx);
					DeleteObject(hRgny);
					DeleteObject(hRgnz);
					DeleteObject(hRgnxx);
					DeleteObject(hRgnww);
					DeleteObject(hRgnee);
					DeleteObject(hRgnyy);


					
					lengthe = 0;
					weighte = 0;
					lengthf = 0;
					weightf = 0;
					lengthg = 0;
					weightg = 0;
					lengthh = 0;
					weighth = 0;
					lengthi = 0;
					weighti = 0;
					lengthj = 0;
					weightj = 0;
					lengthk = 0;
					weightk = 0;
					lengthl = 0;
					weightl = 0;
					lengthm = 0;
					weightm = 0;
					lengthn = 0;
					weightn = 0;
					lengtho = 0;
					weighto = 0;
					lengthp = 0;
					weightp = 0;
					lengthq = 0;
					weightq = 0;
					lengthrr = 0;
					weightrr = 0;
					lengths = 0;
					weights = 0;
					lengtht = 0;
					weightt = 0;
					lengthu = 0;
					weightu = 0;
					lengthv = 0;
					weightv = 0;
					lengthw = 0;
					weightw = 0;
					lengthx = 0;
					weightx = 0;
					lengthy = 0;
					weighty = 0;
					lengthz = 0;
					weightz = 0;
					lengthxx = 0;
					weightxx = 0;
					lengthww = 0;
					weightww = 0;
					lengthee = 0;
					weightee = 0;
					lengthyy = 0;
					weightyy = 0;

					DeleteObject(hBrush);
					DeleteObject(hBrushIshod);
					DeleteObject(hBrushKusok);
					DeleteObject(hBrushFrame);
					DeleteObject(hPen);
					DeleteObject(hFont);

					DeleteObject(hDC);
					EndPaint(hWnd, &ps);

					return 0;
				}
			}
		}

		// Пятый кусок

		if (countPiece > 4)  // в следующем куске 5
		{
			//	f2 = 1; // Обязательно поменять!!
				//Этот код нужен для того, чтобы значение lenghtb и weightb присваивалось только один раз 
			if (lengthe == 0 & weighte == 0)
			{
				lengthe = len1 + propil; // len1 и len2 взяты из полей диалогового окна
				weighte = len2 + propil;
				squar -= squarPiece; // Вычитаем площадь куска из исходника
			}

			int	countBX = 0;
			int countBY = 0;
			int coX{};
			int flagg = 0;
			int fflagg = 0;
			int userReplyPiece;
			int countwarring{ 0 };
			int countwarring2{ 0 };

			for (int coY = 0; coY < (widthIshodnic)& flag1 == 0; coY+=3, countBY-=3)
			{
				if (countwarring2 > 10000000)
				{
					SendMessage(hWnd, WM_DESTROY, 0, 0);
		
				}
				++countwarring2;

				for (int coX = 0; coX < (lengthIshodnic - lengthe) & flag1 == 0; coX+=3, countBX+=3)//!!
				{
					if (countwarring > 10000000)
					{
						SendMessage(hWnd, WM_DESTROY, 0, 0);
					}
					++countwarring;

					e.left = left + countBX;	//отступ левого верхнего угла по оси X
					e.top = top1 + countBY;  //отступ левого верхнего угла по оси Y: +pos.x это для перерисовки прямоугольника для полосы прокрутки
					e.right = e.left + lengthe; // длина по оси X с учетом a.left
					e.bottom = e.top - weighte; // длина по оси Y с учетом a.top

					if (!(RectInRegion(hRgnRam1, &e)))
					{
						flag1 = 1;
						fflagg = 1;
					}
				}

				countBX = 0;
				coX = 0;
			}
			flag1 = 0;

			if (fflagg)
			{
		
				hRgne = CreateRectRgnIndirect(&e);
				CombineRgn(hRgnRam1, hRgnRam1, hRgne, RGN_OR);
				FillRect(hDC, &e, hBrushKusok);
				FrameRgn(hDC, hRgne, hBrushFrame , 3, 3);
				DrawText(hDC, "5", -1, &e, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
				DrawText(hDC, IntToStr(lengthe - propil), -1, &e, DT_SINGLELINE | DT_LEFT | DT_CENTER);
				DrawText(hDC, IntToStr(weighte - propil), -1, &e, DT_SINGLELINE | DT_LEFT | DT_VCENTER);
				SetWindowText(hStat, DoubleToStr(squar, 2));//Выводим площадь исходника в статическое поле

			}
			else
			{
				{
					MessageBox(hWnd, "Недопустимые размеры",
						"", 0);
					lengthe = 0;
					weighte = 0;
				countPiece=4;
	
				squar = 0;
					DeleteObject(hRgnRam1);
					DeleteObject(hRgnRam2);
					DeleteObject(hRgnRam3);
					DeleteObject(hRgnRam4);
					DeleteObject(hRgna);
					DeleteObject(hRgnb);
					DeleteObject(hRgnc);
					DeleteObject(hRgnd);
					DeleteObject(hRgne);
					DeleteObject(hRgnf);
					DeleteObject(hRgng);
					DeleteObject(hRgnh);
					DeleteObject(hRgni);
					DeleteObject(hRgnj);
					DeleteObject(hRgnk);
					DeleteObject(hRgnl);
					DeleteObject(hRgnm);
					DeleteObject(hRgnn);
					DeleteObject(hRgno);
					DeleteObject(hRgnp);
					DeleteObject(hRgnq);
					DeleteObject(hRgnrr);
					DeleteObject(hRgns);
					DeleteObject(hRgnt);
					DeleteObject(hRgnu);
					DeleteObject(hRgnv);
					DeleteObject(hRgnw);
					DeleteObject(hRgnx);
					DeleteObject(hRgny);
					DeleteObject(hRgnz);
					DeleteObject(hRgnxx);
					DeleteObject(hRgnww);
					DeleteObject(hRgnee);
					DeleteObject(hRgnyy);


					
					lengthf = 0;
					weightf = 0;
					lengthg = 0;
					weightg = 0;
					lengthh = 0;
					weighth = 0;
					lengthi = 0;
					weighti = 0;
					lengthj = 0;
					weightj = 0;
					lengthk = 0;
					weightk = 0;
					lengthl = 0;
					weightl = 0;
					lengthm = 0;
					weightm = 0;
					lengthn = 0;
					weightn = 0;
					lengtho = 0;
					weighto = 0;
					lengthp = 0;
					weightp = 0;
					lengthq = 0;
					weightq = 0;
					lengthrr = 0;
					weightrr = 0;
					lengths = 0;
					weights = 0;
					lengtht = 0;
					weightt = 0;
					lengthu = 0;
					weightu = 0;
					lengthv = 0;
					weightv = 0;
					lengthw = 0;
					weightw = 0;
					lengthx = 0;
					weightx = 0;
					lengthy = 0;
					weighty = 0;
					lengthz = 0;
					weightz = 0;
					lengthxx = 0;
					weightxx = 0;
					lengthww = 0;
					weightww = 0;
					lengthee = 0;
					weightee = 0;
					lengthyy = 0;
					weightyy = 0;

					DeleteObject(hBrush);
					DeleteObject(hBrushIshod);
					DeleteObject(hBrushKusok);
					DeleteObject(hBrushFrame);
					DeleteObject(hPen);
					DeleteObject(hFont);

					DeleteObject(hDC);
					EndPaint(hWnd, &ps);

					return 0;
				}
			}
		}

		// Шестой кусок

		if (countPiece > 5)  // в следующем куске 6
		{
			//	f2 = 1; // Обязательно поменять!!
				//Этот код нужен для того, чтобы значение lenghtb и weightb присваивалось только один раз 
			if (lengthf == 0 & weightf == 0)
			{
				lengthf = len1 + propil; // len1 и len2 взяты из полей диалогового окна
				weightf = len2 + propil;
				squar -= squarPiece; // Вычитаем площадь куска из исходника
			}

			int	countBX = 0;
			int countBY = 0;
			int coX{};
			int flagg = 0;
			int fflagg = 0;
			int userReplyPiece;
			int countwarring{ 0 };
			int countwarring2{ 0 };

			for (int coY = 0; coY < (widthIshodnic)& flag1 == 0; coY+=3, countBY-=3)
			{
				if (countwarring2 > 10000000)
				{
					SendMessage(hWnd, WM_DESTROY, 0, 0);
					return 0;
				}
				++countwarring2;

			    for (int coX = 0; coX < (lengthIshodnic - lengthf) & flag1 == 0; coX+=3, countBX+=3) //!!
				{
					if (countwarring > 10000000)
					{
						SendMessage(hWnd, WM_DESTROY, 0, 0);
						return 0;
					}
					++countwarring;

					f.left = left + countBX;	//отступ левого верхнего угла по оси X
					f.top = top1 + countBY;  //отступ левого верхнего угла по оси Y: +pos.x это для перерисовки прямоугольника для полосы прокрутки
					f.right = f.left + lengthf; // длина по оси X с учетом a.left
					f.bottom = f.top - weightf; // длина по оси Y с учетом a.top

					if (!(RectInRegion(hRgnRam1, &f)))
					{
						flag1 = 1;
						fflagg = 1;
					}
				}

				countBX = 0;
				coX = 0;
			}
			flag1 = 0;

			if (fflagg)
			{

				hRgnf = CreateRectRgnIndirect(&f);
				CombineRgn(hRgnRam1, hRgnRam1, hRgnf, RGN_OR);
				FillRect(hDC, &f, hBrushKusok);
				FrameRgn(hDC, hRgnf, hBrushFrame , 3, 3);
				
				DrawText(hDC, "6", -1, &f, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
				DrawText(hDC, IntToStr(lengthf - propil), -1, &f, DT_SINGLELINE | DT_LEFT | DT_CENTER);
				DrawText(hDC, IntToStr(weightf - propil), -1, &f, DT_SINGLELINE | DT_LEFT | DT_VCENTER);
				SetWindowText(hStat, DoubleToStr(squar, 2));//Выводим площадь исходника в статическое поле

			}
			else
			{
				{
					MessageBox(hWnd, "Недопустимые размеры",
						"", 0);
					lengthf = 0;
					weightf = 0;
				countPiece=5;
				squar = 0;
					DeleteObject(hRgnRam1);
					DeleteObject(hRgnRam2);
					DeleteObject(hRgnRam3);
					DeleteObject(hRgnRam4);
					DeleteObject(hRgna);
					DeleteObject(hRgnb);
					DeleteObject(hRgnc);
					DeleteObject(hRgnd);
					DeleteObject(hRgne);
					DeleteObject(hRgnf);
					DeleteObject(hRgng);
					DeleteObject(hRgnh);
					DeleteObject(hRgni);
					DeleteObject(hRgnj);
					DeleteObject(hRgnk);
					DeleteObject(hRgnl);
					DeleteObject(hRgnm);
					DeleteObject(hRgnn);
					DeleteObject(hRgno);
					DeleteObject(hRgnp);
					DeleteObject(hRgnq);
					DeleteObject(hRgnrr);
					DeleteObject(hRgns);
					DeleteObject(hRgnt);
					DeleteObject(hRgnu);
					DeleteObject(hRgnv);
					DeleteObject(hRgnw);
					DeleteObject(hRgnx);
					DeleteObject(hRgny);
					DeleteObject(hRgnz);
					DeleteObject(hRgnxx);
					DeleteObject(hRgnww);
					DeleteObject(hRgnee);
					DeleteObject(hRgnyy);


					lengthg = 0;
					weightg = 0;
					lengthh = 0;
					weighth = 0;
					lengthi = 0;
					weighti = 0;
					lengthj = 0;
					weightj = 0;
					lengthk = 0;
					weightk = 0;
					lengthl = 0;
					weightl = 0;
					lengthm = 0;
					weightm = 0;
					lengthn = 0;
					weightn = 0;
					lengtho = 0;
					weighto = 0;
					lengthp = 0;
					weightp = 0;
					lengthq = 0;
					weightq = 0;
					lengthrr = 0;
					weightrr = 0;
					lengths = 0;
					weights = 0;
					lengtht = 0;
					weightt = 0;
					lengthu = 0;
					weightu = 0;
					lengthv = 0;
					weightv = 0;
					lengthw = 0;
					weightw = 0;
					lengthx = 0;
					weightx = 0;
					lengthy = 0;
					weighty = 0;
					lengthz = 0;
					weightz = 0;
					lengthxx = 0;
					weightxx = 0;
					lengthww = 0;
					weightww = 0;
					lengthee = 0;
					weightee = 0;
					lengthyy = 0;
					weightyy = 0;

					DeleteObject(hBrush);
					DeleteObject(hBrushIshod);
					DeleteObject(hBrushKusok);
					DeleteObject(hBrushFrame);
					DeleteObject(hPen);
					DeleteObject(hFont);
					DeleteObject(hDC);
					EndPaint(hWnd, &ps);

					return 0;
				}
			}
		}
		// Седьмой кусок

		if (countPiece > 6)  // в следующем куске 7
		{
			
			if (lengthg == 0 & weightg == 0)
			{
				lengthg = len1 + propil; // len1 и len2 взяты из полей диалогового окна
				weightg = len2 + propil;
				squar -= squarPiece; // Вычитаем площадь куска из исходника
			}

			int	countBX = 0;
			int countBY = 0;
			int coX{};
			int flagg = 0;
			int fflagg = 0;
			int userReplyPiece;
			int countwarring{ 0 };
			int countwarring2{ 0 };

			for (int coY = 0; coY < (widthIshodnic)& flag1 == 0; coY+=3, countBY-=3)
			{
				if (countwarring2 > 10000000)
				{
					SendMessage(hWnd, WM_DESTROY, 0, 0);
		
				}
				++countwarring2;

				
				for (int coX = 0; coX < (lengthIshodnic - lengthg) & flag1 == 0; coX+=3, countBX+=3)
				{
					if (countwarring > 10000000)
					{
						SendMessage(hWnd, WM_DESTROY, 0, 0);
		//				return 0;
					}
					++countwarring;

					g.left = left + countBX;	//отступ левого верхнего угла по оси X
					g.top = top1 + countBY;  //отступ левого верхнего угла по оси Y: +pos.x это для перерисовки прямоугольника для полосы прокрутки
					g.right = g.left + lengthg; // длина по оси X с учетом a.left
					g.bottom = g.top - weightg; // длина по оси Y с учетом a.top

					if (!(RectInRegion(hRgnRam1, &g)))
					{
						flag1 = 1;
						fflagg = 1;
					}
				}

				countBX = 0;
				coX = 0;
			}
			flag1 = 0;

			if (fflagg)
			{

				hRgng = CreateRectRgnIndirect(&g);
				CombineRgn(hRgnRam1, hRgnRam1, hRgng, RGN_OR);
				FillRect(hDC, &g, hBrushKusok);
				FrameRgn(hDC, hRgng, hBrushFrame , 3, 3);
				
				DrawText(hDC, "7", -1, &g, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
				DrawText(hDC, IntToStr(lengthg - propil), -1, &g, DT_SINGLELINE | DT_LEFT | DT_CENTER);
				DrawText(hDC, IntToStr(weightg - propil), -1, &g, DT_SINGLELINE | DT_LEFT | DT_VCENTER);
				SetWindowText(hStat, DoubleToStr(squar, 2));//Выводим площадь исходника в статическое поле

			
			}
			else
			{
				{
					MessageBox(hWnd, "Недопустимые размеры",
						"", 0);
					lengthg = 0;
					weightg = 0;
				countPiece=6;
				
				squar = 0;
				DeleteObject(hRgnRam1);
				DeleteObject(hRgnRam2);
				DeleteObject(hRgnRam3);
				DeleteObject(hRgnRam4);
				DeleteObject(hRgna);
				DeleteObject(hRgnb);
				DeleteObject(hRgnc);
				DeleteObject(hRgnd);
				DeleteObject(hRgne);
				DeleteObject(hRgnf);
				DeleteObject(hRgng);
				DeleteObject(hRgnh);
				DeleteObject(hRgni);
				DeleteObject(hRgnj);
				DeleteObject(hRgnk);
				DeleteObject(hRgnl);
				DeleteObject(hRgnm);
				DeleteObject(hRgnn);
				DeleteObject(hRgno);
				DeleteObject(hRgnp);
				DeleteObject(hRgnq);
				DeleteObject(hRgnrr);
				DeleteObject(hRgns);
				DeleteObject(hRgnt);
				DeleteObject(hRgnu);
				DeleteObject(hRgnv);
				DeleteObject(hRgnw);
				DeleteObject(hRgnx);
				DeleteObject(hRgny);
				DeleteObject(hRgnz);
				DeleteObject(hRgnxx);
				DeleteObject(hRgnww);
				DeleteObject(hRgnee);
				DeleteObject(hRgnyy);


				
				lengthh = 0;
				weighth = 0;
				lengthi = 0;
				weighti = 0;
				lengthj = 0;
				weightj = 0;
				lengthk = 0;
				weightk = 0;
				lengthl = 0;
				weightl = 0;
				lengthm = 0;
				weightm = 0;
				lengthn = 0;
				weightn = 0;
				lengtho = 0;
				weighto = 0;
				lengthp = 0;
				weightp = 0;
				lengthq = 0;
				weightq = 0;
				lengthrr = 0;
				weightrr = 0;
				lengths = 0;
				weights = 0;
				lengtht = 0;
				weightt = 0;
				lengthu = 0;
				weightu = 0;
				lengthv = 0;
				weightv = 0;
				lengthw = 0;
				weightw = 0;
				lengthx = 0;
				weightx = 0;
				lengthy = 0;
				weighty = 0;
				lengthz = 0;
				weightz = 0;
				lengthxx = 0;
				weightxx = 0;
				lengthww = 0;
				weightww = 0;
				lengthee = 0;
				weightee = 0;
				lengthyy = 0;
				weightyy = 0;

				DeleteObject(hBrush);
				DeleteObject(hBrushIshod);
				DeleteObject(hBrushKusok);
				DeleteObject(hBrushFrame);
				DeleteObject(hPen);
				DeleteObject(hFont);
				DeleteObject(hDC);
				EndPaint(hWnd, &ps);

				return 0;
				}
			}
		}
		// Восьмой кусок

		if (countPiece > 7)  // в следующем куске 8
		{
			
			if (lengthh == 0 & weighth == 0)
			{
				lengthh = len1 + propil; // len1 и len2 взяты из полей диалогового окна
				weighth = len2 + propil;
				squar -= squarPiece; // Вычитаем площадь куска из исходника
			}

			int	countBX = 0;
			int countBY = 0;
			int coX{};
			int flagg = 0;
			int fflagg = 0;
			int userReplyPiece;
			int countwarring{ 0 };
			int countwarring2{ 0 };

			
			for (int coY = 0; coY < (widthIshodnic)& flag1 == 0; coY+=3, countBY-=3)
			{
				if (countwarring2 > 10000000)
				{
					SendMessage(hWnd, WM_DESTROY, 0, 0);
			
				}
				++countwarring2;

			
				for (int coX = 0; coX < (lengthIshodnic - lengthh) & flag1 == 0; coX+=3, countBX+=3)
				{
					if (countwarring > 10000000)
					{
						SendMessage(hWnd, WM_DESTROY, 0, 0);
		
					}
					++countwarring;
					h.left = left + countBX;	//отступ левого верхнего угла по оси X
					h.top = top1 + countBY;  //отступ левого верхнего угла по оси Y: +pos.x это для перерисовки прямоугольника для полосы прокрутки
					h.right = h.left + lengthh; // длина по оси X с учетом a.left
					h.bottom = h.top - weighth; // длина по оси Y с учетом a.top

					if (!(RectInRegion(hRgnRam1, &h)))
					{
						flag1 = 1;
						fflagg = 1;
					}
				}

				countBX = 0;
				coX = 0;
			}
			flag1 = 0;

			if (fflagg)
			{

				hRgnh = CreateRectRgnIndirect(&h);
				CombineRgn(hRgnRam1, hRgnRam1, hRgnh, RGN_OR);
				FillRect(hDC, &h, hBrushKusok);
				FrameRgn(hDC, hRgnh, hBrushFrame , 3, 3);
				
				DrawText(hDC, "8", -1, &h, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
				DrawText(hDC, IntToStr(lengthh - propil), -1, &h, DT_SINGLELINE | DT_LEFT | DT_CENTER);
				DrawText(hDC, IntToStr(weighth - propil), -1, &h, DT_SINGLELINE | DT_LEFT | DT_VCENTER);
				SetWindowText(hStat, DoubleToStr(squar, 2));//Выводим площадь исходника в статическое поле

				
			}
			else
			{
				{
					MessageBox(hWnd, "Недопустимые размеры",
						"", 0);
					lengthh = 0;
					weighth = 0;
				countPiece=7;
					
				squar = 0;
					
					DeleteObject(hRgnRam1);
					DeleteObject(hRgnRam2);
					DeleteObject(hRgnRam3);
					DeleteObject(hRgnRam4);
					DeleteObject(hRgna);
					DeleteObject(hRgnb);
					DeleteObject(hRgnc);
					DeleteObject(hRgnd);
					DeleteObject(hRgne);
					DeleteObject(hRgnf);
					DeleteObject(hRgng);
					DeleteObject(hRgnh);
					DeleteObject(hRgni);
					DeleteObject(hRgnj);
					DeleteObject(hRgnk);
					DeleteObject(hRgnl);
					DeleteObject(hRgnm);
					DeleteObject(hRgnn);
					DeleteObject(hRgno);
					DeleteObject(hRgnp);
					DeleteObject(hRgnq);
					DeleteObject(hRgnrr);
					DeleteObject(hRgns);
					DeleteObject(hRgnt);
					DeleteObject(hRgnu);
					DeleteObject(hRgnv);
					DeleteObject(hRgnw);
					DeleteObject(hRgnx);
					DeleteObject(hRgny);
					DeleteObject(hRgnz);
					DeleteObject(hRgnxx);
					DeleteObject(hRgnww);
					DeleteObject(hRgnee);
					DeleteObject(hRgnyy);


					
					lengthi = 0;
					weighti = 0;
					lengthj = 0;
					weightj = 0;
					lengthk = 0;
					weightk = 0;
					lengthl = 0;
					weightl = 0;
					lengthm = 0;
					weightm = 0;
					lengthn = 0;
					weightn = 0;
					lengtho = 0;
					weighto = 0;
					lengthp = 0;
					weightp = 0;
					lengthq = 0;
					weightq = 0;
					lengthrr = 0;
					weightrr = 0;
					lengths = 0;
					weights = 0;
					lengtht = 0;
					weightt = 0;
					lengthu = 0;
					weightu = 0;
					lengthv = 0;
					weightv = 0;
					lengthw = 0;
					weightw = 0;
					lengthx = 0;
					weightx = 0;
					lengthy = 0;
					weighty = 0;
					lengthz = 0;
					weightz = 0;
					lengthxx = 0;
					weightxx = 0;
					lengthww = 0;
					weightww = 0;
					lengthee = 0;
					weightee = 0;
					lengthyy = 0;
					weightyy = 0;

					DeleteObject(hBrush);
					DeleteObject(hBrushIshod);
					DeleteObject(hBrushKusok);
					DeleteObject(hBrushFrame);
					DeleteObject(hPen);
					DeleteObject(hFont);
					DeleteObject(hDC);
					EndPaint(hWnd, &ps);

					return 0;
				}
			}
		}
		//Девятый  кусок

		if (countPiece > 8)  // в следующем куске 9
		{
			
			if (lengthi == 0 & weighti == 0)
			{
				lengthi = len1 + propil; // len1 и len2 взяты из полей диалогового окна
				weighti = len2 + propil;
				squar -= squarPiece; // Вычитаем площадь куска из исходника
			}

			int	countBX = 0;
			int countBY = 0;
			int coX{};
			int flagg = 0;
			int fflagg = 0;
			int userReplyPiece;
			int countwarring{ 0 };
			int countwarring2{ 0 };

			for (int coY = 0; coY < (widthIshodnic)& flag1 == 0; coY+=3, countBY-=3)
			{
				if (countwarring2 > 10000000)
				{
					SendMessage(hWnd, WM_DESTROY, 0, 0);
			
				}
				++countwarring2;

				for (int coX = 0; coX < (lengthIshodnic - lengthi) & flag1 == 0; ++coX, ++countBX) //!!
				{
					if (countwarring > 10000000)
					{
						SendMessage(hWnd, WM_DESTROY, 0, 0);
		
					}
					++countwarring;
					i.left = left + countBX;	//отступ левого верхнего угла по оси X
					i.top = top1 + countBY;  //отступ левого верхнего угла по оси Y: +pos.x это для перерисовки прямоугольника для полосы прокрутки
					i.right = i.left + lengthi; // длина по оси X с учетом a.left
					i.bottom = i.top - weighti; // длина по оси Y с учетом a.top

					if (!(RectInRegion(hRgnRam1, &i)))
					{
						flag1 = 1;
						fflagg = 1;
					}
				}

				countBX = 0;
				coX = 0;
			}
			flag1 = 0;

			if (fflagg)
			{

				hRgni = CreateRectRgnIndirect(&i);
				CombineRgn(hRgnRam1, hRgnRam1, hRgni, RGN_OR);
				FillRect(hDC, &i, hBrushKusok);
				FrameRgn(hDC, hRgni, hBrushFrame , 3, 3);
				
				DrawText(hDC, "9", -1, &i, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
				DrawText(hDC, IntToStr(lengthi - propil), -1, &i, DT_SINGLELINE | DT_LEFT | DT_CENTER);
				DrawText(hDC, IntToStr(weighti - propil), -1, &i, DT_SINGLELINE | DT_LEFT | DT_VCENTER);
				SetWindowText(hStat, DoubleToStr(squar, 2));//Выводим площадь исходника в статическое поле

				
			}
			else
			{
				{
					MessageBox(hWnd, "Недопустимые размеры",
						"", 0);
					lengthi = 0;
					weighti = 0;
				countPiece=8;
				
				squar = 0;
				DeleteObject(hRgnRam1);
				DeleteObject(hRgnRam2);
				DeleteObject(hRgnRam3);
				DeleteObject(hRgnRam4);
				DeleteObject(hRgna);
				DeleteObject(hRgnb);
				DeleteObject(hRgnc);
				DeleteObject(hRgnd);
				DeleteObject(hRgne);
				DeleteObject(hRgnf);
				DeleteObject(hRgng);
				DeleteObject(hRgnh);
				DeleteObject(hRgni);
				DeleteObject(hRgnj);
				DeleteObject(hRgnk);
				DeleteObject(hRgnl);
				DeleteObject(hRgnm);
				DeleteObject(hRgnn);
				DeleteObject(hRgno);
				DeleteObject(hRgnp);
				DeleteObject(hRgnq);
				DeleteObject(hRgnrr);
				DeleteObject(hRgns);
				DeleteObject(hRgnt);
				DeleteObject(hRgnu);
				DeleteObject(hRgnv);
				DeleteObject(hRgnw);
				DeleteObject(hRgnx);
				DeleteObject(hRgny);
				DeleteObject(hRgnz);
				DeleteObject(hRgnxx);
				DeleteObject(hRgnww);
				DeleteObject(hRgnee);
				DeleteObject(hRgnyy);


		
				lengthj = 0;
				weightj = 0;
				lengthk = 0;
				weightk = 0;
				lengthl = 0;
				weightl = 0;
				lengthm = 0;
				weightm = 0;
				lengthn = 0;
				weightn = 0;
				lengtho = 0;
				weighto = 0;
				lengthp = 0;
				weightp = 0;
				lengthq = 0;
				weightq = 0;
				lengthrr = 0;
				weightrr = 0;
				lengths = 0;
				weights = 0;
				lengtht = 0;
				weightt = 0;
				lengthu = 0;
				weightu = 0;
				lengthv = 0;
				weightv = 0;
				lengthw = 0;
				weightw = 0;
				lengthx = 0;
				weightx = 0;
				lengthy = 0;
				weighty = 0;
				lengthz = 0;
				weightz = 0;
				lengthxx = 0;
				weightxx = 0;
				lengthww = 0;
				weightww = 0;
				lengthee = 0;
				weightee = 0;
				lengthyy = 0;
				weightyy = 0;

				DeleteObject(hBrush);
				DeleteObject(hBrushIshod);
				DeleteObject(hBrushKusok);
				DeleteObject(hBrushFrame);
				DeleteObject(hPen);
				DeleteObject(hFont);
				DeleteObject(hDC);
				EndPaint(hWnd, &ps);

				return 0;
				}
			}
		}
		//Десятый  кусок

		if (countPiece > 9)  // в следующем куске 10
		{
			
			if (lengthj == 0 & weightj == 0)
			{
				lengthj = len1 + propil; // len1 и len2 взяты из полей диалогового окна
				weightj = len2 + propil;
				squar -= squarPiece; // Вычитаем площадь куска из исходника
			}

			int	countBX = 0;
			int countBY = 0;
			int coX{};
			int flagg = 0;
			int fflagg = 0;
			int userReplyPiece;
			int countwarring{ 0 };
			int countwarring2{ 0 };

			
			for (int coY = 0; coY < (widthIshodnic)& flag1 == 0; coY+=3, countBY-=3)
			{
				if (countwarring2 > 10000000)
				{
					SendMessage(hWnd, WM_DESTROY, 0, 0);
		
				}
				++countwarring2;

				
				for (int coX = 0; coX < (lengthIshodnic - lengthj) & flag1 == 0; coX+=3, countBX+=3)
				{
					if (countwarring > 10000000)
					{
						SendMessage(hWnd, WM_DESTROY, 0, 0);
		
					}
					++countwarring;
					j.left = left + countBX;	//отступ левого верхнего угла по оси X
					j.top = top1 + countBY;  //отступ левого верхнего угла по оси Y: +pos.x это для перерисовки прямоугольника для полосы прокрутки
					j.right = j.left + lengthj; // длина по оси X с учетом a.left
					j.bottom = j.top - weightj; // длина по оси Y с учетом a.top

					if (!(RectInRegion(hRgnRam1, &j)))
					{
						flag1 = 1;
						fflagg = 1;
					}
				}

				countBX = 0;
				coX = 0;
			}
			flag1 = 0;

			if (fflagg)
			{

				hRgnj = CreateRectRgnIndirect(&j);
				CombineRgn(hRgnRam1, hRgnRam1, hRgnj, RGN_OR);
				FillRect(hDC, &j, hBrushKusok);
				FrameRgn(hDC, hRgnj, hBrushFrame , 3, 3);
				
				DrawText(hDC, "10", -1, &j, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
				DrawText(hDC, IntToStr(lengthj - propil), -1, &j, DT_SINGLELINE | DT_LEFT | DT_CENTER);
				DrawText(hDC, IntToStr(weightj - propil), -1, &j, DT_SINGLELINE | DT_LEFT | DT_VCENTER);
				SetWindowText(hStat, DoubleToStr(squar, 2));//Выводим площадь исходника в статическое поле

				
			}
			else
			{
				{
					MessageBox(hWnd, "Недопустимые размеры",
						"", 0);
					lengthj = 0;
					weightj = 0;
				countPiece=9;
			
				squar = 0;
				DeleteObject(hRgnRam1);
				DeleteObject(hRgnRam2);
				DeleteObject(hRgnRam3);
				DeleteObject(hRgnRam4);
				DeleteObject(hRgna);
				DeleteObject(hRgnb);
				DeleteObject(hRgnc);
				DeleteObject(hRgnd);
				DeleteObject(hRgne);
				DeleteObject(hRgnf);
				DeleteObject(hRgng);
				DeleteObject(hRgnh);
				DeleteObject(hRgni);
				DeleteObject(hRgnj);
				DeleteObject(hRgnk);
				DeleteObject(hRgnl);
				DeleteObject(hRgnm);
				DeleteObject(hRgnn);
				DeleteObject(hRgno);
				DeleteObject(hRgnp);
				DeleteObject(hRgnq);
				DeleteObject(hRgnrr);
				DeleteObject(hRgns);
				DeleteObject(hRgnt);
				DeleteObject(hRgnu);
				DeleteObject(hRgnv);
				DeleteObject(hRgnw);
				DeleteObject(hRgnx);
				DeleteObject(hRgny);
				DeleteObject(hRgnz);
				DeleteObject(hRgnxx);
				DeleteObject(hRgnww);
				DeleteObject(hRgnee);
				DeleteObject(hRgnyy);


			
				lengthk = 0;
				weightk = 0;
				lengthl = 0;
				weightl = 0;
				lengthm = 0;
				weightm = 0;
				lengthn = 0;
				weightn = 0;
				lengtho = 0;
				weighto = 0;
				lengthp = 0;
				weightp = 0;
				lengthq = 0;
				weightq = 0;
				lengthrr = 0;
				weightrr = 0;
				lengths = 0;
				weights = 0;
				lengtht = 0;
				weightt = 0;
				lengthu = 0;
				weightu = 0;
				lengthv = 0;
				weightv = 0;
				lengthw = 0;
				weightw = 0;
				lengthx = 0;
				weightx = 0;
				lengthy = 0;
				weighty = 0;
				lengthz = 0;
				weightz = 0;
				lengthxx = 0;
				weightxx = 0;
				lengthww = 0;
				weightww = 0;
				lengthee = 0;
				weightee = 0;
				lengthyy = 0;
				weightyy = 0;

				DeleteObject(hBrush);
				DeleteObject(hBrushIshod);
				DeleteObject(hBrushKusok);
				DeleteObject(hBrushFrame);
				DeleteObject(hPen);
				DeleteObject(hFont);
				DeleteObject(hDC);
				EndPaint(hWnd, &ps);

				return 0;
				}
			}
		}
		//Одинадцатый  кусок

		if (countPiece > 10)  // в следующем куске 11
		{
		
			if (lengthk == 0 & weightk == 0)
			{
				lengthk = len1 + propil; // len1 и len2 взяты из полей диалогового окна
				weightk = len2 + propil;
				squar -= squarPiece; // Вычитаем площадь куска из исходника
			}

			int	countBX = 0;
			int countBY = 0;
			int coX{};
			int flagg = 0;
			int fflagg = 0;
			int userReplyPiece;
			int countwarring{ 0 };
			int countwarring2{ 0 };

			
			for (int coY = 0; coY < (widthIshodnic)& flag1 == 0; coY+=3, countBY-=3)
			{
				if (countwarring2 > 10000000)
				{
					SendMessage(hWnd, WM_DESTROY, 0, 0);
		//			return 0;
				}
				++countwarring2;

				
				for (int coX = 0; coX < (lengthIshodnic - lengthk) & flag1 == 0; coX+=3, countBX+=3) //!!
				{
					if (countwarring > 10000000)
					{
						SendMessage(hWnd, WM_DESTROY, 0, 0);
	
					}
					++countwarring;
					k.left = left + countBX;	//отступ левого верхнего угла по оси X
					k.top = top1 + countBY;  //отступ левого верхнего угла по оси Y: +pos.x это для перерисовки прямоугольника для полосы прокрутки
					k.right = k.left + lengthk; // длина по оси X с учетом a.left
					k.bottom = k.top - weightk; // длина по оси Y с учетом a.top

					if (!(RectInRegion(hRgnRam1, &k)))
					{
						flag1 = 1;
						fflagg = 1;
					}
				}

				countBX = 0;
				coX = 0;
			}
			flag1 = 0;

			if (fflagg)
			{

				hRgnk = CreateRectRgnIndirect(&k);
				CombineRgn(hRgnRam1, hRgnRam1, hRgnk, RGN_OR);
				FillRect(hDC, &k, hBrushKusok);
				FrameRgn(hDC, hRgnk, hBrushFrame , 3, 3);
				
				DrawText(hDC, "11", -1, &k, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
				DrawText(hDC, IntToStr(lengthk - propil), -1, &k, DT_SINGLELINE | DT_LEFT | DT_CENTER);
				DrawText(hDC, IntToStr(weightk - propil), -1, &k, DT_SINGLELINE | DT_LEFT | DT_VCENTER);
				SetWindowText(hStat, DoubleToStr(squar, 2));//Выводим площадь исходника в статическое поле

				
			}
			else
			{
				{
					MessageBox(hWnd, "Недопустимые размеры",
						"", 0);
					lengthk = 0;
					weightk = 0;
				countPiece=10;
				
				squar = 0;
					DeleteObject(hRgnRam1);
					DeleteObject(hRgnRam2);
					DeleteObject(hRgnRam3);
					DeleteObject(hRgnRam4);
					DeleteObject(hRgna);
					DeleteObject(hRgnb);
					DeleteObject(hRgnc);
					DeleteObject(hRgnd);
					DeleteObject(hRgne);
					DeleteObject(hRgnf);
					DeleteObject(hRgng);
					DeleteObject(hRgnh);
					DeleteObject(hRgni);
					DeleteObject(hRgnj);
					DeleteObject(hRgnk);
					DeleteObject(hRgnl);
					DeleteObject(hRgnm);
					DeleteObject(hRgnn);
					DeleteObject(hRgno);
					DeleteObject(hRgnp);
					DeleteObject(hRgnq);
					DeleteObject(hRgnrr);
					DeleteObject(hRgns);
					DeleteObject(hRgnt);
					DeleteObject(hRgnu);
					DeleteObject(hRgnv);
					DeleteObject(hRgnw);
					DeleteObject(hRgnx);
					DeleteObject(hRgny);
					DeleteObject(hRgnz);
					DeleteObject(hRgnxx);
					DeleteObject(hRgnww);
					DeleteObject(hRgnee);
					DeleteObject(hRgnyy);


					
					lengthl = 0;
					weightl = 0;
					lengthm = 0;
					weightm = 0;
					lengthn = 0;
					weightn = 0;
					lengtho = 0;
					weighto = 0;
					lengthp = 0;
					weightp = 0;
					lengthq = 0;
					weightq = 0;
					lengthrr = 0;
					weightrr = 0;
					lengths = 0;
					weights = 0;
					lengtht = 0;
					weightt = 0;
					lengthu = 0;
					weightu = 0;
					lengthv = 0;
					weightv = 0;
					lengthw = 0;
					weightw = 0;
					lengthx = 0;
					weightx = 0;
					lengthy = 0;
					weighty = 0;
					lengthz = 0;
					weightz = 0;
					lengthxx = 0;
					weightxx = 0;
					lengthww = 0;
					weightww = 0;
					lengthee = 0;
					weightee = 0;
					lengthyy = 0;
					weightyy = 0;

					DeleteObject(hBrush);
					DeleteObject(hBrushIshod);
					DeleteObject(hBrushKusok);
					DeleteObject(hBrushFrame);
					DeleteObject(hPen);
					DeleteObject(hFont);
					DeleteObject(hDC);
					EndPaint(hWnd, &ps);

					return 0;
				}
			}
		}
		//Двенадцатый  кусок

		if (countPiece > 11)  // в следующем куске 12
		{
			
			if (lengthl == 0 & weightl == 0)
			{
				lengthl = len1 + propil; // len1 и len2 взяты из полей диалогового окна
				weightl = len2 + propil;
				squar -= squarPiece; // Вычитаем площадь куска из исходника
			}

			int	countBX = 0;
			int countBY = 0;
			int coX{};
			int flagg = 0;
			int fflagg = 0;
			int userReplyPiece;
			int countwarring{ 0 };
			int countwarring2{ 0 };

		
			for (int coY = 0; coY < (widthIshodnic)& flag1 == 0; coY+=3, countBY-=3)
			{
				if (countwarring2 > 10000000)
				{
					SendMessage(hWnd, WM_DESTROY, 0, 0);
		
				}
				++countwarring2;

			
				for (int coX = 0; coX < (lengthIshodnic - lengthl) & flag1 == 0; coX+=3, countBX+=3)
				{
					if (countwarring > 10000000)
					{
						SendMessage(hWnd, WM_DESTROY, 0, 0);
	
					}
					++countwarring;
					l.left = left + countBX;	//отступ левого верхнего угла по оси X
					l.top = top1 + countBY;  //отступ левого верхнего угла по оси Y: +pos.x это для перерисовки прямоугольника для полосы прокрутки
					l.right = l.left + lengthl; // длина по оси X с учетом a.left
					l.bottom = l.top - weightl; // длина по оси Y с учетом a.top

					if (!(RectInRegion(hRgnRam1, &l)))
					{
						flag1 = 1;
						fflagg = 1;
					}
				}

				countBX = 0;
				coX = 0;
			}
			flag1 = 0;

			if (fflagg)
			{

				hRgnl = CreateRectRgnIndirect(&l);
				CombineRgn(hRgnRam1, hRgnRam1, hRgnl, RGN_OR);
				FillRect(hDC, &l, hBrushKusok);
				FrameRgn(hDC, hRgnl, hBrushFrame, 3, 3);
				
				DrawText(hDC, "12", -1, &l, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
				DrawText(hDC, IntToStr(lengthl - propil), -1, &l, DT_SINGLELINE | DT_LEFT | DT_CENTER);
				DrawText(hDC, IntToStr(weightl - propil), -1, &l, DT_SINGLELINE | DT_LEFT | DT_VCENTER);
				SetWindowText(hStat, DoubleToStr(squar, 2));//Выводим площадь исходника в статическое поле

			
			}
			else
			{
				{
					MessageBox(hWnd, "Недопустимые размеры",
						"", 0);
					lengthl = 0;
					weightl = 0;
				countPiece=11;
					
				squar = 0;
					
					DeleteObject(hRgnRam1);
					DeleteObject(hRgnRam2);
					DeleteObject(hRgnRam3);
					DeleteObject(hRgnRam4);
					DeleteObject(hRgna);
					DeleteObject(hRgnb);
					DeleteObject(hRgnc);
					DeleteObject(hRgnd);
					DeleteObject(hRgne);
					DeleteObject(hRgnf);
					DeleteObject(hRgng);
					DeleteObject(hRgnh);
					DeleteObject(hRgni);
					DeleteObject(hRgnj);
					DeleteObject(hRgnk);
					DeleteObject(hRgnl);
					DeleteObject(hRgnm);
					DeleteObject(hRgnn);
					DeleteObject(hRgno);
					DeleteObject(hRgnp);
					DeleteObject(hRgnq);
					DeleteObject(hRgnrr);
					DeleteObject(hRgns);
					DeleteObject(hRgnt);
					DeleteObject(hRgnu);
					DeleteObject(hRgnv);
					DeleteObject(hRgnw);
					DeleteObject(hRgnx);
					DeleteObject(hRgny);
					DeleteObject(hRgnz);
					DeleteObject(hRgnxx);
					DeleteObject(hRgnww);
					DeleteObject(hRgnee);
					DeleteObject(hRgnyy);


				
					lengthm = 0;
					weightm = 0;
					lengthn = 0;
					weightn = 0;
					lengtho = 0;
					weighto = 0;
					lengthp = 0;
					weightp = 0;
					lengthq = 0;
					weightq = 0;
					lengthrr = 0;
					weightrr = 0;
					lengths = 0;
					weights = 0;
					lengtht = 0;
					weightt = 0;
					lengthu = 0;
					weightu = 0;
					lengthv = 0;
					weightv = 0;
					lengthw = 0;
					weightw = 0;
					lengthx = 0;
					weightx = 0;
					lengthy = 0;
					weighty = 0;
					lengthz = 0;
					weightz = 0;
					lengthxx = 0;
					weightxx = 0;
					lengthww = 0;
					weightww = 0;
					lengthee = 0;
					weightee = 0;
					lengthyy = 0;
					weightyy = 0;

					DeleteObject(hBrush);
					DeleteObject(hBrushIshod);
					DeleteObject(hBrushKusok);
					DeleteObject(hBrushFrame);
					DeleteObject(hPen);
					DeleteObject(hFont);
					DeleteObject(hDC);
					EndPaint(hWnd, &ps);

					return 0;
				}
			}
		}
		//Тринадцатый  кусок

		if (countPiece > 12)  // в следующем куске 13
		{
		
			if (lengthm == 0 & weightm == 0)
			{
				lengthm = len1 + propil; // len1 и len2 взяты из полей диалогового окна
				weightm = len2 + propil;
				squar -= squarPiece; // Вычитаем площадь куска из исходника
			}

			int	countBX = 0;
			int countBY = 0;
			int coX{};
			int flagg = 0;
			int fflagg = 0;
			int userReplyPiece;
			int countwarring{ 0 };
			int countwarring2{ 0 };

			
			for (int coY = 0; coY < (widthIshodnic)& flag1 == 0; coY+=3, countBY-=3)
			{
				if (countwarring2 > 10000000)
				{
					SendMessage(hWnd, WM_DESTROY, 0, 0);
		
				}
				++countwarring2;

				
				for (int coX = 0; coX < (lengthIshodnic - lengthm) & flag1 == 0; coX+=3, countBX+=3) //!!
				{
					if (countwarring > 10000000)
					{
						SendMessage(hWnd, WM_DESTROY, 0, 0);
		
					}
					++countwarring;
					m.left = left + countBX;	//отступ левого верхнего угла по оси X
					m.top = top1 + countBY;  //отступ левого верхнего угла по оси Y: +pos.x это для перерисовки прямоугольника для полосы прокрутки
					m.right = m.left + lengthm; // длина по оси X с учетом a.left
					m.bottom = m.top - weightm; // длина по оси Y с учетом a.top

					if (!(RectInRegion(hRgnRam1, &m)))
					{
						flag1 = 1;
						fflagg = 1;
					}
				}

				countBX = 0;
				coX = 0;
			}
			flag1 = 0;

			if (fflagg)
			{

				hRgnm = CreateRectRgnIndirect(&m);
				CombineRgn(hRgnRam1, hRgnRam1, hRgnm, RGN_OR);
				FillRect(hDC, &m, hBrushKusok);
				FrameRgn(hDC, hRgnm, hBrushFrame , 3, 3);
				
				DrawText(hDC, "13", -1, &m, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
				DrawText(hDC, IntToStr(lengthm - propil), -1, &m, DT_SINGLELINE | DT_LEFT | DT_CENTER);
				DrawText(hDC, IntToStr(weightm - propil), -1, &m, DT_SINGLELINE | DT_LEFT | DT_VCENTER);
				SetWindowText(hStat, DoubleToStr(squar, 2));//Выводим площадь исходника в статическое поле

				
			}
			else
			{
				{
					MessageBox(hWnd, "Недопустимые размеры",
						"", 0);
					lengthm = 0;
					weightm = 0;
				countPiece=12;
					
				squar = 0;
					DeleteObject(hRgnRam1);
					DeleteObject(hRgnRam2);
					DeleteObject(hRgnRam3);
					DeleteObject(hRgnRam4);
					DeleteObject(hRgna);
					DeleteObject(hRgnb);
					DeleteObject(hRgnc);
					DeleteObject(hRgnd);
					DeleteObject(hRgne);
					DeleteObject(hRgnf);
					DeleteObject(hRgng);
					DeleteObject(hRgnh);
					DeleteObject(hRgni);
					DeleteObject(hRgnj);
					DeleteObject(hRgnk);
					DeleteObject(hRgnl);
					DeleteObject(hRgnm);
					DeleteObject(hRgnn);
					DeleteObject(hRgno);
					DeleteObject(hRgnp);
					DeleteObject(hRgnq);
					DeleteObject(hRgnrr);
					DeleteObject(hRgns);
					DeleteObject(hRgnt);
					DeleteObject(hRgnu);
					DeleteObject(hRgnv);
					DeleteObject(hRgnw);
					DeleteObject(hRgnx);
					DeleteObject(hRgny);
					DeleteObject(hRgnz);
					DeleteObject(hRgnxx);
					DeleteObject(hRgnww);
					DeleteObject(hRgnee);
					DeleteObject(hRgnyy);


			
					lengthn = 0;
					weightn = 0;
					lengtho = 0;
					weighto = 0;
					lengthp = 0;
					weightp = 0;
					lengthq = 0;
					weightq = 0;
					lengthrr = 0;
					weightrr = 0;
					lengths = 0;
					weights = 0;
					lengtht = 0;
					weightt = 0;
					lengthu = 0;
					weightu = 0;
					lengthv = 0;
					weightv = 0;
					lengthw = 0;
					weightw = 0;
					lengthx = 0;
					weightx = 0;
					lengthy = 0;
					weighty = 0;
					lengthz = 0;
					weightz = 0;
					lengthxx = 0;
					weightxx = 0;
					lengthww = 0;
					weightww = 0;
					lengthee = 0;
					weightee = 0;
					lengthyy = 0;
					weightyy = 0;

					DeleteObject(hBrush);
					DeleteObject(hBrushIshod);
					DeleteObject(hBrushKusok);
					DeleteObject(hBrushFrame);
					DeleteObject(hPen);
					DeleteObject(hFont);
					DeleteObject(hDC);
					EndPaint(hWnd, &ps);

					return 0;
				}
			}
		}
		//Четырнадцатый  кусок

		if (countPiece > 13)  // в следующем куске 14
		{
			
			if (lengthn == 0 & weightn == 0)
			{
				lengthn = len1 + propil; // len1 и len2 взяты из полей диалогового окна
				weightn = len2 + propil;
				squar -= squarPiece; // Вычитаем площадь куска из исходника
			}

			int	countBX = 0;
			int countBY = 0;
			int coX{};
			int flagg = 0;
			int fflagg = 0;
			int userReplyPiece;
			int countwarring{ 0 };
			int countwarring2{ 0 };

			
			for (int coY = 0; coY < (widthIshodnic)& flag1 == 0; coY+=3, countBY-=3)
			{
				if (countwarring2 > 10000000)
				{
					SendMessage(hWnd, WM_DESTROY, 0, 0);
		
				}
				++countwarring2;

				
				for (int coX = 0; coX < (lengthIshodnic - lengthn) & flag1 == 0; coX+=3, countBX+=3) //!!
				{
					if (countwarring > 10000000)
					{
						SendMessage(hWnd, WM_DESTROY, 0, 0);
		
					}
					++countwarring;
					n.left = left + countBX;	//отступ левого верхнего угла по оси X
					n.top = top1 + countBY;  //отступ левого верхнего угла по оси Y: +pos.x это для перерисовки прямоугольника для полосы прокрутки
					n.right = n.left + lengthn; // длина по оси X с учетом a.left
					n.bottom = n.top - weightn; // длина по оси Y с учетом a.top

					if (!(RectInRegion(hRgnRam1, &n)))
					{
						flag1 = 1;
						fflagg = 1;
					}
				}

				countBX = 0;
				coX = 0;
			}
			flag1 = 0;

			if (fflagg)
			{

				hRgnn = CreateRectRgnIndirect(&n);
				CombineRgn(hRgnRam1, hRgnRam1, hRgnn, RGN_OR);
				FillRect(hDC, &n, hBrushKusok);
				FrameRgn(hDC, hRgnn, hBrushFrame , 3, 3);
				
				DrawText(hDC, "14", -1, &n, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
				DrawText(hDC, IntToStr(lengthn - propil), -1, &n, DT_SINGLELINE | DT_LEFT | DT_CENTER);
				DrawText(hDC, IntToStr(weightn - propil), -1, &n, DT_SINGLELINE | DT_LEFT | DT_VCENTER);
				SetWindowText(hStat, DoubleToStr(squar, 2));//Выводим площадь исходника в статическое поле

				
			}
			else
			{
				{
					MessageBox(hWnd, "Недопустимые размеры",
						"", 0);
					lengthn = 0;
					weightn = 0;
				countPiece=13;
					
				squar = 0;
					DeleteObject(hRgnRam1);
					DeleteObject(hRgnRam2);
					DeleteObject(hRgnRam3);
					DeleteObject(hRgnRam4);
					DeleteObject(hRgna);
					DeleteObject(hRgnb);
					DeleteObject(hRgnc);
					DeleteObject(hRgnd);
					DeleteObject(hRgne);
					DeleteObject(hRgnf);
					DeleteObject(hRgng);
					DeleteObject(hRgnh);
					DeleteObject(hRgni);
					DeleteObject(hRgnj);
					DeleteObject(hRgnk);
					DeleteObject(hRgnl);
					DeleteObject(hRgnm);
					DeleteObject(hRgnn);
					DeleteObject(hRgno);
					DeleteObject(hRgnp);
					DeleteObject(hRgnq);
					DeleteObject(hRgnrr);
					DeleteObject(hRgns);
					DeleteObject(hRgnt);
					DeleteObject(hRgnu);
					DeleteObject(hRgnv);
					DeleteObject(hRgnw);
					DeleteObject(hRgnx);
					DeleteObject(hRgny);
					DeleteObject(hRgnz);
					DeleteObject(hRgnxx);
					DeleteObject(hRgnww);
					DeleteObject(hRgnee);
					DeleteObject(hRgnyy);


					
					lengtho = 0;
					weighto = 0;
					lengthp = 0;
					weightp = 0;
					lengthq = 0;
					weightq = 0;
					lengthrr = 0;
					weightrr = 0;
					lengths = 0;
					weights = 0;
					lengtht = 0;
					weightt = 0;
					lengthu = 0;
					weightu = 0;
					lengthv = 0;
					weightv = 0;
					lengthw = 0;
					weightw = 0;
					lengthx = 0;
					weightx = 0;
					lengthy = 0;
					weighty = 0;
					lengthz = 0;
					weightz = 0;
					lengthxx = 0;
					weightxx = 0;
					lengthww = 0;
					weightww = 0;
					lengthee = 0;
					weightee = 0;
					lengthyy = 0;
					weightyy = 0;

					DeleteObject(hBrush);
					DeleteObject(hBrushIshod);
					DeleteObject(hBrushKusok);
					DeleteObject(hBrushFrame);
					DeleteObject(hPen);
					DeleteObject(hFont);
					DeleteObject(hDC);
					EndPaint(hWnd, &ps);

					return 0;
				}
			}
		}
		//Пятнадцатый  кусок

		if (countPiece > 14)  // в следующем куске 15
		{
		
			if (lengtho == 0 & weighto == 0)
			{
				lengtho = len1 + propil; // len1 и len2 взяты из полей диалогового окна
				weighto = len2 + propil;
				squar -= squarPiece; // Вычитаем площадь куска из исходника
			}

			int	countBX = 0;
			int countBY = 0;
			int coX{};
			int flagg = 0;
			int fflagg = 0;
			int userReplyPiece;
			int countwarring{ 0 };
			int countwarring2{ 0 };

			
			for (int coY = 0; coY < (widthIshodnic)& flag1 == 0; coY+=3, countBY-=3)
			{
				if (countwarring2 > 10000000)
				{
					SendMessage(hWnd, WM_DESTROY, 0, 0);
		
				}
				++countwarring2;

				
				for (int coX = 0; coX < (lengthIshodnic - lengtho) & flag1 == 0; coX+=3, countBX+=3) //!!
				{
					if (countwarring > 10000000)
					{
						SendMessage(hWnd, WM_DESTROY, 0, 0);
		
					}
					++countwarring;
					o.left = left + countBX;	//отступ левого верхнего угла по оси X
					o.top = top1 + countBY;  //отступ левого верхнего угла по оси Y: +pos.x это для перерисовки прямоугольника для полосы прокрутки
					o.right = o.left + lengtho; // длина по оси X с учетом a.left
					o.bottom = o.top - weighto; // длина по оси Y с учетом a.top

					if (!(RectInRegion(hRgnRam1, &o)))
					{
						flag1 = 1;
						fflagg = 1;
					}
				}

				countBX = 0;
				coX = 0;
			}
			flag1 = 0;

			if (fflagg)
			{

				hRgno = CreateRectRgnIndirect(&o);
				CombineRgn(hRgnRam1, hRgnRam1, hRgno, RGN_OR);
				FillRect(hDC, &o, hBrushKusok);
				FrameRgn(hDC, hRgno, hBrushFrame, 3, 3);
				
				DrawText(hDC, "15", -1, &o, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
				DrawText(hDC, IntToStr(lengtho - propil), -1, &o, DT_SINGLELINE | DT_LEFT | DT_CENTER);
				DrawText(hDC, IntToStr(weighto - propil), -1, &o, DT_SINGLELINE | DT_LEFT | DT_VCENTER);
				SetWindowText(hStat, DoubleToStr(squar, 2));//Выводим площадь исходника в статическое поле

				
			}
			else
			{
				{
					MessageBox(hWnd, "Недопустимые размеры",
						"", 0);
					lengtho = 0;
					weighto = 0;
					countPiece=14;
				
					squar = 0;
					DeleteObject(hRgnRam1);
					DeleteObject(hRgnRam2);
					DeleteObject(hRgnRam3);
					DeleteObject(hRgnRam4);
					DeleteObject(hRgna);
					DeleteObject(hRgnb);
					DeleteObject(hRgnc);
					DeleteObject(hRgnd);
					DeleteObject(hRgne);
					DeleteObject(hRgnf);
					DeleteObject(hRgng);
					DeleteObject(hRgnh);
					DeleteObject(hRgni);
					DeleteObject(hRgnj);
					DeleteObject(hRgnk);
					DeleteObject(hRgnl);
					DeleteObject(hRgnm);
					DeleteObject(hRgnn);
					DeleteObject(hRgno);
					DeleteObject(hRgnp);
					DeleteObject(hRgnq);
					DeleteObject(hRgnrr);
					DeleteObject(hRgns);
					DeleteObject(hRgnt);
					DeleteObject(hRgnu);
					DeleteObject(hRgnv);
					DeleteObject(hRgnw);
					DeleteObject(hRgnx);
					DeleteObject(hRgny);
					DeleteObject(hRgnz);
					DeleteObject(hRgnxx);
					DeleteObject(hRgnww);
					DeleteObject(hRgnee);
					DeleteObject(hRgnyy);


				
					lengthp = 0;
					weightp = 0;
					lengthq = 0;
					weightq = 0;
					lengthrr = 0;
					weightrr = 0;
					lengths = 0;
					weights = 0;
					lengtht = 0;
					weightt = 0;
					lengthu = 0;
					weightu = 0;
					lengthv = 0;
					weightv = 0;
					lengthw = 0;
					weightw = 0;
					lengthx = 0;
					weightx = 0;
					lengthy = 0;
					weighty = 0;
					lengthz = 0;
					weightz = 0;
					lengthxx = 0;
					weightxx = 0;
					lengthww = 0;
					weightww = 0;
					lengthee = 0;
					weightee = 0;
					lengthyy = 0;
					weightyy = 0;

					DeleteObject(hBrush);
					DeleteObject(hBrushIshod);
					DeleteObject(hBrushKusok);
					DeleteObject(hBrushFrame);
					DeleteObject(hPen);
					DeleteObject(hFont);
					DeleteObject(hDC);
					EndPaint(hWnd, &ps);

					return 0;
				}
			}
		}
		//Шестнадцатый  кусок

		if (countPiece > 15)  // в следующем куске 16
		{
		
			if (lengthp == 0 & weightp == 0)
			{
				lengthp = len1 + propil; // len1 и len2 взяты из полей диалогового окна
				weightp = len2 + propil;
				squar -= squarPiece; // Вычитаем площадь куска из исходника
			}

			int	countBX = 0;
			int countBY = 0;
			int coX{};
			int flagg = 0;
			int fflagg = 0;
			int userReplyPiece;
			int countwarring{ 0 };
			int countwarring2{ 0 };

			
			for (int coY = 0; coY < (widthIshodnic)& flag1 == 0; coY+=3, countBY-=3)
			{
				if (countwarring2 > 10000000)
				{
					SendMessage(hWnd, WM_DESTROY, 0, 0);
		
				}
				++countwarring2;

		
				for (int coX = 0; coX < (lengthIshodnic - lengthp) & flag1 == 0; coX+=3, countBX+=3) //!!
				{
					if (countwarring > 10000000)
					{
						SendMessage(hWnd, WM_DESTROY, 0, 0);
		
					}
					++countwarring;
					p.left = left + countBX;	//отступ левого верхнего угла по оси X
					p.top = top1 + countBY;  //отступ левого верхнего угла по оси Y: +pos.x это для перерисовки прямоугольника для полосы прокрутки
					p.right = p.left + lengthp; // длина по оси X с учетом a.left
					p.bottom = p.top - weightp; // длина по оси Y с учетом a.top

					if (!(RectInRegion(hRgnRam1, &p)))
					{
						flag1 = 1;
						fflagg = 1;
					}
				}

				countBX = 0;
				coX = 0;
			}
			flag1 = 0;

			if (fflagg)
			{

				hRgnp = CreateRectRgnIndirect(&p);
				CombineRgn(hRgnRam1, hRgnRam1, hRgnp, RGN_OR);
				FillRect(hDC, &p, hBrushKusok);
				FrameRgn(hDC, hRgnp, hBrushFrame , 3, 3);
				
				DrawText(hDC, "16", -1, &p, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
				DrawText(hDC, IntToStr(lengthp - propil), -1, &p, DT_SINGLELINE | DT_LEFT | DT_CENTER);
				DrawText(hDC, IntToStr(weightp - propil), -1, &p, DT_SINGLELINE | DT_LEFT | DT_VCENTER);
				SetWindowText(hStat, DoubleToStr(squar, 2));//Выводим площадь исходника в статическое поле

			
			}
			else
			{
				{
					MessageBox(hWnd, "Недопустимые размеры",
						"", 0);
					lengthp = 0;
					weightp = 0;
					countPiece=15;
					
					squar = 0;
					DeleteObject(hRgnRam1);
					DeleteObject(hRgnRam2);
					DeleteObject(hRgnRam3);
					DeleteObject(hRgnRam4);
					DeleteObject(hRgna);
					DeleteObject(hRgnb);
					DeleteObject(hRgnc);
					DeleteObject(hRgnd);
					DeleteObject(hRgne);
					DeleteObject(hRgnf);
					DeleteObject(hRgng);
					DeleteObject(hRgnh);
					DeleteObject(hRgni);
					DeleteObject(hRgnj);
					DeleteObject(hRgnk);
					DeleteObject(hRgnl);
					DeleteObject(hRgnm);
					DeleteObject(hRgnn);
					DeleteObject(hRgno);
					DeleteObject(hRgnp);
					DeleteObject(hRgnq);
					DeleteObject(hRgnrr);
					DeleteObject(hRgns);
					DeleteObject(hRgnt);
					DeleteObject(hRgnu);
					DeleteObject(hRgnv);
					DeleteObject(hRgnw);
					DeleteObject(hRgnx);
					DeleteObject(hRgny);
					DeleteObject(hRgnz);
					DeleteObject(hRgnxx);
					DeleteObject(hRgnww);
					DeleteObject(hRgnee);
					DeleteObject(hRgnyy);


				
					lengthq = 0;
					weightq = 0;
					lengthrr = 0;
					weightrr = 0;
					lengths = 0;
					weights = 0;
					lengtht = 0;
					weightt = 0;
					lengthu = 0;
					weightu = 0;
					lengthv = 0;
					weightv = 0;
					lengthw = 0;
					weightw = 0;
					lengthx = 0;
					weightx = 0;
					lengthy = 0;
					weighty = 0;
					lengthz = 0;
					weightz = 0;
					lengthxx = 0;
					weightxx = 0;
					lengthww = 0;
					weightww = 0;
					lengthee = 0;
					weightee = 0;
					lengthyy = 0;
					weightyy = 0;

					DeleteObject(hBrush);
					DeleteObject(hBrushIshod);
					DeleteObject(hBrushKusok);
					DeleteObject(hBrushFrame);
					DeleteObject(hPen);
					DeleteObject(hFont);
					DeleteObject(hDC);
					EndPaint(hWnd, &ps);

					return 0;
				}
			}
		}
		//Семнадцатый кусок

		if (countPiece > 16)  // в следующем куске 17
		{
		
			if (lengthq == 0 & weightq == 0)
			{
				lengthq = len1 + propil; // len1 и len2 взяты из полей диалогового окна
				weightq = len2 + propil;
				squar -= squarPiece; // Вычитаем площадь куска из исходника
			}

			int	countBX = 0;
			int countBY = 0;
			int coX{};
			int flagg = 0;
			int fflagg = 0;
			int userReplyPiece;
			int countwarring{ 0 };
			int countwarring2{ 0 };

			
			for (int coY = 0; coY < (widthIshodnic)& flag1 == 0; coY+=3, countBY-=3)
			{
				if (countwarring2 > 10000000)
				{
					SendMessage(hWnd, WM_DESTROY, 0, 0);
		
				}
				++countwarring2;

			
				for (int coX = 0; coX < (lengthIshodnic - lengthq) & flag1 == 0; coX+=3, countBX+=3) //!!
				{
					if (countwarring > 10000000)
					{
						SendMessage(hWnd, WM_DESTROY, 0, 0);
		//				return 0;
					}
					++countwarring;
					q.left = left + countBX;	//отступ левого верхнего угла по оси X
					q.top = top1 + countBY;  //отступ левого верхнего угла по оси Y: +pos.x это для перерисовки прямоугольника для полосы прокрутки
					q.right = q.left + lengthq; // длина по оси X с учетом a.left
					q.bottom = q.top - weightq; // длина по оси Y с учетом a.top

					if (!(RectInRegion(hRgnRam1, &q)))
					{
						flag1 = 1;
						fflagg = 1;
					}
				}

				countBX = 0;
				coX = 0;
			}
			flag1 = 0;

			if (fflagg)
			{

				hRgnq = CreateRectRgnIndirect(&q);
				CombineRgn(hRgnRam1, hRgnRam1, hRgnq, RGN_OR);
				FillRect(hDC, &q, hBrushKusok);
				FrameRgn(hDC, hRgnq, hBrushFrame , 3, 3);
				
				DrawText(hDC, "17", -1, &q, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
				DrawText(hDC, IntToStr(lengthq - propil), -1, &q, DT_SINGLELINE | DT_LEFT | DT_CENTER);
				DrawText(hDC, IntToStr(weightq - propil), -1, &q, DT_SINGLELINE | DT_LEFT | DT_VCENTER);
				SetWindowText(hStat, DoubleToStr(squar, 2));//Выводим площадь исходника в статическое поле

				
			}
			else
			{
				{
					MessageBox(hWnd, "Недопустимые размеры",
						"", 0);
					lengthq = 0;
					weightq = 0;
				countPiece=16;
				
				squar = 0;
					DeleteObject(hRgnRam1);
					DeleteObject(hRgnRam2);
					DeleteObject(hRgnRam3);
					DeleteObject(hRgnRam4);
					DeleteObject(hRgna);
					DeleteObject(hRgnb);
					DeleteObject(hRgnc);
					DeleteObject(hRgnd);
					DeleteObject(hRgne);
					DeleteObject(hRgnf);
					DeleteObject(hRgng);
					DeleteObject(hRgnh);
					DeleteObject(hRgni);
					DeleteObject(hRgnj);
					DeleteObject(hRgnk);
					DeleteObject(hRgnl);
					DeleteObject(hRgnm);
					DeleteObject(hRgnn);
					DeleteObject(hRgno);
					DeleteObject(hRgnp);
					DeleteObject(hRgnq);
					DeleteObject(hRgnrr);
					DeleteObject(hRgns);
					DeleteObject(hRgnt);
					DeleteObject(hRgnu);
					DeleteObject(hRgnv);
					DeleteObject(hRgnw);
					DeleteObject(hRgnx);
					DeleteObject(hRgny);
					DeleteObject(hRgnz);
					DeleteObject(hRgnxx);
					DeleteObject(hRgnww);
					DeleteObject(hRgnee);
					DeleteObject(hRgnyy);


				
					lengthrr = 0;
					weightrr = 0;
					lengths = 0;
					weights = 0;
					lengtht = 0;
					weightt = 0;
					lengthu = 0;
					weightu = 0;
					lengthv = 0;
					weightv = 0;
					lengthw = 0;
					weightw = 0;
					lengthx = 0;
					weightx = 0;
					lengthy = 0;
					weighty = 0;
					lengthz = 0;
					weightz = 0;
					lengthxx = 0;
					weightxx = 0;
					lengthww = 0;
					weightww = 0;
					lengthee = 0;
					weightee = 0;
					lengthyy = 0;
					weightyy = 0;

					DeleteObject(hBrush);
					DeleteObject(hBrushIshod);
					DeleteObject(hBrushKusok);
					DeleteObject(hBrushFrame);
					DeleteObject(hPen);
					DeleteObject(hFont);
					DeleteObject(hDC);
					EndPaint(hWnd, &ps);

					return 0;
				}
			}
		}
		//Восемнадцатый кусок

		if (countPiece > 17)  // в следующем куске 18
		{
		
			if (lengthrr == 0 & weightrr == 0)
			{
				lengthrr = len1 + propil; // len1 и len2 взяты из полей диалогового окна
				weightrr = len2 + propil;
				squar -= squarPiece; // Вычитаем площадь куска из исходника
			}

			int	countBX = 0;
			int countBY = 0;
			int coX{};
			int flagg = 0;
			int fflagg = 0;
			int userReplyPiece;
			int countwarring{ 0 };
			int countwarring2{ 0 };

			
			for (int coY = 0; coY < (widthIshodnic)& flag1 == 0; coY+=3, countBY-=3)
			{
				if (countwarring2 > 10000000)
				{
					SendMessage(hWnd, WM_DESTROY, 0, 0);
	
				}
				++countwarring2;

				
				for (int coX = 0; coX < (lengthIshodnic - lengthrr) & flag1 == 0; coX+=3, countBX+=3) //!!
				{
					if (countwarring > 10000000)
					{
						SendMessage(hWnd, WM_DESTROY, 0, 0);
		
					}
					++countwarring;

					rr.left = left + countBX;	//отступ левого верхнего угла по оси X
					rr.top = top1 + countBY;  //отступ левого верхнего угла по оси Y: +pos.x это для перерисовки прямоугольника для полосы прокрутки
					rr.right = rr.left + lengthrr; // длина по оси X с учетом a.left
					rr.bottom = rr.top - weightrr; // длина по оси Y с учетом a.top

					if (!(RectInRegion(hRgnRam1, &rr)))
					{
						flag1 = 1;
						fflagg = 1;
					}
				}

				countBX = 0;
				coX = 0;
			}
			flag1 = 0;

			if (fflagg)
			{

				hRgnrr = CreateRectRgnIndirect(&rr);
				CombineRgn(hRgnRam1, hRgnRam1, hRgnrr, RGN_OR);
				FillRect(hDC, &rr, hBrushKusok);
				FrameRgn(hDC, hRgnrr, hBrushFrame, 3, 3);
				
				DrawText(hDC, "18", -1, &rr, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
				DrawText(hDC, IntToStr(lengthrr - propil), -1, &rr, DT_SINGLELINE | DT_LEFT | DT_CENTER);
				DrawText(hDC, IntToStr(weightrr - propil), -1, &rr, DT_SINGLELINE | DT_LEFT | DT_VCENTER);
				SetWindowText(hStat, DoubleToStr(squar, 2));//Выводим площадь исходника в статическое поле

			
			}
			else
			{
				{
					MessageBox(hWnd, "Недопустимые размеры",
						"", 0);
					lengthrr = 0;
					weightrr = 0;
				countPiece=17;
				
				squar = 0;
					DeleteObject(hRgnRam1);
					DeleteObject(hRgnRam2);
					DeleteObject(hRgnRam3);
					DeleteObject(hRgnRam4);
					DeleteObject(hRgna);
					DeleteObject(hRgnb);
					DeleteObject(hRgnc);
					DeleteObject(hRgnd);
					DeleteObject(hRgne);
					DeleteObject(hRgnf);
					DeleteObject(hRgng);
					DeleteObject(hRgnh);
					DeleteObject(hRgni);
					DeleteObject(hRgnj);
					DeleteObject(hRgnk);
					DeleteObject(hRgnl);
					DeleteObject(hRgnm);
					DeleteObject(hRgnn);
					DeleteObject(hRgno);
					DeleteObject(hRgnp);
					DeleteObject(hRgnq);
					DeleteObject(hRgnrr);
					DeleteObject(hRgns);
					DeleteObject(hRgnt);
					DeleteObject(hRgnu);
					DeleteObject(hRgnv);
					DeleteObject(hRgnw);
					DeleteObject(hRgnx);
					DeleteObject(hRgny);
					DeleteObject(hRgnz);
					DeleteObject(hRgnxx);
					DeleteObject(hRgnww);
					DeleteObject(hRgnee);
					DeleteObject(hRgnyy);


			
					lengths = 0;
					weights = 0;
					lengtht = 0;
					weightt = 0;
					lengthu = 0;
					weightu = 0;
					lengthv = 0;
					weightv = 0;
					lengthw = 0;
					weightw = 0;
					lengthx = 0;
					weightx = 0;
					lengthy = 0;
					weighty = 0;
					lengthz = 0;
					weightz = 0;
					lengthxx = 0;
					weightxx = 0;
					lengthww = 0;
					weightww = 0;
					lengthee = 0;
					weightee = 0;
					lengthyy = 0;
					weightyy = 0;

					DeleteObject(hBrush);
					DeleteObject(hBrushIshod);
					DeleteObject(hBrushKusok);
					DeleteObject(hBrushFrame);
					DeleteObject(hPen);
					DeleteObject(hFont);
					DeleteObject(hDC);
					EndPaint(hWnd, &ps);

					return 0;
				}
			}
		}
		//Девятнадцатый кусок

		if (countPiece > 18)  // в следующем куске 19
		{
		
			if (lengths == 0 & weights == 0)
			{
				lengths = len1 + propil; // len1 и len2 взяты из полей диалогового окна
				weights = len2 + propil;
				squar -= squarPiece; // Вычитаем площадь куска из исходника
			}

			int	countBX = 0;
			int countBY = 0;
			int coX{};
			int flagg = 0;
			int fflagg = 0;
			int userReplyPiece;
			int countwarring{ 0 };
			int countwarring2{ 0 };

			
			for (int coY = 0; coY < (widthIshodnic)& flag1 == 0; coY+=3, countBY-=3)
			{
				if (countwarring2 > 10000000)
				{
					SendMessage(hWnd, WM_DESTROY, 0, 0);
		
				}
				++countwarring2;

				
				for (int coX = 0; coX < (lengthIshodnic - lengths) & flag1 == 0; coX+=3, countBX+=3) //!!
				{
					if (countwarring > 10000000)
					{
						SendMessage(hWnd, WM_DESTROY, 0, 0);
		
					}
					++countwarring;

					s.left = left + countBX;	//отступ левого верхнего угла по оси X
					s.top = top1 + countBY;  //отступ левого верхнего угла по оси Y: +pos.x это для перерисовки прямоугольника для полосы прокрутки
					s.right = s.left + lengths; // длина по оси X с учетом a.left
					s.bottom = s.top - weights; // длина по оси Y с учетом a.top

					if (!(RectInRegion(hRgnRam1, &s)))
					{
						flag1 = 1;
						fflagg = 1;
					}
				}

				countBX = 0;
				coX = 0;
			}
			flag1 = 0;

			if (fflagg)
			{

				hRgns = CreateRectRgnIndirect(&s);
				CombineRgn(hRgnRam1, hRgnRam1, hRgns, RGN_OR);
				FillRect(hDC, &s, hBrushKusok);
				FrameRgn(hDC, hRgns, hBrushFrame , 3, 3);
				
				DrawText(hDC, "19", -1, &s, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
				DrawText(hDC, IntToStr(lengths - propil), -1, &s, DT_SINGLELINE | DT_LEFT | DT_CENTER);
				DrawText(hDC, IntToStr(weights - propil), -1, &s, DT_SINGLELINE | DT_LEFT | DT_VCENTER);
				SetWindowText(hStat, DoubleToStr(squar, 2));//Выводим площадь исходника в статическое поле

				
			}
			else
			{
				{
					MessageBox(hWnd, "Недопустимые размеры",
						"", 0);
					lengths = 0;
					weights = 0;
				countPiece=18;
				
				squar = 0;
					DeleteObject(hRgnRam1);
					DeleteObject(hRgnRam2);
					DeleteObject(hRgnRam3);
					DeleteObject(hRgnRam4);
					DeleteObject(hRgna);
					DeleteObject(hRgnb);
					DeleteObject(hRgnc);
					DeleteObject(hRgnd);
					DeleteObject(hRgne);
					DeleteObject(hRgnf);
					DeleteObject(hRgng);
					DeleteObject(hRgnh);
					DeleteObject(hRgni);
					DeleteObject(hRgnj);
					DeleteObject(hRgnk);
					DeleteObject(hRgnl);
					DeleteObject(hRgnm);
					DeleteObject(hRgnn);
					DeleteObject(hRgno);
					DeleteObject(hRgnp);
					DeleteObject(hRgnq);
					DeleteObject(hRgnrr);
					DeleteObject(hRgns);
					DeleteObject(hRgnt);
					DeleteObject(hRgnu);
					DeleteObject(hRgnv);
					DeleteObject(hRgnw);
					DeleteObject(hRgnx);
					DeleteObject(hRgny);
					DeleteObject(hRgnz);
					DeleteObject(hRgnxx);
					DeleteObject(hRgnww);
					DeleteObject(hRgnee);
					DeleteObject(hRgnyy);


					lengtht = 0;
					weightt = 0;
					lengthu = 0;
					weightu = 0;
					lengthv = 0;
					weightv = 0;
					lengthw = 0;
					weightw = 0;
					lengthx = 0;
					weightx = 0;
					lengthy = 0;
					weighty = 0;
					lengthz = 0;
					weightz = 0;
					lengthxx = 0;
					weightxx = 0;
					lengthww = 0;
					weightww = 0;
					lengthee = 0;
					weightee = 0;
					lengthyy = 0;
					weightyy = 0;

					DeleteObject(hBrush);
					DeleteObject(hBrushIshod);
					DeleteObject(hBrushKusok);
					DeleteObject(hBrushFrame);
					DeleteObject(hPen);
					DeleteObject(hFont);
					DeleteObject(hDC);
					EndPaint(hWnd, &ps);

					return 0;
				}
			}
		}
		//Двадцатый кусок

		if (countPiece > 19)  // в следующем куске 20
		{
			
			if (lengtht == 0 & weightt == 0)
			{
				lengtht = len1 + propil; // len1 и len2 взяты из полей диалогового окна
				weightt = len2 + propil;
				squar -= squarPiece; // Вычитаем площадь куска из исходника
			}

			int	countBX = 0;
			int countBY = 0;
			int coX{};
			int flagg = 0;
			int fflagg = 0;
			int userReplyPiece;
			int countwarring{ 0 };
			int countwarring2{ 0 };

		
			for (int coY = 0; coY < (widthIshodnic)& flag1 == 0; coY+=3, countBY-=3)
			{
				if (countwarring2 > 10000000)
				{
					SendMessage(hWnd, WM_DESTROY, 0, 0);
		
				}
				++countwarring2;

				
				for (int coX = 0; coX < (lengthIshodnic - lengtht) & flag1 == 0; coX+=3, countBX+=3) //!!
				{
					if (countwarring > 10000000)
					{
						SendMessage(hWnd, WM_DESTROY, 0, 0);
		
					}
					++countwarring;

					t.left = left + countBX;	//отступ левого верхнего угла по оси X
					t.top = top1 + countBY;  //отступ левого верхнего угла по оси Y: +pos.x это для перерисовки прямоугольника для полосы прокрутки
					t.right = t.left + lengtht; // длина по оси X с учетом a.left
					t.bottom = t.top - weightt; // длина по оси Y с учетом a.top

					if (!(RectInRegion(hRgnRam1, &t)))
					{
						flag1 = 1;
						fflagg = 1;
					}
				}

				countBX = 0;
				coX = 0;
			}
			flag1 = 0;

			if (fflagg)
			{

				hRgnt = CreateRectRgnIndirect(&t);
				CombineRgn(hRgnRam1, hRgnRam1, hRgnt, RGN_OR);
				FillRect(hDC, &t, hBrushKusok);
				FrameRgn(hDC, hRgnt, hBrushFrame, 3, 3);
				
				DrawText(hDC, "20", -1, &t, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
				DrawText(hDC, IntToStr(lengtht - propil), -1, &t, DT_SINGLELINE | DT_LEFT | DT_CENTER);
				DrawText(hDC, IntToStr(weightt - propil), -1, &t, DT_SINGLELINE | DT_LEFT | DT_VCENTER);
				SetWindowText(hStat, DoubleToStr(squar, 2));//Выводим площадь исходника в статическое поле

			
			}
			else
			{
				{
					MessageBox(hWnd, "Недопустимые размеры",
						"", 0);
					lengtht = 0;
					weightt = 0;
				countPiece=19;
				
				squar = 0;
					DeleteObject(hRgnRam1);
					DeleteObject(hRgnRam2);
					DeleteObject(hRgnRam3);
					DeleteObject(hRgnRam4);
					DeleteObject(hRgna);
					DeleteObject(hRgnb);
					DeleteObject(hRgnc);
					DeleteObject(hRgnd);
					DeleteObject(hRgne);
					DeleteObject(hRgnf);
					DeleteObject(hRgng);
					DeleteObject(hRgnh);
					DeleteObject(hRgni);
					DeleteObject(hRgnj);
					DeleteObject(hRgnk);
					DeleteObject(hRgnl);
					DeleteObject(hRgnm);
					DeleteObject(hRgnn);
					DeleteObject(hRgno);
					DeleteObject(hRgnp);
					DeleteObject(hRgnq);
					DeleteObject(hRgnrr);
					DeleteObject(hRgns);
					DeleteObject(hRgnt);
					DeleteObject(hRgnu);
					DeleteObject(hRgnv);
					DeleteObject(hRgnw);
					DeleteObject(hRgnx);
					DeleteObject(hRgny);
					DeleteObject(hRgnz);
					DeleteObject(hRgnxx);
					DeleteObject(hRgnww);
					DeleteObject(hRgnee);
					DeleteObject(hRgnyy);


					
					lengthu = 0;
					weightu = 0;
					lengthv = 0;
					weightv = 0;
					lengthw = 0;
					weightw = 0;
					lengthx = 0;
					weightx = 0;
					lengthy = 0;
					weighty = 0;
					lengthz = 0;
					weightz = 0;
					lengthxx = 0;
					weightxx = 0;
					lengthww = 0;
					weightww = 0;
					lengthee = 0;
					weightee = 0;
					lengthyy = 0;
					weightyy = 0;

					DeleteObject(hBrush);
					DeleteObject(hBrushIshod);
					DeleteObject(hBrushKusok);
					DeleteObject(hBrushFrame);
					DeleteObject(hPen);
					DeleteObject(hFont);
					DeleteObject(hDC);
					EndPaint(hWnd, &ps);

					return 0;
				}
			}
		}
		//Двадцать первый кусок

		if (countPiece > 20)  // в следующем куске 21
		{
			
			if (lengthu == 0 & weightu == 0)
			{
				lengthu = len1 + propil; // len1 и len2 взяты из полей диалогового окна
				weightu = len2 + propil;
				squar -= squarPiece; // Вычитаем площадь куска из исходника
			}

			int	countBX = 0;
			int countBY = 0;
			int coX{};
			int flagg = 0;
			int fflagg = 0;
			int userReplyPiece;
			int countwarring{ 0 };
			int countwarring2{ 0 };

			
			for (int coY = 0; coY < (widthIshodnic)& flag1 == 0; coY+=3, countBY-=3)
			{
				if (countwarring2 > 10000000)
				{
					SendMessage(hWnd, WM_DESTROY, 0, 0);
		
				}
				++countwarring2;


				for (int coX = 0; coX < (lengthIshodnic - lengthu) & flag1 == 0; coX+=3, countBX+=3) //!!
				{
					if (countwarring > 10000000)
					{
						SendMessage(hWnd, WM_DESTROY, 0, 0);
		
					}
					++countwarring;

					u.left = left + countBX;	//отступ левого верхнего угла по оси X
					u.top = top1 + countBY;  //отступ левого верхнего угла по оси Y: +pos.x это для перерисовки прямоугольника для полосы прокрутки
					u.right = u.left + lengthu; // длина по оси X с учетом a.left
					u.bottom = u.top - weightu; // длина по оси Y с учетом a.top

					if (!(RectInRegion(hRgnRam1, &u)))
					{
						flag1 = 1;
						fflagg = 1;
					}
				}

				countBX = 0;
				coX = 0;
			}
			flag1 = 0;

			if (fflagg)
			{

				hRgnu = CreateRectRgnIndirect(&u);
				CombineRgn(hRgnRam1, hRgnRam1, hRgnu, RGN_OR);
				FillRect(hDC, &u, hBrushKusok);
				FrameRgn(hDC, hRgnu, hBrushFrame, 3, 3);
				
				DrawText(hDC, "21", -1, &u, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
				DrawText(hDC, IntToStr(lengthu - propil), -1, &u, DT_SINGLELINE | DT_LEFT | DT_CENTER);
				DrawText(hDC, IntToStr(weightu - propil), -1, &u, DT_SINGLELINE | DT_LEFT | DT_VCENTER);
				SetWindowText(hStat, DoubleToStr(squar, 2));//Выводим площадь исходника в статическое поле

		
			}
			else
			{
				{
					MessageBox(hWnd, "Недопустимые размеры",
						"", 0);
					lengthu = 0;
					weightu = 0;
				countPiece=20;
				
				squar = 0;
					DeleteObject(hRgnRam1);
					DeleteObject(hRgnRam2);
					DeleteObject(hRgnRam3);
					DeleteObject(hRgnRam4);
					DeleteObject(hRgna);
					DeleteObject(hRgnb);
					DeleteObject(hRgnc);
					DeleteObject(hRgnd);
					DeleteObject(hRgne);
					DeleteObject(hRgnf);
					DeleteObject(hRgng);
					DeleteObject(hRgnh);
					DeleteObject(hRgni);
					DeleteObject(hRgnj);
					DeleteObject(hRgnk);
					DeleteObject(hRgnl);
					DeleteObject(hRgnm);
					DeleteObject(hRgnn);
					DeleteObject(hRgno);
					DeleteObject(hRgnp);
					DeleteObject(hRgnq);
					DeleteObject(hRgnrr);
					DeleteObject(hRgns);
					DeleteObject(hRgnt);
					DeleteObject(hRgnu);
					DeleteObject(hRgnv);
					DeleteObject(hRgnw);
					DeleteObject(hRgnx);
					DeleteObject(hRgny);
					DeleteObject(hRgnz);
					DeleteObject(hRgnxx);
					DeleteObject(hRgnww);
					DeleteObject(hRgnee);
					DeleteObject(hRgnyy);


				
					lengthv = 0;
					weightv = 0;
					lengthw = 0;
					weightw = 0;
					lengthx = 0;
					weightx = 0;
					lengthy = 0;
					weighty = 0;
					lengthz = 0;
					weightz = 0;
					lengthxx = 0;
					weightxx = 0;
					lengthww = 0;
					weightww = 0;
					lengthee = 0;
					weightee = 0;
					lengthyy = 0;
					weightyy = 0;

					DeleteObject(hBrush);
					DeleteObject(hBrushIshod);
					DeleteObject(hBrushKusok);
					DeleteObject(hBrushFrame);
					DeleteObject(hPen);
					DeleteObject(hFont);
					DeleteObject(hDC);
					EndPaint(hWnd, &ps);

					return 0;
				}
			}
		}
		//Двадцать второй кусок

		if (countPiece > 21)  // в следующем куске 22
		{
			 
			if (lengthv == 0 & weightv == 0)
			{
				lengthv = len1 + propil; // len1 и len2 взяты из полей диалогового окна
				weightv = len2 + propil;
				squar -= squarPiece; // Вычитаем площадь куска из исходника
			}

			int	countBX = 0;
			int countBY = 0;
			int coX{};
			int flagg = 0;
			int fflagg = 0;
			int userReplyPiece;
			int countwarring{ 0 };
			int countwarring2{ 0 };

			
			for (int coY = 0; coY < (widthIshodnic)& flag1 == 0; coY+=3, countBY-=3)
			{

				if (countwarring2 > 10000000)
				{
					SendMessage(hWnd, WM_DESTROY, 0, 0);
			
				}
				++countwarring2;
				
				for (int coX = 0; coX < (lengthIshodnic - lengthv) & flag1 == 0; coX+=3, countBX+=3) //!!
				{
					

					if (countwarring > 10000000)
					{
						SendMessage(hWnd, WM_DESTROY, 0, 0);
			
					}
					++countwarring;

					v.left = left + countBX;	//отступ левого верхнего угла по оси X
					v.top = top1 + countBY;  //отступ левого верхнего угла по оси Y: +pos.x это для перерисовки прямоугольника для полосы прокрутки
					v.right = v.left + lengthv; // длина по оси X с учетом a.left
					v.bottom = v.top - weightv; // длина по оси Y с учетом a.top

					if (!(RectInRegion(hRgnRam1, &v)))
					{
						flag1 = 1;
						fflagg = 1;
					}
				}

				countBX = 0;
				coX = 0;
			}
			flag1 = 0;

			if (fflagg)
			{

				hRgnv = CreateRectRgnIndirect(&v);
				CombineRgn(hRgnRam1, hRgnRam1, hRgnv, RGN_OR);
				FillRect(hDC, &v, hBrushKusok);
				FrameRgn(hDC, hRgnv, hBrushFrame, 3, 3);
				
				DrawText(hDC, "22", -1, &v, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
				DrawText(hDC, IntToStr(lengthv - propil), -1, &v, DT_SINGLELINE | DT_LEFT | DT_CENTER);
				DrawText(hDC, IntToStr(weightv - propil), -1, &v, DT_SINGLELINE | DT_LEFT | DT_VCENTER);
				SetWindowText(hStat, DoubleToStr(squar, 2));//Выводим площадь исходника в статическое поле

			
			}
			else
			{
				{
					MessageBox(hWnd, "Недопустимые размеры",
						"", 0);
					lengthv = 0;
					weightv = 0;
				countPiece=21;
				
				squar = 0;
					DeleteObject(hRgnRam1);
					DeleteObject(hRgnRam2);
					DeleteObject(hRgnRam3);
					DeleteObject(hRgnRam4);
					DeleteObject(hRgna);
					DeleteObject(hRgnb);
					DeleteObject(hRgnc);
					DeleteObject(hRgnd);
					DeleteObject(hRgne);
					DeleteObject(hRgnf);
					DeleteObject(hRgng);
					DeleteObject(hRgnh);
					DeleteObject(hRgni);
					DeleteObject(hRgnj);
					DeleteObject(hRgnk);
					DeleteObject(hRgnl);
					DeleteObject(hRgnm);
					DeleteObject(hRgnn);
					DeleteObject(hRgno);
					DeleteObject(hRgnp);
					DeleteObject(hRgnq);
					DeleteObject(hRgnrr);
					DeleteObject(hRgns);
					DeleteObject(hRgnt);
					DeleteObject(hRgnu);
					DeleteObject(hRgnv);
					DeleteObject(hRgnw);
					DeleteObject(hRgnx);
					DeleteObject(hRgny);
					DeleteObject(hRgnz);
					DeleteObject(hRgnxx);
					DeleteObject(hRgnww);
					DeleteObject(hRgnee);
					DeleteObject(hRgnyy);


				
					lengthw = 0;
					weightw = 0;
					lengthx = 0;
					weightx = 0;
					lengthy = 0;
					weighty = 0;
					lengthz = 0;
					weightz = 0;
					lengthxx = 0;
					weightxx = 0;
					lengthww = 0;
					weightww = 0;
					lengthee = 0;
					weightee = 0;
					lengthyy = 0;
					weightyy = 0;

					DeleteObject(hBrush);
					DeleteObject(hBrushIshod);
					DeleteObject(hBrushKusok);
					DeleteObject(hBrushFrame);
					DeleteObject(hPen);
					DeleteObject(hFont);
					DeleteObject(hDC);
					EndPaint(hWnd, &ps);

					return 0;
				}
			}
		}
		//Двадцать третий кусок

		if (countPiece > 22)  // в следующем куске 23
		{
		
			if (lengthw == 0 & weightw == 0)
			{
				lengthw = len1 + propil; // len1 и len2 взяты из полей диалогового окна
				weightw = len2 + propil;
				squar -= squarPiece; // Вычитаем площадь куска из исходника
			}

			int	countBX = 0;
			int countBY = 0;
			int coX{};
			int flagg = 0;
			int fflagg = 0;
			int userReplyPiece;
			int countwarring{ 0 };
			int countwarring2{ 0 };

			
			for (int coY = 0; coY < (widthIshodnic)& flag1 == 0; coY+=3, countBY-=3)
			{
				if (countwarring2 > 10000000)
				{
					SendMessage(hWnd, WM_DESTROY, 0, 0);
		
				}
				++countwarring2;

				
				for (int coX = 0; coX < (lengthIshodnic - lengthw) & flag1 == 0; coX+=3, countBX+=3) //!!
				{

					if (countwarring > 10000000)
					{
						SendMessage(hWnd, WM_DESTROY, 0, 0);
		
					}
					++countwarring;

					w.left = left + countBX;	//отступ левого верхнего угла по оси X
					w.top = top1 + countBY;  //отступ левого верхнего угла по оси Y: +pos.x это для перерисовки прямоугольника для полосы прокрутки
					w.right = w.left + lengthw; // длина по оси X с учетом a.left
					w.bottom = w.top - weightw; // длина по оси Y с учетом a.top

					if (!(RectInRegion(hRgnRam1, &w)))
					{
						flag1 = 1;
						fflagg = 1;
					}
				}

				countBX = 0;
				coX = 0;
			}
			flag1 = 0;

			if (fflagg)
			{

				hRgnw = CreateRectRgnIndirect(&w);
				CombineRgn(hRgnRam1, hRgnRam1, hRgnw, RGN_OR);
				FillRect(hDC, &w, hBrushKusok);
				FrameRgn(hDC, hRgnw, hBrushFrame, 3, 3);
				
				DrawText(hDC, "23", -1, &w, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
				DrawText(hDC, IntToStr(lengthw - propil), -1, &w, DT_SINGLELINE | DT_LEFT | DT_CENTER);
				DrawText(hDC, IntToStr(weightw - propil), -1, &w, DT_SINGLELINE | DT_LEFT | DT_VCENTER);
				SetWindowText(hStat, DoubleToStr(squar, 2));//Выводим площадь исходника в статическое поле

			
			}
			else
			{
				{
					MessageBox(hWnd, "Недопустимые размеры",
						"", 0);
					lengthw = 0;
					weightw = 0;
					countPiece=22;
					
					squar = 0;
					DeleteObject(hRgnRam1);
					DeleteObject(hRgnRam2);
					DeleteObject(hRgnRam3);
					DeleteObject(hRgnRam4);
					DeleteObject(hRgna);
					DeleteObject(hRgnb);
					DeleteObject(hRgnc);
					DeleteObject(hRgnd);
					DeleteObject(hRgne);
					DeleteObject(hRgnf);
					DeleteObject(hRgng);
					DeleteObject(hRgnh);
					DeleteObject(hRgni);
					DeleteObject(hRgnj);
					DeleteObject(hRgnk);
					DeleteObject(hRgnl);
					DeleteObject(hRgnm);
					DeleteObject(hRgnn);
					DeleteObject(hRgno);
					DeleteObject(hRgnp);
					DeleteObject(hRgnq);
					DeleteObject(hRgnrr);
					DeleteObject(hRgns);
					DeleteObject(hRgnt);
					DeleteObject(hRgnu);
					DeleteObject(hRgnv);
					DeleteObject(hRgnw);
					DeleteObject(hRgnx);
					DeleteObject(hRgny);
					DeleteObject(hRgnz);
					DeleteObject(hRgnxx);
					DeleteObject(hRgnww);
					DeleteObject(hRgnee);
					DeleteObject(hRgnyy);


			
					lengthx = 0;
					weightx = 0;
					lengthy = 0;
					weighty = 0;
					lengthz = 0;
					weightz = 0;
					lengthxx = 0;
					weightxx = 0;
					lengthww = 0;
					weightww = 0;
					lengthee = 0;
					weightee = 0;
					lengthyy = 0;
					weightyy = 0;

					DeleteObject(hBrush);
					DeleteObject(hBrushIshod);
					DeleteObject(hBrushKusok);
					DeleteObject(hBrushFrame);
					DeleteObject(hPen);
					DeleteObject(hFont);
					DeleteObject(hDC);
					EndPaint(hWnd, &ps);

					return 0;
				}
			}
		}
		//Двадцать четвертый кусок

		if (countPiece > 23)  // в следующем куске 24
		{
			
			if (lengthx == 0 & weightx == 0)
			{
				lengthx = len1 + propil; // len1 и len2 взяты из полей диалогового окна
				weightx = len2 + propil;
				squar -= squarPiece; // Вычитаем площадь куска из исходника
			}

			int	countBX = 0;
			int countBY = 0;
			int coX{};
			int flagg = 0;
			int fflagg = 0;
			int userReplyPiece;
			int countwarring{ 0 };
			int countwarring2{ 0 };

			
			for (int coY = 0; coY < (widthIshodnic)& flag1 == 0; coY+=3, countBY-=3)
			{
				if (countwarring2 > 10000000)
				{
					SendMessage(hWnd, WM_DESTROY, 0, 0);
		
				}
				++countwarring2;

			
				for (int coX = 0; coX < (lengthIshodnic - lengthx) & flag1 == 0; coX+=3, countBX+=3) //!!
				{
					if (countwarring > 10000000)
					{
						SendMessage(hWnd, WM_DESTROY, 0, 0);
		
					}
					++countwarring;

					x.left = left + countBX;	//отступ левого верхнего угла по оси X
					x.top = top1 + countBY;  //отступ левого верхнего угла по оси Y: +pos.x это для перерисовки прямоугольника для полосы прокрутки
					x.right = x.left + lengthx; // длина по оси X с учетом a.left
					x.bottom = x.top - weightx; // длина по оси Y с учетом a.top

					if (!(RectInRegion(hRgnRam1, &x)))
					{
						flag1 = 1;
						fflagg = 1;
					}
				}

				countBX = 0;
				coX = 0;
			}
			flag1 = 0;

			if (fflagg)
			{

				hRgnx = CreateRectRgnIndirect(&x);
				CombineRgn(hRgnRam1, hRgnRam1, hRgnx, RGN_OR);
				FillRect(hDC, &x, hBrushKusok);
				FrameRgn(hDC, hRgnx, hBrushFrame, 3, 3);
				
				DrawText(hDC, "24", -1, &x, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
				DrawText(hDC, IntToStr(lengthx - propil), -1, &x, DT_SINGLELINE | DT_LEFT | DT_CENTER);
				DrawText(hDC, IntToStr(weightx - propil), -1, &x, DT_SINGLELINE | DT_LEFT | DT_VCENTER);
				SetWindowText(hStat, DoubleToStr(squar, 2));//Выводим площадь исходника в статическое поле

				
			}
			else
			{
				{
					MessageBox(hWnd, "Недопустимые размеры",
						"", 0);
					lengthx = 0;
					weightx = 0;
				countPiece=23;
				
				squar = 0;
					DeleteObject(hRgnRam1);
					DeleteObject(hRgnRam2);
					DeleteObject(hRgnRam3);
					DeleteObject(hRgnRam4);
					DeleteObject(hRgna);
					DeleteObject(hRgnb);
					DeleteObject(hRgnc);
					DeleteObject(hRgnd);
					DeleteObject(hRgne);
					DeleteObject(hRgnf);
					DeleteObject(hRgng);
					DeleteObject(hRgnh);
					DeleteObject(hRgni);
					DeleteObject(hRgnj);
					DeleteObject(hRgnk);
					DeleteObject(hRgnl);
					DeleteObject(hRgnm);
					DeleteObject(hRgnn);
					DeleteObject(hRgno);
					DeleteObject(hRgnp);
					DeleteObject(hRgnq);
					DeleteObject(hRgnrr);
					DeleteObject(hRgns);
					DeleteObject(hRgnt);
					DeleteObject(hRgnu);
					DeleteObject(hRgnv);
					DeleteObject(hRgnw);
					DeleteObject(hRgnx);
					DeleteObject(hRgny);
					DeleteObject(hRgnz);
					DeleteObject(hRgnxx);
					DeleteObject(hRgnww);
					DeleteObject(hRgnee);
					DeleteObject(hRgnyy);


					lengthy = 0;
					weighty = 0;
					lengthz = 0;
					weightz = 0;
					lengthxx = 0;
					weightxx = 0;
					lengthww = 0;
					weightww = 0;
					lengthee = 0;
					weightee = 0;
					lengthyy = 0;
					weightyy = 0;

					DeleteObject(hBrush);
					DeleteObject(hBrushIshod);
					DeleteObject(hBrushKusok);
					DeleteObject(hBrushFrame);
					DeleteObject(hPen);
					DeleteObject(hFont);
					DeleteObject(hDC);
					EndPaint(hWnd, &ps);

					return 0;
				}
			}
		}
		//Двадцать пятый кусок

		if (countPiece > 24)  // в следующем куске 25
		{
		
			if (lengthy == 0 & weighty == 0)
			{
				lengthy = len1 + propil; // len1 и len2 взяты из полей диалогового окна
				weighty = len2 + propil;
				squar -= squarPiece; // Вычитаем площадь куска из исходника
			}

			int	countBX = 0;
			int countBY = 0;
			int coX{};
			int flagg = 0;
			int fflagg = 0;
			int userReplyPiece;
			int countwarring{ 0 };
			int countwarring2{ 0 };

			
			for (int coY = 0; coY < (widthIshodnic)& flag1 == 0; coY+=3, countBY-=3)
			{
				if (countwarring2 > 10000000)
				{
					SendMessage(hWnd, WM_DESTROY, 0, 0);
		
				}
				++countwarring2;

				
				for (int coX = 0; coX < (lengthIshodnic - lengthy) & flag1 == 0; coX+=3, countBX+=3) //!!
				{

					if (countwarring > 10000000)
					{
						SendMessage(hWnd, WM_DESTROY, 0, 0);
		
					}
					++countwarring;

					y.left = left + countBX;	//отступ левого верхнего угла по оси X
					y.top = top1 + countBY;  //отступ левого верхнего угла по оси Y: +pos.x это для перерисовки прямоугольника для полосы прокрутки
					y.right = y.left + lengthy; // длина по оси X с учетом a.left
					y.bottom = y.top - weighty; // длина по оси Y с учетом a.top

					if (!(RectInRegion(hRgnRam1, &y)))
					{
						flag1 = 1;
						fflagg = 1;
					}
				}

				countBX = 0;
				coX = 0;
			}
			flag1 = 0;

			if (fflagg)
			{

				hRgny = CreateRectRgnIndirect(&y);
				CombineRgn(hRgnRam1, hRgnRam1, hRgny, RGN_OR);
				FillRect(hDC, &y, hBrushKusok);
				FrameRgn(hDC, hRgny, hBrushFrame, 3, 3);
				
				DrawText(hDC, "25", -1, &y, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
				DrawText(hDC, IntToStr(lengthy - propil), -1, &y, DT_SINGLELINE | DT_LEFT | DT_CENTER);
				DrawText(hDC, IntToStr(weighty - propil), -1, &y, DT_SINGLELINE | DT_LEFT | DT_VCENTER);
				SetWindowText(hStat, DoubleToStr(squar, 2));//Выводим площадь исходника в статическое поле

				
			}
			else
			{
				{
					MessageBox(hWnd, "Недопустимые размеры",
						"", 0);
					lengthy = 0;
					weighty = 0;
				countPiece=24;
					
				squar = 0;
					DeleteObject(hRgnRam1);
					DeleteObject(hRgnRam2);
					DeleteObject(hRgnRam3);
					DeleteObject(hRgnRam4);
					DeleteObject(hRgna);
					DeleteObject(hRgnb);
					DeleteObject(hRgnc);
					DeleteObject(hRgnd);
					DeleteObject(hRgne);
					DeleteObject(hRgnf);
					DeleteObject(hRgng);
					DeleteObject(hRgnh);
					DeleteObject(hRgni);
					DeleteObject(hRgnj);
					DeleteObject(hRgnk);
					DeleteObject(hRgnl);
					DeleteObject(hRgnm);
					DeleteObject(hRgnn);
					DeleteObject(hRgno);
					DeleteObject(hRgnp);
					DeleteObject(hRgnq);
					DeleteObject(hRgnrr);
					DeleteObject(hRgns);
					DeleteObject(hRgnt);
					DeleteObject(hRgnu);
					DeleteObject(hRgnv);
					DeleteObject(hRgnw);
					DeleteObject(hRgnx);
					DeleteObject(hRgny);
					DeleteObject(hRgnz);
					DeleteObject(hRgnxx);
					DeleteObject(hRgnww);
					DeleteObject(hRgnee);
					DeleteObject(hRgnyy);


			
					lengthz = 0;
					weightz = 0;
					lengthxx = 0;
					weightxx = 0;
					lengthww = 0;
					weightww = 0;
					lengthee = 0;
					weightee = 0;
					lengthyy = 0;
					weightyy = 0;

					DeleteObject(hBrush);
					DeleteObject(hBrushIshod);
					DeleteObject(hBrushKusok);
					DeleteObject(hBrushFrame);
					DeleteObject(hPen);
					DeleteObject(hFont);
					DeleteObject(hDC);
					EndPaint(hWnd, &ps);

					return 0;
				}
			}
		}
		//Двадцать шестой кусок

		if (countPiece > 25)  // в следующем куске 26
		{
		
			if (lengthz == 0 & weightz == 0)
			{
				lengthz = len1 + propil; // len1 и len2 взяты из полей диалогового окна
				weightz = len2 + propil;
				squar -= squarPiece; // Вычитаем площадь куска из исходника
			}

			int	countBX = 0;
			int countBY = 0;
			int coX{};
			int flagg = 0;
			int fflagg = 0;
			int userReplyPiece;
			int countwarring{ 0 };
			int countwarring2{ 0 };

		
			for (int coY = 0; coY < (widthIshodnic)& flag1 == 0; coY+=3, countBY-=3)
			{
				if (countwarring2 > 10000000)
				{
					SendMessage(hWnd, WM_DESTROY, 0, 0);
		
				}
				++countwarring2;

			
				for (int coX = 0; coX < (lengthIshodnic - lengthz) & flag1 == 0; coX+=3, countBX+=3) //!!
				{

					if (countwarring > 10000000)
					{
						SendMessage(hWnd, WM_DESTROY, 0, 0);
		
					}
					++countwarring;

					z.left = left + countBX;	//отступ левого верхнего угла по оси X
					z.top = top1 + countBY;  //отступ левого верхнего угла по оси Y: +pos.x это для перерисовки прямоугольника для полосы прокрутки
					z.right = z.left + lengthz; // длина по оси X с учетом a.left
					z.bottom = z.top - weightz; // длина по оси Y с учетом a.top

					if (!(RectInRegion(hRgnRam1, &z)))
					{
						flag1 = 1;
						fflagg = 1;
					}
				}

				countBX = 0;
				coX = 0;
			}
			flag1 = 0;

			if (fflagg)
			{

				hRgnz = CreateRectRgnIndirect(&z);
				CombineRgn(hRgnRam1, hRgnRam1, hRgnz, RGN_OR);
				FillRect(hDC, &z, hBrushKusok);
				FrameRgn(hDC, hRgnz, hBrushFrame, 3, 3);
				
				DrawText(hDC, "26", -1, &z, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
				DrawText(hDC, IntToStr(lengthz - propil), -1, &z, DT_SINGLELINE | DT_LEFT | DT_CENTER);
				DrawText(hDC, IntToStr(weightz - propil), -1, &z, DT_SINGLELINE | DT_LEFT | DT_VCENTER);
				SetWindowText(hStat, DoubleToStr(squar, 2));//Выводим площадь исходника в статическое поле

			
			}
			else
			{
				{
					MessageBox(hWnd, "Недопустимые размеры",
						"", 0);
					lengthz = 0;
					weightz = 0;
				countPiece=25;
				
				squar = 0;
				DeleteObject(hRgnRam1);
				DeleteObject(hRgnRam2);
				DeleteObject(hRgnRam3);
				DeleteObject(hRgnRam4);
				DeleteObject(hRgna);
				DeleteObject(hRgnb);
				DeleteObject(hRgnc);
				DeleteObject(hRgnd);
				DeleteObject(hRgne);
				DeleteObject(hRgnf);
				DeleteObject(hRgng);
				DeleteObject(hRgnh);
				DeleteObject(hRgni);
				DeleteObject(hRgnj);
				DeleteObject(hRgnk);
				DeleteObject(hRgnl);
				DeleteObject(hRgnm);
				DeleteObject(hRgnn);
				DeleteObject(hRgno);
				DeleteObject(hRgnp);
				DeleteObject(hRgnq);
				DeleteObject(hRgnrr);
				DeleteObject(hRgns);
				DeleteObject(hRgnt);
				DeleteObject(hRgnu);
				DeleteObject(hRgnv);
				DeleteObject(hRgnw);
				DeleteObject(hRgnx);
				DeleteObject(hRgny);
				DeleteObject(hRgnz);
				DeleteObject(hRgnxx);
				DeleteObject(hRgnww);
				DeleteObject(hRgnee);
				DeleteObject(hRgnyy);


				lengthxx = 0;
				weightxx = 0;
				lengthww = 0;
				weightww = 0;
				lengthee = 0;
				weightee = 0;
				lengthyy = 0;
				weightyy = 0;

				DeleteObject(hBrush);
				DeleteObject(hBrushIshod);
				DeleteObject(hBrushKusok);
				DeleteObject(hBrushFrame);
				DeleteObject(hPen);
				DeleteObject(hFont);
				DeleteObject(hDC);
				EndPaint(hWnd, &ps);

				return 0;
				}
			}
		}
		//Двадцать седьмой кусок

		if (countPiece > 26)  // в следующем куске 27
		{
		
			if (lengthxx == 0 & weightxx == 0)
			{
				lengthxx = len1 + propil; // len1 и len2 взяты из полей диалогового окна
				weightxx = len2 + propil;
				squar -= squarPiece; // Вычитаем площадь куска из исходника
			}

			int	countBX = 0;
			int countBY = 0;
			int coX{};
			int flagg = 0;
			int fflagg = 0;
			int userReplyPiece;
			int countwarring{ 0 };
			int countwarring2{ 0 };

		
			for (int coY = 0; coY < (widthIshodnic)& flag1 == 0; coY+=3, countBY-=3)
			{
				if (countwarring2 > 10000000)
				{
					SendMessage(hWnd, WM_DESTROY, 0, 0);
		
				}
				++countwarring2;

			
				for (int coX = 0; coX < (lengthIshodnic - lengthxx) & flag1 == 0; coX+=3, countBX+=3) //!!
				{

					if (countwarring > 10000000)
					{
						SendMessage(hWnd, WM_DESTROY, 0, 0);
		
					}
					++countwarring;

					xx.left = left + countBX;	//отступ левого верхнего угла по оси X
					xx.top = top1 + countBY;  //отступ левого верхнего угла по оси Y: +pos.x это для перерисовки прямоугольника для полосы прокрутки
					xx.right = xx.left + lengthxx; // длина по оси X с учетом a.left
					xx.bottom = xx.top - weightxx; // длина по оси Y с учетом a.top

					if (!(RectInRegion(hRgnRam1, &xx)))
					{
						flag1 = 1;
						fflagg = 1;
					}
				}

				countBX = 0;
				coX = 0;
			}
			flag1 = 0;

			if (fflagg)
			{

				hRgnxx = CreateRectRgnIndirect(&xx);
				CombineRgn(hRgnRam1, hRgnRam1, hRgnxx, RGN_OR);
				FillRect(hDC, &xx, hBrushKusok);
				FrameRgn(hDC, hRgnxx, hBrushFrame, 3, 3);
				
				DrawText(hDC, "27", -1, &xx, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
				DrawText(hDC, IntToStr(lengthxx - propil), -1, &xx, DT_SINGLELINE | DT_LEFT | DT_CENTER);
				DrawText(hDC, IntToStr(weightxx - propil), -1, &xx, DT_SINGLELINE | DT_LEFT | DT_VCENTER);
				SetWindowText(hStat, DoubleToStr(squar, 2));//Выводим площадь исходника в статическое поле

			
			}
			else
			{
				{
					MessageBox(hWnd, "Недопустимые размеры",
						"", 0);
					lengthxx = 0;
					weightxx = 0;
					countPiece=26;
				
					squar = 0;
				
					DeleteObject(hRgnRam1);
					DeleteObject(hRgnRam2);
					DeleteObject(hRgnRam3);
					DeleteObject(hRgnRam4);
					DeleteObject(hRgna);
					DeleteObject(hRgnb);
					DeleteObject(hRgnc);
					DeleteObject(hRgnd);
					DeleteObject(hRgne);
					DeleteObject(hRgnf);
					DeleteObject(hRgng);
					DeleteObject(hRgnh);
					DeleteObject(hRgni);
					DeleteObject(hRgnj);
					DeleteObject(hRgnk);
					DeleteObject(hRgnl);
					DeleteObject(hRgnm);
					DeleteObject(hRgnn);
					DeleteObject(hRgno);
					DeleteObject(hRgnp);
					DeleteObject(hRgnq);
					DeleteObject(hRgnrr);
					DeleteObject(hRgns);
					DeleteObject(hRgnt);
					DeleteObject(hRgnu);
					DeleteObject(hRgnv);
					DeleteObject(hRgnw);
					DeleteObject(hRgnx);
					DeleteObject(hRgny);
					DeleteObject(hRgnz);
					DeleteObject(hRgnxx);
					DeleteObject(hRgnww);
					DeleteObject(hRgnee);
					DeleteObject(hRgnyy);


					lengthww = 0;
					weightww = 0;
					lengthee = 0;
					weightee = 0;
					lengthyy = 0;
					weightyy = 0;

					DeleteObject(hBrush);
					DeleteObject(hBrushIshod);
					DeleteObject(hBrushKusok);
					DeleteObject(hBrushFrame);
					DeleteObject(hPen);
					DeleteObject(hFont);
					DeleteObject(hDC);
					EndPaint(hWnd, &ps);

					return 0;
				}
			}
		}
		//Двадцать восьмой кусок

		if (countPiece > 27)  // в следующем куске 28
		{
		
			if (lengthww == 0 & weightww == 0)
			{
				lengthww = len1 + propil; // len1 и len2 взяты из полей диалогового окна
				weightww = len2 + propil;
				squar -= squarPiece; // Вычитаем площадь куска из исходника
			}

			int	countBX = 0;
			int countBY = 0;
			int coX{};
			int flagg = 0;
			int fflagg = 0;
			int userReplyPiece;
			int countwarring{ 0 };
			int countwarring2{ 0 };

		
			for (int coY = 0; coY < (widthIshodnic)& flag1 == 0; coY+=3, countBY-=3)
			{
				if (countwarring2 > 10000000)
				{
					SendMessage(hWnd, WM_DESTROY, 0, 0);
	
				}
				++countwarring2;

			
				for (int coX = 0; coX < (lengthIshodnic - lengthww) & flag1 == 0; coX+=3, countBX+=3) //!!
				{

					if (countwarring > 10000000)
					{
						SendMessage(hWnd, WM_DESTROY, 0, 0);
		//				return 0;
					}
					++countwarring;

					ww.left = left + countBX;	//отступ левого верхнего угла по оси X
					ww.top = top1 + countBY;  //отступ левого верхнего угла по оси Y: +pos.x это для перерисовки прямоугольника для полосы прокрутки
					ww.right = ww.left + lengthww; // длина по оси X с учетом a.left
					ww.bottom = ww.top - weightww; // длина по оси Y с учетом a.top

					if (!(RectInRegion(hRgnRam1, &ww)))
					{
						flag1 = 1;
						fflagg = 1;
					}
				}

				countBX = 0;
				coX = 0;
			}
			flag1 = 0;

			if (fflagg)
			{

				hRgnww = CreateRectRgnIndirect(&ww);
				CombineRgn(hRgnRam1, hRgnRam1, hRgnww, RGN_OR);
				FillRect(hDC, &ww, hBrushKusok);
				FrameRgn(hDC, hRgnww, hBrushFrame, 3, 3);
				
				DrawText(hDC, "28", -1, &ww, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
				DrawText(hDC, IntToStr(lengthww - propil), -1, &ww, DT_SINGLELINE | DT_LEFT | DT_CENTER);
				DrawText(hDC, IntToStr(weightww - propil), -1, &ww, DT_SINGLELINE | DT_LEFT | DT_VCENTER);
				SetWindowText(hStat, DoubleToStr(squar, 2));//Выводим площадь исходника в статическое поле

				
			}
			else
			{
				{
					MessageBox(hWnd, "Недопустимые размеры",
						"", 0);
					lengthww = 0;
					weightww = 0;
					countPiece=27;
				
					squar = 0;
					DeleteObject(hRgnRam1);
					DeleteObject(hRgnRam2);
					DeleteObject(hRgnRam3);
					DeleteObject(hRgnRam4);
					DeleteObject(hRgna);
					DeleteObject(hRgnb);
					DeleteObject(hRgnc);
					DeleteObject(hRgnd);
					DeleteObject(hRgne);
					DeleteObject(hRgnf);
					DeleteObject(hRgng);
					DeleteObject(hRgnh);
					DeleteObject(hRgni);
					DeleteObject(hRgnj);
					DeleteObject(hRgnk);
					DeleteObject(hRgnl);
					DeleteObject(hRgnm);
					DeleteObject(hRgnn);
					DeleteObject(hRgno);
					DeleteObject(hRgnp);
					DeleteObject(hRgnq);
					DeleteObject(hRgnrr);
					DeleteObject(hRgns);
					DeleteObject(hRgnt);
					DeleteObject(hRgnu);
					DeleteObject(hRgnv);
					DeleteObject(hRgnw);
					DeleteObject(hRgnx);
					DeleteObject(hRgny);
					DeleteObject(hRgnz);
					DeleteObject(hRgnxx);
					DeleteObject(hRgnww);
					DeleteObject(hRgnee);
					DeleteObject(hRgnyy);
					
					lengthee = 0;
					weightee = 0;
					lengthyy = 0;
					weightyy = 0;

					DeleteObject(hBrush);
					DeleteObject(hBrushIshod);
					DeleteObject(hBrushKusok);
					DeleteObject(hBrushFrame);
					DeleteObject(hPen);
					DeleteObject(hFont);
					DeleteObject(hDC);
					EndPaint(hWnd, &ps);

					return 0;
				}
			}
		}
		//Двадцать девятый кусок

		if (countPiece > 28)  // в следующем куске 29
		{
			if (lengthee == 0 & weightee == 0)
			{
				lengthee = len1 + propil; // len1 и len2 взяты из полей диалогового окна
				weightee = len2 + propil;
				squar -= squarPiece; // Вычитаем площадь куска из исходника
			}

			int	countBX = 0;
			int countBY = 0;
			int coX{};
			int flagg = 0;
			int fflagg = 0;
			int userReplyPiece;
			int countwarring{ 0 };
			int countwarring2{ 0 };

			
			for (int coY = 0; coY < (widthIshodnic)& flag1 == 0; coY+=3, countBY-=3)
			{
				if (countwarring2 > 10000000)
				{
					SendMessage(hWnd, WM_DESTROY, 0, 0);
		
				}
				++countwarring2;

				
				for (int coX = 0; coX < (lengthIshodnic - lengthee) & flag1 == 0; coX+=3, countBX+=3) //!!
				{

					if (countwarring > 10000000)
					{
						SendMessage(hWnd, WM_DESTROY, 0, 0);
		
					}
					++countwarring;

					ee.left = left + countBX;	//отступ левого верхнего угла по оси X
					ee.top = top1 + countBY;  //отступ левого верхнего угла по оси Y: +pos.x это для перерисовки прямоугольника для полосы прокрутки
					ee.right = ee.left + lengthee; // длина по оси X с учетом a.left
					ee.bottom = ee.top - weightee; // длина по оси Y с учетом a.top

					if (!(RectInRegion(hRgnRam1, &ee)))
					{
						flag1 = 1;
						fflagg = 1;
					}
				}

				countBX = 0;
				coX = 0;
			}
			flag1 = 0;

			if (fflagg)
			{

				hRgnee = CreateRectRgnIndirect(&ee);
				CombineRgn(hRgnRam1, hRgnRam1, hRgnee, RGN_OR);
				FillRect(hDC, &ee, hBrushKusok);
				FrameRgn(hDC, hRgnee, hBrushFrame, 3, 3);
				
				DrawText(hDC, "29", -1, &ee, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
				DrawText(hDC, IntToStr(lengthee - propil), -1, &ee, DT_SINGLELINE | DT_LEFT | DT_CENTER);
				DrawText(hDC, IntToStr(weightee - propil), -1, &ee, DT_SINGLELINE | DT_LEFT | DT_VCENTER);
				SetWindowText(hStat, DoubleToStr(squar, 2));//Выводим площадь исходника в статическое поле

				
			}
			else
			{
				{
					MessageBox(hWnd, "Недопустимые размеры",
						"", 0);
					lengthee = 0;
					weightee = 0;
					countPiece=28;
					
					squar = 0;
					DeleteObject(hRgnRam1);
					DeleteObject(hRgnRam2);
					DeleteObject(hRgnRam3);
					DeleteObject(hRgnRam4);
					DeleteObject(hRgna);
					DeleteObject(hRgnb);
					DeleteObject(hRgnc);
					DeleteObject(hRgnd);
					DeleteObject(hRgne);
					DeleteObject(hRgnf);
					DeleteObject(hRgng);
					DeleteObject(hRgnh);
					DeleteObject(hRgni);
					DeleteObject(hRgnj);
					DeleteObject(hRgnk);
					DeleteObject(hRgnl);
					DeleteObject(hRgnm);
					DeleteObject(hRgnn);
					DeleteObject(hRgno);
					DeleteObject(hRgnp);
					DeleteObject(hRgnq);
					DeleteObject(hRgnrr);
					DeleteObject(hRgns);
					DeleteObject(hRgnt);
					DeleteObject(hRgnu);
					DeleteObject(hRgnv);
					DeleteObject(hRgnw);
					DeleteObject(hRgnx);
					DeleteObject(hRgny);
					DeleteObject(hRgnz);
					DeleteObject(hRgnxx);
					DeleteObject(hRgnww);
					DeleteObject(hRgnee);
					DeleteObject(hRgnyy);


					
					lengthyy = 0;
					weightyy = 0;

					DeleteObject(hBrush);
					DeleteObject(hBrushIshod);
					DeleteObject(hBrushKusok);
					DeleteObject(hBrushFrame);
					DeleteObject(hPen);
					DeleteObject(hFont);
					DeleteObject(hDC);
					EndPaint(hWnd, &ps);

					return 0;
				}
			}
		}
		//Тридцатый кусок

		if (countPiece > 29)  // в следующем куске 30
		{
			
			if (lengthyy == 0 & weightyy == 0)
			{
				lengthyy = len1 + propil; // len1 и len2 взяты из полей диалогового окна
				weightyy = len2 + propil;
				squar -= squarPiece; // Вычитаем площадь куска из исходника
			}

			int	countBX = 0;
			int countBY = 0;
			int coX{};
			int flagg = 0;
			int fflagg = 0;
			int userReplyPiece;
			int countwarring{ 0 };
			int countwarring2{ 0 };

		
			for (int coY = 0; coY < (widthIshodnic)& flag1 == 0; coY+=3, countBY-=3)
			{
				if (countwarring2 > 10000000)
				{
					SendMessage(hWnd, WM_DESTROY, 0, 0);		
				}
				++countwarring2;

			
				for (int coX = 0; coX < (lengthIshodnic - lengthyy) & flag1 == 0; coX+=3, countBX+=3) //!!
				{

					if (countwarring > 10000000)
					{
						SendMessage(hWnd, WM_DESTROY, 0, 0);
		
					}
					++countwarring;

					yy.left = left + countBX;	//отступ левого верхнего угла по оси X
					yy.top = top1 + countBY;  //отступ левого верхнего угла по оси Y: +pos.x это для перерисовки прямоугольника для полосы прокрутки
					yy.right = yy.left + lengthyy; // длина по оси X с учетом a.left
					yy.bottom = yy.top - weightyy; // длина по оси Y с учетом a.top

					if (!(RectInRegion(hRgnRam1, &yy)))
					{
						flag1 = 1;
						fflagg = 1;
					}
				}

				countBX = 0;
				coX = 0;
			}
			flag1 = 0;

			if (fflagg)
			{

				hRgnyy = CreateRectRgnIndirect(&yy);
				CombineRgn(hRgnRam1, hRgnRam1, hRgnyy, RGN_OR);
				FillRect(hDC, &yy, hBrushKusok);
				FrameRgn(hDC, hRgnyy, hBrushFrame, 3, 3);
				
				DrawText(hDC, "30", -1, &yy, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
				DrawText(hDC, IntToStr(lengthyy - propil), -1, &yy, DT_SINGLELINE | DT_LEFT | DT_CENTER);
				DrawText(hDC, IntToStr(weightyy - propil), -1, &yy, DT_SINGLELINE | DT_LEFT | DT_VCENTER);
				SetWindowText(hStat, DoubleToStr(squar, 2));//Выводим площадь исходника в статическое поле

				
			}
			else
			{
				{
					MessageBox(hWnd, "Недопустимые размеры",
						"", 0);
					lengthyy = 0;
					weightyy = 0;
					countPiece=29;
					
					squar = 0;
				
					DeleteObject(hRgnRam1);
					DeleteObject(hRgnRam2);
					DeleteObject(hRgnRam3);
					DeleteObject(hRgnRam4);
					DeleteObject(hRgna);
					DeleteObject(hRgnb);
					DeleteObject(hRgnc);
					DeleteObject(hRgnd);
					DeleteObject(hRgne);
					DeleteObject(hRgnf);
					DeleteObject(hRgng);
					DeleteObject(hRgnh);
					DeleteObject(hRgni);
					DeleteObject(hRgnj);
					DeleteObject(hRgnk);
					DeleteObject(hRgnl);
					DeleteObject(hRgnm);
					DeleteObject(hRgnn);
					DeleteObject(hRgno);
					DeleteObject(hRgnp);
					DeleteObject(hRgnq);
					DeleteObject(hRgnrr);
					DeleteObject(hRgns);
					DeleteObject(hRgnt);
					DeleteObject(hRgnu);
					DeleteObject(hRgnv);
					DeleteObject(hRgnw);
					DeleteObject(hRgnx);
					DeleteObject(hRgny);
					DeleteObject(hRgnz);
					DeleteObject(hRgnxx);
					DeleteObject(hRgnww);
					DeleteObject(hRgnee);
					DeleteObject(hRgnyy);


				

					DeleteObject(hBrush);
					DeleteObject(hBrushIshod);
					DeleteObject(hBrushKusok);
					DeleteObject(hBrushFrame);
					DeleteObject(hPen);
					DeleteObject(hFont);
					DeleteObject(hDC);
					EndPaint(hWnd, &ps);

					return 0;
				}
			}
		}
		
	//########################################################################################################

		//if(countPiece > 0 ) // запись в метафайл после добавления первого листа, чтобы не было глюков в пайнте
	//	if (flagMeta==1) // запись в метафайл после добавления первого листа, чтобы не было глюков в пайнте
	//{ 
	
		SelectObject(hdcEMF, hPen);
		SelectObject(hdcEMF, hFont);
		SetMapMode(hdcEMF, MM_ISOTROPIC); // Переход на логические координаты
		SetBkMode(hdcEMF, TRANSPARENT); //заливка текста
	
		SetWindowExtEx(hdcEMF, 1000, mas, 0);
		SetViewportExtEx(hdcEMF, cxClient, -cyClient, 0);

		// исходник

		FillRect(hdcEMF, &r, hBrushIshod);
		DrawText(hdcEMF, "исходный лист", -1, &r,
			DT_SINGLELINE | DT_CENTER | DT_VCENTER);

		// Первый кусок
		if (countPiece > 0)  // в следующем куске 30
		{
			FillRect(hdcEMF, &a, hBrushKusok);
			FrameRgn(hdcEMF, hRgna, hBrushFrame, 3, 3);
			DrawText(hdcEMF, "1", -1, &a, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
			DrawText(hdcEMF, IntToStr(length - propil), -1, &a, DT_SINGLELINE | DT_LEFT | DT_CENTER);
			DrawText(hdcEMF, IntToStr(weight - propil), -1, &a, DT_SINGLELINE | DT_LEFT | DT_VCENTER);
		}
			
		
		// Второй кусок
		if (countPiece > 1)  // в следующем куске 30
		{
			FillRect(hdcEMF, &b, hBrushKusok);
			FrameRgn(hdcEMF, hRgnb, hBrushFrame, 3, 3);
			DrawText(hdcEMF, "2", -1, &b, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
			DrawText(hdcEMF, IntToStr(lengthb - propil), -1, &b, DT_SINGLELINE | DT_LEFT | DT_CENTER);
			DrawText(hdcEMF, IntToStr(weightb - propil), -1, &b, DT_SINGLELINE | DT_LEFT | DT_VCENTER);
		}

		// Третий кусок
		if (countPiece > 2)  // в следующем куске 30
		{
			FillRect(hdcEMF, &c, hBrushKusok);
			FrameRgn(hdcEMF, hRgnc, hBrushFrame, 3, 3);
			DrawText(hdcEMF, "3", -1, &c, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
			DrawText(hdcEMF, IntToStr(lengthc - propil), -1, &c, DT_SINGLELINE | DT_LEFT | DT_CENTER);
			DrawText(hdcEMF, IntToStr(weightc - propil), -1, &c, DT_SINGLELINE | DT_LEFT | DT_VCENTER);
		}
		
		// Четвертый кусок

		if (countPiece > 3)  // в следующем куске 30
		{
			FillRect(hdcEMF, &d, hBrushKusok);
			FrameRgn(hdcEMF, hRgnd, hBrushFrame, 3, 3);
			DrawText(hdcEMF, "4", -1, &d, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
			DrawText(hdcEMF, IntToStr(lengthd - propil), -1, &d, DT_SINGLELINE | DT_LEFT | DT_CENTER);
			DrawText(hdcEMF, IntToStr(weightd - propil), -1, &d, DT_SINGLELINE | DT_LEFT | DT_VCENTER);
		}
				
		//Пятый кусок
		if (countPiece > 4)  // в следующем куске 30
		{
			FillRect(hdcEMF, &e, hBrushKusok);
			FrameRgn(hdcEMF, hRgne, hBrushFrame, 3, 3);
			DrawText(hdcEMF, "5", -1, &e, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
			DrawText(hdcEMF, IntToStr(lengthe - propil), -1, &e, DT_SINGLELINE | DT_LEFT | DT_CENTER);
			DrawText(hdcEMF, IntToStr(weighte - propil), -1, &e, DT_SINGLELINE | DT_LEFT | DT_VCENTER);
		}
		//Шестой кусок

		if (countPiece > 5)  // в следующем куске 30
		{

			FillRect(hdcEMF, &f, hBrushKusok);
			FrameRgn(hdcEMF, hRgnf, hBrushFrame, 3, 3);
			DrawText(hdcEMF, "6", -1, &f, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
			DrawText(hdcEMF, IntToStr(lengthf - propil), -1, &f, DT_SINGLELINE | DT_LEFT | DT_CENTER);
			DrawText(hdcEMF, IntToStr(weightf - propil), -1, &f, DT_SINGLELINE | DT_LEFT | DT_VCENTER);
		}
		//Седьмой кусок

		if (countPiece > 6)  // в следующем куске 30
		{
			FillRect(hdcEMF, &g, hBrushKusok);
			FrameRgn(hdcEMF, hRgng, hBrushFrame, 3, 3);
			DrawText(hdcEMF, "7", -1, &g, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
			DrawText(hdcEMF, IntToStr(lengthg - propil), -1, &g, DT_SINGLELINE | DT_LEFT | DT_CENTER);
			DrawText(hdcEMF, IntToStr(weightg - propil), -1, &g, DT_SINGLELINE | DT_LEFT | DT_VCENTER);
		}
		//Восьмой кусок
		if (countPiece > 7)  // в следующем куске 30
		{

			FillRect(hdcEMF, &h, hBrushKusok);
			FrameRgn(hdcEMF, hRgnh, hBrushFrame, 3, 3);
			DrawText(hdcEMF, "8", -1, &h, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
			DrawText(hdcEMF, IntToStr(lengthh - propil), -1, &h, DT_SINGLELINE | DT_LEFT | DT_CENTER);
			DrawText(hdcEMF, IntToStr(weighth - propil), -1, &h, DT_SINGLELINE | DT_LEFT | DT_VCENTER);
		}
		//Девятый кусок
		if (countPiece > 8)  // в следующем куске 30
		{
			FillRect(hdcEMF, &i, hBrushKusok);
			FrameRgn(hdcEMF, hRgni, hBrushFrame, 3, 3);
			DrawText(hdcEMF, "9", -1, &i, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
			DrawText(hdcEMF, IntToStr(lengthi - propil), -1, &i, DT_SINGLELINE | DT_LEFT | DT_CENTER);
			DrawText(hdcEMF, IntToStr(weighti - propil), -1, &i, DT_SINGLELINE | DT_LEFT | DT_VCENTER);
		}
		//Деcятый кусок

		if (countPiece > 9)  // в следующем куске 30
		{
			FillRect(hdcEMF, &j, hBrushKusok);
			FrameRgn(hdcEMF, hRgnj, hBrushFrame, 3, 3);
			DrawText(hdcEMF, "10", -1, &j, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
			DrawText(hdcEMF, IntToStr(lengthj - propil), -1, &j, DT_SINGLELINE | DT_LEFT | DT_CENTER);
			DrawText(hdcEMF, IntToStr(weightj - propil), -1, &j, DT_SINGLELINE | DT_LEFT | DT_VCENTER);
		}
		//Одиннадцатый кусок

		if (countPiece > 10)  // в следующем куске 30
		{
			FillRect(hdcEMF, &k, hBrushKusok);
			FrameRgn(hdcEMF, hRgnk, hBrushFrame, 3, 3);
			DrawText(hdcEMF, "11", -1, &k, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
			DrawText(hdcEMF, IntToStr(lengthk - propil), -1, &k, DT_SINGLELINE | DT_LEFT | DT_CENTER);
			DrawText(hdcEMF, IntToStr(weightk - propil), -1, &k, DT_SINGLELINE | DT_LEFT | DT_VCENTER);
		}
		//Двенадцатый кусок
		if (countPiece > 11)  // в следующем куске 30
		{

			FillRect(hdcEMF, &l, hBrushKusok);
			FrameRgn(hdcEMF, hRgnl, hBrushFrame, 3, 3);
			DrawText(hdcEMF, "12", -1, &l, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
			DrawText(hdcEMF, IntToStr(lengthl - propil), -1, &l, DT_SINGLELINE | DT_LEFT | DT_CENTER);
			DrawText(hdcEMF, IntToStr(weightl - propil), -1, &l, DT_SINGLELINE | DT_LEFT | DT_VCENTER);
		}
		//Тринадцатый кусок
		if (countPiece > 12)  // в следующем куске 30
		{
			FillRect(hdcEMF, &m, hBrushKusok);
			FrameRgn(hdcEMF, hRgnm, hBrushFrame, 3, 3);
			DrawText(hdcEMF, "13", -1, &m, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
			DrawText(hdcEMF, IntToStr(lengthm - propil), -1, &m, DT_SINGLELINE | DT_LEFT | DT_CENTER);
			DrawText(hdcEMF, IntToStr(weightm - propil), -1, &m, DT_SINGLELINE | DT_LEFT | DT_VCENTER);
		}
		//Четырнадцатый кусок
		if (countPiece > 13)  // в следующем куске 30
		{
			FillRect(hdcEMF, &n, hBrushKusok);
			FrameRgn(hdcEMF, hRgnn, hBrushFrame, 3, 3);
			DrawText(hdcEMF, "14", -1, &n, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
			DrawText(hdcEMF, IntToStr(lengthn - propil), -1, &n, DT_SINGLELINE | DT_LEFT | DT_CENTER);
			DrawText(hdcEMF, IntToStr(weightn - propil), -1, &n, DT_SINGLELINE | DT_LEFT | DT_VCENTER);
		}
		//Пятнадцатый кусок

		if (countPiece > 14)  // в следующем куске 30
		{
			FillRect(hdcEMF, &o, hBrushKusok);
			FrameRgn(hdcEMF, hRgno, hBrushFrame, 3, 3);
			DrawText(hdcEMF, "15", -1, &o, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
			DrawText(hdcEMF, IntToStr(lengtho - propil), -1, &o, DT_SINGLELINE | DT_LEFT | DT_CENTER);
			DrawText(hdcEMF, IntToStr(weighto - propil), -1, &o, DT_SINGLELINE | DT_LEFT | DT_VCENTER);
		}
		//Шестнадцатый кусок

		if (countPiece > 15)  // в следующем куске 30
		{
			FillRect(hdcEMF, &p, hBrushKusok);
			FrameRgn(hdcEMF, hRgnp, hBrushFrame, 3, 3);
			DrawText(hdcEMF, "16", -1, &p, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
			DrawText(hdcEMF, IntToStr(lengthp - propil), -1, &p, DT_SINGLELINE | DT_LEFT | DT_CENTER);
			DrawText(hdcEMF, IntToStr(weightp - propil), -1, &p, DT_SINGLELINE | DT_LEFT | DT_VCENTER);
		}
		//Семнадцатый кусок

		if (countPiece > 16)  // в следующем куске 30
		{
			FillRect(hdcEMF, &q, hBrushKusok);
			FrameRgn(hdcEMF, hRgnq, hBrushFrame, 3, 3);
			DrawText(hdcEMF, "17", -1, &q, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
			DrawText(hdcEMF, IntToStr(lengthq - propil), -1, &q, DT_SINGLELINE | DT_LEFT | DT_CENTER);
			DrawText(hdcEMF, IntToStr(weightq - propil), -1, &q, DT_SINGLELINE | DT_LEFT | DT_VCENTER);
		}
		//Восемнадцатый кусок

		if (countPiece > 17)  // в следующем куске 30
		{
			FillRect(hdcEMF, &rr, hBrushKusok);
			FrameRgn(hdcEMF, hRgnrr, hBrushFrame, 3, 3);
			DrawText(hdcEMF, "18", -1, &rr, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
			DrawText(hdcEMF, IntToStr(lengthrr - propil), -1, &rr, DT_SINGLELINE | DT_LEFT | DT_CENTER);
			DrawText(hdcEMF, IntToStr(weightrr - propil), -1, &rr, DT_SINGLELINE | DT_LEFT | DT_VCENTER);
		}
		//Девятнадцатый кусок
		if (countPiece > 18)  // в следующем куске 30
		{
			FillRect(hdcEMF, &s, hBrushKusok);
			FrameRgn(hdcEMF, hRgns, hBrushFrame, 3, 3);
			DrawText(hdcEMF, "19", -1, &s, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
			DrawText(hdcEMF, IntToStr(lengths - propil), -1, &s, DT_SINGLELINE | DT_LEFT | DT_CENTER);
			DrawText(hdcEMF, IntToStr(weights - propil), -1, &s, DT_SINGLELINE | DT_LEFT | DT_VCENTER);
			
		}
		//Двадцатый кусок
		if (countPiece > 19)  // в следующем куске 30
		{
			FillRect(hdcEMF, &t, hBrushKusok);
			FrameRgn(hdcEMF, hRgnt, hBrushFrame, 3, 3);
			DrawText(hdcEMF, "20", -1, &t, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
			DrawText(hdcEMF, IntToStr(lengtht - propil), -1, &t, DT_SINGLELINE | DT_LEFT | DT_CENTER);
			DrawText(hdcEMF, IntToStr(weightt - propil), -1, &t, DT_SINGLELINE | DT_LEFT | DT_VCENTER);
		}
		//Двадцать первый кусок

		if (countPiece > 20)  // в следующем куске 30
		{
			FillRect(hdcEMF, &u, hBrushKusok);
			FrameRgn(hdcEMF, hRgnu, hBrushFrame, 3, 3);
			DrawText(hdcEMF, "21", -1, &u, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
			DrawText(hdcEMF, IntToStr(lengthu - propil), -1, &u, DT_SINGLELINE | DT_LEFT | DT_CENTER);
			DrawText(hdcEMF, IntToStr(weightu - propil), -1, &u, DT_SINGLELINE | DT_LEFT | DT_VCENTER);
		}
		//Двадцать второй кусок

		if (countPiece > 21)  // в следующем куске 30
		{
			FillRect(hdcEMF, &v, hBrushKusok);
			FrameRgn(hdcEMF, hRgnv, hBrushFrame, 3, 3);
			DrawText(hdcEMF, "22", -1, &v, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
			DrawText(hdcEMF, IntToStr(lengthv - propil), -1, &v, DT_SINGLELINE | DT_LEFT | DT_CENTER);
			DrawText(hdcEMF, IntToStr(weightv - propil), -1, &v, DT_SINGLELINE | DT_LEFT | DT_VCENTER);
		}
		//Двадцать третий кусок
		if (countPiece > 22)  // в следующем куске 30
		{

			FillRect(hdcEMF, &w, hBrushKusok);
			FrameRgn(hdcEMF, hRgnw, hBrushFrame, 3, 3);
			DrawText(hdcEMF, "23", -1, &w, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
			DrawText(hdcEMF, IntToStr(lengthw - propil), -1, &w, DT_SINGLELINE | DT_LEFT | DT_CENTER);
			DrawText(hdcEMF, IntToStr(weightw - propil), -1, &w, DT_SINGLELINE | DT_LEFT | DT_VCENTER);
		}
		//Двадцать четвертый кусок
		if (countPiece > 23)  // в следующем куске 30
		{
			FillRect(hdcEMF, &x, hBrushKusok);
			FrameRgn(hdcEMF, hRgnx, hBrushFrame, 3, 3);
			DrawText(hdcEMF, "24", -1, &x, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
			DrawText(hdcEMF, IntToStr(lengthx - propil), -1, &x, DT_SINGLELINE | DT_LEFT | DT_CENTER);
			DrawText(hdcEMF, IntToStr(weightx - propil), -1, &x, DT_SINGLELINE | DT_LEFT | DT_VCENTER);
		}
		//Двадцать пятый кусок
		if (countPiece > 24)  // в следующем куске 30
		{
			FillRect(hdcEMF, &y, hBrushKusok);
			FrameRgn(hdcEMF, hRgny, hBrushFrame, 3, 3);
			DrawText(hdcEMF, "25", -1, &y, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
			DrawText(hdcEMF, IntToStr(lengthy - propil), -1, &y, DT_SINGLELINE | DT_LEFT | DT_CENTER);
			DrawText(hdcEMF, IntToStr(weighty - propil), -1, &y, DT_SINGLELINE | DT_LEFT | DT_VCENTER);
		}
		//Двадцать шестой кусок

		if (countPiece > 25)  // в следующем куске 30
		{
			FillRect(hdcEMF, &z, hBrushKusok);
			FrameRgn(hdcEMF, hRgnz, hBrushFrame, 3, 3);
			DrawText(hdcEMF, "26", -1, &z, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
			DrawText(hdcEMF, IntToStr(lengthz - propil), -1, &z, DT_SINGLELINE | DT_LEFT | DT_CENTER);
			DrawText(hdcEMF, IntToStr(weightz - propil), -1, &z, DT_SINGLELINE | DT_LEFT | DT_VCENTER);
		}
		//Двадцать седьмой кусок
		if (countPiece > 26)  // в следующем куске 30
		{
			FillRect(hdcEMF, &xx, hBrushKusok);
			FrameRgn(hdcEMF, hRgnxx, hBrushFrame, 3, 3);
			DrawText(hdcEMF, "27", -1, &xx, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
			DrawText(hdcEMF, IntToStr(lengthxx - propil), -1, &xx, DT_SINGLELINE | DT_LEFT | DT_CENTER);
			DrawText(hdcEMF, IntToStr(weightxx - propil), -1, &xx, DT_SINGLELINE | DT_LEFT | DT_VCENTER);
		}
		//Двадцать восьмой кусок
		if (countPiece > 27)  // в следующем куске 30
		{

			FillRect(hdcEMF, &ww, hBrushKusok);
			FrameRgn(hdcEMF, hRgnww, hBrushFrame, 3, 3);
			DrawText(hdcEMF, "28", -1, &ww, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
			DrawText(hdcEMF, IntToStr(lengthww - propil), -1, &ww, DT_SINGLELINE | DT_LEFT | DT_CENTER);
			DrawText(hdcEMF, IntToStr(weightww - propil), -1, &ww, DT_SINGLELINE | DT_LEFT | DT_VCENTER);
		}
		//Двадцать девятый кусок
		if (countPiece > 28)  // в следующем куске 30
		{
			FillRect(hdcEMF, &ee, hBrushKusok);
			FrameRgn(hdcEMF, hRgnee, hBrushFrame, 3, 3);
			DrawText(hdcEMF, "29", -1, &ee, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
			DrawText(hdcEMF, IntToStr(lengthee - propil), -1, &ee, DT_SINGLELINE | DT_LEFT | DT_CENTER);
			DrawText(hdcEMF, IntToStr(weightee - propil), -1, &ee, DT_SINGLELINE | DT_LEFT | DT_VCENTER);
		}
		//Тридцатый кусок
		if (countPiece > 29)  // в следующем куске 30
		{
			FillRect(hdcEMF, &yy, hBrushKusok);
			FrameRgn(hdcEMF, hRgnyy, hBrushFrame, 3, 3);
			DrawText(hdcEMF, "30", -1, &yy, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
			DrawText(hdcEMF, IntToStr(lengthyy - propil), -1, &yy, DT_SINGLELINE | DT_LEFT | DT_CENTER);
			DrawText(hdcEMF, IntToStr(weightyy - propil), -1, &yy, DT_SINGLELINE | DT_LEFT | DT_VCENTER);
		}

	
//#########################################################################################################

		DeleteObject(hRgnRam1);
		DeleteObject(hRgnRam2);
		DeleteObject(hRgnRam3);
		DeleteObject(hRgnRam4);
		DeleteObject(hRgna);
		DeleteObject(hRgnb);
		DeleteObject(hRgnc);
		DeleteObject(hRgnd);
		DeleteObject(hRgne);
		DeleteObject(hRgnf);
		DeleteObject(hRgng);
		DeleteObject(hRgnh);
		DeleteObject(hRgni);
		DeleteObject(hRgnj);
		DeleteObject(hRgnk);
		DeleteObject(hRgnl);
		DeleteObject(hRgnm);
		DeleteObject(hRgnn);
		DeleteObject(hRgno);
		DeleteObject(hRgnp);
		DeleteObject(hRgnq);
		DeleteObject(hRgnrr);
		DeleteObject(hRgns);
		DeleteObject(hRgnt);
		DeleteObject(hRgnu);
		DeleteObject(hRgnv);
		DeleteObject(hRgnw);
		DeleteObject(hRgnx);
		DeleteObject(hRgny);
		DeleteObject(hRgnz);
		DeleteObject(hRgnxx);
		DeleteObject(hRgnww);
		DeleteObject(hRgnee);
		DeleteObject(hRgnyy);

		DeleteObject(hBrush);
		DeleteObject(hBrushIshod);
		DeleteObject(hBrushKusok);
		DeleteObject(hBrushFrame);
		DeleteObject(hPen);
		DeleteObject(hFont);

		DeleteObject(hDC);
		EndPaint(hWnd, &ps);

	

		return 0;
		


		// Cоздание кнопки "Добавить"
	case WM_CREATE: // сообщение создания окна 

		hInst = ((LPCREATESTRUCT)lParam)->hInstance; //получение дескриптора приложения


		hBtn1 = CreateWindow("button", "+",
			WS_CHILD | WS_VISIBLE | WS_BORDER,
			500, 25, 20, 20, hWnd, 0, hInst, NULL);

		// Cоздание кнопки "-"
		hBtn2 = CreateWindow("button", "-",
			WS_CHILD | WS_VISIBLE | WS_BORDER,
			470, 25, 20, 20, hWnd, 0, hInst, NULL);
		

		// Cоздание кнопки "Создать исходник"
		hBtn3 = CreateWindow("button", "Создать",
			WS_CHILD | WS_VISIBLE | WS_BORDER,
			300, 25, 100, 25, hWnd, 0, hInst, NULL);

	

		// Создаем и показываем первое поле редактирования
		hEdt1 = CreateWindow("edit", "",
			WS_CHILD | WS_VISIBLE | WS_BORDER | ES_RIGHT, 900, 30 + (-nPos), 60, 20,
			hWnd, 0, hInst, NULL);

	

		// Создаем и показываем третье поле редактирования
		hEdt3 = CreateWindow("edit", "",
			WS_CHILD | WS_VISIBLE | WS_BORDER | ES_RIGHT, 50, 30 + (-nPos), 45, 20,
			hWnd, 0, hInst, NULL);
		//ShowWindow(hEdt3, SW_SHOWNORMAL);
		// Создаем и показываем четвертое поле редактирования
		hEdt4 = CreateWindow("edit", "",
			WS_CHILD | WS_VISIBLE | WS_BORDER | ES_RIGHT, 180, 30 + (-nPos), 45,
			20, hWnd, 0, hInst, NULL);
		//ShowWindow(hEdt4, SW_SHOWNORMAL);

		//Статическое поле для площади исходника
		hStat = CreateWindow("static", "0", WS_CHILD | WS_VISIBLE | WS_BORDER,
			645, 30 + (-nPos), 45, 20, hWnd, 0, hInst, NULL);
		ShowWindow(hStat, SW_SHOWNORMAL);

		//Статическое поле для стоимости исходника
		hStatCena = CreateWindow("static", "0", WS_CHILD | WS_VISIBLE | WS_BORDER,
			780, 30 + (-nPos), 60, 20, hWnd, 0, hInst, NULL);
		ShowWindow(hStat, SW_SHOWNORMAL);

		//#######################################################################################################

		


		break;




	case WM_COMMAND:  // сообщение о команде
		//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

		if (LOWORD(wParam) == IDMyOpenMetaFileNew) //Eсли нажали кнопку "Открыть"
		{
	

			GetOpenFileName(&ofn);

			HWND hMeta1;
			int count;
			int dlina;
			char ch;
			TCHAR StrCountPiece[20];
			TCHAR StrLentish[20];
			TCHAR StrWeigtish[20];
			TCHAR StrL[20];
			TCHAR StrW[20];
			TCHAR StrLb[20];
			TCHAR StrWb[20];
			TCHAR StrLc[20];
			TCHAR StrWc[20];
			TCHAR StrLd[20];
			TCHAR StrWd[20];
			TCHAR StrLe[20];
			TCHAR StrWe[20];
			TCHAR StrLf[20];
			TCHAR StrWf[20];
			TCHAR StrLg[20];
			TCHAR StrWg[20];
			TCHAR StrLh[20];
			TCHAR StrWh[20];
			TCHAR StrLi[20];
			TCHAR StrWi[20];
			TCHAR StrLj[20];
			TCHAR StrWj[20];
			TCHAR StrLk[20];
			TCHAR StrWk[20];
			TCHAR StrLl[20];
			TCHAR StrWl[20];
			TCHAR StrLm[20];
			TCHAR StrWm[20];
			TCHAR StrLn[20];
			TCHAR StrWn[20];
			TCHAR StrLo[20];
			TCHAR StrWo[20];
			TCHAR StrLp[20];
			TCHAR StrWp[20];
			TCHAR StrLq[20];
			TCHAR StrWq[20];
			TCHAR StrLrr[20];
			TCHAR StrWrr[20];
			TCHAR StrLs[20];
			TCHAR StrWs[20];
			TCHAR StrLt[20];
			TCHAR StrWt[20];
			TCHAR StrLu[20];
			TCHAR StrWu[20];
			TCHAR StrLv[20];
			TCHAR StrWv[20];
			TCHAR StrLw[20];
			TCHAR StrWw[20];
			TCHAR StrLx[20];
			TCHAR StrWx[20];
			TCHAR StrLy[20];
			TCHAR StrWy[20];
			TCHAR StrLz[20];
			TCHAR StrWz[20];
			TCHAR StrLxx[20];
			TCHAR StrWxx[20];
			TCHAR StrLww[20];
			TCHAR StrWww[20];
			TCHAR StrLee[20];
			TCHAR StrWee[20];
			TCHAR StrLyy[20];
			TCHAR StrWyy[20];

	        TCHAR Strmas[20];

			TCHAR Strsquar[20];

			std::string str;


			fin.open(ofn.lpstrFile);
		
			if (!fin.is_open())
	
			{
				MessageBox(hWnd, " Файл не найден.", "Error", MB_OK);
			}
			else
			{
		

				fin.eof();
				fin >> StrCountPiece;
				countPiece = StrToInt(StrCountPiece);


				fin >> StrLentish;
				lengthIshodnic = StrToInt(StrLentish);
				fin >> StrWeigtish;
				widthIshodnic = StrToInt(StrWeigtish);

				fin >> StrL;
				length = StrToInt(StrL);
				fin >> StrW;
				weight = StrToInt(StrW);

				fin >> StrLb;
				lengthb = StrToInt(StrLb);
				fin >> StrWb;
				weightb = StrToInt(StrWb);

				fin >> StrLc;
				lengthc = StrToInt(StrLc);
				fin >> StrWc;
				weightc = StrToInt(StrWc);

				fin >> StrLd;
				lengthd = StrToInt(StrLd);
				fin >> StrWd;
				weightd = StrToInt(StrWd);

				fin >> StrLe;
				lengthe = StrToInt(StrLe);
				fin >> StrWe;
				weighte = StrToInt(StrWe);

				fin >> StrLf;
				lengthf = StrToInt(StrLf);
				fin >> StrWf;
				weightf = StrToInt(StrWf);

				fin >> StrLg;
				lengthg = StrToInt(StrLg);
				fin >> StrWg;
				weightg = StrToInt(StrWg);

				fin >> StrLh;
				lengthh = StrToInt(StrLh);
				fin >> StrWh;
				weighth = StrToInt(StrWh);

				fin >> StrLi;
				lengthi = StrToInt(StrLi);
				fin >> StrWi;
				weighti = StrToInt(StrWi);

				fin >> StrLj;
				lengthj = StrToInt(StrLj);
				fin >> StrWj;
				weightj = StrToInt(StrWj);

				fin >> StrLk;
				lengthk = StrToInt(StrLk);
				fin >> StrWk;
				weightk = StrToInt(StrWk);

				fin >> StrLl;
				lengthl = StrToInt(StrLl);
				fin >> StrWl;
				weightl = StrToInt(StrWl);

				fin >> StrLm;
				lengthm = StrToInt(StrLm);
				fin >> StrWm;
				weightm = StrToInt(StrWm);


				fin >> StrLn;
				lengthn = StrToInt(StrLn);
				fin >> StrWn;
				weightn = StrToInt(StrWn);

				fin >> StrLo;
				lengtho = StrToInt(StrLo);
				fin >> StrWo;
				weighto = StrToInt(StrWo);

				fin >> StrLp;
				lengthp = StrToInt(StrLp);
				fin >> StrWp;
				weightp = StrToInt(StrWp);

				fin >> StrLq;
				lengthq = StrToInt(StrLq);
				fin >> StrWq;
				weightq = StrToInt(StrWq);

				fin >> StrLrr;
				lengthrr = StrToInt(StrLrr);
				fin >> StrWrr;
				weightrr = StrToInt(StrWrr);

				fin >> StrLs;
				lengths = StrToInt(StrLs);
				fin >> StrWs;
				weights = StrToInt(StrWs);

				fin >> StrLt;
				lengtht = StrToInt(StrLt);
				fin >> StrWt;
				weightt = StrToInt(StrWt);


				fin >> StrLu;
				lengthu = StrToInt(StrLu);
				fin >> StrWu;
				weightu = StrToInt(StrWu);


				fin >> StrLv;
				lengthv = StrToInt(StrLv);
				fin >> StrWv;
				weightv = StrToInt(StrWv);

				fin >> StrLw;
				lengthw = StrToInt(StrLw);
				fin >> StrWw;
				weightw = StrToInt(StrWw);

				fin >> StrLx;
				lengthx = StrToInt(StrLx);
				fin >> StrWx;
				weightx = StrToInt(StrWx);

				fin >> StrLy;
				lengthy = StrToInt(StrLy);
				fin >> StrWy;
				weighty = StrToInt(StrWy);

				fin >> StrLz;
				lengthz = StrToInt(StrLz);
				fin >> StrWz;
				weightz = StrToInt(StrWz);

				fin >> StrLxx;
				lengthxx = StrToInt(StrLxx);
				fin >> StrWxx;
				weightxx = StrToInt(StrWxx);

				fin >> StrLww;
				lengthww = StrToInt(StrLww);
				fin >> StrWww;
				weightww = StrToInt(StrWww);

				fin >> StrLee;
				lengthee = StrToInt(StrLee);
				fin >> StrWee;
				weightee = StrToInt(StrWee);

				fin >> StrLyy;
				lengthyy = StrToInt(StrLyy);
				fin >> StrWyy;
				weightyy = StrToInt(StrWyy);

				fin >> Strmas;
				mas = StrToInt(Strmas);

				fin >> Strsquar;
				squar = StrToInt(Strsquar);


				fin.close();
		
			}
			
			open = 1;

			InvalidateRect(0, 0, 0);
		}


		if (LOWORD(wParam) == IDMyCreatMetaFileNew)  // Если нажали кнопку "Создать"
		{
		
			GetSaveFileName(&ofn);

			fout.open(ofn.lpstrFile);

		
			fout.close();
		
		}
		//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@



		if (LOWORD(wParam) == IDMySaveMetaFileNew)    // Если нажали кнопку "Сохранить"
		{
			GetSaveFileName(&ofn);
		
			fout.open(ofn.lpstrFile);
			if (!fout.is_open())
			{
				MessageBox(hWnd, " Файл не найден!!!.", "Error", MB_OK);
			}
		
	        flagMeta = 1;
			fout << countPiece << "\n";
			fout << lengthIshodnic << "\n";
			fout << widthIshodnic << "\n";
			fout << length << "\n";
	        fout << weight << "\n";
			fout << lengthb << "\n";
			fout << weightb << "\n";
			fout << lengthc << "\n";
			fout << weightc << "\n";
			fout << lengthd << "\n";
			fout << weightd << "\n";
			fout << lengthe << "\n";
			fout << weighte << "\n";
			fout << lengthf << "\n";
			fout << weightf << "\n";
			fout << lengthg << "\n";
			fout << weightg << "\n";
			fout << lengthh << "\n";
			fout << weighth << "\n";
			fout << lengthi << "\n";
			fout << weighti << "\n";
			fout << lengthj << "\n";
			fout << weightj << "\n";
			fout << lengthk << "\n";
			fout << weightk << "\n";
			fout << lengthl << "\n";
			fout << weightl << "\n";
			fout << lengthm << "\n";
			fout << weightm << "\n";
			fout << lengthn << "\n";
			fout << weightn << "\n";
			fout << lengtho << "\n";
			fout << weighto << "\n";
			fout << lengthp << "\n";
			fout << weightp << "\n";
			fout << lengthq << "\n";
			fout << weightq << "\n";
			fout << lengthrr << "\n";
			fout << weightrr << "\n";
			fout << lengths << "\n";
			fout << weights << "\n";
			fout << lengtht << "\n";
			fout << weightt << "\n";
			fout << lengthu << "\n";
			fout << weightu << "\n";
			fout << lengthv << "\n";
			fout << weightv << "\n";
			fout << lengthw << "\n";
			fout << weightw << "\n";
			fout << lengthx << "\n";
			fout << weightx << "\n";
			fout << lengthy << "\n";
			fout << weighty << "\n";
			fout << lengthz << "\n";
			fout << weightz << "\n";
			fout << lengthxx << "\n";
			fout << weightxx << "\n";
			fout << lengthww << "\n";
			fout << weightww << "\n";
			fout << lengthee << "\n";
			fout << weightee << "\n";
			fout << lengthyy << "\n";
			fout << weightyy << "\n";
			fout << mas << "\n";
			fout << squar << "\n";

		
			fout.close();


			hdcEMF = CreateEnhMetaFile(NULL, FILE_NAME, NULL, "CreateMetaFile\0Pict1\0");

			InvalidateRect(0, 0, 0); // Создаем сообщение WM_PAINT (первый аргумент 0 для стирания фона)
		}

		if (lParam == (LPARAM)hBtn1)    // если нажали на кнопку "+"
		{

			
			if(countPiece==0)// чтобы менять масштаб до добавления первого элемента
			{ 
			mas -= 100;
		
			InvalidateRect(0, 0, 0);
			}
			else
			{
				MessageBox(hWnd, "Менять масштаб можно только до добавления первого элемента",
					"", 0);
			}
		}


		if (lParam == (LPARAM)hBtn2)    // если нажали на кнопку "-"
		{
			if (countPiece == 0)// чтобы менять масштаб до добавления первого элемента
			{
				mas += 100;
			
				InvalidateRect(0, 0, 0);
			}
			else
			{
				MessageBox(hWnd, "Менять масштаб можно только до добавления первого элемента",
					"", 0);
			}
		}

		if (lParam == (LPARAM)hBtn3)    // если нажали на кнопку "Создать исходник"
		{


			len = GetWindowText(hEdt3, StrA, 20);
			lengthIshodnic = StrToInt(StrA); // считываем число из первого поля
			len = GetWindowText(hEdt4, StrA, 20);
			widthIshodnic = StrToInt(StrA); // считываем число из второго поля
			squar = (lengthIshodnic / 1000) * (widthIshodnic / 1000); //Площадь исходника (/1000 для перевода в м2) 
		

			//Определяем стоимость листа
			CenaI = GetWindowText(hEdt1, StrA, 20);
			CenaII = StrToInt(StrA);
			SetWindowText(hStatCena, DoubleToStr(((lengthIshodnic / 1000) * (widthIshodnic / 1000)*CenaII), 1));

			InvalidateRect(0, 0, 0); // Создаем сообщение WM_PAINT
		
		}

		if (LOWORD(wParam) == IDMyVIHOD)    // Обработка нажатия кнопки меню (1001 это ID кнопки "Выход"
		{

			userReply = MessageBox(hWnd, " Вы действительно хотите закрыть окно?",
				"", MB_YESNO | MB_ICONQUESTION);
			if (IDYES == userReply)
				DestroyWindow(hWnd);
		}

		if (LOWORD(wParam) == IDMyNEXTLIST)    // Обработка нажатия кнопки меню (IDMyNEXTLIST это ID кнопки "Следующий лист")
		{

			hwndNewList = CreateDialog(hInst,
				MAKEINTRESOURCE(IDD_DLG1),
				hWnd, (DLGPROC)WndNewListProc);
			ShowWindow(hwndNewList, SW_SHOW);
			

		}

		if (LOWORD(wParam) == AddToOne)    // Обработка нажатия кнопки меню (IDMyNEXTLIST это ID кнопки "Добавить кусок (по одному)")
		{

			hwndAddToOne = CreateDialog(hInst,
				MAKEINTRESOURCE(IDD_DLG2),
				hWnd, (DLGPROC)WndAddToOneProc);
			ShowWindow(hwndAddToOne, SW_SHOW);
			

		}

		if (LOWORD(wParam) == Povorot)    // Обработка нажатия меню "Поворот элемента"
		{

		
			hwndPovorot = CreateDialog(hInst,
				MAKEINTRESOURCE(IDD_DLG5),
				hWnd, (DLGPROC)PovorotProc);
			ShowWindow(hwndPovorot, SW_SHOW);
		

		}


		if (LOWORD(wParam) == Delete)    // Обработка нажатия меню "Удалить элемент"
		{

			hwndDelete = CreateDialog(hInst,
				MAKEINTRESOURCE(IDD_DLG4),
				hWnd, (DLGPROC)DELETEProc);
			ShowWindow(hwndSwap, SW_SHOW);
			
		}

		if (LOWORD(wParam) == Swap)    // Обработка нажатия меню "Заменить элемент"
		{
			
			hwndSwap = CreateDialog(hInst,
				MAKEINTRESOURCE(IDD_DLG3),
				hWnd, (DLGPROC)SWAPProc);
			ShowWindow(hwndSwap, SW_SHOW);
				
		}

		break;
	

	case WM_CLOSE:
		userReply = MessageBox(hWnd, " Сохранить изменения в документе?",
			"", MB_YESNO | MB_ICONQUESTION);
		if (IDYES == userReply)
		{
		
			GetSaveFileName(&ofn);
		
			fout.open(ofn.lpstrFile);
		
			flagMeta = 1;
			fout << countPiece << "\n";
			fout << lengthIshodnic << "\n";
			fout << widthIshodnic << "\n";
			fout << length << "\n";
			fout << weight << "\n";
			fout << lengthb << "\n";
			fout << weightb << "\n";
			fout << lengthc << "\n";
			fout << weightc << "\n";
			fout << lengthd << "\n";
			fout << weightd << "\n";
			fout << lengthe << "\n";
			fout << weighte << "\n";
			fout << lengthf << "\n";
			fout << weightf << "\n";
			fout << lengthg << "\n";
			fout << weightg << "\n";
			fout << lengthh << "\n";
			fout << weighth << "\n";
			fout << lengthi << "\n";
			fout << weighti << "\n";
			fout << lengthj << "\n";
			fout << weightj << "\n";
			fout << lengthk << "\n";
			fout << weightk << "\n";
			fout << lengthl << "\n";
			fout << weightl << "\n";
			fout << lengthm << "\n";
			fout << weightm << "\n";
			fout << lengthn << "\n";
			fout << weightn << "\n";
			fout << lengtho << "\n";
			fout << weighto << "\n";
			fout << lengthp << "\n";
			fout << weightp << "\n";
			fout << lengthq << "\n";
			fout << weightq << "\n";
			fout << lengthrr << "\n";
			fout << weightrr << "\n";
			fout << lengths << "\n";
			fout << weights << "\n";
			fout << lengtht << "\n";
			fout << weightt << "\n";
			fout << lengthu << "\n";
			fout << weightu << "\n";
			fout << lengthv << "\n";
			fout << weightv << "\n";
			fout << lengthw << "\n";
			fout << weightw << "\n";
			fout << lengthx << "\n";
			fout << weightx << "\n";
			fout << lengthy << "\n";
			fout << weighty << "\n";
			fout << lengthz << "\n";
			fout << weightz << "\n";
			fout << lengthxx << "\n";
			fout << weightxx << "\n";
			fout << lengthww << "\n";
			fout << weightww << "\n";
			fout << lengthee << "\n";
			fout << weightee << "\n";
			fout << lengthyy << "\n";
			fout << weightyy << "\n";
			fout << mas << "\n";
			fout << squar << "\n";
		
			fout.close();

			hdcEMF = CreateEnhMetaFile(NULL, FILE_NAME, NULL, "CreateMetaFile\0Pict1\0");

			InvalidateRect(0, 0, 0); // Создаем сообщение WM_PAINT (первый аргумент 0 для стирания фона)

			userReply = MessageBox(hWnd, "Закрыть?",
				"", MB_YESNO | MB_ICONQUESTION);
			if (IDYES == userReply)
			{ 
			DestroyWindow(hWnd);
			}
		break;
		}
		else
		{
			DestroyWindow(hWnd);
		}

	case WM_DESTROY:
		delete[] lpString;   // освобождаем память 
		delete[] lpStringCopy;

		lpString = nullptr;
		lpStringCopy = nullptr;
	
		hemf = CloseEnhMetaFile(hdcEMF);   
		DeleteEnhMetaFile(hemf);
		PostQuitMessage(0);
		break;
	default:

		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	
	}

	

	return 0;

	

}
//////////////////////////////////////////////////////////////////////

// Оконная процедура для диалогового окна "Следующий лист"


DLGPROC CALLBACK WndNewListProc(HWND hwndNewList, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_CLOSE:

		DestroyWindow(hwndNewList);
		hwndNewList = NULL;
	
		break;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:


			lengthIshodnic = GetDlgItemInt(hwndNewList, IDC_EDIT1,
				0, 0);
			widthIshodnic = GetDlgItemInt(hwndNewList, IDC_EDIT2,
				0, 0);
			squar = (lengthIshodnic / 1000) * (widthIshodnic / 1000); //Площадь исходника (/1000 для перевода в м2) 

			InvalidateRect(0, 0, 0);
	

			break;

		case IDCANCEL:

			EndDialog(hwndNewList, wParam);
			break;
		}

	}
	return (DLGPROC)FALSE;

}

DLGPROC CALLBACK WndAddToOneProc(HWND hwndAddToOne, UINT messageToOne, WPARAM wParam, LPARAM lParam)
{

	switch (messageToOne)
	{
	case WM_CLOSE:

		DestroyWindow(hwndAddToOne);
		hwndAddToOne = NULL;

		break;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOKAddToOne:

			len1 = GetDlgItemInt(hwndAddToOne, IDC_EDITAddToOneWeght, 0, 0);
			len2 = GetDlgItemInt(hwndAddToOne, IDC_EDITAddToOneLenght, 0, 0);

			squarPiece = ((len1 + propil) / 1000) * ((len2 + propil) / 1000);

			SetWindowText(GetDlgItem(hwndAddToOne, IDC_STATIC), DoubleToStr(squarPiece, 2)); //Выводим площадь куска
		
			InvalidateRect(0, 0, 0);
		
			++countPiece;
			break;

		case IDCANCELAddtoOne:

			EndDialog(hwndAddToOne, wParam);
			break;
		}

	}
	return (DLGPROC)FALSE;

}

DLGPROC CALLBACK SWAPProc(HWND hwndSwap, UINT messageSwap, WPARAM wParam, LPARAM lParam)
{
	int lenSwap1;
	int lenSwap2;
	double xl;
	double yl;
	double xw;
	double yw;
	double swap1; //length
	double swap2; //weight
	double swap3; //lengthb
	double swap4;

	switch (messageSwap)
	{
	case WM_CLOSE:

		DestroyWindow(hwndSwap);
		hwndSwap = NULL;
	
		break;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOKSwap:

			
			lenSwap1 = GetDlgItemInt(hwndSwap, IDC_SWAP1, 0, 0);
			lenSwap2 = GetDlgItemInt(hwndSwap, IDC_SWAP2, 0, 0);

			
				if (lenSwap1 == 1)
				{
					xl = length;
					xw = weight;
				}
	
				else if(lenSwap1 == 2)
				{
					xl = lengthb;
					xw = weightb;
				}
				else if (lenSwap1 == 3)
				{
					xl = lengthc;
					xw = weightc;
				}
				else if (lenSwap1 == 4)
				{
					xl = lengthd;
					xw = weightd;
				}
				else if (lenSwap1 == 5)
				{
					xl = lengthe;
					xw = weighte;
				}
				else if (lenSwap1 == 6)
				{
					xl = lengthf;
					xw = weightf;
				}
				else if (lenSwap1 == 7)
				{
					xl = lengthg;
					xw = weightg;
				}
				else if (lenSwap1 == 8)
				{
					xl = lengthh;
					xw = weighth;
				}
				else if (lenSwap1 == 9)
				{
					xl = lengthi;
					xw = weighti;
				}
				else if (lenSwap1 == 10)
				{
					xl = lengthj;
					xw = weightj;
				}
				else if (lenSwap1 == 11)
				{
					xl = lengthk;
					xw = weightk;
				}
				else if (lenSwap1 == 12)
				{
					xl = lengthl;
					xw = weightl;
				}
				else if (lenSwap1 == 13)
				{
					xl = lengthm;
					xw = weightm;
				}
				else if (lenSwap1 == 14)
				{
					xl = lengthn;
					xw = weightn;
				}
				else if (lenSwap1 == 15)
				{
					xl = lengtho;
					xw = weighto;
				}
				else if (lenSwap1 == 16)
				{
					xl = lengthp;
					xw = weightp;
				}
				else if (lenSwap1 == 17)
				{
					xl = lengthq;
					xw = weightq;
				}
				else if (lenSwap1 == 18)
				{
					xl = lengthrr;
					xw = weightrr;
				}
				else if (lenSwap1 == 19)
				{
					xl = lengths;
					xw = weights;
				}
				else if (lenSwap1 == 20)
				{
					xl = lengtht;
					xw = weightt;
				}
				else if (lenSwap1 == 21)
				{
				xl = lengthu;
				xw = weightu;
				}
				else if (lenSwap1 == 22)
				{
				xl = lengthv;
				xw = weightv;
				}
				else if (lenSwap1 == 23)
				{
				xl = lengthw;
				xw = weightw;
				}
				else if (lenSwap1 == 24)
				{
				xl = lengthx;
				xw = weightx;
				}
				else if (lenSwap1 == 25)
				{
				xl = lengthy;
				xw = weighty;
				}
				else if (lenSwap1 == 26)
				{
				xl = lengthz;
				xw = weightz;
				}
				else if (lenSwap1 == 27)
				{
				xl = lengthxx;
				xw = weightxx;
				}
				else if (lenSwap1 == 28)
				{
				xl = lengthww;
				xw = weightww;
				}
				else if (lenSwap1 == 29)
				{
				xl = lengthee;
				xw = weightee;
				}
				else if (lenSwap1 == 30)
				{
				xl = lengthyy;
				xw = weightyy;
				}

		

				else
				{
					MessageBox(hwndSwap, "Нет такого элемента", "", 0);
					return 0;
				}

				if (lenSwap2 == 1)
				{
					yl = length;
					yw = weight;
				}

				else if (lenSwap2 == 2)
				{
					yl = lengthb;
					yw = weightb;
				}
				else if (lenSwap2 == 3)
				{
					yl = lengthc;
					yw = weightc;
				}
				else if (lenSwap2 == 4)
				{
					yl = lengthd;
					yw = weightd;
				}
				else if (lenSwap2 == 5)
				{
					yl = lengthe;
					yw = weighte;
				}
				else if (lenSwap2 == 6)
				{
					yl = lengthf;
					yw = weightf;
				}
				else if (lenSwap2 == 7)
				{
					yl = lengthg;
					yw = weightg;
				}
				else if (lenSwap2 == 8)
				{
					yl = lengthh;
					yw = weighth;
				}
				else if (lenSwap2 == 9)
				{
					yl = lengthi;
					yw = weighti;
				}
				else if (lenSwap2 == 10)
				{
					yl = lengthj;
					yw = weightj;
				}
				else if (lenSwap2 == 11)
				{
					yl = lengthk;
					yw = weightk;
				}
				else if (lenSwap2 == 12)
				{
					yl = lengthl;
					yw = weightl;
				}
				else if (lenSwap2 == 13)
				{
					yl = lengthm;
					yw = weightm;
				}
				else if (lenSwap2 == 14)
				{
					yl = lengthn;
					yw = weightn;
				}
				else if (lenSwap2 == 15)
				{
					yl = lengtho;
					yw = weighto;
				}
				else if (lenSwap2 == 16)
				{
					yl = lengthp;
					yw = weightp;
				}
				else if (lenSwap2 == 17)
				{
					yl = lengthq;
					yw = weightq;
				}
				else if (lenSwap2 == 18)
				{
					yl = lengthrr;
					yw = weightrr;
				}
				else if (lenSwap2 == 19)
				{
					yl = lengths;
					yw = weights;
				}
				else if (lenSwap2 == 20)
				{
					yl = lengtht;
					yw = weightt;
				}
				else if (lenSwap2 == 21)
				{
				yl = lengthu;
				yw = weightu;
				}
				else if (lenSwap2 == 22)
				{
				yl = lengthv;
				yw = weightv;
				}
				else if (lenSwap2 == 23)
				{
				yl = lengthw;
				yw = weightw;
				}
				else if (lenSwap2 == 24)
				{
				yl = lengthx;
				yw = weightx;
				}
				else if (lenSwap2 == 25)
				{
				yl = lengthy;
				yw = weighty;
				}
				else if (lenSwap2 == 26)
				{
				yl = lengthz;
				yw = weightz;
				}
				else if (lenSwap2 == 27)
				{
				yl = lengthxx;
				yw = weightxx;
				}
				else if (lenSwap2 == 28)
				{
				yl = lengthww;
				yw = weightww;
				}
				else if (lenSwap2 == 29)
				{
				yl = lengthee;
				yw = weightee;
				}
				else if (lenSwap2 == 30)
				{
				yl = lengthyy;
				yw = weightyy;
				}

				else
				{
					MessageBox(hwndSwap, "Нет такого элемента", "", 0);
					return 0;
				}
					
				swap1 = xl; //length
				swap2 = xw; //weight
				swap3 = yl; //lengthb
				 swap4 = yw; //weightb
				yl = swap1;
				yw = swap2;
				xl = swap3;
				xw = swap4;

				if (lenSwap1 == 1)
				{
					 length =xl;
					 weight= xw;
				}

				else if (lenSwap1 == 2)
				{
					lengthb = xl;
					weightb = xw;
				}
				else if (lenSwap1 == 3)
				{
					lengthc = xl;
					weightc = xw;
				}
				else if (lenSwap1 == 4)
				{
					lengthd = xl;
					weightd = xw;
				}
				else if (lenSwap1 == 5)
				{
					lengthe = xl;
					weighte = xw;
				}
				else if (lenSwap1 == 6)
				{
					lengthf = xl;
					weightf = xw;
				}
				else if (lenSwap1 == 7)
				{
					lengthg = xl;
					weightg = xw;
				}
				else if (lenSwap1 == 8)
				{
					lengthh = xl;
					weighth = xw;
				}
				else if (lenSwap1 == 9)
				{
					lengthi = xl;
					weighti = xw;
				}
				else if (lenSwap1 == 10)
				{
					lengthj = xl;
					weightj = xw;
				}
				else if (lenSwap1 == 11)
				{
					lengthk = xl;
					weightk = xw;
				}
				else if (lenSwap1 == 12)
				{
					lengthl = xl;
					weightl = xw;
				}
				else if (lenSwap1 == 13)
				{
					lengthm = xl;
					weightm = xw;
				}
				else if (lenSwap1 == 14)
				{
					lengthn = xl;
					weightn = xw;
				}
				else if (lenSwap1 == 15)
				{
					lengtho = xl;
					weighto = xw;
				}
				else if (lenSwap1 == 16)
				{
					lengthp = xl;
					weightp = xw;
				}
				else if (lenSwap1 == 17)
				{
					lengthq = xl;
					weightq = xw;
				}
				else if (lenSwap1 == 18)
				{
					lengthrr = xl;
					weightrr = xw;
				}
				else if (lenSwap1 == 19)
				{
					lengths = xl;
					weights = xw;
				}
				else if (lenSwap1 == 20)
				{
					lengtht = xl;
					weightt = xw;
				}
				else if (lenSwap1 == 21)
				{
				lengthu = xl;
				weightu = xw;
				}
				else if (lenSwap1 == 22)
				{
				lengthv = xl;
				weightv = xw;
				}
				else if (lenSwap1 == 23)
				{
				lengthw = xl;
				weightw = xw;
				}
				else if (lenSwap1 == 24)
				{
				lengthx = xl;
				weightx = xw;
				}
				else if (lenSwap1 == 25)
				{
				lengthy = xl;
				weighty = xw;
				}
				else if (lenSwap1 == 26)
				{
				lengthz = xl;
				weightz = xw;
				}
				else if (lenSwap1 == 27)
				{
				lengthxx = xl;
				weightxx = xw;
				}
				else if (lenSwap1 == 28)
				{
				lengthww = xl;
				weightww = xw;
				}
				else if (lenSwap1 == 29)
				{
				lengthee = xl;
				weightee = xw;
				}
				else if (lenSwap1 == 30)
				{
				lengthyy = xl;
				weightyy = xw;
				}

				else
				{
					MessageBox(hwndSwap, "Нет такого элемента", "", 0);
					return 0;
				}

				if (lenSwap2 == 1)
				{
					 length= yl;
					 weight =yw;
				}

				else if (lenSwap2 == 2)
				{
					lengthb = yl;
					weightb = yw;
				}
				else if (lenSwap2 == 3)
				{
					lengthc = yl;
					weightc = yw;
				}
				else if (lenSwap2 == 4)
				{
					lengthd = yl;
					weightd = yw;
				}
				else if (lenSwap2 == 5)
				{
					lengthe = yl;
					weighte = yw;
				}
				else if (lenSwap2 == 6)
				{
					lengthf = yl;
					weightf = yw;
				}
				else if (lenSwap2 == 7)
				{
					lengthg = yl;
					weightg = yw;
				}
				else if (lenSwap2 == 8)
				{
					lengthh = yl;
					weighth = yw;
				}
				else if (lenSwap2 == 9)
				{
					lengthi = yl;
					weighti = yw;
				}
				else if (lenSwap2 == 10)
				{
					lengthj = yl;
					weightj = yw;
				}
				else if (lenSwap2 == 11)
				{
					lengthk = yl;
					weightk = yw;
				}
				else if (lenSwap2 == 12)
				{
					lengthl = yl;
					weightl = yw;
				}
				else if (lenSwap2 == 13)
				{
					lengthm = yl;
					weightm = yw;
				}
				else if (lenSwap2 == 14)
				{
					lengthn = yl;
					weightn = yw;
				}
				else if (lenSwap2 == 15)
				{
					lengtho = yl;
					weighto = yw;
				}
				else if (lenSwap2 == 16)
				{
					lengthp = yl;
					weightp = yw;
				}
				else if (lenSwap2 == 17)
				{
					lengthq = yl;
					weightq = yw;
				}
				else if (lenSwap2 == 18)
				{
					lengthrr = yl;
					weightrr = yw;
				}
				else if (lenSwap2 == 19)
				{
					lengths = yl;
					weights = yw;
				}
				else if (lenSwap2 == 20)
				{
					lengtht = yl;
					weightt = yw;
				}
				else if (lenSwap2 == 21)
				{
				lengthu = yl;
				weightu = yw;
				}
				else if (lenSwap2 == 22)
				{
				lengthv = yl;
				weightv = yw;
				}
				else if (lenSwap2 == 23)
				{
				lengthw = yl;
				weightw = yw;
				}
				else if (lenSwap2 == 24)
				{
				lengthx = yl;
				weightx = yw;
				}
				else if (lenSwap2 == 25)
				{
				lengthy = yl;
				weighty = yw;
				}
				else if (lenSwap2 == 26)
				{
				lengthz = yl;
				weightz = yw;
				}
				else if (lenSwap2 == 27)
				{
				lengthxx = yl;
				weightxx = yw;
				}
				else if (lenSwap2 == 28)
				{
				lengthww = yl;
				weightww = yw;
				}
				else if (lenSwap2 == 29)
				{
				lengthee = yl;
				weightee = yw;
				}
				else if (lenSwap2 == 30)
				{
				lengthyy = yl;
				weightyy = yw;
				}


				else
				{
					MessageBox(hwndSwap, "Нет такого элемента", "", 0);
					return 0;
				}
				InvalidateRect(0, 0, 0);
				
			break;

		case IDCANCELSwap:

			EndDialog(hwndSwap, wParam);
			break;
		}

	}
	return (DLGPROC)FALSE;

}

DLGPROC CALLBACK PovorotProc(HWND hwndPovorot, UINT messagePovorot, WPARAM wParam, LPARAM lParam)
{
	int lenPovorot;
	double povorot1;
	double povorot2;

	switch (messagePovorot)
	{
	case WM_CLOSE:

		DestroyWindow(hwndPovorot);
		hwndPovorot = NULL;
	
		break;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOKPovorot:


			lenPovorot = GetDlgItemInt(hwndPovorot, IDC_EDITPovorot, 0, 0);
		
			if (lenPovorot == 1)
			{
				

				povorot1=length;
				povorot2=weight;
				weight = povorot1;
				length= povorot2;
				
			}

			else if (lenPovorot == 2)
			{
				
				povorot1 = lengthb;
				povorot2 = weightb;
				weightb = povorot1;
				lengthb = povorot2;
				
			}
			else if (lenPovorot == 3)
			{
				
				povorot1 = lengthc;
				povorot2 = weightc;
				weightc = povorot1;
				lengthc = povorot2;
				
			}
			else if (lenPovorot == 4)
			{

				povorot1 = lengthd;
				povorot2 = weightd;
				weightd = povorot1;
				lengthd = povorot2;

			}
			else if (lenPovorot == 5)
			{

				povorot1 = lengthe;
				povorot2 = weighte;
				weighte = povorot1;
				lengthe = povorot2;

			}
			else if (lenPovorot == 6)
			{

				povorot1 = lengthf;
				povorot2 = weightf;
				weightf = povorot1;
				lengthf = povorot2;

			}
			else if (lenPovorot == 7)
			{

				povorot1 = lengthg;
				povorot2 = weightg;
				weightg = povorot1;
				lengthg = povorot2;

			}
			else if (lenPovorot == 8)
			{

				povorot1 = lengthh;
				povorot2 = weighth;
				weighth = povorot1;
				lengthh = povorot2;

			}
			else if (lenPovorot == 9)
			{

				povorot1 = lengthi;
				povorot2 = weighti;
				weighti = povorot1;
				lengthi = povorot2;

			}
			else if (lenPovorot == 10)
			{

				povorot1 = lengthj;
				povorot2 = weightj;
				weightj = povorot1;
				lengthj = povorot2;

			}
			else if (lenPovorot == 11)
			{

				povorot1 = lengthk;
				povorot2 = weightk;
				weightk = povorot1;
				lengthk = povorot2;

			}
			else if (lenPovorot == 12)
			{

			povorot1 = lengthl;
			povorot2 = weightl;
			weightl = povorot1;
			lengthl = povorot2;

			}
			else if (lenPovorot == 13)
			{

			povorot1 = lengthm;
			povorot2 = weightm;
			weightm = povorot1;
			lengthm = povorot2;

			}
			else if (lenPovorot == 14)
			{

			povorot1 = lengthn;
			povorot2 = weightn;
			weightn = povorot1;
			lengthn = povorot2;

			}
			else if (lenPovorot == 15)
			{
			povorot1 = lengtho;
			povorot2 = weighto;
			weighto = povorot1;
			lengtho = povorot2;
			}
			else if (lenPovorot == 16)
			{
			povorot1 = lengthp;
			povorot2 = weightp;
			weightp = povorot1;
			lengthp = povorot2;
			}
			else if (lenPovorot == 17)
			{
			povorot1 = lengthq;
			povorot2 = weightq;
			weightq = povorot1;
			lengthq = povorot2;
			}
			else if (lenPovorot == 18)
			{
			povorot1 = lengthrr;
			povorot2 = weightrr;
			weightrr = povorot1;
			lengthrr = povorot2;
			}
			else if (lenPovorot == 19)
			{
			povorot1 = lengths;
			povorot2 = weights;
			weights = povorot1;
			lengths = povorot2;
			}
			else if (lenPovorot == 20)
			{
			povorot1 = lengtht;
			povorot2 = weightt;
			weightt = povorot1;
			lengtht = povorot2;
			}
			else if (lenPovorot == 21)
			{
			povorot1 = lengthu;
			povorot2 = weightu;
			weightu = povorot1;
			lengthu = povorot2;
			}
			else if (lenPovorot == 22)
			{
			povorot1 = lengthv;
			povorot2 = weightv;
			weightv = povorot1;
			lengthv = povorot2;
			}
			else if (lenPovorot == 23)
			{
			povorot1 = lengthw;
			povorot2 = weightw;
			weightw = povorot1;
			lengthw = povorot2;
			}
			else if (lenPovorot == 24)
			{
			povorot1 = lengthx;
			povorot2 = weightx;
			weightx = povorot1;
			lengthx = povorot2;
			}
			else if (lenPovorot == 25)
			{
			povorot1 = lengthy;
			povorot2 = weighty;
			weighty = povorot1;
			lengthy = povorot2;
			}
			else if (lenPovorot == 26)
			{
			povorot1 = lengthz;
			povorot2 = weightz;
			weightz = povorot1;
			lengthz = povorot2;
			}
			else if (lenPovorot == 27)
			{
			povorot1 = lengthxx;
			povorot2 = weightxx;
			weightxx = povorot1;
			lengthxx = povorot2;
			}
			else if (lenPovorot == 28)
			{
			povorot1 = lengthww;
			povorot2 = weightww;
			weightww = povorot1;
			lengthww = povorot2;
			}
			else if (lenPovorot == 29)
			{
			povorot1 = lengthee;
			povorot2 = weightee;
			weightee = povorot1;
			lengthee = povorot2;
			}
			else if (lenPovorot == 30)
			{
			povorot1 = lengthyy;
			povorot2 = weightyy;
			weightyy = povorot1;
			lengthyy = povorot2;
			}

			else
			{
				MessageBox(hwndPovorot, "Нет такого элемента", "", 0);
				return 0;
			}
		
			InvalidateRect(0, 0, 0);		
			break;

		case IDCANCELPovorot:

			EndDialog(hwndPovorot, wParam);
			break;
		}

	}
	return (DLGPROC)FALSE;
}

DLGPROC CALLBACK DELETEProc(HWND hwndDelete, UINT messageDelete, WPARAM wParam, LPARAM lParam)
{
	int lenDelete1;

	switch (messageDelete)
	{
	case WM_CLOSE:

		DestroyWindow(hwndDelete);
		hwndDelete = NULL;
		break;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDDELETEOK:


			lenDelete1 = GetDlgItemInt(hwndDelete, IDC_DELETE1, 0, 0);
	
			if (lenDelete1 == 1)
			{
				double plo = ((length + propil) / 1000) * ((weight + propil) / 1000);

				length = 1;
				weight = 1;
				squar += plo;
			}

			else if (lenDelete1 == 2)
			{
				double plo = ((lengthb + propil) / 1000) * ((weightb + propil) / 1000);
				lengthb = 1;
				weightb = 1;
				squar += plo;
			}
			else if (lenDelete1 == 3)
			{
				double plo = ((lengthc + propil) / 1000) * ((weightc + propil) / 1000);
				lengthc = 1;
				weightc = 1;
				squar += plo;
			}
			else if (lenDelete1 == 4)
			{
				double plo = ((lengthd + propil) / 1000) * ((weightd + propil) / 1000);
				lengthd = 1;
				weightd = 1;
				squar += plo;
			}
			else if (lenDelete1 == 5)
			{
				double plo = ((lengthe + propil) / 1000) * ((weighte + propil) / 1000);
				lengthe = 1;
				weighte = 1;
				squar += plo;
			}
			else if (lenDelete1 == 6)
			{
				double plo = ((lengthf + propil) / 1000) * ((weightf + propil) / 1000);
				lengthf = 1;
				weightf = 1;
				squar += plo;
			}
			else if (lenDelete1 == 7)
			{
				double plo = ((lengthg + propil) / 1000) * ((weightg + propil) / 1000);
				lengthg = 1;
				weightg = 1;
				squar += plo;
			}
			else if (lenDelete1 == 8)
			{
				double plo = ((lengthh + propil) / 1000) * ((weighth + propil) / 1000);
				lengthh = 1;
				weighth = 1;
				squar += plo;
			}
			else if (lenDelete1 == 9)
			{
				double plo = ((lengthi + propil) / 1000) * ((weighti + propil) / 1000);
				lengthi = 1;
				weighti = 1;
				squar += plo;
			}
			else if (lenDelete1 == 10)
			{
				double plo = ((lengthj + propil) / 1000) * ((weightj + propil) / 1000);
				lengthj = 1;
				weightj = 1;
				squar += plo;
			}
			else if (lenDelete1 == 11)
			{
				double plo = ((lengthk + propil) / 1000) * ((weightk + propil) / 1000);
				lengthk = 1;
				weightk = 1;
				squar += plo;
			}
			else if (lenDelete1 == 12)
			{
				double plo = ((lengthl + propil) / 1000) * ((weightl + propil) / 1000);
				lengthl = 1;
				weightl = 1;
				squar += plo;
			}
			else if (lenDelete1 == 13)
			{
				double plo = ((lengthm + propil) / 1000) * ((weightm + propil) / 1000);
				lengthm = 1;
				weightm = 1;
				squar += plo;
			}
			else if (lenDelete1 == 14)
			{
				double plo = ((lengthn + propil) / 1000) * ((weightn + propil) / 1000);
				lengthn = 1;
				weightn = 1;
				squar += plo;
			}
			else if (lenDelete1 == 15)
			{
				double plo = ((lengtho + propil) / 1000) * ((weighto + propil) / 1000);
				lengtho = 1;
				weighto = 1;
				squar += plo;
			}
			else if (lenDelete1 == 16)
			{
				double plo = ((lengthp + propil) / 1000) * ((weightp + propil) / 1000);
				lengthp = 1;
				weightp = 1;
				squar += plo;
			}
			else if (lenDelete1 == 17)
			{
				double plo = ((lengthq + propil) / 1000) * ((weightq + propil) / 1000);
				lengthq = 1;
				weightq = 1;
				squar += plo;
			}
			else if (lenDelete1 == 18)
			{
				double plo = ((lengthrr + propil) / 1000) * ((weightrr + propil) / 1000);
				lengthrr = 1;
				weightrr = 1;
				squar += plo;
			}
			else if (lenDelete1 == 19)
			{
				double plo = ((lengths + propil) / 1000) * ((weights + propil) / 1000);
				lengths = 1;
				weights = 1;
				squar += plo;
			}
			else if (lenDelete1 == 20)
			{
				double plo = ((lengtht + propil) / 1000) * ((weightt + propil) / 1000);
				lengtht = 1;
				weightt = 1;
				squar += plo;
			}
			else if (lenDelete1 == 21)
			{
				double plo = ((lengthu + propil) / 1000) * ((weightu + propil) / 1000);
				lengthu = 1;
				weightu = 1;
				squar += plo;
			}
			else if (lenDelete1 == 22)
			{
				double plo = ((lengthv + propil) / 1000) * ((weightv + propil) / 1000);
				lengthv = 1;
				weightv = 1;
				squar += plo;
			}
			else if (lenDelete1 == 23)
			{
				double plo = ((lengthw + propil) / 1000) * ((weightw + propil) / 1000);
				lengthw = 1;
				weightw = 1;
				squar += plo;
			}
			else if (lenDelete1 == 24)
			{
				double plo = ((lengthx + propil) / 1000) * ((weightx + propil) / 1000);
				lengthx = 1;
				weightx = 1;
				squar += plo;
			}
			else if (lenDelete1 == 25)
			{
				double plo = ((lengthy + propil) / 1000) * ((weighty + propil) / 1000);
				lengthy = 1;
				weighty = 1;
				squar += plo;
			}
			else if (lenDelete1 == 26)
			{
				double plo = ((lengthz + propil) / 1000) * ((weightz + propil) / 1000);
				lengthz = 1;
				weightz = 1;
				squar += plo;
			}
			else if (lenDelete1 == 27)
			{
				double plo = ((lengthxx + propil) / 1000) * ((weightxx + propil) / 1000);
				lengthxx = 1;
				weightxx = 1;
				squar += plo;
			}
			else if (lenDelete1 == 28)
			{
				double plo = ((lengthww + propil) / 1000) * ((weightww + propil) / 1000);
				lengthww = 1;
				weightww = 1;
				squar += plo;
			}
			else if (lenDelete1 == 29)
			{
				double plo = ((lengthee + propil) / 1000) * ((weightee + propil) / 1000);
				lengthee = 1;
				weightee = 1;
				squar += plo;
			}
			else if (lenDelete1 == 30)
			{
				double plo = ((lengthyy + propil) / 1000) * ((weightyy + propil) / 1000);
				lengthyy = 1;
				weightyy = 1;
				squar += plo;
			}

			else
			{
				MessageBox(hwndDelete, "Нет такого элемента", "", 0);
				return 0;
			}

			InvalidateRect(0, 0, 0);
	

			break;
		case IDDELETECANCEL:
			EndDialog(hwndDelete, wParam);
			break;
		}
	}
	return (DLGPROC)FALSE;
}
