##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=iSSB
ConfigurationName      :=Debug
WorkspacePath          :=/home/luis/Code/iSSB/Projects/Codelite
ProjectPath            :=/home/luis/Code/iSSB/Projects/Codelite
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Luis Finke
Date                   :=13/05/21
CodeLitePath           :=/home/luis/.codelite
LinkerName             :=/usr/bin/clang++
SharedObjectLinkerName :=/usr/bin/clang++ -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=$(PreprocessorSwitch)SMASHBROS_SCRIPT_DISABLE 
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="iSSB.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch)../../src $(IncludeSwitch)../../External/ChaiScript/include $(IncludeSwitch)../../External/SDL/SDL/include $(IncludeSwitch)../../External/SDL/SDL_image $(IncludeSwitch)../../External/SDL/SDL_mixer $(IncludeSwitch)../../External/SDL/SDL_ttf $(IncludeSwitch)../../External/SDL/SDL_gfx $(IncludeSwitch)../../External/SDL/SDL_p2p/include 
IncludePCH             := 
RcIncludePath          := 
Libs                   := $(LibrarySwitch)SDL2 $(LibrarySwitch)SDL2_image $(LibrarySwitch)SDL2_mixer $(LibrarySwitch)SDL2_ttf $(LibrarySwitch)SDL_p2p $(LibrarySwitch)pthread 
ArLibs                 :=  "SDL2" "SDL2_image" "SDL2_mixer" "SDL2_ttf" "SDL_p2p" "pthread" 
LibPath                := $(LibraryPathSwitch). $(LibraryPathSwitch)../../External/SDL/SDL_p2p/projects/codelite/Debug 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := /usr/bin/ar rcu
CXX      := /usr/bin/clang++
CC       := /usr/bin/clang
CXXFLAGS :=  -g -O0 -std=c++17  $(Preprocessors)
CFLAGS   :=  -g -O0  $(Preprocessors)
ASFLAGS  := 
AS       := /usr/bin/as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/up_up_Source_SmashBros_Game_Stages_StagePieces_Platform.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_Source_ScriptModule_modules_GameEngine_inherit_lib_ge_inherit_Actor.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_Source_ScriptModule_modules_GameEngine_inherit_lib_ge_inherit_TextActor.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_Source_ScriptModule_modules_GameEngine_inherit_lib_ge_inherit_WireframeActor.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_Source_ScriptModule_modules_SmashBros_inherit_lib_sb_inherit_Player.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_Source_ScriptModule_modules_SmashBros_inherit_lib_sb_inherit_Stage.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_Source_SmashBros_Menus_MenuPieces_ActorGrid.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_Source_SmashBros_Menus_MenuPieces_Arrows.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_Source_SmashBros_Menus_MenuPieces_MenuBar.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_Source_SmashBros_Game_Stages_StagePieces_HangPoint.cpp$(ObjectSuffix) \
	$(IntermediateDirectory)/up_up_Source_SmashBros_Menus_MenuPieces_MenuBarSmall.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_Source_SmashBros_Menus_MenuPieces_MenuBarValue.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_Source_SmashBros_Menus_MenuPieces_ToggleButton.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_Source_SmashBros_Menus_MenuPieces_TogglePane.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_Source_SmashBros_Menus_MenuPieces_MenuBarToggle.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_Source_SmashBros_Game_Characters_Pikachu.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_Source_SmashBros_Game_Characters_Sonic.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_Source_SmashBros_Game_Items_BeamSword.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_Source_SmashBros_Game_Items_SuperMushroom.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_Source_SmashBros_Game_Characters_Link.cpp$(ObjectSuffix) \
	$(IntermediateDirectory)/up_up_Source_SmashBros_Game_Stages_FinalDestinationBrawl.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_Source_SmashBros_Game_Stages_FractalStage.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_Source_SmashBros_Game_Characters_Ichigo.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_Source_SmashBros_Game_Stages_HillsideBattleground.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_Source_ScriptModule_modules_GameEngine_lib_ge_Actor.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_Source_SmashBros_Game_Items_PoisonMushroom.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_Source_ScriptModule_modules_GameEngine_lib_ge_IO.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_Source_ScriptModule_modules_GameEngine_lib_ge_ScreenManager.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_Source_SmashBros_Game_Characters_Mario.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_Source_ScriptModule_modules_GameEngine_lib_ge_Util.cpp$(ObjectSuffix) \
	$(IntermediateDirectory)/up_up_Source_ScriptModule_modules_SmashBros_lib_sb_GameElement.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_Source_ScriptModule_modules_SmashBros_lib_sb_Stage.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_Source_ScriptModule_modules_SmashBros_lib_SmashBros.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_Source_GameEngine_Actor_Animation.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_Source_GameEngine_Actor_WireframeActor.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_Source_ScriptModule_modules_GameEngine_lib_ge_Graphics.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_Source_SmashBros_Menus_MenuPieces_ToggleButtons.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_Source_ScriptModule_modules_GameEngine_lib_ge_Global.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_Source_GameEngine_CodeBridge_ObjCBridge.mm$(ObjectSuffix) $(IntermediateDirectory)/up_up_Source_ScriptModule_modules_SmashBros_inherit_lib_sb_inherit_GameElement.cpp$(ObjectSuffix) \
	$(IntermediateDirectory)/up_up_Source_SmashBros_Game_Items_SmashBall.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_Source_ScriptModule_modules_GameEngine_lib_ge_Math.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_Source_GameEngine_CodeBridge_WinBridge.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_Source_GameEngine_Graphics_Graphics2D.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_Source_SmashBros_AttackRandomizer.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_Source_GameEngine_Util_Font.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_Source_SmashBros_AttackTemplates.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_Source_SmashBros_HitBox.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_Source_SmashBros_Game_Stages_BattlefieldBrawl.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_Source_GameEngine_Util_FileTools.cpp$(ObjectSuffix) \
	$(IntermediateDirectory)/up_up_Source_ScriptModule_modules_SmashBros_lib_sb_Player.cpp$(ObjectSuffix) 

Objects1=$(IntermediateDirectory)/up_up_Source_SmashBros_Stage.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_Source_GameEngine_ScreenManager_MenuScreen.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_Source_ScriptModule_ScriptManager.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_Source_ScriptModule_ScriptEntity.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_Source_SmashBros_Projectile.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_Source_ScriptModule_ScriptOperatorOverloads.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_Source_Game.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_Source_GameEngine_Util_HapticFeedback.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_Source_SmashBros_Chargebar.cpp$(ObjectSuffix) \
	$(IntermediateDirectory)/up_up_Source_SmashBros_CollisionManager.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_Source_SmashBros_Menus_MenuPieces_MenuBarSmallButton.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_Source_SmashBros_Camera.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_Source_GameEngine_AssetManager.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_Source_SmashBros_GameElement.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_Source_ScriptModule_modules_GameEngine_inherit_lib_ge_inherit_Screen.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_Source_SmashBros_Controls.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_Source_SmashBros_P2PDataManager.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_Source_SmashBros_Game_Stages_StagePieces_OffScreenExplode.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_Source_GameEngine_Actor_AnimationManager.cpp$(ObjectSuffix) \
	$(IntermediateDirectory)/up_up_Source_GameEngine_CodeBridge_CPPBridge.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_Source_SmashBros_Player.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_Source_SmashBros_SoundManager.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_Source_SmashBros_MusicManager.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_Source_SmashBros_HUD.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_Source_SmashBros_Preferences.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_Source_SmashBros_Game_GameScreen.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_Source_GameEngine_ApplicationEventListener.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_Source_ScriptModule_modules_SmashBros_lib_sb_Global.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_Source_SmashBros_ItemManager.cpp$(ObjectSuffix) \
	$(IntermediateDirectory)/up_up_Source_SmashBros_Loader.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_Source_GameEngine_GameEngine.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_Source_GameEngine_BatchLoader.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_Source_GameEngine_Util_P2PManager.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_Source_SmashBros_Magnifier.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_Source_GameEngine_Util_PrefManager.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_Source_GameEngine_Application.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_Source_SmashBros_Menus_Menus.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_Source_GameEngine_Actor_Actor.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_Source_SmashBros_Global.cpp$(ObjectSuffix) \
	$(IntermediateDirectory)/up_up_Source_GameEngine_Util_Image.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_Source_GameEngine_Input_Mouse.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_Source_SmashBros_Game_Characters_Fox.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_Source_ScriptModule_modules_GameEngine_lib_GameEngine.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_Source_SmashBros_Game_WinnerScreen.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_Source_SmashBros_Game_Items_RayGun.cpp$(ObjectSuffix) 

Objects2=$(IntermediateDirectory)/up_up_Source_SmashBros_Menus_StageSelectScreen.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_Source_Program.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_Source_SmashBros_ProjectileManager.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_Source_ScriptModule_modules_GameEngine_inherit_lib_ge_inherit_MenuScreen.cpp$(ObjectSuffix) \
	$(IntermediateDirectory)/up_up_Source_SmashBros_Game_Stages_HyruleTemple.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_Source_SmashBros_Menus_CharSelectScreen.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_Source_GameEngine_View.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_Source_GameEngine_Util_Thread.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_Source_GameEngine_Util_PixelIterator.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_Source_GameEngine_Util_HapticFeedbackiOS.mm$(ObjectSuffix) $(IntermediateDirectory)/up_up_Source_GameEngine_Sound_Music.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_Source_GameEngine_Util_String.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_Source_GameEngine_Util_Bitset.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_Source_GameEngine_Util_Color.cpp$(ObjectSuffix) \
	$(IntermediateDirectory)/up_up_Source_GameEngine_Actor_TextActor.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_Source_SmashBros_Item.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_Source_GameEngine_ScreenManager_Screen.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_Source_GameEngine_Actor_PrimitiveActor.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_Source_GameEngine_Sound_Sound.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_Source_GameEngine_ScreenManager_ScreenManager.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_Source_SmashBros_Game_Items_HeartContainer.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_Source_GameEngine_Output_Console.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_Source_SmashBros_Menus_MenuClasses.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_Source_GameEngine_Util_BufferedImage.cpp$(ObjectSuffix) \
	$(IntermediateDirectory)/up_up_Source_SmashBros_AttackManager.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_Source_GameEngine_Input_Keys.cpp$(ObjectSuffix) 



Objects=$(Objects0) $(Objects1) $(Objects2) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d ".build-debug/SDL_p2p" $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	@echo $(Objects1) >> $(ObjectsFileList)
	@echo $(Objects2) >> $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

".build-debug/SDL_p2p":
	@$(MakeDirCommand) ".build-debug"
	@echo stam > ".build-debug/SDL_p2p"




PostBuild:
	@echo Executing Post Build commands ...
	rm -rf Debug/Images Debug/Sounds Debug/Music Debug/Fonts
	ln -s ../../../Images Debug/Images
	ln -s ../../../Sounds Debug/Sounds
	ln -s ../../../Music Debug/Music
	ln -s ../../../Fonts Debug/Fonts
	@echo Done

MakeIntermediateDirs:
	@test -d ./Debug || $(MakeDirCommand) ./Debug


$(IntermediateDirectory)/.d:
	@test -d ./Debug || $(MakeDirCommand) ./Debug

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/up_up_Source_SmashBros_Game_Stages_StagePieces_Platform.cpp$(ObjectSuffix): ../../Source/SmashBros/Game/Stages/StagePieces/Platform.cpp $(IntermediateDirectory)/up_up_Source_SmashBros_Game_Stages_StagePieces_Platform.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/luis/Code/iSSB/Source/SmashBros/Game/Stages/StagePieces/Platform.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_Source_SmashBros_Game_Stages_StagePieces_Platform.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_Source_SmashBros_Game_Stages_StagePieces_Platform.cpp$(DependSuffix): ../../Source/SmashBros/Game/Stages/StagePieces/Platform.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_Source_SmashBros_Game_Stages_StagePieces_Platform.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_Source_SmashBros_Game_Stages_StagePieces_Platform.cpp$(DependSuffix) -MM ../../Source/SmashBros/Game/Stages/StagePieces/Platform.cpp

$(IntermediateDirectory)/up_up_Source_SmashBros_Game_Stages_StagePieces_Platform.cpp$(PreprocessSuffix): ../../Source/SmashBros/Game/Stages/StagePieces/Platform.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_Source_SmashBros_Game_Stages_StagePieces_Platform.cpp$(PreprocessSuffix) ../../Source/SmashBros/Game/Stages/StagePieces/Platform.cpp

$(IntermediateDirectory)/up_up_Source_ScriptModule_modules_GameEngine_inherit_lib_ge_inherit_Actor.cpp$(ObjectSuffix): ../../Source/ScriptModule/modules/GameEngine/inherit/lib_ge_inherit_Actor.cpp $(IntermediateDirectory)/up_up_Source_ScriptModule_modules_GameEngine_inherit_lib_ge_inherit_Actor.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/luis/Code/iSSB/Source/ScriptModule/modules/GameEngine/inherit/lib_ge_inherit_Actor.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_Source_ScriptModule_modules_GameEngine_inherit_lib_ge_inherit_Actor.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_Source_ScriptModule_modules_GameEngine_inherit_lib_ge_inherit_Actor.cpp$(DependSuffix): ../../Source/ScriptModule/modules/GameEngine/inherit/lib_ge_inherit_Actor.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_Source_ScriptModule_modules_GameEngine_inherit_lib_ge_inherit_Actor.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_Source_ScriptModule_modules_GameEngine_inherit_lib_ge_inherit_Actor.cpp$(DependSuffix) -MM ../../Source/ScriptModule/modules/GameEngine/inherit/lib_ge_inherit_Actor.cpp

$(IntermediateDirectory)/up_up_Source_ScriptModule_modules_GameEngine_inherit_lib_ge_inherit_Actor.cpp$(PreprocessSuffix): ../../Source/ScriptModule/modules/GameEngine/inherit/lib_ge_inherit_Actor.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_Source_ScriptModule_modules_GameEngine_inherit_lib_ge_inherit_Actor.cpp$(PreprocessSuffix) ../../Source/ScriptModule/modules/GameEngine/inherit/lib_ge_inherit_Actor.cpp

$(IntermediateDirectory)/up_up_Source_ScriptModule_modules_GameEngine_inherit_lib_ge_inherit_TextActor.cpp$(ObjectSuffix): ../../Source/ScriptModule/modules/GameEngine/inherit/lib_ge_inherit_TextActor.cpp $(IntermediateDirectory)/up_up_Source_ScriptModule_modules_GameEngine_inherit_lib_ge_inherit_TextActor.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/luis/Code/iSSB/Source/ScriptModule/modules/GameEngine/inherit/lib_ge_inherit_TextActor.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_Source_ScriptModule_modules_GameEngine_inherit_lib_ge_inherit_TextActor.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_Source_ScriptModule_modules_GameEngine_inherit_lib_ge_inherit_TextActor.cpp$(DependSuffix): ../../Source/ScriptModule/modules/GameEngine/inherit/lib_ge_inherit_TextActor.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_Source_ScriptModule_modules_GameEngine_inherit_lib_ge_inherit_TextActor.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_Source_ScriptModule_modules_GameEngine_inherit_lib_ge_inherit_TextActor.cpp$(DependSuffix) -MM ../../Source/ScriptModule/modules/GameEngine/inherit/lib_ge_inherit_TextActor.cpp

$(IntermediateDirectory)/up_up_Source_ScriptModule_modules_GameEngine_inherit_lib_ge_inherit_TextActor.cpp$(PreprocessSuffix): ../../Source/ScriptModule/modules/GameEngine/inherit/lib_ge_inherit_TextActor.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_Source_ScriptModule_modules_GameEngine_inherit_lib_ge_inherit_TextActor.cpp$(PreprocessSuffix) ../../Source/ScriptModule/modules/GameEngine/inherit/lib_ge_inherit_TextActor.cpp

$(IntermediateDirectory)/up_up_Source_ScriptModule_modules_GameEngine_inherit_lib_ge_inherit_WireframeActor.cpp$(ObjectSuffix): ../../Source/ScriptModule/modules/GameEngine/inherit/lib_ge_inherit_WireframeActor.cpp $(IntermediateDirectory)/up_up_Source_ScriptModule_modules_GameEngine_inherit_lib_ge_inherit_WireframeActor.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/luis/Code/iSSB/Source/ScriptModule/modules/GameEngine/inherit/lib_ge_inherit_WireframeActor.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_Source_ScriptModule_modules_GameEngine_inherit_lib_ge_inherit_WireframeActor.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_Source_ScriptModule_modules_GameEngine_inherit_lib_ge_inherit_WireframeActor.cpp$(DependSuffix): ../../Source/ScriptModule/modules/GameEngine/inherit/lib_ge_inherit_WireframeActor.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_Source_ScriptModule_modules_GameEngine_inherit_lib_ge_inherit_WireframeActor.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_Source_ScriptModule_modules_GameEngine_inherit_lib_ge_inherit_WireframeActor.cpp$(DependSuffix) -MM ../../Source/ScriptModule/modules/GameEngine/inherit/lib_ge_inherit_WireframeActor.cpp

$(IntermediateDirectory)/up_up_Source_ScriptModule_modules_GameEngine_inherit_lib_ge_inherit_WireframeActor.cpp$(PreprocessSuffix): ../../Source/ScriptModule/modules/GameEngine/inherit/lib_ge_inherit_WireframeActor.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_Source_ScriptModule_modules_GameEngine_inherit_lib_ge_inherit_WireframeActor.cpp$(PreprocessSuffix) ../../Source/ScriptModule/modules/GameEngine/inherit/lib_ge_inherit_WireframeActor.cpp

$(IntermediateDirectory)/up_up_Source_ScriptModule_modules_SmashBros_inherit_lib_sb_inherit_Player.cpp$(ObjectSuffix): ../../Source/ScriptModule/modules/SmashBros/inherit/lib_sb_inherit_Player.cpp $(IntermediateDirectory)/up_up_Source_ScriptModule_modules_SmashBros_inherit_lib_sb_inherit_Player.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/luis/Code/iSSB/Source/ScriptModule/modules/SmashBros/inherit/lib_sb_inherit_Player.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_Source_ScriptModule_modules_SmashBros_inherit_lib_sb_inherit_Player.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_Source_ScriptModule_modules_SmashBros_inherit_lib_sb_inherit_Player.cpp$(DependSuffix): ../../Source/ScriptModule/modules/SmashBros/inherit/lib_sb_inherit_Player.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_Source_ScriptModule_modules_SmashBros_inherit_lib_sb_inherit_Player.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_Source_ScriptModule_modules_SmashBros_inherit_lib_sb_inherit_Player.cpp$(DependSuffix) -MM ../../Source/ScriptModule/modules/SmashBros/inherit/lib_sb_inherit_Player.cpp

