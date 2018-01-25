//
//  Mapper.hpp
//  SpritebuilderIOS
//
//  Created by Oleh on 11/5/17.
//

#ifndef Mapper_hpp
#define Mapper_hpp
namespace mapper {
enum CC_TYPE {
    NODE,BUTTON,EDITTEXT,SPRITE,LIST
};
    std::unordered_map<std::string, CC_TYPE> typeMap;
    
}

#endif /* Mapper_hpp */
