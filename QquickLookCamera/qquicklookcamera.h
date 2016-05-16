#ifndef QQUICKLOOKCAMERA_H
#define QQUICKLOOKCAMERA_H

#include <QMainWindow>
#include "ui_qquicklookcamera.h"
#include "myclass.h"
#include "../QData/InstructionProcess.h"
class QLabel;

//�����ṩ������λ����������
class QquickLookCamera : public QMainWindow
{
	Q_OBJECT
public:
	QquickLookCamera(QWidget *parent = 0);
	~QquickLookCamera();

	//������������Ӵ���
	void createControlFrame();
	//����״̬��
	void cerateStatus();

public slots :
	void OpenFile();
	void saveFlie();
	void AECRun();
	void Stop();
	void setExpoTime(long long _time);
	void setFrRate(int _rate);

private: 
	//Ui::QquickLookCameraClass ui; //��ʹ��UI��ʹ�ô�����ķ�ʽ��ӿؼ�

	QString filename;
	MyClass *showWidget;
	QFrame *ctrlFrame;
	QDockWidget *ctrlFrameDock;

private:
	QLineEdit *expoTimeLineEdit;
	QLineEdit *frRateLineEdit;

	long long expoTime{ 8000 };
	int frRate{ 18 };
	long long frLength{ 10000 };
	bool uploadFlag{ false };//�����ϴ���־

	//������
	/*QToolBar *fileTool;
	QToolBar *zoomTool;
	QToolBar *rotateTool;
	QToolBar *mirrorTool;
	QToolBar *doToolBar;*/

	//״̬��
	QLabel  *expoTimeLabel;
	QLabel  *frRateLabel;
	QLabel  *frLengthLabel;	
};

#endif // QQUICKLOOKCAMERA_H
