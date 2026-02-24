#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
/* This is where all the input to the window goes to */
HWND textfield,button1,button2,button3,button4,TextBox,TextBox2;
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch(Message) {
		case WM_CREATE:
		textfield = CreateWindow("STATIC","Please input two numbers",WS_VISIBLE | WS_CHILD | WS_BORDER , 20,20,200,25,hwnd,NULL,NULL,NULL);
		button1 = CreateWindow("BUTTON","+",WS_VISIBLE | WS_CHILD | WS_BORDER,30,120,30,25,hwnd,(HMENU) 1,NULL,NULL);
		button2 = CreateWindow("BUTTON","-",WS_VISIBLE | WS_CHILD | WS_BORDER,80,120,30,25,hwnd,(HMENU) 2,NULL,NULL);
		button3 = CreateWindow("BUTTON","*",WS_VISIBLE | WS_CHILD | WS_BORDER,130,120,30,25,hwnd,(HMENU) 3,NULL,NULL);
		button4 = CreateWindow("BUTTON","/",WS_VISIBLE | WS_CHILD | WS_BORDER,180,120,30,25,hwnd,(HMENU) 4,NULL,NULL);
		TextBox = CreateWindow("EDIT","",WS_BORDER | WS_CHILD | WS_VISIBLE ,50,50,150,20,hwnd,NULL,NULL,NULL);
		TextBox2 = CreateWindow("EDIT","",WS_BORDER | WS_CHILD | WS_VISIBLE ,50,75,150,20,hwnd,NULL,NULL,NULL);
		


		break;
		
		case WM_COMMAND:
		
		char buf1[50], buf2[50], resultStr[100];
		double a, b, result;
		GetWindowText(TextBox, buf1, 50);
		GetWindowText(TextBox2, buf2, 50);

		a = atof(buf1);
		b = atof(buf2);
			switch(LOWORD(wParam)){
			case 1:
            result = a + b;
			sprintf(resultStr, "%f", result);
			MessageBox(hwnd, resultStr, "Result", MB_OK);
            break;

        	case 2: 
            result = a - b;
			sprintf(resultStr, "%f", result);
			MessageBox(hwnd, resultStr, "Result", MB_OK);
            break;

       	 	case 3: 
            result = a * b;
			sprintf(resultStr, "%f", result);
			MessageBox(hwnd, resultStr, "Result", MB_OK);
            break;

        	case 4: 
            if(b == 0) {
                MessageBox(hwnd, "Cannot divide by zero", "Error", MB_OK);
                return 0;
            }
            result = a / b;
			sprintf(resultStr, "%f", result);
			MessageBox(hwnd, resultStr, "Result", MB_OK);
            break;

			}
			
		
			break;
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
	wc.hbrBackground = CreateSolidBrush(RGB(256,55,25));
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