$(IntermediateDirectory)/up_up_Source_ScriptModule_modules_SmashBros_inherit_lib_sb_inherit_Player.cpp$(PreprocessSuffix): ../../Source/ScriptModule/modules/SmashBros/inherit/lib_sb_inherit_Player.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_Source_ScriptModule_modules_SmashBros_inherit_lib_sb_inherit_Player.cpp$(PreprocessSuffix) ../../Source/ScriptModule/modules/SmashBros/inherit/lib_sb_inherit_Player.cpp

$(IntermediateDirectory)/up_up_Source_ScriptModule_modules_SmashBros_inherit_lib_sb_inherit_Stage.cpp$(ObjectSuffix): ../../Source/ScriptModule/modules/SmashBros/inherit/lib_sb_inherit_Stage.cpp $(IntermediateDirectory)/up_up_Source_ScriptModule_modules_SmashBros_inherit_lib_sb_inherit_Stage.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/luis/Code/iSSB/Source/ScriptModule/modules/SmashBros/inherit/lib_sb_inherit_Stage.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_Source_ScriptModule_modules_SmashBros_inherit_lib_sb_inherit_Stage.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_Source_ScriptModule_modules_SmashBros_inherit_lib_sb_inherit_Stage.cpp$(DependSuffix): ../../Source/ScriptModule/modules/SmashBros/inherit/lib_sb_inherit_Stage.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_Source_ScriptModule_modules_SmashBros_inherit_lib_sb_inherit_Stage.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_Source_ScriptModule_modules_SmashBros_inherit_lib_sb_inherit_Stage.cpp$(DependSuffix) -MM ../../Source/ScriptModule/modules/SmashBros/inherit/lib_sb_inherit_Stage.cpp

$(IntermediateDirectory)/up_up_Source_ScriptModule_modules_SmashBros_inherit_lib_sb_inherit_Stage.cpp$(PreprocessSuffix): ../../Source/ScriptModule/modules/SmashBros/inherit/lib_sb_inherit_Stage.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_Source_ScriptModule_modules_SmashBros_inherit_lib_sb_inherit_Stage.cpp$(PreprocessSuffix) ../../Source/ScriptModule/modules/SmashBros/inherit/lib_sb_inherit_Stage.cpp

$(IntermediateDirectory)/up_up_Source_SmashBros_Menus_MenuPieces_ActorGrid.cpp$(ObjectSuffix): ../../Source/SmashBros/Menus/MenuPieces/ActorGrid.cpp $(IntermediateDirectory)/up_up_Source_SmashBros_Menus_MenuPieces_ActorGrid.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/luis/Code/iSSB/Source/SmashBros/Menus/MenuPieces/ActorGrid.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_Source_SmashBros_Menus_MenuPieces_ActorGrid.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_Source_SmashBros_Menus_MenuPieces_ActorGrid.cpp$(DependSuffix): ../../Source/SmashBros/Menus/MenuPieces/ActorGrid.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_Source_SmashBros_Menus_MenuPieces_ActorGrid.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_Source_SmashBros_Menus_MenuPieces_ActorGrid.cpp$(DependSuffix) -MM ../../Source/SmashBros/Menus/MenuPieces/ActorGrid.cpp

$(IntermediateDirectory)/up_up_Source_SmashBros_Menus_MenuPieces_ActorGrid.cpp$(PreprocessSuffix): ../../Source/SmashBros/Menus/MenuPieces/ActorGrid.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_Source_SmashBros_Menus_MenuPieces_ActorGrid.cpp$(PreprocessSuffix) ../../Source/SmashBros/Menus/MenuPieces/ActorGrid.cpp

$(IntermediateDirectory)/up_up_Source_SmashBros_Menus_MenuPieces_Arrows.cpp$(ObjectSuffix): ../../Source/SmashBros/Menus/MenuPieces/Arrows.cpp $(IntermediateDirectory)/up_up_Source_SmashBros_Menus_MenuPieces_Arrows.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/luis/Code/iSSB/Source/SmashBros/Menus/MenuPieces/Arrows.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_Source_SmashBros_Menus_MenuPieces_Arrows.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_Source_SmashBros_Menus_MenuPieces_Arrows.cpp$(DependSuffix): ../../Source/SmashBros/Menus/MenuPieces/Arrows.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_Source_SmashBros_Menus_MenuPieces_Arrows.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_Source_SmashBros_Menus_MenuPieces_Arrows.cpp$(DependSuffix) -MM ../../Source/SmashBros/Menus/MenuPieces/Arrows.cpp

$(IntermediateDirectory)/up_up_Source_SmashBros_Menus_MenuPieces_Arrows.cpp$(PreprocessSuffix): ../../Source/SmashBros/Menus/MenuPieces/Arrows.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_Source_SmashBros_Menus_MenuPieces_Arrows.cpp$(PreprocessSuffix) ../../Source/SmashBros/Menus/MenuPieces/Arrows.cpp

$(IntermediateDirectory)/up_up_Source_SmashBros_Menus_MenuPieces_MenuBar.cpp$(ObjectSuffix): ../../Source/SmashBros/Menus/MenuPieces/MenuBar.cpp $(IntermediateDirectory)/up_up_Source_SmashBros_Menus_MenuPieces_MenuBar.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/luis/Code/iSSB/Source/SmashBros/Menus/MenuPieces/MenuBar.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_Source_SmashBros_Menus_MenuPieces_MenuBar.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_Source_SmashBros_Menus_MenuPieces_MenuBar.cpp$(DependSuffix): ../../Source/SmashBros/Menus/MenuPieces/MenuBar.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_Source_SmashBros_Menus_MenuPieces_MenuBar.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_Source_SmashBros_Menus_MenuPieces_MenuBar.cpp$(DependSuffix) -MM ../../Source/SmashBros/Menus/MenuPieces/MenuBar.cpp

$(IntermediateDirectory)/up_up_Source_SmashBros_Menus_MenuPieces_MenuBar.cpp$(PreprocessSuffix): ../../Source/SmashBros/Menus/MenuPieces/MenuBar.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_Source_SmashBros_Menus_MenuPieces_MenuBar.cpp$(PreprocessSuffix) ../../Source/SmashBros/Menus/MenuPieces/MenuBar.cpp

$(IntermediateDirectory)/up_up_Source_SmashBros_Game_Stages_StagePieces_HangPoint.cpp$(ObjectSuffix): ../../Source/SmashBros/Game/Stages/StagePieces/HangPoint.cpp $(IntermediateDirectory)/up_up_Source_SmashBros_Game_Stages_StagePieces_HangPoint.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/luis/Code/iSSB/Source/SmashBros/Game/Stages/StagePieces/HangPoint.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_Source_SmashBros_Game_Stages_StagePieces_HangPoint.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_Source_SmashBros_Game_Stages_StagePieces_HangPoint.cpp$(DependSuffix): ../../Source/SmashBros/Game/Stages/StagePieces/HangPoint.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_Source_SmashBros_Game_Stages_StagePieces_HangPoint.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_Source_SmashBros_Game_Stages_StagePieces_HangPoint.cpp$(DependSuffix) -MM ../../Source/SmashBros/Game/Stages/StagePieces/HangPoint.cpp

$(IntermediateDirectory)/up_up_Source_SmashBros_Game_Stages_StagePieces_HangPoint.cpp$(PreprocessSuffix): ../../Source/SmashBros/Game/Stages/StagePieces/HangPoint.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_Source_SmashBros_Game_Stages_StagePieces_HangPoint.cpp$(PreprocessSuffix) ../../Source/SmashBros/Game/Stages/StagePieces/HangPoint.cpp

$(IntermediateDirectory)/up_up_Source_SmashBros_Menus_MenuPieces_MenuBarSmall.cpp$(ObjectSuffix): ../../Source/SmashBros/Menus/MenuPieces/MenuBarSmall.cpp $(IntermediateDirectory)/up_up_Source_SmashBros_Menus_MenuPieces_MenuBarSmall.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/luis/Code/iSSB/Source/SmashBros/Menus/MenuPieces/MenuBarSmall.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_Source_SmashBros_Menus_MenuPieces_MenuBarSmall.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_Source_SmashBros_Menus_MenuPieces_MenuBarSmall.cpp$(DependSuffix): ../../Source/SmashBros/Menus/MenuPieces/MenuBarSmall.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_Source_SmashBros_Menus_MenuPieces_MenuBarSmall.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_Source_SmashBros_Menus_MenuPieces_MenuBarSmall.cpp$(DependSuffix) -MM ../../Source/SmashBros/Menus/MenuPieces/MenuBarSmall.cpp

$(IntermediateDirectory)/up_up_Source_SmashBros_Menus_MenuPieces_MenuBarSmall.cpp$(PreprocessSuffix): ../../Source/SmashBros/Menus/MenuPieces/MenuBarSmall.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_Source_SmashBros_Menus_MenuPieces_MenuBarSmall.cpp$(PreprocessSuffix) ../../Source/SmashBros/Menus/MenuPieces/MenuBarSmall.cpp

$(IntermediateDirectory)/up_up_Source_SmashBros_Menus_MenuPieces_MenuBarValue.cpp$(ObjectSuffix): ../../Source/SmashBros/Menus/MenuPieces/MenuBarValue.cpp $(IntermediateDirectory)/up_up_Source_SmashBros_Menus_MenuPieces_MenuBarValue.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/luis/Code/iSSB/Source/SmashBros/Menus/MenuPieces/MenuBarValue.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_Source_SmashBros_Menus_MenuPieces_MenuBarValue.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_Source_SmashBros_Menus_MenuPieces_MenuBarValue.cpp$(DependSuffix): ../../Source/SmashBros/Menus/MenuPieces/MenuBarValue.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_Source_SmashBros_Menus_MenuPieces_MenuBarValue.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_Source_SmashBros_Menus_MenuPieces_MenuBarValue.cpp$(DependSuffix) -MM ../../Source/SmashBros/Menus/MenuPieces/MenuBarValue.cpp

$(IntermediateDirectory)/up_up_Source_SmashBros_Menus_MenuPieces_MenuBarValue.cpp$(PreprocessSuffix): ../../Source/SmashBros/Menus/MenuPieces/MenuBarValue.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_Source_SmashBros_Menus_MenuPieces_MenuBarValue.cpp$(PreprocessSuffix) ../../Source/SmashBros/Menus/MenuPieces/MenuBarValue.cpp

$(IntermediateDirectory)/up_up_Source_SmashBros_Menus_MenuPieces_ToggleButton.cpp$(ObjectSuffix): ../../Source/SmashBros/Menus/MenuPieces/ToggleButton.cpp $(IntermediateDirectory)/up_up_Source_SmashBros_Menus_MenuPieces_ToggleButton.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/luis/Code/iSSB/Source/SmashBros/Menus/MenuPieces/ToggleButton.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_Source_SmashBros_Menus_MenuPieces_ToggleButton.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_Source_SmashBros_Menus_MenuPieces_ToggleButton.cpp$(DependSuffix): ../../Source/SmashBros/Menus/MenuPieces/ToggleButton.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_Source_SmashBros_Menus_MenuPieces_ToggleButton.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_Source_SmashBros_Menus_MenuPieces_ToggleButton.cpp$(DependSuffix) -MM ../../Source/SmashBros/Menus/MenuPieces/ToggleButton.cpp

$(IntermediateDirectory)/up_up_Source_SmashBros_Menus_MenuPieces_ToggleButton.cpp$(PreprocessSuffix): ../../Source/SmashBros/Menus/MenuPieces/ToggleButton.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_Source_SmashBros_Menus_MenuPieces_ToggleButton.cpp$(PreprocessSuffix) ../../Source/SmashBros/Menus/MenuPieces/ToggleButton.cpp

$(IntermediateDirectory)/up_up_Source_SmashBros_Menus_MenuPieces_TogglePane.cpp$(ObjectSuffix): ../../Source/SmashBros/Menus/MenuPieces/TogglePane.cpp $(IntermediateDirectory)/up_up_Source_SmashBros_Menus_MenuPieces_TogglePane.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/luis/Code/iSSB/Source/SmashBros/Menus/MenuPieces/TogglePane.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_Source_SmashBros_Menus_MenuPieces_TogglePane.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_Source_SmashBros_Menus_MenuPieces_TogglePane.cpp$(DependSuffix): ../../Source/SmashBros/Menus/MenuPieces/TogglePane.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_Source_SmashBros_Menus_MenuPieces_TogglePane.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_Source_SmashBros_Menus_MenuPieces_TogglePane.cpp$(DependSuffix) -MM ../../Source/SmashBros/Menus/MenuPieces/TogglePane.cpp

$(IntermediateDirectory)/up_up_Source_SmashBros_Menus_MenuPieces_TogglePane.cpp$(PreprocessSuffix): ../../Source/SmashBros/Menus/MenuPieces/TogglePane.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_Source_SmashBros_Menus_MenuPieces_TogglePane.cpp$(PreprocessSuffix) ../../Source/SmashBros/Menus/MenuPieces/TogglePane.cpp

$(IntermediateDirectory)/up_up_Source_SmashBros_Menus_MenuPieces_MenuBarToggle.cpp$(ObjectSuffix): ../../Source/SmashBros/Menus/MenuPieces/MenuBarToggle.cpp $(IntermediateDirectory)/up_up_Source_SmashBros_Menus_MenuPieces_MenuBarToggle.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/luis/Code/iSSB/Source/SmashBros/Menus/MenuPieces/MenuBarToggle.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_Source_SmashBros_Menus_MenuPieces_MenuBarToggle.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_Source_SmashBros_Menus_MenuPieces_MenuBarToggle.cpp$(DependSuffix): ../../Source/SmashBros/Menus/MenuPieces/MenuBarToggle.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_Source_SmashBros_Menus_MenuPieces_MenuBarToggle.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_Source_SmashBros_Menus_MenuPieces_MenuBarToggle.cpp$(DependSuffix) -MM ../../Source/SmashBros/Menus/MenuPieces/MenuBarToggle.cpp

$(IntermediateDirectory)/up_up_Source_SmashBros_Menus_MenuPieces_MenuBarToggle.cpp$(PreprocessSuffix): ../../Source/SmashBros/Menus/MenuPieces/MenuBarToggle.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_Source_SmashBros_Menus_MenuPieces_MenuBarToggle.cpp$(PreprocessSuffix) ../../Source/SmashBros/Menus/MenuPieces/MenuBarToggle.cpp

$(IntermediateDirectory)/up_up_Source_SmashBros_Game_Characters_Pikachu.cpp$(ObjectSuffix): ../../Source/SmashBros/Game/Characters/Pikachu.cpp $(IntermediateDirectory)/up_up_Source_SmashBros_Game_Characters_Pikachu.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/luis/Code/iSSB/Source/SmashBros/Game/Characters/Pikachu.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_Source_SmashBros_Game_Characters_Pikachu.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_Source_SmashBros_Game_Characters_Pikachu.cpp$(DependSuffix): ../../Source/SmashBros/Game/Characters/Pikachu.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_Source_SmashBros_Game_Characters_Pikachu.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_Source_SmashBros_Game_Characters_Pikachu.cpp$(DependSuffix) -MM ../../Source/SmashBros/Game/Characters/Pikachu.cpp

$(IntermediateDirectory)/up_up_Source_SmashBros_Game_Characters_Pikachu.cpp$(PreprocessSuffix): ../../Source/SmashBros/Game/Characters/Pikachu.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_Source_SmashBros_Game_Characters_Pikachu.cpp$(PreprocessSuffix) ../../Source/SmashBros/Game/Characters/Pikachu.cpp

$(IntermediateDirectory)/up_up_Source_SmashBros_Game_Characters_Sonic.cpp$(ObjectSuffix): ../../Source/SmashBros/Game/Characters/Sonic.cpp $(IntermediateDirectory)/up_up_Source_SmashBros_Game_Characters_Sonic.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/luis/Code/iSSB/Source/SmashBros/Game/Characters/Sonic.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_Source_SmashBros_Game_Characters_Sonic.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_Source_SmashBros_Game_Characters_Sonic.cpp$(DependSuffix): ../../Source/SmashBros/Game/Characters/Sonic.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_Source_SmashBros_Game_Characters_Sonic.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_Source_SmashBros_Game_Characters_Sonic.cpp$(DependSuffix) -MM ../../Source/SmashBros/Game/Characters/Sonic.cpp

$(IntermediateDirectory)/up_up_Source_SmashBros_Game_Characters_Sonic.cpp$(PreprocessSuffix): ../../Source/SmashBros/Game/Characters/Sonic.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_Source_SmashBros_Game_Characters_Sonic.cpp$(PreprocessSuffix) ../../Source/SmashBros/Game/Characters/Sonic.cpp

$(IntermediateDirectory)/up_up_Source_SmashBros_Game_Items_BeamSword.cpp$(ObjectSuffix): ../../Source/SmashBros/Game/Items/BeamSword.cpp $(IntermediateDirectory)/up_up_Source_SmashBros_Game_Items_BeamSword.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/luis/Code/iSSB/Source/SmashBros/Game/Items/BeamSword.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_Source_SmashBros_Game_Items_BeamSword.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_Source_SmashBros_Game_Items_BeamSword.cpp$(DependSuffix): ../../Source/SmashBros/Game/Items/BeamSword.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_Source_SmashBros_Game_Items_BeamSword.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_Source_SmashBros_Game_Items_BeamSword.cpp$(DependSuffix) -MM ../../Source/SmashBros/Game/Items/BeamSword.cpp

$(IntermediateDirectory)/up_up_Source_SmashBros_Game_Items_BeamSword.cpp$(PreprocessSuffix): ../../Source/SmashBros/Game/Items/BeamSword.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_Source_SmashBros_Game_Items_BeamSword.cpp$(PreprocessSuffix) ../../Source/SmashBros/Game/Items/BeamSword.cpp

$(IntermediateDirectory)/up_up_Source_SmashBros_Game_Items_SuperMushroom.cpp$(ObjectSuffix): ../../Source/SmashBros/Game/Items/SuperMushroom.cpp $(IntermediateDirectory)/up_up_Source_SmashBros_Game_Items_SuperMushroom.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/luis/Code/iSSB/Source/SmashBros/Game/Items/SuperMushroom.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_Source_SmashBros_Game_Items_SuperMushroom.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_Source_SmashBros_Game_Items_SuperMushroom.cpp$(DependSuffix): ../../Source/SmashBros/Game/Items/SuperMushroom.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_Source_SmashBros_Game_Items_SuperMushroom.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_Source_SmashBros_Game_Items_SuperMushroom.cpp$(DependSuffix) -MM ../../Source/SmashBros/Game/Items/SuperMushroom.cpp

$(IntermediateDirectory)/up_up_Source_SmashBros_Game_Items_SuperMushroom.cpp$(PreprocessSuffix): ../../Source/SmashBros/Game/Items/SuperMushroom.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_Source_SmashBros_Game_Items_SuperMushroom.cpp$(PreprocessSuffix) ../../Source/SmashBros/Game/Items/SuperMushroom.cpp

