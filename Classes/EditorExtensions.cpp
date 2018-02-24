//
// Created by oleh on 23.02.18.
//

#include "EditorExtensions.h"

void editor::physicsEditor(b2Sprite *sprite) {

    if (ImGui::CollapsingHeader("Sprite properties")) {

        int bodyType = sprite->bodyDef.type;
        const char *bodyTypes[] = {"Static", "Kinematic","Dynamic"};
        const char *fixtureTypes[] = {"Circle", "Edge", "Polygon", "Chain"};

        if (ImGui::Combo("Body type", &bodyType, bodyTypes, 3)) {
          sprite->bodyDef.type = b2BodyType(bodyType);
        }

        if(ImGui::Button("Create fixture")){
            sprite->createSquareFixture();
        }

        int counter = 0;
        for (EditableDrawNode *editableDrawNode : *sprite->getEditableDrawNodes()) {


            if (ImGui::TreeNode(StringUtils::format("Fixture %d", counter++).c_str())) {
                ImGui::Indent();
                b2FixtureDef *f = editableDrawNode->getFixture();
                if (ImGui::SliderFloat("Restitution", &f->restitution, 0, 1)) {}
                if (ImGui::SliderFloat("Friction", &f->friction, 0, 1)) {}
                if (ImGui::SliderFloat("Density", &f->density, 0, 5)) {}
                if (ImGui::Checkbox("Is sensor", &f->isSensor)) {}

                int fixtureType = editableDrawNode->getType();

                if (ImGui::Combo("Fixture type", &fixtureType, fixtureTypes, 4)) {
                    editableDrawNode->setType(EditableDrawNode::ShapeType(fixtureType));
                    editableDrawNode->redraw();
                }

                if(ImGui::Button("Add point")){
                    editableDrawNode->addPoint(Vec2::ZERO);
                    editableDrawNode->redraw();
                }
                int c = 0;
                for (Rect *r: *editableDrawNode->getRects()) {

                    const char *label = StringUtils::format("Point %d", c++).c_str();
                    if (ImGui::DragFloat2(label, &r->origin.x, 0.1f)) {
                        editableDrawNode->redraw();
                    }

                    ImGui::SameLine();
                    if(ImGui::Button("x")){

                    }
                }
                ImGui::Unindent();
                ImGui::TreePop();
            }
        }

    }
}

//
//        if (ImGui::CollapsingHeader("Physics")) {
//
//
//            if (editableNodeTree && editableNodeTree->enablePhysics) {
//                const char *items[] = {
//                        "Static", "Dynamic", "Kinematic"
//                };
//
//
//                if (!editableNodeTree->physics) {
//                    editNodeBuilder.createDefaultPhysics(editableNodeTree);
//                }
//
//                BodyT *body = editableNodeTree->physics.get();
//                int type = body->type;
//                //static int position = 0;
//                if (ImGui::Combo("Types", &type, items, 3)) body->type = BodyType(type);
//
//
//                Vec2 pos(body->pos->x(), body->pos->y());
//                if (ImGui::DragFloat2("Body position", &pos.x))body->pos.reset(new Vec2f(pos.x, pos.y));
//
//                ImGui::Text("Points");
//
//
//                for (int i = 0; i < body->fixtures.size(); i++) {
//
//                    if (ImGui::TreeNode(StringUtils::format("Fixture %d", i).c_str())) {
//
//
//                        FixtureT *fixtureT = body->fixtures[i].get();
//
//
//                        const char *fixtureTypes[] = {
//                                "Polygon", "Circle", "Line"
//                        };
//                        int fixtureType = fixtureT->type;
//                        if (ImGui::Combo("Fixture type", &fixtureType, fixtureTypes, 3))
//                            fixtureT->type = FixtureType(fixtureType);
//
//
//                        for (int j = 0; j < fixtureT->points.size(); j++) {
//                            const char *label = StringUtils::format("Point %d", j).c_str();
//                            Vec2 fixPos(fixtureT->points[j].x(), fixtureT->points[j].y());
//                            if (ImGui::DragFloat2(label, &fixPos.x))fixtureT->points[j] = Vec2f(fixPos.x, fixPos.y);
//                            ImGui::SameLine();
//                            ImGui::PushID(j);
//                            if (ImGui::Button("x")) {
//                                fixtureT->points.erase(fixtureT->points.begin() + j);
//                            }
//                            ImGui::PopID();
//                        }
//
//                        if (ImGui::Button("Add point")) {
//                            fixtureT->points.push_back(Vec2f(0, 0));
//                        }
//
//                        ImGui::TreePop();
//                    }
//                }
//            }
//        }







