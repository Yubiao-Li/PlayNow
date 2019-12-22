#include "mythread.h"
#define cout qDebug() << "[" <<__FILE__ <<":"<<__FUNCTION__<<":"<<__LINE__ <<"]"

MyThread::MyThread(QObject *parent) : QObject(parent)
{
}

void MyThread::load_widget()
{
    //QThread::sleep(1);
    emit load_widget_signal();
}

void MyThread::load_song()
{
    QString filename="../Table/"+song_Check+".txt";
//    QTextCodec *code = QTextCodec::codecForName("GB2312");//解决中文路径问题
    string name = filename.toStdString();
    fstream file(name,ios::in|ios::binary);
    if(file)
    {
        file.read(reinterpret_cast<char*>(&BPM),sizeof(BPM));

        rhythm note;
        while(file.read(reinterpret_cast<char*>(&note),sizeof(note)))
        {
            key_load.push_back(note);
        }
        key_num=key_load.size();
        for(int i=0;i<key_num;i++)
        {
            float_key.append(NULL);

        }
        file.close();

        emit load_song_finsh();

    }
    else
    {
        cout<<"fail";
    }
}

void MyThread::load_save()
{
    //读取存挡
    ifstream save_file;
    string path = "../save/save.txt";
    save_file.open(path, ios::in|ios::binary);
    if (!save_file)
    {
        archive save;
        for(int i=0;i<num_of_song;i++)
        {
            save.code=i;
            save.grade=' ';
            save.score=0;
            save_data.push_back(save);
        }
    }
    else
    {
        archive save;
        while(save_file.read(reinterpret_cast<char*>(&save),sizeof(save)))
        {
            save_data.push_back(save);
        }
        save_file.close();
    }

}

void MyThread::keep_save()
{
    if(save_data.size()!=0)
    {
        ofstream save_file("../save/save.txt",ios::out|ios::binary);

        for(int i=0;i<num_of_song;i++)
        {
            save_file.write(reinterpret_cast<char*>(&save_data[i]),sizeof(save_data[i]));
        }

        save_file.close();
    }
}
