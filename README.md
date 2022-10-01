# The Karl Programming Language

一门十分简陋的编程语言。

目前支持的语句有：

- 条件语句 `if`
- 循环语句 `while`
- 赋值语句
- 表达式语句

数据类型有：

- `int`
- `bool`

运算符有：

```
+ - * / % ( ) > < >= <= == !=
```

由于尚未支持函数，表达式语句讲被求值输出。

样例程序如下：

```
i = 0; # this is a comment
s = 0;
while i <= 10 {
    i = i + 1;
    s = s + i;
}
s;
```

输出：`66`