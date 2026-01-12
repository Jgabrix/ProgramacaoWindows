#define WIN32_LEAN_AND_MEAN
#include <windows.h>

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
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = "BasicWindow";





	//Restricao da window class
	if (!RegisterClass(&wndclass))
	{
		MessageBox(NULL, "Erro na criação da janela", "Aplicação", MB_ICONERROR);
		return 0;
	}

	//Criacao da janela baseada na window class
	hwnd = CreateWindow(
		"BasicWindow",
		"Aplicação",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL);


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
