
// robot_li_gangDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "robot_li_gang.h"
#include "robot_li_gangDlg.h"
#include "afxdialogex.h"
#include "direct.h"
#include "motocom.h"
#include <conio.h>
#include "FGCamera.h"
#include <math.h>
#include <iostream>  
#include <fstream>
#include <string>
#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/legacy/legacy.hpp>

#include "function.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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


// Crobot_li_gangDlg 对话框




Crobot_li_gangDlg::Crobot_li_gangDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(Crobot_li_gangDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_x1 = _T("");
	m_y1 = _T("");
	m_z1 = _T("");
	m_x2 = _T("");
	m_y2 = _T("");
	m_z2 = _T("");

	m_th1 = _T("");
	m_th2 = _T("");
	m_th3 = _T("");
	m_th4 = _T("");
	m_th5 = _T("");
	m_th6 = _T("");
}

void Crobot_li_gangDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Control(pDX, IDC_EDIT1, m_x1);
	DDX_Text(pDX, IDC_EDIT1, m_x1);
	DDX_Text(pDX, IDC_EDIT2, m_y1);
	DDX_Text(pDX, IDC_EDIT3, m_z1);
	//  DDX_Control(pDX, IDC_EDIT4, m_x2);
	DDX_Text(pDX, IDC_EDIT4, m_x2);
	DDX_Text(pDX, IDC_EDIT5, m_y2);
	DDX_Text(pDX, IDC_EDIT6, m_z2);

	DDX_Text(pDX, IDC_EDIT7, m_th1);
	DDX_Text(pDX, IDC_EDIT8, m_th2);
	DDX_Text(pDX, IDC_EDIT9, m_th3);

	DDX_Text(pDX, IDC_EDIT10, m_th4);
	DDX_Text(pDX, IDC_EDIT11, m_th5);
	DDX_Text(pDX, IDC_EDIT12, m_th6);
}

BEGIN_MESSAGE_MAP(Crobot_li_gangDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_start, &Crobot_li_gangDlg::OnBnClickedstart)
	ON_BN_CLICKED(IDC_stop, &Crobot_li_gangDlg::OnBnClickedstop)
	ON_BN_CLICKED(IDC_image, &Crobot_li_gangDlg::OnBnClickedimage)
	ON_BN_CLICKED(IDC_go, &Crobot_li_gangDlg::OnBnClickedgo)
END_MESSAGE_MAP()


// Crobot_li_gangDlg 消息处理程序

BOOL Crobot_li_gangDlg::OnInitDialog()
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

void Crobot_li_gangDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void Crobot_li_gangDlg::OnPaint()
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
HCURSOR Crobot_li_gangDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

int nCid;
void Crobot_li_gangDlg::OnBnClickedstart()
{
	// TODO: 在此添加控件通知处理程序代码
	int result;            //接收函数的返回值 
	CString temp; 
	char path[]="E:\\";
	
	nCid=BscOpen(path,16);         //打开连接 
	if(nCid==0)           //打开成功 
	{ 
		HWND hWnd; 
		hWnd=this->m_hWnd;         //取得窗口句柄 
		result=BscSetEther(nCid,"192.168.255.2",0,hWnd);  //设置以太网 
		if(result==1)          //设置以太网成功 
		{ 
			BscConnect(nCid);        //连接以太网 
			if(result!=1) 
			{
				temp= "连接失败！"; 
			} 
			else 
			{
				temp="连接成功！"; 
			} 
			MessageBox(temp);
		} 
		else            
		{ 
			temp="以太网连接错误"; 
			MessageBox(temp);
		} 
	} 
	else  
	{ 
		temp="以太网设置错误"; 
		MessageBox(temp);
	} 

	if(BscServoOn(nCid)==0)       //打开伺服电机 
	{ 
		temp="伺服打开成功"; 
	} 
	else 
	{ 
		temp="伺服打开失败"; 
	}  
	MessageBox(temp);
}


void Crobot_li_gangDlg::OnBnClickedstop()
{
	// TODO: 在此添加控件通知处理程序代码
	CString  temp;  
	int result=BscServoOff(nCid);       //断开伺服电机 
	if(result==0) 
	{
		temp="伺服关闭成功"; 
	} 
	else 
	{
		temp="伺服关闭失败"; 
	} 
	MessageBox(temp);

	BscDisConnect(nCid);        //断开连接 
	if(BscClose(nCid)==0) 
	{
		temp="连接关闭成功"; 
	} 
	else 
	{
		temp="连接关闭失败"; 
	}
	MessageBox(temp);
}