$(IntermediateDirectory)/up_up_Source_SmashBros_Game_Characters_Link.cpp$(ObjectSuffix): ../../Source/SmashBros/Game/Characters/Link.cpp $(IntermediateDirectory)/up_up_Source_SmashBros_Game_Characters_Link.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/luis/Code/iSSB/Source/SmashBros/Game/Characters/Link.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_Source_SmashBros_Game_Characters_Link.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_Source_SmashBros_Game_Characters_Link.cpp$(DependSuffix): ../../Source/SmashBros/Game/Characters/Link.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_Source_SmashBros_Game_Characters_Link.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_Source_SmashBros_Game_Characters_Link.cpp$(DependSuffix) -MM ../../Source/SmashBros/Game/Characters/Link.cpp

$(IntermediateDirectory)/up_up_Source_SmashBros_Game_Characters_Link.cpp$(PreprocessSuffix): ../../Source/SmashBros/Game/Characters/Link.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_Source_SmashBros_Game_Characters_Link.cpp$(PreprocessSuffix) ../../Source/SmashBros/Game/Characters/Link.cpp

$(IntermediateDirectory)/up_up_Source_SmashBros_Game_Stages_FinalDestinationBrawl.cpp$(ObjectSuffix): ../../Source/SmashBros/Game/Stages/FinalDestinationBrawl.cpp $(IntermediateDirectory)/up_up_Source_SmashBros_Game_Stages_FinalDestinationBrawl.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/luis/Code/iSSB/Source/SmashBros/Game/Stages/FinalDestinationBrawl.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_Source_SmashBros_Game_Stages_FinalDestinationBrawl.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_Source_SmashBros_Game_Stages_FinalDestinationBrawl.cpp$(DependSuffix): ../../Source/SmashBros/Game/Stages/FinalDestinationBrawl.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_Source_SmashBros_Game_Stages_FinalDestinationBrawl.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_Source_SmashBros_Game_Stages_FinalDestinationBrawl.cpp$(DependSuffix) -MM ../../Source/SmashBros/Game/Stages/FinalDestinationBrawl.cpp

$(IntermediateDirectory)/up_up_Source_SmashBros_Game_Stages_FinalDestinationBrawl.cpp$(PreprocessSuffix): ../../Source/SmashBros/Game/Stages/FinalDestinationBrawl.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_Source_SmashBros_Game_Stages_FinalDestinationBrawl.cpp$(PreprocessSuffix) ../../Source/SmashBros/Game/Stages/FinalDestinationBrawl.cpp

$(IntermediateDirectory)/up_up_Source_SmashBros_Game_Stages_FractalStage.cpp$(ObjectSuffix): ../../Source/SmashBros/Game/Stages/FractalStage.cpp $(IntermediateDirectory)/up_up_Source_SmashBros_Game_Stages_FractalStage.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/luis/Code/iSSB/Source/SmashBros/Game/Stages/FractalStage.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_Source_SmashBros_Game_Stages_FractalStage.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_Source_SmashBros_Game_Stages_FractalStage.cpp$(DependSuffix): ../../Source/SmashBros/Game/Stages/FractalStage.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_Source_SmashBros_Game_Stages_FractalStage.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_Source_SmashBros_Game_Stages_FractalStage.cpp$(DependSuffix) -MM ../../Source/SmashBros/Game/Stages/FractalStage.cpp

$(IntermediateDirectory)/up_up_Source_SmashBros_Game_Stages_FractalStage.cpp$(PreprocessSuffix): ../../Source/SmashBros/Game/Stages/FractalStage.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_Source_SmashBros_Game_Stages_FractalStage.cpp$(PreprocessSuffix) ../../Source/SmashBros/Game/Stages/FractalStage.cpp

$(IntermediateDirectory)/up_up_Source_SmashBros_Game_Characters_Ichigo.cpp$(ObjectSuffix): ../../Source/SmashBros/Game/Characters/Ichigo.cpp $(IntermediateDirectory)/up_up_Source_SmashBros_Game_Characters_Ichigo.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/luis/Code/iSSB/Source/SmashBros/Game/Characters/Ichigo.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_Source_SmashBros_Game_Characters_Ichigo.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_Source_SmashBros_Game_Characters_Ichigo.cpp$(DependSuffix): ../../Source/SmashBros/Game/Characters/Ichigo.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_Source_SmashBros_Game_Characters_Ichigo.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_Source_SmashBros_Game_Characters_Ichigo.cpp$(DependSuffix) -MM ../../Source/SmashBros/Game/Characters/Ichigo.cpp

$(IntermediateDirectory)/up_up_Source_SmashBros_Game_Characters_Ichigo.cpp$(PreprocessSuffix): ../../Source/SmashBros/Game/Characters/Ichigo.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_Source_SmashBros_Game_Characters_Ichigo.cpp$(PreprocessSuffix) ../../Source/SmashBros/Game/Characters/Ichigo.cpp

$(IntermediateDirectory)/up_up_Source_SmashBros_Game_Stages_HillsideBattleground.cpp$(ObjectSuffix): ../../Source/SmashBros/Game/Stages/HillsideBattleground.cpp $(IntermediateDirectory)/up_up_Source_SmashBros_Game_Stages_HillsideBattleground.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/luis/Code/iSSB/Source/SmashBros/Game/Stages/HillsideBattleground.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_Source_SmashBros_Game_Stages_HillsideBattleground.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_Source_SmashBros_Game_Stages_HillsideBattleground.cpp$(DependSuffix): ../../Source/SmashBros/Game/Stages/HillsideBattleground.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_Source_SmashBros_Game_Stages_HillsideBattleground.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_Source_SmashBros_Game_Stages_HillsideBattleground.cpp$(DependSuffix) -MM ../../Source/SmashBros/Game/Stages/HillsideBattleground.cpp

$(IntermediateDirectory)/up_up_Source_SmashBros_Game_Stages_HillsideBattleground.cpp$(PreprocessSuffix): ../../Source/SmashBros/Game/Stages/HillsideBattleground.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_Source_SmashBros_Game_Stages_HillsideBattleground.cpp$(PreprocessSuffix) ../../Source/SmashBros/Game/Stages/HillsideBattleground.cpp

$(IntermediateDirectory)/up_up_Source_ScriptModule_modules_GameEngine_lib_ge_Actor.cpp$(ObjectSuffix): ../../Source/ScriptModule/modules/GameEngine/lib_ge_Actor.cpp $(IntermediateDirectory)/up_up_Source_ScriptModule_modules_GameEngine_lib_ge_Actor.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/luis/Code/iSSB/Source/ScriptModule/modules/GameEngine/lib_ge_Actor.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_Source_ScriptModule_modules_GameEngine_lib_ge_Actor.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_Source_ScriptModule_modules_GameEngine_lib_ge_Actor.cpp$(DependSuffix): ../../Source/ScriptModule/modules/GameEngine/lib_ge_Actor.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_Source_ScriptModule_modules_GameEngine_lib_ge_Actor.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_Source_ScriptModule_modules_GameEngine_lib_ge_Actor.cpp$(DependSuffix) -MM ../../Source/ScriptModule/modules/GameEngine/lib_ge_Actor.cpp

$(IntermediateDirectory)/up_up_Source_ScriptModule_modules_GameEngine_lib_ge_Actor.cpp$(PreprocessSuffix): ../../Source/ScriptModule/modules/GameEngine/lib_ge_Actor.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_Source_ScriptModule_modules_GameEngine_lib_ge_Actor.cpp$(PreprocessSuffix) ../../Source/ScriptModule/modules/GameEngine/lib_ge_Actor.cpp

$(IntermediateDirectory)/up_up_Source_SmashBros_Game_Items_PoisonMushroom.cpp$(ObjectSuffix): ../../Source/SmashBros/Game/Items/PoisonMushroom.cpp $(IntermediateDirectory)/up_up_Source_SmashBros_Game_Items_PoisonMushroom.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/luis/Code/iSSB/Source/SmashBros/Game/Items/PoisonMushroom.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_Source_SmashBros_Game_Items_PoisonMushroom.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_Source_SmashBros_Game_Items_PoisonMushroom.cpp$(DependSuffix): ../../Source/SmashBros/Game/Items/PoisonMushroom.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_Source_SmashBros_Game_Items_PoisonMushroom.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_Source_SmashBros_Game_Items_PoisonMushroom.cpp$(DependSuffix) -MM ../../Source/SmashBros/Game/Items/PoisonMushroom.cpp

$(IntermediateDirectory)/up_up_Source_SmashBros_Game_Items_PoisonMushroom.cpp$(PreprocessSuffix): ../../Source/SmashBros/Game/Items/PoisonMushroom.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_Source_SmashBros_Game_Items_PoisonMushroom.cpp$(PreprocessSuffix) ../../Source/SmashBros/Game/Items/PoisonMushroom.cpp

$(IntermediateDirectory)/up_up_Source_ScriptModule_modules_GameEngine_lib_ge_IO.cpp$(ObjectSuffix): ../../Source/ScriptModule/modules/GameEngine/lib_ge_IO.cpp $(IntermediateDirectory)/up_up_Source_ScriptModule_modules_GameEngine_lib_ge_IO.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/luis/Code/iSSB/Source/ScriptModule/modules/GameEngine/lib_ge_IO.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_Source_ScriptModule_modules_GameEngine_lib_ge_IO.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_Source_ScriptModule_modules_GameEngine_lib_ge_IO.cpp$(DependSuffix): ../../Source/ScriptModule/modules/GameEngine/lib_ge_IO.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_Source_ScriptModule_modules_GameEngine_lib_ge_IO.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_Source_ScriptModule_modules_GameEngine_lib_ge_IO.cpp$(DependSuffix) -MM ../../Source/ScriptModule/modules/GameEngine/lib_ge_IO.cpp

$(IntermediateDirectory)/up_up_Source_ScriptModule_modules_GameEngine_lib_ge_IO.cpp$(PreprocessSuffix): ../../Source/ScriptModule/modules/GameEngine/lib_ge_IO.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_Source_ScriptModule_modules_GameEngine_lib_ge_IO.cpp$(PreprocessSuffix) ../../Source/ScriptModule/modules/GameEngine/lib_ge_IO.cpp

$(IntermediateDirectory)/up_up_Source_ScriptModule_modules_GameEngine_lib_ge_ScreenManager.cpp$(ObjectSuffix): ../../Source/ScriptModule/modules/GameEngine/lib_ge_ScreenManager.cpp $(IntermediateDirectory)/up_up_Source_ScriptModule_modules_GameEngine_lib_ge_ScreenManager.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/luis/Code/iSSB/Source/ScriptModule/modules/GameEngine/lib_ge_ScreenManager.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_Source_ScriptModule_modules_GameEngine_lib_ge_ScreenManager.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_Source_ScriptModule_modules_GameEngine_lib_ge_ScreenManager.cpp$(DependSuffix): ../../Source/ScriptModule/modules/GameEngine/lib_ge_ScreenManager.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_Source_ScriptModule_modules_GameEngine_lib_ge_ScreenManager.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_Source_ScriptModule_modules_GameEngine_lib_ge_ScreenManager.cpp$(DependSuffix) -MM ../../Source/ScriptModule/modules/GameEngine/lib_ge_ScreenManager.cpp

$(IntermediateDirectory)/up_up_Source_ScriptModule_modules_GameEngine_lib_ge_ScreenManager.cpp$(PreprocessSuffix): ../../Source/ScriptModule/modules/GameEngine/lib_ge_ScreenManager.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_Source_ScriptModule_modules_GameEngine_lib_ge_ScreenManager.cpp$(PreprocessSuffix) ../../Source/ScriptModule/modules/GameEngine/lib_ge_ScreenManager.cpp

$(IntermediateDirectory)/up_up_Source_SmashBros_Game_Characters_Mario.cpp$(ObjectSuffix): ../../Source/SmashBros/Game/Characters/Mario.cpp $(IntermediateDirectory)/up_up_Source_SmashBros_Game_Characters_Mario.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/luis/Code/iSSB/Source/SmashBros/Game/Characters/Mario.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_Source_SmashBros_Game_Characters_Mario.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_Source_SmashBros_Game_Characters_Mario.cpp$(DependSuffix): ../../Source/SmashBros/Game/Characters/Mario.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_Source_SmashBros_Game_Characters_Mario.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_Source_SmashBros_Game_Characters_Mario.cpp$(DependSuffix) -MM ../../Source/SmashBros/Game/Characters/Mario.cpp

$(IntermediateDirectory)/up_up_Source_SmashBros_Game_Characters_Mario.cpp$(PreprocessSuffix): ../../Source/SmashBros/Game/Characters/Mario.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_Source_SmashBros_Game_Characters_Mario.cpp$(PreprocessSuffix) ../../Source/SmashBros/Game/Characters/Mario.cpp

$(IntermediateDirectory)/up_up_Source_ScriptModule_modules_GameEngine_lib_ge_Util.cpp$(ObjectSuffix): ../../Source/ScriptModule/modules/GameEngine/lib_ge_Util.cpp $(IntermediateDirectory)/up_up_Source_ScriptModule_modules_GameEngine_lib_ge_Util.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/luis/Code/iSSB/Source/ScriptModule/modules/GameEngine/lib_ge_Util.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_Source_ScriptModule_modules_GameEngine_lib_ge_Util.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_Source_ScriptModule_modules_GameEngine_lib_ge_Util.cpp$(DependSuffix): ../../Source/ScriptModule/modules/GameEngine/lib_ge_Util.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_Source_ScriptModule_modules_GameEngine_lib_ge_Util.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_Source_ScriptModule_modules_GameEngine_lib_ge_Util.cpp$(DependSuffix) -MM ../../Source/ScriptModule/modules/GameEngine/lib_ge_Util.cpp

$(IntermediateDirectory)/up_up_Source_ScriptModule_modules_GameEngine_lib_ge_Util.cpp$(PreprocessSuffix): ../../Source/ScriptModule/modules/GameEngine/lib_ge_Util.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_Source_ScriptModule_modules_GameEngine_lib_ge_Util.cpp$(PreprocessSuffix) ../../Source/ScriptModule/modules/GameEngine/lib_ge_Util.cpp

$(IntermediateDirectory)/up_up_Source_ScriptModule_modules_SmashBros_lib_sb_GameElement.cpp$(ObjectSuffix): ../../Source/ScriptModule/modules/SmashBros/lib_sb_GameElement.cpp $(IntermediateDirectory)/up_up_Source_ScriptModule_modules_SmashBros_lib_sb_GameElement.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/luis/Code/iSSB/Source/ScriptModule/modules/SmashBros/lib_sb_GameElement.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_Source_ScriptModule_modules_SmashBros_lib_sb_GameElement.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_Source_ScriptModule_modules_SmashBros_lib_sb_GameElement.cpp$(DependSuffix): ../../Source/ScriptModule/modules/SmashBros/lib_sb_GameElement.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_Source_ScriptModule_modules_SmashBros_lib_sb_GameElement.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_Source_ScriptModule_modules_SmashBros_lib_sb_GameElement.cpp$(DependSuffix) -MM ../../Source/ScriptModule/modules/SmashBros/lib_sb_GameElement.cpp

$(IntermediateDirectory)/up_up_Source_ScriptModule_modules_SmashBros_lib_sb_GameElement.cpp$(PreprocessSuffix): ../../Source/ScriptModule/modules/SmashBros/lib_sb_GameElement.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_Source_ScriptModule_modules_SmashBros_lib_sb_GameElement.cpp$(PreprocessSuffix) ../../Source/ScriptModule/modules/SmashBros/lib_sb_GameElement.cpp

$(IntermediateDirectory)/up_up_Source_ScriptModule_modules_SmashBros_lib_sb_Stage.cpp$(ObjectSuffix): ../../Source/ScriptModule/modules/SmashBros/lib_sb_Stage.cpp $(IntermediateDirectory)/up_up_Source_ScriptModule_modules_SmashBros_lib_sb_Stage.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/luis/Code/iSSB/Source/ScriptModule/modules/SmashBros/lib_sb_Stage.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_Source_ScriptModule_modules_SmashBros_lib_sb_Stage.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_Source_ScriptModule_modules_SmashBros_lib_sb_Stage.cpp$(DependSuffix): ../../Source/ScriptModule/modules/SmashBros/lib_sb_Stage.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_Source_ScriptModule_modules_SmashBros_lib_sb_Stage.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_Source_ScriptModule_modules_SmashBros_lib_sb_Stage.cpp$(DependSuffix) -MM ../../Source/ScriptModule/modules/SmashBros/lib_sb_Stage.cpp

$(IntermediateDirectory)/up_up_Source_ScriptModule_modules_SmashBros_lib_sb_Stage.cpp$(PreprocessSuffix): ../../Source/ScriptModule/modules/SmashBros/lib_sb_Stage.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_Source_ScriptModule_modules_SmashBros_lib_sb_Stage.cpp$(PreprocessSuffix) ../../Source/ScriptModule/modules/SmashBros/lib_sb_Stage.cpp

$(IntermediateDirectory)/up_up_Source_ScriptModule_modules_SmashBros_lib_SmashBros.cpp$(ObjectSuffix): ../../Source/ScriptModule/modules/SmashBros/lib_SmashBros.cpp $(IntermediateDirectory)/up_up_Source_ScriptModule_modules_SmashBros_lib_SmashBros.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/luis/Code/iSSB/Source/ScriptModule/modules/SmashBros/lib_SmashBros.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_Source_ScriptModule_modules_SmashBros_lib_SmashBros.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_Source_ScriptModule_modules_SmashBros_lib_SmashBros.cpp$(DependSuffix): ../../Source/ScriptModule/modules/SmashBros/lib_SmashBros.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_Source_ScriptModule_modules_SmashBros_lib_SmashBros.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_Source_ScriptModule_modules_SmashBros_lib_SmashBros.cpp$(DependSuffix) -MM ../../Source/ScriptModule/modules/SmashBros/lib_SmashBros.cpp

$(IntermediateDirectory)/up_up_Source_ScriptModule_modules_SmashBros_lib_SmashBros.cpp$(PreprocessSuffix): ../../Source/ScriptModule/modules/SmashBros/lib_SmashBros.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_Source_ScriptModule_modules_SmashBros_lib_SmashBros.cpp$(PreprocessSuffix) ../../Source/ScriptModule/modules/SmashBros/lib_SmashBros.cpp

$(IntermediateDirectory)/up_up_Source_GameEngine_Actor_Animation.cpp$(ObjectSuffix): ../../Source/GameEngine/Actor/Animation.cpp $(IntermediateDirectory)/up_up_Source_GameEngine_Actor_Animation.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/luis/Code/iSSB/Source/GameEngine/Actor/Animation.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_Source_GameEngine_Actor_Animation.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_Source_GameEngine_Actor_Animation.cpp$(DependSuffix): ../../Source/GameEngine/Actor/Animation.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_Source_GameEngine_Actor_Animation.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_Source_GameEngine_Actor_Animation.cpp$(DependSuffix) -MM ../../Source/GameEngine/Actor/Animation.cpp

