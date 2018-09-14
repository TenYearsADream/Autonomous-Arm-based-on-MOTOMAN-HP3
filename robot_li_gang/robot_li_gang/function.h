#include <opencv2\highgui\highgui.hpp>
#include <opencv2\core\core.hpp>
#include<opencv2/opencv.hpp>
#include<iostream>
#include <stdio.h>
#include <list> 
#include <cv.h>
using namespace cv;
using namespace std;

cv::Mat thinImage(const cv::Mat & src, const int maxIterations = -1)  
{  
    assert(src.type() == CV_8UC1);  
    cv::Mat dst;  
    int width  = src.cols;  
    int height = src.rows;  
    src.copyTo(dst);  
    int count = 0;  //��¼��������  
    while (true)  
    {  
        count++;  
        if (maxIterations != -1 && count > maxIterations) //���ƴ������ҵ�����������  
            break;  
        std::vector<uchar *> mFlag; //���ڱ����Ҫɾ���ĵ�  
        //�Ե���  
        for (int i = 0; i < height ;++i)  
        {  
            uchar * p = dst.ptr<uchar>(i);  
            for (int j = 0; j < width; ++j)  
            {  
                //��������ĸ����������б��  
                //  p9 p2 p3  
                //  p8 p1 p4  
                //  p7 p6 p5  
                uchar p1 = p[j];  
                if (p1 != 1) continue;  
                uchar p4 = (j == width - 1) ? 0 : *(p + j + 1);  
                uchar p8 = (j == 0) ? 0 : *(p + j - 1);  
                uchar p2 = (i == 0) ? 0 : *(p - dst.step + j);  
                uchar p3 = (i == 0 || j == width - 1) ? 0 : *(p - dst.step + j + 1);  
                uchar p9 = (i == 0 || j == 0) ? 0 : *(p - dst.step + j - 1);  
                uchar p6 = (i == height - 1) ? 0 : *(p + dst.step + j);  
                uchar p5 = (i == height - 1 || j == width - 1) ? 0 : *(p + dst.step + j + 1);  
                uchar p7 = (i == height - 1 || j == 0) ? 0 : *(p + dst.step + j - 1);  
                if ((p2 + p3 + p4 + p5 + p6 + p7 + p8 + p9) >= 2 && (p2 + p3 + p4 + p5 + p6 + p7 + p8 + p9) <= 6)  
                {  
                    int ap = 0;  
                    if (p2 == 0 && p3 == 1) ++ap;  
                    if (p3 == 0 && p4 == 1) ++ap;  
                    if (p4 == 0 && p5 == 1) ++ap;  
                    if (p5 == 0 && p6 == 1) ++ap;  
                    if (p6 == 0 && p7 == 1) ++ap;  
                    if (p7 == 0 && p8 == 1) ++ap;  
                    if (p8 == 0 && p9 == 1) ++ap;  
                    if (p9 == 0 && p2 == 1) ++ap;  
  
                    if (ap == 1 && p2 * p4 * p6 == 0 && p4 * p6 * p8 == 0)  
                    {  
                        //���  
                        mFlag.push_back(p+j);  
                    }  
                }  
            }  
        }  
  
        //����ǵĵ�ɾ��  
        for (std::vector<uchar *>::iterator i = mFlag.begin(); i != mFlag.end(); ++i)  
        {  
            **i = 0;  
        }  
  
        //ֱ��û�е����㣬�㷨����  
        if (mFlag.empty())  
        {  
            break;  
        }  
        else  
        {  
            mFlag.clear();//��mFlag���  
        }  
  
        //�Ե���  
        for (int i = 0; i < height; ++i)  
        {  
            uchar * p = dst.ptr<uchar>(i);  
            for (int j = 0; j < width; ++j)  
            {  
                //��������ĸ����������б��  
                //  p9 p2 p3  
                //  p8 p1 p4  
                //  p7 p6 p5  
                uchar p1 = p[j];  
                if (p1 != 1) continue;  
                uchar p4 = (j == width - 1) ? 0 : *(p + j + 1);  
                uchar p8 = (j == 0) ? 0 : *(p + j - 1);  
                uchar p2 = (i == 0) ? 0 : *(p - dst.step + j);  
                uchar p3 = (i == 0 || j == width - 1) ? 0 : *(p - dst.step + j + 1);  
                uchar p9 = (i == 0 || j == 0) ? 0 : *(p - dst.step + j - 1);  
                uchar p6 = (i == height - 1) ? 0 : *(p + dst.step + j);  
                uchar p5 = (i == height - 1 || j == width - 1) ? 0 : *(p + dst.step + j + 1);  
                uchar p7 = (i == height - 1 || j == 0) ? 0 : *(p + dst.step + j - 1);  
  
                if ((p2 + p3 + p4 + p5 + p6 + p7 + p8 + p9) >= 2 && (p2 + p3 + p4 + p5 + p6 + p7 + p8 + p9) <= 6)  
                {  
                    int ap = 0;  
                    if (p2 == 0 && p3 == 1) ++ap;  
                    if (p3 == 0 && p4 == 1) ++ap;  
                    if (p4 == 0 && p5 == 1) ++ap;  
                    if (p5 == 0 && p6 == 1) ++ap;  
                    if (p6 == 0 && p7 == 1) ++ap;  
                    if (p7 == 0 && p8 == 1) ++ap;  
                    if (p8 == 0 && p9 == 1) ++ap;  
                    if (p9 == 0 && p2 == 1) ++ap;  
  
                    if (ap == 1 && p2 * p4 * p8 == 0 && p2 * p6 * p8 == 0)  
                    {  
                        //���  
                        mFlag.push_back(p+j);  
                    }  
                }  
            }  
        }  
  
        //����ǵĵ�ɾ��  
        for (std::vector<uchar *>::iterator i = mFlag.begin(); i != mFlag.end(); ++i)  
        {  
            **i = 0;  
        }  
  
        //ֱ��û�е����㣬�㷨����  
        if (mFlag.empty())  
        {  
            break;  
        }  
        else  
        {  
            mFlag.clear();//��mFlag���  
        }  
    }  
    return dst;  
}  


