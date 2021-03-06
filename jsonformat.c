#include <stdint.h>
#include <string.h>

static void _FormatJsonString(char* json, size_t jsonReduce, char* res, size_t resReduce,
	char** jsonRet, size_t* jsonReduceRet, char** resRet, size_t* resReduceRet)
{
	uint32_t type = 0;
	uint32_t hit = 0;
	while (jsonReduce > 0 && resReduce > 0 && hit < 2)
	{
		/* 特殊字符识别 */
		if (type == 0)
		{
			if (*json == '\\')
				type = 1;
			else
			{
				if (*json == '"')
					hit++;
				*res++ = *json++;
				jsonReduce--;
				resReduce--;
			}
		}
		/* 特殊字符处理 */
		else
		{
			switch (type)
			{
			/* 字符 "\"" 连续2步:先拷贝该字符,再拷贝下一字符 */
			case 1:
				*res++ = *json++;
				jsonReduce--;
				resReduce--;
				type = 11;
				continue;
			case 11:
				*res++ = *json++;
				jsonReduce--;
				resReduce--;
				type = 11;
				break;
			}
			type = 0;
		}
	}
	/* 返回 */
	if (jsonRet)
		*jsonRet = json;
	if (jsonReduceRet)
		*jsonReduceRet = jsonReduce;
	if (resRet)
		*resRet = res;
	if (resReduceRet)
		*resReduceRet = resReduce;
}

static void _FormatJson(char* json, size_t jsonReduce, char* res, size_t resReduce, uint32_t tab,
	char** jsonRet, size_t* jsonReduceRet, char** resRet, size_t* resReduceRet, uint32_t* tabRet,
	uint32_t indentSpace)
{
	uint32_t type = 9;
	uint32_t padding = tab * indentSpace;
	while (jsonReduce > 0 && resReduce > 0)
	{
		/* 特殊字符识别 */
		if (type == 0)
		{
			if (*json == '{' || *json == '[')
				type = 1;
			else if (*json == '}' || *json == ']')
				type = 2;
			else if (*json == ':')
				type = 3;
			else if (*json == ',')
				type = 4;
			else if (*json == '"')
				type = 5;
			/* 除以上特殊字符,在字符串之外,只拷贝数字和字母 */
			/* 因为只剩下数字、true和false(有些语言里首字母大写) */
			else if ((*json >= '0' &&  *json <= '9') ||
				(*json >= 'A' &&  *json <= 'Z') ||
				(*json >= 'a' &&  *json <= 'z') ||
				*json == '-')
			{
				*res++ = *json++;
				resReduce--;
				jsonReduce--;
			}
			else
			{
				json++;
				jsonReduce--;
			}
		}
		/* 特殊字符处理 */
		else
		{
			switch (type)
			{
			/* 字符 "{[" 连续2步:先拷贝,再换行 */
			case 1:
				*res++ = *json++;
				jsonReduce--;
				resReduce--;
				type = 11;
				continue;
			case 11:
				*res++ = '\n';
				resReduce--;
				tab++;
				_FormatJson(json, jsonReduce, res, resReduce, tab, &json, &jsonReduce, &res, &resReduce, &tab, indentSpace);
				break;
			/* 字符 "]}" 连续3步:先换行,再填充tab,再拷贝 */
			case 2:
				*res++ = '\n';
				resReduce--;
				tab--;
				padding = tab * indentSpace;
				type = 22;
				continue;
			case 22:
				if (padding > 0)
				{
					padding--;
					*res++ = ' ';
					resReduce--;
					continue;
				}
				type = 222;
				continue;
			case 222:
				*res++ = *json++;
				jsonReduce--;
				resReduce--;
				/* 返回 */
				if (jsonRet)
					*jsonRet = json;
				if (jsonReduceRet)
					*jsonReduceRet = jsonReduce;
				if (resRet)
					*resRet = res;
				if (resReduceRet)
					*resReduceRet = resReduce;
				if (tabRet)
					*tabRet = tab;
				return;
			/* 字符 ":" 连续2步:先拷贝,再空格 */
			case 3:
				*res++ = *json++;
				jsonReduce--;
				resReduce--;
				type = 33;
				continue;
			case 33:
				*res++ = ' ';
				resReduce--;
				break;
			/* 字符 "," 连续3步:先拷贝,再换行,再填充tab */
			case 4:
				*res++ = *json++;
				jsonReduce--;
				resReduce--;
				type = 44;
				continue;
			case 44:
				*res++ = '\n';
				resReduce--;
				padding = tab * indentSpace;
				type = 9;
				continue;
			/* 字符 " 切换为字符串拷贝模式 */
			case 5:
				_FormatJsonString(json, jsonReduce, res, resReduce, &json, &jsonReduce, &res, &resReduce);
				break;
			/* 行起始,补tab */
			case 9:
				if (padding > 0)
				{
					padding--;
					*res++ = ' ';
					resReduce--;
					continue;
				}
				break;
			}
			type = 0;
		}
	}
	/* 返回 */
	if (jsonRet)
		*jsonRet = json;
	if (jsonReduceRet)
		*jsonReduceRet = jsonReduce;
	if (resRet)
		*resRet = res;
	if (resReduceRet)
		*resReduceRet = resReduce;
	if (tabRet)
		*tabRet = tab;
}

size_t JsonFormat(const char* json, char* buff, size_t buffSize, uint32_t indentSpace)
{
    uint32_t tab = 0;
    if (!json || !buff || buffSize < 1)
	{
        return 0;
	}
	memset(buff, 0, buffSize);
    _FormatJson((char*)json, strlen(json), buff, buffSize, tab, NULL, NULL, NULL, NULL, NULL, indentSpace);
    return strlen(buff);
}