$(IntermediateDirectory)/up_up_Source_GameEngine_Actor_Animation.cpp$(PreprocessSuffix): ../../Source/GameEngine/Actor/Animation.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_Source_GameEngine_Actor_Animation.cpp$(PreprocessSuffix) ../../Source/GameEngine/Actor/Animation.cpp

$(IntermediateDirectory)/up_up_Source_GameEngine_Actor_WireframeActor.cpp$(ObjectSuffix): ../../Source/GameEngine/Actor/WireframeActor.cpp $(IntermediateDirectory)/up_up_Source_GameEngine_Actor_WireframeActor.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/luis/Code/iSSB/Source/GameEngine/Actor/WireframeActor.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_Source_GameEngine_Actor_WireframeActor.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_Source_GameEngine_Actor_WireframeActor.cpp$(DependSuffix): ../../Source/GameEngine/Actor/WireframeActor.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_Source_GameEngine_Actor_WireframeActor.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_Source_GameEngine_Actor_WireframeActor.cpp$(DependSuffix) -MM ../../Source/GameEngine/Actor/WireframeActor.cpp

$(IntermediateDirectory)/up_up_Source_GameEngine_Actor_WireframeActor.cpp$(PreprocessSuffix): ../../Source/GameEngine/Actor/WireframeActor.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_Source_GameEngine_Actor_WireframeActor.cpp$(PreprocessSuffix) ../../Source/GameEngine/Actor/WireframeActor.cpp

$(IntermediateDirectory)/up_up_Source_ScriptModule_modules_GameEngine_lib_ge_Graphics.cpp$(ObjectSuffix): ../../Source/ScriptModule/modules/GameEngine/lib_ge_Graphics.cpp $(IntermediateDirectory)/up_up_Source_ScriptModule_modules_GameEngine_lib_ge_Graphics.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/luis/Code/iSSB/Source/ScriptModule/modules/GameEngine/lib_ge_Graphics.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_Source_ScriptModule_modules_GameEngine_lib_ge_Graphics.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_Source_ScriptModule_modules_GameEngine_lib_ge_Graphics.cpp$(DependSuffix): ../../Source/ScriptModule/modules/GameEngine/lib_ge_Graphics.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_Source_ScriptModule_modules_GameEngine_lib_ge_Graphics.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_Source_ScriptModule_modules_GameEngine_lib_ge_Graphics.cpp$(DependSuffix) -MM ../../Source/ScriptModule/modules/GameEngine/lib_ge_Graphics.cpp

$(IntermediateDirectory)/up_up_Source_ScriptModule_modules_GameEngine_lib_ge_Graphics.cpp$(PreprocessSuffix): ../../Source/ScriptModule/modules/GameEngine/lib_ge_Graphics.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_Source_ScriptModule_modules_GameEngine_lib_ge_Graphics.cpp$(PreprocessSuffix) ../../Source/ScriptModule/modules/GameEngine/lib_ge_Graphics.cpp

$(IntermediateDirectory)/up_up_Source_SmashBros_Menus_MenuPieces_ToggleButtons.cpp$(ObjectSuffix): ../../Source/SmashBros/Menus/MenuPieces/ToggleButtons.cpp $(IntermediateDirectory)/up_up_Source_SmashBros_Menus_MenuPieces_ToggleButtons.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/luis/Code/iSSB/Source/SmashBros/Menus/MenuPieces/ToggleButtons.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_Source_SmashBros_Menus_MenuPieces_ToggleButtons.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_Source_SmashBros_Menus_MenuPieces_ToggleButtons.cpp$(DependSuffix): ../../Source/SmashBros/Menus/MenuPieces/ToggleButtons.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_Source_SmashBros_Menus_MenuPieces_ToggleButtons.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_Source_SmashBros_Menus_MenuPieces_ToggleButtons.cpp$(DependSuffix) -MM ../../Source/SmashBros/Menus/MenuPieces/ToggleButtons.cpp

$(IntermediateDirectory)/up_up_Source_SmashBros_Menus_MenuPieces_ToggleButtons.cpp$(PreprocessSuffix): ../../Source/SmashBros/Menus/MenuPieces/ToggleButtons.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_Source_SmashBros_Menus_MenuPieces_ToggleButtons.cpp$(PreprocessSuffix) ../../Source/SmashBros/Menus/MenuPieces/ToggleButtons.cpp

$(IntermediateDirectory)/up_up_Source_ScriptModule_modules_GameEngine_lib_ge_Global.cpp$(ObjectSuffix): ../../Source/ScriptModule/modules/GameEngine/lib_ge_Global.cpp $(IntermediateDirectory)/up_up_Source_ScriptModule_modules_GameEngine_lib_ge_Global.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/luis/Code/iSSB/Source/ScriptModule/modules/GameEngine/lib_ge_Global.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_Source_ScriptModule_modules_GameEngine_lib_ge_Global.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_Source_ScriptModule_modules_GameEngine_lib_ge_Global.cpp$(DependSuffix): ../../Source/ScriptModule/modules/GameEngine/lib_ge_Global.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_Source_ScriptModule_modules_GameEngine_lib_ge_Global.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_Source_ScriptModule_modules_GameEngine_lib_ge_Global.cpp$(DependSuffix) -MM ../../Source/ScriptModule/modules/GameEngine/lib_ge_Global.cpp

$(IntermediateDirectory)/up_up_Source_ScriptModule_modules_GameEngine_lib_ge_Global.cpp$(PreprocessSuffix): ../../Source/ScriptModule/modules/GameEngine/lib_ge_Global.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_Source_ScriptModule_modules_GameEngine_lib_ge_Global.cpp$(PreprocessSuffix) ../../Source/ScriptModule/modules/GameEngine/lib_ge_Global.cpp

$(IntermediateDirectory)/up_up_Source_GameEngine_CodeBridge_ObjCBridge.mm$(ObjectSuffix): ../../Source/GameEngine/CodeBridge/ObjCBridge.mm $(IntermediateDirectory)/up_up_Source_GameEngine_CodeBridge_ObjCBridge.mm$(DependSuffix)
	$(CXX) $(IncludePCH) -x objective-c++ $(SourceSwitch) "/home/luis/Code/iSSB/Source/GameEngine/CodeBridge/ObjCBridge.mm" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_Source_GameEngine_CodeBridge_ObjCBridge.mm$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_Source_GameEngine_CodeBridge_ObjCBridge.mm$(DependSuffix): ../../Source/GameEngine/CodeBridge/ObjCBridge.mm
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_Source_GameEngine_CodeBridge_ObjCBridge.mm$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_Source_GameEngine_CodeBridge_ObjCBridge.mm$(DependSuffix) -MM ../../Source/GameEngine/CodeBridge/ObjCBridge.mm

$(IntermediateDirectory)/up_up_Source_GameEngine_CodeBridge_ObjCBridge.mm$(PreprocessSuffix): ../../Source/GameEngine/CodeBridge/ObjCBridge.mm
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_Source_GameEngine_CodeBridge_ObjCBridge.mm$(PreprocessSuffix) ../../Source/GameEngine/CodeBridge/ObjCBridge.mm

$(IntermediateDirectory)/up_up_Source_ScriptModule_modules_SmashBros_inherit_lib_sb_inherit_GameElement.cpp$(ObjectSuffix): ../../Source/ScriptModule/modules/SmashBros/inherit/lib_sb_inherit_GameElement.cpp $(IntermediateDirectory)/up_up_Source_ScriptModule_modules_SmashBros_inherit_lib_sb_inherit_GameElement.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/luis/Code/iSSB/Source/ScriptModule/modules/SmashBros/inherit/lib_sb_inherit_GameElement.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_Source_ScriptModule_modules_SmashBros_inherit_lib_sb_inherit_GameElement.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_Source_ScriptModule_modules_SmashBros_inherit_lib_sb_inherit_GameElement.cpp$(DependSuffix): ../../Source/ScriptModule/modules/SmashBros/inherit/lib_sb_inherit_GameElement.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_Source_ScriptModule_modules_SmashBros_inherit_lib_sb_inherit_GameElement.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_Source_ScriptModule_modules_SmashBros_inherit_lib_sb_inherit_GameElement.cpp$(DependSuffix) -MM ../../Source/ScriptModule/modules/SmashBros/inherit/lib_sb_inherit_GameElement.cpp

$(IntermediateDirectory)/up_up_Source_ScriptModule_modules_SmashBros_inherit_lib_sb_inherit_GameElement.cpp$(PreprocessSuffix): ../../Source/ScriptModule/modules/SmashBros/inherit/lib_sb_inherit_GameElement.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_Source_ScriptModule_modules_SmashBros_inherit_lib_sb_inherit_GameElement.cpp$(PreprocessSuffix) ../../Source/ScriptModule/modules/SmashBros/inherit/lib_sb_inherit_GameElement.cpp

$(IntermediateDirectory)/up_up_Source_SmashBros_Game_Items_SmashBall.cpp$(ObjectSuffix): ../../Source/SmashBros/Game/Items/SmashBall.cpp $(IntermediateDirectory)/up_up_Source_SmashBros_Game_Items_SmashBall.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/luis/Code/iSSB/Source/SmashBros/Game/Items/SmashBall.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_Source_SmashBros_Game_Items_SmashBall.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_Source_SmashBros_Game_Items_SmashBall.cpp$(DependSuffix): ../../Source/SmashBros/Game/Items/SmashBall.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_Source_SmashBros_Game_Items_SmashBall.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_Source_SmashBros_Game_Items_SmashBall.cpp$(DependSuffix) -MM ../../Source/SmashBros/Game/Items/SmashBall.cpp

$(IntermediateDirectory)/up_up_Source_SmashBros_Game_Items_SmashBall.cpp$(PreprocessSuffix): ../../Source/SmashBros/Game/Items/SmashBall.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_Source_SmashBros_Game_Items_SmashBall.cpp$(PreprocessSuffix) ../../Source/SmashBros/Game/Items/SmashBall.cpp

$(IntermediateDirectory)/up_up_Source_ScriptModule_modules_GameEngine_lib_ge_Math.cpp$(ObjectSuffix): ../../Source/ScriptModule/modules/GameEngine/lib_ge_Math.cpp $(IntermediateDirectory)/up_up_Source_ScriptModule_modules_GameEngine_lib_ge_Math.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/luis/Code/iSSB/Source/ScriptModule/modules/GameEngine/lib_ge_Math.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_Source_ScriptModule_modules_GameEngine_lib_ge_Math.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_Source_ScriptModule_modules_GameEngine_lib_ge_Math.cpp$(DependSuffix): ../../Source/ScriptModule/modules/GameEngine/lib_ge_Math.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_Source_ScriptModule_modules_GameEngine_lib_ge_Math.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_Source_ScriptModule_modules_GameEngine_lib_ge_Math.cpp$(DependSuffix) -MM ../../Source/ScriptModule/modules/GameEngine/lib_ge_Math.cpp

$(IntermediateDirectory)/up_up_Source_ScriptModule_modules_GameEngine_lib_ge_Math.cpp$(PreprocessSuffix): ../../Source/ScriptModule/modules/GameEngine/lib_ge_Math.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_Source_ScriptModule_modules_GameEngine_lib_ge_Math.cpp$(PreprocessSuffix) ../../Source/ScriptModule/modules/GameEngine/lib_ge_Math.cpp

$(IntermediateDirectory)/up_up_Source_GameEngine_CodeBridge_WinBridge.cpp$(ObjectSuffix): ../../Source/GameEngine/CodeBridge/WinBridge.cpp $(IntermediateDirectory)/up_up_Source_GameEngine_CodeBridge_WinBridge.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/luis/Code/iSSB/Source/GameEngine/CodeBridge/WinBridge.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_Source_GameEngine_CodeBridge_WinBridge.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_Source_GameEngine_CodeBridge_WinBridge.cpp$(DependSuffix): ../../Source/GameEngine/CodeBridge/WinBridge.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_Source_GameEngine_CodeBridge_WinBridge.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_Source_GameEngine_CodeBridge_WinBridge.cpp$(DependSuffix) -MM ../../Source/GameEngine/CodeBridge/WinBridge.cpp

$(IntermediateDirectory)/up_up_Source_GameEngine_CodeBridge_WinBridge.cpp$(PreprocessSuffix): ../../Source/GameEngine/CodeBridge/WinBridge.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_Source_GameEngine_CodeBridge_WinBridge.cpp$(PreprocessSuffix) ../../Source/GameEngine/CodeBridge/WinBridge.cpp

$(IntermediateDirectory)/up_up_Source_GameEngine_Graphics_Graphics2D.cpp$(ObjectSuffix): ../../Source/GameEngine/Graphics/Graphics2D.cpp $(IntermediateDirectory)/up_up_Source_GameEngine_Graphics_Graphics2D.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/luis/Code/iSSB/Source/GameEngine/Graphics/Graphics2D.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_Source_GameEngine_Graphics_Graphics2D.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_Source_GameEngine_Graphics_Graphics2D.cpp$(DependSuffix): ../../Source/GameEngine/Graphics/Graphics2D.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_Source_GameEngine_Graphics_Graphics2D.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_Source_GameEngine_Graphics_Graphics2D.cpp$(DependSuffix) -MM ../../Source/GameEngine/Graphics/Graphics2D.cpp

$(IntermediateDirectory)/up_up_Source_GameEngine_Graphics_Graphics2D.cpp$(PreprocessSuffix): ../../Source/GameEngine/Graphics/Graphics2D.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_Source_GameEngine_Graphics_Graphics2D.cpp$(PreprocessSuffix) ../../Source/GameEngine/Graphics/Graphics2D.cpp

$(IntermediateDirectory)/up_up_Source_SmashBros_AttackRandomizer.cpp$(ObjectSuffix): ../../Source/SmashBros/AttackRandomizer.cpp $(IntermediateDirectory)/up_up_Source_SmashBros_AttackRandomizer.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/luis/Code/iSSB/Source/SmashBros/AttackRandomizer.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_Source_SmashBros_AttackRandomizer.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_Source_SmashBros_AttackRandomizer.cpp$(DependSuffix): ../../Source/SmashBros/AttackRandomizer.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_Source_SmashBros_AttackRandomizer.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_Source_SmashBros_AttackRandomizer.cpp$(DependSuffix) -MM ../../Source/SmashBros/AttackRandomizer.cpp

$(IntermediateDirectory)/up_up_Source_SmashBros_AttackRandomizer.cpp$(PreprocessSuffix): ../../Source/SmashBros/AttackRandomizer.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_Source_SmashBros_AttackRandomizer.cpp$(PreprocessSuffix) ../../Source/SmashBros/AttackRandomizer.cpp

$(IntermediateDirectory)/up_up_Source_GameEngine_Util_Font.cpp$(ObjectSuffix): ../../Source/GameEngine/Util/Font.cpp $(IntermediateDirectory)/up_up_Source_GameEngine_Util_Font.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/luis/Code/iSSB/Source/GameEngine/Util/Font.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_Source_GameEngine_Util_Font.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_Source_GameEngine_Util_Font.cpp$(DependSuffix): ../../Source/GameEngine/Util/Font.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_Source_GameEngine_Util_Font.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_Source_GameEngine_Util_Font.cpp$(DependSuffix) -MM ../../Source/GameEngine/Util/Font.cpp

$(IntermediateDirectory)/up_up_Source_GameEngine_Util_Font.cpp$(PreprocessSuffix): ../../Source/GameEngine/Util/Font.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_Source_GameEngine_Util_Font.cpp$(PreprocessSuffix) ../../Source/GameEngine/Util/Font.cpp

$(IntermediateDirectory)/up_up_Source_SmashBros_AttackTemplates.cpp$(ObjectSuffix): ../../Source/SmashBros/AttackTemplates.cpp $(IntermediateDirectory)/up_up_Source_SmashBros_AttackTemplates.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/luis/Code/iSSB/Source/SmashBros/AttackTemplates.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_Source_SmashBros_AttackTemplates.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_Source_SmashBros_AttackTemplates.cpp$(DependSuffix): ../../Source/SmashBros/AttackTemplates.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_Source_SmashBros_AttackTemplates.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_Source_SmashBros_AttackTemplates.cpp$(DependSuffix) -MM ../../Source/SmashBros/AttackTemplates.cpp

$(IntermediateDirectory)/up_up_Source_SmashBros_AttackTemplates.cpp$(PreprocessSuffix): ../../Source/SmashBros/AttackTemplates.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_Source_SmashBros_AttackTemplates.cpp$(PreprocessSuffix) ../../Source/SmashBros/AttackTemplates.cpp

$(IntermediateDirectory)/up_up_Source_SmashBros_HitBox.cpp$(ObjectSuffix): ../../Source/SmashBros/HitBox.cpp $(IntermediateDirectory)/up_up_Source_SmashBros_HitBox.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/luis/Code/iSSB/Source/SmashBros/HitBox.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_Source_SmashBros_HitBox.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_Source_SmashBros_HitBox.cpp$(DependSuffix): ../../Source/SmashBros/HitBox.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_Source_SmashBros_HitBox.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_Source_SmashBros_HitBox.cpp$(DependSuffix) -MM ../../Source/SmashBros/HitBox.cpp

$(IntermediateDirectory)/up_up_Source_SmashBros_HitBox.cpp$(PreprocessSuffix): ../../Source/SmashBros/HitBox.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_Source_SmashBros_HitBox.cpp$(PreprocessSuffix) ../../Source/SmashBros/HitBox.cpp

$(IntermediateDirectory)/up_up_Source_SmashBros_Game_Stages_BattlefieldBrawl.cpp$(ObjectSuffix): ../../Source/SmashBros/Game/Stages/BattlefieldBrawl.cpp $(IntermediateDirectory)/up_up_Source_SmashBros_Game_Stages_BattlefieldBrawl.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/luis/Code/iSSB/Source/SmashBros/Game/Stages/BattlefieldBrawl.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_Source_SmashBros_Game_Stages_BattlefieldBrawl.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_Source_SmashBros_Game_Stages_BattlefieldBrawl.cpp$(DependSuffix): ../../Source/SmashBros/Game/Stages/BattlefieldBrawl.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_Source_SmashBros_Game_Stages_BattlefieldBrawl.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_Source_SmashBros_Game_Stages_BattlefieldBrawl.cpp$(DependSuffix) -MM ../../Source/SmashBros/Game/Stages/BattlefieldBrawl.cpp

$(IntermediateDirectory)/up_up_Source_SmashBros_Game_Stages_BattlefieldBrawl.cpp$(PreprocessSuffix): ../../Source/SmashBros/Game/Stages/BattlefieldBrawl.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_Source_SmashBros_Game_Stages_BattlefieldBrawl.cpp$(PreprocessSuffix) ../../Source/SmashBros/Game/Stages/BattlefieldBrawl.cpp

