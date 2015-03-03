#include "HelloWorldScene.h"

USING_NS_CC;

HelloWorld::~HelloWorld(){
	m_Darkmask->release();
}

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	
	//背景追加
	Sprite* back = Sprite::create("HelloWorld.png");
	back->setPosition(visibleSize / 2);
	addChild(back);

	//暗闇追加
	m_Darkmask = Sprite::create("DarkMask.png");
	m_Darkmask->setPosition(visibleSize / 2);
	m_Darkmask->retain(); //addChildされているものをやりたい場合はいらない。
	
	//ライト画像を追加
	m_Light = Sprite::create("Light.png");
	m_Light->setPosition(visibleSize / 2);
	m_Light->retain();

	//暗闇から切り抜くため、アルファブレンドをします。
	BlendFunc blend;
	blend.src = GL_DST_COLOR;
	blend.dst = GL_ONE;

	m_Light->setBlendFunc(blend);


	//オフスクリーンレンダリング用のテクスチャ作成
	RenderTexture* texture = RenderTexture::create(visibleSize.width, visibleSize.height);
	texture->setPosition(visibleSize / 2);
	
	//オフスクリーンレンダリング開始
	texture->beginWithClear(1, 1, 1, 1);
	{
		m_Darkmask->visit();
		
		//一回の描画だけではかなり薄いので繰り返し描画させます。
		for (int i = 0; i < 4; i++){
			m_Light->visit();
		}
	}
	texture->end();

	addChild(texture);

	//暗闇に乗算合成を設定ます。
	blend.src = GL_ZERO;
	blend.dst = GL_SRC_COLOR;

	texture->getSprite()->setBlendFunc(blend);
 }


void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
