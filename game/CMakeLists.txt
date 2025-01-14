cmake_minimum_required(VERSION 3.28)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
set(CMAKE_BUILD_TYPE Release)
project(game C CXX)

add_subdirectory(../src crepe)

add_executable(main)

target_sources(main PUBLIC
	# enemy
	enemy/BattleScript.cpp
	enemy/EnemyPool.cpp
	enemy/EnemyBulletScript.cpp
	enemy/EnemyBulletSubScene.cpp
	enemy/EnemyBulletPool.cpp
	enemy/EnemySubScene.cpp
	enemy/EnemyScript.cpp

	#background
	background/AquariumSubScene.cpp
	background/AquariumScript.cpp
	background/BackgroundSubScene.cpp
	background/ForestParallaxScript.cpp
	background/ForestSubScene.cpp
	background/HallwaySubScene.cpp
	background/StartSubScene.cpp
	background/HallwayScript.cpp

	# mainscenes
	GameScene.cpp
	menus/shop/ShopMenuScene.cpp
	menus/shop/ShopLoadScript.cpp
	menus/shop/ButtonBuySelectBubbleScript.cpp
	menus/shop/ButtonBuySelectBulletScript.cpp
	menus/mainmenu/MainMenuScene.cpp
	PreviewScene.cpp
	main.cpp

	# missile
	missile/MissilePool.cpp
	missile/MissileScript.cpp
	missile/MissileSubScene.cpp
	missile/AlertSubScene.cpp
	missile/AlertScript.cpp
	missile/SpawnEvent.cpp

	#scheduling
	scheduler/ObjectsScheduler.cpp

	# Preview
	preview/SmokeSubScene.cpp
	preview/NpcSubScene.cpp
	preview/NpcScript.cpp
	preview/PrevPlayerSubScene.cpp
	preview/PrevPlayerScript.cpp
	preview/PreviewStopRecSubScript.cpp
	preview/PreviewStartRecSubScript.cpp
	preview/PreviewReplaySubScript.cpp

	# scripts
	GameScene.cpp
	MoveCameraManualyScript.cpp
	StartGameScript.cpp
	QuitScript.cpp

	# player
	player/PlayerScript.cpp
	player/PlayerSubScene.cpp
	player/PlayerBulletPool.cpp
	player/PlayerBulletScript.cpp
	player/PlayerBulletSubScene.cpp
	player/PlayerEndScript.cpp
	player/PlayerAudioScript.cpp

	# workers
	workers/WorkersSubScene.cpp
	workers/WorkerScript.cpp
	workers/PanicFromPlayerScript.cpp
	workers/CollisionScript.cpp

	# menus
	menus/BannerSubScene.cpp
	menus/ButtonSubScene.cpp
	menus/IButtonScript.cpp
	menus/ButtonSetShopSubScript.cpp
	menus/ButtonSetMainMenuSubScript.cpp
	menus/ButtonReplaySubScript.cpp
	menus/ButtonNextMainMenuSubScript.cpp
	menus/FloatingWindowSubScene.cpp
	menus/IFloatingWindowScript.cpp
	menus/ButtonShowCreditsSubScript.cpp
	menus/mainmenu/ButtonTransitionPreviewSubScript.cpp
	menus/mainmenu/ITransitionScript.cpp
	menus/mainmenu/TransitionStartSubScript.cpp
	menus/mainmenu/CreditsSubScene.cpp
	menus/mainmenu/CreditsSubScript.cpp
	menus/endgame/EndGameSubScene.cpp
	menus/endgame/EndGameSubScript.cpp

	# coins
	coins/CoinSubScene.cpp
	coins/CoinPoolSubScene.cpp
	coins/CoinSystemScript.cpp
	coins/CoinScript.cpp

	# hud
	hud/HudSubScene.cpp
	hud/HudScript.cpp
	hud/SpeedScript.cpp

	#random
	Random.cpp
)

add_subdirectory(background)
add_subdirectory(prefab)

target_link_libraries(main PUBLIC crepe)
target_include_directories(main PRIVATE .)

