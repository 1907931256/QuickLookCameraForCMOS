#ifndef ImageWindowItem_H
#define ImageWindowItem_H

/// \brief ImageWindowItem provides a window magnifying the area around the mouse
#include <QMessageBox>
#include <memory>
#include <QWidget>
#include "IWindowItem.h"
#include <QMouseEvent>
#include <QMenu>
#include <QContextMenuEvent>
#include "../QData/IDataItem.h"
#include "./Utility/PixelConvertor.h"
#include "QData/InstructionProcess.h"
#include "../SaveFile/SaveToFile.h"
class ImageWindowItem : public QWidget, public IWindowItem
{
    Q_OBJECT

protected:
	unsigned int m_expoTime{ 2000 };
	int m_frRate{ 18 };
	float m_dg{ 1.0 };
	float m_ag_cg{ 1.00 };
	bool uploadFlag{ false };

	QPoint m_cursorPostion{ 0, 0 }; //zoom in center
	QPoint m_mousePostion{ 0, 0 };
    QSize m_range{16,16}; //
    QImage* m_image{nullptr}; //
    std::shared_ptr<unsigned char> m_imgBuffer{nullptr};
	QMenu *menu = new QMenu(this);//右键菜单
	QAction *startAction;
	QAction *stopAction;
	QAction *expoAction;
	QAction *ag_cgAction;
	QAction *dgAction;
	QAction *fpsAction;
protected:
    virtual void paintEvent(QPaintEvent *) override; 
	//鼠标移动时，发送当前坐标
	void onMouseMoved(const QPoint& absPos); //slot of mouseMoved signal
	//鼠标移动
	virtual void mouseMoveEvent(QMouseEvent *ev) override
	{
		emit mouseMoved(ev->pos());
	}
	////鼠标左键单击
	//void mousePressEvent(QMouseEvent *ev)
	//{
	//	if (ev->button()==Qt::LeftButton)
	//		emit mousePressed(ev->pos());
	//}
	//鼠标双击
	void mouseDoubleClickEvent(QMouseEvent *ev)
	{
		emit mouseDoubleClicked(ev->pos());
	}
	//右击菜单
	void contextMenuEvent(QContextMenuEvent *ev)
	{
		menu->move(this->cursor().pos());
		menu->show();
	}
//右键菜单需要用到的槽函数
protected:
	void onStartActionTriggerd();
	void onStopActionTriggerd();
	void onExpoActionTriggerd();
	void onFpsActionTriggerd();
	void onAg_cgActionTriggerd();
	void onDgActionTriggerd();
private:
	Instruction::CMOSID cmosNumber;
	QImage::Format strFormat;

protected:
    virtual int displayModeDisplay() const override;

public:
	virtual int saveToFile() const override;

public:
	ImageWindowItem(QWidget* parent = nullptr, Qt::WindowFlags f = 0, QImage::Format str = QImage::Format_ARGB32);//不带默认形参的只能放在带默认形参的前面
    ~ImageWindowItem();
	void setCmosNumber(Instruction::CMOSID number);
    virtual IWindowItem* clone() const override;
    virtual int setDataItemPtr(std::shared_ptr<IDataItem>& ptr)  override;
    virtual int refresh() override;
    virtual QWidget* widget() /*const*/ override {return this;}


signals:
	void cursorPositionChanged(int x, int y); //when mouse pos changed
	void displayPressMousePostion(QString str); //when mouse pressed
signals:
	void mouseMoved(const QPoint& absolutePositon);
	//void mousePressed(const QPoint& absolutePositon);
	void mouseDoubleClicked(const QPoint& absolutePositon);
public:	
    void setMagnifierRange(int width, int height); //set range of zoom in area


};

#endif // ImageWindowItem_H
