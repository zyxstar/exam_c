

宏在本处展开，而不是调用，直接能用上下文

通过元语义来表达类型、成员，达到类似反射功能

充分表达语义，指针，类型，成员
#define container_of(ptr, type, member)

直接使用展开方式，一不利于重用，二影响语义表达


#define array(type, size) typeof(type [size])

int main(int argc, const char* argv[]){

    array(char,) charray = "hello";
    array(int, 20) intarr = {1,2,3,4};
    printf("%s\n", charray);
    (void)(charray == intarr);
    return 0;
}


找到二叉树节点前驱 某左 右指向，可以使用 ** ,而不需要重新定义一个变量


parent 方案


