## json字符串格式化整理

* 1. 支持过滤原有格式,格式化不会重叠(例如原来有换行的,格式化后不会变成2次换行)

* 2. 支持指定缩进空格数

* 3. 过滤非字符串内的不可见字符

* 4. 没有进行格式错误检查,需自行注意

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
