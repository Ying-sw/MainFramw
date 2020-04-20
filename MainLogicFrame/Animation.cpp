#include "stdafx.h"
#include "Animation.h"
#include "MainWidget.h"

Animation::Animation(QWidget *parent)
	: QWidget(parent), m_IsShow(true)
{
}

Animation::~Animation()
{
	 
}

void Animation::showEvent(QShowEvent* event) {
	if (!m_IsShow)
		return;
	QPropertyAnimation *animation = new QPropertyAnimation(MainWidget::staticThis, "windowOpacity");
	animation->setDuration(700);
	animation->setStartValue(0);
	animation->setEndValue(1);
	animation->setEasingCurve(QEasingCurve::Linear);

	QDesktopWidget deskTop;
	QPropertyAnimation *animation2 = new QPropertyAnimation(MainWidget::staticThis, "geometry");
	animation2->setDuration(300);
	animation2->setStartValue(QRect(0, 0, deskTop.width(), deskTop.height()));
	animation2->setEndValue(MainWidget::staticThis->geometry());

	QParallelAnimationGroup *group = new QParallelAnimationGroup;
	group->addAnimation(animation);
	group->addAnimation(animation2);
	group->start();

	QGraphicsDropShadowEffect *m_pShadow = new QGraphicsDropShadowEffect(MainWidget::staticThis);
	m_pShadow->setColor(QColor(0, 0, 0, 85));
	m_pShadow->setBlurRadius(10);
	m_pShadow->setOffset(4, 4);
	MainWidget::staticThis->setGraphicsEffect(m_pShadow);
}

void Animation::setAnimation(bool isShow /*= true*/)
{
	m_IsShow = isShow;
}

void Animation::hideEvent(QHideEvent *event)
{

}

void Animation::closeAnimation(bool closeHide) {
	if (!m_IsShow)
		return;
 	QPropertyAnimation *animation = new QPropertyAnimation(MainWidget::staticThis, "windowOpacity");
 	animation->setDuration(300);
 	animation->setStartValue(1);
 	animation->setEndValue(0);
 	if (closeHide) 
 		connect(animation, &QPropertyAnimation::finished, this, &QWidget::close);
 	else 
 		connect(animation, &QPropertyAnimation::finished, MainWidget::staticThis, &QWidget::hide);
	animation->start();
}