#!/usr/bin/env python
# -*- coding:gbk -*-

class ListNode:
    def __init__(self, value: int):
        self.value, self.next = value, None

class RadixSort:
    def sort(self, head: ListNode) -> None:
        maxValue, minValue, current = head.next.value, head.next.value, head.next.next
        while current:
            if maxValue < current.value:
                maxValue = current.value
            if minValue > current.value:
                minValue = current.value
            current = current.next

        buckets = [ListNode(0) for _ in range(10)]

        diff, gap = maxValue - minValue, 1
        while gap <= diff:
            for bucket in buckets:
                bucket.next = None

            current = head.next
            while current:
                bucket = buckets[((current.value - minValue) // gap) % 10]
                while bucket.next:
                    bucket = bucket.next
                bucket.next, current, bucket.next.next = current, current.next, None

            current = head
            for bucket in buckets:
                current.next = bucket.next
                while current.next:
                    current = current.next
            current.next = None
            gap *= 10
