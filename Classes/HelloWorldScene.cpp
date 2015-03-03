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
	
	//�w�i�ǉ�
	Sprite* back = Sprite::create("HelloWorld.png");
	back->setPosition(visibleSize / 2);
	addChild(back);

	//�ÈŒǉ�
	m_Darkmask = Sprite::create("DarkMask.png");
	m_Darkmask->setPosition(visibleSize / 2);
	m_Darkmask->retain(); //addChild����Ă�����̂���肽���ꍇ�͂���Ȃ��B
	
	//���C�g�摜��ǉ�
	m_Light = Sprite::create("Light.png");
	m_Light->setPosition(visibleSize / 2);
	m_Light->retain();

	//�Èł���؂蔲�����߁A�A���t�@�u�����h�����܂��B
	BlendFunc blend;
	blend.src = GL_DST_COLOR;
	blend.dst = GL_ONE;

	m_Light->setBlendFunc(blend);


	//�I�t�X�N���[�������_�����O�p�̃e�N�X�`���쐬
	RenderTexture* texture = RenderTexture::create(visibleSize.width, visibleSize.height);
	texture->setPosition(visibleSize / 2);
	
	//�I�t�X�N���[�������_�����O�J�n
	texture->beginWithClear(1, 1, 1, 1);
	{
		m_Darkmask->visit();
		
		//���̕`�悾���ł͂��Ȃ蔖���̂ŌJ��Ԃ��`�悳���܂��B
		for (int i = 0; i < 4; i++){
			m_Light->visit();
		}
	}
	texture->end();

	addChild(texture);

	//�Èłɏ�Z������ݒ�܂��B
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
