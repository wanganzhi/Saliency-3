/* This code is to generate a svm compatible files corresponding to the gt, image, depth and features files generated earlier 
 * This requires gt.txt, image.txt, depth.txt and features.txt files to be available and to be equal in number of files
 */

//Cpp
#include <iostream>
#include <fstream>
#include <dir_files/dir_files.h>

using namespace std;

int main(int ac, char* av[])
{
	//Enter the folders of the gt.txt, image.txt, depth.txt and features.txt
	if(ac<5)
	{
		cout<<"Enter the folders of the gt.txt, image.txt, depth.txt, features.txt and svmfiles folder"<<endl;
		return 0;
	}
	string dir_gt = av[1];
	string dir_img = av[2];
	string dir_d = av[3];
	string dir_features = av[4];
	string dir_svmfiles = av[5];
	
	vector<string> list_gt, list_img, list_d, list_features;

	dir_files D_gt(dir_gt, list_gt, "txt");
	dir_files D_img(dir_img, list_img, "txt");
	dir_files D_d(dir_d, list_d, "txt");
	dir_files D_features(dir_features, list_features, "txt");

	if(list_gt.size()==list_img.size() && list_img.size() == list_d.size() && list_d.size() == list_features.size())
	{
		for(int i=0; i<list_gt.size(); i++)
		{
			cout<<list_gt[i]<<" "<<list_img[i]<<" "<<list_d[i]<<" "<<list_features[i]<<endl;
			string path_gt, path_img, path_d, path_features;
			
			path_gt = dir_gt+"/"+list_gt[i];
			path_img = dir_img+"/"+list_img[i];
			path_d = dir_d+"/"+list_d[i];
			path_features = dir_features+"/"+list_features[i];

			ifstream f1, f2, f3, f4;
			ofstream fo;
			string svmfile;
			stringstream n_ss;
			n_ss<<i+1;
			if(i+1<10)
				svmfile = dir_svmfiles+"/svmfile_0"+n_ss.str()+".txt";
			else
				svmfile = dir_svmfiles+"/svmfile_"+n_ss.str()+".txt";

			fo.open(svmfile.c_str());
			f1.open(path_gt.c_str()); f2.open(path_img.c_str()); f3.open(path_d.c_str()); f4.open(path_features.c_str());
			int no_features;
			f4>>no_features;

			for(int k=0; k<307200; k++)
			{
				double val1, val2, val3, val4;
				f1>>val1; f2>>val2; f3>>val3;
				if(val1==255)
					fo<<"255 ";	//+1
				else
					fo<<"0 ";	//-1
				fo<<"1:"<<val2/255<<" 2:"<<val3/255<<" ";
				for(int l=0; l<no_features-1; l++)
				{
					f4>>val4;
					fo<<l+3<<":"<<val4<<" ";
				}
				f4>>val4;
				fo<<no_features+2<<":"<<val4<<endl;
			}
		}
	}
	else
		cout<<"Check the no of images in all the folders theirs lists are not equal"<<endl;

	return 0;
}
