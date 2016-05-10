#ifndef QQUICKLOOKCAMERA_H
#define QQUICKLOOKCAMERA_H

#include <QMainWindow>

#include "ui_qquicklookcamera.h"
#include "myclass.h"
#include "./instruct/Instruction.h"
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
	//��������
	void createActions();
	//�����˵���
	void createMenus();
	// void createToolBars();
	//����״̬��
	void cerateStatus();

public slots :
	void OpenFile();
	void saveFlie();

	void Initial();
	void Start();
	void Stop();

	void setExposureRate(int _rate);
	void setFrameRate(int _rate);

private: 
	//Ui::QquickLookCameraClass ui; //��ʹ��UI��ʹ�ô�����ķ�ʽ��ӿؼ�

	QString filename;
	MyClass *showWidget;
	Instruction *instructionE;
	Instruction *instruction1;
	Instruction *instruction2;
	Instruction *instruction3;
	QFrame *ctrlFrame;
	QDockWidget *ctrlFrameDock;

private:
	//�˵���
	QMenu *fileMenu;//�ļ����򿪡����桢�˳���
	QMenu *dataControlMenu;//���ݿ��ƣ���ʼ�����ϴ���ֹͣ��
	QMenu *cameraControlMenu;//������ƣ��ع��ʡ�֡�ʣ�
	QMenu *motorControlMenu;//�������
	QMenu *helpMenu;

	//�˵�����Ӧ����
	QAction *openFileAction;
	QAction *saveAction;
	QAction *exitAction;

	QAction *initAction;
	QAction *startAction;
	QAction *stopAction;

	QAction *setExposureRateAction;
	QAction *setFrameRateAction;

	QAction *aboutAction;

	QLineEdit *exposureRateLineEdit;
	QLineEdit *frameRateLineEdit;

	int exposureRate{ 0 };
	int frameRate{ 0 };

	//������
	/*QToolBar *fileTool;
	QToolBar *zoomTool;
	QToolBar *rotateTool;
	QToolBar *mirrorTool;
	QToolBar *doToolBar;*/

	//״̬��
	QLabel  *statusLabel;
	QLabel  *frameRateLabel;
	
};

#endif // QQUICKLOOKCAMERA_H
