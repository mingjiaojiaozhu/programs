#!/usr/bin/env python
# -*- coding:gbk -*-

class RabinKarp:
    def search(self, text: str, pattern: str) -> int:
        code, patternCode = self.__getHashCode(text, len(pattern)), self.__getHashCode(pattern, len(pattern))
        for i in range(len(text) - len(pattern) + 1):
            if code == patternCode:
                index, patternIndex = i, 0
                while index < len(text):
                    if text[index] != pattern[patternIndex]:
                        break

                    if patternIndex == len(pattern) - 1:
                        return index - patternIndex
                    index += 1
                    patternIndex += 1

            if i < len(text) - len(pattern):
                code += ord(text[i + len(pattern)]) - ord(text[i])
        return -1

    def __getHashCode(self, text: str, length: int) -> int:
        code = 0
        for i in range(length):
            code += ord(text[i]) - ord('a')
        return code