void maze(Point start, Point end, list<Point> &road, vector<vector<int>> map)
{
	int rows;
	int cols;
	rows = map.size();
	cols = map[1].size();
	int **record = new int*[rows];       
	for (int i = 0; i < rows; i++)
	{
		record[i] = new int[cols];
		for (int j = 0; j < cols; j++)
			record[i][j] = 0;
	}

	Point move[8];
	move[0].x = 0; move[0].y = 1;
	move[1].x = 1; move[1].y = 1;
	move[2].x = 1; move[2].y = 0;
	move[3].x = 1; move[3].y = -1;
	move[4].x = 0; move[4].y = -1;
	move[5].x = -1; move[5].y = -1;
	move[6].x = 1; move[6].y = 0;
	move[7].x = -1; move[7].y = 1;

	road.push_back(start);
	Point current = road.back();
	int d;
	while (!road.empty() && !((current.x == end.x) && (current.y == end.y)))
	{
		for (d = 0; d < 8; d++)
		{
			int i = move[d].x + current.x;
			int j = move[d].y + current.y;
			if (map[i][j] == 1 && record[i][j] == 0)
			{
				record[i][j] = 1;
				road.push_back(Point(i, j));
				current.x = i;
				current.y = j;
				break;
			}
		}
		if (d == 8)
		{
			road.pop_back();
			current = road.back();
		}
	}
}


double OldImage[4][2]; //�洢��������λ����ͼƬ�е�����
double OldReal[4][2]; //�洢��������λ���ڻ���������ϵ�µ�����
double NewReal[4][2]; //ͼ��Χ�ǵ��Ӧ��ʵ������
double A[2][2]; //����Ϊһϵ�б任����
double Atran[2][2];
double OM[2][2];
double OR[2][2];
double temp;
double D[2];


