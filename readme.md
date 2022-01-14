## json字符串格式化整理

* 1. 支持过滤原有格式,格式化不会重叠(例如原来有换行的,格式化后不会变成2次换行)

* 2. 支持指定缩进空格数

* 3. 过滤字符串外部的, 除特殊字符"{[]},:"之外, 除数字、大小写字母(即true和false,有些语言首字母大写)之外, 的所有字符

* 4. 没有进行额外格式错误检查和纠正(指括号的关闭、符号",:"的出现位置等),需自行注意

## 效果演示

* 输入
```json
{"int": 123,"string": "abc","array": [1, 2, 3],"object": {"array1": ["abc", "def", "ghi"],"array2":[{"name": "demo1","commit": "Hello world !"},{"name": "demo2","commit": "abc,efg"}],"txt":"\"\n\t这是一行带格式的文本,\n内含换行、tab和转义字符,\r\n正常格式化理应保留原有的样子\""}}
```

* 输出
```json
{
    "int": 123,
    "string": "abc",
    "array": [
        1,
        2,
        3
    ],
    "object": {
        "array1": [
            "abc",
            "def",
            "ghi"
        ],
        "array2": [
            {
                "name": "demo1",
                "commit": "Hello world !"
            },
            {
                "name": "demo2",
                "commit": "abc,efg"
            }
        ],
        "txt": "\"\n\t这是一行带格式的文本,\n内含换行、tab和转义字符,\r\n正常格式化理应保留原有的样子\""
    }
}
```
