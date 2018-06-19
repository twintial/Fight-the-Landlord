#include<SettingScene.h>
USING_NS_CC;
using namespace ui;
using namespace CocosDenshion;
Scene* SettingScene::CreateScene()
{
	return SettingScene::create();
}
bool SettingScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	ReturnButton();
	BGMVolume();
	return true;
}
void SettingScene::ReturnStartScene(Ref *pSender)
{
	Director::getInstance()->popScene();
}
void SettingScene::ReturnButton()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto button = Sprite::create("return.png");
	auto returnItem = MenuItemSprite::create(button, button, CC_CALLBACK_1(SettingScene::ReturnStartScene, this));
	auto menu = Menu::create(returnItem, NULL);
	menu->setPosition(visibleSize.width - returnItem->getContentSize().width / 2, visibleSize.height - returnItem->getContentSize().height / 2);
	this->addChild(menu);
}
void SettingScene::BGMVolume()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto music_slider = Slider::create();
	music_slider->loadBarTexture("dark.png");
	music_slider->loadSlidBallTextures("adjust_button.png", "adjust_button.png", "");
	music_slider->loadProgressBarTexture("light.png");
	//��ȡ֮ǰ���õı�������
	float music_percent = UserDefault::getInstance()->getFloatForKey("music_percent");
	if (music_percent == 0.0f)
	{
		music_percent = 100.0f;
	}
	//���û�������ʼֵ
	music_slider->setPercent(music_percent);
	music_slider->setPosition(visibleSize / 2);
	//ʵ�ֵ��������Ĺ���
	music_slider->addEventListener([=](Ref* pSender, Slider::EventType type)
	{
		if (type == Slider::EventType::ON_PERCENTAGE_CHANGED)
		{
			//��ȡ�����ٷֱ�
			float percent = music_slider->getPercent();
			SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(percent / 100);
			//�������õ�����
			UserDefault::getInstance()->setFloatForKey("music_percent", percent);
		}
	});
	addChild(music_slider);
}