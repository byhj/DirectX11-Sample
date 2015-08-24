#ifndef DXUTHELPER
#define DXUTHELPER



namespace byhj
{

class DXUTHelper
{
public:
	DXUTHelper();
	~DXUTHelper();

public:
	void Init();
	void Render();
	void Shutdown();

private:
	int m_ScreenWidth = 0;
	int m_ScreenHeight = 0;
};

}

#endif