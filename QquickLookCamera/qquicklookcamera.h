#ifndef QQUICKLOOKCAMERA_H
#define QQUICKLOOKCAMERA_H

#include <QMainWindow>
#include "ui_qquicklookcamera.h"
#include "myclass.h"
#include "../QData/InstructionProcess.h"
class QLabel;
class QComboBox;

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
	void setExpoTime(unsigned int _time);
	void setFrRate(int _rate);
	void setAGCG(float _totalGain);
	void setDG(float _dg);
	void AGCGBoxChanged();

private: 
	//Ui::QquickLookCameraClass ui; //��ʹ��UI��ʹ�ô�����ķ�ʽ��ӿؼ�

	QString filename;
	MyClass *showWidget;
	QFrame *ctrlFrame;
	QDockWidget *ctrlFrameDock;

private:
	QLineEdit *expoTimeLineEdit;
	QLineEdit *frRateLineEdit;
	QLineEdit *DGLineEdit;
	//QLineEdit *AGCGLineEdit;
	QComboBox *AGCGComboBox;

	unsigned int expoTime{ 2000 };
	int frRate{ 18 };
	unsigned int frLength{ 10000 };
	float dg{1.0};
	float ag_cg{1.00};
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
	QLabel  *infoLabel;
};

#endif // QQUICKLOOKCAMERA_H
