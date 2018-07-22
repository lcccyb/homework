#include "GameScene.h"
#include "GameOver.h"
#include "StartScene.h"
#include <ui/UIImageView.h>
#include "SimpleAudioEngine.h"
#include "cocos2d.h"

USING_NS_CC;
using namespace CocosDenshion;

Scene* GameScene::createScene(){
	auto scene = Scene::create();
	auto layer = GameScene::create();
	scene->addChild(layer);
	return scene;
}

bool GameScene::init()
{
	if (!Scene::init()){
		return false;
	}
	visibleSize = Director::getInstance()->getVisibleSize();	

	auto gameBj = ui::ImageView::create("gamebg.png");		
	gameBj->setPosition(Vec2(0,0));                         
	gameBj->setAnchorPoint(Vec2(0, 0));						
	float uiX = gameBj->getContentSize().width;				
	float uiY = gameBj->getContentSize().height;			
	gameBj->setScaleX(480 / uiX);												
	gameBj->setScaleY(600 / uiY);							
	this->addChild(gameBj);

	//��ʾ����
	ScoreSystem();

	//���������ɫ
	srand(time(NULL));
	createFix();
	this->schedule(schedule_selector(GameScene::boxMove), 0.5f);

	//�ر����ְ�ť
	auto musicOn = MenuItemImage::create("menu_on.png", "menu_on.png");
	musicOn->setTag(1);
	auto musicOff = MenuItemImage::create("menu_off.png", "menu_off.png");
	musicOff->setTag(2);

	auto musicTogg = MenuItemToggle::createWithCallback(CC_CALLBACK_1(
		GameScene::menuMusicTogg, this), musicOn, musicOff, NULL);
	musicTogg->setPosition(Vec2(440, 550));

	Menu* mn = Menu::create(musicTogg, NULL);
	mn->setPosition(Vec2::ZERO);
	this->addChild(mn);

	//�����¼�
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	listener->setSwallowTouches(true);  
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}

//���ֿ���
void GameScene::menuMusicTogg(Ref* pSender){
	auto musicTogg = (MenuItemToggle*) pSender;

	if (musicTogg->getSelectedIndex() == 1){
		SimpleAudioEngine::getInstance()->pauseBackgroundMusic();//��ͣ���ű�������
	}
	else{
		SimpleAudioEngine::getInstance()->resumeBackgroundMusic();//�������ű�������
	}
}

//�����¼�
bool GameScene::onTouchBegan(Touch* touch, Event* event){
	Point pos = touch->getLocation();

	if (pos.y > 0 && pos.y < 128){
		if (pos.x > 0 && pos.x < 120){         //����
			leftMove();
		}
		else if (pos.x > 120 && pos.x < 240){  //����
			rightMove();
		}
		else if (pos.x > 240 && pos.x < 360){  //��ת
			fkRotate(shape);
		}
		else if (pos.x > 360 && pos.x < 480){  //����
			fastDrop(0.01f);
		}
	}

	return true;
}

//Ԥ������
void GameScene::PreviewBox(int box[4][2]){
	int s, zx, zy;
	s = 20;
	zx = 410;
	zy = 460;

	//���÷������ɫ	
	Colors[0] = Color3B(255, 0, 0);       
	Colors[1] = Color3B(0, 255, 0);       
	Colors[2] = Color3B(0, 0, 255);       
	Colors[3] = Color3B(255, 255, 0);     
	Colors[4] = Color3B(255, 0, 255);     
	Colors[5] = Color3B(0, 255, 255);     

	auto texture = TextureCache::getInstance()->getTextureForKey("box.png");       //ͼƬ������
	auto frame = SpriteFrame::createWithTexture(texture, Rect(0, 0, s - 1, s - 1));//��������֡
	for (int i = 0; i < 4; i++){
		auto sp = Sprite::createWithSpriteFrame(frame);                            //ͨ������������
		sp->setPosition(Point(zx + box[i][0] * s, zy + box[i][1] * s));            //������������λ��
		sp->setColor(Colors[preColor]);                                            //���÷������ɫ
		this->addChild(sp);
		sp->setTag(90 + i);
	}
}