$(IntermediateDirectory)/up_up_Source_GameEngine_Util_FileTools.cpp$(ObjectSuffix): ../../Source/GameEngine/Util/FileTools.cpp $(IntermediateDirectory)/up_up_Source_GameEngine_Util_FileTools.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/luis/Code/iSSB/Source/GameEngine/Util/FileTools.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_Source_GameEngine_Util_FileTools.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_Source_GameEngine_Util_FileTools.cpp$(DependSuffix): ../../Source/GameEngine/Util/FileTools.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_Source_GameEngine_Util_FileTools.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_Source_GameEngine_Util_FileTools.cpp$(DependSuffix) -MM ../../Source/GameEngine/Util/FileTools.cpp

$(IntermediateDirectory)/up_up_Source_GameEngine_Util_FileTools.cpp$(PreprocessSuffix): ../../Source/GameEngine/Util/FileTools.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_Source_GameEngine_Util_FileTools.cpp$(PreprocessSuffix) ../../Source/GameEngine/Util/FileTools.cpp

$(IntermediateDirectory)/up_up_Source_ScriptModule_modules_SmashBros_lib_sb_Player.cpp$(ObjectSuffix): ../../Source/ScriptModule/modules/SmashBros/lib_sb_Player.cpp $(IntermediateDirectory)/up_up_Source_ScriptModule_modules_SmashBros_lib_sb_Player.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/luis/Code/iSSB/Source/ScriptModule/modules/SmashBros/lib_sb_Player.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_Source_ScriptModule_modules_SmashBros_lib_sb_Player.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_Source_ScriptModule_modules_SmashBros_lib_sb_Player.cpp$(DependSuffix): ../../Source/ScriptModule/modules/SmashBros/lib_sb_Player.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_Source_ScriptModule_modules_SmashBros_lib_sb_Player.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_Source_ScriptModule_modules_SmashBros_lib_sb_Player.cpp$(DependSuffix) -MM ../../Source/ScriptModule/modules/SmashBros/lib_sb_Player.cpp

$(IntermediateDirectory)/up_up_Source_ScriptModule_modules_SmashBros_lib_sb_Player.cpp$(PreprocessSuffix): ../../Source/ScriptModule/modules/SmashBros/lib_sb_Player.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_Source_ScriptModule_modules_SmashBros_lib_sb_Player.cpp$(PreprocessSuffix) ../../Source/ScriptModule/modules/SmashBros/lib_sb_Player.cpp

$(IntermediateDirectory)/up_up_Source_SmashBros_Stage.cpp$(ObjectSuffix): ../../Source/SmashBros/Stage.cpp $(IntermediateDirectory)/up_up_Source_SmashBros_Stage.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/luis/Code/iSSB/Source/SmashBros/Stage.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_Source_SmashBros_Stage.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_Source_SmashBros_Stage.cpp$(DependSuffix): ../../Source/SmashBros/Stage.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_Source_SmashBros_Stage.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_Source_SmashBros_Stage.cpp$(DependSuffix) -MM ../../Source/SmashBros/Stage.cpp

$(IntermediateDirectory)/up_up_Source_SmashBros_Stage.cpp$(PreprocessSuffix): ../../Source/SmashBros/Stage.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_Source_SmashBros_Stage.cpp$(PreprocessSuffix) ../../Source/SmashBros/Stage.cpp

$(IntermediateDirectory)/up_up_Source_GameEngine_ScreenManager_MenuScreen.cpp$(ObjectSuffix): ../../Source/GameEngine/ScreenManager/MenuScreen.cpp $(IntermediateDirectory)/up_up_Source_GameEngine_ScreenManager_MenuScreen.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/luis/Code/iSSB/Source/GameEngine/ScreenManager/MenuScreen.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_Source_GameEngine_ScreenManager_MenuScreen.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_Source_GameEngine_ScreenManager_MenuScreen.cpp$(DependSuffix): ../../Source/GameEngine/ScreenManager/MenuScreen.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_Source_GameEngine_ScreenManager_MenuScreen.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_Source_GameEngine_ScreenManager_MenuScreen.cpp$(DependSuffix) -MM ../../Source/GameEngine/ScreenManager/MenuScreen.cpp

$(IntermediateDirectory)/up_up_Source_GameEngine_ScreenManager_MenuScreen.cpp$(PreprocessSuffix): ../../Source/GameEngine/ScreenManager/MenuScreen.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_Source_GameEngine_ScreenManager_MenuScreen.cpp$(PreprocessSuffix) ../../Source/GameEngine/ScreenManager/MenuScreen.cpp

$(IntermediateDirectory)/up_up_Source_ScriptModule_ScriptManager.cpp$(ObjectSuffix): ../../Source/ScriptModule/ScriptManager.cpp $(IntermediateDirectory)/up_up_Source_ScriptModule_ScriptManager.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/luis/Code/iSSB/Source/ScriptModule/ScriptManager.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_Source_ScriptModule_ScriptManager.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_Source_ScriptModule_ScriptManager.cpp$(DependSuffix): ../../Source/ScriptModule/ScriptManager.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_Source_ScriptModule_ScriptManager.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_Source_ScriptModule_ScriptManager.cpp$(DependSuffix) -MM ../../Source/ScriptModule/ScriptManager.cpp

$(IntermediateDirectory)/up_up_Source_ScriptModule_ScriptManager.cpp$(PreprocessSuffix): ../../Source/ScriptModule/ScriptManager.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_Source_ScriptModule_ScriptManager.cpp$(PreprocessSuffix) ../../Source/ScriptModule/ScriptManager.cpp

$(IntermediateDirectory)/up_up_Source_ScriptModule_ScriptEntity.cpp$(ObjectSuffix): ../../Source/ScriptModule/ScriptEntity.cpp $(IntermediateDirectory)/up_up_Source_ScriptModule_ScriptEntity.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/luis/Code/iSSB/Source/ScriptModule/ScriptEntity.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_Source_ScriptModule_ScriptEntity.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_Source_ScriptModule_ScriptEntity.cpp$(DependSuffix): ../../Source/ScriptModule/ScriptEntity.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_Source_ScriptModule_ScriptEntity.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_Source_ScriptModule_ScriptEntity.cpp$(DependSuffix) -MM ../../Source/ScriptModule/ScriptEntity.cpp

$(IntermediateDirectory)/up_up_Source_ScriptModule_ScriptEntity.cpp$(PreprocessSuffix): ../../Source/ScriptModule/ScriptEntity.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_Source_ScriptModule_ScriptEntity.cpp$(PreprocessSuffix) ../../Source/ScriptModule/ScriptEntity.cpp

$(IntermediateDirectory)/up_up_Source_SmashBros_Projectile.cpp$(ObjectSuffix): ../../Source/SmashBros/Projectile.cpp $(IntermediateDirectory)/up_up_Source_SmashBros_Projectile.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/luis/Code/iSSB/Source/SmashBros/Projectile.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_Source_SmashBros_Projectile.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_Source_SmashBros_Projectile.cpp$(DependSuffix): ../../Source/SmashBros/Projectile.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_Source_SmashBros_Projectile.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_Source_SmashBros_Projectile.cpp$(DependSuffix) -MM ../../Source/SmashBros/Projectile.cpp

$(IntermediateDirectory)/up_up_Source_SmashBros_Projectile.cpp$(PreprocessSuffix): ../../Source/SmashBros/Projectile.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_Source_SmashBros_Projectile.cpp$(PreprocessSuffix) ../../Source/SmashBros/Projectile.cpp

$(IntermediateDirectory)/up_up_Source_ScriptModule_ScriptOperatorOverloads.cpp$(ObjectSuffix): ../../Source/ScriptModule/ScriptOperatorOverloads.cpp $(IntermediateDirectory)/up_up_Source_ScriptModule_ScriptOperatorOverloads.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/luis/Code/iSSB/Source/ScriptModule/ScriptOperatorOverloads.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_Source_ScriptModule_ScriptOperatorOverloads.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_Source_ScriptModule_ScriptOperatorOverloads.cpp$(DependSuffix): ../../Source/ScriptModule/ScriptOperatorOverloads.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_Source_ScriptModule_ScriptOperatorOverloads.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_Source_ScriptModule_ScriptOperatorOverloads.cpp$(DependSuffix) -MM ../../Source/ScriptModule/ScriptOperatorOverloads.cpp

$(IntermediateDirectory)/up_up_Source_ScriptModule_ScriptOperatorOverloads.cpp$(PreprocessSuffix): ../../Source/ScriptModule/ScriptOperatorOverloads.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_Source_ScriptModule_ScriptOperatorOverloads.cpp$(PreprocessSuffix) ../../Source/ScriptModule/ScriptOperatorOverloads.cpp

$(IntermediateDirectory)/up_up_Source_Game.cpp$(ObjectSuffix): ../../Source/Game.cpp $(IntermediateDirectory)/up_up_Source_Game.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/luis/Code/iSSB/Source/Game.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_Source_Game.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_Source_Game.cpp$(DependSuffix): ../../Source/Game.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_Source_Game.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_Source_Game.cpp$(DependSuffix) -MM ../../Source/Game.cpp

$(IntermediateDirectory)/up_up_Source_Game.cpp$(PreprocessSuffix): ../../Source/Game.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_Source_Game.cpp$(PreprocessSuffix) ../../Source/Game.cpp

$(IntermediateDirectory)/up_up_Source_GameEngine_Util_HapticFeedback.cpp$(ObjectSuffix): ../../Source/GameEngine/Util/HapticFeedback.cpp $(IntermediateDirectory)/up_up_Source_GameEngine_Util_HapticFeedback.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/luis/Code/iSSB/Source/GameEngine/Util/HapticFeedback.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_Source_GameEngine_Util_HapticFeedback.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_Source_GameEngine_Util_HapticFeedback.cpp$(DependSuffix): ../../Source/GameEngine/Util/HapticFeedback.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_Source_GameEngine_Util_HapticFeedback.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_Source_GameEngine_Util_HapticFeedback.cpp$(DependSuffix) -MM ../../Source/GameEngine/Util/HapticFeedback.cpp

$(IntermediateDirectory)/up_up_Source_GameEngine_Util_HapticFeedback.cpp$(PreprocessSuffix): ../../Source/GameEngine/Util/HapticFeedback.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_Source_GameEngine_Util_HapticFeedback.cpp$(PreprocessSuffix) ../../Source/GameEngine/Util/HapticFeedback.cpp

$(IntermediateDirectory)/up_up_Source_SmashBros_Chargebar.cpp$(ObjectSuffix): ../../Source/SmashBros/Chargebar.cpp $(IntermediateDirectory)/up_up_Source_SmashBros_Chargebar.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/luis/Code/iSSB/Source/SmashBros/Chargebar.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_Source_SmashBros_Chargebar.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_Source_SmashBros_Chargebar.cpp$(DependSuffix): ../../Source/SmashBros/Chargebar.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_Source_SmashBros_Chargebar.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_Source_SmashBros_Chargebar.cpp$(DependSuffix) -MM ../../Source/SmashBros/Chargebar.cpp

$(IntermediateDirectory)/up_up_Source_SmashBros_Chargebar.cpp$(PreprocessSuffix): ../../Source/SmashBros/Chargebar.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_Source_SmashBros_Chargebar.cpp$(PreprocessSuffix) ../../Source/SmashBros/Chargebar.cpp

$(IntermediateDirectory)/up_up_Source_SmashBros_CollisionManager.cpp$(ObjectSuffix): ../../Source/SmashBros/CollisionManager.cpp $(IntermediateDirectory)/up_up_Source_SmashBros_CollisionManager.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/luis/Code/iSSB/Source/SmashBros/CollisionManager.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_Source_SmashBros_CollisionManager.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_Source_SmashBros_CollisionManager.cpp$(DependSuffix): ../../Source/SmashBros/CollisionManager.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_Source_SmashBros_CollisionManager.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_Source_SmashBros_CollisionManager.cpp$(DependSuffix) -MM ../../Source/SmashBros/CollisionManager.cpp

$(IntermediateDirectory)/up_up_Source_SmashBros_CollisionManager.cpp$(PreprocessSuffix): ../../Source/SmashBros/CollisionManager.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_Source_SmashBros_CollisionManager.cpp$(PreprocessSuffix) ../../Source/SmashBros/CollisionManager.cpp

$(IntermediateDirectory)/up_up_Source_SmashBros_Menus_MenuPieces_MenuBarSmallButton.cpp$(ObjectSuffix): ../../Source/SmashBros/Menus/MenuPieces/MenuBarSmallButton.cpp $(IntermediateDirectory)/up_up_Source_SmashBros_Menus_MenuPieces_MenuBarSmallButton.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/luis/Code/iSSB/Source/SmashBros/Menus/MenuPieces/MenuBarSmallButton.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_Source_SmashBros_Menus_MenuPieces_MenuBarSmallButton.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_Source_SmashBros_Menus_MenuPieces_MenuBarSmallButton.cpp$(DependSuffix): ../../Source/SmashBros/Menus/MenuPieces/MenuBarSmallButton.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_Source_SmashBros_Menus_MenuPieces_MenuBarSmallButton.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_Source_SmashBros_Menus_MenuPieces_MenuBarSmallButton.cpp$(DependSuffix) -MM ../../Source/SmashBros/Menus/MenuPieces/MenuBarSmallButton.cpp

$(IntermediateDirectory)/up_up_Source_SmashBros_Menus_MenuPieces_MenuBarSmallButton.cpp$(PreprocessSuffix): ../../Source/SmashBros/Menus/MenuPieces/MenuBarSmallButton.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_Source_SmashBros_Menus_MenuPieces_MenuBarSmallButton.cpp$(PreprocessSuffix) ../../Source/SmashBros/Menus/MenuPieces/MenuBarSmallButton.cpp

$(IntermediateDirectory)/up_up_Source_SmashBros_Camera.cpp$(ObjectSuffix): ../../Source/SmashBros/Camera.cpp $(IntermediateDirectory)/up_up_Source_SmashBros_Camera.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/luis/Code/iSSB/Source/SmashBros/Camera.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_Source_SmashBros_Camera.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_Source_SmashBros_Camera.cpp$(DependSuffix): ../../Source/SmashBros/Camera.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_Source_SmashBros_Camera.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_Source_SmashBros_Camera.cpp$(DependSuffix) -MM ../../Source/SmashBros/Camera.cpp

$(IntermediateDirectory)/up_up_Source_SmashBros_Camera.cpp$(PreprocessSuffix): ../../Source/SmashBros/Camera.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_Source_SmashBros_Camera.cpp$(PreprocessSuffix) ../../Source/SmashBros/Camera.cpp

$(IntermediateDirectory)/up_up_Source_GameEngine_AssetManager.cpp$(ObjectSuffix): ../../Source/GameEngine/AssetManager.cpp $(IntermediateDirectory)/up_up_Source_GameEngine_AssetManager.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/luis/Code/iSSB/Source/GameEngine/AssetManager.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_Source_GameEngine_AssetManager.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_Source_GameEngine_AssetManager.cpp$(DependSuffix): ../../Source/GameEngine/AssetManager.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_Source_GameEngine_AssetManager.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_Source_GameEngine_AssetManager.cpp$(DependSuffix) -MM ../../Source/GameEngine/AssetManager.cpp

$(IntermediateDirectory)/up_up_Source_GameEngine_AssetManager.cpp$(PreprocessSuffix): ../../Source/GameEngine/AssetManager.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_Source_GameEngine_AssetManager.cpp$(PreprocessSuffix) ../../Source/GameEngine/AssetManager.cpp

$(IntermediateDirectory)/up_up_Source_SmashBros_GameElement.cpp$(ObjectSuffix): ../../Source/SmashBros/GameElement.cpp $(IntermediateDirectory)/up_up_Source_SmashBros_GameElement.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/luis/Code/iSSB/Source/SmashBros/GameElement.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_Source_SmashBros_GameElement.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_Source_SmashBros_GameElement.cpp$(DependSuffix): ../../Source/SmashBros/GameElement.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_Source_SmashBros_GameElement.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_Source_SmashBros_GameElement.cpp$(DependSuffix) -MM ../../Source/SmashBros/GameElement.cpp

$(IntermediateDirectory)/up_up_Source_SmashBros_GameElement.cpp$(PreprocessSuffix): ../../Source/SmashBros/GameElement.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_Source_SmashBros_GameElement.cpp$(PreprocessSuffix) ../../Source/SmashBros/GameElement.cpp

$(IntermediateDirectory)/up_up_Source_ScriptModule_modules_GameEngine_inherit_lib_ge_inherit_Screen.cpp$(ObjectSuffix): ../../Source/ScriptModule/modules/GameEngine/inherit/lib_ge_inherit_Screen.cpp $(IntermediateDirectory)/up_up_Source_ScriptModule_modules_GameEngine_inherit_lib_ge_inherit_Screen.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/luis/Code/iSSB/Source/ScriptModule/modules/GameEngine/inherit/lib_ge_inherit_Screen.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_Source_ScriptModule_modules_GameEngine_inherit_lib_ge_inherit_Screen.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_Source_ScriptModule_modules_GameEngine_inherit_lib_ge_inherit_Screen.cpp$(DependSuffix): ../../Source/ScriptModule/modules/GameEngine/inherit/lib_ge_inherit_Screen.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_Source_ScriptModule_modules_GameEngine_inherit_lib_ge_inherit_Screen.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_Source_ScriptModule_modules_GameEngine_inherit_lib_ge_inherit_Screen.cpp$(DependSuffix) -MM ../../Source/ScriptModule/modules/GameEngine/inherit/lib_ge_inherit_Screen.cpp

$(IntermediateDirectory)/up_up_Source_ScriptModule_modules_GameEngine_inherit_lib_ge_inherit_Screen.cpp$(PreprocessSuffix): ../../Source/ScriptModule/modules/GameEngine/inherit/lib_ge_inherit_Screen.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_Source_ScriptModule_modules_GameEngine_inherit_lib_ge_inherit_Screen.cpp$(PreprocessSuffix) ../../Source/ScriptModule/modules/GameEngine/inherit/lib_ge_inherit_Screen.cpp

$(IntermediateDirectory)/up_up_Source_SmashBros_Controls.cpp$(ObjectSuffix): ../../Source/SmashBros/Controls.cpp $(IntermediateDirectory)/up_up_Source_SmashBros_Controls.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/luis/Code/iSSB/Source/SmashBros/Controls.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_Source_SmashBros_Controls.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_Source_SmashBros_Controls.cpp$(DependSuffix): ../../Source/SmashBros/Controls.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_Source_SmashBros_Controls.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_Source_SmashBros_Controls.cpp$(DependSuffix) -MM ../../Source/SmashBros/Controls.cpp

$(IntermediateDirectory)/up_up_Source_SmashBros_Controls.cpp$(PreprocessSuffix): ../../Source/SmashBros/Controls.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_Source_SmashBros_Controls.cpp$(PreprocessSuffix) ../../Source/SmashBros/Controls.cpp

$(IntermediateDirectory)/up_up_Source_SmashBros_P2PDataManager.cpp$(ObjectSuffix): ../../Source/SmashBros/P2PDataManager.cpp $(IntermediateDirectory)/up_up_Source_SmashBros_P2PDataManager.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/luis/Code/iSSB/Source/SmashBros/P2PDataManager.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_Source_SmashBros_P2PDataManager.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_Source_SmashBros_P2PDataManager.cpp$(DependSuffix): ../../Source/SmashBros/P2PDataManager.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_Source_SmashBros_P2PDataManager.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_Source_SmashBros_P2PDataManager.cpp$(DependSuffix) -MM ../../Source/SmashBros/P2PDataManager.cpp

