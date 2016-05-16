#pragma once
#include "initsock.h"
#include <thread>
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
class Instruction
{
//���캯��&��������
public:
	Instruction(USHORT port_local_send, USHORT port_local_recv, USHORT port_far_send, char* ip_local, char* ip_far);
	~Instruction();

//����
public:
	//ö������CMOSID
	enum CMOSID{ NoCMOS, CMOSE, CMOS1, CMOS2, CMOS3 };
private:
	CMOSID cmosId;
	CMD *cmd;

	int m_FPS;
	long long m_frLength{ 10000 };//֡��
	long long m_frExpoTime{ 8000 };//�ع�ʱ�䣬С��֡��

	bool m_recving{ false }; //�߳��˳���ʶ
	bool m_sendingAECRun{ false }; //�߳��˳���ʶ
	bool m_sendingManualRun{ false }; //�߳��˳���ʶ
	bool m_sendingSetFPS{ false }; //�߳��˳���ʶ

	std::thread m_thrSendSetFPS; //�߳̾��
	std::thread m_thrRecv; //�߳̾��
	std::thread m_thrSendManualRun; //�߳̾��
	std::thread m_thrSendAECRun; //�߳̾��
//socket
protected:
	CInitSock c;//Winsock���װ����ͷ�
	SOCKET sock_send;
	SOCKET sock_recv;
	sockaddr_in addr_local_send;
	sockaddr_in addr_far_send;
	sockaddr_in addr_local_recv;
//
public:
	//
	virtual bool startSendAECRun()
	{
		if (m_sendingAECRun)
			return false;
		m_sendingAECRun = true;
		m_thrSendAECRun = std::thread([this](){this->AECRun(); });
		return true;
	}
	virtual void stopSendAECRun()
	{
		m_sendingAECRun = false;
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
		if (m_thrSendAECRun.joinable())
			m_thrSendAECRun.join();
	}
	//
	virtual bool startSendManualRun(long long _expoTime)
	{
		m_frExpoTime = _expoTime;
		if (m_sendingManualRun)
			return false;
		m_sendingManualRun = true;
		m_thrSendManualRun = std::thread([this](){this->ManualExposure(m_frExpoTime); });
		return true;
	}
	virtual void stopSendManualRun()
	{
		m_sendingManualRun = false;
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
		if (m_thrSendManualRun.joinable())
			m_thrSendManualRun.join();
	}
	virtual bool startSendSetFPS(int _fps)
	{
		m_FPS = _fps;
		if (m_sendingSetFPS)
			return false;
		m_sendingSetFPS = true;
		m_thrSendSetFPS = std::thread([this](){this->SetFPS(m_FPS); });
		return true;
	}
	//ֹͣ����
	virtual void stopSendSetFPS()
	{
		m_sendingSetFPS = false;
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
		if (m_thrSendSetFPS.joinable())
			m_thrSendSetFPS.join();
	}

	//
	virtual bool startRecv()
	{
		if (m_recving)
			return false;
		m_recving = true;
		m_thrRecv = std::thread([this](){this->receive(); });
		return true;
	}
	virtual void stopRecv()
	{
		m_recving = false;
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
		if (m_thrRecv.joinable())
			m_thrRecv.join();
	}
//����
private:
	unsigned short cmdCounter;//����ָ���������ֵΪ0
public:
	void SetCmosId(CMOSID id);
	void AECRun();//��ʼ�ϴ�ͼ���Զ��ع�
	void ManualExposure(long long _expoTime);//�Զ��ع�
	void SetFPS(int _fps);
	void Stop();
protected:
	bool buildCmdReg(int _addr, int _data);
	void sendCmdReg(int _addr, int _data);
	void PowerUp();
	void EnableClockManagement1();
	void EnableClockManagement2();
	void RequiredRegisterUpload();
	void ExtraConfig();
	void SoftPowerUp();
	void EnableSequencer();

	void DisableSequencer();
	void SoftPowerDown();
	void DisableClockManagement2();
	void DisableClockManagement1();
	void PowerDown();
//����
public:
	bool DONEFLAG = false;
protected:
	void receive();
};