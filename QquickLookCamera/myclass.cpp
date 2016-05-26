#include "myclass.h"
#include "QData\Instruction.h"
#include <iostream>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
MyClass::MyClass(Instruction::CMOSID _cmosId, QWidget *parent, Qt::WindowFlags f)
	: QWidget(parent, f),
	cmosId(_cmosId),
	m_height(1024), 
	m_imgWidth(1280),
	m_assWidth(20), 
	m_angle(0),
	m_BufPicNum(64)
{
	if (_cmosId==Instruction::CMOSE)
	{
		m_inputSrc = new InputCMOS(3956, inet_addr("192.168.1.2"));
	}
	else if (_cmosId == Instruction::CMOS1)
	{
		m_inputSrc = new InputCMOS(3957, inet_addr("192.168.1.2"));
	}
	else if (_cmosId == Instruction::CMOS2)
	{
		m_inputSrc = new InputCMOS(3958, inet_addr("192.168.1.2"));
	}
	else if (_cmosId == Instruction::CMOS3)
	{
		m_inputSrc = new InputCMOS(3959, inet_addr("192.168.1.2"));
	}
	//m_rotatedDataProvider = new RotatedImageDataItem(m_angle);
	//��ʼ�����ݻ�����
	std::dynamic_pointer_cast<CCirQueue>(m_cmosData)->Initial(m_height * (m_assWidth + m_imgWidth) * m_BufPicNum, (m_assWidth + m_imgWidth));//ÿ��������һ������
	std::dynamic_pointer_cast<CCirQueue>(m_cmosImageData)->Initial(m_height * m_imgWidth * m_BufPicNum, m_height * m_imgWidth);//ÿ��������һ��ͼƬ������
	//ע�Ỻ����
	m_inputSrc->registerOutputBuffer(0, m_cmosData); 
	std::dynamic_pointer_cast<ImageDataItem>(m_dataProvider)->registerInputBuffer(0, m_cmosData);
	std::dynamic_pointer_cast<ImageDataItem>(m_dataProvider)->registerOutputBuffer(0, m_cmosImageData);
	std::dynamic_pointer_cast<RotatedImageDataItem>(m_rotatedDataProvider)->registerInputBuffer(0, m_cmosImageData);

	//��ʼ�ϴ�����
	m_inputSrc->start();
	//��ʼͼ�����
	m_dataProvider->setup(m_assWidth, m_imgWidth, m_height);
	//��ʼͼ����ת
	m_rotatedDataProvider->setup(m_assWidth, m_imgWidth, m_height);
	const FeaturesOfDataItem* rotatedFeatures = m_rotatedDataProvider->constDataFeatures();

    //���ڰ�����ָ�룬��ʼ��m_dataProvider
	m_window->setDataItemPtr(m_rotatedDataProvider);
	//���ڰ�����ת��ָ�룬��ʼ��m_convertor
	m_window->setConvertor(std::shared_ptr<PixelConvertor>(new Pixel8To32));
	//���ñ����ļ�����ʼ��m_file
	m_window->setSave(std::shared_ptr<SaveToFile>(new SaveToBmpGray));


	m_magnifier->setDataItemPtr(m_rotatedDataProvider);
	//���ڰ�����ת��ָ�룬��ʼ��m_convertor
	m_magnifier->setConvertor(std::shared_ptr<PixelConvertor>(new Pixel8To32));
	//���ñ����ļ�����ʼ��m_file
	m_magnifier->setSave(std::shared_ptr<SaveToFile>(new SaveToBmpGray));

	//���ô��ڴ�С
	m_window->setMagnifierRange(rotatedFeatures->payloadDataWidth, rotatedFeatures->linesPerFrame);
	//��ʱˢ�½���
	m_refreshTimer = new QTimer(this);	
	connect(m_refreshTimer, &QTimer::timeout, this, [this](){m_window->refresh(); });//�����б��в����������ں����еľֲ������������ں�������ʹ�øñ�����
	connect(m_refreshTimer, &QTimer::timeout, this, [this](){m_magnifier->refresh(); });
	m_refreshTimer->start(30); //ÿ��30ms����һ��
	
	//m_magnifier->show();
	m_magnifier->setCmosNumber(cmosId);
	m_window->setCmosNumber(cmosId);
	connect(m_window, &ImageWindowItem::cursorPositionChanged, m_magnifier, &ImageMagnifierItem::onCursorPositionChanged);
	connect(m_window, &ImageWindowItem::mouseDoubleClicked, this, &MyClass::onMouseDoubleClicked);
	connect(m_window, &ImageWindowItem::rotateActionTriggerd, this, &MyClass::rotateImage);

	//Ĭ�Ͻ���
	gridLayout->addWidget(m_window);
	setLayout(gridLayout);
}

MyClass::~MyClass()
{
}

void MyClass::rotateImage()
{
	if (m_angle == 270)
		m_angle = 0;
	else
		m_angle += 90;
	std::dynamic_pointer_cast<RotatedImageDataItem>(m_rotatedDataProvider)->changeAngle(m_angle);
	const FeaturesOfDataItem* rotatedFeatures = m_rotatedDataProvider->constDataFeatures();
	m_window->setMagnifierRange(rotatedFeatures->payloadDataWidth, rotatedFeatures->linesPerFrame);
}