$(IntermediateDirectory)/up_up_Source_SmashBros_P2PDataManager.cpp$(PreprocessSuffix): ../../Source/SmashBros/P2PDataManager.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_Source_SmashBros_P2PDataManager.cpp$(PreprocessSuffix) ../../Source/SmashBros/P2PDataManager.cpp

$(IntermediateDirectory)/up_up_Source_SmashBros_Game_Stages_StagePieces_OffScreenExplode.cpp$(ObjectSuffix): ../../Source/SmashBros/Game/Stages/StagePieces/OffScreenExplode.cpp $(IntermediateDirectory)/up_up_Source_SmashBros_Game_Stages_StagePieces_OffScreenExplode.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/luis/Code/iSSB/Source/SmashBros/Game/Stages/StagePieces/OffScreenExplode.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_Source_SmashBros_Game_Stages_StagePieces_OffScreenExplode.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_Source_SmashBros_Game_Stages_StagePieces_OffScreenExplode.cpp$(DependSuffix): ../../Source/SmashBros/Game/Stages/StagePieces/OffScreenExplode.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_Source_SmashBros_Game_Stages_StagePieces_OffScreenExplode.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_Source_SmashBros_Game_Stages_StagePieces_OffScreenExplode.cpp$(DependSuffix) -MM ../../Source/SmashBros/Game/Stages/StagePieces/OffScreenExplode.cpp

$(IntermediateDirectory)/up_up_Source_SmashBros_Game_Stages_StagePieces_OffScreenExplode.cpp$(PreprocessSuffix): ../../Source/SmashBros/Game/Stages/StagePieces/OffScreenExplode.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_Source_SmashBros_Game_Stages_StagePieces_OffScreenExplode.cpp$(PreprocessSuffix) ../../Source/SmashBros/Game/Stages/StagePieces/OffScreenExplode.cpp

$(IntermediateDirectory)/up_up_Source_GameEngine_Actor_AnimationManager.cpp$(ObjectSuffix): ../../Source/GameEngine/Actor/AnimationManager.cpp $(IntermediateDirectory)/up_up_Source_GameEngine_Actor_AnimationManager.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/luis/Code/iSSB/Source/GameEngine/Actor/AnimationManager.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_Source_GameEngine_Actor_AnimationManager.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_Source_GameEngine_Actor_AnimationManager.cpp$(DependSuffix): ../../Source/GameEngine/Actor/AnimationManager.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_Source_GameEngine_Actor_AnimationManager.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_Source_GameEngine_Actor_AnimationManager.cpp$(DependSuffix) -MM ../../Source/GameEngine/Actor/AnimationManager.cpp

$(IntermediateDirectory)/up_up_Source_GameEngine_Actor_AnimationManager.cpp$(PreprocessSuffix): ../../Source/GameEngine/Actor/AnimationManager.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_Source_GameEngine_Actor_AnimationManager.cpp$(PreprocessSuffix) ../../Source/GameEngine/Actor/AnimationManager.cpp

$(IntermediateDirectory)/up_up_Source_GameEngine_CodeBridge_CPPBridge.cpp$(ObjectSuffix): ../../Source/GameEngine/CodeBridge/CPPBridge.cpp $(IntermediateDirectory)/up_up_Source_GameEngine_CodeBridge_CPPBridge.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/luis/Code/iSSB/Source/GameEngine/CodeBridge/CPPBridge.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_Source_GameEngine_CodeBridge_CPPBridge.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_Source_GameEngine_CodeBridge_CPPBridge.cpp$(DependSuffix): ../../Source/GameEngine/CodeBridge/CPPBridge.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_Source_GameEngine_CodeBridge_CPPBridge.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_Source_GameEngine_CodeBridge_CPPBridge.cpp$(DependSuffix) -MM ../../Source/GameEngine/CodeBridge/CPPBridge.cpp

$(IntermediateDirectory)/up_up_Source_GameEngine_CodeBridge_CPPBridge.cpp$(PreprocessSuffix): ../../Source/GameEngine/CodeBridge/CPPBridge.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_Source_GameEngine_CodeBridge_CPPBridge.cpp$(PreprocessSuffix) ../../Source/GameEngine/CodeBridge/CPPBridge.cpp

$(IntermediateDirectory)/up_up_Source_SmashBros_Player.cpp$(ObjectSuffix): ../../Source/SmashBros/Player.cpp $(IntermediateDirectory)/up_up_Source_SmashBros_Player.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/luis/Code/iSSB/Source/SmashBros/Player.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_Source_SmashBros_Player.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_Source_SmashBros_Player.cpp$(DependSuffix): ../../Source/SmashBros/Player.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_Source_SmashBros_Player.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_Source_SmashBros_Player.cpp$(DependSuffix) -MM ../../Source/SmashBros/Player.cpp

$(IntermediateDirectory)/up_up_Source_SmashBros_Player.cpp$(PreprocessSuffix): ../../Source/SmashBros/Player.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_Source_SmashBros_Player.cpp$(PreprocessSuffix) ../../Source/SmashBros/Player.cpp

$(IntermediateDirectory)/up_up_Source_SmashBros_SoundManager.cpp$(ObjectSuffix): ../../Source/SmashBros/SoundManager.cpp $(IntermediateDirectory)/up_up_Source_SmashBros_SoundManager.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/luis/Code/iSSB/Source/SmashBros/SoundManager.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_Source_SmashBros_SoundManager.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_Source_SmashBros_SoundManager.cpp$(DependSuffix): ../../Source/SmashBros/SoundManager.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_Source_SmashBros_SoundManager.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_Source_SmashBros_SoundManager.cpp$(DependSuffix) -MM ../../Source/SmashBros/SoundManager.cpp

$(IntermediateDirectory)/up_up_Source_SmashBros_SoundManager.cpp$(PreprocessSuffix): ../../Source/SmashBros/SoundManager.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_Source_SmashBros_SoundManager.cpp$(PreprocessSuffix) ../../Source/SmashBros/SoundManager.cpp

$(IntermediateDirectory)/up_up_Source_SmashBros_MusicManager.cpp$(ObjectSuffix): ../../Source/SmashBros/MusicManager.cpp $(IntermediateDirectory)/up_up_Source_SmashBros_MusicManager.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/luis/Code/iSSB/Source/SmashBros/MusicManager.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_Source_SmashBros_MusicManager.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_Source_SmashBros_MusicManager.cpp$(DependSuffix): ../../Source/SmashBros/MusicManager.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_Source_SmashBros_MusicManager.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_Source_SmashBros_MusicManager.cpp$(DependSuffix) -MM ../../Source/SmashBros/MusicManager.cpp

$(IntermediateDirectory)/up_up_Source_SmashBros_MusicManager.cpp$(PreprocessSuffix): ../../Source/SmashBros/MusicManager.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_Source_SmashBros_MusicManager.cpp$(PreprocessSuffix) ../../Source/SmashBros/MusicManager.cpp

$(IntermediateDirectory)/up_up_Source_SmashBros_HUD.cpp$(ObjectSuffix): ../../Source/SmashBros/HUD.cpp $(IntermediateDirectory)/up_up_Source_SmashBros_HUD.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/luis/Code/iSSB/Source/SmashBros/HUD.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_Source_SmashBros_HUD.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_Source_SmashBros_HUD.cpp$(DependSuffix): ../../Source/SmashBros/HUD.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_Source_SmashBros_HUD.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_Source_SmashBros_HUD.cpp$(DependSuffix) -MM ../../Source/SmashBros/HUD.cpp

$(IntermediateDirectory)/up_up_Source_SmashBros_HUD.cpp$(PreprocessSuffix): ../../Source/SmashBros/HUD.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_Source_SmashBros_HUD.cpp$(PreprocessSuffix) ../../Source/SmashBros/HUD.cpp

$(IntermediateDirectory)/up_up_Source_SmashBros_Preferences.cpp$(ObjectSuffix): ../../Source/SmashBros/Preferences.cpp $(IntermediateDirectory)/up_up_Source_SmashBros_Preferences.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/luis/Code/iSSB/Source/SmashBros/Preferences.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_Source_SmashBros_Preferences.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_Source_SmashBros_Preferences.cpp$(DependSuffix): ../../Source/SmashBros/Preferences.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_Source_SmashBros_Preferences.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_Source_SmashBros_Preferences.cpp$(DependSuffix) -MM ../../Source/SmashBros/Preferences.cpp

$(IntermediateDirectory)/up_up_Source_SmashBros_Preferences.cpp$(PreprocessSuffix): ../../Source/SmashBros/Preferences.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_Source_SmashBros_Preferences.cpp$(PreprocessSuffix) ../../Source/SmashBros/Preferences.cpp

$(IntermediateDirectory)/up_up_Source_SmashBros_Game_GameScreen.cpp$(ObjectSuffix): ../../Source/SmashBros/Game/GameScreen.cpp $(IntermediateDirectory)/up_up_Source_SmashBros_Game_GameScreen.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/luis/Code/iSSB/Source/SmashBros/Game/GameScreen.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_Source_SmashBros_Game_GameScreen.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_Source_SmashBros_Game_GameScreen.cpp$(DependSuffix): ../../Source/SmashBros/Game/GameScreen.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_Source_SmashBros_Game_GameScreen.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_Source_SmashBros_Game_GameScreen.cpp$(DependSuffix) -MM ../../Source/SmashBros/Game/GameScreen.cpp

$(IntermediateDirectory)/up_up_Source_SmashBros_Game_GameScreen.cpp$(PreprocessSuffix): ../../Source/SmashBros/Game/GameScreen.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_Source_SmashBros_Game_GameScreen.cpp$(PreprocessSuffix) ../../Source/SmashBros/Game/GameScreen.cpp

$(IntermediateDirectory)/up_up_Source_GameEngine_ApplicationEventListener.cpp$(ObjectSuffix): ../../Source/GameEngine/ApplicationEventListener.cpp $(IntermediateDirectory)/up_up_Source_GameEngine_ApplicationEventListener.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/luis/Code/iSSB/Source/GameEngine/ApplicationEventListener.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_Source_GameEngine_ApplicationEventListener.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_Source_GameEngine_ApplicationEventListener.cpp$(DependSuffix): ../../Source/GameEngine/ApplicationEventListener.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_Source_GameEngine_ApplicationEventListener.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_Source_GameEngine_ApplicationEventListener.cpp$(DependSuffix) -MM ../../Source/GameEngine/ApplicationEventListener.cpp

$(IntermediateDirectory)/up_up_Source_GameEngine_ApplicationEventListener.cpp$(PreprocessSuffix): ../../Source/GameEngine/ApplicationEventListener.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_Source_GameEngine_ApplicationEventListener.cpp$(PreprocessSuffix) ../../Source/GameEngine/ApplicationEventListener.cpp

$(IntermediateDirectory)/up_up_Source_ScriptModule_modules_SmashBros_lib_sb_Global.cpp$(ObjectSuffix): ../../Source/ScriptModule/modules/SmashBros/lib_sb_Global.cpp $(IntermediateDirectory)/up_up_Source_ScriptModule_modules_SmashBros_lib_sb_Global.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/luis/Code/iSSB/Source/ScriptModule/modules/SmashBros/lib_sb_Global.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_Source_ScriptModule_modules_SmashBros_lib_sb_Global.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_Source_ScriptModule_modules_SmashBros_lib_sb_Global.cpp$(DependSuffix): ../../Source/ScriptModule/modules/SmashBros/lib_sb_Global.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_Source_ScriptModule_modules_SmashBros_lib_sb_Global.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_Source_ScriptModule_modules_SmashBros_lib_sb_Global.cpp$(DependSuffix) -MM ../../Source/ScriptModule/modules/SmashBros/lib_sb_Global.cpp

$(IntermediateDirectory)/up_up_Source_ScriptModule_modules_SmashBros_lib_sb_Global.cpp$(PreprocessSuffix): ../../Source/ScriptModule/modules/SmashBros/lib_sb_Global.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_Source_ScriptModule_modules_SmashBros_lib_sb_Global.cpp$(PreprocessSuffix) ../../Source/ScriptModule/modules/SmashBros/lib_sb_Global.cpp

$(IntermediateDirectory)/up_up_Source_SmashBros_ItemManager.cpp$(ObjectSuffix): ../../Source/SmashBros/ItemManager.cpp $(IntermediateDirectory)/up_up_Source_SmashBros_ItemManager.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/luis/Code/iSSB/Source/SmashBros/ItemManager.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_Source_SmashBros_ItemManager.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_Source_SmashBros_ItemManager.cpp$(DependSuffix): ../../Source/SmashBros/ItemManager.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_Source_SmashBros_ItemManager.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_Source_SmashBros_ItemManager.cpp$(DependSuffix) -MM ../../Source/SmashBros/ItemManager.cpp

$(IntermediateDirectory)/up_up_Source_SmashBros_ItemManager.cpp$(PreprocessSuffix): ../../Source/SmashBros/ItemManager.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_Source_SmashBros_ItemManager.cpp$(PreprocessSuffix) ../../Source/SmashBros/ItemManager.cpp

$(IntermediateDirectory)/up_up_Source_SmashBros_Loader.cpp$(ObjectSuffix): ../../Source/SmashBros/Loader.cpp $(IntermediateDirectory)/up_up_Source_SmashBros_Loader.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/luis/Code/iSSB/Source/SmashBros/Loader.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_Source_SmashBros_Loader.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_Source_SmashBros_Loader.cpp$(DependSuffix): ../../Source/SmashBros/Loader.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_Source_SmashBros_Loader.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_Source_SmashBros_Loader.cpp$(DependSuffix) -MM ../../Source/SmashBros/Loader.cpp

$(IntermediateDirectory)/up_up_Source_SmashBros_Loader.cpp$(PreprocessSuffix): ../../Source/SmashBros/Loader.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_Source_SmashBros_Loader.cpp$(PreprocessSuffix) ../../Source/SmashBros/Loader.cpp

$(IntermediateDirectory)/up_up_Source_GameEngine_GameEngine.cpp$(ObjectSuffix): ../../Source/GameEngine/GameEngine.cpp $(IntermediateDirectory)/up_up_Source_GameEngine_GameEngine.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/luis/Code/iSSB/Source/GameEngine/GameEngine.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_Source_GameEngine_GameEngine.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_Source_GameEngine_GameEngine.cpp$(DependSuffix): ../../Source/GameEngine/GameEngine.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_Source_GameEngine_GameEngine.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_Source_GameEngine_GameEngine.cpp$(DependSuffix) -MM ../../Source/GameEngine/GameEngine.cpp

$(IntermediateDirectory)/up_up_Source_GameEngine_GameEngine.cpp$(PreprocessSuffix): ../../Source/GameEngine/GameEngine.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_Source_GameEngine_GameEngine.cpp$(PreprocessSuffix) ../../Source/GameEngine/GameEngine.cpp

$(IntermediateDirectory)/up_up_Source_GameEngine_BatchLoader.cpp$(ObjectSuffix): ../../Source/GameEngine/BatchLoader.cpp $(IntermediateDirectory)/up_up_Source_GameEngine_BatchLoader.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/luis/Code/iSSB/Source/GameEngine/BatchLoader.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_Source_GameEngine_BatchLoader.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_Source_GameEngine_BatchLoader.cpp$(DependSuffix): ../../Source/GameEngine/BatchLoader.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_Source_GameEngine_BatchLoader.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_Source_GameEngine_BatchLoader.cpp$(DependSuffix) -MM ../../Source/GameEngine/BatchLoader.cpp

$(IntermediateDirectory)/up_up_Source_GameEngine_BatchLoader.cpp$(PreprocessSuffix): ../../Source/GameEngine/BatchLoader.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_Source_GameEngine_BatchLoader.cpp$(PreprocessSuffix) ../../Source/GameEngine/BatchLoader.cpp

$(IntermediateDirectory)/up_up_Source_GameEngine_Util_P2PManager.cpp$(ObjectSuffix): ../../Source/GameEngine/Util/P2PManager.cpp $(IntermediateDirectory)/up_up_Source_GameEngine_Util_P2PManager.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/luis/Code/iSSB/Source/GameEngine/Util/P2PManager.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_Source_GameEngine_Util_P2PManager.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_Source_GameEngine_Util_P2PManager.cpp$(DependSuffix): ../../Source/GameEngine/Util/P2PManager.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_Source_GameEngine_Util_P2PManager.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_Source_GameEngine_Util_P2PManager.cpp$(DependSuffix) -MM ../../Source/GameEngine/Util/P2PManager.cpp

$(IntermediateDirectory)/up_up_Source_GameEngine_Util_P2PManager.cpp$(PreprocessSuffix): ../../Source/GameEngine/Util/P2PManager.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_Source_GameEngine_Util_P2PManager.cpp$(PreprocessSuffix) ../../Source/GameEngine/Util/P2PManager.cpp

$(IntermediateDirectory)/up_up_Source_SmashBros_Magnifier.cpp$(ObjectSuffix): ../../Source/SmashBros/Magnifier.cpp $(IntermediateDirectory)/up_up_Source_SmashBros_Magnifier.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/luis/Code/iSSB/Source/SmashBros/Magnifier.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_Source_SmashBros_Magnifier.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_Source_SmashBros_Magnifier.cpp$(DependSuffix): ../../Source/SmashBros/Magnifier.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_Source_SmashBros_Magnifier.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_Source_SmashBros_Magnifier.cpp$(DependSuffix) -MM ../../Source/SmashBros/Magnifier.cpp

$(IntermediateDirectory)/up_up_Source_SmashBros_Magnifier.cpp$(PreprocessSuffix): ../../Source/SmashBros/Magnifier.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_Source_SmashBros_Magnifier.cpp$(PreprocessSuffix) ../../Source/SmashBros/Magnifier.cpp

$(IntermediateDirectory)/up_up_Source_GameEngine_Util_PrefManager.cpp$(ObjectSuffix): ../../Source/GameEngine/Util/PrefManager.cpp $(IntermediateDirectory)/up_up_Source_GameEngine_Util_PrefManager.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/luis/Code/iSSB/Source/GameEngine/Util/PrefManager.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_Source_GameEngine_Util_PrefManager.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_Source_GameEngine_Util_PrefManager.cpp$(DependSuffix): ../../Source/GameEngine/Util/PrefManager.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_Source_GameEngine_Util_PrefManager.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_Source_GameEngine_Util_PrefManager.cpp$(DependSuffix) -MM ../../Source/GameEngine/Util/PrefManager.cpp

$(IntermediateDirectory)/up_up_Source_GameEngine_Util_PrefManager.cpp$(PreprocessSuffix): ../../Source/GameEngine/Util/PrefManager.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_Source_GameEngine_Util_PrefManager.cpp$(PreprocessSuffix) ../../Source/GameEngine/Util/PrefManager.cpp

