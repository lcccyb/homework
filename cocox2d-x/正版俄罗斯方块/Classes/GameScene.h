#ifndef _GameScene_H_
#define _GameScene_H_

#include "cocos2d.h"
USING_NS_CC;

class GameScene :public Scene{
public:
	static Scene*createScene();
	virtual bool init();
	//����Ԥ������
	void PreviewBox(int box[4][2]);
	//��������ͼ��
	void createFix();

	//��ȡ��������
	float getX(int x);
	float getY(int y);
	//��ȡ����
	int getIx(float x);
	int getIy(float y);

	cocos2d::Vector<cocos2d::Sprite*> StopList;//�洢�Ѿ�ֹͣ�ƶ��ķ���
	cocos2d::Vector<cocos2d::Sprite*> MoveList;//�洢�����ƶ��ķ���

	//��ȡ��߸߶�
	int Highest();

	//�����¼�
	bool onTouchBegan(Touch*touch, Event*event);

	void moveFks(int num);//�ƶ�����
	bool isCollSion(int tag);//�ж��Ƿ���ײ	
	bool isBoxStopLeft();//�ж��ܷ�����
	bool isBoxStopRight();//�ж��ܷ�����
	bool isRotate(int x, int y);//�жϷ����ܷ���ת

	void leftMove();//����
	void rightMove();//����
	void downMove(float delta);//����
	void fastDrop(float f);//��������
	void boxMove(float delta);//�ƶ�
	void fkRotate(int num);//��ת����
	void Eliminate();//��������
	void menuMusicTogg(Ref* pSender);//���ֿ���
	void Suspend(Ref* pSender);//��ͣ��ť
	void Continue(Ref* pSender);//������Ϸ��ť
	void Restart(Ref* pSender);
	Menu* menu_on;//������Ϸ��ť
	Menu* restart_on;//���¿�ʼ��ťs
	
	void ScoreSystem();//��ʾ�����͵ȼ�
	Dictionary*dic;//��ȡXML�ļ�
	Size visibleSize;
	int score = 0;//��ʼ������
	Label*Fs;//��ǰ����
	Label*Gf;//��߷���

	CREATE_FUNC(GameScene);
private:
	Color3B Colors[6];//���÷������ɫ
	int bSize = 31;//�����������С
	int preColor = -1;//Ԥ��ͼ����ɫ
	int preShape = -1;//Ԥ��ͼ��
	int shape = -1;;//ͼ��

};

#endif