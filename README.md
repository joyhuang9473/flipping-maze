![hackathon-game-framework@460](http://imgur.com/GGDApDN.png)

Hackathon-Game-Framework
=========

|  |iOS|Mac|Linux|Win32|Android|Win8.1-Universal|
| ----|----|----- | ---|----|------|---|
|v3|passing|passing|none|none|none|none|

Hackathon-Game-Framework is a quick development framework for developing game application. It is based on [Cocos2d-x](http://www.cocos2d-x.org/).

Through its simple directory architecture, developers can quickly relocation codes and resource files to Hackathon-Game-Framework. Besides, there are some ready-made tools, such as Role Entity, FSM, RobotController, CSVParser, etc.

In short, Hackathon-Game-Framework would be useful for running hackathon contest and developing prototypes.

Directory Architecture
-----------------------

We focus on `Classes` and `Resources` directory.

In `Classes` directory:

- `Controller`: used for controlling entity. It can usually be the controller of keyboard, touch, joystick, robot, etc.

- `Entity`: used for storing entity classes and related FSM, such as role, player, item, etc.

- `Layer`: used for rendering main ui and executing game logic.

- `Scene`: used for arranging layer's orders.

- `Util`: providing some useful tools, such as CSVParser, the AnimationUtil.

In `Resources` directory:

- `Audio`: storing background musics and effects.

- `Button`: storing button images.

- `Character`: storing `Entity`'s images and plist files.

- `Font`: storing fonts.

- `Map`: storing background images and tilemaps.

- `Other`: storing temporary files or unclassified files.

- `Setting`: storing initial map, entity, stage settings.

Role & FSM
-----------------------

Role has `Animation`, `BoundingBox`, `Controller`, `FSM` attributes ready to set.

### Bind Animation ###

    std::string spName = "myRole";

    Animation* moveAnim = AnimationUtil::createAnimWithFrameName(StringUtils::format("%s-move", spName.c_str()).c_str());
    Animation* attackAnim = AnimationUtil::createAnimWithFrameName(StringUtils::format("%s-attack", spName.c_str()).c_str());

    role->setMoveAction(moveAnim);
    role->setAttackAction(attackAnim);

### Bind BoundingBox ###

    role->m_bodyBox = this->createBoundingBox(
        Point(-spriteSize.width/2, -spriteSize.height/2),
        Size(spriteSize.width, spriteSize.height)
    );

### Bind Controller ###

    RobotController* robotController = RobotController::create();
    RobotController->setRole(role);

    role->setController(robotController);
    role->addChild(robotController);

### Set FSM ###

In Role class:

    /*
    * State
    */
    this->m_fsm->addState("walking");

    /*
    * Enter function
    */
    auto onWalking = [this]() {
        auto animate = Animate::create(this->m_moveAction);
        auto repeat = RepeatForever::create(animate);
        repeat->setTag(AnimationType::WALKING);
        this->m_sprite->runAction(repeat);
    };
    this->m_fsm->setOnEnter("walking", onWalking);

    /*
    * Event
    */
    this->m_fsm->addEvent("walk", "idle", "walking")

GameManager
-----------------------

GameManager is responsible for adding resource pathes to the game application, and it stores the game's progress or essential datas, which will be updated as the game developes.

Installation
-----------------------

1. Install [Cocos2d-x](http://www.cocos2d-x.org/)
2. Create a new cocos2d-x project and move `cocos2d` directory to this framework's root directory

Build and run
-----------------------

Just like what we do in cocos2d-x project!

for ios:

    $ cocos run -p ios

for mac:

    $ cocos run -p mac

Reference
-----------------------

[1]. Cocos2d-x, "[Cocos2d-x Programmers Guide v3.9](http://www.cocos2d-x.org/programmersguide/)", 2015.

[2]. 鍾迪龍, "[Cocos2d-x 遊戲開發之旅](http://product.dangdang.com/23321791.html#catalog)", 電子工業出版社, 2013.

[3]. douxt, "[Cocos2dx 3.2 横版过关游戏Brave学习笔记](http://www.tairan.com/archives/8344/)", 泰然網, 2014.

Credit
-----------------------

Character Graphics Credit: [creek23](http://opengameart.org/users/creek23)