$(IntermediateDirectory)/up_up_Source_GameEngine_Application.cpp$(ObjectSuffix): ../../Source/GameEngine/Application.cpp $(IntermediateDirectory)/up_up_Source_GameEngine_Application.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/luis/Code/iSSB/Source/GameEngine/Application.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_Source_GameEngine_Application.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_Source_GameEngine_Application.cpp$(DependSuffix): ../../Source/GameEngine/Application.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_Source_GameEngine_Application.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_Source_GameEngine_Application.cpp$(DependSuffix) -MM ../../Source/GameEngine/Application.cpp

$(IntermediateDirectory)/up_up_Source_GameEngine_Application.cpp$(PreprocessSuffix): ../../Source/GameEngine/Application.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_Source_GameEngine_Application.cpp$(PreprocessSuffix) ../../Source/GameEngine/Application.cpp

$(IntermediateDirectory)/up_up_Source_SmashBros_Menus_Menus.cpp$(ObjectSuffix): ../../Source/SmashBros/Menus/Menus.cpp $(IntermediateDirectory)/up_up_Source_SmashBros_Menus_Menus.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/luis/Code/iSSB/Source/SmashBros/Menus/Menus.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_Source_SmashBros_Menus_Menus.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_Source_SmashBros_Menus_Menus.cpp$(DependSuffix): ../../Source/SmashBros/Menus/Menus.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_Source_SmashBros_Menus_Menus.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_Source_SmashBros_Menus_Menus.cpp$(DependSuffix) -MM ../../Source/SmashBros/Menus/Menus.cpp

$(IntermediateDirectory)/up_up_Source_SmashBros_Menus_Menus.cpp$(PreprocessSuffix): ../../Source/SmashBros/Menus/Menus.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_Source_SmashBros_Menus_Menus.cpp$(PreprocessSuffix) ../../Source/SmashBros/Menus/Menus.cpp

$(IntermediateDirectory)/up_up_Source_GameEngine_Actor_Actor.cpp$(ObjectSuffix): ../../Source/GameEngine/Actor/Actor.cpp $(IntermediateDirectory)/up_up_Source_GameEngine_Actor_Actor.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/luis/Code/iSSB/Source/GameEngine/Actor/Actor.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_Source_GameEngine_Actor_Actor.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_Source_GameEngine_Actor_Actor.cpp$(DependSuffix): ../../Source/GameEngine/Actor/Actor.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_Source_GameEngine_Actor_Actor.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_Source_GameEngine_Actor_Actor.cpp$(DependSuffix) -MM ../../Source/GameEngine/Actor/Actor.cpp

$(IntermediateDirectory)/up_up_Source_GameEngine_Actor_Actor.cpp$(PreprocessSuffix): ../../Source/GameEngine/Actor/Actor.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_Source_GameEngine_Actor_Actor.cpp$(PreprocessSuffix) ../../Source/GameEngine/Actor/Actor.cpp

$(IntermediateDirectory)/up_up_Source_SmashBros_Global.cpp$(ObjectSuffix): ../../Source/SmashBros/Global.cpp $(IntermediateDirectory)/up_up_Source_SmashBros_Global.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/luis/Code/iSSB/Source/SmashBros/Global.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_Source_SmashBros_Global.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_Source_SmashBros_Global.cpp$(DependSuffix): ../../Source/SmashBros/Global.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_Source_SmashBros_Global.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_Source_SmashBros_Global.cpp$(DependSuffix) -MM ../../Source/SmashBros/Global.cpp

$(IntermediateDirectory)/up_up_Source_SmashBros_Global.cpp$(PreprocessSuffix): ../../Source/SmashBros/Global.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_Source_SmashBros_Global.cpp$(PreprocessSuffix) ../../Source/SmashBros/Global.cpp

$(IntermediateDirectory)/up_up_Source_GameEngine_Util_Image.cpp$(ObjectSuffix): ../../Source/GameEngine/Util/Image.cpp $(IntermediateDirectory)/up_up_Source_GameEngine_Util_Image.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/luis/Code/iSSB/Source/GameEngine/Util/Image.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_Source_GameEngine_Util_Image.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_Source_GameEngine_Util_Image.cpp$(DependSuffix): ../../Source/GameEngine/Util/Image.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_Source_GameEngine_Util_Image.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_Source_GameEngine_Util_Image.cpp$(DependSuffix) -MM ../../Source/GameEngine/Util/Image.cpp

$(IntermediateDirectory)/up_up_Source_GameEngine_Util_Image.cpp$(PreprocessSuffix): ../../Source/GameEngine/Util/Image.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_Source_GameEngine_Util_Image.cpp$(PreprocessSuffix) ../../Source/GameEngine/Util/Image.cpp

$(IntermediateDirectory)/up_up_Source_GameEngine_Input_Mouse.cpp$(ObjectSuffix): ../../Source/GameEngine/Input/Mouse.cpp $(IntermediateDirectory)/up_up_Source_GameEngine_Input_Mouse.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/luis/Code/iSSB/Source/GameEngine/Input/Mouse.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_Source_GameEngine_Input_Mouse.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_Source_GameEngine_Input_Mouse.cpp$(DependSuffix): ../../Source/GameEngine/Input/Mouse.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_Source_GameEngine_Input_Mouse.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_Source_GameEngine_Input_Mouse.cpp$(DependSuffix) -MM ../../Source/GameEngine/Input/Mouse.cpp

$(IntermediateDirectory)/up_up_Source_GameEngine_Input_Mouse.cpp$(PreprocessSuffix): ../../Source/GameEngine/Input/Mouse.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_Source_GameEngine_Input_Mouse.cpp$(PreprocessSuffix) ../../Source/GameEngine/Input/Mouse.cpp

$(IntermediateDirectory)/up_up_Source_SmashBros_Game_Characters_Fox.cpp$(ObjectSuffix): ../../Source/SmashBros/Game/Characters/Fox.cpp $(IntermediateDirectory)/up_up_Source_SmashBros_Game_Characters_Fox.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/luis/Code/iSSB/Source/SmashBros/Game/Characters/Fox.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_Source_SmashBros_Game_Characters_Fox.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_Source_SmashBros_Game_Characters_Fox.cpp$(DependSuffix): ../../Source/SmashBros/Game/Characters/Fox.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_Source_SmashBros_Game_Characters_Fox.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_Source_SmashBros_Game_Characters_Fox.cpp$(DependSuffix) -MM ../../Source/SmashBros/Game/Characters/Fox.cpp

$(IntermediateDirectory)/up_up_Source_SmashBros_Game_Characters_Fox.cpp$(PreprocessSuffix): ../../Source/SmashBros/Game/Characters/Fox.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_Source_SmashBros_Game_Characters_Fox.cpp$(PreprocessSuffix) ../../Source/SmashBros/Game/Characters/Fox.cpp

$(IntermediateDirectory)/up_up_Source_ScriptModule_modules_GameEngine_lib_GameEngine.cpp$(ObjectSuffix): ../../Source/ScriptModule/modules/GameEngine/lib_GameEngine.cpp $(IntermediateDirectory)/up_up_Source_ScriptModule_modules_GameEngine_lib_GameEngine.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/luis/Code/iSSB/Source/ScriptModule/modules/GameEngine/lib_GameEngine.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_Source_ScriptModule_modules_GameEngine_lib_GameEngine.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_Source_ScriptModule_modules_GameEngine_lib_GameEngine.cpp$(DependSuffix): ../../Source/ScriptModule/modules/GameEngine/lib_GameEngine.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_Source_ScriptModule_modules_GameEngine_lib_GameEngine.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_Source_ScriptModule_modules_GameEngine_lib_GameEngine.cpp$(DependSuffix) -MM ../../Source/ScriptModule/modules/GameEngine/lib_GameEngine.cpp

$(IntermediateDirectory)/up_up_Source_ScriptModule_modules_GameEngine_lib_GameEngine.cpp$(PreprocessSuffix): ../../Source/ScriptModule/modules/GameEngine/lib_GameEngine.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_Source_ScriptModule_modules_GameEngine_lib_GameEngine.cpp$(PreprocessSuffix) ../../Source/ScriptModule/modules/GameEngine/lib_GameEngine.cpp

$(IntermediateDirectory)/up_up_Source_SmashBros_Game_WinnerScreen.cpp$(ObjectSuffix): ../../Source/SmashBros/Game/WinnerScreen.cpp $(IntermediateDirectory)/up_up_Source_SmashBros_Game_WinnerScreen.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/luis/Code/iSSB/Source/SmashBros/Game/WinnerScreen.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_Source_SmashBros_Game_WinnerScreen.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_Source_SmashBros_Game_WinnerScreen.cpp$(DependSuffix): ../../Source/SmashBros/Game/WinnerScreen.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_Source_SmashBros_Game_WinnerScreen.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_Source_SmashBros_Game_WinnerScreen.cpp$(DependSuffix) -MM ../../Source/SmashBros/Game/WinnerScreen.cpp

$(IntermediateDirectory)/up_up_Source_SmashBros_Game_WinnerScreen.cpp$(PreprocessSuffix): ../../Source/SmashBros/Game/WinnerScreen.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_Source_SmashBros_Game_WinnerScreen.cpp$(PreprocessSuffix) ../../Source/SmashBros/Game/WinnerScreen.cpp

$(IntermediateDirectory)/up_up_Source_SmashBros_Game_Items_RayGun.cpp$(ObjectSuffix): ../../Source/SmashBros/Game/Items/RayGun.cpp $(IntermediateDirectory)/up_up_Source_SmashBros_Game_Items_RayGun.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/luis/Code/iSSB/Source/SmashBros/Game/Items/RayGun.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_Source_SmashBros_Game_Items_RayGun.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_Source_SmashBros_Game_Items_RayGun.cpp$(DependSuffix): ../../Source/SmashBros/Game/Items/RayGun.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_Source_SmashBros_Game_Items_RayGun.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_Source_SmashBros_Game_Items_RayGun.cpp$(DependSuffix) -MM ../../Source/SmashBros/Game/Items/RayGun.cpp

$(IntermediateDirectory)/up_up_Source_SmashBros_Game_Items_RayGun.cpp$(PreprocessSuffix): ../../Source/SmashBros/Game/Items/RayGun.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_Source_SmashBros_Game_Items_RayGun.cpp$(PreprocessSuffix) ../../Source/SmashBros/Game/Items/RayGun.cpp

$(IntermediateDirectory)/up_up_Source_SmashBros_Menus_StageSelectScreen.cpp$(ObjectSuffix): ../../Source/SmashBros/Menus/StageSelectScreen.cpp $(IntermediateDirectory)/up_up_Source_SmashBros_Menus_StageSelectScreen.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/luis/Code/iSSB/Source/SmashBros/Menus/StageSelectScreen.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_Source_SmashBros_Menus_StageSelectScreen.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_Source_SmashBros_Menus_StageSelectScreen.cpp$(DependSuffix): ../../Source/SmashBros/Menus/StageSelectScreen.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_Source_SmashBros_Menus_StageSelectScreen.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_Source_SmashBros_Menus_StageSelectScreen.cpp$(DependSuffix) -MM ../../Source/SmashBros/Menus/StageSelectScreen.cpp

$(IntermediateDirectory)/up_up_Source_SmashBros_Menus_StageSelectScreen.cpp$(PreprocessSuffix): ../../Source/SmashBros/Menus/StageSelectScreen.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_Source_SmashBros_Menus_StageSelectScreen.cpp$(PreprocessSuffix) ../../Source/SmashBros/Menus/StageSelectScreen.cpp

$(IntermediateDirectory)/up_up_Source_Program.cpp$(ObjectSuffix): ../../Source/Program.cpp $(IntermediateDirectory)/up_up_Source_Program.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/luis/Code/iSSB/Source/Program.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_Source_Program.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_Source_Program.cpp$(DependSuffix): ../../Source/Program.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_Source_Program.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_Source_Program.cpp$(DependSuffix) -MM ../../Source/Program.cpp

$(IntermediateDirectory)/up_up_Source_Program.cpp$(PreprocessSuffix): ../../Source/Program.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_Source_Program.cpp$(PreprocessSuffix) ../../Source/Program.cpp

$(IntermediateDirectory)/up_up_Source_SmashBros_ProjectileManager.cpp$(ObjectSuffix): ../../Source/SmashBros/ProjectileManager.cpp $(IntermediateDirectory)/up_up_Source_SmashBros_ProjectileManager.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/luis/Code/iSSB/Source/SmashBros/ProjectileManager.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_Source_SmashBros_ProjectileManager.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_Source_SmashBros_ProjectileManager.cpp$(DependSuffix): ../../Source/SmashBros/ProjectileManager.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_Source_SmashBros_ProjectileManager.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_Source_SmashBros_ProjectileManager.cpp$(DependSuffix) -MM ../../Source/SmashBros/ProjectileManager.cpp

$(IntermediateDirectory)/up_up_Source_SmashBros_ProjectileManager.cpp$(PreprocessSuffix): ../../Source/SmashBros/ProjectileManager.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_Source_SmashBros_ProjectileManager.cpp$(PreprocessSuffix) ../../Source/SmashBros/ProjectileManager.cpp

$(IntermediateDirectory)/up_up_Source_ScriptModule_modules_GameEngine_inherit_lib_ge_inherit_MenuScreen.cpp$(ObjectSuffix): ../../Source/ScriptModule/modules/GameEngine/inherit/lib_ge_inherit_MenuScreen.cpp $(IntermediateDirectory)/up_up_Source_ScriptModule_modules_GameEngine_inherit_lib_ge_inherit_MenuScreen.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/luis/Code/iSSB/Source/ScriptModule/modules/GameEngine/inherit/lib_ge_inherit_MenuScreen.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_Source_ScriptModule_modules_GameEngine_inherit_lib_ge_inherit_MenuScreen.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_Source_ScriptModule_modules_GameEngine_inherit_lib_ge_inherit_MenuScreen.cpp$(DependSuffix): ../../Source/ScriptModule/modules/GameEngine/inherit/lib_ge_inherit_MenuScreen.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_Source_ScriptModule_modules_GameEngine_inherit_lib_ge_inherit_MenuScreen.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_Source_ScriptModule_modules_GameEngine_inherit_lib_ge_inherit_MenuScreen.cpp$(DependSuffix) -MM ../../Source/ScriptModule/modules/GameEngine/inherit/lib_ge_inherit_MenuScreen.cpp

$(IntermediateDirectory)/up_up_Source_ScriptModule_modules_GameEngine_inherit_lib_ge_inherit_MenuScreen.cpp$(PreprocessSuffix): ../../Source/ScriptModule/modules/GameEngine/inherit/lib_ge_inherit_MenuScreen.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_Source_ScriptModule_modules_GameEngine_inherit_lib_ge_inherit_MenuScreen.cpp$(PreprocessSuffix) ../../Source/ScriptModule/modules/GameEngine/inherit/lib_ge_inherit_MenuScreen.cpp

$(IntermediateDirectory)/up_up_Source_SmashBros_Game_Stages_HyruleTemple.cpp$(ObjectSuffix): ../../Source/SmashBros/Game/Stages/HyruleTemple.cpp $(IntermediateDirectory)/up_up_Source_SmashBros_Game_Stages_HyruleTemple.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/luis/Code/iSSB/Source/SmashBros/Game/Stages/HyruleTemple.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_Source_SmashBros_Game_Stages_HyruleTemple.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_Source_SmashBros_Game_Stages_HyruleTemple.cpp$(DependSuffix): ../../Source/SmashBros/Game/Stages/HyruleTemple.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_Source_SmashBros_Game_Stages_HyruleTemple.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_Source_SmashBros_Game_Stages_HyruleTemple.cpp$(DependSuffix) -MM ../../Source/SmashBros/Game/Stages/HyruleTemple.cpp

$(IntermediateDirectory)/up_up_Source_SmashBros_Game_Stages_HyruleTemple.cpp$(PreprocessSuffix): ../../Source/SmashBros/Game/Stages/HyruleTemple.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_Source_SmashBros_Game_Stages_HyruleTemple.cpp$(PreprocessSuffix) ../../Source/SmashBros/Game/Stages/HyruleTemple.cpp

$(IntermediateDirectory)/up_up_Source_SmashBros_Menus_CharSelectScreen.cpp$(ObjectSuffix): ../../Source/SmashBros/Menus/CharSelectScreen.cpp $(IntermediateDirectory)/up_up_Source_SmashBros_Menus_CharSelectScreen.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/luis/Code/iSSB/Source/SmashBros/Menus/CharSelectScreen.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_Source_SmashBros_Menus_CharSelectScreen.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_Source_SmashBros_Menus_CharSelectScreen.cpp$(DependSuffix): ../../Source/SmashBros/Menus/CharSelectScreen.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_Source_SmashBros_Menus_CharSelectScreen.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_Source_SmashBros_Menus_CharSelectScreen.cpp$(DependSuffix) -MM ../../Source/SmashBros/Menus/CharSelectScreen.cpp

$(IntermediateDirectory)/up_up_Source_SmashBros_Menus_CharSelectScreen.cpp$(PreprocessSuffix): ../../Source/SmashBros/Menus/CharSelectScreen.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_Source_SmashBros_Menus_CharSelectScreen.cpp$(PreprocessSuffix) ../../Source/SmashBros/Menus/CharSelectScreen.cpp

$(IntermediateDirectory)/up_up_Source_GameEngine_View.cpp$(ObjectSuffix): ../../Source/GameEngine/View.cpp $(IntermediateDirectory)/up_up_Source_GameEngine_View.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/luis/Code/iSSB/Source/GameEngine/View.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_Source_GameEngine_View.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_Source_GameEngine_View.cpp$(DependSuffix): ../../Source/GameEngine/View.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_Source_GameEngine_View.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_Source_GameEngine_View.cpp$(DependSuffix) -MM ../../Source/GameEngine/View.cpp

$(IntermediateDirectory)/up_up_Source_GameEngine_View.cpp$(PreprocessSuffix): ../../Source/GameEngine/View.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_Source_GameEngine_View.cpp$(PreprocessSuffix) ../../Source/GameEngine/View.cpp

$(IntermediateDirectory)/up_up_Source_GameEngine_Util_Thread.cpp$(ObjectSuffix): ../../Source/GameEngine/Util/Thread.cpp $(IntermediateDirectory)/up_up_Source_GameEngine_Util_Thread.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/luis/Code/iSSB/Source/GameEngine/Util/Thread.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_Source_GameEngine_Util_Thread.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_Source_GameEngine_Util_Thread.cpp$(DependSuffix): ../../Source/GameEngine/Util/Thread.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_Source_GameEngine_Util_Thread.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_Source_GameEngine_Util_Thread.cpp$(DependSuffix) -MM ../../Source/GameEngine/Util/Thread.cpp

