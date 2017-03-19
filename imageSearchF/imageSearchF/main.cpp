#include<iostream>  
#include "stdio.h" 
//#include "stdafx.h" 
#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp>  
#include "opencv/cv.h"  
#include <opencv2/opencv.hpp> 

time_t start;
time_t end;
using namespace std;
using namespace cv;
double minResult=5;
string minFileName=NULL;

//string resultPAth=NULL;

int main(int argc, char** argv)
{
    
	time_t start = clock();
	
		/////////stackoverflow
		IplImage *input = cvLoadImage("D:\\ImageSearchFromDatabase\\input.jpg",1);
		if (!input)
		{
			cout << "cvLoadImage() failed in input!" << endl;
			return -1;
	       // deal with error! return, exit or whatever
		}

		//�Ҷȴ���
		IplImage* input_gray = cvCreateImage(cvSize(input->width,input->height), input->depth, 1);
		if (!input_gray)
		{
			cout << "input����!" << endl;
			return -1;
		}
		cvCvtColor(input,input_gray, CV_RGB2GRAY);

		//��ȡ����
		CvMemStorage *input_mems = cvCreateMemStorage();
		CvSeq *input_seqs;
		cvFindContours(input_gray, input_mems,&input_seqs, sizeof(CvContour), CV_RETR_TREE);
		

		string dir_path = "D:\\ImageSearchFromDatabase\\database\\";
		Directory dir;
		vector<string> fileNames = dir.GetListFiles(dir_path, "*.jpg", false);
		if (fileNames.empty()) { 
			cout << "error:���ݿ���û�������Ϣ��" << endl; 
			return -1;
		}


		unsigned int i;
		for (i = 0; i < fileNames.size(); i++)
		{
			string fileName = fileNames[i];
			string fileFullName = dir_path + fileName;

			const char *s= fileFullName.c_str();//;����ת��
			IplImage *test = cvLoadImage(s,1);
			IplImage *test_gray = cvCreateImage(cvSize(test->width, test->height), test->depth, 1);
			if (!test_gray)
			{
				cout << "�޷���ȡtest!" << endl;
				return -1;
				// deal with error! return, exit or whatever
			}

			//test�ĻҶȻ�����
			cvCvtColor(test,test_gray, CV_RGB2GRAY);
			
			//test��ȡ����
			CvMemStorage *test_mems = cvCreateMemStorage();
			CvSeq *test_seqs;
			cvFindContours(test_gray, test_mems, &test_seqs, sizeof(CvContour), CV_RETR_TREE);

			double value1 = cvMatchShapes(input_seqs, test_seqs, CV_CONTOURS_MATCH_I1);
		   //double value2 = cvMatchShapes(input_gray, test_gray, CV_CONTOURS_MATCH_I2);
			//double value 3= cvMatchShapes(input_gray, test_gray, CV_CONTOURS_MATCH_I3);
			cout << "file name:" << fileName <<"��ƥ��ֵΪ"<< value1 << endl;
			
			//ƥ��ֵԽСԽƥ��
			if(value1<minResult)
			{
				minResult=value1;
				minFileName=fileName;
			}
		}
		time_t end = clock();
		cout << "��ƥ��Ľ��Ϊ��" << minFileName << "����ƥ��ֵΪ��"<<minResult<<endl;
		cout << "����ʱ�䣺" << double(end - start) / CLOCKS_PER_SEC << endl;
	   system("pause");

	return 0;

}