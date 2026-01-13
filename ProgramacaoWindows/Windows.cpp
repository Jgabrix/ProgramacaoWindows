#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <windowsx.h> // funcoes extras
#include "Resources.h"

//Window Procedure
LRESULT CALLBACK WinProc(HWND, UINT, WPARAM, LPARAM);


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
	wndclass.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = "BasicWindow";





	//Restricao da window class
	if (!RegisterClass(&wndclass))
	{
		MessageBox(NULL, "Erro na criação da janela", "Aplicação", MB_ICONERROR);
		return 0;
	}

	//Tamanho da janela igual ao tamanho da tela
	int windowWidth = 960; //x
	int windowHeigth = 540;//y


	//Centralizar a janela na tela
	int windowPosX = GetSystemMetrics(SM_CXSCREEN) / 2 - windowWidth / 2;
	int windowPosY = GetSystemMetrics(SM_CYSCREEN) / 2 - windowHeigth / 2;



	//Criacao da janela baseada na window class
	hwnd = CreateWindowEx(
		NULL,
		"BasicWindow",
		"Aplicação",
		WS_OVERLAPPED | WS_SYSMENU,
		windowPosX,
		windowPosY,
		windowWidth,
		windowHeigth,
		NULL,
		NULL,
		hInstance,
		NULL);


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
	windowPosX = (GetSystemMetrics(SM_CXSCREEN) / 2 ) - ( (winRect.right - winRect.left) / 2);
	windowPosY = (GetSystemMetrics(SM_CYSCREEN) / 2) - ((winRect.bottom - winRect.top) / 2);


	//Redimensiona a janela
	MoveWindow(
		hwnd,
		windowPosX,
		windowPosY,
		winRect.right - winRect.left,
		winRect.bottom - winRect.top,
		TRUE);

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

LRESULT CALLBACK WinProc(HWND hwnd, UINT mesagem , WPARAM wParam, LPARAM lParam)
{
	HDC hdc;			//Pincel Virtual
	RECT rect;			//Defini a area do retangulo
	PAINTSTRUCT ps;		//Operacoes

	//Definir os tipos de eventos
	switch (mesagem)
	{
		//Repintura
		case WM_PAINT: 
			hdc = BeginPaint(hwnd, &ps);

			GetClientRect(hwnd, &rect);
			DrawText(hdc, "Oi janela!", -1, &rect,DT_SINGLELINE | DT_CENTER | DT_VCENTER);

			EndPaint(hwnd, &ps);
			return 0;

		//Janela destruida
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
	}

	return DefWindowProc(hwnd, mesagem, wParam, lParam);


}