//����ת��������Nx��NyΪͼƬ�ϵ�X��Y����
double ImagetoReal(double Nx,double Ny,int XorY)
{
if(XorY) //ת��Ϊ�����������µ�X����
return Atran[0][0]*Nx+Atran[0][1]*Ny+D[0];
else //ת��Ϊ�����������µ�Y����
return Atran[1][0]*Nx+Atran[1][1]*Ny+D[1];
}


int biaoding()//�궨����
{
//ֻ��Ҫ����������λ�ö�Ӧ�Ļ����˺�ͼƬ���껻�ɲ����Ľ������
//λ��1
OldReal[0][0]=116.44; //����������X
OldReal[0][1]=-514.67; //����������Y
OldImage[0][0]=6; //ͼƬ����X
OldImage[0][1]=52; //ͼƬ����Y
//λ��2
OldReal[1][0]=-119.97;
OldReal[1][1]=-558.66;
OldImage[1][0]=37;
OldImage[1][1]=18;
//λ��3
OldReal[2][0]=-83.09;
OldReal[2][1]=-618.23;
OldImage[2][0]=38;
OldImage[2][1]=44;
//λ��4
OldReal[3][0]=OldReal[1][0];
OldReal[3][1]=OldReal[1][1];
OldImage[3][0]=OldImage[1][0];
OldImage[3][1]=OldImage[1][1];
//��ͼƬ����ϵ�е���������
OM[0][0]=OldImage[0][0]-OldImage[1][0];OM[0][1]=OldImage[2][0]-OldImage[3][0];
OM[1][0]=OldImage[0][1]-OldImage[1][1];OM[1][1]=OldImage[2][1]-OldImage[3][1];
//�������ϵ��������������
OR[0][0]=OldReal[0][0]-OldReal[1][0];OR[0][1]=OldReal[2][0]-OldReal[3][0];
OR[1][0]=OldReal[0][1]-OldReal[1][1];OR[1][1]=OldReal[2][1]-OldReal[3][1];
temp=OM[0][0]*OM[1][1]-OM[1][0]*OM[0][1]; //��ת����������ʽ
if(temp==0)
{
return 0;
}
else
{
//�������
A[0][0]=OM[1][1]/temp;
A[0][1]=-OM[0][1]/temp;
A[1][0]=-OM[1][0]/temp;
A[1][1]=OM[0][0]/temp;
//��ת������
Atran[0][0]=OR[0][0]*A[0][0]+OR[0][1]*A[1][0];
Atran[0][1]=OR[0][0]*A[0][1]+OR[0][1]*A[1][1];
Atran[1][0]=OR[1][0]*A[0][0]+OR[1][1]*A[1][0];
Atran[1][1]=OR[1][0]*A[0][1]+OR[1][1]*A[1][1];
//��������C
D[0]=OldReal[0][0]-Atran[0][0]*OldImage[0][0]-Atran[0][1]*OldImage[0][1];
D[1]=OldReal[0][1]-Atran[1][0]*OldImage[0][0]-Atran[1][1]*OldImage[0][1];
//����ͼ��Χ�Ľǵ��Ӧ��ʵ������ϵ����
NewReal[0][0]=ImagetoReal(1000,800,1);
NewReal[0][1]=ImagetoReal(1000,800,0);
NewReal[1][0]=ImagetoReal(1024,0,1);
NewReal[1][1]=ImagetoReal(1024,0,0);
NewReal[2][0]=ImagetoReal(1024,768,1);
NewReal[2][1]=ImagetoReal(1024,768,0);
NewReal[3][0]=ImagetoReal(0,768,1);
NewReal[3][1]=ImagetoReal(0,768,0);
return 0;
}
}
