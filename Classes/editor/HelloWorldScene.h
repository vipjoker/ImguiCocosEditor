#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include <vector>


USING_NS_CC;
class HelloWorld : public cocos2d::Scene
{
    Sprite3D *house;
    DrawNode *drawNode;
    LayerColor *background;
    std::vector<Vec2> vectors;
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init() override;
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    void drawLine(const Vec2 begin,const Vec2 end);
    void drawCircle(const Vec2 center,Color4F color = Color4F::RED );
    void addCorner(std::vector<Vec2> &points,const Vec2 begin,const Vec2 end);
    void addLine(std::vector<Vec2> &points);
    void update(float dt) override;
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
