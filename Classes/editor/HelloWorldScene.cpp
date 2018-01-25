#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

int getPt( int n1 , int n2 , float perc )
{
    int diff = n2 - n1;
    
    return n1 + ( diff * perc );
}

bool HelloWorld::init()
{
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width/2;
        float y = origin.y + closeItem->getContentSize().height/2;
        closeItem->setPosition(Vec2(x,y));
    }

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    if (label == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        // position the label on the center of the screen
        label->setPosition(Vec2(origin.x + visibleSize.width/2,
                                origin.y + visibleSize.height - label->getContentSize().height));

        // add the label as a child to this layer
        this->addChild(label, 1);
    }

    drawNode = DrawNode::create(3);
    addChild(drawNode,2);
    background = LayerColor::create(Color4B::WHITE, visibleSize.width, visibleSize.height);
    
//    addChild(background,1);
    
    
    EventListenerTouchOneByOne *listener = EventListenerTouchOneByOne::create();
    bool fileex = FileUtils::getInstance()->isFileExist("woodTex.jpg");
    
    if(fileex)CCLOG("Exists");
    else CCLOG("Not exists");
//    auto spr = Sprite::create("house.c3b");
//    addChild(spr,3);
    house = Sprite3D::create("rabbit.c3b");
  
    house->setTexture("woodTex.jpg");
    house->setColor(Color3B::RED);
    
 
    
    addChild(house,3);
    
    house->setPositionNormalized(Point::ANCHOR_MIDDLE);
    
   
    
    
    
    listener->onTouchBegan = [this](Touch *touch,Event *event){
        vectors.push_back(touch->getLocation());
        
      //  drawNode->clear();
        for(int i = 0 ; i < vectors.size(); i ++){
            
            Vec2 point = vectors.at(i);
            
                drawNode->drawSolidCircle(point, 20, 360, 32, 1, 1,Color4F::BLUE);
            if(i != 0){
                drawNode->drawLine(vectors[i-1], point, Color4F::GREEN);
                
            }
            
        }
       
        return true;
    };
    scheduleUpdate();
    getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
    
    return true;
}
void HelloWorld::addCorner(std::vector<Vec2> &points, const Vec2 begin,const Vec2 end){
    Vec2 control(200,100);
    Vec2 first(0,100);
    Vec2 dest(200,50);
    drawCircle(first);
    drawCircle(dest);
    drawCircle(control);
    float precision = 32;
    std::vector<Vec2> vectors2;
    vectors2.push_back(first);
    for(float i = 1/precision ; i < 1 ; i+= 1/precision){
        Vec2 begin =first.lerp( control,i);
        Vec2 end = control.lerp(dest,i);
        Vec2 res = begin.lerp(end,i);
        vectors2.push_back(res);
        
    }
    
    vectors2.push_back(dest);
    
    
    
    
    
    
    drawNode->drawSolidPoly(vectors2.data(), vectors2.size(), Color4F::GREEN);
    drawNode->drawPoly(vectors2.data(), vectors2.size(),true, Color4F::BLUE);
    
}


void HelloWorld::update(float dt){
   
    house->setRotation3D(house->getRotation3D() + Vec3(0,1,0));
}

void HelloWorld::addLine(std::vector<Vec2> &points){
    
}


void HelloWorld::drawLine(const Vec2 begin,const Vec2 end){
    drawNode->drawLine(begin, end, Color4F::BLACK);
}

void HelloWorld::drawCircle(const Vec2 center,Color4F color ){
    drawNode->drawSolidCircle(center, 10, 180, 32, 1, 1, color );
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif

}
