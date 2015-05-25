俄罗斯方块
==========

![Screenshot1.png](./Screenshot1.png)

![Screenshot2.png](./Screenshot2.png)

- 基础helper工具类，与具体应用无关，可重用，在`..\utils`中
    + `console.c`的实现，用于输出调试信息
    + `simple_timer.c`的实现，实现了可注册多个时间响应函数，响应函数可接受一个`void*`的数据，由于C不存在内嵌函数及闭包，必要的上下文则由该参数来保持（该上下文由创建者来指定）
    + `vt_code`，`termios`的相关封装，参考了网上的例子
- __模型层__：`BLOCK`，`GAME`的实现，它们只有逻辑部分，不包含UI交互
    + 它们可被单独测试，测试代码在`test_game.c`中
    + 它们不依赖于具体的UI技术，比如使用qt，只需能完成`GAME_UI`适配即可
    + 高层函数，即开放在`game.h`中的，抽象一致，并且所有逻辑判断不超过两层，基本达到可读性
    + 计分规则`_calc_score`、升级规则`_check_level_up`、加速规则`_speed_up`等由单独函数来完成，方便修改
    + <del>使用了`mutex`，防止在手工的与`timer`激发的`move_down`动作同时发生时，产生资源竞争，导致数据不一致</del>采用信号屏蔽，防止资源竞争
    + 如`POS *set = (POS*)(&pos_set);`，采用结构体，利用了它能被整体赋值的优势，必要时，将它再强制转换成数组，方便数据计算
    + 使用函数指针数组`void(*config_set_fn[])(POS_SET*)`，充当路由的功能，类似高级语言中的多态，避免了过多的`swich/if`
    + 原则上来说，`GAME`中不能依赖`SIMPER_TIMER`（破坏了可测性），而在控制层将两者联系到一起，达到解耦，但此处选择了相对方便的方式将两者耦合在一起了
- __视图层__：`view.c`存放具体的UI绘制的部分，它依赖于工具类中的`vt_code`
    + 它也可被单独运行，在`test_view.c`中用于测试单个绘制是否有效
- __控制层__：
    + `ctrl.c`，接收UI的交互（键盘输入），并将行为委托给模型层的具体方法。
    + 模型层发生的变化，借由`GAME_UI`来绘制UI，后者承担`GAME`与`view`之间的联系，由一系列函数指针组成的结构体，充担高级语言中的接口的概念
- 避免了全局变量的存在，方便在单人应用`tetris_single`与双人应用`tetris_double`使用同一套逻辑

> 运行时监控，`make tetris_single && ./tetris_single 2>>debug.log`，并同时启动`tail -f debug.log`
