#include <iostream>
#include <vector>
#include <string>
using namespace std;
struct ErrordRecord //错误记录
{
public:
    string pathWay;;
    string fileName;
    int line;
    int num;//记录的数目
};

int main()
{
    vector<ErrordRecord *> errordRecords;

    //  while (errordRecords.size()<8)//当记录多余8条是结束程序
    string pathWay;
    string fileName;
    int line;

    while (cin >> pathWay >> line)
    {

        fileName = pathWay.substr(pathWay.find_last_of("\\") + 1);
        bool exist = false;//如果记录是否已经存在


        for (int i = 0;i < errordRecords.size();++i)
        {
            if (fileName == (errordRecords[i]->fileName) && line == (errordRecords[i]->line))
            {
                errordRecords[i]->num = (errordRecords[i]->num) + 1;
                exist = true;
                break;
            }
        }
        if (exist == false)//记录不存在
        {
            ErrordRecord *errordRecord = new ErrordRecord();
            errordRecord->fileName = fileName;
            errordRecord->line = line;
            errordRecord->num = 1;
            errordRecords.push_back(errordRecord);
        }

       /* if (getchar() == '\n')	//用于判断回车符终止循环输入
		break;*/
	/*if ((getchar() == '\n')&&(getchar() == '\n'))
		break;*/
    }


    //根据数目多少输出,冒泡排序
    for (int i = 0;i < errordRecords.size();++i)
    {
        for (int j = i + 1;j < errordRecords.size();++j)
        {
            if (errordRecords[i]->num < errordRecords[j]->num)
            {
                string fileName = errordRecords[i]->fileName;
                int line = errordRecords[i]->line;
                int num = errordRecords[i]->num;

                errordRecords[i]->fileName = errordRecords[j]->fileName;
                errordRecords[i]->line = errordRecords[j]->line;
                errordRecords[i]->num = errordRecords[j]->num;

                errordRecords[j]->fileName = fileName;
                errordRecords[j]->line = line;
                errordRecords[j]->num = num;

            }
        }
    }

    //for (int i = 0;i < errordRecords.size();++i)
    for (int i = 0;i < errordRecords.size() && i < 8;++i)//输出前八条记录
    {
        if (errordRecords[i]->fileName.length() > 16)
        {
            cout << errordRecords[i]->fileName.substr(fileName.length()-16)
                << " " << errordRecords[i]->line << " " << errordRecords[i]->num << endl;
        }
        else {
            cout << errordRecords[i]->fileName << " " << errordRecords[i]->line << " " << errordRecords[i]->num << endl;
        }
        

    }


    return 0;
};
