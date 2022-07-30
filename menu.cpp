#include "ImGui/ImGui.h"
#include "ImGui/imgui_impl_dx9.h"
#include "ImGui/imgui_impl_win32.h"

#include "menu.h"
#include "globals.h"

#include <iostream>
#include <windows.h>
#include <string>

class initWindow {
public:
    const char* window_title = "Kinta Helper";
    ImVec2 window_size{ 400, 330 };
    ImVec2 window_size2{ 150, 170 }; //width, height
    
    DWORD window_flags = ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize;
} iw;

struct nekoPatches {
    bool isinRoom = false;
    bool espLine, espBox, espHealth, espName, espDistance, espHero, espMonsterHealth, espMonsterBox, showSkillCD, showSpellCD = false;
    bool aimSkill1, aimSkill2, aimSkill3, aimSkill4, aimBasicAtk, aimBattleSpell = false;
    bool isClosestTarget, isLowestHP = false;
    bool autoRetri, retriPriority = false;
    bool targetLord, targetTurtle, targetLithowanderer, targetPurple, targetRed, targetGold = false;
    int droneValue = 1;
    float targetRange = 25.0f;
} nekoPatch;

struct ImGuiParameterState {
    int selected_radio;
};

static ImGuiParameterState state;

void menu::render()
{
    if (globals.active)
    {
        ImGui::SetNextWindowSize(iw.window_size);
        ImGui::SetNextWindowBgAlpha(1.0f);
        ImGui::Begin(iw.window_title, &globals.active, iw.window_flags);
        {
            if (ImGui::BeginTabBar("Cheat Function", ImGuiTabBarFlags_None)) {
                if (ImGui::BeginTabItem("Visual Menu")) {
                    ImGui::Text("View Camera");
                    ImGui::SliderInt("##dronevalue", &nekoPatch.droneValue, 1, 100);

                    ImGui::NewLine();

                    ImGui::Text("ESP:");
                    ImGui::Columns(2);

                    ImGui::Text("Player ESP:");
                    ImGui::BeginGroup();
                    ImGui::Checkbox("Line", &nekoPatch.espLine);
                    ImGui::Checkbox("Box", &nekoPatch.espBox);
                    ImGui::Checkbox("Health", &nekoPatch.espHealth);
                    ImGui::Checkbox("Name", &nekoPatch.espName);
                    ImGui::Checkbox("Distance", &nekoPatch.espDistance);
                    ImGui::Checkbox("Hero", &nekoPatch.espHero);
                    ImGui::EndGroup();

                    ImGui::NextColumn();

                    ImGui::Text("Jungle ESP:");
                    ImGui::BeginGroup();
                    ImGui::Checkbox("Monster Health", &nekoPatch.espMonsterHealth);
                    ImGui::Checkbox("Monster Box", &nekoPatch.espMonsterBox);
                    ImGui::EndGroup();

                    ImGui::NewLine();

                    ImGui::Text("Info ESP:");
                    ImGui::BeginGroup();
                    ImGui::Checkbox("Show Skill CD", &nekoPatch.showSkillCD);
                    ImGui::Checkbox("Show Spell CD", &nekoPatch.showSpellCD);
                    ImGui::EndGroup();

                    ImGui::Columns(1);

                    ImGui::EndTabItem();
                }
                if (ImGui::BeginTabItem("Helper Menu")) {
                    ImGui::Text("Auto Aim:");
                    ImGui::Columns(2);

                    ImGui::Text("Skills:");
                    ImGui::BeginGroup();
                    ImGui::Checkbox("Skill 1", &nekoPatch.aimSkill1);
                    ImGui::Checkbox("Skill 2", &nekoPatch.aimSkill2);
                    ImGui::Checkbox("Skill 3", &nekoPatch.aimSkill3);
                    ImGui::Checkbox("Skill 4", &nekoPatch.aimSkill4);
                    ImGui::NewLine();
                    ImGui::Text("Auto Retribution:");
                    ImGui::Checkbox("Enable", &nekoPatch.autoRetri);
                    ImGui::Checkbox("Priority Only", &nekoPatch.retriPriority);
                    ImGui::EndGroup();

                    if (nekoPatch.retriPriority == true) {
                        ImGui::SetNextWindowSize(iw.window_size2);
                        ImGui::SetNextWindowBgAlpha(1.0f);
                        ImGui::Begin("Target Priority", nullptr, iw.window_flags);
                        ImGui::Checkbox("Lord", &nekoPatch.targetLord);
                        ImGui::Checkbox("Turtle", &nekoPatch.targetTurtle);
                        ImGui::Checkbox("Lithowanderer", &nekoPatch.targetLithowanderer);
                        ImGui::Checkbox("Purple Buff", &nekoPatch.targetPurple);
                        ImGui::Checkbox("Red Buff", &nekoPatch.targetRed);
                        ImGui::Checkbox("Gold Buff", &nekoPatch.targetGold);
                        ImGui::End();
                    }

                    ImGui::NextColumn();

                    ImGui::Text("Other:");
                    ImGui::BeginGroup();
                    ImGui::Checkbox("Basic Attack", &nekoPatch.aimBasicAtk);
                    ImGui::Checkbox("Spell", &nekoPatch.aimBattleSpell);
                    ImGui::NewLine();
                    ImGui::Text("Target Priority:");
                    ImGui::PushID(0);
                    if (ImGui::RadioButton("Closest Target", &state.selected_radio, 0)) {
                        // code for closest target
                    }
                    ImGui::PopID();
                    ImGui::PushID(1);
                    if (ImGui::RadioButton("Lowest HP", &state.selected_radio, 1)) {
                        // code for lowest hp target
                    }
                    ImGui::PopID();
                    ImGui::Text("Range (0 for No Limit):");
                    ImGui::SliderFloat("##sliderRange", &nekoPatch.targetRange, 0.0f, 50.0f);
                    ImGui::EndGroup();

                    ImGui::Columns(1);

                    ImGui::EndTabItem();
                }
                if (ImGui::BeginTabItem("Room Info")) {
                    char team_info[] = "Team Info:";
                    char enemy_info[] = "Enemy Info:";
                    if (!nekoPatch.isinRoom) {
                        // Table Team
                        ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(104, 104, 255, 255));
                        ImGui::Text(team_info);
                        ImGui::PopStyleColor();
                        if (ImGui::BeginTable("Team", 5))
                        {
                            char playerName[] = "Hiruzen.";
                            char squadName[] = "No Squad";
                            char isVerifiedSquad[] = "No";
                            char rankInfo[] = "Epic IV";
                            char rankPoint[] = "20";
                            ImGui::TableNextColumn();
                            ImGui::Text("Name");
                            ImGui::TableNextColumn();
                            ImGui::Text("Squad");
                            ImGui::TableNextColumn();
                            ImGui::Text("Verified");
                            ImGui::TableNextColumn();
                            ImGui::Text("Rank");
                            ImGui::TableNextColumn();
                            ImGui::Text("Point(s)");
                            ImGui::Separator();
                            for (int i = 0; i < 5; i++) {
                                ImGui::TableNextColumn();
                                ImGui::Text("%s", playerName);
                                ImGui::TableNextColumn();
                                ImGui::Text("%s", squadName);
                                ImGui::TableNextColumn();
                                ImGui::Text("%s", isVerifiedSquad);
                                ImGui::TableNextColumn();
                                ImGui::Text("%s", rankInfo);
                                ImGui::TableNextColumn();
                                ImGui::Text("%s", rankPoint);
                            }
                            ImGui::EndTable();
                        }
                        // END Table Team
                        ImGui::NewLine();
                        // Table Enemy
                        ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 0, 0, 255));
                        ImGui::Text(enemy_info);
                        ImGui::PopStyleColor();
                        if (ImGui::BeginTable("Enemy", 5))
                        {
                            char playerName[100] = "Hiruzen.";
                            char squadName[100] = "No Squad";
                            char isVerifiedSquad[4] = "No";
                            char rankInfo[100] = "Epic IV";
                            char rankPoint[10000] = "20";
                            ImGui::TableNextColumn();
                            ImGui::Text("Name");
                            ImGui::TableNextColumn();
                            ImGui::Text("Squad");
                            ImGui::TableNextColumn();
                            ImGui::Text("Verified");
                            ImGui::TableNextColumn();
                            ImGui::Text("Rank");
                            ImGui::TableNextColumn();
                            ImGui::Text("Point(s)");
                            ImGui::Separator();
                            for (int i = 0; i < 5; i++) {
                                ImGui::TableNextColumn();
                                ImGui::Text("%s", playerName);
                                ImGui::TableNextColumn();
                                ImGui::Text("%s", squadName);
                                ImGui::TableNextColumn();
                                ImGui::Text("%s", isVerifiedSquad);
                                ImGui::TableNextColumn();
                                ImGui::Text("%s", rankInfo);
                                ImGui::TableNextColumn();
                                ImGui::Text("%s", rankPoint);
                            }
                            ImGui::EndTable();
                        }
                        // END Table Enemy
                    }
                    else {
                        ImGui::Text("You're not in any room / match");
                    }
                    ImGui::EndTabItem();
                }
                
                ImGui::EndTabBar();
            }
        }
        ImGui::End();
    }
    else
    {
        exit(0);
    }
}