$(IntermediateDirectory)/up_up_Source_GameEngine_Util_Thread.cpp$(PreprocessSuffix): ../../Source/GameEngine/Util/Thread.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_Source_GameEngine_Util_Thread.cpp$(PreprocessSuffix) ../../Source/GameEngine/Util/Thread.cpp

$(IntermediateDirectory)/up_up_Source_GameEngine_Util_PixelIterator.cpp$(ObjectSuffix): ../../Source/GameEngine/Util/PixelIterator.cpp $(IntermediateDirectory)/up_up_Source_GameEngine_Util_PixelIterator.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/luis/Code/iSSB/Source/GameEngine/Util/PixelIterator.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_Source_GameEngine_Util_PixelIterator.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_Source_GameEngine_Util_PixelIterator.cpp$(DependSuffix): ../../Source/GameEngine/Util/PixelIterator.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_Source_GameEngine_Util_PixelIterator.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_Source_GameEngine_Util_PixelIterator.cpp$(DependSuffix) -MM ../../Source/GameEngine/Util/PixelIterator.cpp

$(IntermediateDirectory)/up_up_Source_GameEngine_Util_PixelIterator.cpp$(PreprocessSuffix): ../../Source/GameEngine/Util/PixelIterator.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_Source_GameEngine_Util_PixelIterator.cpp$(PreprocessSuffix) ../../Source/GameEngine/Util/PixelIterator.cpp

$(IntermediateDirectory)/up_up_Source_GameEngine_Util_HapticFeedbackiOS.mm$(ObjectSuffix): ../../Source/GameEngine/Util/HapticFeedbackiOS.mm $(IntermediateDirectory)/up_up_Source_GameEngine_Util_HapticFeedbackiOS.mm$(DependSuffix)
	$(CXX) $(IncludePCH) -x objective-c++ $(SourceSwitch) "/home/luis/Code/iSSB/Source/GameEngine/Util/HapticFeedbackiOS.mm" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_Source_GameEngine_Util_HapticFeedbackiOS.mm$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_Source_GameEngine_Util_HapticFeedbackiOS.mm$(DependSuffix): ../../Source/GameEngine/Util/HapticFeedbackiOS.mm
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_Source_GameEngine_Util_HapticFeedbackiOS.mm$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_Source_GameEngine_Util_HapticFeedbackiOS.mm$(DependSuffix) -MM ../../Source/GameEngine/Util/HapticFeedbackiOS.mm

$(IntermediateDirectory)/up_up_Source_GameEngine_Util_HapticFeedbackiOS.mm$(PreprocessSuffix): ../../Source/GameEngine/Util/HapticFeedbackiOS.mm
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_Source_GameEngine_Util_HapticFeedbackiOS.mm$(PreprocessSuffix) ../../Source/GameEngine/Util/HapticFeedbackiOS.mm

$(IntermediateDirectory)/up_up_Source_GameEngine_Sound_Music.cpp$(ObjectSuffix): ../../Source/GameEngine/Sound/Music.cpp $(IntermediateDirectory)/up_up_Source_GameEngine_Sound_Music.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/luis/Code/iSSB/Source/GameEngine/Sound/Music.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_Source_GameEngine_Sound_Music.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_Source_GameEngine_Sound_Music.cpp$(DependSuffix): ../../Source/GameEngine/Sound/Music.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_Source_GameEngine_Sound_Music.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_Source_GameEngine_Sound_Music.cpp$(DependSuffix) -MM ../../Source/GameEngine/Sound/Music.cpp

$(IntermediateDirectory)/up_up_Source_GameEngine_Sound_Music.cpp$(PreprocessSuffix): ../../Source/GameEngine/Sound/Music.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_Source_GameEngine_Sound_Music.cpp$(PreprocessSuffix) ../../Source/GameEngine/Sound/Music.cpp

$(IntermediateDirectory)/up_up_Source_GameEngine_Util_String.cpp$(ObjectSuffix): ../../Source/GameEngine/Util/String.cpp $(IntermediateDirectory)/up_up_Source_GameEngine_Util_String.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/luis/Code/iSSB/Source/GameEngine/Util/String.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_Source_GameEngine_Util_String.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_Source_GameEngine_Util_String.cpp$(DependSuffix): ../../Source/GameEngine/Util/String.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_Source_GameEngine_Util_String.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_Source_GameEngine_Util_String.cpp$(DependSuffix) -MM ../../Source/GameEngine/Util/String.cpp

$(IntermediateDirectory)/up_up_Source_GameEngine_Util_String.cpp$(PreprocessSuffix): ../../Source/GameEngine/Util/String.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_Source_GameEngine_Util_String.cpp$(PreprocessSuffix) ../../Source/GameEngine/Util/String.cpp

$(IntermediateDirectory)/up_up_Source_GameEngine_Util_Bitset.cpp$(ObjectSuffix): ../../Source/GameEngine/Util/Bitset.cpp $(IntermediateDirectory)/up_up_Source_GameEngine_Util_Bitset.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/luis/Code/iSSB/Source/GameEngine/Util/Bitset.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_Source_GameEngine_Util_Bitset.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_Source_GameEngine_Util_Bitset.cpp$(DependSuffix): ../../Source/GameEngine/Util/Bitset.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_Source_GameEngine_Util_Bitset.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_Source_GameEngine_Util_Bitset.cpp$(DependSuffix) -MM ../../Source/GameEngine/Util/Bitset.cpp

$(IntermediateDirectory)/up_up_Source_GameEngine_Util_Bitset.cpp$(PreprocessSuffix): ../../Source/GameEngine/Util/Bitset.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_Source_GameEngine_Util_Bitset.cpp$(PreprocessSuffix) ../../Source/GameEngine/Util/Bitset.cpp

$(IntermediateDirectory)/up_up_Source_GameEngine_Util_Color.cpp$(ObjectSuffix): ../../Source/GameEngine/Util/Color.cpp $(IntermediateDirectory)/up_up_Source_GameEngine_Util_Color.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/luis/Code/iSSB/Source/GameEngine/Util/Color.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_Source_GameEngine_Util_Color.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_Source_GameEngine_Util_Color.cpp$(DependSuffix): ../../Source/GameEngine/Util/Color.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_Source_GameEngine_Util_Color.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_Source_GameEngine_Util_Color.cpp$(DependSuffix) -MM ../../Source/GameEngine/Util/Color.cpp

$(IntermediateDirectory)/up_up_Source_GameEngine_Util_Color.cpp$(PreprocessSuffix): ../../Source/GameEngine/Util/Color.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_Source_GameEngine_Util_Color.cpp$(PreprocessSuffix) ../../Source/GameEngine/Util/Color.cpp

$(IntermediateDirectory)/up_up_Source_GameEngine_Actor_TextActor.cpp$(ObjectSuffix): ../../Source/GameEngine/Actor/TextActor.cpp $(IntermediateDirectory)/up_up_Source_GameEngine_Actor_TextActor.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/luis/Code/iSSB/Source/GameEngine/Actor/TextActor.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_Source_GameEngine_Actor_TextActor.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_Source_GameEngine_Actor_TextActor.cpp$(DependSuffix): ../../Source/GameEngine/Actor/TextActor.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_Source_GameEngine_Actor_TextActor.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_Source_GameEngine_Actor_TextActor.cpp$(DependSuffix) -MM ../../Source/GameEngine/Actor/TextActor.cpp

$(IntermediateDirectory)/up_up_Source_GameEngine_Actor_TextActor.cpp$(PreprocessSuffix): ../../Source/GameEngine/Actor/TextActor.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_Source_GameEngine_Actor_TextActor.cpp$(PreprocessSuffix) ../../Source/GameEngine/Actor/TextActor.cpp

$(IntermediateDirectory)/up_up_Source_SmashBros_Item.cpp$(ObjectSuffix): ../../Source/SmashBros/Item.cpp $(IntermediateDirectory)/up_up_Source_SmashBros_Item.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/luis/Code/iSSB/Source/SmashBros/Item.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_Source_SmashBros_Item.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_Source_SmashBros_Item.cpp$(DependSuffix): ../../Source/SmashBros/Item.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_Source_SmashBros_Item.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_Source_SmashBros_Item.cpp$(DependSuffix) -MM ../../Source/SmashBros/Item.cpp

$(IntermediateDirectory)/up_up_Source_SmashBros_Item.cpp$(PreprocessSuffix): ../../Source/SmashBros/Item.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_Source_SmashBros_Item.cpp$(PreprocessSuffix) ../../Source/SmashBros/Item.cpp

$(IntermediateDirectory)/up_up_Source_GameEngine_ScreenManager_Screen.cpp$(ObjectSuffix): ../../Source/GameEngine/ScreenManager/Screen.cpp $(IntermediateDirectory)/up_up_Source_GameEngine_ScreenManager_Screen.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/luis/Code/iSSB/Source/GameEngine/ScreenManager/Screen.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_Source_GameEngine_ScreenManager_Screen.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_Source_GameEngine_ScreenManager_Screen.cpp$(DependSuffix): ../../Source/GameEngine/ScreenManager/Screen.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_Source_GameEngine_ScreenManager_Screen.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_Source_GameEngine_ScreenManager_Screen.cpp$(DependSuffix) -MM ../../Source/GameEngine/ScreenManager/Screen.cpp

$(IntermediateDirectory)/up_up_Source_GameEngine_ScreenManager_Screen.cpp$(PreprocessSuffix): ../../Source/GameEngine/ScreenManager/Screen.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_Source_GameEngine_ScreenManager_Screen.cpp$(PreprocessSuffix) ../../Source/GameEngine/ScreenManager/Screen.cpp

$(IntermediateDirectory)/up_up_Source_GameEngine_Actor_PrimitiveActor.cpp$(ObjectSuffix): ../../Source/GameEngine/Actor/PrimitiveActor.cpp $(IntermediateDirectory)/up_up_Source_GameEngine_Actor_PrimitiveActor.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/luis/Code/iSSB/Source/GameEngine/Actor/PrimitiveActor.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_Source_GameEngine_Actor_PrimitiveActor.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_Source_GameEngine_Actor_PrimitiveActor.cpp$(DependSuffix): ../../Source/GameEngine/Actor/PrimitiveActor.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_Source_GameEngine_Actor_PrimitiveActor.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_Source_GameEngine_Actor_PrimitiveActor.cpp$(DependSuffix) -MM ../../Source/GameEngine/Actor/PrimitiveActor.cpp

$(IntermediateDirectory)/up_up_Source_GameEngine_Actor_PrimitiveActor.cpp$(PreprocessSuffix): ../../Source/GameEngine/Actor/PrimitiveActor.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_Source_GameEngine_Actor_PrimitiveActor.cpp$(PreprocessSuffix) ../../Source/GameEngine/Actor/PrimitiveActor.cpp

$(IntermediateDirectory)/up_up_Source_GameEngine_Sound_Sound.cpp$(ObjectSuffix): ../../Source/GameEngine/Sound/Sound.cpp $(IntermediateDirectory)/up_up_Source_GameEngine_Sound_Sound.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/luis/Code/iSSB/Source/GameEngine/Sound/Sound.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_Source_GameEngine_Sound_Sound.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_Source_GameEngine_Sound_Sound.cpp$(DependSuffix): ../../Source/GameEngine/Sound/Sound.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_Source_GameEngine_Sound_Sound.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_Source_GameEngine_Sound_Sound.cpp$(DependSuffix) -MM ../../Source/GameEngine/Sound/Sound.cpp

$(IntermediateDirectory)/up_up_Source_GameEngine_Sound_Sound.cpp$(PreprocessSuffix): ../../Source/GameEngine/Sound/Sound.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_Source_GameEngine_Sound_Sound.cpp$(PreprocessSuffix) ../../Source/GameEngine/Sound/Sound.cpp

$(IntermediateDirectory)/up_up_Source_GameEngine_ScreenManager_ScreenManager.cpp$(ObjectSuffix): ../../Source/GameEngine/ScreenManager/ScreenManager.cpp $(IntermediateDirectory)/up_up_Source_GameEngine_ScreenManager_ScreenManager.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/luis/Code/iSSB/Source/GameEngine/ScreenManager/ScreenManager.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_Source_GameEngine_ScreenManager_ScreenManager.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_Source_GameEngine_ScreenManager_ScreenManager.cpp$(DependSuffix): ../../Source/GameEngine/ScreenManager/ScreenManager.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_Source_GameEngine_ScreenManager_ScreenManager.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_Source_GameEngine_ScreenManager_ScreenManager.cpp$(DependSuffix) -MM ../../Source/GameEngine/ScreenManager/ScreenManager.cpp

$(IntermediateDirectory)/up_up_Source_GameEngine_ScreenManager_ScreenManager.cpp$(PreprocessSuffix): ../../Source/GameEngine/ScreenManager/ScreenManager.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_Source_GameEngine_ScreenManager_ScreenManager.cpp$(PreprocessSuffix) ../../Source/GameEngine/ScreenManager/ScreenManager.cpp

$(IntermediateDirectory)/up_up_Source_SmashBros_Game_Items_HeartContainer.cpp$(ObjectSuffix): ../../Source/SmashBros/Game/Items/HeartContainer.cpp $(IntermediateDirectory)/up_up_Source_SmashBros_Game_Items_HeartContainer.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/luis/Code/iSSB/Source/SmashBros/Game/Items/HeartContainer.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_Source_SmashBros_Game_Items_HeartContainer.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_Source_SmashBros_Game_Items_HeartContainer.cpp$(DependSuffix): ../../Source/SmashBros/Game/Items/HeartContainer.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_Source_SmashBros_Game_Items_HeartContainer.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_Source_SmashBros_Game_Items_HeartContainer.cpp$(DependSuffix) -MM ../../Source/SmashBros/Game/Items/HeartContainer.cpp

$(IntermediateDirectory)/up_up_Source_SmashBros_Game_Items_HeartContainer.cpp$(PreprocessSuffix): ../../Source/SmashBros/Game/Items/HeartContainer.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_Source_SmashBros_Game_Items_HeartContainer.cpp$(PreprocessSuffix) ../../Source/SmashBros/Game/Items/HeartContainer.cpp

$(IntermediateDirectory)/up_up_Source_GameEngine_Output_Console.cpp$(ObjectSuffix): ../../Source/GameEngine/Output/Console.cpp $(IntermediateDirectory)/up_up_Source_GameEngine_Output_Console.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/luis/Code/iSSB/Source/GameEngine/Output/Console.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_Source_GameEngine_Output_Console.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_Source_GameEngine_Output_Console.cpp$(DependSuffix): ../../Source/GameEngine/Output/Console.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_Source_GameEngine_Output_Console.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_Source_GameEngine_Output_Console.cpp$(DependSuffix) -MM ../../Source/GameEngine/Output/Console.cpp

$(IntermediateDirectory)/up_up_Source_GameEngine_Output_Console.cpp$(PreprocessSuffix): ../../Source/GameEngine/Output/Console.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_Source_GameEngine_Output_Console.cpp$(PreprocessSuffix) ../../Source/GameEngine/Output/Console.cpp

$(IntermediateDirectory)/up_up_Source_SmashBros_Menus_MenuClasses.cpp$(ObjectSuffix): ../../Source/SmashBros/Menus/MenuClasses.cpp $(IntermediateDirectory)/up_up_Source_SmashBros_Menus_MenuClasses.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/luis/Code/iSSB/Source/SmashBros/Menus/MenuClasses.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_Source_SmashBros_Menus_MenuClasses.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_Source_SmashBros_Menus_MenuClasses.cpp$(DependSuffix): ../../Source/SmashBros/Menus/MenuClasses.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_Source_SmashBros_Menus_MenuClasses.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_Source_SmashBros_Menus_MenuClasses.cpp$(DependSuffix) -MM ../../Source/SmashBros/Menus/MenuClasses.cpp

$(IntermediateDirectory)/up_up_Source_SmashBros_Menus_MenuClasses.cpp$(PreprocessSuffix): ../../Source/SmashBros/Menus/MenuClasses.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_Source_SmashBros_Menus_MenuClasses.cpp$(PreprocessSuffix) ../../Source/SmashBros/Menus/MenuClasses.cpp

$(IntermediateDirectory)/up_up_Source_GameEngine_Util_BufferedImage.cpp$(ObjectSuffix): ../../Source/GameEngine/Util/BufferedImage.cpp $(IntermediateDirectory)/up_up_Source_GameEngine_Util_BufferedImage.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/luis/Code/iSSB/Source/GameEngine/Util/BufferedImage.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_Source_GameEngine_Util_BufferedImage.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_Source_GameEngine_Util_BufferedImage.cpp$(DependSuffix): ../../Source/GameEngine/Util/BufferedImage.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_Source_GameEngine_Util_BufferedImage.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_Source_GameEngine_Util_BufferedImage.cpp$(DependSuffix) -MM ../../Source/GameEngine/Util/BufferedImage.cpp

$(IntermediateDirectory)/up_up_Source_GameEngine_Util_BufferedImage.cpp$(PreprocessSuffix): ../../Source/GameEngine/Util/BufferedImage.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_Source_GameEngine_Util_BufferedImage.cpp$(PreprocessSuffix) ../../Source/GameEngine/Util/BufferedImage.cpp

$(IntermediateDirectory)/up_up_Source_SmashBros_AttackManager.cpp$(ObjectSuffix): ../../Source/SmashBros/AttackManager.cpp $(IntermediateDirectory)/up_up_Source_SmashBros_AttackManager.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/luis/Code/iSSB/Source/SmashBros/AttackManager.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_Source_SmashBros_AttackManager.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_Source_SmashBros_AttackManager.cpp$(DependSuffix): ../../Source/SmashBros/AttackManager.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_Source_SmashBros_AttackManager.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_Source_SmashBros_AttackManager.cpp$(DependSuffix) -MM ../../Source/SmashBros/AttackManager.cpp

$(IntermediateDirectory)/up_up_Source_SmashBros_AttackManager.cpp$(PreprocessSuffix): ../../Source/SmashBros/AttackManager.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_Source_SmashBros_AttackManager.cpp$(PreprocessSuffix) ../../Source/SmashBros/AttackManager.cpp

$(IntermediateDirectory)/up_up_Source_GameEngine_Input_Keys.cpp$(ObjectSuffix): ../../Source/GameEngine/Input/Keys.cpp $(IntermediateDirectory)/up_up_Source_GameEngine_Input_Keys.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/luis/Code/iSSB/Source/GameEngine/Input/Keys.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_Source_GameEngine_Input_Keys.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_Source_GameEngine_Input_Keys.cpp$(DependSuffix): ../../Source/GameEngine/Input/Keys.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_Source_GameEngine_Input_Keys.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_Source_GameEngine_Input_Keys.cpp$(DependSuffix) -MM ../../Source/GameEngine/Input/Keys.cpp

$(IntermediateDirectory)/up_up_Source_GameEngine_Input_Keys.cpp$(PreprocessSuffix): ../../Source/GameEngine/Input/Keys.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_Source_GameEngine_Input_Keys.cpp$(PreprocessSuffix) ../../Source/GameEngine/Input/Keys.cpp


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/


