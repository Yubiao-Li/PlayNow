#include"source.h"

QString song_Check="";

int score=0;

double BPM=0;

QString song_name[num_of_song+1]={"Diana Boncheva - Beethoven Virus","Maksim Mrvica","HandClap","Add your song!"};

QVector<rhythm>key_load={};  //谱面的数据

int key_num=0;

QVector<FloatNote*>float_key={};     //用于创建音符

MyMoive *perfect,*great,*miss;

int combo=0;

int perfect_num=0;
int great_num=0;
int miss_num=0;
double accuray_num=0;
int highest_combo=0;

double scale=0.5;

QVector<archive>save_data={};

ComboWidget *combo_widget=NULL;

source::source()
{

}