//��������ͼ��
void GameScene::createFix()
{
	int ctime[7] = { 0, 1, 1, 1, 3, 3, 3 };

	auto sframe = SpriteFrame::create("box.png", Rect(0, 0, bSize - 1, bSize - 1));
	//����ͼ������
	int boxes[7][4][2]{
		{ { 0, 0 }, { 1, 0 }, { 0, 1 }, { 1, 1 } },	//"��" ���η���
		{ { 1, 0 }, { 0, 0 }, { 2, 0 }, { 3, 0 } },	// "1" ���η���
		{ { 1, 1 }, { 0, 0 }, { 1, 0 }, { 2, 1 } },	//"����"�η���
		{ { 1, 1 }, { 0, 1 }, { 1, 0 }, { 2, 0 } },	//"������" �η���
		{ { 1, 0 }, { 0, 0 }, { 2, 0 }, { 1, 1 } },	//"͹"	���η���
		{ { 1, 0 }, { 0, 0 }, { 0, 1 }, { 2, 0 } },	//"��L" �η���
		{ { 1, 0 }, { 0, 0 }, { 2, 0 }, { 2, 1 } }	//"L"  �η���
	};	
	//���÷������ɫ
	Colors[0] = Color3B(255, 0, 0);
	Colors[1] = Color3B(0, 255, 0);
	Colors[2] = Color3B(0, 0, 255);
	Colors[3] = Color3B(255, 255, 0);
	Colors[4] = Color3B(255, 0, 255);
	Colors[5] = Color3B(0, 255, 255);

	//ȡ����ɫ
	if (preColor == -1){
		preColor = rand() % 6;
	}
	
	//ȡ����״
	if (preShape == -1){
		shape = preShape;
		preShape = rand() % 7;
	}

	//��ȡ��״
	for (int i = 0; i < 4; i++){
		Sprite*box = Sprite::createWithSpriteFrame(sframe);
		box->setColor(Colors[preColor]);//������ɫ
		box->setAnchorPoint(Vec2(0, 0));//����ê�㣨���������յ㣩
		box->setPosition(Vec2(getX(4 + boxes[preShape][i][0]), getY(13 + boxes[preShape][i][1])));//����λ��
		this->addChild(box);
		box->setTag(110 + i);
		MoveList.pushBack(box); //���浽��������ķ���������
	}

	Eliminate(); //��������
	shape = preShape;
	preShape = rand() % 7;
	preColor = rand() % 6;
	PreviewBox(boxes[preShape]);
}

//����ת������        
float GameScene::getX(int x){
	return 85 + x * 31;
}
float GameScene::getY(int y){
	return 128 + y * 31;
}

//����ת������ 
int GameScene::getIx(float x){
	return (x - 85) / 31;
}
int GameScene::getIy(float y){
	return (y - 128) / 31;
}

//��ȡ��߸߶�
int GameScene::Highest(){
	int h = 0;
	for (int i = 0; i<StopList.size(); i++)
	{
		Sprite* box = StopList.at(i);
		int y = getIy(box->getPositionY());
		if (y > h)
			h = y;
	}
	return h;

}

//��������
void GameScene::fastDrop(float f){
	moveFks(0);
}

//�����ƶ�
void GameScene::boxMove(float delta){
	moveFks(0);
}

//��������
void GameScene::downMove(float delta)
{
	//��ȡ����������ĸ�����,�ı�����y��λ��
	for (auto block : MoveList)
	{
		block->setPositionY(getY(getIy(block->getPositionY()) - 1));
	}
}
//�ж��ܷ�����
void GameScene::moveFks(int num){
	//�Ȼ�ȡ4���������Ϣ
	Sprite *temp[4] = { NULL };
	for (int i = 0; i < 4; i++)
	{
		temp[i] = (Sprite *)this->getChildByTag(110 + i);
	}
	//�������ķ��������˵ײ����ķ���
	if (isCollSion(110) || isCollSion(111) || isCollSion(112) || isCollSion(113))
	{
		this->unschedule(schedule_selector(GameScene::downMove));
		for (int i = 0; i < 4; i++)
		{
			temp[i]->setTag(120);
			MoveList.eraseObject(temp[i]);
			this->StopList.pushBack(temp[i]);	//���浽ֹͣ���������
		}
		if (Highest() < 13)
		{
			for (int i = 0; i < 4; i++)
			{
				Sprite* remove = (Sprite*)this->getChildByTag(90 + i);
				remove->removeFromParent();
			}
			createFix();
		}
		else
		{
			//�洢��ǰ��������
			UserDefault::getInstance()->setIntegerForKey("score", score);
			//��¼��߷�
			int top_gf = UserDefault::getInstance()->getIntegerForKey("tallscore");
			if (score > top_gf){
				UserDefault::getInstance()->setIntegerForKey("tallscore", score);
			}

			Director::getInstance()->replaceScene(GameOver::createScene());

			SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
		}
	}
	else
	{
		downMove(0);
	}
}

