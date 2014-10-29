
// FlashToCocosXDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "FlashToCocosX.h"
#include "FlashToCocosXDlg.h"
#include "afxdialogex.h"
#include "tinyxml.h"
#include <vector>
#include <map>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


#define M_PI 3.14159265387

using namespace std;
// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CFlashToCocosXDlg 对话框



CFlashToCocosXDlg::CFlashToCocosXDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFlashToCocosXDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFlashToCocosXDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CFlashToCocosXDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CFlashToCocosXDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CFlashToCocosXDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CFlashToCocosXDlg 消息处理程序

BOOL CFlashToCocosXDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CFlashToCocosXDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CFlashToCocosXDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CFlashToCocosXDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CFlashToCocosXDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CFlashToCocosXDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
    CFileDialog dlg(TRUE, //TRUE为OPEN对话框，FALSE为SAVE AS对话框
        NULL, 
        NULL,
        OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
        (LPCTSTR)_TEXT("XML Files (*.xml)|*.xml|All Files (*.*)|*.*||"),
        NULL);
    if(dlg.DoModal()==IDOK)
    {
        selectFilePath=dlg.GetPathName(); //文件名保存在了FilePathName里
		SetDlgItemText(IDC_STATIC,selectFilePath.GetString());
    }
    else
    {
         return;
    }
}


void CFlashToCocosXDlg::readXml(const std::string &filename)
{
	
	TiXmlDocument *docFile = new TiXmlDocument();
	docFile->LoadFile((LPSTR)(LPCTSTR)selectFilePath);
	TiXmlHandle docHandle(docFile);
    
    TiXmlElement *layeritem = docHandle.FirstChild("DOMDocument").FirstChild("timelines").FirstChild("DOMTimeline").FirstChild("layers").FirstChild("DOMLayer").ToElement();

	 //NSMutableArray *frameArr = [NSMutableArray new];
	 while ( layeritem != NULL ) {

        const char *layerName = layeritem->Attribute("name");
 
        TiXmlElement *frameElement = layeritem->FirstChildElement("frames")->FirstChildElement("DOMFrame");
		std::map<std::string ,std::string> frameDict;
        while (frameElement != NULL) {
            
            // 当前第几帧
            const char *index = frameElement->Attribute("index");
            const char *name = frameElement->Attribute("name");
            const char  *isKeyFrame = "0";
            if (name){
                isKeyFrame = "1";
            }
            // 这帧循环几帧 默认0次 也就是不循环
            const char *duration = frameElement->Attribute("duration");
			string frameTimes = duration != NULL ? duration: "0";
            // 这帧的数据
            TiXmlElement *frameData = frameElement->FirstChildElement("elements")->FirstChildElement("DOMSymbolInstance");


            //NSMutableArray *frameArr = [NSMutableArray new];
			std::vector<std::map<string,string>> frameArr;
            while (frameData != NULL) {
                
                //NSMutableDictionary *elementDict = [NSMutableDictionary new];
                std::map<std::string ,std::string> elementDict;
                // 当前帧 用到的图片 
                const char *libraryItemName = frameData->Attribute("libraryItemName");
                //NSString *pngName  = [NSString stringWithCString:libraryItemName encoding:NSUTF8StringEncoding];
				frameArr.insert("bitmapName", libraryItemName);
                //[elementDict setObject:pngName forKey:@"bitmapName"];

                ////  Matrix 部分
                
                string scaleY	= "1";
                string scaleX	= "1";
                string rota		= "0";
                float txFloat = 0;
                float tyFloat = 0;
                
                TiXmlElement *matrixData = frameData->FirstChildElement("matrix");
                if(matrixData != NULL){
                    matrixData = matrixData->FirstChildElement("Matrix");
                    if (matrixData!= NULL ){
                        
                        const char *a = matrixData->Attribute("a");
                        const char *b = matrixData->Attribute("b");
                        const char *c = matrixData->Attribute("c");
                        const char *d = matrixData->Attribute("d");
                        
						string aStr = a != NULL ? a:"1";
                        string bStr = b != NULL ? b:"0";
                        string cStr = c != NULL ? c:"0";
                        string dStr = d != NULL ? d:"1";
                                              
						rota = this->getRotationByA(aStr,bStr,cStr,dStr);
                        scaleY = this->getScaleYByA(aStr,bStr,cStr,dStr);
                        scaleX = this->getScaleXByA(aStr,bStr,cStr,dStr);
  
                        elementDict.insert("scaleX", scaleX.c_str());
						elementDict.insert("scaleY", scaleY.c_str());
						elementDict.insert("rotation", rota.c_str());
                        
                        const char *tx = matrixData->Attribute("tx");
						string txStr   = tx != NULL ? tx:"0";
                      
                        const char *ty = matrixData->Attribute("ty");
						string tyStr   = ty != NULL ? ty:"0";
                   
                        elementDict.insert("positionX", txStr.c_str());
						elementDict.insert("positionY", tyStr.c_str());
                    }
                }
                
                //  color部分
                TiXmlElement *colorData = frameData->FirstChildElement("color");
                if (colorData != NULL){
                    colorData = colorData->FirstChildElement("Color");
                    if (colorData!= NULL){
                        const char *alphaMultiplier = colorData->Attribute("alphaMultiplier");
                        string alpha = alphaMultiplier != NULL ? alphaMultiplier:"1";
                        elementDict.insert("alpha", alpha.c_str()); 
                    }
                }
				frameArr.push_back(elementDict);
                frameData = frameData->NextSiblingElement();
            }
			

            frameDict.insert() 
            //[frameDict setObject:frameArr forKey:[NSString stringWithFormat:@"%@",frameNum]];
            //[frameDict setObject:isKeyFrame forKey:[NSString stringWithFormat:@"%@_isKeyFrame",frameNum]];
            

            if ([frameTimes intValue] > 0){               
                for (int i=0 ; i<[frameTimes intValue];i++){
                    int frameIndex =  [frameNum intValue] + i;
                    [frameDict setObject:frameArr forKey:[NSString stringWithFormat:@"%d",frameIndex]];
                    if (frameIndex > layerNum){
                        layerNum = frameIndex;
                    }
                }
            }else {
                layerNum = [frameNum intValue] ;
            }            

            [frameArr release];

            frameElement = frameElement->NextSiblingElement();
        }

        [self writeXMlForLayerName:layerName dict:frameDict];
        
        [frameDict release];
        
        layeritem = layeritem->NextSiblingElement();
    }
}


