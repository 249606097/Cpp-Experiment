#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

class CD
{
    public:
        CD(string name, string songs[]);
        string getSinger();         // ��ø��ֵ�����
        string getSong(int index); // ���ĳ�׸�ĸ���
        void listSongs();           // �г�CD������

    private:
        string singer;		// ���ֵ����֡�
        string songs[6];		// ÿ��ר��6�׸�����֡�
};

CD::CD(string name, string songs[])
{
    this->singer = name;
    
    for (int i = 0; i < 6; i++)
    {
        this->songs[i] = songs[i];
    }
}

string CD::getSinger()
{
    return this->singer;
}

string CD::getSong(int index)
{
    return this->songs[index];
}

void CD::listSongs()
{
    for (int i = 0; i < 6; i++)
    {
        cout << i << ". " << this->getSong(i) << endl;
    }

    return;
}

class CDPlayer 
{
    public:
        CDPlayer();

        /*�ṩ���û�һ���˵���ͨ������˵����û�����ѡ��
        1. ����CD
        2. ����CD
        3. ����CD
        0. �ػ�   */
        void showMenu();

        /*����CD. void insertCD(CD* cd)���β���ָ��CD�����ָ�롣���CDPlayer���Ѿ���CD����ʾ��ȡ��CD�����CDPlayer��û��CD����ʾ��������λ���ǵ�CD��*/
        void insertCD(CD *cd);

        /*����CD. CD *ejectCD()������ֵ��ָ���CD�����ָ�롣���CDPlayer���Ѿ���CD����ʾ��������λ���ǵ�CD�����ظ�CD��ָ�룻���CDPlayer��û��CD����ʾCDPlayer��û��CD������NULL��*/
        CD *ejectCD();
        /*����CD�����CDPlayer���Ѿ���CD����ʾ���ڲ�����λ���ǵ�CD������ӡCD�и������嵥�����CDPlayer��û��CD����ʾCDPlayer��û��CD������ʾ�û�����CD��*/
        void play();

    private:
        /* ����CDPlayer�е�CD������ָ��CD�����ָ�롣û��CDʱ��Ϊnull��ʹ��ָ�룬�ܺõ�ģ�� ��CD�����ǲ�������һ���֣�������ֻ�Ƕ�ȡ�������е�CD�����ݡ�*/
        CD *cd;
        bool cdIn;  // CDPlayer���Ƿ��Ѿ�����CD
};

CDPlayer::CDPlayer()
{
    this->cd = NULL;
    this->cdIn = false;
}

void CDPlayer::showMenu()
{
    cout << "*********************************" << endl;
    cout << "*  1. ����CD                       *" << endl;
    cout << "*  2. ����CD                       *" << endl;
    cout << "*  3. ����CD                       *" << endl;
    cout << "*  0. �ػ�                         *" << endl;
    cout << "*********************************" << endl;
    cout << endl;
    
    return;
}

void CDPlayer::insertCD(CD *cd)
{
    if (this->cdIn)
        cout << "��ȡ��CD" << endl;
    else
    {
        cout << "������" << cd->getSinger()<< "��CD......" << endl;
        this->cd = cd;
        this->cdIn = true;
    }
    
    return;
}

CD *CDPlayer::ejectCD()
{
    if (!this->cdIn)
    {
        cout << "Please insert CD first" << endl;
        return NULL;
    }
    else
    {
        cout << "������" << this->cd->getSinger() <<"��CD......" << endl;
        this->cd = NULL;
        this->cdIn = false;
        return this->cd;
    }  
}

void CDPlayer::play()
{
    if (!this->cdIn)
    {
        cout << "Please insert CD first" << endl;
    }
    else
    {
        cout << "���ڲ���" << this->cd->getSinger() <<"��CD......" << endl;
        cout << "Singer:" << this->cd->getSinger() << endl;
        this->cd->listSongs();
    }
    
    return;
}

int main()
{
    string name;
    string songs[6];

    cout << "����CD......" << endl;
    // �����������
    cout << "  Singer's Name: " << endl;
    cin >> name;  // ���룺�ܽ���

    for (int i = 0; i < 6; i++) 
    {
        cout << "  song" << (i+1) << "#: ";
        cin >> songs[i];
    }

    CD cd(name, songs);   //����CD
    cd.listSongs();       //��ʾCD������
    CDPlayer player;      //����CDplayer
    player.showMenu();    //���ɲ��Ż��İ�ť

    /* ���� */
    player.play();         //��ӡ��Please insert CD first
    /* ����CD */
    player.insertCD(&cd); //��ӡ���������ܽ��׵�CD......
    /* ���� */
    player.play();         //��ӡ�����ڲ����ܽ��׵�CD......
    player.ejectCD();      //��ӡ���������ܽ��׵�CD......

    // /* ����һ��CD�����ֺ͸��¼��ʡ�ԡ�*/
    // CD cd2(name2, songs2);
    // player.insertCD(&cd2);
    // player.play();

    system("PAUSE");
    return 0;
}