//�ж��Ƿ���ײ
bool GameScene::isCollSion(int tag){
	Sprite* block = (Sprite*)this->getChildByTag(tag);
	Point pos_a, pos_b;
	Sprite* _block;
	bool flag = false;
	if (block == NULL)
	{
		return false;
	}
	pos_a.x = getIx(block->getPositionX());		
	pos_a.y = getIy(block->getPositionY());		
	for (int i = 0; i < StopList.size(); i++)	//��ײ���
	{
		_block = StopList.at(i);
		pos_b.x = getIx(_block->getPositionX());
		pos_b.y = getIy(_block->getPositionY());
		if (pos_a.y - pos_b.y == 1 && pos_a.x == pos_b.x)
		{
			flag = true;
		}
	}
	if (pos_a.y <= 0)
		flag = true;
	return flag;
}

//�жϷ����ܷ�����
bool GameScene::isBoxStopLeft()
{
	int M_x[4], M_y[4];
	int S_x, S_y;
	Point pos_stop;
	Sprite* stop_block;
	bool flag = true;

	//��ȡ�����ƶ��ķ��飬������������ת��Ϊ��������
	for (int i = 0; i < 4; i++)
	{
		Sprite *box = (Sprite *)this->getChildByTag(110 + i);
		if (box == NULL)
		{
			return false;
		}
		M_x[i] = getIx(box->getPositionX());
		M_y[i] = getIy(box->getPositionY());
	}

	//�жϴ˴����ƻ᲻�����
	for (int i = 0; i < 4; i++)
	{
		if (M_x[i] - 1 < 0)				
		{
			return false;
		}
	}

	//��ȡ�Ѿ�ֹͣ�ķ��飬������������ת��Ϊ��������,��������ײ�ж�
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < StopList.size(); j++)
		{
			stop_block = StopList.at(j);
			S_x = getIx(stop_block->getPositionX());
			S_y = getIy(stop_block->getPositionY());
			if (M_y[i] == S_y)
			{
				if (M_x[i] - 1 == S_x)
				{
					flag = false;
				}
			}
		}
	}
	return flag;
}

//��������
void GameScene::leftMove(){
	if (!isBoxStopLeft()){
		return;
	}
	Sprite*block = NULL;
	for (int i = 0; i < 4; i++){
		block = MoveList.at(i); 	
		block->setPositionX((block->getPositionX() - 31));
	}
}

//�жϷ����ܷ�����
bool GameScene::isBoxStopRight(){
	int M_x[4], M_y[4];
	int S_x, S_y;
	Point pos_stop;
	Sprite* stop_block;
	bool flag = true;

	//��ȡ�����ƶ��ķ��飬������������ת��Ϊ��������
	for (int i = 0; i < 4; i++)
	{
		Sprite *box = (Sprite *)this->getChildByTag(110 + i);
		if (box == NULL)
		{
			return false;
		}
		M_x[i] = getIx(box->getPositionX());
		M_y[i] = getIy(box->getPositionY());
	}

	//�жϴ˴����ƻ᲻�����
	for (int i = 0; i < 4; i++)
	{
		if (M_x[i] + 1 >= 10)			//ȷ�����ƺ󲻻����
		{
			return false;
		}
	}

	//��ȡ�Ѿ�ֹͣ�ķ��飬������������ת��Ϊ��������,��������ײ�ж�
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < StopList.size(); j++)
		{
			stop_block = StopList.at(j);
			S_x = getIx(stop_block->getPositionX());
			S_y = getIy(stop_block->getPositionY());
			if (M_y[i] == S_y)
			{
				if (M_x[i] + 1 == S_x)
				{
					flag = false;
				}
			}
		}
	}
	return flag;
}

