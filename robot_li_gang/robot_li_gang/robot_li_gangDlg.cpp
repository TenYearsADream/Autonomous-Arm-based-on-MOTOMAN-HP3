
// robot_li_gangDlg.cpp : ʵ���ļ�
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


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// Crobot_li_gangDlg �Ի���




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


// Crobot_li_gangDlg ��Ϣ�������

BOOL Crobot_li_gangDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void Crobot_li_gangDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR Crobot_li_gangDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

int nCid;
void Crobot_li_gangDlg::OnBnClickedstart()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int result;            //���պ����ķ���ֵ 
	CString temp; 
	char path[]="E:\\";
	
	nCid=BscOpen(path,16);         //������ 
	if(nCid==0)           //�򿪳ɹ� 
	{ 
		HWND hWnd; 
		hWnd=this->m_hWnd;         //ȡ�ô��ھ�� 
		result=BscSetEther(nCid,"192.168.255.2",0,hWnd);  //������̫�� 
		if(result==1)          //������̫���ɹ� 
		{ 
			BscConnect(nCid);        //������̫�� 
			if(result!=1) 
			{
				temp= "����ʧ�ܣ�"; 
			} 
			else 
			{
				temp="���ӳɹ���"; 
			} 
			MessageBox(temp);
		} 
		else            
		{ 
			temp="��̫�����Ӵ���"; 
			MessageBox(temp);
		} 
	} 
	else  
	{ 
		temp="��̫�����ô���"; 
		MessageBox(temp);
	} 

	if(BscServoOn(nCid)==0)       //���ŷ���� 
	{ 
		temp="�ŷ��򿪳ɹ�"; 
	} 
	else 
	{ 
		temp="�ŷ���ʧ��"; 
	}  
	MessageBox(temp);
}


void Crobot_li_gangDlg::OnBnClickedstop()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString  temp;  
	int result=BscServoOff(nCid);       //�Ͽ��ŷ���� 
	if(result==0) 
	{
		temp="�ŷ��رճɹ�"; 
	} 
	else 
	{
		temp="�ŷ��ر�ʧ��"; 
	} 
	MessageBox(temp);

	BscDisConnect(nCid);        //�Ͽ����� 
	if(BscClose(nCid)==0) 
	{
		temp="���ӹرճɹ�"; 
	} 
	else 
	{
		temp="���ӹر�ʧ��"; 
	}
	MessageBox(temp);
}

list<Point> road;
void Crobot_li_gangDlg::OnBnClickedimage()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	//����
	vector<vector<Point>> contours1,contours2,contours3,contours4;
	vector<Vec4i> hierarchy;
	findContours(src_binary,contours1,hierarchy,CV_RETR_TREE,CHAIN_APPROX_NONE,Point(0,0));
	cout<<contours1.size();
	Mat src_new;
	src_new=ori.clone();
    //����ɸѡ
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
	drawContours(src_draw, contours2, 1, Scalar(255), CV_FILLED);//255�ǰ�ɫ
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	biaoding();
	char *framename="BASE"; //ѡ�����ؽ�����ϵ(��ֱ������ϵ)
	WORD rconf=0;
	short toolno=0; //���߱�ţ�һ���������Ϊ0
	short speed=4.0; //�������ƶ��ٶ�ռ�ؽ�����ٶȵİٷֱ�
	double dist; //λ�����
	static double p1[12]; //ʵʱ��ȡĩ��λ�úͽǶ�
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
	p[0]=x2;//Ŀ��λ�ùؽڽ� 
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
    while(1) //ȷ���ƶ�����ִ����� 
    { 
        BscIsLoc(nCid,0,&rconf,p1);//��ȡ�ؽڽ� 

        dist=sqrt((x2-p1[0])*(x2-p1[0])+(y2-p1[1])*(y2-p1[1])+(z2-p1[2])*(z2-p1[2])); 


        if(dist<=20) 
            break; 
    }
	}
	}

}
