#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <windowsx.h> // funcoes extras
#include "Resources.h"


//--------------------------------------------------------------
//Configuracoes basicas

int windowWidth = 800;					// largura da janela
int windowHeigth = 300;					// altura da janela
bool fullScreen = false;				// modo de exibicao

const unsigned MaxInputLength = 64;		// Tamanho maximo de texto
char msg[MaxInputLength] = { 0 };		// mensagem do sistema
bool vkKeys[256] = { 0 };				// estado das teclas

//--------------------------------------------------------------





//Window Procedure
LRESULT CALLBACK WinProc(HWND, UINT, WPARAM, LPARAM);




//Programa principal
int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	HWND hwnd;								//Identificador
	WNDCLASS wndclass;						//Window class
	MSG msg;								//Mensagem

	//Definicao da window class

	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WinProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON));
	wndclass.hCursor = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_CURSOR));
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = "GameWindow";





	//Restricao da window class
	if (!RegisterClass(&wndclass))
	{
		MessageBox(NULL, "Erro na criação da janela", "Aplicação", MB_ICONERROR);
		return 0;
	}
	
	int windowSytle = WS_OVERLAPPED | WS_SYSMENU;

	//Tela cheia ou janela
	if (fullScreen)
	{
		windowWidth = GetSystemMetrics(SM_CXSCREEN);
		windowHeigth = GetSystemMetrics(SM_CYSCREEN);
		windowSytle = WS_POPUP;
	}
	


	//Centralizar a janela na tela
	int windowPosX = GetSystemMetrics(SM_CXSCREEN) / 2 - windowWidth / 2;
	int windowPosY = GetSystemMetrics(SM_CYSCREEN) / 2 - windowHeigth / 2;



	//Criacao da janela baseada na window class
	hwnd = CreateWindowEx(
		NULL,
		"GameWindow",
		"Keyboard Input",
		WS_OVERLAPPED | WS_SYSMENU,
		windowPosX,
		windowPosY,
		windowWidth,
		windowHeigth,
		NULL,
		NULL,
		hInstance,
		NULL);


	//Modo janela

	if (!fullScreen)
	{

		//Retangulo com o tamanho da area cliente
		RECT winRect = { 0, 0, windowWidth, windowHeigth };


		//Ajuste do tamanho da janela
		AdjustWindowRectEx(
			&winRect,
			GetWindowStyle(hwnd),
			GetMenu(hwnd) != NULL,
			GetWindowExStyle(hwnd)
		);

		//Centralizar a janela
		windowPosX = (GetSystemMetrics(SM_CXSCREEN) / 2) - ((winRect.right - winRect.left) / 2);
		windowPosY = (GetSystemMetrics(SM_CYSCREEN) / 2) - ((winRect.bottom - winRect.top) / 2);


		//Redimensiona a janela
		MoveWindow(
			hwnd,
			windowPosX,
			windowPosY,
			winRect.right - winRect.left,
			winRect.bottom - winRect.top,
			TRUE);


	}


	
	//Exibicao da janela
	ShowWindow(hwnd, nCmdShow);

	//Atualizacao da janela
	UpdateWindow(hwnd);


	//Envio de mensagens para o tratamento de eventos
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	//Encerramento da janela
	return int(msg.wParam);
}

LRESULT CALLBACK WinProc(HWND hwnd, UINT message , WPARAM wParam, LPARAM lParam)
{
	HDC hdc;			// Pincel Virtual
	RECT rect;			// Defini a area do retangulo
	PAINTSTRUCT ps;		// Guarda regiao invalida da janela

	//Definir os tipos de eventos
	switch (message)
	{
	//janela perdeu foco
	case WM_KILLFOCUS:
		strcpy_s(msg, MaxInputLength, "Volte logo!");
		InvalidateRect(hwnd, NULL, TRUE);
		return 0;

	//janela ganhou foco
	case WM_SETFOCUS:
		strcpy_s(msg, MaxInputLength, "Bem vindo!");
		InvalidateRect(hwnd, NULL, TRUE);
		return 0;

	//tecla pressionada
	case WM_KEYDOWN:
		vkKeys[wParam] = true;
		InvalidateRect(hwnd, NULL, TRUE);
		return 0;

	//tecla liberada
	case WM_KEYUP:
		vkKeys[wParam] = false;
		InvalidateRect(hwnd, NULL, TRUE);
		return 0;
	
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		GetClientRect(hwnd, &rect);


		if (vkKeys[VK_CONTROL])
			DrawText(hdc, "CTRL", -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		if (vkKeys[VK_LEFT])
			DrawText(hdc, "LEFT", -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		if (vkKeys[VK_RIGHT])
			DrawText(hdc, "RIGHT", -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		if (vkKeys[VK_UP])
			DrawText(hdc, "UP", -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		if (vkKeys[VK_DOWN])
			DrawText(hdc, "DOWN", -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		if (vkKeys[VK_SPACE])
			DrawText(hdc, "SPACE", -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		if (vkKeys[VK_RETURN])
			DrawText(hdc, "ENTER", -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		if (vkKeys[VK_ESCAPE])
			DrawText(hdc, "ESC", -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

		rect.bottom -= 100;
		DrawText(hdc, msg, -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		EndPaint(hwnd, &ps);
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	}
		return DefWindowProc(hwnd, message, wParam, lParam);

	}

