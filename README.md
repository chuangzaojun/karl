# The Karl Programming Language

## 全世界无产者，联合起来！

![](/logo.png)

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
i = 0; // this is a comment
s = 0;
while i <= 10 {
    i = i + 1;
    s = s + i;
}
s;
```

输出：`66`

若要使用 Karl，可将使用命令行运行解释器，如使用 Windows x86-64 PowerShell（解释器 `karl-x86-64.exe` 和文件 `a.karl` 均在 PowerShell 目录下）：

```
PS ...> .\karl-x86-64.exe a.karl
```

使用其他操作系统请自行编译。
