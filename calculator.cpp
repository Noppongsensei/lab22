#include <windows.h>
#include <cstdio>
HWND text,button1,button2,button3,button4,button5,a;

/* This is where all the input to the window goes to */
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch(Message) {
		
		case WM_CREATE:{
			text = CreateWindow("STATIC"," Please input two numbers",WS_VISIBLE|WS_CHILD|WS_BORDER,35,20,180,25,hwnd,NULL,NULL,NULL);
			button1 =CreateWindow("BUTTON","+",WS_VISIBLE|WS_CHILD|WS_BORDER,45,110,40,25,hwnd,(HMENU) 1,NULL,NULL);
			button2=CreateWindow("BUTTON","-",WS_VISIBLE|WS_CHILD|WS_BORDER,85,110,40,25,hwnd,(HMENU) 2,NULL,NULL);
			button3=CreateWindow("BUTTON","*",WS_VISIBLE|WS_CHILD|WS_BORDER,125,110,40,25,hwnd,(HMENU) 3,NULL,NULL);
			button4=CreateWindow("BUTTON","/",WS_VISIBLE|WS_CHILD|WS_BORDER,165,110,40,25,hwnd,(HMENU) 4,NULL,NULL);
			button5=CreateWindow("EDIT","",WS_BORDER|WS_CHILD|WS_VISIBLE,35,50,150,25,hwnd,NULL,NULL,NULL);
			a=CreateWindow("EDIT","",WS_BORDER|WS_CHILD|WS_VISIBLE,35,80,150,25,hwnd,NULL,NULL,NULL);
    		SetClassLongPtr(hwnd, GCLP_HBRBACKGROUND, (LONG_PTR)CreateSolidBrush(RGB(250,1, 20)));
		}
		case WM_COMMAND: {

			switch (LOWORD(wParam)) { 
				case 1:{
				char num1[256], num2[256],buffer[256];
				GetWindowText(button5, num1, 256);
				GetWindowText(a, num2, 256);
				double Result1= atof(num1) + atof(num2);
				sprintf(buffer, "Result = %.2f", Result1);
				::MessageBox(hwnd,buffer,"Result", MB_OK | MB_ICONINFORMATION);
				break;
				}
				case 2:{
				char num3[256], num4[256],buffer1[256];
				GetWindowText(button5, num3, 256);
				GetWindowText(a, num4, 256);
				double Result2= atof(num3) - atof(num4);
				sprintf(buffer1, "Result = %.2f", Result2);
				::MessageBox(hwnd,buffer1,"Result", MB_OK | MB_ICONINFORMATION);
				break;
				}
				case 3:{
				char num5[256], num6[256],buffer2[256];
				GetWindowText(button5, num5, 256);
				GetWindowText(a, num6, 256);
				double Result3= atof(num5) * atof(num6);
				sprintf(buffer2, "Result = %.2f", Result3);
				::MessageBox(hwnd,buffer2,"Result", MB_OK | MB_ICONINFORMATION);
				break;
				}
				case 4:{
				char num7[256], num8[256],buffer3[256];
				GetWindowText(button5, num7, 256);
				GetWindowText(a, num8, 256);
				double Result4= atof(num7) / atof(num8);
				sprintf(buffer3, "Result = %.2f", Result4);
				::MessageBox(hwnd,buffer3,"Result", MB_OK | MB_ICONINFORMATION);
				break;
				}
			}
			
			break;
		}
		
		/* Upon destruction, tell the main thread to stop */
		case WM_DESTROY: {
			PostQuitMessage(0);
			break;
		}
		
		/* All other messages (a lot of them) are processed using default procedures */
		default:
			return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}

/* The 'main' function of Win32 GUI programs: this is where execution starts */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	WNDCLASSEX wc; /* A properties struct of our window */
	HWND hwnd; /* A 'HANDLE', hence the H, or a pointer to our window */
	MSG msg; /* A temporary location for all messages */

	/* zero out the struct and set the stuff we want to modify */
	memset(&wc,0,sizeof(wc));
	wc.cbSize	 = sizeof(WNDCLASSEX);
	wc.lpfnWndProc	 = WndProc; /* This is where we will send messages to */
	wc.hInstance	 = hInstance;
	wc.hCursor	 = LoadCursor(NULL, IDC_ARROW);
	
	/* White, COLOR_WINDOW is just a #define for a system color, try Ctrl+Clicking it */
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	wc.lpszClassName = "WindowClass";
	wc.hIcon	 = LoadIcon(NULL, IDI_APPLICATION); /* Load a standard icon */
	wc.hIconSm	 = LoadIcon(NULL, IDI_APPLICATION); /* use the name "A" to use the project icon */

	if(!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Window Registration Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE,"WindowClass","My Calculator",WS_VISIBLE|WS_SYSMENU,
		CW_USEDEFAULT, /* x */
		CW_USEDEFAULT, /* y */
		250, /* width */
		200, /* height */
		NULL,NULL,hInstance,NULL);

	if(hwnd == NULL) {
		MessageBox(NULL, "Window Creation Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	/*
		This is the heart of our program where all input is processed and 
		sent to WndProc. Note that GetMessage blocks code flow until it receives something, so
		this loop will not produce unreasonably high CPU usage
	*/
	while(GetMessage(&msg, NULL, 0, 0) > 0) { /* If no error is received... */
		TranslateMessage(&msg); /* Translate key codes to chars if present */
		DispatchMessage(&msg); /* Send it to WndProc */
	}
	return msg.wParam;
}