//�������� 
void GameScene::rightMove()
{
	if (!isBoxStopRight()){
		return;
	}
	Sprite*block = NULL;
	for (int i = 0; i < 4; i++){
		block = MoveList.at(i);
		block->setPositionX((block->getPositionX() + 31));
	}
}

//�жϷ����ܷ���ת 
bool GameScene::isRotate(int x, int y)
{
	Sprite*block;
	bool flag = true;

	for (int i = 0; i < StopList.size(); i++)
	{
		block = StopList.at(i);
		int bx = getIx(block->getPositionX());
		int by = getIy(block->getPositionY());
		if (x == bx&&y == by){
			flag = false;//������ת
		}
	}
	if (x < 0 || x>9 || y < 0)
		flag = false;
	return flag;
}

//��ת����  
void GameScene::fkRotate(int num){
	static int boxs[] = { 0, 1, 1, 1, 3, 3, 3 };
	int flag = 0;
	Sprite*spBox[4] = { NULL };
	int bx[4], by[4];
	int fx[4], fy[4];
	for (int i = 0; i < 4; i++){
		spBox[i] = (Sprite*)this->getChildByTag(110 + i);
		if (spBox[i] == NULL){
			return;
		}
		bx[i] = getIx(spBox[i]->getPositionX());
		by[i] = getIy(spBox[i]->getPositionY());
	}
	//�жϱ��δ���
	if (boxs[num] == 0){
		//������
	}
	else if (boxs[num] == 1){
		if (flag == 0)
		{
			//˳ʱ����ת
			for (int i = 0; i < 4; i++)
			{
				fx[i] = bx[0] + (by[0] - by[i]);
				fy[i] = by[0] - (bx[0] - bx[i]);
			}
			flag = 1;
		}
		else if (flag == 1)
		{
			//��ʱ����ת
			for (int i = 0; i < 4; i++)
			{
				fx[i] = bx[0] - (by[0] - by[i]);
				fy[i] = by[0] + (bx[0] - bx[i]);
			}
			flag = 0;
		}
		//��������ת
		if (isRotate(fx[0], fy[0]) && isRotate(fx[1], fy[1]) && isRotate(fx[2], fy[2]) && isRotate(fx[3], fy[3]))
		{
			for (int i = 0; i < 4; i++){
				spBox[i]->setPositionX(getX(fx[i]));
				spBox[i]->setPositionY(getY(fy[i]));
			}
		}
		else
		{
			flag = (flag == 1) ? 0 : 1;
		}
	}
	else if (boxs[num] == 3){
		for (int i = 0; i < 4; i++){
			fx[i] = bx[0] - (by[0] - by[i]);
			fy[i] = by[0] + (bx[0] - bx[i]);
		}
	}
	if (isRotate(fx[0], fy[0]) && isRotate(fx[1], fy[1]) && isRotate(fx[2], fy[2]) && isRotate(fx[3], fy[3]))
	{
		for (int i = 0; i < 4; i++){
			spBox[i]->setPositionX(getX(fx[i]));
			spBox[i]->setPositionY(getY(fy[i]));
		}
	}
}

//��������  
void GameScene::Eliminate()
{
	int sum = 0;                                        //�ۼ�һ�еķ�����Ŀ
	int line;
	Sprite *Boxes[10] = { NULL };
	for (line = 0; line < 13; line++)
	{
		for (int j = 0; j < StopList.size(); j++)
		{
			Sprite* Box = StopList.at(j);
			if (getIy(Box->getPositionY()) == line)		//ɸѡ��line�з���
			{
				Boxes[sum++] = Box;					    //������з���
			}
		}
		if (sum == 10)
		{
			for (int i = 0; i < 10; i++)
			{
				StopList.eraseObject(Boxes[i]);
				Boxes[i]->removeFromParent();		    //�������ӷ�				

			}

			score = score + 1;			
			Fs->setString(String::createWithFormat("%d", score)->getCString());				
			
			for (int i = 0; i < StopList.size(); i++)
			{
				Sprite* Drop = StopList.at(i);
				int ThisLine = getIy(Drop->getPositionY());
				if (ThisLine > line)							//�����󣬰�λ�ڵ�line��֮�ϵķ���������
				{
					Drop->setPositionY(getY(ThisLine - 1));
				}
			}
			Eliminate();
		}
		sum = 0;
	}
}

