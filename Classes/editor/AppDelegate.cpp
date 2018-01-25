#include "AppDelegate.h"
#include "editor/EditorScene.h"
#include "OpeglShader.hpp"
#include "Res.h"
// #define USE_AUDIO_ENGINE 1
// #define USE_SIMPLE_AUDIO_ENGINE 1

#if USE_AUDIO_ENGINE && USE_SIMPLE_AUDIO_ENGINE
#error "Don't use AudioEngine and SimpleAudioEngine at the same time. Please just select one in your game!"
#endif

#if USE_AUDIO_ENGINE
#include "audio/include/AudioEngine.h"
using namespace cocos2d::experimental;
#elif USE_SIMPLE_AUDIO_ENGINE
#include "audio/include/SimpleAudioEngine.h"
using namespace CocosDenshion;
#endif

USING_NS_CC;


AppDelegate::AppDelegate(){}

AppDelegate::~AppDelegate() 
{
#if USE_AUDIO_ENGINE
    AudioEngine::end();
#elif USE_SIMPLE_AUDIO_ENGINE
    SimpleAudioEngine::end();
#endif
}

void AppDelegate::initGLContextAttrs()
{
    // set OpenGL context attributes: red,green,blue,alpha,depth,stencil,multisamplesCount
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8, 0};
    GLView::setGLContextAttrs(glContextAttrs);
}



bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    
    Size s = Size(640,480);
    
    auto glview = director->getOpenGLView();
    

    
    
    if(!glview) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
        glview =  GLViewImpl::create("Editor", true);
        
#else
        glview = GLViewImpl::create("SpritebuilderIOS");
#endif
        director->setOpenGLView(glview);
    }

    
   

    
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    director->setDisplayStats(true);
    director->setAnimationInterval(1.0f / 60);
    
    Size glSize =  glview->getFrameSize();
    glview->setDesignResolutionSize(glSize.width, glSize.height, ResolutionPolicy::NO_BORDER);
    scene = OpenGlShader::createScene();
    director->runWithScene(scene);

    return true;
}

void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();
    
#if USE_AUDIO_ENGINE
    AudioEngine::pauseAll();
#elif USE_SIMPLE_AUDIO_ENGINE
    SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
    SimpleAudioEngine::getInstance()->pauseAllEffects();
#endif
}


// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();
    
#if USE_AUDIO_ENGINE
    AudioEngine::resumeAll();
#elif USE_SIMPLE_AUDIO_ENGINE
    SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
    SimpleAudioEngine::getInstance()->resumeAllEffects();
#endif
}

// this function will be called when the app windows is resized
void AppDelegate::applicationScreenSizeChanged(int newWidth, int newHeight)
{
    auto view = Director::getInstance()->getOpenGLView();
    CCLOG("RESIZE %d %d",newWidth,newHeight);
    EventCustom e(constants::RESIZE_EVENT);
    Size *s = new Size(newWidth,newHeight);
    e.setUserData(s);
    scene->getEventDispatcher()->dispatchEvent(&e);
    view->setDesignResolutionSize(newWidth ,newHeight,ResolutionPolicy::NO_BORDER);
}
