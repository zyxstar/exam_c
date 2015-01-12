学生管理系统：（链表）
=======================
1. 能够管理一个学校的学生
1. 学校的年届可以增加和删除
1. 每一年级的班级可以增加和删除
1. 每个班级的学生也可以增加和删除
1. 对班级的学生可以根据学号和姓名进行查找
1. 对班级的学生分数具有排序功能
1. 对同一年级的学生具有按成绩排序的功能
1. 要求使用有头双向循环链表完成
1. 能够把年级，班级，学生存储到文件中，下次打开系统可以直接载入文件。
1. 每次修改都必须对文件进行保存

实现说明
=======================
- 本项目使用内核链表来实现
- `STUDENT`只有一个`struct list_head`，用于编成链，`CLASS`，`GRADE`均有两个`struct list_head`，一个表示下级的链表，另一个用于自身编成链
- 用 __宏__(`../utils/kernel_list_helper.h`) 封装了内核链表在 `each`、`find`、`save`、`load`方面的通用实现(因为如果用函数封装，不能模拟泛型的要求)

> 使用如下，第一行是声明，第二行是实现，将来宏会被展开

```c
// declare
void class_each_student(CLASS *, void *env, void(*each_do)(STUDENT *, int idx, void *env));
// implement
_implement_list_each(class_each_student, CLASS, student_list, STUDENT, node);
```

- 排序功能使用了标准库的`qsort()`，返回的是一个指向`STUDENT *`的数组，相当于一个视图，并未真正改变他们在各自班级中的顺序，盖因为排序的依据是可变的，以这种视图的方式呈现可能更好些

- 简单的实现了一个事件机制(位于`../utils/event.h`，内部的事件列表也是使用内核链表实现的)，`CLASS`中`STUDENT`的增删能够被`GRADE`所监听，后者可据此做一些事情（如增减学生的计数）