//��¼���� 
void GameScene::ScoreSystem()
{	
	//��ȡXML�ļ�
	dic = Dictionary::createWithContentsOfFile("fonts/Chanies.xml");

	//��߷�����ʾ
	auto tall_score = Label::create();
	tall_score->setString(((__String*)(dic->objectForKey("tallscore")))->getCString());
	tall_score->setSystemFontSize(20);
	tall_score->setColor(Color3B::GREEN);
	tall_score->setAnchorPoint(Point(0.5, 0.5));
	tall_score->setPosition(Point(visibleSize.width - 440, visibleSize.height - 60));
	this->addChild(tall_score);

	Gf = Label::create();
	Gf->setSystemFontSize(20);
	Gf->setColor(Color3B::BLUE);
	Gf->setPosition(Point(visibleSize.width - 440, visibleSize.height - 90));
	this->addChild(Gf);

	//��ǰ������ʾ
	auto dq_score = Label::create();
	dq_score->setString(((__String*)(dic->objectForKey("score")))->getCString());
	dq_score->setSystemFontSize(20);
	dq_score->setColor(Color3B::GREEN);
	dq_score->setPosition(Point(visibleSize.width - 440, visibleSize.height - 120));
	this->addChild(dq_score);

	Fs = Label::create();
	Fs->setSystemFontSize(20);
	Fs->setColor(Color3B::BLUE);
	Fs->setPosition(Point(visibleSize.width - 440, visibleSize.height - 150));
	this->addChild(Fs);

	//UserDefault�洢��߷�
	int top_score = UserDefault::getInstance()->getIntegerForKey("tallscore");
	Gf->setString(String::createWithFormat("%d", top_score)->getCString());

	//��ǰ��
	Fs->setString(String::createWithFormat("%d", score)->getCString());	

	//�����ͣ��ť
	auto btn_label = Label::create();
	btn_label->setString(((__String*)(dic->objectForKey("suspend")))->getCString());
	btn_label->setSystemFontSize(30);

	auto zt_menu = MenuItemLabel::create(btn_label,
		CC_CALLBACK_1(GameScene::Suspend, this));

	Menu* btn_menu = Menu::create(zt_menu, NULL);
	btn_menu->setPosition(Vec2(visibleSize.width - btn_label->getContentSize().width / 2 - 13, visibleSize.height - 250));
	this->addChild(btn_menu);
}

//��ͣ��ť����
void GameScene::Suspend(Ref* pSender)
{
	//��ȡXML�ļ�
	dic = Dictionary::createWithContentsOfFile("fonts/Chanies.xml");
		
	SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
	this->pause();
	for (const auto&node : this->getChildren())
	{
		node->pause();
	}

	//������Ϸ��ť
	auto go_on = Label::create();
	go_on->setString(((__String*)(dic->objectForKey("goOn")))->getCString());
	go_on->setSystemFontSize(30);
	auto go_menu = MenuItemLabel::create(go_on, CC_CALLBACK_1(GameScene::Continue, this));
	
	menu_on = Menu::create(go_menu, NULL);
	menu_on->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 2 / 3));
	this->addChild(menu_on);	

	//���¿�ʼ��ť
	auto restart = Label::create();
	restart->setString(((__String*)(dic->objectForKey("restart")))->getCString());
	restart->setSystemFontSize(30);
	auto restart_menu = MenuItemLabel::create(restart, CC_CALLBACK_1(GameScene::Restart, this));

	restart_on = Menu::create(restart_menu, NULL);
	restart_on->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 2 / 4));
	this->addChild(restart_on);
}

//������Ϸ��ť����
void GameScene::Continue(Ref* pSender)
{	
	//�������ű�������
	SimpleAudioEngine::getInstance()->resumeBackgroundMusic();

	//������ǰ���NodeԪ��
	this->resume();

	//������ǰ�����NodeԪ��
	for (const auto&node : this->getChildren())
	{
		node->resume();
	}
	//���˵���ť�Ƴ�
	removeChild(menu_on);
	removeChild(restart_on);
}

void GameScene::Restart(Ref* pSender){
	Director::getInstance()->replaceScene(StartScene::createScene());
}