//-(NSString *)getRotationByA:(NSString *)_a B:(NSString *)_b C:(NSString *)_c D:(NSString *)_d{
string CFlashToCocosXDlg::getRotationByA(const string &_a, const string &_b, const string &_c, const string &_d)
{
	float aa = atof(_a.c_str());
	float bb = atof(_b.c_str());
	float cc = atof(_c.c_str());
	float dd = atof(_d.c_str());


    if (bb > 0){
        aabb = sqrt((aa * aa + bb * bb));
    }else {
        aabb = -sqrt((aa * aa + bb * bb));
    }
    
    double cos_a = aa / aabb;
    float rota = acosf(cos_a) * 180 / M_PI;
    NSLog(@"rota = %f",rota);
    return [NSString stringWithFormat:@"%f",rota];

}

//-(NSString *)getScaleXByA:(NSString *)_a B:(NSString *)_b C:(NSString *)_c D:(NSString *)_d{
string CFlashToCocosXDlg::getRotationByA(const string &_a, const string &_b, const string &_c, const string &_d)
{
	float aa = atof(_a.c_str());
	float bb = atof(_b.c_str());
	float cc = atof(_c.c_str());
	float dd = atof(_d.c_str());

	if (bb > 0){
		aabb = sqrt((aa * aa + bb * bb));
	}else {
		aabb = -sqrt((aa * aa + bb * bb));
	}

	double cos_a = aa / aabb;
	float rota = acosf(cos_a) * 180 / M_PI;
	printf("rota = %f",rota);
	char strSy[20];
	sprintf(strSy,"%f",rota);
	string sRota =  strSy;
	return  sRota;
}

string CFlashToCocosXDlg::getScaleYByA(const string &_a, const string &_b, const string &_c, const string &_d)
{
	float aa = atof(_a.c_str());
	float bb = atof(_b.c_str());
	float cc = atof(_c.c_str());
	float dd = atof(_d.c_str());

	if (dd == 0){
		dd = 1.0;
	}
	char strSy[20];
	sprintf(strSy,"%f", dd * aabb / aa);
	string sy = strSy;  
	return sy;
}

string CFlashToCocosXDlg::getScaleXByA(const string &_a, const string &_b, const string &_c, const string &_d)
{
	float aa = atof(_a.c_str());
	float bb = atof(_b.c_str());
	float cc = atof(_c.c_str());
	float dd = atof(_d.c_str());

	char strSy[20];
	sprintf(strSy,"%f", aabb);
	string sy = strSy;  
	return sy;
}