list<Point> road;
void Crobot_li_gangDlg::OnBnClickedimage()
{
	// TODO: 在此添加控件通知处理程序代码
	Mat src=imread("maze.jpg");
	waitKey();
	int newrows=(int)src.rows/10;
	int newcols=(int)src.cols/10;
	Mat ori;
	resize(src,ori,Size(newrows,newcols),0,0);
	//ori=src.clone();
	imshow("orig",ori);
	Mat src_Gray;
	Mat src_binary;
	cvtColor(ori,src_Gray,COLOR_BGR2GRAY);
	threshold(src_Gray,src_binary,100,255,THRESH_BINARY|THRESH_OTSU);
	//imshow("binary",src_Gray);
	//cvWaitKey();
	//轮廓
	vector<vector<Point>> contours1,contours2,contours3,contours4;
	vector<Vec4i> hierarchy;
	findContours(src_binary,contours1,hierarchy,CV_RETR_TREE,CHAIN_APPROX_NONE,Point(0,0));
	cout<<contours1.size();
	Mat src_new;
	src_new=ori.clone();
    //轮廓筛选
	int count=0;
	int flag;
	for(int i=0;i<contours1.size();i++)
	{
		if((hierarchy[i][2]!=-1)&&count==0)
		{
			flag=i;
			count++;
		}
		else if(count!=0)
		{
			count++;
		}
		else if(hierarchy[i][2]==-1)
		{
			count=0;
			flag=-1;
		}
		flag=i;
		while (hierarchy[flag][2]!=-1)
		{
			flag=hierarchy[flag][2];
			count++;
		}
		if(count>=2)
		{
			contours2.push_back(contours1[i]);
			count=0;
		}
		else count=0;
	}
		for(int i=0;i<contours1.size();i++)
	{
		drawContours(src_new,contours1,i,CV_RGB(0,255,0));
	}
	
	//cout<<contours2.size();
	//imshow("result1",src_new);
	//waitKey();
	Mat src_draw=Mat::zeros(src_new.rows,src_new.cols,CV_8UC1);
	drawContours(src_draw, contours2, 1, Scalar(255), CV_FILLED);//255是白色
    //imshow("result",src_draw);
	bitwise_and(src_draw,src_Gray,src_draw);
	drawContours(src_draw,contours2,1,CV_RGB(0,0,0));
	Mat src_result;
	Mat src_10;
	//imshow("real",src_draw);
	threshold(src_draw,src_10,128,1,THRESH_BINARY);
	//imshow("bi",src_10);
	Mat dst=thinImage(src_10);
	dst = dst*255;
	imshow("line",dst);
	waitKey();
	
	vector<Point> midline;
	vector<vector<int>> map(ori.rows);
	for (int i=0;i<src_new.rows;i++)
	{
		uchar* data=dst.ptr<uchar>(i);
		map[i].resize(ori.cols);
		for(int j=0;j<src_new.cols;j++)
		{
			if(data[j]!=0)
				{
					midline.push_back(Point(i,j));
			        map[i][j]=1;
			    }
			else map[i][j]=0;
		}
	}
	cout<<midline;
	
	Point start(6,15);
	Point end(36,9);
	maze(start,end,road,map);
	if(!road.empty())
	{
	list<Point>::iterator itor;
	itor = road.begin();
	while(itor!=road.end())
	{
		cout << (*itor).x << "," << (*itor).y << endl;
		itor++;
	}
	}
	
}


void Crobot_li_gangDlg::OnBnClickedgo()
{
	// TODO: 在此添加控件通知处理程序代码
	biaoding();
	char *framename="BASE"; //选择腰关节坐标系(即直角坐标系)
	WORD rconf=0;
	short toolno=0; //工具编号，一般情况下设为0
	short speed=4.0; //机器人移动速度占关节最大速度的百分比
	double dist; //位置误差
	static double p1[12]; //实时读取末端位置和角度
	static double p[12];
	
	if(!road.empty())
	{
	list<Point>::iterator itor;
	itor = road.begin();
	while (itor != road.end())
	{
    double x=(*itor).x;
	double y=(*itor).y;
	double x2=ImagetoReal(x,y,1);
	double y2=ImagetoReal(x,y,0);
	double z2=80;
	itor++;
	p[0]=x2;//目标位置关节角 
    p[1]=y2; 
    p[2]=z2; 
    p[3]=179; 
    p[4]=-2.9; 
    p[5]=10; 
    p[6]=0; 
    p[7]=0; 
    p[8]=0; 
    p[9]=0; 
    p[10]=0; 
    p[11]=0; 

    BscMovj(nCid,speed,framename,rconf,toolno,p); 
    while(1) //确保移动命令执行完毕 
    { 
        BscIsLoc(nCid,0,&rconf,p1);//读取关节角 

        dist=sqrt((x2-p1[0])*(x2-p1[0])+(y2-p1[1])*(y2-p1[1])+(z2-p1[2])*(z2-p1[2])); 


        if(dist<=20) 
            break; 
    }
	}
	}

}
