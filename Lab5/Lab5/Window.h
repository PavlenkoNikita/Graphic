#pragma once
class Window
{
private:
	std::map<std::string, HWND> mapElemets;
	std::vector<Element>        elements;
	unsigned short				nElements;
	HINSTANCE                   hInstance;
	HWND                        hWnd;
	LPTSTR						name;
	LPTSTR						title;
	unsigned short				width;
	unsigned short				height;
	unsigned short				x;
	unsigned short				y;

	ATOM registerClass();
	BOOL InitInstance(HINSTANCE hInstance, int nCmdShow);
public:
	Window(HINSTANCE phInstance, LPTSTR pName, LPTSTR pTitle);
	Window(HINSTANCE phInstance);
	Window();

	void	  setSize(unsigned short pWidth, unsigned short pHeight);
	void	  setLocation(unsigned short pX, unsigned short pY);
	int		  run(int nCmdShow);
	void      addElement(std::string pKey, HWND pValue);
	HINSTANCE getHInstance();
	void      addElements(std::vector<Element> pElement, HWND hwnd);
	void	  moveElements(int pWidth, int pHeight = 0, int widthSettings = 100);
	int       getWidth();
	int       getHeight();
	HWND      getElement(std::string pKey);

	~Window();
};