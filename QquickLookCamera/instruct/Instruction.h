#pragma once
#include ".\\QData\\initsock.h"

#pragma pack (push)
#pragma pack (1)
struct CMD
{
	//16 byte + 8 byte
	unsigned int synWord{ 0 }; // ����ͬ���� - 4 byte
	unsigned int dataLength{ 0 }; // �������ݳ��� - 4 byte
	unsigned short counter{ 0 }; // ��������� - 2 byte
	unsigned short form{ 0 }; // ��������
	unsigned short timeStamp{ 0 }; // ʱ���
	unsigned short checkSum{ 0 }; // У���

	unsigned long long data{ 0 }; // ��������
};

#pragma pack (pop)

//PC->FPGA��ָ�������������ı� ��������ҪҪ��ָ���Ӳ�������ݣ�Ȼ��InputCOMS��ʼ�������ݡ�
class Instruction
{
public:
	enum CMOSID{ NoCMOS, CMOSE, CMOS1, CMOS2, CMOS3 };
public:
	Instruction(USHORT port_target, ULONG ip_target, USHORT port_local, ULONG ip_local);
	~Instruction();

	//����CMOS��ţ��ڵ��÷���ָ��ĺ���ǰӦ���ñ�����
	bool SetCmosId(CMOSID id);
	bool Initial();
	bool Start();
	bool Stop();
	bool SetExposureRate(int _rate){ return true; }
	bool SetFrameRate(int _rate){ return true; }

protected:
	bool OpenSystem();
	bool Reset();
	bool PowerUp();
	bool EnableClockManagement1();
	bool EnableClockManagement2();
	bool RequiredRegisterUpload();
	bool SoftPowerUp();
	bool EnableSequencer();

	bool DisableSequencer();
	bool SoftPowerDown();
	bool DisableClockManagement2();
	bool DisableClockManagement1();
	bool PowerOff();
	
protected:
	bool buildCmdReg(CMD* _cmd, int _addr, int _data);
	bool sendCmdReg(int _addr, int _data);

protected:
	CInitSock c;//Winsock���װ����ͷ�
	SOCKET sock;//����ͼ�������׽���
	sockaddr_in addr_local;//���ص�ַ
	sockaddr_in addr_target;//Զ�̵�ַ


private:
	CMOSID cmosId;
	unsigned short cmdCounter;//��ֵΪ0
	const int maxSend; //���������ʹ���
	const int maxWaitS; //�������ȴ�ʱ��s
	const int maxWaitUS; //�������ȴ�ʱ��us
};
