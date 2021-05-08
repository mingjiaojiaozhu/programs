#!/usr/bin/env python
# -*- coding:gbk -*-

class Manacher:
    def search(self, text: str) -> str:
        aux = '|' + '|'.join(list(text)) + '|'
        border, middle, center, maxLength, buckets = 0, 0, 0, 0, [0 for _ in range((len(text) << 1) + 1)]
        for i in range(len(buckets)):
            if i < border:
                index = (middle << 1) - i
                buckets[i] = min(buckets[index], border - i)
                if i + buckets[index] < border:
                    continue

            left, right = i - buckets[i] - 1, i + buckets[i] + 1
            while left >= 0 and right < len(buckets):
                if aux[left] != aux[right]:
                    break
                buckets[i] += 1

                left -= 1
                right += 1

            border, middle = buckets[i] + i, i
            if maxLength < buckets[i]:
                maxLength, center = buckets[i], i

        result = ''
        for value in aux[center - maxLength : center + maxLength + 1]:
            if '|' != value:
                result += value
        return result
